/**
 * @file logindialog.cpp
 * @brief The login page shown when the program is started.
 * @author Alex Zirbel
 *
 * The GUI element that sets up and loads a user profile.  Since statistics
 * are saved for every user, different users can log on with unique usernames
 * to keep their data separate.
 */

#include <QtGui>
#include "logindialog.hpp"

using namespace std;

ProfileManager *profileManager;

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    profileManager = new ProfileManager;

    loginPrompt = new QLabel(tr("Login as:"));
    usernameLineEdit = new QLineEdit;

    loginButton = new QPushButton(tr("&Login"));
    loginButton->setDefault(false);

    newProfileButton = new QPushButton(tr("&Create new profile"));
    newProfileButton->setDefault(false);

    loginPrompt->setBuddy(usernameLineEdit);

    connect(loginButton, SIGNAL(clicked()),
            this, SLOT(loginClicked()));
    connect(newProfileButton, SIGNAL(clicked()),
            this, SLOT(newProfileClicked()));
    connect(usernameLineEdit, SIGNAL(returnPressed()),
            this, SLOT(loginClicked()));

    QHBoxLayout *loginHBox = new QHBoxLayout;
    loginHBox->addWidget(usernameLineEdit);
    loginHBox->addWidget(loginButton);
    loginHBox->addWidget(newProfileButton);

    QVBoxLayout *mainBox = new QVBoxLayout;
    mainBox->addWidget(loginPrompt);
    mainBox->addLayout(loginHBox);

    setLayout(mainBox);

    // Window settings
    setWindowTitle(tr("Login Page | WordQuiz"));
    setTabOrder(usernameLineEdit, loginButton);
    setFixedHeight(sizeHint().height());
    setMinimumWidth(500);
}


LoginDialog::~LoginDialog()
{
    cout << "Login Dialog object destroyed." << endl;
}


/**
 * Handles a sumbitted username login.
 *
 * Checks that the submitted username is valid. To make a new profile,
 * a different button must be clicked.
 */
void LoginDialog::loginClicked()
{
    if(profileManager == NULL)
        throw new InvalidProfileManagerException;

    string username = (usernameLineEdit->text()).toStdString();

    // First, check that the username is valid and let the user know if not.
    // A username should contain alphanumeric characters and - or _
    if(!profileManager->isValidUsername(username))
    {
        cout << "Invalid username." << endl;
        return;
    }

    if(!profileManager->profileExists(username))
    {
        cout << "The specified profile does not exist." << endl;
        return;
    }

    UserProfile *profile = profileManager->loadProfile(username);

    emit(submitProfile(profile));
}


/**
 * Handles a request to create a new user profile.
 *
 * The specified profile must not exist already.
 */
void LoginDialog::newProfileClicked()
{
    if(profileManager == NULL)
        throw new InvalidProfileManagerException;

    string username = (usernameLineEdit->text()).toStdString();

    if(profileManager->profileExists(username))
    {
        cout << "The profile already exists!" << endl;
        return;
    }

    UserProfile *profile = profileManager->createNewProfile(username);

    emit(submitProfile(profile));
}
