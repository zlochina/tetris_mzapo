#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "app_structure.h"
#include "constants.h"
#include "controllers.h"
#include "game_mechanics.h"
#include "menu.h"

// defines of flags
#define FALL_A_ROW 1
#define LEFT_ORIENTATION 1 << 1
#define RIGHT_ORIENTATION 1 << 2
#define LEFT_MOVEMENT 1 << 3
#define RIGHT_MOVEMENT 1 << 4
#define DROP_FIGURE 1 << 5

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

/*
 * functions prints three different sections with predefined coords in game
 * frame such as: tetris section, next section & stats section
 */
void print_sections(application_t *app, unsigned short color,
                    char *tetris_section_str);

/*
 * function that writes actual stats numbers to stats section
 */
void update_stats_section(application_t *app);

/*
 * function inits game frame by printing sections & and printint predefined
 * strings in stats section
 */
void init_game_frame(application_t *app);

/*
 * functions rewrites printed sections with different color to show "Lost game
 * attitude"
 */
void update_game_frame_to_gameover(application_t *app);

/*
 * alternative main function, which runs game frame
 */
void game_state(application_t *app);

/*
 * function initialises game frame + initialises some starting variables in app
 */
void init_game(application_t *app);
