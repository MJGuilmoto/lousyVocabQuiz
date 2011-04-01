/**
 * A file including definitons for multiple exceptions the program can throw.
 *
 * All exceptions extend std::exception. Exceptions are used to stop the
 * program in case of failure, but also provide easy error messages and allow
 * higher parts of the program to catch the exception and handle it without
 * crashing outright.
 *
 * @todo Something about the way I throw exceptions may not be supported in
 * QT. This should be fixed. Preferably by QT =P
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

/**
 * Handles all bad file readings. This is the best way to show that a
 * constructor failed, which may be the case when loading dictionaries.
 */
class LoadFileException
{
    virtual const char* what() const throw()
    {
        return "Unable to load dictionary file.";
    }
};

/**
 * Handles the case when a requested profile does not exist.
 */
class NoSuchProfileException
{
    virtual const char* what() const throw()
    {
        return "No such user profile exists.";
    }
};

/**
 * Exception which means the specified languages are invalid.
 * For example, if the languages a word translates from and to are the same,
 * this exception will be thrown because a language must be invalid.
 */
class InvalidLanguageException
{
    virtual const char* what() const throw()
    {
        return "One or more languages specified are invalid.";
    }
};

#endif // EXCEPTIONS_H
