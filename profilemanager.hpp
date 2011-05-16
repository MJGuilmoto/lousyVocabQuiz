/**
 * @file profilemanager.hpp
 * @brief Header definitions for the profile manager class.
 * @author Alex Zirbel
 */

#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <iostream>
#include "userprofile.hpp"
#include "exceptions.hpp"
#include "util_global.hpp"

#include "boost/algorithm/string.hpp"

class ProfileManager
{

public:
    ProfileManager();

    UserProfile* createNewProfile(std::string username);
    UserProfile* loadProfile(std::string username);
    bool isValidUsername(std::string username);
    bool profileExists(std::string username);

private:
    bool fexists(std::string filename);
    bool legalCharacter(char c);
    std::string usernameToFilename(std::string username);

};

#endif // PROFILEMANAGER_H
