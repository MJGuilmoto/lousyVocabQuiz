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

void FillInVocabQuiz::LoadDictionary(Dictionary dictionary)
{
    unordered_map<string, string> dict = dictionary.getDictionary();

    /* Stores a list of the words in order for quizzing. */
    vector<string> quizList;


    /* We need to get all the keys from the dictionary, and then order them
     * randomly. */
    for(unordered_map<string, string>::const_iterator itr (dict.begin()); itr != dict.end(); itr++)
    {
        quizList.push_back(itr->first);
    }

    for(unsigned int i=0; i < quizList.size(); i++)
    {
        cout << quizList[i] << endl;
    }

    randomizeList(&quizList);
}

void FillInVocabQuiz::randomizeList(vector<string> * list)
{

}
