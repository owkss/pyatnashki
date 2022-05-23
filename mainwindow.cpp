#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "field.h"

#include <QDebug>
#include <QLabel>
#include <QDialog>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setObjectName("mainwindow");
    ui->setupUi(this);

    m_field = new Field(this);
    setCentralWidget(m_field);

    QObject::connect(this, &MainWindow::set_dimension, m_field, &Field::generate_board);
    QObject::connect(ui->new_game_action, &QAction::triggered, this, &MainWindow::new_game_action_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_game_action_triggered()
{
    // TODO если игра началась то уведомить

    QDialog d(this);
    if (d.layout()) delete d.layout();
    d.setWindowTitle(tr("Конфигурация поля"));
    d.setMinimumSize(240, 120);
    QFormLayout *fl = new QFormLayout;

    QSpinBox *row_spin = new QSpinBox(&d);
    row_spin->setRange(1, 100);
    row_spin->setValue(m_field->board()->row_count());

    QSpinBox *col_spin = new QSpinBox(&d);
    col_spin->setRange(1, 100);
    col_spin->setValue(m_field->board()->column_count());

    fl->addRow(tr("Строки"), row_spin);
    fl->addRow(tr("Столбцы"), col_spin);

    QHBoxLayout *hl = new QHBoxLayout;
    QPushButton *ok = new QPushButton(tr("Ок"), &d);
    QPushButton *cancel = new QPushButton(tr("Отмена"), &d);
    hl->addWidget(cancel);
    hl->addWidget(ok);

    QVBoxLayout *vl = new QVBoxLayout;
    vl->addLayout(fl);
    vl->addLayout(hl);

    d.setLayout(vl);

    QObject::connect(ok, &QPushButton::clicked, &d, &QDialog::accept);
    QObject::connect(cancel, &QPushButton::clicked, &d, &QDialog::reject);

    if (d.exec() == QDialog::Rejected)
        return;

    emit set_dimension(row_spin->value(), col_spin->value());
}

