/*
 * @author: zlochvla (Vladyslav Zlochevskyi)
 * This file is responsible for creating and manipulating menu states
 * Take a notice that there are duplicates of implementation of knobs'
 * listeners, The reason why they are not integrated as individual modules is
 * that calling potential listener functions could take too much resources, so
 * in order for application to be faster they are structured like that
 */
#include "menu.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

void draw_main_menu_template(application_t *app) {
  write_frame_bakcground(app->frame_buffers.main_menu_frame);

  // print strings with central allignment
  int offset_y = 40;
  uint32_t str_sizes =
      get_sizes_str(MAIN_MENU_TITLE, 6, app->font_descriptors.big);
  draw_string(get_str_start(str_sizes >> 16), offset_y, MAIN_MENU_TITLE,
              FONT_COLOR, 6, app->frame_buffers.main_menu_frame,
              app->font_descriptors.big);
  offset_y += (str_sizes & 0xffff) + 20;

  // 2nd string
  str_sizes = get_sizes_str(CURRENT_HIGH_SCORE, 1, app->font_descriptors.small);
  draw_string(get_str_start(str_sizes >> 16), offset_y, CURRENT_HIGH_SCORE,
              FONT_COLOR, 1, app->frame_buffers.main_menu_frame,
              app->font_descriptors.small);
  offset_y += (str_sizes & 0xffff) + 30;

  // 3rd string
  str_sizes = get_sizes_str(MAIN_MENU_NEW_GAME, 2, app->font_descriptors.big);
  draw_string(get_str_start(str_sizes >> 16), offset_y, MAIN_MENU_NEW_GAME,
              FONT_COLOR, 2, app->frame_buffers.main_menu_frame,
              app->font_descriptors.big);
  offset_y += (str_sizes & 0xffff) + 10;

  app->frame_buffers.main_menu_metadata.option_1_offset_y = offset_y - 3;
  app->frame_buffers.main_menu_metadata.option_1_width = str_sizes >> 16;
  offset_y += 10;

  // 4th string
  str_sizes = get_sizes_str(MAIN_MENU_SET_SPEED, 2, app->font_descriptors.big);
  draw_string(get_str_start(str_sizes >> 16), offset_y, MAIN_MENU_SET_SPEED,
              FONT_COLOR, 2, app->frame_buffers.main_menu_frame,
              app->font_descriptors.big);
  offset_y += (str_sizes & 0xffff) + 10;

  app->frame_buffers.main_menu_metadata.option_2_offset_y = offset_y - 3;
  app->frame_buffers.main_menu_metadata.option_2_width = str_sizes >> 16;
  offset_y += 10;

  // 5th string
  str_sizes = get_sizes_str(MAIN_MENU_EXIT, 2, app->font_descriptors.big);
  draw_string(get_str_start(str_sizes >> 16), offset_y, MAIN_MENU_EXIT,
              FONT_COLOR, 2, app->frame_buffers.main_menu_frame,
              app->font_descriptors.big);
  offset_y += (str_sizes & 0xffff) + 10;

  app->frame_buffers.main_menu_metadata.option_3_offset_y = offset_y - 3;
  app->frame_buffers.main_menu_metadata.option_3_width = str_sizes >> 16;
}

void draw_game_menu_template(application_t *app) {
  write_frame_bakcground(app->frame_buffers.game_menu_frame);

  font_descriptor_t *fdes_tmp = app->font_descriptors.big;
  int offset_y = 40;
  int offset_y_additional = 0;
  int scale = 1;
  int num_strings = 4;
  char *str_array[] = {GAME_MENU_TITLE, GAME_MENU_CONTINUE, GAME_MENU_RESTART,
                       GAME_MENU_QUIT};
  // print strings with central allignment
  for (int i = 0; i < num_strings; i++) {
    char *str_tmp = str_array[i];

    // init some values
    switch (i) {
        // fdes_tmp is constant here
      case (0):
        // Title
        scale = 4;
        offset_y_additional = 60;
        break;
      case (1):
        // non-Title
        scale = 2;
        offset_y_additional = 10;
        break;
    }

    // draw string_tmp
    uint32_t str_sizes = get_sizes_str(str_tmp, scale, fdes_tmp);
    draw_string(get_str_start(str_sizes >> 16), offset_y, str_tmp, FONT_COLOR,
                scale, app->frame_buffers.game_menu_frame, fdes_tmp);
    offset_y += (str_sizes & 0xffff) + offset_y_additional;

    // write metadata
    switch (i) {
      case (1):
        app->frame_buffers.game_menu_metadata.option_1_offset_y = offset_y - 3;
        app->frame_buffers.game_menu_metadata.option_1_width = str_sizes >> 16;
        offset_y += 10;
        break;
      case (2):
        app->frame_buffers.game_menu_metadata.option_2_offset_y = offset_y - 3;
        app->frame_buffers.game_menu_metadata.option_2_width = str_sizes >> 16;
        offset_y += 10;
        break;
      case (3):
        app->frame_buffers.game_menu_metadata.option_3_offset_y = offset_y - 3;
        app->frame_buffers.game_menu_metadata.option_3_width = str_sizes >> 16;
        break;
    }
  }
}

void update_main_menu(application_t app) {
  frame_metadata_t metadata = app.frame_buffers.main_menu_metadata;
  int width, offset_y;
  switch (app.settings.current_option) {
    case FIRST:
      width = metadata.option_1_width;
      offset_y = metadata.option_1_offset_y;
      break;
    case SECOND:
      width = metadata.option_2_width;
      offset_y = metadata.option_2_offset_y;
      break;
    case THIRD:
      width = metadata.option_3_width;
      offset_y = metadata.option_3_offset_y;
      break;
    default:
      return;
  }

  // print current high score
  char *high_score = convert_int_to_str(app.settings.high_score);
  int str_sizes = get_sizes_str(high_score, 1, app.font_descriptors.small);
  draw_string(get_str_start(str_sizes >> 16),
              app.frame_buffers.main_menu_metadata.option_1_offset_y - 68,
              high_score, FONT_COLOR, 1, app.frame_buffers.main_menu_frame,
              app.font_descriptors.small);

  int line_height = 4;
  print_line(app, app.frame_buffers.main_menu_frame, width, offset_y,
             line_height);
}

void update_game_menu(application_t app) {
  frame_metadata_t metadata = app.frame_buffers.game_menu_metadata;
  int width, offset_y;
  int line_height = 4;
  switch (app.settings.current_option) {
    case FIRST:
      width = metadata.option_1_width;
      offset_y = metadata.option_1_offset_y;
      break;
    case SECOND:
      width = metadata.option_2_width;
      offset_y = metadata.option_2_offset_y;
      break;
    case THIRD:
      width = metadata.option_3_width;
      offset_y = metadata.option_3_offset_y;
      break;
    default:
      return;
  }

  print_line(app, app.frame_buffers.game_menu_frame, width, offset_y,
             line_height);
}

void print_line(application_t app, unsigned short *frame_buffer, int width,
                int offset_y, int line_height) {
  int start_point = (WIDTH - get_str_start(width)) * HEIGHT + offset_y;
  for (int x = 0; x < line_height; x++) {
    for (int y = 0; y < width; y++) {
      int coord = start_point + y * HEIGHT + x;
      frame_buffer[coord] = FONT_COLOR;
    }
  }
  parlcd_write_frame(app.address_book.parlcd_membase, frame_buffer);
}

void print_line_speed_mode(application_t app) {
  print_line(app, app.frame_buffers.main_menu_frame,
             app.frame_buffers.main_menu_metadata.option_2_width,
             app.frame_buffers.main_menu_metadata.option_2_offset_y, 8);
}

uint32_t increase_speed_value(uint32_t speed) {
  switch (speed) {
    case FASTEST:
      return speed;
    case FAST:
      return FASTEST;
    case MEDIUM:
      return FAST;
    default:
      return MEDIUM;
  }
}

uint32_t decrease_speed_value(uint32_t speed) {
  switch (speed) {
    case SLOW:
      return speed;
    case MEDIUM:
      return SLOW;
    case FAST:
      return MEDIUM;
    default:
      return FAST;
  }
}

void led_line_flush(application_t *app) { *(app->address_book.led_line) = 0; }

void set_speed(application_t *app, uint32_t speed) {
  *(app->address_book.led_line) = speed;
  app->settings.speed = speed;
}

void change_app_state(application_t *app, uint8_t to_state) {
  app->settings.app_state = to_state;
}

void change_speed_state(application_t *app) {
  address_book_t add_book = app->address_book;
  struct timespec loop_delay = create_delay(100);
  uint32_t actual_knobs_value = *add_book.knobs;
  uint32_t led_line_val = *add_book.led_line;
  cached_knobs_t old_knobs_values;

  uint8_t clicks = 0;
  uint8_t cached_state = 0;
  old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
  old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
  old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  while (true) {
    // if nothing changed go to delay
    if (actual_knobs_value == *add_book.knobs) goto delay;

    actual_knobs_value = *add_book.knobs;
    clicks = actual_knobs_value >> 24;

    // any button was clicked -> exit SETSPEED state
    if ((clicks & 0x7) & ~cached_state) {
      change_app_state(app, MAINMENU);
      return;
    }
    cached_state = clicks;
    uint8_t actions = listen_to_knobs(actual_knobs_value, old_knobs_values);

    if (actions & 0x15) {
      // turned clockwise
      led_line_val = increase_speed_value(led_line_val);
    } else if (actions & 0x2a) {
      // turned anti-clockwise
      led_line_val = decrease_speed_value(led_line_val);
    }

    // Update cached values
    old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
    old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
    old_knobs_values.bottom_button = actual_knobs_value & 0xff;

    set_speed(app, led_line_val);
  delay:
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
}

void main_menu_state(application_t *app) {
  address_book_t add_book = app->address_book;
  struct timespec loop_delay = create_delay(100);
  uint32_t actual_knobs_value = *add_book.knobs;
  cached_knobs_t old_knobs_values;

  uint8_t clicks = 0;
  uint8_t cached_state = 0;
  old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
  old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
  old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  // create frame buffer
  if (app->frame_buffers.main_menu_frame[0] == 0) draw_main_menu_template(app);

  update_main_menu(*app);
  while (true) {
    // if nothing changed go to delay
    if (actual_knobs_value == *add_book.knobs) goto delay;

    actual_knobs_value = *add_book.knobs;
    clicks = actual_knobs_value >> 24;

    // any button was clicked -> Proceed according to current_option
    if ((clicks & 0x7) & ~cached_state) {
      switch (app->settings.current_option) {
        case FIRST:
          // "New Game" was clicked
          change_app_state(app, GAME);
          return;
        case SECOND:
          // "Set Speed" was clicked
          change_app_state(app, SETSPEED);
          print_line_speed_mode(*app);
          return;
        case THIRD:
          // "Exit" was clicked
          change_app_state(app, EXIT);
          return;
      }
    }
    cached_state = clicks;
    uint8_t actions = listen_to_knobs(actual_knobs_value, old_knobs_values);

    if (actions & 0x15) {
      // turned clockwise
      choose_next_option(app);
    } else if (actions & 0x2a) {
      // turned anti-clockwise
      choose_previous_option(app);
    }
    update_main_menu(*app);

    // Update cached values
    old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
    old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
    old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  delay:
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
}

void game_menu_state(application_t *app) {
  address_book_t add_book = app->address_book;
  struct timespec loop_delay = create_delay(100);
  uint32_t actual_knobs_value = *add_book.knobs;
  cached_knobs_t old_knobs_values;

  uint8_t clicks = 0;
  uint8_t cached_state = 0;
  old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
  old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
  old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  // create frame buffer
  if (app->frame_buffers.game_menu_frame[0] == 0) draw_game_menu_template(app);

  update_game_menu(*app);
  while (true) {
    // if nothing changed go to delay
    if (actual_knobs_value == *add_book.knobs) goto delay;

    actual_knobs_value = *add_book.knobs;
    clicks = actual_knobs_value >> 24;

    // any button was clicked -> Proceed according to current_option
    if ((clicks & 0x7) & ~cached_state) {
      switch (app->settings.current_option) {
        case FIRST:
          // "Continue" was clicked
          change_app_state(app, GAME);
          app->settings.continue_clicked = true;
          return;
        case SECOND:
          // "Restart" was clicked
          change_app_state(app, GAME);
          return;
        case THIRD:
          // "Quit to Title" was clicked
          change_app_state(app, MAINMENU);
          app->settings.current_option = FIRST;
          return;
      }
    }
    cached_state = clicks;
    uint8_t actions = listen_to_knobs(actual_knobs_value, old_knobs_values);

    if (actions & 0x15) {
      // turned clockwise
      choose_next_option(app);
    } else if (actions & 0x2a) {
      // turned anti-clockwise
      choose_previous_option(app);
    }
    update_game_menu(*app);

    // Update cached values
    old_knobs_values.top_button = (actual_knobs_value >> 16) & 0xff;
    old_knobs_values.middle_button = (actual_knobs_value >> 8) & 0xff;
    old_knobs_values.bottom_button = actual_knobs_value & 0xff;

  delay:
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
}

void choose_next_option(application_t *app) {
  switch (app->settings.current_option) {
    case FIRST:
      app->settings.current_option = SECOND;
      break;
    default:
      app->settings.current_option = THIRD;
  }
}

void choose_previous_option(application_t *app) {
  switch (app->settings.current_option) {
    case THIRD:
      app->settings.current_option = SECOND;
      break;
    default:
      app->settings.current_option = FIRST;
  }
}
