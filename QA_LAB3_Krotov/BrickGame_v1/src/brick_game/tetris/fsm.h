#ifndef FSM_H
#define FSM_H

#include "backend.h"
#include "defines.h"
#include "tetris_lib.h"

/**
 * @brief Основной диспетчер конечного автомата
 *
 * Вызывает нужный обработчик в зависимости от текущего состояния игры.
 * Сбрасывает флаг нажатия кнопки после обработки.
 */
void sigact();

/**
 * @brief Обработчик состояния Begin — ожидание старта
 * @param full_info Указатель на полное состояние игры
 */
void start_handler(FullInfo *full_info);

/**
 * @brief Обработчик состояния Moving — движение фигуры по вводу пользователя
 * @param full_info Указатель на полное состояние игры
 */
void moving_handler(FullInfo *full_info);

/**
 * @brief Обработчик состояния Break — пауза
 * @param full_info Указатель на полное состояние игры
 */
void pause_handler(FullInfo *full_info);

/**
 * @brief Обработчик состояния Spawn — инициализация новой фигуры
 * @param full_info Указатель на полное состояние игры
 */
void spawn_figure(FullInfo *full_info);

/**
 * @brief Обработчик состояния Attaching — фиксация фигуры на поле
 * @param full_info Указатель на полное состояние игры
 */
void attaching_handler(FullInfo *full_info);

#endif  // FSM_H
