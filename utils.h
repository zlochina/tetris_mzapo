/*
 * Function to compress rgb color stored in int to short, which is acknowledged
 * by lcd display
 */
#include <stdint.h>

unsigned short compress_rgb_color(unsigned int);

char *convert_int_to_str(int num);

int calculate_score(uint16_t built_lines, uint32_t speed);

void write_frame_bakcground(unsigned short *frame_buffer);

struct timespec create_delay(uint32_t msecs);

// Debug functions
void write_to_file(unsigned short *);
unsigned int decompress_rgb_color(unsigned short);
