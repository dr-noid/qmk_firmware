/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

#include QMK_KEYBOARD_H

// Layer names
enum ats_layers {
    // Base layers
    QWERTY_LAYER,
    CANARY_LAYER,
    // F1 through F12
    FUNC_LAYER,
    // Alternate Function layer
    ALT_LAYER
};

// Custom keycodes
enum custom_keycodes {
    TG_LAYOUT = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_LAYOUT:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == CANARY_LAYER) {
                    default_layer_set(1UL << QWERTY_LAYER);
                } else {
                    default_layer_set(1UL << CANARY_LAYER);
                }
            }
            return false;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY_LAYER] = LAYOUT(
    KC_ESC,        KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_CAPS_LOCK,   KC_AUDIO_MUTE,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,   KC_PRINT_SCREEN,
    KC_BACKSPACE,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_DELETE,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  KC_COMMA,     KC_DOT,       KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, MO(FUNC_LAYER),                KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    ),
    [CANARY_LAYER] = LAYOUT(
    KC_ESC,        KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_CAPS_LOCK,   KC_AUDIO_MUTE,
    KC_TAB,        KC_W,        KC_L,        KC_Y,  KC_P,  KC_K,  KC_Z,      KC_X,  KC_O,  KC_U,         KC_SEMICOLON, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,   KC_PRINT_SCREEN,
    KC_BACKSPACE,  KC_C,        KC_R,        KC_S,  KC_T,  KC_B,  KC_F,      KC_N,  KC_E,  KC_I,         KC_A,         KC_QUOTE,                          KC_ENTER,       KC_DELETE,
    KC_LEFT_SHIFT,              KC_J,        KC_V,  KC_D,  KC_G,  KC_Q,      KC_M,  KC_H,  KC_SLASH,     KC_COMMA,     KC_DOT,                            KC_RIGHT_SHIFT, KC_UP,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, MO(FUNC_LAYER),                KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    ),
    [FUNC_LAYER] = LAYOUT(
    KC_GRAVE,      KC_F1,       KC_F2,       KC_F3, KC_F4, KC_F5, KC_F6,     KC_F7, KC_F8, KC_F9,        KC_F10,       KC_F11,          KC_F12,           TG_LAYOUT,      KC_TRNS,
    RM_TOGG,       KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         RM_HUEU,         RM_HUED,          KC_BACKSLASH,   KC_F13,
    KC_BACKSPACE,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         RM_SATD,      RM_SATU,                           KC_ENTER,       KC_F14,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  KC_COMMA,     KC_DOT,       KC_SLASH,                          KC_RIGHT_SHIFT, RM_VALU,
    KC_LEFT_CTRL,  GU_TOGG,     KC_LEFT_ALT,                      KC_SPACE,                RM_NEXT,      _______,                       MO(ALT_LAYER),    RM_SPDD,        RM_VALD,        RM_SPDU
    ),
    [ALT_LAYER] = LAYOUT(
    KC_ESC,        KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,      KC_7,  KC_8,  KC_9,         KC_0,         KC_MINUS,        KC_EQUAL,         KC_CAPS_LOCK,   KC_TRNS,
    KC_TAB,        KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,      KC_U,  KC_I,  KC_O,         KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,   KC_TRNS,
    KC_BACKSPACE,  KC_A,        KC_S,        KC_D,  KC_F,  KC_G,  KC_H,      KC_J,  KC_K,  KC_L,         KC_SEMICOLON, KC_QUOTE,                          KC_ENTER,       KC_TRNS,
    KC_LEFT_SHIFT,              KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,      KC_N,  KC_M,  _______,      _______,      KC_SLASH,                          KC_RIGHT_SHIFT, KC_UP,
    KC_LEFT_CTRL,  KC_LEFT_GUI, KC_LEFT_ALT,                      KC_SPACE,                KC_RIGHT_ALT, _______,                       KC_RIGHT_CTRL,    KC_LEFT,        KC_DOWN,        KC_RIGHT
    )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERTY_LAYER] = {ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)},
    [CANARY_LAYER] = {ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)},
    [FUNC_LAYER]   = {ENCODER_CCW_CW(KC_F15, KC_F16)},
    [ALT_LAYER]    = {ENCODER_CCW_CW(RM_SATD, RM_SATU)},
};
#endif
