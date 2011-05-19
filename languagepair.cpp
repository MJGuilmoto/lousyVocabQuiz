/**
 * @file languagepair.cpp
 * @brief Stores two languages in a set, sorted alphabetically
 * @author Alex Zirbel
 *
 * Stores a pair of languages to help categorize quiz lists - each list
 * has a pair of languages that define it.
 *
 * @todo Error-checking functions to make sure languages are legitimate, and
 *  to compare languagePairs?
 * @todo Check for invalid "" languages, equal languages, etc. Make this a
 *  public static function and make all the other classes which do this check
 *  use the function in this class.
 */

#include "languagepair.hpp"

using namespace std;
using namespace boost;
using boost::lexical_cast;
using boost::bad_lexical_cast;  // Used to catch bad lexical casts

/**
 * This default constructor should not be called and will throw an error, but
 * was needed for clean compiling for some reason.
 *
 * Language pairs should always be initialized with langauge parameters.
 * @todo Somehow remove the option to call this initializer.
 */
LanguagePair::LanguagePair()
{
    lang1 = "";
    lang2 = "";
    valid = false;
}


/**
 * Constructs a LanguagePair as a copy of an existing pair.
 * Seems to be needed for std::make_pair.
 */
LanguagePair::LanguagePair(LanguagePair* existing)
{
    lang1 = existing->lang1;
    lang2 = existing->lang2;
    homeLang = existing->homeLang;
    valid = existing->isValid();
}


/**
 * Initialize a pair of languages. Languages must be unique and can be
 * specified in any order, but whichIsHome should be 1 if the first
 * language specified is the home language, and whichIsHome should be 2
 * if the second language is home.
 *
 * This constructor sorts the languages alphabetically
 * and creates the new object.
 *
 * @param myLang1 One language in the pair
 * @param myLang2 The other language in the pair
 * @param whichIsHome 1 if myLang1 is the home language, 2 if myLang2 is
 */
LanguagePair::LanguagePair(string myLang1, string myLang2, int whichIsHome)
{
    if(boost::iequals(myLang1, myLang2))
        throw new InvalidLanguageException;

    if(boost::algorithm::lexicographical_compare(myLang1, myLang2,
        boost::is_iless()))
    {
        homeLang = whichIsHome;
        lang1 = myLang1;
        lang2 = myLang2;
    }
    else
    {
        if(whichIsHome == 1) homeLang = 2;
        else homeLang = 1;

        lang1 = myLang2;
        lang2 = myLang1;
    }
    valid = true;
}


/**
 * The only function that should be called to create a language pair from
 * a string.
 * @param line A single line to be loaded from, assumed to be saved from
 *  languagePair's exportToLine function.
 * @param status A return code: 0 if everything as expected, and 1 if
 *  the order of languages was reversed (ie they needed sorting).
 * @return True if the load was successful, false otherwise
 */
bool LanguagePair::loadFromLine(string line, int *status)
{
    string myLang1, myLang2;

    *status = 0;

    // Tokenize based on tab characters
    char_separator <char> sep("\t");
    tokenizer <char_separator <char> > tokens(line, sep);
    tokenizer<char_separator <char> >::iterator itr = tokens.begin();

    // Make sure there are at least two tokens. A third may be used to
    // specify the home language.
    myLang1 = *itr;
    itr++;
    if(itr == tokens.end())
        return false;
    myLang2 = *itr;

    // Check to see if the languages are equal (this is not allowed)
    if(boost::iequals(myLang1, myLang2))
        return false;

    itr++;

    if(itr != tokens.end())
    {
        // Get the home language, or return a problem load
        try
        {
            homeLang = lexical_cast<unsigned int>(*itr);
        }
        catch(bad_lexical_cast &)
        {
            return false;
        }
    }
    else
    {
        homeLang = 1;
    }

    // Ensure languages are sorted alphabetically when stored
    if(boost::algorithm::lexicographical_compare
        (myLang1, myLang2, boost::is_iless()))
    {
        // Languages were specified in order
        lang1 = myLang1;
        lang2 = myLang2;
    }
    else
    {
        // Swap languages
        lang1 = myLang2;
        lang2 = myLang1;
        homeLang = (homeLang == 1) ? 2 : 1;
        *status = 1;
    }

    valid = true;
    return true;
}


/**
 * Exports the information from a language pair into a one-line string
 * to be saved to a file.
 */
string LanguagePair::exportToLine()
{
    if(!valid)
        throw new InvalidLanguageException;

    stringstream line;

    line << lang1 << "\t" << lang2 << "\t" << homeLang << "\n";

    return line.str();
}



//! @todo restore these.
/**
 * Returns the first language, which is private and immutable once declared.
 * @return The first language alphabetically
 */
/*string LanguagePair::getLang1()
{
    if(!valid)
        throw new InvalidLanguageException;

    return lang1;
}
*/

/**
 * Returns the second language, which is private and immutable once declared.
 * @return The second language alphabetically
 */
/*string LanguagePair::getLang2()
{
    if(!valid)
        throw new InvalidLanguageException;

    return lang2;
}*/


/**
 * Returns an int specifying which language is the user's home language.
 * @return 1 if lang1 is home, 2 if lang2 is home.
 */
short LanguagePair::whichLangIsHome()
{
    if(!valid)
        throw new InvalidLanguageException;

    return homeLang;
}


/**
 * Checks that the newHomeLang is valid and then sets this connection so that
 * the user's home language is lang1 if newHomeLang == 1 and lang2 if
 * newHomeLang == 2.
 * @param newHomeLang 1 to make lang1 the home language, 2 for lang2.
 */
void LanguagePair::setHomeLang(short newHomeLang)
{
    if(!valid)
        throw new InvalidLanguageException;

    if(newHomeLang != 1 && newHomeLang != 2)
    {
        throw new InvalidHomeLanguageException;
    }

    homeLang = newHomeLang;
}


/**
 * Based on the homeLang variable, returns the string representing the
 * language the user has set as their home language.
 * @return The name of the user's home language
 */
std::string LanguagePair::getHomeLang()
{
    if(!valid)
        throw new InvalidLanguageException;

    if(homeLang == 1)
        return lang1;
    else
        return lang2;
}

/**
 * Based on the homeLang variable, returns the string representing the
 * language the user has set as their foreign language.
 * @return The name of the user's foreign language
 */
std::string LanguagePair::getForeignLang()
{
    if(!valid)
        throw new InvalidLanguageException;

    if(homeLang == 1)
        return lang2;
    else
        return lang1;
}


/**
 * A debugging tool to show the language pair's data.
 */
void LanguagePair::printContents()
{
    cout << "LanguagePair: <" << lang1 << "," << lang2 << ">, home is: "
            << homeLang << endl;

}


bool LanguagePair::isValid()
{
    return valid;
}
