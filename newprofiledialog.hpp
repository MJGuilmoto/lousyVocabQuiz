/**
 * @file newprofiledialog.hpp
 * @brief Header definitions for the new profile dialog class
 * @author Alex Zirbel
 */

#ifndef NEWPROFILEDIALOG_H
#define NEWPROFILEDIALOG_H

#include <QDialog>
#include <boost/lexical_cast.hpp>

#include "profilemanager.hpp"
#include "util_global.hpp"
#include "userprofile.hpp"

class QLabel;
class QLineEdit;
class QPushButton;

class NewProfileDialog : public QDialog
{
    Q_OBJECT

ProfileManager *profileManager;

QLabel *usernamePrompt;
QLabel *usernamePromptSub;
QLineEdit *usernameLineEdit;
QLabel *fullNamePrompt;
QLabel *fullNamePromptSub;
QLineEdit *fullNameLineEdit;
QPushButton *createButton;
QPushButton *backButton;

public:
    NewProfileDialog(QWidget *parent = 0);
    ~NewProfileDialog();

signals:
    void submitProfile(UserProfile *profile);
    void back();

private slots:
    void createClicked();
    void backClicked();
};

#endif // NEWPROFILEDIALOG_H

