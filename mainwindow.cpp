#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Dictionary basicDict;
    basicDict.printContents();

    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
