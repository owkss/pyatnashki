#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "board.h"
#include "field.h"
#include "application.h"

#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QDialog>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setObjectName("mainwindow");
    ui->setupUi(this);

    m_field = new Field(this);
    setCentralWidget(m_field);

    QObject::connect(this, &MainWindow::generate_board, m_field, &Field::generate_board);
    QObject::connect(m_field, &Field::step_has_been_taken, this, &MainWindow::step_has_been_taken);
    QObject::connect(m_field, &Field::win, this, &MainWindow::win);

    QObject::connect(ui->new_game_action, &QAction::triggered, this, &MainWindow::new_game_action_triggered);
    QObject::connect(ui->quit_action, &QAction::triggered, this, &MainWindow::quit_action_triggered);
    QObject::connect(ui->background_color_action, &QAction::triggered, this, &MainWindow::background_color_action_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_game_action_triggered()
{
    QDialog d(this);
    if (d.layout()) delete d.layout();
    d.setWindowTitle(tr("Конфигурация поля"));
    d.setMinimumSize(240, 120);
    QFormLayout *fl = new QFormLayout;

    QSpinBox *count_spin = new QSpinBox(&d);
    count_spin->setRange(3, 32);
    count_spin->setValue(m_field->board() ? m_field->board()->count() : 4);

    fl->addRow(tr("Размер"), count_spin);

    QHBoxLayout *hl = new QHBoxLayout;
    QPushButton *ok = new QPushButton(tr("Ок"), &d);
    QPushButton *cancel = new QPushButton(tr("Отмена"), &d);
    hl->addWidget(cancel);
    hl->addWidget(ok);

    QVBoxLayout *vl = new QVBoxLayout;
    QHBoxLayout *fhl = new QHBoxLayout;
    QLineEdit *edit = new QLineEdit(&d);
    QPushButton *btn = new QPushButton(tr("Выбрать"));

    QObject::connect(btn, &QPushButton::clicked, [edit, &d]()
    {
        QString path = QFileDialog::getOpenFileName(&d, tr("Выбор файла"), Application::applicationDirPath(), "Изображения(*.bmp *.gif *.jpg *.jpeg *.png)");
        edit->setText(path);
    });

    edit->setPlaceholderText(tr("Файл картинки"));
    fhl->addWidget(edit);
    fhl->addWidget(btn);

    vl->addLayout(fl);
    vl->addLayout(fhl);
    vl->addLayout(hl);

    d.setLayout(vl);

    QObject::connect(ok, &QPushButton::clicked, &d, &QDialog::accept);
    QObject::connect(cancel, &QPushButton::clicked, &d, &QDialog::reject);

    if (d.exec() == QDialog::Rejected)
        return;

    m_move_count = 0;

    QString path = edit->text();
    if (path.isEmpty())
    {
        path = ":/files/default.jpg";
    }
    else
    {
        if (!QFile::exists(path))
        {
            QMessageBox::warning(&d, tr("Ошибка"), tr("Файл отсутствует"));
            return;
        }
    }

    emit generate_board(count_spin->value(), QImage(path));
}

void MainWindow::quit_action_triggered()
{
    close();
}

void MainWindow::background_color_action_triggered()
{
    QColor c = QColorDialog::getColor(m_field->background_color(), this, tr("Цвет заливки"));
    m_field->set_background_color(c);
}

void MainWindow::step_has_been_taken()
{
    ++m_move_count;
}

void MainWindow::win()
{
    QMessageBox::information(this, tr("Победа"), tr("Поздравляю! Сделано шагов: %1").arg(m_move_count));
    m_move_count = 0;
}

