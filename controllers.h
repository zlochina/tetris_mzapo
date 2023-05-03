#include <stdint.h>

typedef struct {
  uint8_t top_button;
  uint8_t middle_button;
  uint8_t bottom_button;
} cached_knobs_t;

/*
 * Compares old and new values of chosen knob
 * return 0b00 if value wasn't changed
 * returns 0b01 if knob was turned clockwise
 * reutrns ob10 if know was turned anti-clockwise
 */
uint8_t listen_to_knobs(uint32_t actual_knobs_value,
                        cached_knobs_t cached_values);

/* returns non-zero values if any of the know was turned
 */
uint8_t compare_knob_values(uint8_t old_value, uint8_t new_value);
