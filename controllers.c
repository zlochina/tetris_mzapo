#include "controllers.h"

uint8_t compare_knob_values(uint8_t old_value, uint8_t new_value) {
  int sub = new_value - old_value;

  // threshold for checking the aim is 128
  // knob rotation
  if (sub == 0) {
    // not changed
    return 0;
  } else if (sub > 0 && sub < 128 || sub < -128) {
    // turning right
    return 0x1;
  } else {
    // turning left
    return 0x2;
  }
}

uint8_t listen_to_knobs(uint32_t actual_knobs_value,
                        cached_knobs_t cached_values) {
  uint8_t new_top_value = (actual_knobs_value >> 16) & 0xff;
  uint8_t new_mid_value = (actual_knobs_value >> 8) & 0xff;
  uint8_t new_bot_value = actual_knobs_value & 0xff;

  return (compare_knob_values(new_top_value, cached_values.top_button) << 4) |
         (compare_knob_values(new_mid_value, cached_values.middle_button)
          << 2) |
         (compare_knob_values(new_bot_value, cached_values.bottom_button));
}
