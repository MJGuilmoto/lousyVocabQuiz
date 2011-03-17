#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <iostream>
#include "userprofile.h"
#include "exceptions.h"

class ProfileManager
{

public:
    ProfileManager();

    UserProfile* createNewProfile(std::string username);
    UserProfile* loadProfile(std::string username);
    void saveToFile(UserProfile profile);
    bool profileExists(std::string username);
};

#endif // PROFILEMANAGER_H
