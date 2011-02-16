#include "vocabquiz.h"

using namespace std;
using namespace boost;

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
void FillInVocabQuiz::LoadDictionary(Dictionary dictionary)
{
    dict = dictionary.getDictionary();
    quizList.clear();

    /* We need to get all the keys from the dictionary, and then order them
     * randomly. */
    /*for(unordered_map<string, string>::const_iterator itr (dict.begin());
        itr != dict.end(); itr++)
    {
        quizList.push_back(itr->first);
    }*/

    for(unsigned int i=0; i < quizList.size(); i++)
    {
        cout << quizList[i] << endl;
    }
}
