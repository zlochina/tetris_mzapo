#include "game_mechanics.h"

#define LEFT_SHIFT_POS(X) 8 - X

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
        draw_block(i, y - 2 + j, &app, figure.color, 0);
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
        draw_block(i, y - 2 + j, app, figure.color, is_next_section);
      }
      cur_row >>= 1;
      if (cur_row == 0) break;
    }
  }
  parlcd_write_frame(app->address_book.parlcd_membase,
                     app->frame_buffers.game_frame);
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

void init_new_figure_pos(application_t *app, figure_position_t *new_fig_pos) {
  figure_position_t current_figure_pos = app->game.game_field.figure_pos;
  new_fig_pos->figure_state = current_figure_pos.figure_state;
  new_fig_pos->figure = current_figure_pos.figure;
  new_fig_pos->x = current_figure_pos.x;
  new_fig_pos->y = current_figure_pos.y;
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
