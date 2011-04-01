#ifndef QUIZLIST_H
#define QUIZLIST_H

#include "connection.h"
#include <list>
#include <string>
#include <cctype>

#include <iostream>
#include <fstream>
#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/bimap.hpp>

#include <boost/bimap/bimap.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/algorithm/string.hpp>

#include "exceptions.h"

class QuizList
{

public:
    std::string lang1;
    std::string lang2;

    std::string listName;

    //! An ordered list of all the connections loaded into the quiz
    std::list<Connection> connList;
    //! The current position through the quiz
    std::list<Connection>::iterator listItr;

    //! @todo An enumeration of the current order of the list (LEAST_KNOWN, etc)

public:
    QuizList();

    void sortByLang1();
    void sortByLang2();
    void sortByLeastKnown();
    void sortByMostKnown();
    //! Unimplemented until connection's last quizzed variable is implemented
    void sortByLastQuizzed();
    void sortByRecentlyQuizzed();

    bool contains(Connection conn, bool caseSensitive);
};

class MasterList : public QuizList
{

public:
    void printContents();
    bool importDictionaryFromFile(std::string filename);

    bool loadFromFile();
    bool saveToFile();
};

#endif // QUIZLIST_H
