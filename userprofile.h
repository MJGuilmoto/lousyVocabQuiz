#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "connection.h"

class UserProfile
{

public:
    std::string username;
    std::string fullName;

public:
    UserProfile();
    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
    void saveStat(Connection conn);

};

#endif // USERPROFILE_H
