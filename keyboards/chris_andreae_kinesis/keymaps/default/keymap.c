// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_F7,     KC_F8,          KC_W,      KC_2,             KC_EQUAL,    KC_TAB,       KC_CAPS_LOCK ,
        KC_F1,  KC_F6,     KC_F5,          KC_S,      KC_X,             KC_1,         KC_Q,         KC_LSFT   ,
        KC_F2,  KC_F3,     KC_F4,          KC_NO,             KC_NONUS_BACKSLASH, KC_A,         KC_Z,         KC_GRAVE ,
        KC_5,   KC_B,      KC_R,           KC_4,      KC_LEFT,          KC_C,         KC_D,         KC_NO               ,
        KC_T,   KC_G,      KC_F,           KC_V,      KC_RIGHT,         KC_3,         KC_E,         KC_NO               ,
        KC_NO,          KC_NO,             KC_NO,                  KC_RCTL, KC_PGUP,          KC_LCTL,    KC_END,       KC_NO               ,
        KC_NO,          KC_NO,             KC_NO,                  KC_ENTER,  KC_RALT,         KC_BACKSPACE, KC_LALT,     KC_NO               ,
        KC_NO,          KC_NO,             KC_NO,                  KC_PGDN,   KC_SPACE,         KC_HOME,      KC_DELETE,    KC_NO               ,
        KC_Y,   KC_H,      KC_J,           KC_M,      KC_UP,            KC_8,         KC_I,         KC_NO               ,
        KC_6,   KC_N,      KC_U,           KC_7,      KC_DOWN,          KC_COMMA,     KC_K,         KC_NO               ,
        KC_F9,  KC_NO, QK_BOOTLOADER,     KC_NO,             KC_LEFT_BRACKET,       KC_SEMICOLON, KC_SLASH,     KC_RIGHT_BRACKET  ,
        KC_F10, KC_PAUSE,  KC_SCROLL_LOCK,  KC_L,      KC_DOT,        KC_0,         KC_P,         KC_RSFT   ,
        KC_F11, KC_F12,    KC_PRINT_SCREEN, KC_O,      KC_9,             KC_MINUS,    KC_BACKSLASH, KC_QUOTE
    )
};
