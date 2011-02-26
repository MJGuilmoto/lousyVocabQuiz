#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include "dictionary.h"
#include <set>
#include <boost/algorithm/string.hpp>

// Settings for this quiz
#define STANDARD 1
#define REVERSE 0

class VocabQuiz
{

protected:
    /** A list of which indices of words are still unused as prompts */
    std::set<int> quizList; //!< Better as boost::unordered_set?
    DictMap dict;
    int direction;          //!< Stores direction of the quiz
    int isCaseSensitive;    //!< Whether to check for capitals or not
    int numRight, numWrong; //!< Store how the user is doing

public:
    VocabQuiz();
    VocabQuiz(int myDirection);
    virtual ~VocabQuiz();
    virtual void loadDictionary(Dictionary dict) = 0;
    void setDirection(int newDirection);
    int getDirection();
    void setCaseSensitive(bool newCaseSensitive);
    bool getCaseSensitive();
    int getNumRight();
    int getNumWrong();
};

class FillInVocabQuiz : VocabQuiz
{
//!< @todo Variables like "caseSensitive" and other answer-checking options

public:
    void loadDictionary(Dictionary dict);
    std::string getNextRandomElement();
    bool checkAnswer(std::string prompt, std::string answer);
    std::string getCorrectAnswer(std::string prompt);
    void resetQuiz();
    using VocabQuiz::setDirection;
    using VocabQuiz::getDirection;
    using VocabQuiz::setCaseSensitive;
    using VocabQuiz::getCaseSensitive;
    using VocabQuiz::getNumRight;
    using VocabQuiz::getNumWrong;

private:
    bool isCorrectAnswer(std::string prompt, std::string answer);

};

#endif // VOCABQUIZ_H
