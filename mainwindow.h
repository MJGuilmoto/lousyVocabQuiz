#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userprofile.h"

#include "quizdialog.h"
#include "menudialog.h"
#include "logindialog.h"

#include "util_global.h"

class QAction;
class QLabel;
class LoginDialog;
class QuizDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void handleLogin(UserProfile *profile);
    void startQuiz();
    void showLoginScreen();
    void showQuizScreen();

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

    LoginDialog *loginDialog;
    MenuDialog *menuDialog;
    QuizDialog *quizDialog;

    UserProfile currentUser;
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
};

#endif
