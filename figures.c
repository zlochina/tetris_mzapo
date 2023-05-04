/* Names for the figures of the tetris game are corresponding to
 * next @reference: https://tetris.wiki/Tetromino
 *
 * Width and height for the figures will be 4 x 4 bits
 * which then will be scaled by 5 so the final width would be 20 pixels
 */

#include "figures.h"

uint8_t fig_I[] = {
    0x00, 0x00, 0x0f, 0x00,
    /*
     * horizontal I
     */
    0x04, 0x04, 0x04, 0x04,
    /*
     * vertical I
     */
};

uint8_t fig_O[] = {
    0x00, 0x06, 0x06, 0x00,
    /* It is just box with one state
     */
};

uint8_t fig_T[] = {
    0x00, 0x04, 0x0e, 0x00,
    /* T reverse
     */
    0x00, 0x02, 0x06, 0x02,
    /* T looking left
     */
    0x00, 0x0e, 0x04, 0x00,
    /* normal looking T
     */
    0x00, 0x04, 0x06, 0x04,
    /* T looking right
     */
};

uint8_t fig_S[] = {
    0x00, 0x06, 0x0c, 0x00,
    /*
     * normal looking S
     */
    0x00, 0x08, 0x0c, 0x04,
    /*
     * 0000
     * 1000
     * 1100
     * 0100
     */
    0x00, 0x06, 0x0c, 0x00,
    /*
     * normal looking S
     */
    0x00, 0x04, 0x06, 0x02,
    /*
     * 0000
     * 0100
     * 0110
     * 0010
     */
};

uint8_t fig_Z[] = {
    0x00, 0x0c, 0x06, 0x00,
    /*
     * normal looking Z
     */
    0x00, 0x04, 0x0c, 0x08,
    /*
     * 0000
     * 0100
     * 1100
     * 1000
     */
    0x00, 0x0c, 0x06, 0x00,
    /*
     * normal looking Z
     */
    0x00, 0x02, 0x06, 0x04,
    /*
     * 0000
     * 0010
     * 0110
     * 0100
     */
};

uint8_t fig_J[] = {
    0x02, 0x02, 0x06, 0x00,
    /*
     * 0010
     * 0010
     * 0110
     * 0000
     */
    0x00, 0x0e, 0x02, 0x00,
    /*
     * 0000
     * 1110
     * 0010
     * 0000
     */
    0x06, 0x04, 0x04, 0x00,
    /*
     * 0110
     * 0100
     * 0100
     * 0000
     */
    0x00, 0x08, 0x0e, 0x00,
    /*
     * 0000
     * 1000
     * 1110
     * 0000
     */
};

uint8_t fig_L[] = {
    0x04, 0x04, 0x06, 0x00,
    /*
     * 0100
     * 0100
     * 0110
     * 0000
     */
    0x00, 0x02, 0x0e, 0x00,
    /*
     * 0000
     * 0010
     * 1110
     * 0000
     */
    0x06, 0x02, 0x02, 0x00,
    /*
     * 0110
     * 0010
     * 0010
     * 0000
     */
    0x00, 0x0e, 0x08, 0x00
    /*
     * 0000
     * 1110
     * 1000
     * 0000
     */
};

figure_t figure_S;
figure_t figure_I;
figure_t figure_O;
figure_t figure_T;
figure_t figure_Z;
figure_t figure_J;
figure_t figure_L;

// TODO init figure structures and pass them to main function
void init_figures() {
  figure_S.num_states = 4;
  figure_S.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_S.num_states);
  memcpy(figure_S.fig, fig_S, 4 * 4 * sizeof(uint8_t));

  figure_I.num_states = 2;
  figure_I.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_I.num_states);
  memcpy(figure_I.fig, fig_I, 4 * 2 * sizeof(uint8_t));

  figure_O.num_states = 1;
  figure_O.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_O.num_states);
  memcpy(figure_O.fig, fig_O, 4 * 1 * sizeof(uint8_t));

  figure_T.num_states = 4;
  figure_T.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_T.num_states);
  memcpy(figure_T.fig, fig_T, 4 * 4 * sizeof(uint8_t));

  figure_Z.num_states = 4;
  figure_Z.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_Z.num_states);
  memcpy(figure_Z.fig, fig_Z, 4 * 4 * sizeof(uint8_t));

  figure_J.num_states = 4;
  figure_J.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_J.num_states);
  memcpy(figure_J.fig, fig_J, 4 * 4 * sizeof(uint8_t));

  figure_L.num_states = 4;
  figure_L.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_L.num_states);
  memcpy(figure_L.fig, fig_L, 4 * 4 * sizeof(uint8_t));
}

void free_fig_mem() {
  free(figure_S.fig);
  free(figure_I.fig);
  free(figure_O.fig);
  free(figure_T.fig);
  free(figure_Z.fig);
  free(figure_J.fig);
  free(figure_L.fig);
}
