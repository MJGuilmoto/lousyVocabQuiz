#include <QtGui>

#include "quizdialog.h"

using namespace std;

/**
 * Sets up all elements of the QuizDialog widget, and initializes the
 * FillInVocabQuiz which runs in the background.
 */
QuizDialog::QuizDialog(FillInVocabQuiz *quiz, QWidget *parent) : QDialog(parent)
{
    // List of elements
    title = new QLabel
            (tr("<font size=4><b>Quizzing from English to German:</b></font>"));
    prompt = new QLabel(tr("<word>"));
    info = new QLabel(tr("<info>"));
    answer = new QLineEdit;
    prompt->setBuddy(answer);

    caseCheckBox = new QCheckBox(tr("Case &Sensitive"));
    reverseCheckBox = new QCheckBox(tr("Reverse &Direction"));

    checkButton = new QPushButton(tr("&Check"));
    checkButton->setDefault(true);

    resetButton = new QPushButton(tr("&Reset Quiz"));
    resetButton->setDefault(true);

    closeButton = new QPushButton(tr("Close"));

    // Actions which happen when buttons are clicked
    connect(checkButton, SIGNAL(clicked()),
            this, SLOT(checkAnswer()));
    connect(resetButton, SIGNAL(clicked()),
            this, SLOT(resetClicked()));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

    // The layout is broken up into three horizontal sections, each of which is
    // split as necessary into vertical secitons.
    QHBoxLayout *answerBox = new QHBoxLayout;
    answerBox->addWidget(answer);
    answerBox->addWidget(checkButton);

    QVBoxLayout *quizBox = new QVBoxLayout;
    quizBox->addWidget(prompt);
    quizBox->addLayout(answerBox);
    quizBox->addWidget(info);

    QVBoxLayout *optionsBox = new QVBoxLayout;
    optionsBox->addWidget(caseCheckBox);
    optionsBox->addWidget(reverseCheckBox);

    QVBoxLayout *resetsBox = new QVBoxLayout;
    resetsBox->addWidget(resetButton);
    resetsBox->addWidget(closeButton);

    QHBoxLayout *bottomBox = new QHBoxLayout;
    bottomBox->addLayout(optionsBox);
    bottomBox->addLayout(resetsBox);

    QFrame *hLine = new QFrame;
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    QFrame *hLine2 = new QFrame;
    hLine2->setFrameShape(QFrame::HLine);
    hLine2->setFrameShadow(QFrame::Sunken);

    QVBoxLayout *mainBox = new QVBoxLayout;
    mainBox->addWidget(title);
    mainBox->addWidget(hLine);
    mainBox->addLayout(quizBox);
    mainBox->addWidget(hLine2);
    mainBox->addLayout(bottomBox);
    setLayout(mainBox);

    // Window settings
    setWindowTitle(tr("WordQuiz"));
    setTabOrder(answer, checkButton);
    setFixedHeight(sizeHint().height());
    setMinimumWidth(500);

    // Initialize the quiz to be run in this widget
    myQuiz = quiz;
    getNextPrompt();
}

/**
 * Checks the answer currently typed into the lineEdit answer box.
 * If the quiz as currently set up accepts this as an answer (or if not),
 * sets the info box accordingly.
 */
void QuizDialog::checkAnswer()
{
    QString text = answer->text();

    if(strcmp(curPrompt.c_str(), "") == 0)
    {
        string sRight = boost::lexical_cast<string>(myQuiz->getNumRight());
        string sWrong = boost::lexical_cast<string>
                        (myQuiz->getNumWrong() + myQuiz->getNumRight());
        string endString = "End of quiz. You answered " + sRight + "/" + sWrong
                        + " correctly.";
        info->setText(QString(endString.c_str()));
        return;
    }

    // Check if the response was right: set case sensitivity
    if(caseCheckBox->isChecked())
        myQuiz->setCaseSensitive(true);
    else
        myQuiz->setCaseSensitive(false);

    if(myQuiz->checkAnswer(curPrompt, text.toStdString()))
        info->setText("Correct!");
    else
    {
        string response = "Wrong - \"" + curPrompt + "\" is: \"" +
                          myQuiz->getCorrectAnswer(curPrompt) + "\".";
        info->setText(QString(response.c_str()));
    }

    getNextPrompt();
}

/**
 * Clears the list of words quizzed so far, starting the quiz over.
 */
void QuizDialog::resetClicked()
{
    myQuiz->resetQuiz();
    info->setText("");
    getNextPrompt();
}

/**
 * Sets up the quiz for the next prompt and sets it as the current prompt
 * At this point, changes direction of the quiz in case it was changed during
 * the last cycle. Finally, sets curPrompt to the next prompt provided by the
 * quiz.
 */
void QuizDialog::getNextPrompt()
{
    // At this point, reverse direction if it needed to be reversed.
    if(reverseCheckBox->isChecked())
    {
        myQuiz->setDirection(REVERSE);
        title->setText(tr(
                "<font size=4><b>Quizzing from German to English:</b></font>"));
    }
    else
    {
        myQuiz->setDirection(STANDARD);
        title->setText(tr(
                "<font size=4><b>Quizzing from English to German:</b></font>"));
    }

    curPrompt = myQuiz->getNextRandomElement();
    prompt->setText(QString(curPrompt.c_str()));
}