#include <stdbool.h>
#include <stdint.h>

#include "constants.h"

enum states { MAINMENU = 10, GAMEMENU, GAME, SETSPEED };

typedef struct {
  uint8_t app_state;
  uint32_t speed;
  uint8_t current_option;
} game_settings_t;

typedef struct {
  uint32_t score;
  uint32_t built_lines;
  _Bool **game_field;
} game_t;

typedef struct {
  unsigned char game_menu_frame[SIZE];
  unsigned char main_menu_frame[SIZE];
  unsigned char game_frame[SIZE];
} frame_buffers_t;

typedef struct {
  unsigned char *parlcd_membase;
  volatile uint32_t *led_line;
  volatile uint32_t *knobs;
} address_book_t;

typedef struct {
  game_settings_t settings;
  game_t game;
  frame_buffers_t frame_buffers;
  address_book_t address_book;
} application_t;
