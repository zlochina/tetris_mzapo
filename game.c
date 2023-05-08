#include "game.h"

#include <stdio.h>

#include "app_structure.h"
#include "mzapo_parlcd.h"
#include "utils.h"

#define LEFT_SHIFT_POS(X) 8 - X

section_t print_game_section(section_t draw_section, application_t *app,
                             char *str, unsigned short color) {
  section_t section_out;
  uint8_t line_width = 2;
  int scale = 1;
  uint32_t str_sizes = get_sizes_str(str, scale, app->font_descriptors.small);

  int x_str = draw_section.x + ((draw_section.width + (str_sizes >> 16)) >> 1);
  draw_section.x = WIDTH - draw_section.x;
  //   draw string
  draw_string(x_str, draw_section.y, str, color, scale,
              app->frame_buffers.game_frame, app->font_descriptors.small);

  // draw borders
  int offset_str = ((str_sizes & 0xffff) - line_width) >> 1;
  int start_point = HEIGHT * draw_section.x + draw_section.y + offset_str;
  // draw WEST border
  int ptr = start_point;
  for (int x = 0; x < line_width; x++) {
    for (int y = 0; y < draw_section.height; y++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += -HEIGHT - draw_section.height;
  }

  // draw NORTH border
  int half_width_without_string =
      ((draw_section.width - (str_sizes >> 16)) >> 1) - line_width;

  // Debug and only TODO delete
  if (half_width_without_string <= 0) {
    printf("ERROR\n");
  }
  start_point = ptr;
  for (int x = 0; x < half_width_without_string; x++) {
    for (int y = 0; y < line_width; y++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += -HEIGHT - line_width;
  }
  // skip string
  ptr -= (HEIGHT) * ((str_sizes >> 16) + line_width);
  for (int x = 0; x < half_width_without_string; x++) {
    for (int y = 0; y < line_width; y++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += -HEIGHT - line_width;
  }

  // draw SOUTH border
  ptr = start_point + draw_section.height - line_width;
  for (int x = 0; x < draw_section.width - line_width; x++) {
    for (int y = 0; y < line_width; y++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += -HEIGHT - line_width;
  }

  // draw EAST border
  ptr += line_width - draw_section.height;
  for (int x = 0; x < line_width; x++) {
    for (int y = 0; y < draw_section.height; y++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += -HEIGHT - draw_section.height;
  }

  section_out.x = (WIDTH - draw_section.x) + (line_width << 1);
  section_out.y = draw_section.y + (str_sizes & 0xffff);
  section_out.width = draw_section.width - 4 * line_width;
  section_out.height =
      draw_section.height - 2 * line_width - (str_sizes & 0xffff);
  return section_out;
}

void print_sections(application_t *app, unsigned short color,
                    char *tetris_section_str) {
  section_t tetris_section;
  section_t stats_section;
  section_t next_section;

  tetris_section.x = 6;
  tetris_section.y = 30;
  tetris_section.width = 208;
  tetris_section.height = 420;
  app->game.tetris_section =
      print_game_section(tetris_section, app, tetris_section_str, color);
  /*printf("Retrieved section params:\nx = %d, y = %d, width = %d, height =
     %d\n", tetris_section.x, tetris_section.y, tetris_section.width,
         tetris_section.height);
    */

  next_section.x = 218;
  next_section.y = 30;
  next_section.width = 100;
  next_section.height = 100;
  app->game.next_section =
      print_game_section(next_section, app, GAME_NEXT, color);

  stats_section.x = 218;
  stats_section.y = 240;
  stats_section.width = 100;
  stats_section.height = 80;
  app->game.stats_section =
      print_game_section(stats_section, app, GAME_STATS, color);
}

void update_stats_section(application_t *app) {
  // clean stats
  clean_section(app, app->game.stats_section, BG_COLOR);

  // print_strings
  int start_x = app->game.stats_section.x + 2;
  int start_y = app->game.stats_section.y + 10;

  // print "Score"
  int str_sizes = get_sizes_str(SCORE, 1, app->font_descriptors.small);
  draw_string(start_x + (str_sizes >> 16), start_y, SCORE, FONT_COLOR, 1,
              app->frame_buffers.game_frame, app->font_descriptors.small);

  app->frame_buffers.game_metadata.option_1_width = str_sizes >> 16;
  app->frame_buffers.game_metadata.option_1_offset_y = start_y;

  start_y += (str_sizes & 0xffff) + 20;

  // print "Score"
  str_sizes = get_sizes_str(BUILT_LINES, 1, app->font_descriptors.small);
  draw_string(start_x + (str_sizes >> 16), start_y, BUILT_LINES, FONT_COLOR, 1,
              app->frame_buffers.game_frame, app->font_descriptors.small);

  app->frame_buffers.game_metadata.option_2_width = str_sizes >> 16;
  app->frame_buffers.game_metadata.option_2_offset_y = start_y;

  // print numbers
  start_x = app->game.stats_section.x + 2 +
            app->frame_buffers.game_metadata.option_1_width;
  start_y = app->frame_buffers.game_metadata.option_1_offset_y;
  char *score = convert_int_to_str(
      calculate_score(app->game.built_lines, app->settings.speed));

  str_sizes = get_sizes_str(score, 1, app->font_descriptors.small);
  draw_string(start_x + (str_sizes >> 16), start_y, score, FONT_COLOR, 1,
              app->frame_buffers.game_frame, app->font_descriptors.small);

  char *built_lines = convert_int_to_str(app->game.built_lines);

  start_x = app->game.stats_section.x + 2 +
            app->frame_buffers.game_metadata.option_2_width;
  start_y = app->frame_buffers.game_metadata.option_2_offset_y;

  str_sizes = get_sizes_str(built_lines, 1, app->font_descriptors.small);
  draw_string(start_x + (str_sizes >> 16), start_y, built_lines, FONT_COLOR, 1,
              app->frame_buffers.game_frame, app->font_descriptors.small);

  // free strings
  free(score);
  free(built_lines);
}

void init_game_frame(application_t *app) {
  print_sections(app, FONT_COLOR, GAME_TITLE);
  update_stats_section(app);
}

void update_game_frame_to_gameover(application_t *app) {
  section_t section;
  section.x = 6;
  section.y = 30;
  section.width = 208;
  section.height = 16;
  clean_section(app, section, BG_COLOR);
  print_sections(app, RED, GAME_OVER);
  parlcd_write_frame(app->address_book.parlcd_membase,
                     app->frame_buffers.game_frame);
}

void draw_block(int8_t x, int8_t y, application_t *app, unsigned short color,
                _Bool is_next_section) {
  // check if coords are wrong
  if (x < 0 || x > 9 || y < 0 || y > 19) {
    return;
  }

  int x_new, y_new;
  // convert coords
  if (!is_next_section) {
    x_new = app->game.tetris_section.x + 20 * x + 20;
    y_new = app->game.tetris_section.y + 20 * y;
  } else {
    x_new = app->game.next_section.x + 20 * x + 30;
    y_new = app->game.next_section.y + 20 * y + 10;
  }

  int ptr = (WIDTH - x_new) * HEIGHT + y_new;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += HEIGHT - 20;
  }
}

void draw_figure(figure_position_t fig_pos, application_t app) {
  uint8_t x = fig_pos.x;
  uint8_t y = fig_pos.y;
  figure_t figure = fig_pos.figure;
  uint8_t fig_state = fig_pos.figure_state;
  for (int j = 0; j < 4; j++) {
    uint8_t cur_row = figure.fig[j + fig_state * 4];

    for (int i = x + 2; i > x - 2; i--) {
      if (cur_row & 0x1) {
        draw_block(i, y - 2 + j, &app, figure.color, 0);  // TODO may create bug
      }
      cur_row >>= 1;
      if (cur_row == 0) break;
    }
  }
  parlcd_write_frame(app.address_book.parlcd_membase,
                     app.frame_buffers.game_frame);
}

void save_figure_to_buffer(figure_position_t fig_pos, application_t *app,
                           _Bool is_next_section) {
  uint8_t x = fig_pos.x;
  uint8_t y = fig_pos.y;
  figure_t figure = fig_pos.figure;
  uint8_t fig_state = fig_pos.figure_state;

  for (int j = 0; j < 4; j++) {
    uint8_t cur_row = figure.fig[j + fig_state * 4];

    for (int i = x + 2; i > x - 2; i--) {
      if (cur_row & 0x1) {
        draw_block(i, y - 2 + j, app, figure.color,
                   is_next_section);  // TODO may create bug
      }
      cur_row >>= 1;
      if (cur_row == 0) break;
    }
  }
  parlcd_write_frame(app->address_book.parlcd_membase,
                     app->frame_buffers.game_frame);
}

// TODO delete
void test_animation(figure_t fig, application_t app) {
  figure_position_t fig_pos;
  fig_pos.x = 5;
  fig_pos.y = 5;
  fig_pos.figure = fig;
  for (int i = 0; i < fig.num_states; i++) {
    fig_pos.figure_state = i;
    draw_figure(fig_pos, app);
    sleep(2);
  }
}

void clean_section(application_t *app, section_t section,
                   unsigned short color) {
  int ptr = (WIDTH - section.width - section.x) * HEIGHT + section.y;
  for (int x = 0; x < section.width; x++) {
    for (int y = 0; y < section.height; y++) {
      app->frame_buffers.game_frame[ptr++] = color;
    }
    ptr += HEIGHT - section.height;
  }
}

// alternative main function for the PLAYTHROUGH
void game_state(application_t *app) {
  address_book_t add_book = app->address_book;
  struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 30 * 1000 * 1000};
  uint32_t actual_knobs_value = *add_book.knobs;
  cached_knobs_t old_knobs_values;

  // periphereas
  uint8_t clicks = 0;
  uint8_t cached_state = 0;
  old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
  old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
  old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  int game_clocks = 100;
  int cur_clock = 1;

  if (app->settings.continue_clicked) {
    // continue clicked
    app->settings.continue_clicked = false;
    parlcd_write_frame(add_book.parlcd_membase, app->frame_buffers.game_frame);
    draw_figure(app->game.game_field.figure_pos, *app);
  } else {
    // new game clicked
    init_game(app);
  }

  // define game_clocks
  switch (app->settings.speed) {
    case (SLOW):
      game_clocks = 13;
      break;
    case (MEDIUM):
      game_clocks = 11;
      break;
    case (FAST):
      game_clocks = 9;
      break;
    case (FASTEST):
      game_clocks = 2;
      break;
  }

  uint8_t flags = 0;

  while (true) {
    // if nothing changed go to delay
    if (actual_knobs_value == *add_book.knobs) goto delay;

    actual_knobs_value = *add_book.knobs;
    clicks = actual_knobs_value >> 24;

    if ((clicks & 0x5) & ~cached_state) {
      // top or bottom button were clicked

      // write new high score
      int new_high_score =
          calculate_score(app->game.built_lines, app->settings.speed);
      if (app->settings.high_score < new_high_score)
        app->settings.high_score = new_high_score;

      change_app_state(app, GAMEMENU);
      return;
    } else if ((clicks & 0x2) & ~cached_state) {
      // middle button clicked
      flags |= DROP_FIGURE;
    }

    cached_state = clicks;
    uint8_t actions = listen_to_knobs(actual_knobs_value, old_knobs_values);

    // figure orientation
    if (actions & 0x10) {
      // top rotation clockwise
      flags |= RIGHT_ORIENTATION;
    } else if (actions & 0x20) {
      // top rotation anti-clockwise
      flags |= LEFT_ORIENTATION;
    }

    // figure horizontal movement
    if (actions & 0x4) {
      // middle rotation clockwise
      flags |= RIGHT_MOVEMENT;
    } else if (actions & 0x8) {
      // middle rotation anti-clockwise
      flags |= LEFT_MOVEMENT;
    }

    // Update cached values
    old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
    old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
    old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  delay:
    if (app->game.game_state == GAMEOVER) {
      printf("Game Over\n");
      update_game_frame_to_gameover(app);

      sleep(5);
      change_app_state(app, MAINMENU);

      // write new high score
      int new_high_score =
          calculate_score(app->game.built_lines, app->settings.speed);
      if (app->settings.high_score < new_high_score)
        app->settings.high_score = new_high_score;

      return;
    } else if (cur_clock++ % game_clocks == 0) {
      flags = flags | FALL_A_ROW;
      cur_clock %= game_clocks;
    }

    if (flags) {
      update_state(app, flags);
      flags = 0;
    }

    // sleep delay
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
}

// TODO maybe I should move game mechanics functions to the indiviual file

void init_game(application_t *app) {
  for (int i = 0; i < SIZE; i++) {
    app->frame_buffers.game_frame[i] = BG_COLOR;
  }

  // write template
  init_game_frame(app);

  parlcd_write_frame(app->address_book.parlcd_membase,
                     app->frame_buffers.game_frame);

  // init variables
  app->game.game_state = PLAYABLE;
  app->game.built_lines = 0;

  for (int i = 0; i < 22; i++) {
    app->game.game_field.field[i] = 0x801;  // 1000 0000 0001
  }
  app->game.game_field.field[22] = 0xfff;  // 1111 1111 1111

  app->game.game_field.next_figure = get_random_figure(app->game.figure_arr);
  spawn_next_figure(app);
}

figure_t get_random_figure(figure_arr_t fig_arr) {
  uint8_t random_number = rand() % 7;

  switch (random_number) {
    case 0:
      return fig_arr.Z;
    case 1:
      return fig_arr.I;
    case 2:
      return fig_arr.J;
    case 3:
      return fig_arr.L;
    case 4:
      return fig_arr.O;
    case 5:
      return fig_arr.T;
    default:
      return fig_arr.S;
  }
}

void spawn_next_figure(application_t *app) {
  figure_position_t new_figure_pos;
  new_figure_pos.x = START_X;
  new_figure_pos.y = START_Y;
  new_figure_pos.figure = app->game.game_field.next_figure;
  new_figure_pos.figure_state = 0;
  app->game.game_field.figure_pos = new_figure_pos;
  app->game.game_field.next_figure = get_random_figure(app->game.figure_arr);

  draw_figure(new_figure_pos, *app);

  // write figure to next_section
  figure_position_t next_fig_pos;
  next_fig_pos.x = 1;
  next_fig_pos.y = 2;
  next_fig_pos.figure = app->game.game_field.next_figure;
  next_fig_pos.figure_state = 0;

  clean_section(app, app->game.next_section, BG_COLOR);
  save_figure_to_buffer(next_fig_pos, app, true);
}

void init_new_figure_pos(application_t *app, figure_position_t *new_fig_pos) {
  figure_position_t current_figure_pos = app->game.game_field.figure_pos;
  new_fig_pos->figure_state = current_figure_pos.figure_state;
  new_fig_pos->figure = current_figure_pos.figure;
  new_fig_pos->x = current_figure_pos.x;
  new_fig_pos->y = current_figure_pos.y;
}

void update_state(application_t *app, uint8_t flags) {
  figure_position_t new_figure_pos;

  if (flags & 0x1) {  // FALL_A_ROW
    // check if figure can fall down;
    init_new_figure_pos(app, &new_figure_pos);
    new_figure_pos.y += 1;

    if (is_possible_figure_position(new_figure_pos, app->game.game_field)) {
      // change y of current figure draw_figure
      app->game.game_field.figure_pos = new_figure_pos;
      draw_figure(new_figure_pos, *app);
    } else {
      save_figure_to_buffer(app->game.game_field.figure_pos, app, 0);
      update_game_field_array(app);

      if (!is_game_possible(app->game.game_field)) {
        app->game.game_state = GAMEOVER;
      }

      //  spawn next figure
      spawn_next_figure(app);
      clean_lines(app);
      update_stats_section(app);
    }
  }

  if (flags & 0x2) {  // LEFT_ORIENTATION
    // change current figure's state by going 1 up
    init_new_figure_pos(app, &new_figure_pos);

    new_figure_pos.figure_state++;
    new_figure_pos.figure_state %= new_figure_pos.figure.num_states;

    // check if figure can be rotated, if not -> do not change state
    if (is_possible_figure_position(new_figure_pos, app->game.game_field)) {
      app->game.game_field.figure_pos = new_figure_pos;
      draw_figure(new_figure_pos, *app);
    }
    // TODO but when the problem is side walls, figure should rotate freely (in
    // this case figure will be just moved a little)
    return;
  }

  if (flags & 0x4) {  // RIGHT_ORIENTATION
    // change current figure's state by going 1 down
    init_new_figure_pos(app, &new_figure_pos);

    new_figure_pos.figure_state += new_figure_pos.figure.num_states - 1;
    new_figure_pos.figure_state %= new_figure_pos.figure.num_states;
    // check if figure can be rotated, if not -> do not change state
    if (is_possible_figure_position(new_figure_pos, app->game.game_field)) {
      app->game.game_field.figure_pos = new_figure_pos;
      // draw_figure
      draw_figure(new_figure_pos, *app);
    }
  }

  if (flags & 0x8) {  // LEFT_MOVEMENT
    init_new_figure_pos(app, &new_figure_pos);

    new_figure_pos.x -= 1;
    // check if it can go left, if not do not change anything
    if (is_possible_figure_position(new_figure_pos, app->game.game_field)) {
      app->game.game_field.figure_pos = new_figure_pos;
      // draw_figure
      draw_figure(new_figure_pos, *app);
    }
  }

  if (flags & 0x10) {  // RIGHT_MOVEMENT
    init_new_figure_pos(app, &new_figure_pos);

    new_figure_pos.x += 1;
    // check if it can go right, if not do not change anything
    if (is_possible_figure_position(new_figure_pos, app->game.game_field)) {
      app->game.game_field.figure_pos = new_figure_pos;
      // draw_figure
      draw_figure(new_figure_pos, *app);
    }
  }

  if (flags & 0x20) {  // DROP_FIGURE
    // go to some kind of loop, where we change the y of figure and checking if
    // it could be placed like that

    init_new_figure_pos(app, &new_figure_pos);

    while (is_possible_figure_position(new_figure_pos, app->game.game_field)) {
      new_figure_pos.y += 1;
    }
    new_figure_pos.y -= 1;

    app->game.game_field.figure_pos = new_figure_pos;
    // and update state so it could spawn new figure
    update_state(app, FALL_A_ROW);
  }
}

_Bool is_possible_figure_position(figure_position_t new_fig_pos,
                                  game_field_t game_field) {
  int left_shift = LEFT_SHIFT_POS(new_fig_pos.x);
  int start_row = new_fig_pos.y;
  uint32_t cur_fig_row;

  for (int i = 0; i < 4; i++) {
    if (start_row + i < 0) continue;
    uint32_t cur_field_row = game_field.field[start_row + i];
    if (left_shift >= 0) {
      cur_fig_row = new_fig_pos.figure.fig[new_fig_pos.figure_state * 4 + i]
                    << left_shift;
    } else {
      cur_fig_row = new_fig_pos.figure.fig[new_fig_pos.figure_state * 4 + i] >>
                    -left_shift;
    }

    if (cur_fig_row & cur_field_row) {
      // there is intersection
      return false;
    }
  }

  return true;
}

_Bool is_game_possible(game_field_t game_field) {
  // 0x7fe is mask for 0111 1111 1110
  if (game_field.field[1] & 0x7fe) return false;
  return true;
}

void clean_lines(application_t *app) {
  // go through lines and if there is a full line
  for (int i = 2; i < 22; i++) {
    uint16_t cur_line = app->game.game_field.field[i];

    if (cur_line == 0xfff) {  // FULL line
      // shift all upper lines by 1 down
      shift_game_field_array(app, i - 2);

      // increment lines value
      app->game.built_lines++;

      // buffer: clean section with y = this line,
      section_t section;
      section.x = app->game.tetris_section.x;
      section.y = app->game.tetris_section.y + 20 * (i - 2);
      section.width = app->game.tetris_section.width;
      section.height = app->game.tetris_section.height / 20;
      clean_section(app, section, BG_COLOR);

      //  move upper part of buffer by the height of one line
      if (i - 2 > 0) shift_game_frame_buffer(app, i - 2);

      // clean section with y = 0;
    }
  }
}

void shift_game_field_array(application_t *app, uint8_t full_line_pos) {
  for (int i = full_line_pos; i >= 0; i--) {
    app->game.game_field.field[i + 2] = app->game.game_field.field[i + 1];
  }
}

void shift_game_frame_buffer(application_t *app, uint8_t full_line_pos) {
  section_t tetris_section = app->game.tetris_section;
  int block_height = (tetris_section.height / 20);
  int offset_y_section = full_line_pos * block_height + block_height;
  int offset_y = tetris_section.y + offset_y_section - 1;
  int ptr =
      offset_y + (WIDTH - tetris_section.width - tetris_section.x) * HEIGHT;

  for (int x = 0; x < tetris_section.width; x++) {
    for (int y = 0; y < offset_y_section - 16; y++) {
      app->frame_buffers.game_frame[ptr] =
          app->frame_buffers.game_frame[ptr - block_height];
      ptr--;
    }
    ptr += HEIGHT + offset_y_section - 16;
  }
}

void update_game_field_array(application_t *app) {
  figure_position_t cur_fig_pos = app->game.game_field.figure_pos;
  int left_shift = LEFT_SHIFT_POS(cur_fig_pos.x);

  int start_row = cur_fig_pos.y;
  uint16_t cur_fig_row;

  for (int i = 0; i < 4; i++) {
    uint16_t cur_field_row = app->game.game_field.field[start_row + i];

    if (left_shift >= 0) {
      cur_fig_row = cur_fig_pos.figure.fig[cur_fig_pos.figure_state * 4 + i]
                    << left_shift;
    } else {
      cur_fig_row = cur_fig_pos.figure.fig[cur_fig_pos.figure_state * 4 + i] >>
                    -left_shift;
    }

    app->game.game_field.field[start_row + i] = cur_field_row | cur_fig_row;
  }
}
