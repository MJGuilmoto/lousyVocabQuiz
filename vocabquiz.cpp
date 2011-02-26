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
 * Default interface constructor sets direction to standard
 */
VocabQuiz::VocabQuiz()
{
    direction = STANDARD;
    isCaseSensitive = true;
}


/**
 * Possible to construct with a direction set
 */
VocabQuiz::VocabQuiz(int myDirection)
{
    direction = myDirection;
    isCaseSensitive = true;
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
 * Sets the direction the vocab quiz asks and evaulates answers in. Direction
 * can either be STANDARD or REVERSE. If STANDARD, the quiz will ask words from
 * lang1 and expect answers from lang2; if REVERSE, the opposite is true.
 * @param newDirection Direction of quiz, STANDARD or REVERSE
 */
void VocabQuiz::setDirection(int newDirection)
{
    direction = newDirection;
}


/**
 * Returns the current direction of the quiz, STANDARD or REVERSE.
 * @return The current direction of the quiz.
 */
int VocabQuiz::getDirection()
{
    return direction;
}


/**
 * Sets the case sensitivity preference for the quiz.  If the quiz is case
 * sensitive (true), then typing the correct capitalization of words matters
 * when the quiz evaluates responses.  Otherwise (false), it doesn't matter.
 * @param newCaseSensitive True if the quiz should be case sensitive.
 */
void VocabQuiz::setCaseSensitive(bool newCaseSensitive)
{
    isCaseSensitive = newCaseSensitive;
}


/**
 * Returns the current case sensitivity of the given quiz.
 * @return True if the quiz is case sensitive, false otherwise.
 */
bool VocabQuiz::getCaseSensitive()
{
    return isCaseSensitive;
}


/**
 * Accessor for number of correct answers so far.
 * @return Number of questions the user has answered correctly.
 */
int VocabQuiz::getNumRight()
{
    return numRight;
}


/**
 * Accessor for number of incorrect answers so far.
 * @return Number of questions the user has answered incorrectly.
 */
int VocabQuiz::getNumWrong()
{
    return numWrong;
}


/**
 * Loads a dictionary object (word-answer pairs) into memory and initializes
 * quizList, an array of all the strings which have not been asked yet.
 * @param dictionary An object containing mappings of words to meanings.
 */
void FillInVocabQuiz::loadDictionary(Dictionary dictionary)
{
    dict = dictionary.getDictionary();
    resetQuiz();
}


/**
 * Returns a new prompt for the next question, in the given direction (STANDARD or
 * REVERSE).  Prompts are guaranteed never to repeat throughout the course of a test.
 * @return The next randomly selected prompt word, or "" if out of words.
 */
string FillInVocabQuiz::getNextRandomElement()
{
    if(quizList.size() == 0)
        return "";

    srand( time(NULL) );
    int nextElementIndex = rand() % quizList.size();
    set<int>::iterator listItr = quizList.begin();
    for(int i=0; i<nextElementIndex; i++) listItr++;
    int nextElementNum = *listItr;
    quizList.erase( quizList.find(nextElementNum) );

    string toReturn;

    DictMap::const_iterator dictItr = dict.begin();
    for(int i = 0; i < nextElementNum; i++)
    {
        dictItr++;
    }

    if(direction == STANDARD)
    {
       toReturn = dictItr->get<lang1>();
    }
    else
    {
        toReturn = dictItr->get<lang2>();
    }
    return toReturn;
}


/**
 * Returns a string representing the correct answer for a given prompt.
 * @param prompt The question word (from lang1 if direction is STANDARD)
 * @return A string representing the correct answer in the current direction.
 */
string FillInVocabQuiz::getCorrectAnswer(string prompt)
{
    string correctAnswer;

    if(direction == STANDARD)
    {
        correctAnswer = dict.left.at(prompt);
    }
    else
    {
        correctAnswer = dict.right.at(prompt);
    }

    return correctAnswer;
}


/**
 * Checks a prompt and answer and returns whether the answer was correct in the
 * loaded dictionary. Does not change quiz statistics.
 * @param prompt The question word (from lang1 if direction is STANDARD)
 * @param answer The entered answer for the prompt
 * @return True if the answer was correct, false otherwise
 */
bool FillInVocabQuiz::isCorrectAnswer(string prompt, string answer)
{
    string correctAnswer = getCorrectAnswer(prompt);

    if(isCaseSensitive)
    {
        if(boost::equals(answer, correctAnswer))
            return true;
        else
            return false;
    }
    else
    {
        if(boost::iequals(answer, correctAnswer))
            return true;
        else
            return false;
    }
}


/**
 * Checks a prompt and answer and returns whether the answer was correct in the
 * loaded dictionary. Also keeps track of statistics - number right and wrong.
 * @param prompt The question word (from lang1 if direction is STANDARD)
 * @param answer The entered answer for the prompt
 * @return True if the answer was correct, false otherwise
 */
bool FillInVocabQuiz::checkAnswer(string prompt, string answer)
{
    if(isCorrectAnswer(prompt, answer))
    {
        numRight++;
        return true;
    }
    else
    {
        numWrong++;
        return false;
    }
}


/**
 * Restarts the quiz, clearing the saved data of words quizzed so far.
 */
void FillInVocabQuiz::resetQuiz()
{
    quizList.clear();

    numRight = 0;
    numWrong = 0;

    for( unsigned int i = 0; i < dict.size(); i++ )
    {
        quizList.insert(i);
    }
}
