/* Names for the figures of the tetris game are corresponding to
 * next @reference: https://tetris.wiki/Tetromino
 *
 * Width and height for the figures will be 4 x 4 bits
 * which then will be scaled by 5 so the final width would be 20 pixels
 *
 * @author: Vladyslav Zlochevskyi
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
     * 0000
     * 0100
     * 1110
     * 0000
     */
    0x00, 0x02, 0x06, 0x02,
    /* T looking left
     * 0000
     * 0010
     * 0110
     * 0010
     */
    0x00, 0x0e, 0x04, 0x00,
    /* normal looking T
     * 0000
     * 1110
     * 0100
     * 0000
     */
    0x00, 0x08, 0x0c, 0x08,
    /* T looking right
     * 1000
     * 1100
     * 1000
     * 0000
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
    0x00, 0x06, 0x04, 0x04,
    /*
     * 0000
     * 0110
     * 0100
     * 0100
     */
    0x00, 0x04, 0x07, 0x00,
    /*
     * 0000
     * 0100
     * 0111
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
    0x00, 0x06, 0x02, 0x02,
    /*
     * 0000
     * 0110
     * 0010
     * 0010
     */
    0x00, 0x07, 0x04, 0x00
    /*
     * 0000
     * 0111
     * 0100
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

void array_copy(uint8_t *dest, uint8_t source[], uint32_t nmemb) {
  for (int i = 0; i < nmemb; i++) {
    *(dest + i) = source[i];
  }
}

figure_arr_t init_figures() {
  figure_S.num_states = 4;
  figure_S.color = CYAN;
  figure_S.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_S.num_states);
  array_copy(figure_S.fig, fig_S, 4 * 4);

  figure_I.num_states = 2;
  figure_I.color = PINK;
  figure_I.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_I.num_states);
  array_copy(figure_I.fig, fig_I, 4 * 2);

  figure_O.num_states = 1;
  figure_O.color = SUNNY;
  figure_O.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_O.num_states);
  array_copy(figure_O.fig, fig_O, 4 * 1);

  figure_T.num_states = 4;
  figure_T.color = ACID;
  figure_T.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_T.num_states);
  array_copy(figure_T.fig, fig_T, 4 * 4);

  figure_Z.num_states = 4;
  figure_Z.color = LIGHT_PINK;
  figure_Z.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_Z.num_states);
  array_copy(figure_Z.fig, fig_Z, 4 * 4);

  figure_J.num_states = 4;
  figure_J.color = WHITE;
  figure_J.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_J.num_states);
  array_copy(figure_J.fig, fig_J, 4 * 4);

  figure_L.num_states = 4;
  figure_L.color = ORANGE;
  figure_L.fig = (uint8_t *)malloc(sizeof(uint8_t) * 4 * figure_L.num_states);
  array_copy(figure_L.fig, fig_L, 4 * 4);

  figure_arr_t fig_arr;
  fig_arr.I = figure_I;
  fig_arr.S = figure_S;
  fig_arr.O = figure_O;
  fig_arr.T = figure_T;
  fig_arr.Z = figure_Z;
  fig_arr.J = figure_J;
  fig_arr.L = figure_L;
  return fig_arr;
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
