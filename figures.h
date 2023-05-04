#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uint8_t num_states;  // Number of states
  uint8_t *fig;
} figure_t;

extern figure_t figure_S;
extern figure_t figure_I;
extern figure_t figure_O;
extern figure_t figure_T;
extern figure_t figure_Z;
extern figure_t figure_J;
extern figure_t figure_L;

void init_figures();

void free_fig_mem();
