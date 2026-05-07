#include "tetris_lib.h"

/* Хранит единый экземпляр состояния, общий для backend, FSM и GUI. */
FullInfo *get_current_state() {
  static FullInfo full_info = {0};
  return &full_info;
}

/* Сохраняет последнее действие пользователя до следующего шага FSM. */
void userInput(UserAction_t action, bool hold) {
  FullInfo *full_info = get_current_state();
  full_info->button_pressed = hold;
  full_info->user_action = action;
}

GameInfo_t updateCurrentState() {
  FullInfo *full_info = get_current_state();

  return full_info->game_info;
}
