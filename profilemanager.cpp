#include "profilemanager.h"

ProfileManager::ProfileManager()
{
}

UserProfile* ProfileManager::createNewProfile(std::string username)
{
    return new UserProfile;
}

/** Assumes the "username" profile exists; throws an exception if not */
UserProfile* ProfileManager::loadProfile(std::string username)
{
    if(!profileExists(username))
    {
        NoSuchProfileException exception;
        throw exception;
    }
    return new UserProfile;
}

bool ProfileManager::profileExists(std::string username)
{
    return false;
}
