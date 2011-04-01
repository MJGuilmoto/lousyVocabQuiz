#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <boost/lexical_cast.hpp>

#include "profilemanager.h"
#include "userprofile.h"

class QLabel;
class QLineEdit;
class QPushButton;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void submitProfile(UserProfile *profile);

private slots:
    void loginClicked();

private:
    QLabel *loginPrompt;
    QLineEdit *usernameLineEdit;
    QPushButton *loginButton;
};

#endif // QUIZDIALOG_H
