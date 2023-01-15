/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// clang-format off
#include QMK_KEYBOARD_H
#include "keymap_swiss_de.h"
#include <stdio.h>
#include "oneshot.h"
#include "swapper.h"

enum layers {
  DEF, // including shifted keycodes
  NUM, // including shifted keycodes
  NAV,
  EXT,
  DWM,
};

#define LA_NUM MO(NUM)
#define LA_NAV MO(NAV)
#define LA_EXT MO(EXT)
#define LA_DWM MO(DWM)

#define S_LEFT   S(KC_LEFT) 
#define S_RGHT   S(KC_RGHT)
#define S_UP     S(KC_UP) 
#define S_DOWN   S(KC_DOWN) 
#define S_TAB    S(KC_TAB)

#define RALT_F1  RALT(KC_F1)
#define RALT_F2  RALT(KC_F2)
#define RALT_F3  RALT(KC_F3)
#define RALT_F4  RALT(KC_F4)
#define RALT_F5  RALT(KC_F5)
#define RALT_F6  RALT(KC_F6)
#define RALT_F7  RALT(KC_F7)
#define RALT_F8  RALT(KC_F8)
#define RALT_F9  RALT(KC_F9)

#define RALT_P   RALT(KC_P)
#define RALT_EN  RALT(KC_ENT)

#define RALT_H   RALT(KC_H)
#define RALT_J   RALT(KC_J)
#define RALT_K   RALT(KC_K)
#define RALT_L   RALT(KC_L)

#define RALT_t   RALT(KC_T)
#define RALT_M   RALT(KC_M)

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

const key_override_t lbrc_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_LBRC, CH_LCBR); // Shift [ is {
const key_override_t rbrc_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_RBRC, CH_RCBR); // Shift ] is }
const key_override_t pipe_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_PIPE, CH_EXLM); // Shift | is !
const key_override_t four_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_4,    CH_MINS); // Shift 4 is -
const key_override_t hash_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_HASH, CH_AT);   // Shift # is @
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, CH_RPRN); // Shift BSPC is )
const key_override_t dlr_key_override  = ko_make_basic(MOD_MASK_SHIFT, CH_DLR,  CH_LPRN); // Shift $ is (
const key_override_t slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_SLSH, CH_BSLS); // Shift / is '\'  

const key_override_t lNUM_comm_key_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, CH_LABK, 1 << NUM); // on layer NUM, Shift , is <
const key_override_t lNUM_dot_key_override  = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT,  CH_RABK, 1 << NUM); // on layer NUM, Shift . is >
const key_override_t lNUM_mins_key_override = ko_make_with_layers(MOD_MASK_SHIFT, CH_MINS, CH_DEG,  1 << NUM); // on layer NUM, Shift - is °

const key_override_t** key_overrides = (const key_override_t*[]){
    &lbrc_key_override,
    &rbrc_key_override,
    &pipe_key_override,
    &four_key_override,
    &hash_key_override,
    &bspc_key_override,
    &dlr_key_override,
    &slsh_key_override,

    &lNUM_comm_key_override,
    &lNUM_dot_key_override,
    &lNUM_mins_key_override,
    NULL
};

/*
  This keymap is intended to be used with the OS
  set to 'de_CH_latin1' keymap translation.
  I.e. the keyboard does send 'pre-mapped' keycodes to the OS,
  which then maps them via de_CH_latin1 to symbols.

  This means:
  - some of the base keycodes, and
  - especially shifted keycodes
  - some of the shifted keycodes got overridden ('key-override'),
    they are marked as 'ko' in the comments below

  will be maped to symbols by OS differently than would be the case with us keymap.
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3(
                               
     // qQ       wW       eE       rR       tT       zZ       uU       iI       oO       pP
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    CH_Z,    KC_U,    KC_I,    KC_O,    KC_P,

     // aA       sS       dD       fF       gG       hH       jJ       kK       lL       nN
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,

     // yY       xX       cC       vV       bB       nN       mM       ,;       .:       -_ 
        CH_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  CH_MINS,

                          LA_NAV, KC_LSFT, KC_CAPS,  KC_SPC,  LA_NUM,  LA_DWM
    ),

    [NUM] = LAYOUT_split_3x5_3(

     // üè       6&       5%       4- ko    '?       |! ko    /\ ko    [{ ko    ]} ko    
        CH_UDIA, KC_6,    KC_5,    KC_4,    CH_QUOT, CH_PIPE, CH_SLSH, CH_LBRC, CH_RBRC, KC_DEL, 

     // äà       3*       2"       1+       #@ ko    ~        0=       $( ko    BSPC) ko
        CH_ADIA, KC_3,    KC_2,    KC_1,    CH_HASH, CH_TILD, KC_0,    CH_DLR,  KC_BSPC, KC_ENT,
        
     // öé       9        8        7        ^`                         ,< ko    .> ko    -° ko
        CH_ODIA, KC_9,    KC_8,    KC_7,    CH_CIRC, XXXXXXX, OS_ALT,  KC_COMM, KC_DOT,  CH_MINS,

                          _______, _______, _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_split_3x5_3(

        SW_WIN,  KC_HOME, KC_END,  KC_MUTE, KC_VOLD, KC_VOLU, S_TAB,   KC_TAB,  XXXXXXX, QK_BOOT,

        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_PSCR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S_LEFT,  S_DOWN,  S_UP,    S_RGHT,  XXXXXXX,

                          _______, _______, _______, _______, _______, _______
    ),

    // currently unused (identical to DEF) 
    [EXT] = LAYOUT_split_3x5_3(

     // qQ       wW       eE       rR       tT       zZ       uU       iI       oO       pP
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    CH_Z,    KC_U,    KC_I,    KC_O,    KC_P,

     // aA       sS       dD       fF       gG       hH       jJ       kK       lL       nN
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,

     // yY       xX       cC       vV       bB       nN       mM       ,;       .:       -_ 
        CH_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  CH_MINS,

                          _______, _______, _______, _______, _______, _______
    ),

    [DWM] = LAYOUT_split_3x5_3(

        RALT_F1, RALT_F2, RALT_F3, RALT_F4, RALT_F5, RALT_F6, RALT_F7, RALT_F8, RALT_F9, RALT_P,

        KC_F11,  KC_F12,  RALT_t,  RALT_M,  RALT_B,  RALT_H,  RALT_J,  RALT_K,  RALT_L,  RALT_EN,

        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,

                          _______, _______, _______, _______, _______, _______
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NUM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NUM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, NUM, NAV, EXT);
}
