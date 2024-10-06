/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

// #include "keymap_russian.h"
// #include "keymap_us_international.h"
// #include "sendstring_us_international.h"
// #include "keymap_uk.h"
// #include "sendstring_uk.h"

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_FUN,
    LAYER_SYM,
    LAYER_MEDIA,
    LAYER_POINTER,
};

// функция tab dance https://docs.qmk.fm/features/tap_dance#example-4

enum {
    TD_L_LANG = 0,
};

// Определяем пользовательский keycode
enum custom_keycodes {
    M_CTRL_SHIFT_V = SAFE_RANGE, // Макрос для Ctrl+Shift+V
    M_HIGLIGHT_ALL,
    M_COPY_WORD,
    M_W_SHIFT_S, // print screen
    M_3_CLICK, // выделение абзаца
    M_SEND_COMMA,
    M_DOPLICATE_PAGE,
    M_COPY_PAGE_URL
};

enum unicode_names {
  U_QUEST_SYM,
};

const uint32_t unicode_map[] PROGMEM = {
  [U_QUEST_SYM]   = 0x003f,  // ?
};

#define U_QUEST UM(U_QUEST_SYM)

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// Layers
#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define FUN MO(LAYER_FUN)
#define MEDIA MO(LAYER_MEDIA)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// Ctrl-Tab
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Short
#define SC_NWIN LCTL(KC_N)
#define SC_NTAB LCTL(KC_T)
#define SC_CLOSE LCTL(KC_W)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,          KC_Y,  KC_U,    KC_I,  KC_O,   KC_P,     KC_LBRC,
  // ├───────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,  KC_J,    KC_K,  KC_L,  KC_SCLN,   KC_QUOT,
  // ├───────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       SC_LCPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,  KC_M, KC_COMM,  KC_DOT, ALT_T(KC_SLSH), KC_RBRC,
  // ╰───────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
            LWIN_T(KC_BSPC),  LT(LAYER_SYM, KC_SPC), MO(LOWER),   LT(RAISE, KC_TAB),  LT(FUN, KC_ENT)
  //          ╰──────────────────────────────────────────────────╯ ╰───────────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭────────────────────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
            POINTER_DEFAULT_DPI_FORWARD, XXXXXXX, KC_WH_D, KC_WH_U, QK_BOOT, EE_CLR,               KC_LBRC,  KC_7,  KC_8,  KC_9,  KC_RBRC,  XXXXXXX,
  // ├────────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       POINTER_DEFAULT_DPI_REVERSE, DRAGSCROLL_MODE, KC_BTN4, KC_BTN5, M_COPY_WORD, M_3_CLICK,     KC_EQL,  KC_4, KC_5,  KC_6, KC_MINS, KC_LSFT,
  // ├────────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
                        KC_LCTL, KC_BTN1, KC_BTN2, KC_BTN3, SNIPING,  XXXXXXX,                     KC_0,  KC_1,  KC_2,  KC_3,  KC_PSLS,  KC_LALT,
  // ╰────────────────────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                                                   XXXXXXX, XXXXXXX, _______,      _______, XXXXXXX
  //                                                             ╰────────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    C(S(KC_T)), SC_CLOSE, S(KC_B), M_COPY_PAGE_URL, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TAB, KC_LEFT,   KC_DOWN, KC_UP, KC_RGHT, XXXXXXX,     SC_NTAB, M_DOPLICATE_PAGE, RCS_TAB, CTL_TAB, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    SC_NWIN, KC_TAB,  KC_LCTL, KC_LSFT, KC_LALT, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, MEDIA, FUN,          _______, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

    [LAYER_FUN] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_F7, KC_F8, KC_F9, KC_F12, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, C(KC_C), C(KC_V), C(KC_X), C(KC_A), XXXXXXX,     XXXXXXX, KC_F4, KC_F5, KC_F6, KC_F11, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LALT, A(KC_F4), C(KC_Z), C(S(KC_Z)),  C(S(KC_Z)), XXXXXXX,   XXXXXXX, KC_F1,  KC_F2, KC_F3, KC_F10, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_BSPC
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYM] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_ASTR, KC_GRV, KC_DLR, KC_PERC, KC_AT, KC_CIRC,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_EXLM, KC_LCBR, KC_AMPR, KC_PIPE, KC_RCBR, KC_COLN,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_QUES, KC_LPRN, KC_LT, KC_GT, KC_RPRN, KC_UNDS,       U_QUEST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MEDIA] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX,    XXXXXXX, KC_WSCH, KC_WHOM, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_WBAK, XXXXXXX, KC_WFWD, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_S, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, EE_CLR,  QK_BOOT,    QK_BOOT, EE_CLR,  SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  TG(0), TG(1), TG(2),             TG(3), TG(0)
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};

//////////////// CUSTOM ///////////////

const uint16_t PROGMEM CB_PRINT_SCREEN[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM CB_PASTE_WITHOUT_FROMATTING[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM CB_HIGLIGHT_ALL[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM CB_CAPS_WORD[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM CB_STOP_TRACK[] = {KC_MPRV, KC_MNXT, COMBO_END};
const uint16_t PROGMEM CB_COMMA[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM CB_DOT[] = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM CB_SWITCH_LANG[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(CB_PRINT_SCREEN, KC_PSCR),
    COMBO(CB_PASTE_WITHOUT_FROMATTING, M_CTRL_SHIFT_V), // keycodes with modifiers are possible too!
    COMBO(CB_HIGLIGHT_ALL, M_HIGLIGHT_ALL),
    COMBO(CB_CAPS_WORD, CW_TOGG),
    COMBO(CB_STOP_TRACK, KC_MPLY),
    COMBO(CB_COMMA, M_SEND_COMMA),
    COMBO(CB_DOT, KC_DOT),
    COMBO(CB_SWITCH_LANG, A(KC_LSFT)),
};

// Обработка Tap Dance
void dance_abc_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_L);
            break;
        case 2:
            tap_code16(A(KC_LSFT));
            break;
    }
}

// Обработка удержания
void dance_abc_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_N);
    }
    else {
        unregister_code(KC_N);
    }
}

// Определение Tap Dance
tap_dance_action_t tap_dance_actions[] = {
    [TD_L_LANG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_abc_finished, dance_abc_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_CTRL_SHIFT_V:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_V);
            } else {
                unregister_code(KC_V);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            break;
        case M_W_SHIFT_S:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_LSFT);
                register_code(KC_S);   
            } else {
                unregister_code(KC_LWIN);
                unregister_code(KC_LSFT);
                unregister_code(KC_S);
            }
            break; 
        case M_HIGLIGHT_ALL: 
            if (record->event.pressed) {
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
            }
            break; 
        case M_COPY_WORD: 
            if (record->event.pressed) {
                tap_code(KC_BTN1);
                tap_code(KC_BTN1);
                tap_code16(C(KC_C));
            }
            break;         
        case M_3_CLICK:
            if (record->event.pressed) {
                tap_code(KC_BTN1);
                tap_code(KC_BTN1);
                tap_code(KC_BTN1);
                tap_code16(C(KC_C));
            }
            break;
        case M_SEND_COMMA:
            if (record->event.pressed) { // to do
                SEND_STRING(",");
            }
            break;
        case M_DOPLICATE_PAGE:
            if (record->event.pressed) {
                tap_code16(A(KC_D));
                tap_code16(A(KC_ENT));
            }
            break;  
        case M_COPY_PAGE_URL:
            if (record->event.pressed) {
                tap_code16(A(KC_D));
                tap_code16(C(KC_C));
                tap_code(KC_ESC);
            }
            break;                    
    }
    return true;
}

//////////////// END CUSTOM ////////////////

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
