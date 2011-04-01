#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include "quizlist.h"

#include <set>
#include <boost/algorithm/string.hpp>

// Settings for this quiz
#define STANDARD 1
#define REVERSE 0

//! An abstract base class
class VocabQuiz
{

protected:
    std::string lang1;
    std::string lang2;
    QuizList *list;
    Connection *curConn;
    int direction;          //!< Stores direction of the quiz
    int isCaseSensitive;    //!< Whether to check for capitals or not
    int numRight, numWrong; //!< Store how the user is doing

public:
    VocabQuiz() { }
    ~VocabQuiz();

    void setDirection(int newDirection);
    int getDirection();
    void resetQuiz();
    void setCaseSensitive(bool newCaseSensitive);
    bool getCaseSensitive();
    int getNumRight();
    int getNumWrong();

    virtual std::string getQuizType() =0;
};

class FillInVocabQuiz : VocabQuiz
{
//!< @todo Variables like "caseSensitive" and other answer-checking options

public:
    FillInVocabQuiz(QuizList *myList);

    std::string nextPrompt();
    bool isCorrectAnswer(std::string answer);
    bool checkAnswer(std::string answer);
    std::string getCorrectAnswer();

    using VocabQuiz::setDirection;
    using VocabQuiz::getDirection;
    using VocabQuiz::setCaseSensitive;
    using VocabQuiz::getCaseSensitive;
    using VocabQuiz::getNumRight;
    using VocabQuiz::getNumWrong;
    using VocabQuiz::resetQuiz;

    std::string getQuizType();
};

#endif // VOCABQUIZ_H
