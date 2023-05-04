/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  include your name there and license for distribution.

  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.

 *******************************************************************/

#include <string.h>
#define _POSIX_C_SOURCE 200112L

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "constants.h"
#include "converters.h"
#include "game.h"
#include "lcd_chars.h"
#include "menu.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "utils.h"

#define GET_RIGHT_X(x) WIDTH - x;

int main(int argc, char *argv[]) {
  // @INIT
  printf(INIT_MESSAGE);

  unsigned char *mem_base;
  application_t app;
  // settings
  app.settings.app_state = MAINMENU;
  app.settings.speed = SLOW;
  app.settings.current_option = FIRST;

  // game
  // app.game.

  // frame_buffers
  memset(app.frame_buffers.game_frame, 0, sizeof(unsigned short) * SIZE);
  memset(app.frame_buffers.game_menu_frame, 0, sizeof(unsigned short) * SIZE);
  memset(app.frame_buffers.main_menu_frame, 0, sizeof(unsigned short) * SIZE);

  // address book
  app.address_book.parlcd_membase =
      map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

  // check if mapping was failed
  if (app.address_book.parlcd_membase == NULL || mem_base == NULL) exit(1);

  app.address_book.led_line =
      (volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o);
  app.address_book.knobs =
      (volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

  // font descriptors
  app.font_descriptors.small = &font_rom8x16;
  app.font_descriptors.big = &font_winFreeSystem14x16;

  // init lcd display
  parlcd_hx8357_init(app.address_book.parlcd_membase);

  // LETSSS GOOO - Application running
  // unsigned short frame_buffer[320 * 480] = {0};
  parlcd_flush(app.address_book.parlcd_membase);
  led_line_flush(&app);
  printf("FLUSHED\n");
  sleep(1);
  set_speed(&app, SLOW);

  /*
  // TODO DEBUG delete
  // are vertical
  // TEST 1 COMPLETE
  int ptr = 0;
  unsigned short color;
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      int x_r = GET_RIGHT_X(x);
      if (y > 460 && x_r < 80)
        color = CYAN;
      else if (y > 460 && x_r > 240)
        color = PINK;
      else if (y > 440 && x_r < 80)
        color = ORANGE;
      else if (y > 440 && x_r > 240)
        color = SUNNY;
      else if (y > 460 && (x_r > 120 || x_r < 180))
        color = ACID;
      else if (y > 400 && x_r > 240) {
        color = LIGHT_PINK;
      } else if (y > 400 && x_r < 80)
        color = WHITE;
      else
        color = BG_COLOR;
      frame_buffer[ptr++] = color;
    }
  }

  // TEST 4 should check how chars are shown
  // draw_char(100, 100, 'a', FONT_COLOR, 2, frame_buffer, fdes_sm);
  parlcd_write_frame(app.address_book.parlcd_membase, frame_buffer);
  // write_to_file(frame_buffer);
  printf("Written to file\n");
  */
  printf("Entering main menu state...\n");
  main_menu_state(&app);
  printf("Exiting main menu state...\n");
  sleep(10);
  goto clean;

  // TEST 5
  printf("Test SETSPEED Mode\n");

  change_app_state(&app, SETSPEED);
  change_speed_state(&app);
  printf("Test SETSPEED Over\n");

  /*
    printf("Now sleeping\n");
    sleep(5);
    // flushing lcd
    parlcd_flush(parlcd_mem_base);

    printf("Test led line\n");

    // TEST 2 Led line PASSED
    // I think there will be 4 speeds: indicator will be 8 leds, 16 leds, 24
    leds
    // and 32 leds
    // TODO move to init part
    led_line =
    knobs =

    uint32_t led_line_val = SLOW;
    *(led_line) = led_line_val;

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 100 * 1000 * 1000};
    // TEST 3 knobs on led_line
    uint32_t actual_knobs_value = *knobs;

    uint8_t clicks = 0;
    uint8_t cached_state = 0;
    uint8_t top_button_cached_value = (actual_knobs_value >> 16) & 0xff;
    uint8_t middle_button_cached_value = (actual_knobs_value >> 8) & 0xff;
    uint8_t bottom_button_cached_value = actual_knobs_value & 0xff;
    while (true) {
      actual_knobs_value = *knobs;
      // printf("Value is %#X\n", *knobs);
      clicks = actual_knobs_value >> 24;

      // CLICKS PASSED
      if ((clicks & 0x4) & ~cached_state) {
        printf("Top button clicked\n");
      }
      if ((clicks & 0x2) & ~cached_state) {
        printf("Middle button clicked\n");
      }
      if ((clicks & 0x1) & ~cached_state) {
        printf("Bottom button clicked\n");
      }
      cached_state = clicks;
      // threshold for checking the smer is 128
      uint8_t new_mid_value = (actual_knobs_value >> 8) & 0xff;
      int sub = new_mid_value - middle_button_cached_value;
      if (sub == 0) {
        // not changed
      } else if (sub > 0 && sub < 128 || sub < -128) {
        // turning right
        printf("RIGHT\n");
        led_line_val = increase_speed_value(led_line_val);

      } else {
        // turning left
        printf("LEFT\n");
        led_line_val = decrease_speed_value(led_line_val);
      }

      middle_button_cached_value = new_mid_value;

      *(led_line) = led_line_val;
      clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
  */
  //
  /* Explanation of the flow
   * So we've got several main states for sure: INIT, PLAYTHROUGH, EXIT
   *    INIT is expected to set some variables and also initiate first frame of
   * the programm, PLAYTHROUGH will be as some while true loop, which will
   * constantly check states of the physical indicators So if we wanna indicate
   * changes in physical indicators states, we're gonna have set variables for
   * them, and compare their current value to the stored one function that
   * checks any of indicators' changes -> will return some boolean array, by
   * which i'll get to know which values have been changed depending on the
   * previous outcome values will be passed to @action functions (I expect there
   * to be some )
   *
   *    EXIT will set the lcd display to black screen and clear some dynamic
   * memory if used, Also parameter Score will be saved to some file.
   *
   *    Ideas: "New High score!" display,
   */

  // @EXIT
  // Cleaning
clean:
  led_line_flush(&app);
  parlcd_flush(app.address_book.parlcd_membase);

  printf(OUTPUT_MESSAGE);
  return 0;
}
