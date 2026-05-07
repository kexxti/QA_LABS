#ifndef MAIN_H
#define MAIN_H

#include <locale.h>

#include "brick_game/tetris/tetris_lib.h"
#include "gui/cli/frontend.h"

/**
 * @brief Основной игровой цикл: обновляет состояние, отрисовывает и обрабатывает ввод
 */
void run();

/**
 * @brief Преобразует код клавиши в действие пользователя и передаёт в FSM
 * @param user_action Код нажатой клавиши (результат getch())
 */
void get_user_input(int user_action);

#endif  // MAIN_H
