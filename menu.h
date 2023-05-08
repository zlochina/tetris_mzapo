#ifndef __MENU_H__
#define __MENU_H__

#include <stdint.h>

#include "app_structure.h"
#include "constants.h"
#include "controllers.h"
#include "lcd_chars.h"
#include "mzapo_parlcd.h"
// #include "game.h"

enum options { FIRST, SECOND, THIRD };

void draw_main_menu_template(application_t* app);

void draw_game_menu_template(application_t* app);

void update_main_menu(application_t app);

void update_game_menu(application_t app);

void print_line(application_t app, unsigned short* frame_buffer, int width,
                int offset_y, int line_height);

void print_line_speed_mode(application_t app);

void led_line_flush(application_t* app);

void set_speed(application_t* app, uint32_t speed);

void change_app_state(application_t* app, uint8_t to_state);

void change_speed_state(application_t* app);

uint32_t decrease_speed_value(uint32_t);

uint32_t increase_speed_value(uint32_t);

void change_speed_state(application_t*);

void choose_next_option(application_t* app);

void choose_previous_option(application_t* app);

void main_menu_state(application_t* app);

void game_menu_state(application_t* app);

#endif  //__MENU_H__
