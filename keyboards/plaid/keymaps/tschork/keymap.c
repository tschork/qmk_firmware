#include QMK_KEYBOARD_H

/*
Swiss french layout, derived from a TKL keyboard.
Feel free to get inspiration from this, I take no responsabilities for hair loss if debugging this thing.

todo: * convert the MO switches to TG and use the leds as a layer indicator.
        use the 2 leds like binary clocks (o is off, x is on)
            o o layer 0
            x o layer 1
            o x layer 2
            x x layer 3

7.05.2020
    enabling numlock at keyboard boot
    moved mouse keys 1 column to the right
    commented layers, now to give a visual representation like the default keymap

08.05.2020
    enabled auto shift
    enabled tap dance, double shift = caps lock
*/

//force numlock to on on keyboard boot
void matrix_init_user(void) {
    if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
}

//Tap Dance Declarations
enum {
  TD_CAPS_LOCK = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for left shift, twice for Caps Lock
  [TD_CAPS_LOCK]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	//base layer, qwertz
    [0] = LAYOUT_plaid_mit(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_LBRC, KC_RBRC,
		TD(TD_CAPS_LOCK)/*KC_LSFT*/, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_SCLN, KC_QUOT, KC_BSLS, KC_SFTENT,
		KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, MO(1), LT(3,KC_SPC), MO(2), KC_COMM, KC_DOT, KC_SLSH, KC_NUBS
	),
    //F keys and numbers
	[1] = LAYOUT_plaid_mit(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_DEL,
		KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_MPRV, KC_HOME, KC_END, KC_ENT,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_SPC, KC_NO, KC_MFFD, KC_VOLD, KC_VOLU, KC_MPLY
	),
    //mouse emulation and wasd as arrows
	[2] = LAYOUT_plaid_mit(
		KC_ESC, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_MINS, KC_EQL, KC_BSPC,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3, KC_DEL,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_MPRV, KC_BTN2, KC_NO, KC_ENT,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_SPC, KC_NO, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
	),
    //wasd as arrows and numeric keypad
	[3] = LAYOUT_plaid_mit(
		DEBUG, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PSLS,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PAST,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PMNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_P0, KC_PDOT, KC_PENT, KC_PPLS
	)
};
