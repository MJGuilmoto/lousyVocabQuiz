/**
 * A file including definitons for multiple exceptions the program can throw.
 *
 * All exceptions extend std::exception. Exceptions are used to stop the
 * program in case of failure, but also provide easy error messages and allow
 * higher parts of the program to catch the exception and handle it without
 * crashing outright.
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

#endif // EXCEPTIONS_H
