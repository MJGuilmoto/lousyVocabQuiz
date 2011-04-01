#include "userprofile.h"

using namespace std;
using namespace boost;

UserProfile::UserProfile()
{
}

void UserProfile::saveProfileToFile(std::string filename)
{
}

void UserProfile::loadProfileFromFile(std::string filename)
{
}

MasterList* UserProfile::getMasterListForLanguages(std::string lang1, std::string lang2)
{
    return new MasterList;
}

void UserProfile::saveMasterList(QuizList* masterList)
{
}
