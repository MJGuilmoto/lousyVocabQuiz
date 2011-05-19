/**
 * @file mainwindow.hpp
 * @brief Header definitions for the main window class
 * @author Alex Zirbel
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "quizdialog.hpp"
#include "logindialog.hpp"
#include "newprofiledialog.hpp"
#include "languagedialog.hpp"
#include "menudialog.hpp"

#include "languagepair.hpp"
#include "userprofile.hpp"

#include "util_global.hpp"

class QAction;
class QLabel;
//! @todo remove - I don't think these are necessary
class LoginDialog;
class LanguageDialog;
class NewProfileDialog;
class QuizDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

LoginDialog *loginDialog;
NewProfileDialog *newProfileDialog;
LanguageDialog *languageDialog;
MenuDialog *menuDialog;
QuizDialog *quizDialog;

//! Global variables for the session. Is there a way around them?
UserProfile currentUser;

//! Stores the current pair of languages the user is studying, including
//! which one the user has set as their home language.
LanguagePair currentLanguages;
bool homeIsStandard;
MasterList *nextToQuiz;

QLabel *locationLabel;
QLabel *formulaLabel;
QStringList recentFiles;
QString curFile;

enum { MaxRecentFiles = 3 };
QAction *recentFileActions[MaxRecentFiles];
QAction *separatorAction;

QMenu *fileMenu;
QMenu *helpMenu;
QToolBar *fileToolBar;
QAction *openAction;
QAction *exitAction;
QAction *aboutAction;
QAction *aboutQtAction;

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void about();
    void openRecentFile();
    void updateStatusBar();

    void switchToLoginDialog();
    void switchToNewProfileDialog();
    void switchToLanguageDialog();
    void switchToMenuDialog();

    void handleLogin(UserProfile *profile);
    void handleLanguageChoice(LanguagePair *languages);
    void startQuiz();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    bool loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

};

#endif
