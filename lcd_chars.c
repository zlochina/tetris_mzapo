/* Most of the functions were taken from one of the examples of working with
 * MZ_APO device on the page of APO subject in FEL courseware
 * BUT there are functions which are written by @author of the project
 */
#include "lcd_chars.h"

#include <stdio.h>

void draw_pixel(int x, int y, unsigned short color, unsigned short *frame) {
  if (x >= 0 && x < 320 && y >= 0 && y < 480) {
    frame[y + 480 * x] = color;
  }
}

void draw_pixel_big(int x, int y, unsigned short color, uint8_t scale,
                    unsigned short *frame) {
  int i, j;
  for (i = 0; i < scale; i++) {
    for (j = 0; j < scale; j++) {
      draw_pixel(x + i, y + j, color, frame);
    }
  }
}

int char_width(int ch, font_descriptor_t *fdes) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch - fdes->firstchar];
  }
  return width;
}

void draw_char(int x, int y, char ch, unsigned short color, int scale,
               unsigned short *frame, font_descriptor_t *fdes) {
  int w = char_width(ch, fdes);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch - fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch - fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth + 15) / 16;
      ptr = &fdes->bits[(ch - fdes->firstchar) * bw * fdes->height];
    }
    int i, j;
    for (i = 0; i < fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j = w - 1; j != 0; j--) {
        if ((val & 0x8000) != 0) {
          draw_pixel_big(x + scale * j, y + scale * i, color, scale, frame);
        }
        val <<= 1;
      }
      ptr++;
    }
  }
}

void draw_string(int x, int y, char *str, unsigned short color, int scale,
                 unsigned short *frame, font_descriptor_t *fdes) {
  int offset = 0;
  x = WIDTH - x;

  unsigned int str_len = get_str_length(str);
  for (int i = str_len - 1; i != -1; i--) {
    char char_tmp = *(str + i);
    draw_char(x + offset, y, char_tmp, color, scale, frame, fdes);

    // update char_tmp
    offset += char_width(char_tmp, fdes) * scale;
  }
}

unsigned int get_str_length(char *str) {
  unsigned int length = 0;
  char char_tmp = *(str);
  while (char_tmp != '\0') {
    char_tmp = *(str + ++length);
  }
  return length;
}

uint32_t get_sizes_str(char *str, int scale, font_descriptor_t *fdes) {
  uint16_t width = 0, height = 0;
  char char_tmp = *str;
  int ptr = 0;

  while (char_tmp != '\0') {
    width += char_width(char_tmp, fdes) * scale;
    char_tmp = *(str + ++ptr);
  }
  height += fdes->height * scale;

  return (width << 16) | height;
}

// find x_coord for central allignment
uint16_t get_str_start(uint16_t str_width) {
  return ((WIDTH + str_width) >> 1);
}
