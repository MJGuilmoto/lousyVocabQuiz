/**
 * @file newprofiledialog.cpp
 * @brief A page prompting the user for new profile information.
 * @author Alex Zirbel
 *
 * A subscreen of the NewProfileDialog, in which a new user is prompted for
 * information to fill out a new profile. For example, username and full
 * name of the user are collected. A new profile is set up correctly
 * and the user is logged into the program as their new identity.
 */

#include <QtGui>
#include "newprofiledialog.hpp"

using namespace std;

NewProfileDialog::NewProfileDialog(QWidget *parent) : QDialog(parent)
{
    profileManager = new ProfileManager;

    usernamePrompt = new QLabel(tr("Pick a username for yourself!"));
    usernamePrompt->setObjectName("h1");
    usernamePromptSub = new QLabel(tr("Only use a-z, A-Z, hyphens and underscores:"));
    usernamePromptSub->setObjectName("p");
    usernameLineEdit = new QLineEdit;

    fullNamePrompt = new QLabel(tr("Enter your full name."));
    fullNamePrompt->setObjectName("h1");
    fullNamePromptSub = new QLabel(tr("(Like \"Luke Skywalker\"). Use any symbols you like:"));
    fullNamePromptSub->setObjectName("p");
    fullNameLineEdit = new QLineEdit;

    createButton = new QPushButton(tr("&Create Profile"));
    createButton->setDefault(false);
    //! @todo Enable the button for valid usernames only.
    //createButton->setEnabled(false);

    backButton = new QPushButton(tr("&Back"));
    backButton->setDefault(false);

    connect(createButton, SIGNAL(clicked()),
        this, SLOT(createClicked()));
    connect(backButton, SIGNAL(clicked()),
        this, SLOT(backClicked()));

    QHBoxLayout *buttonBox = new QHBoxLayout;
    buttonBox->addWidget(createButton);
    buttonBox->addWidget(backButton);

    QSpacerItem *spacer = new QSpacerItem(0, 10000, QSizePolicy::Minimum,
                                          QSizePolicy::Maximum);

    QVBoxLayout *mainBox = new QVBoxLayout;
    mainBox->addWidget(usernamePrompt);
    mainBox->addWidget(usernamePromptSub);
    mainBox->addWidget(usernameLineEdit);
    mainBox->addWidget(fullNamePrompt);
    mainBox->addWidget(fullNamePromptSub);
    mainBox->addWidget(fullNameLineEdit);
    mainBox->addLayout(buttonBox);
    mainBox->addItem(spacer);

    setLayout(mainBox);

    // Window settings
    setWindowTitle(tr("Create New Profile | WordQuiz"));
    setMinimumHeight(STD_HEIGHT);
    setMinimumWidth(STD_WIDTH);
}


NewProfileDialog::~NewProfileDialog()
{
}


void NewProfileDialog::createClicked()
{
    if(profileManager == NULL)
        throw new InvalidProfileManagerException;

    string username = (usernameLineEdit->text()).toStdString();
    string fullName = (fullNameLineEdit->text()).toStdString();

    // First, check that the username is valid and let the user know if not.
    // A username should contain only alphanumeric characters and - or _
    if(!profileManager->isValidUsername(username))
    {
        cout << "Invalid username." << endl;
        return;
    }

    if(profileManager->profileExists(username))
    {
        cout << "The specified profile already exists. Please pick a different username." << endl;
        return;
    }

    UserProfile *profile = profileManager->createNewProfile(username, fullName);
    if(!profileManager->saveProfile(profile))
    {
        cout << "Problem saving profile." << endl;
    }

    emit(submitProfile(profile));
}


void NewProfileDialog::backClicked()
{
    emit(back());
}
