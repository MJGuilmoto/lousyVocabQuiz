#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "userprofile.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class MenuDialog : public QDialog
{
    Q_OBJECT

UserProfile *currentUser;
QuizList *currentQuiz;

QLabel *welcomeText;
QLabel *selectedQuizText;
QPushButton *startQuizButton;
QPushButton *changeUserButton;

public:
    MenuDialog(QWidget *parent = 0);
    ~MenuDialog();
    void setUserProfile(UserProfile *newProfile);

signals:
    void startQuiz();
    void changeUser();

private slots:
    void startButtonClicked();
    void changeUserClicked();


};

#endif // MENUDIALOG_H
