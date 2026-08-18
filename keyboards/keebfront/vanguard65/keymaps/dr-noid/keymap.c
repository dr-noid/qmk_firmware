/* Copyright 2022 <hello@keebfront.com>
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
#include "analog.h"

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
    TG_LAYOUT = QK_KB_0, // QK_KB_* so VIA can address it as a custom keycode
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
    // Caps Lock and Backspace are swapped on every layer.
    [QWERTY_LAYER] = LAYOUT_ansi_blocker(
    KC_AUDIO_MUTE, KC_ESC,  KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,     KC_7,  KC_8,     KC_9,     KC_0,         KC_MINUS,     KC_EQUAL,        KC_CAPS_LOCK,     KC_PRINT_SCREEN,
                   KC_TAB,  KC_Q,        KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,     KC_U,  KC_I,     KC_O,     KC_P,         KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,  KC_DELETE,
                   KC_BACKSPACE, KC_A,   KC_S,        KC_D,  KC_F,  KC_G,  KC_H,     KC_J,  KC_K,     KC_L,     KC_SEMICOLON, KC_QUOTE,                      KC_ENTER,         KC_HOME,
                   KC_LEFT_SHIFT,        KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,     KC_COMMA, KC_DOT,       KC_SLASH,                      KC_RIGHT_SHIFT,   KC_UP,
                   KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT,                 KC_SPACE,                            KC_RIGHT_ALT, MO(FUNC_LAYER),                KC_LEFT,          KC_DOWN, KC_RIGHT
    ),
    [CANARY_LAYER] = LAYOUT_ansi_blocker(
    KC_AUDIO_MUTE, KC_ESC,  KC_1,        KC_2,        KC_3,  KC_4,  KC_5,  KC_6,     KC_7,  KC_8,     KC_9,     KC_0,         KC_MINUS,     KC_EQUAL,        KC_CAPS_LOCK,     KC_PRINT_SCREEN,
                   KC_TAB,  KC_W,        KC_L,        KC_Y,  KC_P,  KC_K,  KC_Z,     KC_X,  KC_O,     KC_U,     KC_SEMICOLON, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,  KC_DELETE,
                   KC_BACKSPACE, KC_C,   KC_R,        KC_S,  KC_T,  KC_B,  KC_F,     KC_N,  KC_E,     KC_I,     KC_A,         KC_QUOTE,                      KC_ENTER,         KC_HOME,
                   KC_LEFT_SHIFT,        KC_J,        KC_V,  KC_D,  KC_G,  KC_Q,     KC_M,  KC_H,     KC_SLASH, KC_COMMA,     KC_DOT,                        KC_RIGHT_SHIFT,   KC_UP,
                   KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT,                 KC_SPACE,                            KC_RIGHT_ALT, MO(FUNC_LAYER),                KC_LEFT,          KC_DOWN, KC_RIGHT
    ),
    [FUNC_LAYER] = LAYOUT_ansi_blocker(
    _______,       KC_GRAVE, KC_F1,      KC_F2,       KC_F3, KC_F4, KC_F5, KC_F6,    KC_F7, KC_F8,    KC_F9,    KC_F10,       KC_F11,       KC_F12,          TG_LAYOUT,        KC_F13,
                   UG_TOGG, UG_NEXT,     KC_W,        KC_E,  KC_R,  KC_T,  KC_Y,     KC_U,  KC_I,     KC_O,     KC_P,         UG_HUEU,      UG_HUED,         KC_BACKSLASH,     KC_F14,
                   KC_BACKSPACE, KC_A,   KC_S,        KC_D,  KC_F,  KC_G,  KC_H,     KC_J,  KC_K,     KC_L,     UG_SATD,      UG_SATU,                       KC_ENTER,         KC_END,
                   KC_LEFT_SHIFT,        KC_Z,        KC_X,  KC_C,  KC_V,  KC_B,     KC_N,  KC_M,     KC_COMMA, KC_DOT,       KC_SLASH,                      KC_RIGHT_SHIFT,   UG_VALU,
                   KC_LEFT_CTRL, GU_TOGG, KC_LEFT_ALT,                KC_SPACE,                       MO(ALT_LAYER), _______,                               UG_SPDD,          UG_VALD, UG_SPDU
    ),
    [ALT_LAYER] = LAYOUT_ansi_blocker(
    _______,       _______, _______,     _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,         _______,          QK_BOOT,
                   _______, _______,     _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,         _______,          _______,
                   _______, _______,     _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,                       _______,          _______,
                   _______,              _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,                       _______,          _______,
                   _______, _______,     _______,                       _______,                            _______, _______,                                _______,          _______, _______
    )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERTY_LAYER] = {ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)},
    [CANARY_LAYER] = {ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)},
    [FUNC_LAYER]   = {ENCODER_CCW_CW(KC_F15, KC_F16)},
    [ALT_LAYER]    = {ENCODER_CCW_CW(UG_SATD, UG_SATU)},
};
#endif

// ---------------------------------------------------------------------------
// Slider -> absolute monitor brightness
//
// The slider is an absolute 0..127 value sent as MIDI CC 90. A companion script
// on the Windows host (see host/slider_brightness.py) turns that into a
// Twinkle Tray --Set call, so slider position == monitor brightness.
//
// The raw ADC is noisy and pots rarely reach the electrical rails, so this
// smooths, calibrates and rate-limits before sending anything.
// ---------------------------------------------------------------------------

#define SLIDER_CC            90
#define SLIDER_MIDI_CHANNEL  0
#define SLIDER_POLL_MS       10
// Measured travel endpoints. Widen these if the top/bottom of the physical
// throw does not reach 0 / 127; narrow them if it saturates early.
#define SLIDER_RAW_MIN       8
#define SLIDER_RAW_MAX       1015
// Send immediately on a change this large, otherwise wait for the slider to
// settle. Keeps ADC jitter off the wire without losing the exact endpoints.
#define SLIDER_STEP          2
#define SLIDER_SETTLE_MS     150

extern MidiDevice midi_device;

static uint16_t slider_acc     = 0;      // EMA accumulator, 4x oversampled
static uint8_t  slider_sent    = 0xFF;   // last value actually transmitted
static uint16_t slider_poll_at = 0;
static uint16_t slider_moved_at = 0;
static bool     slider_pending = false;
static bool     slider_primed  = false;

static uint8_t slider_scale(uint16_t raw) {
    if (raw <= SLIDER_RAW_MIN) return 0;
    if (raw >= SLIDER_RAW_MAX) return 127;
    return ((uint32_t)(raw - SLIDER_RAW_MIN) * 127) / (SLIDER_RAW_MAX - SLIDER_RAW_MIN);
}

static void slider_task(void) {
    if (timer_elapsed(slider_poll_at) < SLIDER_POLL_MS) return;
    slider_poll_at = timer_read();

    uint16_t raw = analogReadPin(SLIDER_PINA);

    if (!slider_primed) {
        slider_acc    = raw << 2;
        slider_primed = true;
    }
    slider_acc = slider_acc - (slider_acc >> 2) + raw;

    uint8_t value = slider_scale(slider_acc >> 2);
    int16_t delta = (int16_t)value - (int16_t)slider_sent;
    if (delta < 0) delta = -delta;

    if (delta >= SLIDER_STEP) {
        midi_send_cc(&midi_device, SLIDER_MIDI_CHANNEL, SLIDER_CC, value);
        slider_sent     = value;
        slider_pending  = false;
        slider_moved_at = timer_read();
    } else if (delta > 0) {
        // One step off: hold it until the slider stops moving, then flush so we
        // always land on the exact value (including a hard 0 or 127).
        if (!slider_pending) {
            slider_pending  = true;
            slider_moved_at = timer_read();
        } else if (timer_elapsed(slider_moved_at) >= SLIDER_SETTLE_MS) {
            midi_send_cc(&midi_device, SLIDER_MIDI_CHANNEL, SLIDER_CC, value);
            slider_sent    = value;
            slider_pending = false;
        }
    } else {
        slider_pending = false;
    }
}

void housekeeping_task_user(void) {
    slider_task();
}
