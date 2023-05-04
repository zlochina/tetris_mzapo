#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "font_types.h"

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
  uint16_t option_1_width;
  uint16_t option_1_offset_y;
  uint16_t option_2_width;
  uint16_t option_2_offset_y;
  uint16_t option_3_width;
  uint16_t option_3_offset_y;
} frame_metadata_t;

typedef struct {
  unsigned short game_menu_frame[SIZE];
  frame_metadata_t game_menu_metadata;
  unsigned short main_menu_frame[SIZE];
  frame_metadata_t main_menu_metadata;
  unsigned short game_frame[SIZE];
} frame_buffers_t;

typedef struct {
  unsigned char *parlcd_membase;
  volatile uint32_t *led_line;
  volatile uint32_t *knobs;
} address_book_t;

typedef struct {
  font_descriptor_t *big;
  font_descriptor_t *small;
} font_des_t;

typedef struct {
  game_settings_t settings;
  game_t game;
  frame_buffers_t frame_buffers;
  address_book_t address_book;
  font_des_t font_descriptors;
} application_t;
