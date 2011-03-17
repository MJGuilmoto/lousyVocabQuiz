#ifndef QUIZLIST_H
#define QUIZLIST_H

#include "dictionary.h"
#include <list>
#include <string>
#include <cctype>

class QuizList
{
std::string lang1;
std::string lang2;

//! An ordered list of all the words loaded into the quiz
std::list<std::string> connList;
//! The current position through the quiz
std::list<std::string>::iterator connListItr;

public:
    QuizList();

    void loadDictionary(Dictionary dict);

    void sortByLang1();
    void sortByLang2();
    void sortByLeastKnown();
    void sortByMostKnown();
    //! Unimplemented until connection's last quizzed variable is implemented
    void sortByLastQuizzed();
    void sortByRecentlyQuizzed();
};

#endif // QUIZLIST_H
