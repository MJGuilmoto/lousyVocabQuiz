#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/bimap.hpp>

#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>

#include "exceptions.h"

#define MAX_WORDLEN 100

struct language1 {};
struct language2 {};

//typedef boost::unordered_map<std::string, std::string> DictMap;
//typedef DictMap::const_iterator DictItr;

/* Uses a bimap to map each language to the other (quizzing both ways is fine)
 * at the cost of forcing each word to be unique in its language. */
typedef boost::bimap
        <
            boost::bimaps::unordered_set_of< boost::bimaps::tagged< std::string, language1 > >,
            boost::bimaps::unordered_set_of< boost::bimaps::tagged< std::string, language2 > >,
            boost::bimaps::list_of_relation
        > DictMap;

typedef DictMap::value_type translation;

class Dictionary
{
/* Keeps track of the language this dictionary contains words from and to. */
//std::string language1, language2;
    //TODO: replace with struct language1,2 stuff

/* The name of this list (example: "Basic German") */
std::string listName;

/* The actual list of words */

//boost::unordered_map<std::string, std::string> dict;
DictMap dict;

public:
    Dictionary();
    void printContentsStandard();
    void loadFromFile(std::string filename);
    DictMap getDictionary();

};

#endif // DICTIONARY_H
