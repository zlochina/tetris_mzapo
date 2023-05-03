#include "utils.h"

#include <stdint.h>
#include <stdio.h>

#define TEST_OUTPUT "output.ppm"

unsigned short compress_rgb_color(unsigned int color) {
  unsigned int r = color >> 16;
  r >>= 3;
  unsigned int g = (color >> 8) & 0xff;
  g >>= 2;
  unsigned int b = (color)&0xff;
  return (r << 11) | (g << 5) | b >> 3;
}

unsigned int decompress_rgb_color(unsigned short color) {
  unsigned int r = color & 0xf800;
  unsigned int g = color & 0x7e0;
  unsigned int b = color & 0x1f;
  r <<= 8;
  g <<= 5;
  b <<= 3;
  return r | g | b;
}

void write_to_file(unsigned short frame[]) {
  // init
  FILE* file = fopen(TEST_OUTPUT, "wb");

  // process
  uint8_t frame_dup[320 * 480 * 3] = {0};
  for (int i = 0; i < 480; i++) {
    int i_base = i * 320;
    for (int j = 0; j < 320; j++) {
      unsigned int val = decompress_rgb_color(frame[i_base + j]);
      int coord = i_base + j;
      frame_dup[3 * coord] = (val >> 16) & 0xff;
      frame_dup[3 * coord + 1] = (val >> 8) & 0xff;
      frame_dup[3 * coord + 2] = val & 0xff;
    }
  }
  fprintf(file, "P6\n%d\n%d\n255\n", 320, 480);
  fwrite(frame_dup, sizeof(char), 320 * 480 * 3, file);

  // close
  fclose(file);
}
