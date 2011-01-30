#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include "dictionary.h"

/**
 * An interface which defines common methods all vocal quiz types should
 * have, such as the ability to load a dictionary and get the next word
 * to be quizzed over.
 */
class VocabQuiz
{

public:
    VocabQuiz();
    virtual ~VocabQuiz();
    virtual void LoadDictionary(Dictionary dict) = 0;

};

class FillInVocabQuiz : VocabQuiz
{

public:
    virtual void LoadDictionary(Dictionary dict);


};

#endif // VOCABQUIZ_H
