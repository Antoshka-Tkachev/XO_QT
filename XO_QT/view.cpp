#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: rgb(170, 170, 255)");
    //this->setStyleSheet("background-color: rgb(255, 165, 246)");

    array.resize(3);
       for (int i = 0; i < 3; i++)
       {
           array[i].resize(3);
       }

       for (int i = 0; i < 3; i++)
        {
               for (int j = 0; j < 3; j++)
               {
                   QPushButton* button = new QPushButton;
                   QString name = QString::number(i) + QString::number(j);
                   button->setObjectName(name);
                   button->setText("");
                   button->setFixedSize(120,120);
                   button->setStyleSheet("QPushButton{background:rgb(255, 255, 255)}");
                   array[i][j] = button;
                   ui->gridLayout->addWidget (button, i, j);
               }
       }

    ui->button_restart->setVisible(false);
    ui->button_1_plus->setVisible(false);
    ui->button_2_plus->setVisible(false);
    ui->button_1_minus->setVisible(false);
    ui->button_2_minus->setVisible(false);

    connect(ui->comboBox_gameMode, SIGNAL(currentIndexChanged(const int &)), this, SLOT (game_mode(const int &)));
    gameMode = 0;
    ui->radioButton_move_X->setChecked(true);

    connect_error_start();

    game.set_whose_move(0);
    the_end = false;
}

View::~View()
{
    delete ui;
}

void View::game_mode(const int & bufer)
{
    gameMode = bufer;

    ui->label_start->setText("");
    game.zeroing_logic();
    zeroing_view();
    the_end = false;
    ui->button_start->setVisible(true);
    ui->button_restart->setVisible(false);

    disconnect_move();
    disconnect_error_restart();
    disconnect_error_start();
    connect_error_start();


    if(gameMode == 0)
    {
        ui->radioButton_move_X->setVisible(true);
        ui->radioButton_move_O->setVisible(true);
        ui->button_1_plus->setVisible(false);
        ui->button_2_plus->setVisible(false);
        ui->button_1_minus->setVisible(false);
        ui->button_2_minus->setVisible(false);

        ui->label_text_1->setText("Вы:");
        ui->label_text_2->setText("Компьютер:");
        ui->label_score_1->setNum(game.get_score_0_1());
        ui->label_score_2->setNum(game.get_score_0_2());
    }
    else
    {
        ui->radioButton_move_X->setVisible(false);
        ui->radioButton_move_O->setVisible(false);
        ui->button_1_plus->setVisible(true);
        ui->button_2_plus->setVisible(true);
        ui->button_1_minus->setVisible(true);
        ui->button_2_minus->setVisible(true);

        ui->label_text_1->setText("Игрок 1:");
        ui->label_text_2->setText("Игрок 2:");
        ui->label_score_1->setNum(game.get_score_1_1());
        ui->label_score_2->setNum(game.get_score_1_2());

    }
}

void View::error_start()
{
    QMessageBox :: information(this, "Ошибка", "Нажмите кнопку \"Начать\"!");
}

void View::error_restart()
{
    QMessageBox :: information(this, "Ошибка", "Нажмите кнопку \"Заново\"\nИли выберете другой режим игры!");
}

void View::text_label_start()
{
    if(game.get_whose_move() % 2 == 0)
    {
        ui->label_start->setStyleSheet("QLabel{color:  rgb(200, 0, 0)}");
        ui->label_start->setText("Ходят X!");
    }
    else
    {
        ui->label_start->setStyleSheet("QLabel{color:  blue}");
        ui->label_start->setText("Ходят O!");
    }
}

void View::on_button_start_clicked()
{
    game.set_whose_move(0);

    if(gameMode == 0)
    {
        if(ui->radioButton_move_X->isChecked())
        {
            ui->label_start->setStyleSheet("QLabel{color:  rgb(200, 0, 0)}");
            ui->label_start->setText("Игра началась,\nВы играете X!");
        }
        else
        {
            ui->label_start->setStyleSheet("QLabel{color: blue}");
            ui->label_start->setText("Игра началась,\nВы играете O!");
        }
    }
    else
    {
        ui->label_start->setStyleSheet("QLabel{color: rgb(200, 0, 0)}");
        ui->label_start->setText("Игра началась,\nПервыми ходят X!");
    }

    ui->button_start->setVisible(false);

    disconnect_error_start();
    connect_move();

    if(ui->radioButton_move_O->isChecked() && gameMode == 0)
    {
        game.rand_move();// делаем случайный ход
        print(array[game.get_row()][game.get_column()]);
        game.set_whose_move(1);
    }
}

void View::move()
{
    QPushButton *button = (QPushButton *)sender();
    QString name = sender()->objectName();

    game.set_row_column(name); // устанавливаем индексы

    if(gameMode == 0)// если с компом
    {
        if(game.get_matrix_logic(game.get_row(), game.get_column()) != "X" && game.get_matrix_logic(game.get_row(), game.get_column()) != "O")
        {
            print(button);

            game.set_matrix_logic(game.get_row(), game.get_column(),button->text());

            game.set_whose_move(game.get_whose_move() + 1);//изменяем "Чей ход"

            if(!game.win() && !game.full())
            {
                if(ui->radioButton_move_X->isChecked())//если играем крестиками
                {
                    if (game.attack_O() == 2)// если атака не выполнилась, то выполняем защиту
                        game.defense_O();
                }
                else // если играем ноликами
                {
                    if (game.attack_X() == 2)// если атака не выполнилась, то выполняем защиту
                        game.defense_X();
                }

                print_computer_move();
            }
            else
            {
                end();
            }

            if((game.win() || game.full()) && the_end == false)
            {
                end();
            }
        }
    }
    else if (gameMode == 1)// если с человеком
    {
        if(!game.win() && !game.full())
        {
            print(button);
            game.set_matrix_logic(game.get_row(), game.get_column(),button->text());
            game.set_whose_move(game.get_whose_move() + 1);
            text_label_start();
        }
        else
        {
            end();
        }

        if((game.win() || game.full()) && the_end == false)
        {
            end();
        }
    }
}

void View::print(QPushButton *button)
{
    if(game.get_whose_move() % 2 == 0)
    {
        button->setText("X");
        button->setStyleSheet("QPushButton{background:rgb(255, 255, 255);color: red}");
        QFont f = button->font(); //QFont определяет шрифт, используемый для рисования текста//Font() берет шрифт кнопки
        f.setPointSize(80); //Устанавливает шрифт
        f.setBold(true); //делает жирным (Принимает bool да/нет)
        button->setFont(f);// устанавливает шрифт по переменной f
    }
    else
    {
        button->setText("O");
        button->setStyleSheet("QPushButton {background:rgb(255, 255, 255);color: blue}");
        QFont f = button->font(); //QFont определяет шрифт, используемый для рисования текста//Font() берет шрифт кнопки
        f.setPointSize(80); //Устанавливает шрифт
        f.setBold(true); //делает жирным (Принимает bool да/нет)
        button->setFont(f);// устанавливает шрифт по переменной f
    }
}

void View::print_computer_move()
{
    print(array[game.get_row()][game.get_column()]);
    game.set_whose_move(game.get_whose_move() + 1);
}

void View::end()
{
    the_end = true;

    ui->button_restart->setVisible(true);

    if(game.get_result() == "X")
    {
        ui->label_start->setStyleSheet("QLabel{color:  rgb(200, 0, 0)}");
        ui->label_start->setText("Игра закончена,\nПобедили X!");
    }
    else if(game.get_result() == "O")
    {
        ui->label_start->setStyleSheet("QLabel{color:  blue}");
        ui->label_start->setText("Игра закончена,\nПобедили O!");
    }
    else
    {
        ui->label_start->setStyleSheet("QLabel{color:  rgb(0, 85, 0);}");
        ui->label_start->setText("Игра закончена,\nНичья!");
    }

    score();

    disconnect_move();
    connect_error_restart();
}

void View::zeroing_view()
{
    for (int i = 0; i < 3; i++)
     {
            for (int j = 0; j < 3; j++)
            {
                array[i][j]->setText("");
            }
    }
}

void View::on_button_restart_clicked()
{
    the_end = false;
    ui->button_restart->setVisible(false);

    game.set_whose_move(0);
    game.zeroing_logic();
    zeroing_view();

    if(gameMode == 0)
    {
        if(ui->radioButton_move_X->isChecked())
        {
            ui->label_start->setStyleSheet("QLabel{color:  rgb(200, 00, 0)}");
            ui->label_start->setText("Игра началась,\nВы играете X!");
        }
        else
        {
            ui->label_start->setStyleSheet("QLabel{color:  blue}");
            ui->label_start->setText("Игра началась,\nВы играете O!");
        }
    }
    else
    {
        ui->label_start->setStyleSheet("QLabel{color:  rgb(200, 0, 0);}");
        ui->label_start->setText("Игра началась,\nПервыми ходят X!");
    }

    disconnect_error_restart();
    connect_move();

    if(ui->radioButton_move_O->isChecked() && gameMode == 0)
    {
        game.rand_move();// делаем случайный ход
        print(array[game.get_row()][game.get_column()]);
        game.set_whose_move(1);
    }
}

void View::connect_move()
{
    connect(array[0][0], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[0][1], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[0][2], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[1][0], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[1][1], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[1][2], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[2][0], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[2][1], SIGNAL(clicked()), this, SLOT (move()));
    connect(array[2][2], SIGNAL(clicked()), this, SLOT (move()));
}

void View::disconnect_move()
{
    disconnect(array[0][0], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[0][1], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[0][2], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[1][0], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[1][1], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[1][2], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[2][0], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[2][1], SIGNAL(clicked()), this, SLOT (move()));
    disconnect(array[2][2], SIGNAL(clicked()), this, SLOT (move()));
}

void View::connect_error_start()
{
    connect(array[0][0], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[0][1], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[0][2], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[1][0], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[1][1], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[1][2], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[2][0], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[2][1], SIGNAL(clicked()), this, SLOT (error_start()));
    connect(array[2][2], SIGNAL(clicked()), this, SLOT (error_start()));
}

void View::disconnect_error_start()
{
    disconnect(array[0][0], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[0][1], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[0][2], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[1][0], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[1][1], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[1][2], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[2][0], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[2][1], SIGNAL(clicked()), this, SLOT (error_start()));
    disconnect(array[2][2], SIGNAL(clicked()), this, SLOT (error_start()));
}

void View::connect_error_restart()
{
    connect(array[0][0], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[0][1], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[0][2], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[1][0], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[1][1], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[1][2], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[2][0], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[2][1], SIGNAL(clicked()), this, SLOT (error_restart()));
    connect(array[2][2], SIGNAL(clicked()), this, SLOT (error_restart()));
}

void View::disconnect_error_restart()
{
    disconnect(array[0][0], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[0][1], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[0][2], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[1][0], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[1][1], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[1][2], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[2][0], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[2][1], SIGNAL(clicked()), this, SLOT (error_restart()));
    disconnect(array[2][2], SIGNAL(clicked()), this, SLOT (error_restart()));
}

void View::on_radioButton_move_X_clicked()
{
    ui->label_start->setText("");

    game.zeroing_logic();
    zeroing_view();
    the_end = false;
    ui->button_start->setVisible(true);
    ui->button_restart->setVisible(false);

    disconnect_move();
    disconnect_error_restart();
    disconnect_error_start();
    connect_error_start();
}

void View::on_radioButton_move_O_clicked()
{
    ui->label_start->setText("");

    game.zeroing_logic();
    zeroing_view();
    the_end = false;
    ui->button_start->setVisible(true);
    ui->button_restart->setVisible(false);

    disconnect_move();
    disconnect_error_restart();
    disconnect_error_start();
    connect_error_start();
}

void View::score()
{
    if(gameMode == 0 && ui->radioButton_move_X->isChecked())
    {
        if(game.get_result() == "X")
        {
            game.set_score_0_1(game.get_score_0_1() + 1);
            ui->label_score_1->setNum(game.get_score_0_1());
        }
        if(game.get_result() == "O")
        {
            game.set_score_0_2(game.get_score_0_2() + 1);
            ui->label_score_2->setNum(game.get_score_0_2());
        }
    }

    if(gameMode == 0 && ui->radioButton_move_O->isChecked())
    {
        if(game.get_result() == "X")
        {
            game.set_score_0_2(game.get_score_0_2() + 1);
            ui->label_score_2->setNum(game.get_score_0_2());
        }
        if(game.get_result() == "O")
        {
            game.set_score_1_1(game.get_score_0_1() + 1);
            ui->label_score_1->setNum(game.get_score_0_1());
        }
    }
}

void View::on_button_reset_clicked()
{
    if(gameMode == 0)
    {
        game.set_score_0_1(0);
        game.set_score_0_2(0);
    }
    else
    {
        game.set_score_1_1(0);
        game.set_score_1_2(0);
    }

    ui->label_score_1->setNum(0);
    ui->label_score_2->setNum(0);
}

void View::on_button_1_plus_clicked()
{
    game.set_score_1_1(game.get_score_1_1() + 1);
    ui->label_score_1->setNum(game.get_score_1_1());
}

void View::on_button_2_plus_clicked()
{
    game.set_score_1_2(game.get_score_1_2() + 1);
    ui->label_score_2->setNum(game.get_score_1_2());
}

void View::on_button_1_minus_clicked()
{
    if(game.get_score_1_1() > 0)
    {
        game.set_score_1_1(game.get_score_1_1() - 1);
        ui->label_score_1->setNum(game.get_score_1_1());
    }
}

void View::on_button_2_minus_clicked()
{
    if(game.get_score_1_2() > 0)
    {
        game.set_score_1_2(game.get_score_1_2() - 1);
        ui->label_score_2->setNum(game.get_score_1_2());
    }
}
