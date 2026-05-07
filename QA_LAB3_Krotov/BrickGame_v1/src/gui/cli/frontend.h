#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris_lib.h"

/**
 * @brief Главная функция отрисовки — вызывает все вспомогательные функции GUI
 * @param game_info Текущее состояние игры для отображения
 */
void fill_window(GameInfo_t game_info);

/**
 * @brief Отрисовывает текущую падающую фигуру на игровом поле
 */
void print_Figure();

/**
 * @brief Отрисовывает игровое поле HEIGHT×WIDTH с зафиксированными блоками
 * @param game_info Текущее состояние игры
 */
void print_boardGame(GameInfo_t game_info);

/**
 * @brief Отрисовывает информационную панель: рекорд, счёт, уровень, следующая фигура
 * @param game_info Текущее состояние игры
 */
void print_boardInfo(GameInfo_t game_info);

/**
 * @brief Отрисовывает рамку игрового поля
 */
void print_borders();

/**
 * @brief Отображает экран паузы с подсказками по управлению
 */
void print_pauseInfo();

/**
 * @brief Отображает экран конца игры
 */
void print_gameOver();

/**
 * @brief Отображает стартовый экран с подсказками по управлению
 */
void print_startGame();

#endif  // FRONTEND_H
