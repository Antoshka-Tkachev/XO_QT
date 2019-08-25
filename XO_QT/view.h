#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include <QFont>
#include <QDebug>
#include <QMessageBox>

#include "logic.h"

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

private slots:
    void error_start();
    void error_restart();

    void on_button_start_clicked();
    void on_button_restart_clicked();
    void on_radioButton_move_X_clicked();
    void on_radioButton_move_O_clicked();
    void on_button_reset_clicked();
    void on_button_1_plus_clicked();
    void on_button_2_plus_clicked();
    void on_button_1_minus_clicked();
    void on_button_2_minus_clicked();

    void score();
    void game_mode(const int & bufer);
    void move();
    void print(QPushButton *button);
    void print_computer_move();
    void end();
    void zeroing_view();

    void text_label_start();// для игры вдвоем

    void connect_move();
    void disconnect_move();
    void connect_error_restart();
    void disconnect_error_restart();
    void connect_error_start();
    void disconnect_error_start();

private:
    Ui::View *ui;
    Logic game;
    QVector<QVector<QPushButton*>> array;
    bool the_end; // отвечает за конец
    int gameMode;
};

#endif // VIEW_H
