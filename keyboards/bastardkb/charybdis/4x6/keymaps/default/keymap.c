/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYMBL,
    LAYER_NUMAR,
    LAYER_POINTER,
};

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

#define SYMBL MO(LAYER_SYMBL)
#define NUMAR MO(LAYER_NUMAR)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#define MT_SFE LSFT_T(KC_E)
#define MT_SFN LSFT_T(KC_N)
#define MT_CTA LCTL_T(KC_A)
#define MT_CTR LCTL_T(KC_R)
#define MT_ALI LALT_T(KC_I)
#define MT_ALT LALT_T(KC_T)
#define MT_GUO LGUI_T(KC_O)
#define MT_GUS LGUI_T(KC_S)

#define PT_U LT(LAYER_POINTER, KC_U)
#define PT_D LT(LAYER_POINTER, KC_D)
#define CKC_EUR RALT(KC_E)     // €
#define CKC_UNS LSFT(KC_SLASH) // _
#define CKC_LBK RALT(KC_8)     // [
#define CKC_RBK RALT(KC_9)     // ]
#define CKC_EXC LSFT(KC_1)     // !
#define CKC_RTR LSFT(KC_NUBS)  // >
#define CKC_EQL LSFT(KC_0)     // =
#define CKC_AMP LSFT(KC_6)     // &
#define CKC_PAR LSFT(KC_3)     // §
#define CKC_BSL RALT(KC_MINS)  // backslash
#define CKC_SLH LSFT(KC_7)     // /
#define CKC_LBC RALT(KC_7)     // {
#define CKC_RBC RALT(KC_0)     // }
#define CKC_AST LSFT(KC_RBRC)  // *
#define CKC_QST LSFT(KC_MINS)  // ?
#define CKC_LPR LSFT(KC_8)     // (
#define CKC_RPR LSFT(KC_9)     // )
#define CKC_CLN LSFT(KC_DOT)   // :
#define CKC_AT  RALT(KC_Q)     // @
#define CKC_DLR LSFT(KC_4)     // $
#define CKC_PIP RALT(KC_NUBS)  // |
#define CKC_TLD RALT(KC_RBRC)  // ~
#define CKC_GRV LSFT(KC_EQL)   // `
#define CKC_PRC LSFT(KC_5)     // %
#define CKC_QOT LSFT(KC_2)     // "
#define CKC_APO LSFT(KC_BSLS)  // '
#define CKC_SMC LSFT(KC_COMMA) // ;

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

    // clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PMNS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_X,    KC_V,    KC_L,    KC_C,    KC_W,       KC_K,    KC_H,    KC_G,    KC_F,    KC_Q, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    PT_U,  MT_ALI,  MT_CTA,  MT_SFE,  MT_GUO,     MT_GUS,  MT_SFN,  MT_CTR,  MT_ALT,    PT_D,    KC_Z,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL, KC_LBRC, KC_SCLN, KC_QUOT,    KC_P,    KC_Y,       KC_B,    KC_M, KC_COMM,  KC_DOT,    KC_J, KC_LGUI,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_LALT, KC_SPC,   SYMBL,      SYMBL, KC_BSPC,
                                            KC_ENT,   NUMAR,      NUMAR
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYMBL] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       RGB_TOG, RGB_MOD,RGB_RMOD, XXXXXXX, XXXXXXX,  KC_EQL,    CKC_GRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_F24, CKC_EUR, CKC_UNS, CKC_LBK, CKC_RBK,  KC_GRV,    CKC_EXC, KC_NUBS, CKC_RTR, CKC_EQL, CKC_AMP, CKC_PAR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, CKC_BSL, CKC_SLH, CKC_LBC, CKC_RBC, CKC_AST,    CKC_QST, CKC_LPR, CKC_RPR, KC_SLSH, CKC_CLN,  CKC_AT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_BSLS, CKC_DLR, CKC_PIP, CKC_TLD, CKC_GRV,    KC_RBRC, CKC_PRC, CKC_QOT, CKC_APO, CKC_SMC, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, XXXXXXX,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NUMAR] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL, KC_PGDN,    KC_MNXT, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, KC_PMNS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,    KC_MPLY, KC_KP_4, KC_KP_5, KC_KP_6, KC_PDOT, KC_COMM,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,  KC_ESC,  KC_TAB,  KC_INS,  KC_ENT, KC_UNDO,    KC_MPRV, KC_KP_1, KC_KP_2, KC_KP_3, KC_PAST, KC_PSLS,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, KC_LGUI,    KC_KP_0, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD,    RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX,  KC_NUM, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD,  KC_NUM, XXXXXXX, XXXXXXX, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, DRGSCRL, KC_WBAK, KC_WFWD, XXXXXXX,    XXXXXXX, KC_WBAK, KC_WFWD, DRGSCRL, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, XXXXXXX, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           DRGSCRL, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

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
