#include "utils.h"

// Output strings

#define INIT_MESSAGE "Starting game of Tetris\n"
#define OUTPUT_MESSAGE "Exiting...\n"
// strings when exiting.
#define NEW_HIGH_SCORE "New High Score: "
#define FINAL_SCORE "Your final score: "

// To be displayed strings
// Defines of menus strings
//  Titles should be scaled and bigger font will be used for these strings
#define MAIN_MENU_TITLE "Tetris"
#define MAIN_MENU_NEW_GAME "New Game"
#define MAIN_MENU_SET_SPEED "Set Speed"
#define MAIN_MENU_EXIT "Exit"

// would be used in main menu without scaling
#define CURRENT_HIGH_SCORE "Current High Score: "

#define GAME_MENU_TITLE "Paused"
#define GAME_MENU_CONTINUE "Continue"
#define GAME_MENU_RESTART "Restart"
#define GAME_MENU_QUIT "Quit to Title"

// strings of game frame. Smaller font will be used with scaling 1
#define GAME_SCORE "Score"
#define GAME_NEXT "Next"
#define GAME_HELP "Help"
#define GAME_STATS "Stats"

// Palette's defines
#define BG_COLOR compress_rgb_color(0x22223b)
#define FONT_COLOR compress_rgb_color(0xf2e9e4)

// figures' palette
#define CYAN compress_rgb_color(0x70d6ff)
#define PINK compress_rgb_color(0xff70a6)
#define ORANGE compress_rgb_color(0xff9770)
#define SUNNY compress_rgb_color(0xffd670)
#define ACID compress_rgb_color(0xe9ff70)
#define LIGHT_PINK compress_rgb_color(0x9381ff)
#define WHITE compress_rgb_color(0xf8f7ff)

// speed values
#define SLOW 0xff
#define MEDIUM 0xffff
#define FAST 0xffffff
#define FASTEST 0xffffffff

// WIDTH AND HEIGHT OF THE LCD WINDOW
#define WIDTH 320
#define HEIGHT 480
#define SIZE HEIGHT* WIDTH
