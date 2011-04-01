/**
 * @file dictionary.cpp
 * @brief A class to keep track of a list of words and their translations.
 * @author Alex Zirbel
 *
 * The dictionary class contains functions to load, and eventually edit and
 * save, word lists.  It loads the lists into a bidirectional map
 * (boost::bimap) and stores them in an iterable way.

 * @todo make this an interface, and then implement it with two types:
 * 1. CustomDictionary doens't worry about any error checking, syncing,
 *      word lists, or language-specific stuff.
 * 2. StandardDictionary makes sure that all the words for a particular
 *      language are consistent, tries to help with style, etc.
 */

#include "dictionary.h"

using namespace std;
using namespace boost;

/**
 * Constructs a default dictionary based on a hardcoded path to a word list.
 */
Dictionary::Dictionary(string dictionaryFile)
{
    loadFromFile(dictionaryFile);
}

/**
 * Displays the dictionary name, the direction of translation, and all
 * contents of the given dictionary.
 * @param direction 1 (STANDARD): traverse from lang1 to lang2; or 0 (REVERSE)
 * @todo remove this method.
 */
void Dictionary::printContents()
{
    for( DictMap::const_iterator itr = dict.begin(); itr != dict.end(); itr++ )
    {
        cout << itr->get<lang1>() << " <=> " << itr->get<lang2>() << endl;
    }
}

/**
 * Loads the contents of a file (here, one-to-one translation information)
 * into a DictMap for later use.
 * @param filename The path and name of the file to load.
 */
void Dictionary::loadFromFile(string filename)
{
    ifstream dictFile;
    dictFile.open(filename.c_str(), ifstream::in);

    // Check for failed file open
    if(!dictFile.is_open())
    {
        LoadFileException exception;
        throw exception;
    }

    string line;

    // The first line of the file is the dictionary name
    getline(dictFile, listName);

    // Read the languages from the top of the dictionary file
    getline(dictFile, line);

    if(dictFile.eof())
    {
        // This is a malformed file if it does not have languages first.
        LoadFileException exception;
        throw exception;
    }

    // Tokenize based on tab characters
    char_separator <char> sep("\t");
    tokenizer <char_separator <char> > tokens(line, sep);
    tokenizer<char_separator <char> >::iterator itr = tokens.begin();
    string myLang1 = *itr;

    // Make sure there are at least two tokens; ignore any additional
    itr++;
    if(itr == tokens.end())
    {
        throw new LoadFileException;
    }
    string myLang2 = *itr;

    // Add to the dictionary (DictMap)
    bool isBackward = false;

    cout << "MyLang1: <" << myLang1 << ">, myLang2: <" << myLang2 << ">" << endl;

    // Check to see if the languages are equal (this is not allowed)
    if(boost::iequals(myLang1, myLang2))
    {
        throw new LoadFileException;
    }

    // isBackward makes sure the languages are sorted alphabetically when
    // words are added to the dictionary.
    if(boost::ilexicographical_compare(myLang1, myLang2) < 0)
    //if(boost::algorithm::lexicographical_compare(myLang1, myLang2, boost::is_iless()) < 0)
    {
        isBackward = true;
        lang1Name = myLang2;
        lang2Name = myLang1;
    }
    else
    {
        isBackward = false;
        lang2Name = myLang2;
        lang1Name = myLang1;
    }

    return;

    // Read the entire dictionary file
    while(dictFile.good())
    {
        getline(dictFile, line);

        if(dictFile.eof())
            break;

        // Tokenize based on tab characters
        char_separator <char> sep("\t");
        tokenizer <char_separator <char> > tokens(line, sep);
        tokenizer<char_separator <char> >::iterator itr = tokens.begin();
        string key = *itr;

        // Make sure there are at least two tokens; ignore any additional
        itr++;
        if(itr == tokens.end())
        {
            throw new LoadFileException;
        }

        // Add to the dictionary (DictMap)
        if(isBackward)
            dict.push_back( translation(*itr, key) );
        else
            dict.push_back( translation(key, *itr) );
    }

    dictFile.close();
}

/**
 * An accessor for the dictionary list.
 * @return DictMap A DictMap object with all the words and translations.
 */
DictMap Dictionary::getDictionary()
{
    return dict;
}

string Dictionary::getLang1Name()
{
    return lang1Name;
}

string Dictionary::getLang2Name()
{
    return lang2Name;
}

string Dictionary::getDictionaryName()
{
    return listName;
}
