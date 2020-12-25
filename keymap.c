/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Keebio BDN9 9-key Macropad Code
 * Code compiled by godofbooks (https://github.com/godofbooks)
 * Resources and source code can be found at https://github.com/godofbooks/bdn9rev1
 *
 * This code accounts for 2 encoders in the upper corners; a third encoder in the upper
 * middle spot is also an option, please be aware that this code doesn't include that.
*/

//defines base keyboard layout
#include QMK_KEYBOARD_H

//defines layer names 
enum layer_names{
    _GEN,
    _CODE,
    _ART,
    _MEDIA,
    _BL,
};

//defines encoder names
enum encoder_names {
  _LEFT,
  _RIGHT,
};

//defines custom keycodes that don't exist as commands already
enum custom_keycodes {
    KC_SAVE,
    KC_REDO,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_SAVE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("s"));
        }
        break;
    case KC_REDO:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("y"));
        }
        break;
    }
    return true;
};

/*    DEFINE KEYCODES    */
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_X)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)

/*     RGB COLORS         */
#define RGB_WHITE 0xFF, 0xFF, 0xFF
#define RGB_RED 0xFF, 0x00, 0x00
#define RGB_CORAL 0xFF, 0x7C, 0x4D
#define RGB_ORANGE 0xFF, 0x80, 0x00
#define RGB_GOLDENROD 0xD9, 0xA5, 0x21
#define RGB_GOLD 0xFF, 0xD9, 0x00
#define RGB_YELLOW 0xFF, 0xFF, 0x00
#define RGB_CHARTREUSE 0x80, 0xFF, 0x00
#define RGB_GREEN 0x00, 0xFF, 0x00
#define RGB_SPRINGGREEN 0x00, 0xFF, 0x80
#define RGB_TURQUOISE 0x47, 0x6E, 0x6A
#define RGB_TEAL 0x00, 0x80, 0x80
#define RGB_CYAN 0x00, 0xFF, 0xFF
#define RGB_AZURE 0x99, 0xf5, 0xFF
#define RGB_BLUE 0x00, 0x00, 0xFF
#define RGB_PURPLE 0x7A, 0x00, 0xFF
#define RGB_MAGENTA 0xFF, 0x00, 0xFF
#define RGB_PINK 0xFF, 0x80, 0xBF
#define RGB_BLACK 0x00, 0x00, 0x00
#define RGB_OFF RGB_BLACK

//enables RGB underglow (must have RGB LEDs on the board)
void matrix_init_user(void) {
  rgblight_enable();
  rgblight_setrgb(RGB_WHITE);
};

//switches what color the LEDs display depending on what layer is active
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _GEN:
        rgblight_setrgb (RGB_GREEN);
        break;
    case _CODE:
        rgblight_setrgb (RGB_CYAN);
        break;
    case _ART:
        rgblight_setrgb (RGB_GOLD);
        break;
    case _MEDIA:
        rgblight_setrgb (RGB_RED);
        break;
    case _BL:
        rgblight_setrgb (RGB_WHITE);
        break;
    }
  return state;
}

//keyboard layouts per layer
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up | Toggles: | Knob 2: Tab Fwd/Bk |
        | Press: Play/Pause | Layer 1  | Press: Mute        |
        | Windows Key       | Up       | My Computer        |
        | Left              | Down     | Right              |
     */
    [_GEN] = LAYOUT(
        KC_MPLY, TO(1), KC_MUTE,
        KC_LGUI, KC_UP  , KC_MYCM,
        KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    /*
        | Knob 1 Vol Dn/Up  | Toggles: | Knob 2: Page Dn/Up |
        | Press: Play/Pause | Layer 2  | Press: Mute        |
        | Cut               | Copy     | Save               |
        | Enter             | Paste    | Undo               |
     */
    [_CODE] = LAYOUT(
        KC_MPLY, TO(2) , KC_MUTE,
        KC_CUT, KC_COPY, KC_SAVE,
        KC_ENT, KC_PASTE , KC_UNDO
    ),
    /*
        | Knob 1 Vol Dn/Up  | Toggles: | Knob 2: Page Dn/Up |
        | Press: Play/Pause | Layer 3  | Press: Mute        |
        | Cut               | Copy     | Save               |
        | Redo              | Paste    | Undo               |
     */
    [_ART] = LAYOUT(
        KC_MPLY, TO(3) , KC_MUTE,
        KC_CUT, KC_COPY, KC_SAVE,
        KC_REDO, KC_PASTE , KC_UNDO
    ),
    /*
        (Please note the commands on this layer are designed specifically
        for Youtube; they may or may not work on other video sites.)

        | Knob 1 Vol Dn/Up   | Toggles:   | Knob 2: Scroll thru video |
        | Press: Play/Pause  | Layer 4    | Press: Mute               |
        | Fullscreen On/Off  | Play/Pause | Caption On/Off            |
        | Back 10 sec        | Mute       | Forward 10 sec            |
    */
    [_MEDIA] = LAYOUT(
        KC_MPLY, TO(4) , KC_MUTE,
        KC_F, KC_K, KC_C,
        KC_J, KC_M , KC_L
    ),
    /*
        | Knob 1 Vol Dn/Up  | Toggles:         | Knob 2: Page Dn/Up |
        | Press: Play/Pause | Layer 0          | Press: Mute        |
        | Backlight On      | Toggle BL        | Backlight Off      |
        | Increase BL Level | Toggle Breathing | Decrease BL Level  |
     */
    [_BL] = LAYOUT(
        KC_MPLY, TO(0) , KC_MUTE,
        BL_ON, BL_TOGG, BL_OFF,
        BL_INC, BL_BRTG , BL_DEC
    ),
};

//encoder commands; right encoder has per layer commands
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _RIGHT) {
        if (IS_LAYER_ON(0) == true){
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
        } else if (IS_LAYER_ON(2) == true){
            if (clockwise) {
                tap_code(KC_DOT);
            } else {
                tap_code(KC_COMM);
            }
        } else {
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        }
    }
}
