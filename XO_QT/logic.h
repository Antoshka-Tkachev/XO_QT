#ifndef LOGIC_H
#define LOGIC_H

#include <QString>
#include <QTime>

class Logic
{
private:
    QString matrix_logic[3][3];
    QString result;
    int whose_move;
    int row;
    int column;
    int score_0_1;
    int score_0_2;
    int score_1_1;
    int score_1_2;

public:
    Logic();
    QString get_matrix_logic(int i, int j);
    void set_matrix_logic(int i, int j, QString X_O);

    int get_whose_move();
    void set_whose_move(int temp);

    int get_score_0_1();
    int get_score_0_2();
    int get_score_1_1();
    int get_score_1_2();
    void set_score_0_1(int score);
    void set_score_0_2(int score);
    void set_score_1_1(int score);
    void set_score_1_2(int score);

    QString get_result();

    int get_row();
    int get_column();
    void set_row_column(QString name);

    void rand_move();
    int attack_O();
    int defense_O();
    int attack_X();
    int defense_X();

    bool full();
    bool win();

    void zeroing_logic();
};

#endif // LOGIC_H
