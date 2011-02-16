/**
 * @file main.cpp
 * @brief The main control, links GUI to backend
 * @author Alex Zirbel
 *
 * The main control for what happens in WordQuiz.
 * Almost nothing should happen in this class itself, except for
 * connecting the GUI to the dictionary and backend.
 */

#include <QtGui/QApplication>
#include "mainwindow.h"

#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Dictionary basicDict;
    basicDict.printContents(STANDARD);
    cout << endl;
    basicDict.printContents(REVERSE);

    return a.exec();
}
