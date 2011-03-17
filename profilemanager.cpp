#include "profilemanager.h"

//! @todo Implement
ProfileManager::ProfileManager()
{
}

//! @todo Implement
UserProfile* ProfileManager::createNewProfile(std::string username)
{
    return new UserProfile;
}

/** Assumes the "username" profile exists; throws an exception if not */
//! @todo Implement
UserProfile* ProfileManager::loadProfile(std::string username)
{
    if(!profileExists(username))
    {
        NoSuchProfileException exception;
        throw exception;
    }
    return new UserProfile;
}

//! @todo Implement
void ProfileManager::saveToFile(UserProfile profile)
{
}

//! @todo Implement
bool ProfileManager::profileExists(std::string username)
{
    return false;
}
