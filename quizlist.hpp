#ifndef QUIZLIST_H
#define QUIZLIST_H

#include "connection.hpp"
#include "languagepair.hpp"

#include <list>
#include <string>
#include <cctype>
#include <set>

#include <iostream>
#include <fstream>
#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "exceptions.hpp"

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
    MasterList();
    MasterList(LanguagePair languages);
    MasterList(MasterList* existing);
    void printContents();
    bool importDictionaryFromFile(std::string filename);

    bool loadFromFile(std::string filename);
    bool saveToFile(std::string filename);
};

#endif // QUIZLIST_H
