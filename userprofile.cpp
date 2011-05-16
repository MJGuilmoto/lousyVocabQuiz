/**
 * @file userprofile.cpp
 * @brief Stores information for a given username: statistics and dictionaries
 * @author Alex Zirbel
 *
 * Stores all the data associated with a given user.
 */

#include "userprofile.hpp"

using namespace std;
using namespace boost;

typedef pair<LanguagePair, MasterList> pair_t;

UserProfile::UserProfile()
{
    username = "";
    fullName = "";
    valid = false;
    cout << "Blank (invalid) user profile created." << endl;
}

/**
 * Creates a new user profile with minimal information.
 */
UserProfile::UserProfile(string newUsername)
{
    username = newUsername;
    fullName = "";
    valid = true;
    cout << "New user profile created, with username but no full name." << endl;
}

/**
 * Creates a new user profile with full information.
 */
UserProfile::UserProfile(string newUsername, string newFullName)
{
    username = newUsername;
    fullName = newFullName;
    valid = true;
    cout << "New user profile created, with username and password." << endl;
}

MasterList* UserProfile::getMasterListForLanguages(LanguagePair languages)
{
    if(!valid)
        throw new InvalidUserProfileException;

    return &((*(masterListMap.find(languages))).second);
}


bool UserProfile::saveProfile(string filename)
{
    cout << "Saving profile..." << endl;

    if(!valid)
        throw new InvalidUserProfileException;

    ofstream userFile;
    userFile.open(filename.c_str(), ofstream::out);

    // Check for failed file open
    if(!userFile.is_open())
        return false;

    cout << "Printing user info." << endl;

    userFile << username << endl;
    userFile << fullName << endl;

    cout << "Masterlistmap size: " << masterListMap.size() << endl;

    BOOST_FOREACH(pair_t pair, masterListMap)
    {
        cout << "Printing master list." << endl;

        userFile << "---\n";

        LanguagePair lp = pair.first;
        MasterList list = pair.second;

        lp.printContents();
        list.printContents();

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

    cout << "Saved profile." << endl;

    return true;
}


bool UserProfile::loadProfile(string filename)
{
    cout << "Loading profile..." << endl;

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
        if(!languages->loadFromLine(line))
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

        MasterList *mList = new MasterList(*languages);

        // Fill the master list with connections
        while(userFile.good())
        {
            getline(userFile, line);
            cout << "Got line: <" << line << ">" << endl;

            if(line.compare("---") == 0 || line.compare("\n") == 0 || line.empty())
                break;

            Connection *conn = new Connection;

            //! @todo Maintain a list of failed loads and print error reports.
            // Add the connection to the list if the connection loaded.
            if(conn->loadFromLine(line, languages->lang1, languages->lang2))
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

    //debug
    //! @todo remove
    saveProfile("/home/azirbel/Desktop/temp.txt");

    cout << "Loaded user profile." << endl;
    return true;
}
