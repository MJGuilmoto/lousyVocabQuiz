#include "quizlist.h"

QuizList::QuizList()
{
    connListItr = connList.begin();
}

void QuizList::loadDictionary(Dictionary dict)
{
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

//! Unimplemented until connection's last quizzed variable is implemented
void QuizList::sortByLastQuizzed()
{
}

void QuizList::sortByRecentlyQuizzed()
{
}
