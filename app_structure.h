#ifndef __APP_STRUCTURE_H__
#define __APP_STRUCTURE_H__
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "figures.h"
#include "font_types.h"

enum states { MAINMENU = 10, GAMEMENU, GAME, SETSPEED, EXIT };
enum gamestate { PLAYABLE = 20, GAMEOVER, PAUSED };

typedef struct {
  uint8_t app_state;
  uint32_t speed;
  uint8_t current_option;
  _Bool continue_clicked;
  uint32_t high_score;
} game_settings_t;

typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
} section_t;

typedef struct {
  int8_t x;
  int8_t y;
  uint8_t figure_state;
  figure_t figure;
} figure_position_t;

typedef struct {
  uint16_t field[23];  // only for computation, colors are in buffer
  figure_position_t figure_pos;
  figure_t next_figure;  // last 2 variables are saved only just for situation,
                         // where user paused game
} game_field_t;

typedef struct {
  uint32_t built_lines;
  section_t tetris_section;
  section_t next_section;
  section_t stats_section;
  game_field_t game_field;
  figure_arr_t figure_arr;
  uint8_t game_state;
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
  frame_metadata_t game_metadata;
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

#endif  //__APP_STRUCTURE_H__
