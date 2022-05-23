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

public slots:

private slots:
    void new_game_action_triggered();

private:
    Ui::MainWindow *ui;
    Field *m_field = nullptr;

signals:
    void set_dimension(int r, int c);
};
#endif // MAINWINDOW_H
