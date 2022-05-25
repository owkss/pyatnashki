#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Field;
class QImage;
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
    void quit_action_triggered();
    void step_has_been_taken();
    void win();

private:
    Ui::MainWindow *ui;
    Field *m_field = nullptr;

    int m_move_count = 0;

signals:
    void generate_board(int r, int c, const QImage &img = QImage(":/files/default.jpg"));
};
#endif // MAINWINDOW_H
