#include QMK_KEYBOARD_H

/*
Swiss french layout, derived from a TKL keyboard.
Feel free to get inspiration from this, I take no responsabilities for hair loss if debugging this thing.

7.05.2020
    enabling numlock at keyboard boot
    moved mouse keys 1 column to the right
    commented layers, now to give a visual representation like the default keymap

08.05.2020
    enabled auto shift
    enabled tap dance, double shift = caps lock

09.05.2020
    Added LED layer reporting
    added tap dancing on LGUI => F5 and <> => F12
    converted MO to OSL, so that I don't need to keep the modifier pushed

11.05.2020
    altGR + backspace = delete
    tap dancing on enter => tab

12.05.2020
    Tap dancing is now as such:
        enter   => tab
        control => F5
        <       => F12
        shift   => caps lock
*/

//force numlock to ON on keyboard boot
void matrix_init_user(void) {
    if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
}

enum layers { _QWERTZ, _NBR, _MOUSE, _PAD };

// Report layers active using leds
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTZ:
            writePinLow(LED_RED);
            writePinLow(LED_GREEN);
            break;
        case _NBR:
            writePinHigh(LED_RED);
            writePinLow(LED_GREEN);
            break;
        case _MOUSE:
            writePinLow(LED_RED);
            writePinHigh(LED_GREEN);
            break;
        case _PAD:
            writePinHigh(LED_RED);
            writePinHigh(LED_GREEN);
    }
    return state;
}

//Tap Dance Declarations
enum {
  TD_CAPS_LOCK = 0
  ,TD_F5 = 1
  ,TD_F12 = 2
  ,TD_TAB = 3
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for left shift, twice for Caps Lock
  [TD_CAPS_LOCK]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
  ,[TD_F5] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_F5)
  ,[TD_F12] = ACTION_TAP_DANCE_DOUBLE(KC_NUBS, KC_F12)
  ,[TD_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_ENTER, KC_TAB)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	//base layer, qwertz
    [_QWERTZ] = LAYOUT_plaid_mit(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_LBRC, KC_RBRC,
		TD(TD_CAPS_LOCK), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENTER,
		TD(TD_F5), KC_LGUI, KC_LALT, KC_RALT, OSL(1), LT(3,KC_SPC), OSL(2), KC_COMM, KC_DOT, KC_SLSH, TD(TD_F12)
	),
    //F keys and numbers
	[_NBR] = LAYOUT_plaid_mit(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_NO,
		KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_MPRV, KC_HOME, KC_END, KC_ENTER,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_SPC, KC_NO, KC_MFFD, KC_VOLD, KC_VOLU, KC_MPLY
	),
    //mouse emulation and wasd as arrows
	[_MOUSE] = LAYOUT_plaid_mit(
		KC_ESC, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_MINS, KC_EQL, KC_BSPC,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_MPRV, KC_BTN2, KC_NO, KC_ENTER,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_SPC, KC_NO, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
	),
    //wasd as arrows and numeric keypad
	[_PAD] = LAYOUT_plaid_mit(
		KC_ASTG, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PSLS,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PAST,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PMNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_P0, KC_PDOT, KC_PENT, KC_PPLS
	)
};

static bool control_disabled = false;
static bool delete_pressed = false;

/**
 * Change altGR+backspace into delete and do not register the altGr modifier.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(keycode == KC_BSPC) {
    if (record->event.pressed) {
      if(keyboard_report->mods & MOD_BIT(KC_RALT)) {
        delete_pressed = true;
        control_disabled = true;
        unregister_code(KC_RALT);
        register_code(KC_DEL);
        return false;
      }
    } else if(delete_pressed) {
      delete_pressed = false;
      unregister_code(KC_DEL);

      if(control_disabled) {
        control_disabled = false;
        register_code(KC_RALT);
      }
      return false;
    }
  } else if(keycode == KC_RALT && !record->event.pressed && delete_pressed) {
    delete_pressed = false;
    control_disabled = false;
    unregister_code(KC_DEL);
    register_code(KC_BSPC);
    return false;
  }
  return true;
}
