#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include "exceptions.h"

#define MAX_WORDLEN 100

typedef unordered_map<string, string> DictMap;
typedef DictMap::const_iterator DictItr;

class Dictionary
{
/* Keeps track of the language this dictionary contains words from and to. */
string language1, language2;

/* The name of this list (example: "Basic German") */
string listName;

/* The actual list of words */
DictMap dict;

public:
    Dictionary();
    void printContents();
    void loadFromFile(string filename);
    DictMap getDictionary();
};

#endif // DICTIONARY_H
