#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>

#include "defines.h"
#include "tetris_lib.h"

/**
 * @brief Считывает рекорд из файла и сохраняет в структуру
 * @param full_info Указатель на полное состояние игры
 */
void get_highscore(FullInfo *full_info);

/**
 * @brief Записывает текущий счёт в файл рекордов
 * @param full_info Указатель на полное состояние игры
 */
void set_highscore(FullInfo *full_info);

/**
 * @brief Случайным образом создаёт следующую фигуру из 7 шаблонов
 * @param full_info Указатель на полное состояние игры
 */
void create_next_figure(FullInfo *full_info);

/**
 * @brief Инициализирует игру: выделяет память, сбрасывает счёт и уровень
 * @param full_info Указатель на полное состояние игры
 */
void start_game(FullInfo *full_info);

/**
 * @brief Завершает игру: освобождает память поля и следующей фигуры
 * @param full_info Указатель на полное состояние игры
 */
void end_game(FullInfo *full_info);

/**
 * @brief Сдвигает фигуру на одну клетку влево (если нет коллизии)
 * @param full_info Указатель на полное состояние игры
 */
void move_left(FullInfo *full_info);

/**
 * @brief Сдвигает фигуру на одну клетку вправо (если нет коллизии)
 * @param full_info Указатель на полное состояние игры
 */
void move_right(FullInfo *full_info);

/**
 * @brief Проверяет столкновение фигуры с нижней границей или блоками на поле
 * @param game_info Текущее состояние игрового поля
 * @param figure Проверяемая фигура
 * @return true если фигура столкнулась с препятствием, false иначе
 */
bool check_collision(GameInfo_t game_info, Figure figure);

/**
 * @brief Опускает фигуру на одну клетку вниз или переходит в состояние Attaching
 * @param full_info Указатель на полное состояние игры
 */
void move_down(FullInfo *full_info);

/**
 * @brief Вычисляет новую фигуру после поворота на 90° по часовой стрелке
 *
 * Алгоритм вращения матрицы N×N:
 * \f[ result[j][N-i-1] = matrix[i][j] \f]
 *
 * @param full_info Указатель на полное состояние игры
 * @return Новый объект Figure с повёрнутыми координатами блоков
 */
Figure rotated_figure(FullInfo *full_info);

/**
 * @brief Поворачивает текущую фигуру с проверкой границ и коллизий
 * @param full_info Указатель на полное состояние игры
 */
void rotate(FullInfo *full_info);

/**
 * @brief Фиксирует блоки текущей фигуры на игровом поле
 * @param full_info Указатель на полное состояние игры
 */
void refresh_field(FullInfo *full_info);

/**
 * @brief Проверяет условие конца игры (блоки достигли второй строки)
 * @param full_info Указатель на полное состояние игры
 * @return true если игра окончена, false иначе
 */
bool check_gameover(FullInfo *full_info);

/**
 * @brief Повышает уровень при достижении порогового счёта
 *
 * Уровень повышается каждые 600 очков: \f[ score > level \times 600 \f]
 * Максимальный уровень — 10.
 *
 * @param full_info Указатель на полное состояние игры
 */
void set_level(FullInfo *full_info);

/**
 * @brief Удаляет заполненные строки и начисляет очки
 *
 * Таблица очков за одновременно удалённые строки:
 * | Строк | Очков |
 * |-------|-------|
 * | 1     | 100   |
 * | 2     | 300   |
 * | 3     | 700   |
 * | 4     | 1500  |
 *
 * @param full_info Указатель на полное состояние игры
 */
void check_full_line(FullInfo *full_info);

/**
 * @brief Возвращает текущее время в миллисекундах
 * @return Текущее время (мс) в формате unsigned long long
 */
unsigned long long current_time();

/**
 * @brief Проверяет, истёк ли таймер для автоматического падения фигуры
 *
 * Интервал падения вычисляется по формуле:
 * \f[ t_{fall} = \frac{1000}{level} \text{ (мс)} \f]
 *
 * @param full_info Указатель на полное состояние игры
 * @return true если пора опустить фигуру, false иначе
 */
bool check_shifting(FullInfo *full_info);

/**
 * @brief Выделяет динамическую двумерную матрицу n×m, инициализированную нулями
 * @param matrix Указатель на переменную типа int**, в которую запишется матрица
 * @param n Количество строк
 * @param m Количество столбцов
 */
void allocate_mem(int ***matrix, int n, int m);

/**
 * @brief Освобождает память, выделенную под двумерную матрицу
 * @param matrix Указатель на переменную типа int** с матрицей
 * @param n Количество строк (для обхода)
 */
void free_mem(int ***matrix, int n);

#endif  // BACKEND_H
