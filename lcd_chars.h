#include <stdint.h>

#include "constants.h"
#include "font_types.h"

void draw_pixel(int, int, unsigned short, unsigned short *);

void draw_pixel_big(int, int, unsigned short, uint8_t, unsigned short *);

int char_width(int, font_descriptor_t *);

void draw_char(int, int, char, unsigned short, int, unsigned short *,
               font_descriptor_t *);

void draw_string(int, int, char *, unsigned short, int, unsigned short *,
                 font_descriptor_t *);

unsigned int get_str_length(char *);

uint32_t get_sizes_str(char *, int, font_descriptor_t *);

uint16_t get_str_start(uint16_t);
