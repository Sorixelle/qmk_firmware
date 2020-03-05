/* Copyright 2020 Sorixelle (Ruby Iris Juric)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include QMK_KEYBOARD_H

enum my_keycodes {
    AUCL = SAFE_RANGE, // Toggle Autoclicker (left-click)
    AUCR,              // Toggle Autoclicker (right-click)
    SWQC,              // Switch between QWERTY/Colemak
};

bool runAutoclickL = false;
bool runAutoclickR = false;
layer_state_t currentLayer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_60_hhkb(
    KC_ESC,   KC_1,     KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV, \
    KC_TAB,   KC_Q,     KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,          KC_BSPC,\
    KC_LCTL,  KC_A,     KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,          \
    KC_LSPO,            KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSPC,          MO(2),  \
    KC_LCTL,  KC_LGUI,  KC_LALT,                    KC_SPC,                        KC_RALT,  KC_RGUI,           KC_RCTL         ),

[1] = LAYOUT_60_hhkb(
    KC_ESC,   KC_1,     KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV, \
    KC_TAB,   KC_Q,     KC_W,  KC_F,  KC_P,  KC_G,  KC_J,  KC_L,  KC_U,  KC_O,     KC_SCLN,  KC_LBRC,  KC_RBRC,          KC_BSPC,\
    KC_LCTL,  KC_A,     KC_R,  KC_S,  KC_T,  KC_D,  KC_H,  KC_N,  KC_E,  KC_I,     KC_O,     KC_QUOT,           KC_ENT,          \
    KC_LSPO,            KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_K,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSPC,          MO(3),  \
    KC_LCTL,  KC_LGUI,  KC_LALT,                    KC_SPC,                        KC_RALT,  KC_RGUI,           KC_RCTL         ),

[2] = LAYOUT_60_hhkb(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_TRNS,  MO(4),  \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,    KC_TRNS,           KC_DEL, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,           KC_TRNS,          \
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_PGDN, KC_DOWN,  KC_TRNS,           KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,           DF(1)             ),

[3] = LAYOUT_60_hhkb(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_TRNS,  MO(4),  \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,    KC_TRNS,           KC_DEL, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,           KC_TRNS,          \
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_PGDN, KC_DOWN,  KC_TRNS,           KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,           DF(0)             ),

[4] = LAYOUT_60_hhkb(
    RESET  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,            KC_TRNS,          \
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,\
    AUCR,    KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS,  KC_TRNS,            AUCL             ),
};

void matrix_init_user() {

}

void matrix_scan_user() {
  if (runAutoclickL) {
    tap_code(KC_MS_BTN1);
  }

  if (runAutoclickR) {
    tap_code(KC_MS_BTN2);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case AUCL:
      if (record->event.pressed) {
        runAutoclickL = !runAutoclickL;
      }
      return false;
    case AUCR:
      if (record->event.pressed) {
        runAutoclickR = !runAutoclickR;
      }
      return false;
    case SWQC:
      if (record->event.pressed) {
        if (currentLayer == 0) {
            currentLayer = 3;
        } else {
          currentLayer = 0;
        }
        layer_state_set(currentLayer);
      }
      return false;
    default:
      return true;
  }
}
