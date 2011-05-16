/**
 * @file languagedialog.cpp
 * @brief A screen to choose which language pair to study
 * @author Alex Zirbel
 *
 * Once the user has signed in with a username, this dialog is presented
 * to allow the user to select languages. The userProfile is already
 * loaded at this point, but the masterList and other language-dependent
 * statistics are not.
 *
 * The languagedialog should present the user with options to type
 * in a new set of languages, but should also offer drop-down options
 * for common languages and a drop-down menu of recently quizzed
 * combinations.
 *
 * This dialog should also check that the order of lang1 and lang2
 * doesn't matter.
 */

#include <QtGui>
#include "languagedialog.hpp"

using namespace std;

/**
 * Build the dialog and add elements.  This constructor should not
 * actually run anything: all functions are taken care of by slots
 * which this dialog implements.
 */
LanguageDialog::LanguageDialog(QWidget *parent) : QDialog(parent)
{
    // Text on the page
    languagePromptText = new QLabel(tr("Which language would you like to study?"));
    fromLangText = new QLabel(tr("From"));
    toLangText = new QLabel(tr("to"));
    recentLangText = new QLabel(tr("Recent"));

    // Language input
    //! @todo These should be converted to drop-down menus.
    lang1Select = new QLineEdit;
    lang2Select = new QLineEdit;
    recentList = new QLineEdit;

    // The Go button brings the user to the homepage, with both user profile and
    // main language defined.
    goButton = new QPushButton(tr("Go!"));
    goButton->setDefault(false);

    connect(goButton, SIGNAL(clicked()), this, SLOT(goClicked()));

    // Layouts
    QHBoxLayout *selectNewBox = new QHBoxLayout;
    selectNewBox->addWidget(fromLangText);
    selectNewBox->addWidget(lang1Select);
    selectNewBox->addWidget(toLangText);
    selectNewBox->addWidget(lang2Select);

    QHBoxLayout *recentBox = new QHBoxLayout;
    recentBox->addWidget(recentLangText);
    recentBox->addWidget(recentList);

    QVBoxLayout *mainBox = new QVBoxLayout;
    mainBox->addWidget(languagePromptText);
    mainBox->addLayout(selectNewBox);
    mainBox->addLayout(recentBox);
    mainBox->addWidget(goButton);

    setLayout(mainBox);

    setWindowTitle(tr("Select Language"));
}

/**
 * Frees memory being used by the language dialog, and ideally
 * saves any options the user has selected for use later.
 * @todo Implement these features.
 */
LanguageDialog::~LanguageDialog()
{
    //! @todo Remove
    cout << "Language dialog destroyed." << endl;
}

/**
 * Signal that the languages are chosen and the user is ready
 * to go to the homepage and begin quizzing.
 *
 * Sumbits the languages as the type LanguagePair, which simply makes
 *   sure the ordering is right and (ideally) checks for problems.
 *
 * @todo Check that the languages are valid before we move on and send
 *  the signal.
 */
void LanguageDialog::goClicked()
{
    LanguagePair *languages = new LanguagePair(
            (lang1Select->text()).toStdString(),
            (lang2Select->text()).toStdString(), 1);
    emit submitLanguagePair(languages);
}
