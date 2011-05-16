/**
 * @file logindialog.h
 * @brief Header definitions for the login dialog class
 * @author Alex Zirbel
 */

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <boost/lexical_cast.hpp>

#include "profilemanager.hpp"
#include "userprofile.hpp"

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
    void newProfileClicked();

private:
    QLabel *loginPrompt;
    QLineEdit *usernameLineEdit;
    QPushButton *loginButton;
    QPushButton *newProfileButton;
};

#endif // QUIZDIALOG_H
