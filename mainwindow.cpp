#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setObjectName("mainwindow");
    ui->setupUi(this);

    m_field = new Field(this);
    setCentralWidget(m_field);
}

MainWindow::~MainWindow()
{
    delete ui;
}

