#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "app_structure.h"
#include "constants.h"
#include "controllers.h"
#include "lcd_chars.h"
#include "menu.h"

// defines of flags for the next function
#define FALL_A_ROW 1
#define LEFT_ORIENTATION 1 << 1
#define RIGHT_ORIENTATION 1 << 2
#define LEFT_MOVEMENT 1 << 3
#define RIGHT_MOVEMENT 1 << 4
#define DROP_FIGURE 1 << 5

// defines of starter coords
#define START_X 4
#define START_Y -2
/* function receives next flags:
 * RIGHT_MOVEMENT, LEFT_MOVEMENT, RIGHT_ORIENTATION, LEFT_ORIENTATION,
 * FALL_A_ROW update state of the game window
 */
void update_state(application_t *app, uint8_t flags);

/*
 * Function prints to buffer a so-called "beautified frame" for whatever purpose
 * returns section_t object which indicates where you could draw inside of the
 * "frame", to not cross the borders
 */
section_t print_game_section(section_t draw_section, application_t *app,
                             char *str, unsigned short color);

void print_sections(application_t *app, unsigned short color,
                    char *tetris_section_str);

void clean_section(application_t *app, section_t section, unsigned short color);

void game_state(application_t *app);

void init_game(application_t *app);

figure_t get_random_figure(figure_arr_t fig_arr);

void spawn_next_figure(application_t *app);

_Bool is_possible_figure_position(figure_position_t new_fig_pos,
                                  game_field_t game_field);

_Bool is_game_possible(game_field_t game_field);

void update_game_field_array(application_t *app);
