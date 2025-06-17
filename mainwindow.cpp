#include "mainwindow.h"
#include "./ui_mainwindow.h"

// Constructor: sets up the UI for the main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Destructor: cleans up the UI object
MainWindow::~MainWindow()
{
    delete ui;
}
