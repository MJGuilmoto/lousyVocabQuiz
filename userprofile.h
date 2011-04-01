#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <fstream>

#include "connection.h"
#include "quizlist.h"

#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/bimap.hpp>

#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/algorithm/string.hpp>

class UserProfile
{
std::string username;
std::string fullName;

public:
    UserProfile();
    void saveProfileToFile(std::string filename);
    void loadProfileFromFile(std::string filename);
    MasterList* getMasterListForLanguages(std::string lang1, std::string lang2);
    void saveMasterList(QuizList* masterList);

};

#endif // USERPROFILE_H
