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

FillInVocabQuiz *myQuiz;
std::string curPrompt;
int numCorrect, numWrong;

public:
    //QuizDialog(QWidget *parent = 0);
    QuizDialog(FillInVocabQuiz *quiz, QWidget *parent = 0);

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void checkAnswer();
    void resetClicked();

private:
    QLabel *title;
    QLabel *prompt;
    QLabel *info;
    QLineEdit *answer;
    QCheckBox *caseCheckBox;
    QCheckBox *reverseCheckBox;
    QPushButton *checkButton;
    QPushButton *resetButton;
    QPushButton *closeButton;
    void getNextPrompt();
};

#endif // QUIZDIALOG_H
