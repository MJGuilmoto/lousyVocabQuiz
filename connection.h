#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>

class Connection
{
//! Lang1 is the first language alphabetically.
std::string lang1;
//! Lang2 is the second language alphabetically.
std::string lang2;
//! A rating from 0 to 100, how well the user knows the word.
int userKnowledge;
/** The last time this connection was quizzed on (unimplemented)
 * @todo Implement this, and make it its own data type (Date) */
int lastQuizzed;

public:
    Connection();
    int hashCode();
};

#endif // CONNECTION_H
