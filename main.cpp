/**
 * @file main.cpp
 * @brief The main control, links GUI to backend
 * @author Alex Zirbel
 *
 * The main control for what happens in WordQuiz.
 * Almost nothing should happen in this class itself, except for
 * connecting the GUI to the dictionary and backend.
 *
 * @todo Introduce unit testing - CppUnit
 */

/**
  * @mainpage
  *
  * @section intro_sec Introduction
  *
  * Welcome to WordQuiz! This software is intended as the first attempt of
  * language-learning software meant to expand on vocabulary-learning programs
  * by catering the words presented to individual users.
  *
  * @section organization_sec Organization and Tools
  *
  * WordQuiz is built on QT for all GUI elements, so I recommend installing
  * QT Creator for help with building on your platform.  WordQuiz also uses
  * Boost, extra libraries for C++, which will need to be installed. Finally,
  * this documentation is thanks to Doxygen, which automatically generates
  * documentation based on inline code comments.
  *
  * @section licensing_sec Licensing and joining this project
  *
  * WordQuiz is open source under the GNU General Public License. Since it's
  * still young, I haven't looked into licensing very far yet, but I would like
  * to retrain rights as original creator of the project while allowing other
  * people to download, build on, and improve this software. If you would like
  * contribute to the official version of this project, please contact me.
  */

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "quizdialog.h"

#include "dictionary.h"
#include "vocabquiz.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
