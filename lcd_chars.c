/* Most of the functions were taken from one of the examples of working with
 * MZ_APO device on the page of APO subject in FEL courseware
 */
#include "lcd_chars.h"

void draw_pixel(int x, int y, unsigned short color, unsigned short *frame) {
  if (x >= 0 && x < 480 && y >= 0 && y < 320) {
    frame[x + 320 * y] = color;
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
      for (j = 0; j < w; j++) {
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
  char char_tmp = *str;
  int ptr = 0;
  int offset = 0;
  while (char_tmp != '\0') {
    draw_char(x + offset, y, char_tmp, color, scale, frame, fdes);

    // update char_tmp
    offset += char_width(char_tmp, fdes) * scale;
    char_tmp = *(str + ++ptr);
  }
}
