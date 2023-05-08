#include "app_structure.h"
#include "constants.h"
#include "mzapo_parlcd.h"

// defines of starter coords
#define START_X 4
#define START_Y -2

void draw_block(int8_t x, int8_t y, application_t *app, unsigned short color,
                _Bool is_next_section);

void draw_figure(figure_position_t fig_pos, application_t app);

void save_figure_to_buffer(figure_position_t fig_pos, application_t *app,
                           _Bool is_next_section);

void clean_section(application_t *app, section_t section, unsigned short color);

figure_t get_random_figure(figure_arr_t fig_arr);

void init_new_figure_pos(application_t *app, figure_position_t *new_fig_pos);

_Bool is_possible_figure_position(figure_position_t new_fig_pos,
                                  game_field_t game_field);

_Bool is_game_possible(game_field_t game_field);

void shift_game_field_array(application_t *app, uint8_t full_line_pos);

void update_game_field_array(application_t *app);

void clean_lines(application_t *app);

void shift_game_frame_buffer(application_t *app, uint8_t full_line_pos);

void spawn_next_figure(application_t *app);
