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

#include "quizlist.h"

using namespace std;
using namespace boost;

QuizList::QuizList()
{
    listItr = connList.begin();
}

void QuizList::sortByLang1()
{
}

void QuizList::sortByLang2()
{
}

void QuizList::sortByLeastKnown()
{
}

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

void QuizList::sortByRecentlyQuizzed()
{
}

bool QuizList::contains(Connection conn, bool caseSensitive)
{
    list<Connection>::iterator itr;

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

bool MasterList::loadFromFile()
{
    return true;
}

bool MasterList::saveToFile()
{
    return true;
}
