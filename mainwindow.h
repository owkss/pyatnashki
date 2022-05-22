#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Field;
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Field *m_field = nullptr;
};
#endif // MAINWINDOW_H
