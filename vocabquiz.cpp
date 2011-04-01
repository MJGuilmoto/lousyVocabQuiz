/**
 * @file vocabquiz.cpp
 * @brief Manages the entire backend of each kind of quiz.
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
FillInVocabQuiz::FillInVocabQuiz(QuizList *myList)
{
    direction = STANDARD;
    isCaseSensitive = true;
    list = myList;
    resetQuiz();
}



/**
 * Default interface destructor does nothing
 * This is supposed to "pass pointer ownership to another party without
 * exposing the base class"
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
 * Returns a new prompt for the next question, in the given direction
 * (STANDARD or REVERSE).  Prompts are guaranteed never to repeat throughout
 * the course of a test.
 *
 * Grabs the current connection, and at the end of the method advances the
 * iterator.
 * @return The next randomly selected prompt word, or "" if out of words.
 */
string FillInVocabQuiz::nextPrompt()
{
    //! @todo More input checks
    /*if(*(list->listItr) == NULL)
    {
        return "";
    }*/

    if(list->listItr == (list->connList).end())
    {
        return "";
    }

    //! @todo This is ugly and might not be correct. Change later.
    curConn = &(*(list->listItr));

    if(direction == STANDARD)
        return curConn->getWord1();
    else
        return curConn->getWord2();

    (list->listItr)++;
}


/**
 * Returns a string representing the correct answer for a given prompt.
 * @param prompt The question word (from lang1 if direction is STANDARD)
 * @return A string representing the correct answer in the current direction.
 */
string FillInVocabQuiz::getCorrectAnswer()
{
    //! @todo return all possibilities
    if(direction == STANDARD)
        return curConn->getWord2();
    else
        return curConn->getWord1();
}


/**
 * Checks a prompt and answer and returns whether the answer was correct in the
 * loaded dictionary. Does not change quiz statistics.
 * @param prompt The question word (from lang1 if direction is STANDARD)
 * @param answer The entered answer for the prompt
 * @return True if the answer was correct, false otherwise
 */
bool FillInVocabQuiz::isCorrectAnswer(string answer)
{
    Connection *inputConn;

    if(direction == STANDARD)
        inputConn = new Connection(lang1, lang2, curConn->getWord1(), answer);
    else
        inputConn = new Connection(lang1, lang2, answer, curConn->getWord2());

    if(list->contains(*inputConn, isCaseSensitive))
        return true;

    return false;
}

/**
 * Checks a prompt and answer and returns whether the answer was correct in the
 * loaded dictionary. Also keeps track of statistics - number right and wrong.
 * @param prompt The question word (from lang1 if direction is STANDARD)
 * @param answer The entered answer for the prompt
 * @return True if the answer was correct, false otherwise
 */
bool FillInVocabQuiz::checkAnswer(string answer)
{
    if(isCorrectAnswer(answer))
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
void VocabQuiz::resetQuiz()
{
    list->listItr = (list->connList).begin();

    numRight = 0;
    numWrong = 0;
}

string FillInVocabQuiz::getQuizType()
{
    return "FillInVocabQuiz";
}
