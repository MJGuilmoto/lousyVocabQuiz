#ifndef QUIZDIALOG_H
#define QUIZDIALOG_H

#include <QDialog>
#include "vocabquiz.h"
#include <boost/lexical_cast.hpp>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class QuizDialog : public QDialog
{
    Q_OBJECT

// The backend quiz object being used in this gui quiz interace.

FillInVocabQuiz *quiz;
std::string curPrompt;
int numCorrect, numWrong;

public:
    QuizDialog(QuizList *myList, QWidget *parent = 0);
    ~QuizDialog();

private slots:
    void checkAnswer();
    void resetClicked();

private:
    QLabel *listName;
    QLabel *title;
    QLabel *prompt;
    QLabel *info;
    QLineEdit *answer;
    QCheckBox *caseCheckBox;
    QCheckBox *reverseCheckBox;
    QPushButton *checkButton;
    QPushButton *resetButton;
    void getNextPrompt();
};

#endif // QUIZDIALOG_H
