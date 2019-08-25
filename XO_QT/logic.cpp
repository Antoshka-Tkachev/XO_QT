#include "logic.h"

Logic::Logic()
{
    whose_move = 0;
    row = 0;
    column = 0;
    score_0_1 = 0;
    score_0_2 = 0;
    score_1_1 = 0;
    score_1_2 = 0;

    for (int i = 0; i < 3; i++)
     {
            for (int j = 0; j < 3; j++)
            {
                matrix_logic[i][j] = "";
            }
    }
}

QString Logic::get_matrix_logic(int i, int j) // возвращает состояние клетки
{
    return matrix_logic[i][j];
}

void Logic::set_matrix_logic(int i, int j,QString X_O) // возвращает состояние клетки
{
    matrix_logic[i][j] = X_O;
}

int Logic::get_whose_move() // возвращает чей ход
{
    return whose_move;
}

void Logic::set_whose_move(int temp) // устанавливает чей ход
{
     whose_move = temp;
}

int Logic::get_score_0_1() // возвращает рекорд
{
    return score_0_1;
}

int Logic::get_score_0_2() // возвращает рекорд
{
    return score_0_2;
}

void Logic::set_score_0_1(int score)
{
    score_0_1 = score;
}

void Logic::set_score_0_2(int score)
{
    score_0_2 = score;
}

int Logic::get_score_1_1() // возвращает рекорд
{
    return score_1_1;
}

int Logic::get_score_1_2() // возвращает рекорд
{
    return score_1_2;
}

void Logic::set_score_1_1(int score)
{
    score_1_1 = score;
}

void Logic::set_score_1_2(int score)
{
    score_1_2 = score;
}

QString Logic::get_result() // возвращает результат игры
{
     return result;
}

int Logic::get_row()
{
    return row;
}

int Logic::get_column()
{
    return column;
}

void Logic::set_row_column(QString name)
{
    //row = ((QString)name.at(0)).toInt(); //альтернативная сокращенная запись
    QString i_str = name.at(0);
    QString j_str = name.at(1);
    row = i_str.toInt();
    column = j_str.toInt();
}

void Logic::rand_move()// делает рандомный ход
{
    QTime time = QTime::currentTime();
           qsrand((uint)time.msec());
    int i, j;
    bool complete = false;
    while (!complete) // пока не "выполнено"
    {
        i = qrand() % 3;
        j = qrand() % 3;

        if (matrix_logic[i][j] == "") //если клетка пустая, делаем ход
        {
            if(whose_move % 2 == 0)
            {
                matrix_logic[i][j] = "X";
                row = i;
                column = j;
            }
            else
            {
                matrix_logic[i][j] = "O";
                row = i;
                column = j;
            }
            complete = true;
        }
    }
}

int Logic::attack_O()  // атака O
{
    int bufer_i = -1, bufer_j = -1; // для хранения соседнего элемента
    for (int i = 0; i < 3; i++)		// в поле ищем O
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix_logic[i][j] == "O")   //если нашли
            {

                if (!(i == 1 && j == 1) && matrix_logic[1][1] == "O") //если не в центре, но есть центральный элемент, по переводим на ситуацию "центр"
                    goto center;

                if (i == 1 && j == 1) // если он в центре то
                {
                center:
                    for (int q = 0; q < 3; q++) //ищем "Соседа", пропуская центр
                    {
                        for (int p = 0; p < 3; p++)
                        {
                            if (!(q == 1 && p == 1) && matrix_logic[q][p] == "O")// если нашли "Соседа" не в центре
                            {
                                bufer_i = q; //запоминаем индексы "Соседа"
                                bufer_j = p;

                                bufer_i = 1 - bufer_i; //находим "шаг"
                                bufer_j = 1 - bufer_j;
                                bufer_i = 1 + bufer_i; //находим индексы "недостоющей до тройки" ячейки
                                bufer_j = 1 + bufer_j;
                                if (matrix_logic[bufer_i][bufer_j] == "")//если эта ячейка пустая, то запоняем
                                {
                                    matrix_logic[bufer_i][bufer_j] = "O";

                                    row = bufer_i;
                                    column = bufer_j;

                                    return 1;
                                }
                            }
                        }
                    }
                }

                if (i != 1 && j != 1 && matrix_logic[i][j] == "O") //если Х в углу, то ищем пару
                {
                    int count = 0; //cчетчик кол-ва угловых элементов

                    for (int q = 0; q < 3; q += 2) //считаем кол-во угловых элементов
                        for (int p = 0; p < 3; p += 2)
                            if (matrix_logic[q][p] == 'O')
                                count++;

                    if (count > 1) // если элементов 2 и больше, то ищем пары
                    {
                        if ((matrix_logic[0][0] == "O" && matrix_logic[2][2] == "O") || (matrix_logic[0][2] == "O" && matrix_logic[2][0] == "O")) //если пара диагональна
                        {
                            if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                            {
                                matrix_logic[1][1] = "O";

                                row = 1;
                                column = 1;

                                return 1;
                            }
                        }

                        //4 варианта соседих углов
                        // если есть пара и элемент между ними свободен, то делаем этот ход
                        if (matrix_logic[0][0] == "O" && matrix_logic[0][2] == "O" && matrix_logic[0][1] == "")
                        {
                            matrix_logic[0][1] = "O";

                            row = 0;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][0] == "O" && matrix_logic[2][0] == "O" && matrix_logic[1][0] == "")
                        {
                            matrix_logic[1][0] = "O";

                            row = 1;
                            column = 0;

                            return 1;
                        }
                        if (matrix_logic[2][0] == "O" && matrix_logic[2][2] == "O" && matrix_logic[2][1] == "")
                        {
                            matrix_logic[2][1] = "O";

                            row = 2;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][2] == "O" && matrix_logic[2][2] == "O" && matrix_logic[1][2] == "")
                        {
                            matrix_logic[1][2] = "O";

                            row = 1;
                            column = 2;

                            return 1;
                        }
                    }
                }

                if ((matrix_logic[1][0] == "O" && matrix_logic[1][2] == "O") || (matrix_logic[0][1] == "O" && matrix_logic[2][1] == "O")) //если пара противоположная
                {
                    if (matrix_logic[1][1] == "O") // и центр свободен, то ставим в центр
                    {
                        matrix_logic[1][1] = "O";

                        row = 1;
                        column = 1;

                        return 1;
                    }
                }

                //8 ситуаций на соседние элементы
                if (matrix_logic[0][0] == "O" && matrix_logic[0][1] == "O" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "O";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][1] == "O" && matrix_logic[0][2] == "O" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "O";

                    row = 0;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[0][2] == "O" && matrix_logic[1][2] == "O" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "O";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[1][2] == "O" && matrix_logic[2][2] == "O" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "O";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[2][2] == "O" && matrix_logic[2][1] == "O" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "O";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[2][0] == "O" && matrix_logic[2][1] == "O" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "O";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][0] == "O" && matrix_logic[1][0] == "O" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "O";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[1][0] == "O" && matrix_logic[2][0] == "O" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "O";

                    row = 0;
                    column = 0;
                    return 1;
                }

                return 2;
            }
        }
    }
    return 2; // при успешной атаке возвращает 1, если атака не произведена, то возвращает 2
}

int Logic::defense_O() // защита O
{
    int bufer_i = -1, bufer_j = -1; // для хранения соседнего элемента
    for (int i = 0; i < 3; i++) // в поле ищем Х
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix_logic[i][j] == "X") //если нашли
            {

                if (!(i == 1 && j == 1) && matrix_logic[1][1] == "X") //если не в центре, но есть центральный элемент, по переводим на ситуацию "центр"
                    goto center;

                if (i == 1 && j == 1) // если он в центре то
                {
                center:
                    for (int q = 0; q < 3; q++) //ищем "Соседа", пропуская центр
                    {
                        for (int p = 0; p < 3; p++)
                        {
                            if (!(q == 1 && p == 1) && matrix_logic[q][p] == "X") // если нашли не в центре
                            {
                                bufer_i = q; //запоминаем индексы "Соседа"
                                bufer_j = p;

                                bufer_i = 1 - bufer_i; //находим "шаг"
                                bufer_j = 1 - bufer_j;
                                bufer_i = 1 + bufer_i; //находим индексы "недостоющей до тройки" ячейки
                                bufer_j = 1 + bufer_j;
                                if (matrix_logic[bufer_i][bufer_j] == "")//если эта ячейка пустая, то запоняем
                                {
                                    matrix_logic[bufer_i][bufer_j] = "O";

                                    row = bufer_i;
                                    column = bufer_j;

                                    return 1;
                                }
                            }
                        }
                    }
                }

                if (i != 1 && j != 1 && matrix_logic[i][j] == "X") //если Х в углу, то ищем пару
                {
                    int count = 0; //cчетчик кол-ва угловых элементов

                    for (int q = 0; q < 3; q += 2) //считаем кол-во угловых элементов
                        for (int p = 0; p < 3; p += 2)
                            if (matrix_logic[q][p] == "X")
                                count++;

                    if (count > 1) // если элементов 2 и больше, то ищем пары
                    {
                        if ((matrix_logic[0][0] == "X" && matrix_logic[2][2] == "X") || (matrix_logic[0][2] == "X" && matrix_logic[2][0] == "X")) //если пара диагональна
                        {
                            if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                            {
                                matrix_logic[1][1] = "O";

                                row = 1;
                                column = 1;

                                return 1;
                            }
                        }

                        //4 варианта соседих углов
                        // если есть пара и элемент между ними свободен, то делаем этот ход
                        if (matrix_logic[0][0] == "X" && matrix_logic[0][2] == "X" && matrix_logic[0][1] == "")
                        {
                            matrix_logic[0][1] = "O";

                            row = 0;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][0] == "X" && matrix_logic[2][0] == "X" && matrix_logic[1][0] == "")
                        {
                            matrix_logic[1][0] = "O";

                            row = 1;
                            column = 0;

                            return 1;
                        }
                        if (matrix_logic[2][0] == "X" && matrix_logic[2][2] == "X" && matrix_logic[2][1] == "")
                        {
                            matrix_logic[2][1] = "O";

                            row = 2;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][2] == "X" && matrix_logic[2][2] == "X" && matrix_logic[1][2] == "")
                        {
                            matrix_logic[1][2] = "O";

                            row = 1;
                            column = 2;

                            return 1;
                        }
                    }
                }

                if ((matrix_logic[1][0] == "X" && matrix_logic[1][2] == "X") || (matrix_logic[0][1] == "X" && matrix_logic[2][1] == "X")) //если пара противоположная
                {
                    if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                    {
                        matrix_logic[1][1] = "O";

                        row = 1;
                        column = 1;

                        return 1;
                    }
                }

                //8 ситуаций на соседние элементы
                if (matrix_logic[0][0] == "X" && matrix_logic[0][1] == "X" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "O";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][1] == "X" && matrix_logic[0][2] == "X" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "O";

                    row = 0;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[0][2] == "X" && matrix_logic[1][2] == "X" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "O";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[1][2] == "X" && matrix_logic[2][2] == "X" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "O";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[2][2] == "X" && matrix_logic[2][1] == "X" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "O";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[2][0] == "X" && matrix_logic[2][1] == "X" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "O";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][0] == "X" && matrix_logic[1][0] == "X" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "O";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[1][0] == "X" && matrix_logic[2][0] == "X" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "O";

                    row = 0;
                    column = 0;

                    return 1;
                }

                rand_move(); //если нет в выше рассматриваемых ситуацях, то ходит рандомно
                return 1;
            }
        }
    }

    rand_move(); //если нет в выше рассматриваемых ситуацях, то рандомно
    return 1; // возвращает 1, когда ход сделан (ход делается в любос случае)
}

int Logic::attack_X()  // атака Х
{
    int bufer_i = -1, bufer_j = -1; // для хранения соседнего элемента
    for (int i = 0; i < 3; i++) // в поле ищем Х
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix_logic[i][j] == "X") // если нашли
            {

                if (!(i == 1 && j == 1) && matrix_logic[1][1] == "X") //если не в центре, но есть центральный элемент, по переводим на ситуацию "центр"
                    goto center;

                if (i == 1 && j == 1) // если он в центре то
                {
                center:
                    for (int q = 0; q < 3; q++) //ищем "Соседа", пропуская центр
                    {
                        for (int p = 0; p < 3; p++)
                        {
                            if (!(q == 1 && p == 1) && matrix_logic[q][p] == "X") //если нашли не в центре
                            {
                                bufer_i = q; //запоминаем индексы "Соседа"
                                bufer_j = p;

                                bufer_i = 1 - bufer_i; //находим "шаг"
                                bufer_j = 1 - bufer_j;
                                bufer_i = 1 + bufer_i; //находим индексы "недостоющей до тройки" ячейки
                                bufer_j = 1 + bufer_j;
                                if (matrix_logic[bufer_i][bufer_j] == "")//если эта ячейка пустая, то запоняем
                                {
                                    matrix_logic[bufer_i][bufer_j] = "X";

                                    row = bufer_i;
                                    column = bufer_j;

                                    return 1;
                                }
                            }
                        }
                    }
                }

                if (i != 1 && j != 1 && matrix_logic[i][j] == "X") //если Х в углу, то ищем пару
                {
                    int count = 0; //cчетчик кол-ва угловых элементов

                    for (int q = 0; q < 3; q += 2) //считаем кол-во угловых элементов
                        for (int p = 0; p < 3; p += 2)
                            if (matrix_logic[q][p] == "X")
                                count++;

                    if (count > 1) // если элементов 2 и больше, то ищем пары
                    {
                        if ((matrix_logic[0][0] == "X" && matrix_logic[2][2] == "X") || (matrix_logic[0][2] == "X" && matrix_logic[2][0] == "X")) //если пара диагональна
                        {
                            if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                            {
                                matrix_logic[1][1] = "X";

                                row = 1;
                                column = 1;

                                return 1;
                            }
                        }

                        //4 варианта соседих углов
                        // если есть пара и элемент между ними свободен, то делаем этот ход
                        if (matrix_logic[0][0] == "X" && matrix_logic[0][2] == "X" && matrix_logic[0][1] == "")
                        {
                            matrix_logic[0][1] = "X";

                            row = 0;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][0] == "X" && matrix_logic[2][0] == "X" && matrix_logic[1][0] == "")
                        {
                            matrix_logic[1][0] = "X";

                            row = 1;
                            column = 0;

                            return 1;
                        }
                        if (matrix_logic[2][0] == "X" && matrix_logic[2][2] == "X" && matrix_logic[2][1] == "")
                        {
                            matrix_logic[2][1] = "X";

                            row = 2;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][2] == "X" && matrix_logic[2][2] == "X" && matrix_logic[1][2] == "")
                        {
                            matrix_logic[1][2] = "X";

                            row = 1;
                            column = 2;

                            return 1;
                        }
                    }
                }

                if ((matrix_logic[1][0] == "X" && matrix_logic[1][2] == "X") || (matrix_logic[0][1] == "X" && matrix_logic[2][1] == "X")) //если пара противоположная
                {
                    if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                    {
                        matrix_logic[1][1] = "X";

                        row = 1;
                        column = 1;

                        return 1;
                    }
                }

                //8 ситуаций на соседние элементы
                if (matrix_logic[0][0] == "X" && matrix_logic[0][1] == "X" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "X";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][1] == "X" && matrix_logic[0][2] == "X" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "X";

                    row = 0;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[0][2] == "X" && matrix_logic[1][2] == "X" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "X";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[1][2] == "X" && matrix_logic[2][2] == "X" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "X";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[2][2] == "X" && matrix_logic[2][1] == "X" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "X";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[2][0] == "X" && matrix_logic[2][1] == "X" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "X";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][0] == "X" && matrix_logic[1][0] == "X" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "X";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[1][0] == "X" && matrix_logic[2][0] == "X" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "X";

                    row = 0;
                    column = 0;

                    return 1;
                }

                return 2;
            }
        }
    }
    // при успешной атаке возвращает 1, если атака не произведена, то возвращает 2
    return 2;
}

int Logic::defense_X() // защита X
{
    int bufer_i = -1, bufer_j = -1; // для хранения соседнего элемента
    for (int i = 0; i < 3; i++) // в поле ищем O
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix_logic[i][j] == "O") // если нашли
            {

                if (!(i == 1 && j == 1) && matrix_logic[1][1] == "O") //если не в центре, но есть центральный элемент, по переводим на ситуацию "центр"
                    goto center;

                if (i == 1 && j == 1) // если он в центре то
                {
                center:
                    for (int q = 0; q < 3; q++) //ищем "Соседа", пропуская центр
                    {
                        for (int p = 0; p < 3; p++)
                        {
                            if (!(q == 1 && p == 1) && matrix_logic[q][p] == "O") // если нашли не в центре
                            {
                                bufer_i = q; //запоминаем индексы "Соседа"
                                bufer_j = p;

                                bufer_i = 1 - bufer_i; //находим "шаг"
                                bufer_j = 1 - bufer_j;
                                bufer_i = 1 + bufer_i; //находим индексы "недостоющей до тройки" ячейки
                                bufer_j = 1 + bufer_j;
                                if (matrix_logic[bufer_i][bufer_j] == "")//если эта ячейка пустая, то запоняем
                                {
                                    matrix_logic[bufer_i][bufer_j] = "X";

                                    row = bufer_i;
                                    column = bufer_j;

                                    return 1;
                                }
                            }
                        }
                    }
                }

                if (i != 1 && j != 1 && matrix_logic[i][j] == "O") //если Х в углу, то ищем пару
                {
                    int count = 0; //cчетчик кол-ва угловых элементов

                    for (int q = 0; q < 3; q += 2) //считаем кол-во угловых элементов
                        for (int p = 0; p < 3; p += 2)
                            if (matrix_logic[q][p] == "O")
                                count++;

                    if (count > 1) // если элементов 2 и больше, то ищем пары
                    {
                        if ((matrix_logic[0][0] == "O" && matrix_logic[2][2] == "O") || (matrix_logic[0][2] == "O" && matrix_logic[2][0] == "O")) //если пара диагональна
                        {
                            if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                            {
                                matrix_logic[1][1] = "X";

                                row = 1;
                                column = 1;

                                return 1;
                            }
                        }

                        //4 варианта соседих углов
                        // если есть пара и элемент между ними свободен, то делаем этот ход
                        if (matrix_logic[0][0] == "O" && matrix_logic[0][2] == "O" && matrix_logic[0][1] == "")
                        {
                            matrix_logic[0][1] = "X";

                            row = 0;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][0] == "O" && matrix_logic[2][0] == "O" && matrix_logic[1][0] == "")
                        {
                            matrix_logic[1][0] = "X";

                            row = 1;
                            column = 0;

                            return 1;
                        }
                        if (matrix_logic[2][0] == "O" && matrix_logic[2][2] == "O" && matrix_logic[2][1] == "")
                        {
                            matrix_logic[2][1] = "X";

                            row = 2;
                            column = 1;

                            return 1;
                        }
                        if (matrix_logic[0][2] == "O" && matrix_logic[2][2] == "O" && matrix_logic[1][2] == "")
                        {
                            matrix_logic[1][2] = "X";

                            row = 1;
                            column = 2;

                            return 1;
                        }
                    }
                }

                if ((matrix_logic[1][0] == "O" && matrix_logic[1][2] == "O") || (matrix_logic[0][1] == "O" && matrix_logic[2][1] == "O")) //если пара противоположная
                {
                    if (matrix_logic[1][1] == "") // и центр свободен, то ставим в центр
                    {
                        matrix_logic[1][1] = "X";

                        row = 1;
                        column = 1;

                        return 1;
                    }
                }

                //8 ситуаций на соседние элементы
                if (matrix_logic[0][0] == "O" && matrix_logic[0][1] == "O" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "X";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][1] == "O" && matrix_logic[0][2] == "O" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "X";

                    row = 0;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[0][2] == "O" && matrix_logic[1][2] == "O" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "X";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[1][2] == "O" && matrix_logic[2][2] == "O" &&  matrix_logic[0][2] == "")
                {
                    matrix_logic[0][2] = "X";

                    row = 0;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[2][2] == "O" && matrix_logic[2][1] == "O" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "X";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[2][0] == "O" && matrix_logic[2][1] == "O" &&  matrix_logic[2][2] == "")
                {
                    matrix_logic[2][2] = "X";

                    row = 2;
                    column = 2;

                    return 1;
                }
                if (matrix_logic[0][0] == "O" && matrix_logic[1][0] == "O" &&  matrix_logic[2][0] == "")
                {
                    matrix_logic[2][0] = "X";

                    row = 2;
                    column = 0;

                    return 1;
                }
                if (matrix_logic[1][0] == "O" && matrix_logic[2][0] == "O" &&  matrix_logic[0][0] == "")
                {
                    matrix_logic[0][0] = "X";

                    row = 0;
                    column = 0;

                    return 1;
                }

                rand_move(); //если нет в выше рассматриваемых ситуациях, то делает рандомный ход
                return 1;
            }
        }
    }

    rand_move(); //если нет в выше рассматриваемых ситуациях, то делает рандомный ход
    return 1; // возвращает 1, когда ход сделан (ход делается в любос случае)
}

bool Logic::full()     //проверяет на заполненность
{

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matrix_logic[i][j] == "") // если найдено хоть одно свободное поле,
                return false;	  // то возвращием false

    result = "N";                //присваем резальтату "Ничью"

    return true;
}

bool Logic::win() // проверяет на победу
{
    bool complete = false;
    //если найдена победная комбинация, то "результату" присваеваем значение победной комбинации
    if (matrix_logic[0][0] == matrix_logic[0][1] && matrix_logic[0][1] == matrix_logic[0][2] && matrix_logic[0][0] != "")
    {
        complete = true;
        result = matrix_logic[0][0];
    }
    if (matrix_logic[1][0] == matrix_logic[1][1] && matrix_logic[1][1] == matrix_logic[1][2] && matrix_logic[1][0] != "")
    {
        complete = true;
        result = matrix_logic[1][0];
    }
    if (matrix_logic[2][0] == matrix_logic[2][1] && matrix_logic[2][1] == matrix_logic[2][2] && matrix_logic[2][0] != "")
    {
        complete = true;
        result = matrix_logic[2][0];
    }
    if (matrix_logic[0][0] == matrix_logic[1][0] && matrix_logic[1][0] == matrix_logic[2][0] && matrix_logic[0][0] != "")
    {
        complete = true;
        result = matrix_logic[0][0];
    }
    if (matrix_logic[0][1] == matrix_logic[1][1] && matrix_logic[1][1] == matrix_logic[2][1] && matrix_logic[0][1] != "")
    {
        complete = true;
        result = matrix_logic[0][1];
    }
    if (matrix_logic[0][2] == matrix_logic[1][2] && matrix_logic[1][2] == matrix_logic[2][2] && matrix_logic[0][2] != "")
    {
        complete = true;
        result = matrix_logic[0][2];
    }

    if (matrix_logic[0][0] == matrix_logic[1][1] && matrix_logic[1][1] == matrix_logic[2][2] && matrix_logic[0][0] != "")
    {
        complete = true;
        result = matrix_logic[0][0];
    }
    if (matrix_logic[0][2] == matrix_logic[1][1] && matrix_logic[1][1] == matrix_logic[2][0] && matrix_logic[0][2] != "")
    {
        complete = true;
        result = matrix_logic[0][2];
    }
    //возвращает true если победа, если игра продолжается, то false
    return complete;
}

void Logic::zeroing_logic()
{
    whose_move = 0;

    for (int i = 0; i < 3; i++)
     {
            for (int j = 0; j < 3; j++)
            {
                matrix_logic[i][j] = "";
            }
    }
}
