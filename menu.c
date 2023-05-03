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
#include <time.h>

uint32_t increase_speed_value(uint32_t speed) {
  if (speed == FASTEST) return speed;
  if (speed == FAST) return FASTEST;
  if (speed == MEDIUM) return FAST;
  return MEDIUM;
}

uint32_t decrease_speed_value(uint32_t speed) {
  if (speed == SLOW) return speed;
  if (speed == MEDIUM) return SLOW;
  if (speed == FAST) return MEDIUM;
  return FAST;
}

void led_line_flush(application_t app) { *(app.address_book.led_line) = 0; }

void set_speed(application_t app, uint32_t speed) {
  *(app.address_book.led_line) = speed;
  app.settings.speed = speed;
}

void change_app_state(application_t app, uint8_t to_state) {
  app.settings.app_state = to_state;
}

void change_speed_state(application_t app) {
  address_book_t add_book = app.address_book;
  struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 100 * 1000 * 1000};
  uint32_t actual_knobs_value = *add_book.knobs;
  uint32_t led_line_val = *add_book.led_line;

  uint8_t clicks = 0;
  uint8_t cached_state = 0;
  uint8_t top_button_cached_value = (actual_knobs_value >> 16) & 0xff;
  uint8_t middle_button_cached_value = (actual_knobs_value >> 8) & 0xff;
  uint8_t bottom_button_cached_value = actual_knobs_value & 0xff;

  while (true) {
    actual_knobs_value = *add_book.knobs;
    clicks = actual_knobs_value >> 24;

    // any button was clicked -> exit SETSPEED state
    if ((clicks & 0x7) & ~cached_state) {
      change_app_state(app, MAINMENU);
      return;
    }
    cached_state = clicks;

    // threshold for checking the smer is 128
    uint8_t new_top_value = (actual_knobs_value >> 16) & 0xff;
    uint8_t new_mid_value = (actual_knobs_value >> 8) & 0xff;
    uint8_t new_bot_value = actual_knobs_value & 0xff;
    int sub_top = new_top_value - top_button_cached_value;
    int sub_mid = new_mid_value - middle_button_cached_value;
    int sub_bot = new_bot_value - bottom_button_cached_value;

    // middle button rotation
    if (sub_mid == 0) {
      // not changed
    } else if (sub_mid > 0 && sub_mid < 128 || sub_mid < -128) {
      // turning right
      led_line_val = increase_speed_value(led_line_val);
    } else {
      // turning left
      led_line_val = decrease_speed_value(led_line_val);
    }

    // bottom button rotation
    if (sub_bot == 0) {
      // not changed
    } else if (sub_bot > 0 && sub_bot < 128 || sub_bot < -128) {
      // turning right
      led_line_val = increase_speed_value(led_line_val);
    } else {
      // turning left
      led_line_val = decrease_speed_value(led_line_val);
    }

    top_button_cached_value = new_top_value;
    middle_button_cached_value = new_mid_value;
    bottom_button_cached_value = new_bot_value;

    set_speed(app, led_line_val);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
}

void main_menu_state(application_t app) {
  address_book_t add_book = app.address_book;
  struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 100 * 1000 * 1000};
  uint32_t actual_knobs_value = *add_book.knobs;

  uint8_t clicks = 0;
  uint8_t cached_state = 0;
  uint8_t top_button_cached_value = (actual_knobs_value >> 16) & 0xff;
  uint8_t middle_button_cached_value = (actual_knobs_value >> 8) & 0xff;
  uint8_t bottom_button_cached_value = actual_knobs_value & 0xff;

  while (true) {
    // Listeners
  }
}
