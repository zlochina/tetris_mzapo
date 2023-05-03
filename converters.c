#include "converters.h"

unsigned int hsv2rgb(int hue, int saturation, int value) {
  hue = (hue % 360);
  float f = ((hue % 60) / 60.0);
  int p = (value * (255 - saturation)) / 255;
  int q = (value * (255 - saturation * f)) / 255;
  int t = (value * (255 - (saturation * (1.0 - f)))) / 255;
  unsigned int r, g, b;
  if (hue < 60) {
    r = value;
    g = t;
    b = p;
  } else if (hue < 120) {
    r = q;
    g = value;
    b = p;
  } else if (hue < 180) {
    r = p;
    g = value;
    b = t;
  } else if (hue < 240) {
    r = p;
    g = q;
    b = value;
  } else if (hue < 300) {
    r = t;
    g = p;
    b = value;
  } else {
    r = value;
    g = p;
    b = q;
  }
  return ((r << 16) | (g << 8) | b);
}

unsigned int hsv2rgb_lcd(int hue, int saturation, int value) {
  hue = (hue % 360);
  float f = ((hue % 60) / 60.0);
  int p = (value * (255 - saturation)) / 255;
  int q = (value * (255 - saturation * f)) / 255;
  int t = (value * (255 - (saturation * (1.0 - f)))) / 255;
  unsigned int r, g, b;
  if (hue < 60) {
    r = value;
    g = t;
    b = p;
  } else if (hue < 120) {
    r = q;
    g = value;
    b = p;
  } else if (hue < 180) {
    r = p;
    g = value;
    b = t;
  } else if (hue < 240) {
    r = p;
    g = q;
    b = value;
  } else if (hue < 300) {
    r = t;
    g = p;
    b = value;
  } else {
    r = value;
    g = p;
    b = q;
  }
  r >>= 3;
  g >>= 2;
  b >>= 3;
  return (((r & 0x1f) << 11) | ((g & 0x3f) << 5) | (b & 0x1f));
}
