#ifndef DICTIONARY_H
#define DICTIONARY_H

///////////////////////////////////////////////////////////
// STANDARD AND BOOST-SPECIFIC INCLUDES
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/bimap.hpp>

#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>

///////////////////////////////////////////////////////////
// RELATIVE INCLUDES
///////////////////////////////////////////////////////////

#include "exceptions.h"

///////////////////////////////////////////////////////////
// DEFINTIONS
///////////////////////////////////////////////////////////

#define MAX_WORDLEN 100

/* Just used as identifiers for which direction we access the elements. */
struct lang1 {};
struct lang2 {};

/* Uses a bimap to map each language to the other (quizzing both ways is fine)
 * at the cost of forcing each word to be unique in its language. */
typedef boost::bimap
        <
            boost::bimaps::unordered_set_of
                < boost::bimaps::tagged< std::string, lang1 > >,

            boost::bimaps::unordered_set_of
                < boost::bimaps::tagged< std::string, lang2 > >,

            boost::bimaps::list_of_relation

        > DictMap;

typedef DictMap::value_type translation;

///////////////////////////////////////////////////////////
// CLASS DICTIONARY
///////////////////////////////////////////////////////////

class Dictionary
{
/* Keeps track of the language this dictionary contains words from and to. */
//! @todo replace with struct language1,2 stuff
//std::string language1, language2;

/* The name of this list (example: "Basic German") */
std::string listName;

/* The actual list of words */
DictMap dict;

public:
    Dictionary();
    void printContents();
    void loadFromFile(std::string filename);
    DictMap getDictionary();

};

#endif // DICTIONARY_H
