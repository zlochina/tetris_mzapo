#ifndef __FIGURES_H__
#define __FIGURES_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

typedef struct {
  uint8_t num_states;  // Number of states
  unsigned short color;
  uint8_t *fig;
} figure_t;

typedef struct {
  figure_t S;
  figure_t I;
  figure_t O;
  figure_t T;
  figure_t Z;
  figure_t J;
  figure_t L;
} figure_arr_t;

figure_arr_t init_figures();

void free_fig_mem();

#endif  //__FIGURES_H__
