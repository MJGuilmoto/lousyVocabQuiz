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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
