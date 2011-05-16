/**
 * @file profilemanager.cpp
 * @brief Keeps track of saving and loading user profiles.
 * @author Alex Zirbel
 *
 * A class to help in saving, loading, creating, and searching user profiles.
 * The user profile itself stores all the data a user has entered, any
 * other information provided (real name, screen name), and word lists for
 * that user (which should be private from other users).
 */

#include "profilemanager.hpp"

using namespace std;

ProfileManager::ProfileManager()
{
    //! @todo make sure there is a folder for profiles
}


/**
 * Makes a new profile for the username specified.
 *
 * @todo Check that this username doesn't exit already (user profileExists()),
 *  check for other invalid problems, and create the actual file to make sure
 *  saving the profile will work correctly later.
 */
UserProfile* ProfileManager::createNewProfile(string username)
{
    if(!isValidUsername(username))
        throw new InvalidUsernameException;

    return new UserProfile;
}


/**
 * Loads a user profile from a file.
 * Assumes the "username" profile exists; throws an exception if not.
 */
UserProfile* ProfileManager::loadProfile(string username)
{
    if(!isValidUsername(username))
        throw new InvalidUsernameException;

    if(!profileExists(username))
    {
        NoSuchProfileException exception;
        throw exception;
    }

    string filename = usernameToFilename(username);

    UserProfile *toReturn = new UserProfile;
    toReturn->loadProfile(filename);

    return toReturn;
}


/**
 * Checks through the list of saved profiles (or rather, though actual
 * filenames in the profiles/ folder) to see if a user has created a profile
 * yet.
 * @return true if the profile exists, false otherwise.
 */
bool ProfileManager::profileExists(string username)
{
    if(!isValidUsername(username))
        throw new InvalidUsernameException;

    string filename = usernameToFilename(username);

    return fexists(filename);
}


/**
 * Takes a username (assumed to be valid; throws an exception if not)
 * and converts it to a full path filename.
 * @todo Change to return the correct filename given different operating
 *  systems.
 */
string ProfileManager::usernameToFilename(string username)
{
    if(!isValidUsername(username))
        throw new InvalidUsernameException;

    // Convert to lowercase for all filenames (case insensitive).
    boost::to_lower(username);

    string filename = WORDQUIZ_DIR;
    filename.append("profiles/");
    filename.append(username);
    filename.append(".txt");

    return filename;
}


/**
 * Ensures that usernames contain only normal characters which would
 * not corrupt filenames.
 */
bool ProfileManager::isValidUsername(string username)
{
    //! @todo Ideally, just use regex. I was having trouble linking with boost
    string::iterator itr;
    for(itr = username.begin(); itr != username.end(); itr++)
    {
        if(!legalCharacter(*itr))
            return false;
    }
    return true;
}


/**
 * Checks if a character is alphanumeric, or a hyphen or underscore.
 */
bool ProfileManager::legalCharacter(char c)
{
    if(isalnum(c) || c == '-' || c == '_')
        return true;

    return false;
}


/**
 * Attempt to open a file to check if it exists.
 */
bool ProfileManager::fexists(string filename)
{
    ifstream ifile(filename.c_str());
    return ifile;
}
