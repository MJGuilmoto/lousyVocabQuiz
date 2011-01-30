#include "dictionary.h"

/**
 * TODO: make this an interface, and then implement it with two types:
 * 1. CustomDictionary doens't worry about any error checking, syncing,
 *      word lists, or language-specific stuff.
 * 2. StandardDictionary makes sure that all the words for a particular
 *      language are consistent, tries to help with style, etc.
 */

using namespace std;
using namespace boost;



Dictionary::Dictionary()
{
    listName = "Default wordlist";

    loadFromFile("/home/azirbel/Dropbox/programming/qt/WordQuiz/dict.txt");
}

void Dictionary::printContents()
{
    cout << listName << " contents:" << endl;
    for(DictItr itr (dict.begin()); itr != dict.end(); itr++)
    {
        cout << itr->first << " <=> " << itr->second << endl;
    }
}

void Dictionary::loadFromFile(string filename)
{
    ifstream dictFile;
    dictFile.open(filename);

    /* Check for failed file open */
    if(!dictFile.is_open())
    {
        LoadFileException exception;
        throw exception;
    }

    string line;

    /* Read the entire dictionary file */
    while(dictFile.good())
    {
        getline(dictFile, line);

        if(dictFile.eof())
            break;

        /* Tokenize based on tab characters */
        char_separator <char> sep("\t");
        tokenizer <char_separator <char> > tokens(line, sep);
        tokenizer<char_separator <char> >::iterator itr = tokens.begin();
        string key = *itr;

        /* Make sure there are at least two tokens; ignore any additional */
        itr++;
        if(itr == tokens.end())
        {
            LoadFileException exception;
            throw exception;
        }
        dict[key] = *itr;
    }

    dictFile.close();
}

DictMap Dictionary::getDictionary()
{
    return dict;
}
