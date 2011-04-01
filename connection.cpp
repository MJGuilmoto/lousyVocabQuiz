/**
 * @file connection.cpp
 * @brief Defines a correspondence of meaning between two words.
 * @author Alex Zirbel
 *
 * Defines a correspondence between two words in given languages which are
 * closely enough related to be quizzed over.  Languages must be different,
 * but there are no constraints on the words.  This class also provides a hash
 * function for itself, which is useful for storing user data for a connection.
 */

#include "connection.h"

using namespace std;

Connection::Connection(string myLang1, string myLang2, string myWord1, string myWord2)
{
    if(boost::iequals(myLang1, myLang2))
    {
        InvalidLanguageException exception;
        throw exception;
    }

    if(boost::algorithm::lexicographical_compare(myLang1, myLang2, boost::is_iless()))
    {
        lang1 = myLang1;
        lang2 = myLang2;
        word1 = myWord1;
        word2 = myWord2;
    }
    else
    {
        lang1 = myLang2;
        lang2 = myLang1;
        word1 = myWord2;
        word2 = myWord1;
    }
}

int Connection::hashCode()
{
    return 0;
}

string Connection::getLang1()
{
    return lang1;
}

string Connection::getLang2()
{
    return lang2;
}

string Connection::getWord1()
{
    return word1;
}

string Connection::getWord2()
{
    return word2;
}

/**
 * Compares two connections to see if their basic information matches.
 * Basic information: lang1, lang2, word1, word2
 * @return true If languages and words are both the same, false otherwise.
 */
bool Connection::basicEquals(Connection conn2, bool caseSensitive)
{
    if(!boost::iequals(lang1, conn2.getLang1()))
        return false;
    if(!boost::iequals(lang2, conn2.getLang2()))
        return false;

    if(caseSensitive)
    {
        if(!boost::equals(word1, conn2.getWord1()))
            return false;
        if(!boost::equals(word2, conn2.getWord2()))
            return false;
    }
    else
    {
        if(!boost::iequals(word1, conn2.getWord1()))
            return false;
        if(!boost::iequals(word2, conn2.getWord2()))
            return false;
    }

    return true;
}
