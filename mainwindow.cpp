/**
 * @file mainwindow.cpp
 * @brief The GUI setup function
 * @author Alex Zirbel
 *
 * The main interface and organization of the program.  This is intended to
 * be a GUI only, so that all the backend dictionary and functions are not
 * involved in QT.  At some point, I may switch from QT to another GUI helper,
 * and it is critical for the rest of the code to be independent.
 */

#include "mainwindow.hpp"

using namespace std;

/**
 * Set up the main window and set a default widget.
 * @todo Add a homepage as the default widget?
 */
MainWindow::MainWindow()
{
    createActions();
    createMenus();

    setCurrentFile("");

    setWindowTitle(tr("WordQuiz"));

    setMinimumHeight(STD_HEIGHT);
    setMinimumWidth(STD_WIDTH);

    switchToLoginDialog();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Dictionary"), ".",
                                                    tr("Text files (*.txt)"));
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About WordQuiz"),
                       tr("<h2>WordQuiz 1.0</h2>"
                          "<p>Copyright &copy; 2011 Alex Zirbel"
                          "<p>WordQuiz is a lightweight vocabulary"
                          "quizzing program.</p>"));
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText("location");
    formulaLabel->setText("formula");
}


void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing dictionary file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}


bool MainWindow::loadFile(const QString &fileName)
{
    nextToQuiz = new MasterList;
    nextToQuiz->importDictionaryFromFile(fileName.toStdString());

    setCurrentFile(fileName);

    return true;
}


void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2")
                           .arg(j + 1)
                           .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}


QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void MainWindow::switchToLoginDialog()
{
    loginDialog = new LoginDialog;
    setCentralWidget(loginDialog);

    connect(loginDialog, SIGNAL(submitProfile(UserProfile*)), this,
            SLOT(handleLogin(UserProfile*)));
    //! @todo switch to newprofile
    connect(loginDialog, SIGNAL(requestNewProfile()), this,
            SLOT(switchToNewProfileDialog()));
}


void MainWindow::switchToNewProfileDialog()
{
    newProfileDialog = new NewProfileDialog();
    /*connect(newProfileDialog, SIGNAL(submitProfile(UserProfile*)), this,
            SLOT(handleLogin(UserProfile*)));*/
    connect(newProfileDialog, SIGNAL(back()), this,
            SLOT(switchToLoginDialog()));

    setCentralWidget(newProfileDialog);
}


void MainWindow::switchToLanguageDialog()
{
    // Set up and load the new languageDialog
    languageDialog = new LanguageDialog;
    connect(languageDialog, SIGNAL(submitLanguagePair(LanguagePair*)), this,
            SLOT(handleLanguageChoice(LanguagePair*)));
    connect(languageDialog, SIGNAL(back()), this,
            SLOT(switchToLoginDialog()));

    setCentralWidget(languageDialog);
}


void MainWindow::switchToMenuDialog()
{
    menuDialog = new MenuDialog;
    setCentralWidget(menuDialog);
}


/**
 * Once the login dialog returns an acceptable user profile, sets that profile
 * as the current user's profile and moves on to the next dialog (language
 * choosing).
 * @param profile The loaded user profile
 */
void MainWindow::handleLogin(UserProfile *profile)
{
    // Process this login
    currentUser = *profile;

    switchToLanguageDialog();
}


/**
 * Once the language chooser dialog returns an acceptable pair of languages,
 * it returns those languages as a languagePair so that the mainwindow knows
 * what the user wants to study.
 * @param languages The set of two languages the user will study, including
 *  which one is the user's home language.
 */
void MainWindow::handleLanguageChoice(LanguagePair *languages)
{
    currentLanguages = *languages;

}


void MainWindow::startQuiz()
{
    QuizList *temp = new MasterList;
    quizDialog = new QuizDialog(temp);

    setCentralWidget(quizDialog);
}
