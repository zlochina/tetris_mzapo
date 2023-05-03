#include <stdbool.h>
#include <stdint.h>

#include "constants.h"

// defines of flags for the next function
#define FALL_A_ROW 1
#define LEFT_ORIENTATION 1 << 1
#define RIGHT_ORIENTATION 1 << 2
#define LEFT_MOVEMENT 1 << 3
#define RIGHT_MOVEMENT 1 << 4
/* function receives next flags:
 * RIGHT_MOVEMENT, LEFT_MOVEMENT, RIGHT_ORIENTATION, LEFT_ORIENTATION,
 * FALL_A_ROW update state of the game window
 */
void update_state(unsigned char *frame_buffer, uint8_t flags);
