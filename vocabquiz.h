#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include "dictionary.h"

class VocabQuiz
{
protected:
    /* Stores a list of the words in order for quizzing. */
    std::vector<std::string> quizList;
    DictMap dict;

public:
    VocabQuiz();
    virtual ~VocabQuiz();
    virtual void loadDictionary(Dictionary dict) = 0;

};

class FillInVocabQuiz : VocabQuiz
{

public:
    void loadDictionary(Dictionary dict);

};

#endif // VOCABQUIZ_H
