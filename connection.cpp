/**
 * @file connection.cpp
 * @brief Defines a correspondence of meaning between two words.
 * @author Alex Zirbel
 *
 * Defines a correspondence between two words in given languages which are
 * closely enough related to be quizzed over.  Languages must be different,
 * but there are no constraints on the words.
 *
 * Note that this class maintains an important invariant that languages
 * are always sorted alphabetically, ie lang1 always preceeds lang2
 * alphabetically.
 */

#include "connection.hpp"

using namespace std;
using namespace boost;
using boost::lexical_cast;
using boost::bad_lexical_cast;  // Used to catch bad lexical casts

/**
 * Declares an invalid connection with no data.
 *
 * While it is possible to instantiate a blank connection, the valid field
 * in the exception is set to false to signal that the connection should
 * not be treated as legitimate.
 */
Connection::Connection()
{
    word1 = "";
    word2 = "";
    lang1 = "";
    lang2 = "";
    valid = false;
}


/**
 * Initializes a connection. This is the only allowed way to add a new
 * connection. Upon initialization, this constructor orders the languages in
 * alphabetical order and checks for problems.
 * @param myLang1 The first language. Does not have to be first alphabetically.
 * @param myLang2 The second language.
 * @param myWord1 The word in the language of myLang1
 * @param myWord2 The word in the language of myLang2
 */
Connection::Connection(string myLang1, string myLang2,
    string myWord1, string myWord2)
{
    // Languages must be different, ignoring case
    if(boost::iequals(myLang1, myLang2))
    {
        throw new InvalidLanguageException;
    }

    storeInCorrectOrder(myLang1, myLang2, myWord1, myWord2);

    userProficiency = DEFAULT_PROFICIENCY;
    lastQuizzed = (time_t) 0;

    valid = true;
}


/**
 * Used in conjunction with blank connection instantiation, sets Connection
 * data as parsed from the line.  This should be the only method used to
 * read data from lines anywhere in the program.
 * @param line The string to read data from, assumed to store data in the
 *      following format: <word1>\t<word2>\t<proficiency>\t<lastquizzed>
 * @param myLang1 The language corresponding to the connection's first word
 * @param myLang2 The language corresponding to the connection's second word
 */
bool Connection::loadFromLine(string line, string myLang1, string myLang2)
{
    string myWord1, myWord2;

    // Tokenize based on tab characters
    char_separator <char> sep("\t");
    tokenizer<char_separator <char> > tokens(line, sep);
    tokenizer<char_separator <char> >::iterator itr = tokens.begin();

    // Make sure there are at least two tokens; ignore any additional
    myWord1 = *itr;
    itr++;
    if(itr == tokens.end())
        return false;
    myWord2 = *itr;

    storeInCorrectOrder(myLang1, myLang2, myWord1, myWord2);

    itr++;
    if(itr == tokens.end())
    {
        userProficiency = DEFAULT_PROFICIENCY;
        lastQuizzed = 0;
        valid = true;
        return true;
    }

    // Get the user proficiency, or return a problem load
    try
    {
        userProficiency = lexical_cast<int>(*itr);
    }
    catch(bad_lexical_cast &)
    {
        return false;
    }

    itr++;
    if(itr == tokens.end())
    {
        lastQuizzed = 0;
        valid = true;
        return true;
    }

    // Get the last time quizzed, or return a problem load
    try
    {
        lastQuizzed = (time_t) lexical_cast<unsigned int>(*itr);
    }
    catch(bad_lexical_cast &)
    {
        return false;
    }

    // If the whole load worked, the connection is valid.
    valid = true;
    return true;
}


/**
 * Displays connection data as a string representing the line of a
 * file.  Should be the only method used to push Connection data to a
 * file.
 */
string Connection::exportToLine()
{
    stringstream line;

    line << word1 << "\t" << word2 << "\t" << userProficiency << "\t"
        << ((unsigned int) lastQuizzed);
    
    return line.str();
}


/**
 * Accessor for lang1
 * @return lang1 The first language alphabetically
 */
string Connection::getLang1()
{
    return lang1;
}


/**
 * Accessor for lang2
 * @return lang2 The second language alphabetically
 */
string Connection::getLang2()
{
    return lang2;
}


/**
 * Accessor for word1
 * @return word1 The word corresponding to the first language
 */
string Connection::getWord1()
{
    return word1;
}


/**
 * Accessor for word2
 * @return word2 The word corresponding to the second language
 */
string Connection::getWord2()
{
    return word2;
}


/**
 * Compares two connections to see if their basic information matches.
 * Basic information: lang1, lang2, word1, word2
 *
 * @param conn2 The other connection to compare to
 * @param caseSensitive Whether to check words for case sensitivity. Note that
 *  languages will always be compared case insensitive.
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


/**
 * An accessor the check whether the connection is valid.
 * @return True for a valid connection, false otherwise.
 */
bool Connection::isValid()
{
    return valid;
}


/**
 * Given languages and words which correspond (myLang1 is the language
 * of myWord1), stores the data with lang1 being first alphabetically.
 */
void Connection::storeInCorrectOrder(string myLang1, string myLang2,
                                     string myWord1, string myWord2)
{
    // Ensure languages are sorted alphabetically when stored
    if(boost::algorithm::lexicographical_compare
        (myLang1, myLang2, boost::is_iless()))
    {
        // Languages were specified in order
        lang1 = myLang1;
        lang2 = myLang2;
        word1 = myWord1;
        word2 = myWord2;
    }
    else
    {
        // Swap words and languages
        lang1 = myLang2;
        lang2 = myLang1;
        word1 = myWord2;
        word2 = myWord1;
    }
}


