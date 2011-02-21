#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include "dictionary.h"
#include <set>

class VocabQuiz
{

protected:
    /** A list of which indices of words are still unused as prompts */
    std::set<int> quizList; //!< Better as boost::unordered_set?
    DictMap dict;
    int direction;          //!< Stores direction of the quiz

public:
    VocabQuiz();
    VocabQuiz(int myDirection);
    virtual ~VocabQuiz();
    virtual void loadDictionary(Dictionary dict) = 0;
    void setDirection(int newDirection);
};

class FillInVocabQuiz : VocabQuiz
{
//!< @todo Variables like "caseSensitive" and other answer-checking options

public:
    void loadDictionary(Dictionary dict);
    std::string getNextRandomElement();
    bool isCorrectAnswer(std::string prompt, std::string answer);
    void resetQuiz();
    using VocabQuiz::setDirection;

};

#endif // VOCABQUIZ_H
