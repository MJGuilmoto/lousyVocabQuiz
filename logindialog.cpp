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
#include "logindialog.h"

using namespace std;

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    ProfileManager profileManager;

    loginPrompt = new QLabel(tr("Login as:"));
    usernameLineEdit = new QLineEdit;

    loginButton = new QPushButton(tr("&Login"));
    loginButton->setDefault(false);

    loginPrompt->setBuddy(usernameLineEdit);

    connect(loginButton, SIGNAL(clicked()),
            this, SLOT(loginClicked()));

    QHBoxLayout *loginHBox = new QHBoxLayout;
    loginHBox->addWidget(usernameLineEdit);
    loginHBox->addWidget(loginButton);

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

void LoginDialog::loginClicked()
{
    UserProfile *newprofile = new UserProfile;

    //! @todo Check that the name is valid, load the profile, etc.

    emit(submitProfile(newprofile));
}
