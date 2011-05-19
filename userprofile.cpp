/**
 * @file userprofile.cpp
 * @brief Stores information for a given username: statistics and dictionaries
 * @author Alex Zirbel
 *
 * Stores all the data associated with a given user.
 * Contains load and save functions to store this information in a file and to
 * retrieve the information.
 */

#include "userprofile.hpp"

using namespace std;
using namespace boost;

// Necessary for use in the BOOST_FOREACH macro.
typedef pair<LanguagePair, MasterList> pair_t;

UserProfile::UserProfile()
{
    username = "";
    fullName = "";
    valid = false;
}


/**
 * Creates a new user profile with minimal information.
 */
UserProfile::UserProfile(string newUsername)
{
    username = newUsername;
    fullName = "";
    valid = true;
}


/**
 * Creates a new user profile with full information.
 */
UserProfile::UserProfile(string newUsername, string newFullName)
{
    username = newUsername;
    fullName = newFullName;
    valid = true;
}


/**
 * Returns the user's master list for the specified languages.
 * @param languages The language pair to be found.
 * @return The MasterList containing all words in those languages.
 * @todo Make sure it doesn't matter which language is home: we should only
 *  find one set of languages. This should be taken care of already though.
 */
MasterList* UserProfile::getMasterListForLanguages(LanguagePair languages)
{
    if(!valid)
        throw new InvalidUserProfileException;

    return &((*(masterListMap.find(languages))).second);
}


/**
 * Saves all information of a user profile in text format to the specified
 * profile file.
 * @param filename The full path and name of the file
 * @return True if the save was successful, false otherwise.
 * @todo Don't save as plaintext: encrypt somehow so users don't game the
 *  system.
 */
bool UserProfile::saveProfile(string filename)
{
    if(!valid)
        throw new InvalidUserProfileException;

    ofstream userFile;
    userFile.open(filename.c_str(), ofstream::out);

    // Check for failed file open
    if(!userFile.is_open())
        return false;

    userFile << username << endl;
    userFile << fullName << endl;

    BOOST_FOREACH(pair_t pair, masterListMap)
    {
        userFile << "---\n";

        LanguagePair lp = pair.first;
        MasterList list = pair.second;

        userFile << lp.lang1 << "\t" << lp.lang2 << "\t"
                << lp.homeLang << endl;

        std::list<Connection>::iterator itr;
        for(itr = list.connList.begin(); itr != list.connList.end(); itr++)
        {
            Connection conn = *itr;
            userFile << conn.exportToLine() << endl;
        }
    }

    userFile.close();

    return true;
}


/**
 * Loads a user profile from a file and sets the valid tag to true.
 * @param filename The file containing correctly formatted UserProfile data
 * @return True if the load was successful, false otherwise.
 */
bool UserProfile::loadProfile(string filename)
{
    // Temporarily holds lines read from the file
    string line;

    ifstream userFile;
    userFile.open(filename.c_str(), ifstream::in);

    // Check for failed file open
    if(!userFile.is_open())
    {
        cout << "Failed file open." << endl;
        return false;
    }

    if(userFile.eof())
    {
        cout << "Unexpected end of file." << endl;
        return false;
    }

    // The first line of the file is the username
    getline(userFile, username);

    if(userFile.eof())
        return false;

    // The second line of the file is the full name
    getline(userFile, fullName);

    getline(userFile, line);

    // Clear out any masterLists in case load is called after some
    // other initialization.
    masterListMap.clear();

    // Loop to load a master list for each language pair
    while(userFile.good())
    {
        if(line.compare("\n") == 0)
            break;

        if(line.compare("---") != 0)
        {
            getline(userFile, line);
            continue;
        }
        cout << "Found master language!" << endl;

        getline(userFile, line);

        // Load the language pair
        LanguagePair *languages = new LanguagePair;
        int status;

        if(!languages->loadFromLine(line, &status))
        {
            cout << "Problem loading language pair." << endl;
            free(languages);
            continue;
        }

        if(masterListMap.find(*languages) != masterListMap.end())
        {
            cout << "Duplicate languages list." << endl;
            free(languages);
            continue;
        }

        /* Essentially undoes the alphabetical sorting. This is necessary for
           the moment: adding connections needs the languages unsorted again,
           and the connections will sort themselves upon construction. */
        string myLang1 = (status == 0) ? languages->lang1 : languages->lang2;
        string myLang2 = (status == 0) ? languages->lang2 : languages->lang1;

        MasterList *mList = new MasterList(*languages);

        // Fill the master list with connections
        while(userFile.good())
        {
            getline(userFile, line);

            if(line.compare("---") == 0 || line.compare("\n") == 0 || line.empty())
                break;

            Connection *conn = new Connection;

            // Add the connection to the list if the connection loaded.
            //! @todo Maintain a list of failed loads and print error reports.
            if(conn->loadFromLine(line, myLang1, myLang2))
            {
                mList->connList.push_back(*conn);
            }
            else
            {
                cout << "Connection misload." << endl;
                free(conn);
            }
        }

        masterListMap.insert(make_pair(languages, mList));
    }

    userFile.close();

    valid = true;
    return true;
}


string UserProfile::getUsername()
{
    return username;
}



string UserProfile::getFullName()
{
    return fullName;
}


bool UserProfile::isValid()
{
    return valid;
}
