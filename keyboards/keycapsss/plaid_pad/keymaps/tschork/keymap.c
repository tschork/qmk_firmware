#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,-----------------------,
 * |  '  |  =  |  !  |  F5 |
 * |-----+-----+-----+-----|
 * |  :  |  /  |  \  |  F12|
 * |-----+-----+-----+-----|
 * |  @  | del |  up |Enter|
 * |-----+-----+-----+-----|
 * |  #  | Left| Dwn|  rght|
 * `-----------------------'
 */
LAYOUT_ortho_4x4(
		KC_MINS, LSFT(KC_0), LSFT(KC_RBRC), KC_F5,
		LSFT(KC_DOT), LSFT(KC_7), RALT(KC_NUBS), KC_F12,
		RALT(KC_2), KC_DEL,   KC_UP,  KC_ENTER,
		RALT(KC_3), KC_LEFT, KC_DOWN, KC_RGHT
)

};

// Set led state during powerup
void keyboard_post_init_user(void) {
    writePinHigh(LED_RED);
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {         // First encoder - top left
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  } else if (index == 1) {  // Second encoder - top right
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}
