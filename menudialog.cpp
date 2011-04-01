/**
 * @file menudialog.cpp
 * @brief The application homepage after a user logs in
 * @author Alex Zirbel
 */

#include <QtGui>

#include "menudialog.h"

using namespace std;

MenuDialog::MenuDialog(QWidget *parent) : QDialog(parent)
{
    welcomeText = new QLabel
                  (tr("<font size=4><b>Welcome to WordQuiz!</b></font>"))   ;
    selectedQuizText = new QLabel(tr(""));

    startQuizButton = new QPushButton(tr("&Start Quiz"));
    startQuizButton->setDefault(false);

    changeUserButton = new QPushButton(tr("&Change User"));
    changeUserButton->setDefault(false);

    connect(startQuizButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    connect(changeUserButton, SIGNAL(clicked()), this, SLOT(changeUserClicked()));

    QHBoxLayout *buttonBox = new QHBoxLayout;
    buttonBox->addWidget(changeUserButton);
    buttonBox->addWidget(startQuizButton);

    QVBoxLayout *mainBox = new QVBoxLayout;
    mainBox->addWidget(welcomeText);
    mainBox->addWidget(selectedQuizText);
    mainBox->addLayout(buttonBox);

    setLayout(mainBox);

    // Window settings
    setWindowTitle(tr("Homepage"));
}

MenuDialog::~MenuDialog()
{
    cout << "Menu dialog destroyed." << endl;
}

void MenuDialog::setUserProfile(UserProfile *newProfile)
{
    currentUser = newProfile;
}

void MenuDialog::startButtonClicked()
{
    emit startQuiz();
}

void MenuDialog::changeUserClicked()
{
    emit changeUser();
}
