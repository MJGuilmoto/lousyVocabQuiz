#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "exceptions.h"

class Connection
{
//! Lang1 is the first language alphabetically.
std::string lang1;
//! Lang2 is the second language alphabetically.
std::string lang2;

// The word itself and its translation
std::string word1;
std::string word2;

//! A rating from 0 to 100, how well the user knows the word.
int userProficiency;

/** The last time this connection was quizzed on (unimplemented)
 * @todo Implement this, and make it its own data type (Date) */
int lastQuizzed;

//! @todo Implement a list of dictionaries this word occurs in,
//! and lists of last quizzed and how well the user did
//! @todo More stats, like date added to your dictionary, etc?

public:
    Connection(std::string myLang1, std::string myLang2,
               std::string myWord1, std::string myWord2);
    int hashCode();
    int getUserProficiency();
    int getLastQuizzed();
    std::string getLang1();
    std::string getLang2();
    std::string getWord1();
    std::string getWord2();
    bool basicEquals(Connection conn2, bool caseSenstive);
};

#endif // CONNECTION_H
