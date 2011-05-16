/**
 * @file quizlist.cpp
 * @brief Stores a sorted list of connections for a given language.
 * @author Alex Zirbel
 *
 * This class functions as both a general-use dictionary and a partial list
 * of words for use in a quiz.  All words are stored as Connections, containing
 * the words, languages, and statistics of each word.
 *
 * We assume as invariants that the languages of each connection are the same
 * as the languages of the quiz as a whole.
 *
 * The general QuizList class is more useful on a quiz-by-quiz basis, and
 * contains several functions to sort its words in different orders so that
 * they can be presented to the user by least known, etc.
 *
 * However, these functions can also be used to display the words in a list
 * of a user's entire dictionary.  For this purpose, a MasterList is intended
 * to store all the words in a user's dictionary for a certain language.
 */

#include "quizlist.hpp"

using namespace std;
using namespace boost;

/**
 * Resets the QuizList to the beginning of the list
 */
QuizList::QuizList()
{
    listItr = connList.begin();
}


/**
 * Resets the MasterList iterator to the beginning of the list
 */
MasterList::MasterList()
{
    listItr = connList.begin();
}


/**
 * Sets the master list to the specified languages.
 */
MasterList::MasterList(LanguagePair languages)
{
    lang1 = languages.lang1;
    lang2 = languages.lang2;
}


/**
 * Builds a MasterList as a duplicate of an existing MasterList.
 * Simply copies the fields.
 * Seems to be required by std::make_pair.
 */
MasterList::MasterList(MasterList* existing)
{
    lang1 = existing->lang1;
    lang2 = existing->lang2;
    listName = existing->listName;
    connList = existing->connList;
    listItr = existing->listItr;
}


/**
 * Sorts the words so that they are ordered alphabetically by the first
 * language (alphabetically). 'A' words will come before 'Z' words.
 */
void QuizList::sortByLang1()
{
}

/**
 * Sorts the words so that they are ordered alphabetically by the second
 * language (alphabetically). 'A' words will come before 'Z' words.
 */
void QuizList::sortByLang2()
{
}

/**
 * Sorts based on each connection's userProficiency variable, so that words
 * with the lowest proficiency rating come first.
 */
void QuizList::sortByLeastKnown()
{
}

/**
 * Sorts based on each connection's userProficiency variable, so that words
 * with the lowest proficiency rating come last.
 */
void QuizList::sortByMostKnown()
{
    sortByLeastKnown();
    connList.reverse();
}

/*
 RANDOMIZE code

srand( time(NULL) );
int nextElementIndex = rand() % quizList.size();
set<int>::iterator listItr = quizList.begin();
for(int i=0; i<nextElementIndex; i++) listItr++;
int nextElementNum = *listItr;
quizList.erase( quizList.find(nextElementNum) );
*/

//! Unimplemented until connection's last quizzed variable is implemented
void QuizList::sortByLastQuizzed()
{
}

/**
 * Sort the words so that the most recently quizzed word comes first.
 */
void QuizList::sortByRecentlyQuizzed()
{
    sortByLastQuizzed();
    connList.reverse();
}

/**
 * Check if the QuizList contains a given connection.
 *
 * Useful to see if an answer is allowable. If a word has multiple translations
 * and the user answered a legitimate but unexpected response, we should
 * check the whole quizlist to see if the user got the word right. We don't
 * want to punish the user for answering synonyms.
 *
 * @param conn The connection to check for
 * @param caseSensitive Whether to check for case sensitivity of words.
 */
bool QuizList::contains(Connection conn, bool caseSensitive)
{
    list<Connection>::iterator itr;

    // Search the list, check each connection.
    //! @todo Add hashing to make this faster?
    for(itr = connList.begin(); itr != connList.end(); itr++)
    {
        if(conn.basicEquals(*itr, caseSensitive))
        {
            return true;
        }
    }

    return false;
}

/**
 * Builds a master list out of a text file in the expected format. The file
 * must begin with the list name on a new line, followed by tab-separated
 * languages on a new line, and then tab-separated words on each new line
 * in the remainder of the file.
 * @todo This is more of a temporary function and should be converted into
 *  a more friendly function at some point.
 * @param filename The location of the text file to load
 * @return True if the load was successful, false otherwise
 */
bool MasterList::importDictionaryFromFile(std::string filename)
{
    /** @todo When the file reading fails, should this function return false
        or throw an exception? Right now it throws an exception. */

    // Temporarily holds lines read from the file
    string line;

    ifstream dictFile;
    dictFile.open(filename.c_str(), ifstream::in);

    // Check for failed file open
    if(!dictFile.is_open())
        throw new LoadFileException;

    // The first line of the file is the dictionary name
    getline(dictFile, listName);

    // Read the languages from the top of the dictionary file
    getline(dictFile, line);

    if(dictFile.eof())
        throw new LoadFileException;

    // Tokenize based on tab characters
    char_separator <char> sep("\t");
    tokenizer <char_separator <char> > tokens(line, sep);
    tokenizer<char_separator <char> >::iterator itr = tokens.begin();

    // Make sure there are at least two tokens; ignore any additional
    lang1 = *itr;
    itr++;
    if(itr == tokens.end())
        throw new LoadFileException;
    lang2 = *itr;

    // Check to see if the languages are equal (this is not allowed)
    if(boost::iequals(lang1, lang2))
        throw new LoadFileException;

    // Read the entire dictionary file
    while(dictFile.good())
    {
        getline(dictFile, line);

        if(dictFile.eof())
            break;

        // Tokenize based on tab characters
        tokenizer <char_separator <char> > tokens(line, sep);
        tokenizer<char_separator <char> >::iterator itr = tokens.begin();

        // Make sure there are at least two tokens; ignore any additional
        string word1 = *itr;
        itr++;
        if(itr == tokens.end())
            throw new LoadFileException;
        string word2 = *itr;

        // Create a Connection and add it to the master list
        Connection *conn = new Connection(lang1, lang2, word1, word2);
        connList.push_back(*conn);
    }

    dictFile.close();
    return true;
}

/**
 * A debugging tool to print out a user's entire dictionary.
 */
void MasterList::printContents()
{
    cout << "Master List: " << listName << endl;
    cout << "Languages: " << lang1 << ", " << lang2 << endl;
    for(listItr = connList.begin(); listItr != connList.end(); listItr++)
    {
        Connection conn = *listItr;
        cout << "  " << conn.getWord1() << " <==> " << conn.getWord2() << endl;
    }
}

/**
 * Builds a master list out of a text file in the expected format. The file
 * must begin with the list name on a new line, followed by tab-separated
 * languages on a new line, and then tab-separated words on each new line
 * in the remainder of the file.
 * @param filename The location of the text file to load
 * @return True if the load was successful, false otherwise
 */
bool MasterList::loadFromFile(std::string filename)
{
    /** @todo When the file reading fails, should this function return false
        or throw an exception? Right now it returns false. */

    // Temporarily holds lines read from the file
    string line;

    ifstream dictFile;
    dictFile.open(filename.c_str(), ifstream::in);

    // Check for failed file open
    if(!dictFile.is_open())
        return false;

    // The first line of the file is the dictionary name
    getline(dictFile, listName);

    // Read the languages from the top of the dictionary file
    getline(dictFile, line);

    if(dictFile.eof())
        return false;

    // Tokenize based on tab characters
    char_separator <char> sep("\t");
    tokenizer <char_separator <char> > tokens(line, sep);
    tokenizer<char_separator <char> >::iterator itr = tokens.begin();

    // Make sure there are at least two tokens; ignore any additional
    lang1 = *itr;
    itr++;
    if(itr == tokens.end())
        throw new LoadFileException;
    lang2 = *itr;

    // Check to see if the languages are equal (this is not allowed)
    if(boost::iequals(lang1, lang2))
        return false;

    // Read the entire dictionary file
    while(dictFile.good())
    {
        getline(dictFile, line);

        if(dictFile.eof())
            break;

        // Tokenize based on tab characters
        tokenizer <char_separator <char> > tokens(line, sep);
        tokenizer<char_separator <char> >::iterator itr = tokens.begin();

        // Make sure there are at least two tokens; ignore any additional
        string word1 = *itr;
        itr++;
        if(itr == tokens.end())
            return false;
        string word2 = *itr;

        // Create a Connection and add it to the master list
        Connection *conn = new Connection(lang1, lang2, word1, word2);
        connList.push_back(*conn);
    }

    dictFile.close();
    return true;
}

//! @todo Implement
bool MasterList::saveToFile(std::string filename)
{
    ofstream dictFile;
    dictFile.open(filename.c_str(), ofstream::out);

    // Check for failed file open
    if(!dictFile.is_open())
        return false;

    std::list<Connection>::iterator itr;
    for(itr = connList.begin(); itr != connList.end(); itr++)
    {

    }

    dictFile.close();

    return true;
}
