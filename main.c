/*******************************************************************
  game of tetris
  @author: Vladyslav Zlochevskyi

 *******************************************************************/

#include <string.h>
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "figures.h"
#include "game.h"
#include "menu.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#define GET_RIGHT_X(x) WIDTH - x;

/*
 * Function flushing lcd display & led line
 */
void clean(application_t app);

/*
 * prints "Killroy was here"
 */
void print_meme(application_t app);

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
int main(int argc, char *argv[]) {
  // @INIT
  printf(INIT_MESSAGE);

  unsigned char *mem_base;
  application_t app;
  // settings
  app.settings.app_state = GAME;
  app.settings.speed = FASTEST;
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

  // init figures
  app.game.figure_arr = init_figures();

  // init lcd display
  parlcd_hx8357_init(app.address_book.parlcd_membase);

  // init random seed
  srand(time(NULL));

  // LETSSS GOOO - Application running @PLAYTHROUGH
  // preprocess app
  clean(app);
  set_speed(&app, app.settings.speed);
  sleep(1);
  // print_meme(app);

  _Bool exit_requested = false;
  // main flow
  while (!exit_requested) {
    switch (app.settings.app_state) {
      case (MAINMENU):
        printf("Entering main menu state...\n");
        main_menu_state(&app);
        printf("Exiting main menu state...\n");
        break;
      case (SETSPEED):
        printf("Entering SETSPEED state...\n");
        change_speed_state(&app);
        printf("Exiting SETSPEED state...\n");
        break;
      case (GAME):
        printf("Entering game state...\n");
        // TODO for now just exiting
        game_state(&app);
        printf("Exiting game state...\n");
        break;
      case (GAMEMENU):
        printf("Entering game state...\n");
        game_menu_state(&app);
        printf("Exiting game state...\n");
        break;
      case (EXIT):
        printf("Exit state was requested\n");
        exit_requested = true;
        break;
    }
  }

  // @EXIT
  // Cleaning
clean:
  clean(app);
  free_fig_mem();
  print_meme(app);

  printf(OUTPUT_MESSAGE);
  return 0;
}

void clean(application_t app) {
  parlcd_flush(app.address_book.parlcd_membase);
  led_line_flush(&app);
  printf("FLUSHED\n");
}

void print_meme(application_t app) {
  unsigned short fb[SIZE] = {BG_COLOR};
  uint32_t str_sizes =
      get_sizes_str("Kilroy was here", 3, app.font_descriptors.big);
  draw_string(get_str_start(str_sizes >> 16), 160, "Kilroy was here",
              FONT_COLOR, 3, fb, app.font_descriptors.big);
  parlcd_write_frame(app.address_book.parlcd_membase, fb);
  exit(0);
}
