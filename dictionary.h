#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include "exceptions.h"

#define MAX_WORDLEN 100

//typedef boost::unordered_map<std::string, std::string> DictMap;
//typedef DictMap::const_iterator DictItr;

class Dictionary
{
/* Keeps track of the language this dictionary contains words from and to. */
std::string language1, language2;

/* The name of this list (example: "Basic German") */
std::string listName;

/* The actual list of words */
boost::unordered_map<std::string, std::string> dict;
//DictMap dict;

public:
    Dictionary();
    void printContents();
    void loadFromFile(std::string filename);
    boost::unordered_map<std::string, std::string> getDictionary();

};

#endif // DICTIONARY_H
