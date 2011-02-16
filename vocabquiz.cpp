/**
 * @file vocabquiz.cpp
 * @brief An interface for different quiz types and definitions for each type.
 * @author Alex Zirbel
 *
 * The main VocabQuiz interface is built to be general: it can load a list
 * of words, and do standard operations on them, but the implementing classes
 * can define different ways of accessing and generating elements.
 *
 * List of subclasses:
 *   - FillInVocabQuiz
 */

#include "vocabquiz.h"

using namespace std;
using namespace boost;

/**
 * Default interface constructor does nothing.
 */
VocabQuiz::VocabQuiz()
{
}

/**
 * Default interface destructor does nothing
 * This is supposed to "pass pointer ownership to another party without
 * exposing the base class
 */
VocabQuiz::~VocabQuiz()
{
}

/**
  * Loads a dictionary object (word-answer pairs) into memory and initializes
  * quizList, an array of all the strings which have not been asked yet.
  * @param dictionary An object containing mappings of words to meanings.
  */
void FillInVocabQuiz::loadDictionary(Dictionary dictionary)
{
    dict = dictionary.getDictionary();
    quizList.clear();

    /* We need to get all the keys from the dictionary, and keep track of which
     * ones haven't been tested yet. */
    for( DictMap::const_iterator itr = dict.begin(); itr != dict.end(); itr++ )
    {
        quizList.push_back(itr->get<lang1>());
    }

    for( unsigned int i = 0; i < quizList.size(); i++ )
    {
        cout << quizList[i] << endl;
    }
}
