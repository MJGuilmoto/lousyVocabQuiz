/**
 * @file vocabquiz.h Defines an abstract VocabQuiz and subclasses.
 *
 * @author Alex Zirbel
 *
 * An interface which defines common methods all vocal quiz types should
 * have, such as the ability to load a dictionary and get the next word
 * to be quizzed over.
 */

#ifndef VOCABQUIZ_H
#define VOCABQUIZ_H

#include "dictionary.h"

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
    void LoadDictionary(Dictionary dict);

private:
    void randomizeList(std::vector<std::string> * list);

};

#endif // VOCABQUIZ_H
