/**
 * @file userprofile.hpp
 * @brief Header definitions for the User Profile class.
 * @author Alex Zirbel
 */

#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <iostream>
#include <fstream>

#include "connection.hpp"
#include "quizlist.hpp"
#include "languagepair.hpp"

#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string.hpp>

//! @todo Might want to change this later, don't define my own functions
//! @todo Or just make this implementation faster.
//! Note that I don't check or care about homeLang here.
struct ihash
    : std::unary_function<LanguagePair, std::size_t>
{
    std::size_t operator()(LanguagePair const& l) const
    {
        std::stringstream concat;
        concat << l.lang1 << "\t" << l.lang2;
        std::size_t seed = 0;
        boost::hash_combine( seed, concat.str() );
        return seed;
    }
};

//! Also doesn't care about homeLang
struct iequal_to
    : std::binary_function<LanguagePair, LanguagePair, bool>
{
    bool operator()(LanguagePair const& x, LanguagePair const& y) const
    {
        return ( boost::iequals(x.lang1, y.lang1) &&
                 boost::iequals(x.lang2, y.lang2));
    }
};

class UserProfile
{
std::string username;
std::string fullName;

bool valid;

boost::unordered_map<LanguagePair, MasterList, ihash, iequal_to> masterListMap;
boost::unordered_map<LanguagePair, MasterList, ihash, iequal_to>::iterator mItr;

public:
    UserProfile();
    UserProfile(std::string newUsername);
    UserProfile(std::string newUsername, std::string newFullName);
    MasterList* getMasterListForLanguages(LanguagePair languages);
    bool saveProfile(std::string filename);
    bool loadProfile(std::string filename);

    std::string getUsername();
    std::string getFullName();
    bool isValid();
};

#endif // USERPROFILE_H
