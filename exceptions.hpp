/**
 * @file exceptions.hpp
 * @brief A file including definitons for multiple exceptions the program can throw.
 * @author Alex Zirbel
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
 * Handles cases where the username does not match username constraints.
 */
class InvalidUsernameException
{
    virtual const char* what() const throw()
    {
        return "The username specified is invalid.";
    }
};

/**
 * Handles cases where the profile manager was requested, but not initialized
 */
class InvalidProfileManagerException
{
    virtual const char* what() const throw()
    {
        return "ProfileManager called, but was not instantiated correctly.";
    }
};

/**
 * Handles cases where the user profile has not been initialized properly.
 */
class InvalidUserProfileException
{
    virtual const char* what() const throw()
    {
        return "The UserProfile was not marked as valid; bad instantiation.";
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

/**
 * Signals a problem when the home language is set to an invalid language
 * number. The home language must describe language 1 or 2 by being set
 * to the short int 1 or 2.
 */
class InvalidHomeLanguageException
{
    virtual const char* what() const throw()
    {
        return "The home language was set to a value not equal to 1 or 2.";
    }
};


#endif // EXCEPTIONS_H
