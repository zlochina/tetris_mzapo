#include <stdint.h>

#include "app_structure.h"
#include "constants.h"
#include "controllers.h"
// #include "game.h"

enum options { FIRST, SECOND, THIRD };

// TODO update coords to great layout
#define MAIN_TITLE_Y 20
#define NEW_GAME_Y 60

void draw_main_menu_template(unsigned char* frame_buffer);

void draw_game_menu_template(unsigned char* frame_buffer);

void update_main_menu(unsigned char* frame_buffer, uint8_t next_option);

void update_game_menu(unsigned char* frame_buffer, uint8_t next_option);

void led_line_flush(application_t app);

void set_speed(application_t app, uint32_t speed);

void change_app_state(application_t app, uint8_t to_state);

uint32_t decrease_speed_value(uint32_t);

uint32_t increase_speed_value(uint32_t);

void change_speed_state(application_t);
