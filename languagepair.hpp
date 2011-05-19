/**
 * @file languagepair.hpp
 * @brief Header definitions for the language pair class
 * @author Alex Zirbel
 */

#ifndef LANGUAGEPAIR_H
#define LANGUAGEPAIR_H

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "exceptions.hpp"

class LanguagePair
{
//! It is possible to create an invalid language pair with bad information.
//! Keeps track of whether a language pair has been verified or not.
bool valid;

public:

    //! Describes which language is the user's home language - either 1 or 2.
    short homeLang;

    std::string lang1;
    std::string lang2;

    LanguagePair();
    LanguagePair(LanguagePair* existing);
    LanguagePair(std::string myLang1, std::string myLang2, int whichIsHome);

    bool loadFromLine(std::string line, int *status);
    std::string exportToLine();

    short whichLangIsHome();
    void setHomeLang(short newHomeLang);
    std::string getHomeLang();
    std::string getForeignLang();

    void printContents();
    bool isValid();

};

#endif // LANGUAGEPAIR_H
