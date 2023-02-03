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
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_swiss_de.h"
#include <stdio.h>

enum keycodes {
    REPEAT = SAFE_RANGE,
};

enum layers {
  ALA0,
  ALA1,
  ALA2,
  ALA3,
  SYS0,
  SYS1,
  NUM0,
  NUM1,
  SYM0,
  SYM1,
  FUN0,
  FUN1,
};


const key_override_t left_key_override = ko_make_basic(MOD_MASK_ALT, KC_LEFT,  KC_HOME); // Shift Left is Home
const key_override_t down_key_override = ko_make_basic(MOD_MASK_ALT, KC_DOWN,  KC_PGDN); // Shift down is PgDn
const key_override_t up_key_override   = ko_make_basic(MOD_MASK_ALT, KC_UP,    KC_PGUP); // Shift up is PgUp 
const key_override_t right_key_override= ko_make_basic(MOD_MASK_ALT, KC_RIGHT, KC_END);  // Shift right is End 
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_ALT, KC_BSPC,  KC_DEL);  // Shift bspc is del  


const key_override_t** key_overrides = (const key_override_t*[]){
    &left_key_override,
    &down_key_override,
    &up_key_override,
    &right_key_override,
    &bspc_key_override,

    NULL
};

#define LAYOUT_split_9( \
       L11, L12, L13,                     R11, R12, R13,      \
  L20, L21, L22, L23,                     R21, R22, R23, R24, \
                      L31, L32, R31, R32 \
  ) \
  { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, }, \
    { KC_NO, KC_NO, L11, L12, L13, KC_NO }, \
    { KC_NO, L20, L21, L22, L23, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, L31, L32 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, }, \
    { KC_NO, KC_NO, R13, R12, R11, KC_NO }, \
    { KC_NO, R24, R23, R22, R21, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, R32, R31 }  \
  }

#define LAYOUT_split_10( \
       L11, L12, L13,                     R11, R12, R13,      \
  L20, L21, L22, L23,                     R21, R22, R23, R24, \
                 L30, L31, L32, R31, R32, R33                 \
  ) \
  { \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, }, \
    { KC_NO, KC_NO, L11, L12, L13, KC_NO }, \
    { KC_NO, L20, L21, L22, L23, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, L30, L31, L32 },        \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, }, \
    { KC_NO, KC_NO, R13, R12, R11, KC_NO }, \
    { KC_NO, R24, R23, R22, R21, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, R33, R32, R31 }  \
  }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALA0] = LAYOUT_split_10(
                                            LCTL_T(KC_L)   , LT(FUN0 ,KC_G) , LALT_T(KC_D)   , LALT_T(KC_H)   , LT(FUN0 ,KC_U) , RCTL_T(KC_O)   ,

                           LSFT_T(KC_I)   , LT(NUM0,KC_S)  , LT(SYM0,KC_R)  , LT(SYS0 ,KC_T) , LT(SYS0, KC_N) , LT(SYM0, KC_E) , LT(NUM0,KC_A)  , KC_C           ,

                                            REPEAT         , KC_SPC         , OSL(ALA2)      , OSL(ALA3)      , OSL(ALA1)      , XXXXXXX
                           ),

    [ALA1] = LAYOUT_split_10(
                                            KC_V           , KC_W           , KC_M           , KC_F           , CH_DOT ,         CH_Z           ,

                           KC_Q           , KC_J           , LCTL_T(KC_P)   , LALT_T(KC_K)   , RALT_T(KC_B)   , LCTL_T(CH_COMM), KC_X           , CH_Y           ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [ALA2] = LAYOUT_split_10(
                                            LSFT(KC_L)     , LSFT(KC_G)     , LSFT(KC_D)     , LSFT(KC_H)     , LSFT(KC_U)     , LSFT(CH_O)     ,

                           LSFT(KC_I)     , LSFT(KC_S)     , LSFT(KC_R)     , LSFT(KC_T)     , LSFT(KC_N)     , LSFT(KC_E)     , LSFT(KC_A)     , LSFT(CH_C)     ,

                                            _______        , _______        , _______        , _______        , _______         , _______
                           ),
 
    [ALA3] = LAYOUT_split_10(
                                            LSFT(KC_V)     , LSFT(KC_W)     , LSFT(KC_M)     , LSFT(KC_F)     , CH_COLN        , LSFT(CH_Z)     ,

                            LSFT(KC_Q)    , LSFT(KC_J)     , LSFT(KC_P)     , LSFT(KC_K)     , LSFT(KC_B)     , CH_SCLN        , LSFT(KC_X)     , LSFT(CH_Y)     ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [SYS0] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX        , LCTL(KC_G)     ,  KC_TAB        , KC_UP          , KC_BSPC        ,

                            KC_LSFT       , KC_LCTL        , KC_LALT        , KC_ESC         ,  KC_LEFT       , KC_DOWN        , KC_RIGHT       , KC_ENT         ,

                                            _______        , MO(SYS1)       , _______        , _______        , MO(SYS1)       , _______
                           ),
    
    
    [SYS1] = LAYOUT_split_10(
                                            KC_PSCR        , XXXXXXX        , XXXXXXX        , LSFT(KC_TAB)   , KC_PGUP        , KC_DEL         ,

                            KC_LSFT       , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_HOME        , KC_PGDN        , KC_END         , LSFT(KC_ENT)   ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    
    [NUM0] = LAYOUT_split_10(
                                            CH_EGRV        , CH_AGRV        , CH_EACU        , KC_4           , KC_5           , KC_6           , 

                           XXXXXXX        , CH_ODIA        , CH_ADIA        , CH_UDIA        , KC_1           , KC_2           , KC_3           , CH_MINS        ,

                                            _______        , MO(NUM1)       , _______        , _______        , MO(NUM1)       , _______
                           ),
    
    [NUM1] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX        , XXXXXXX        , CH_PLUS        , CH_ASTR        , CH_EQL         ,

                           XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_7           , KC_8           , KC_9           ,  KC_0          ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [SYM0] = LAYOUT_split_10(
                                            CH_AT          , CH_PIPE        , CH_PERC        , CH_LPRN        , CH_RPRN        , CH_UNDS        , 

                           CH_DLR         , CH_QUOT        , CH_DQUO        , CH_TILD        , CH_SLSH        , CH_QUES        , CH_AMPR        , CH_EXLM        ,

                                            _______        , MO(SYM1)       , _______        , _______        , MO(SYM1)       , _______
                           ),
    
    [SYM1] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX        , CH_HASH        , CH_LCBR        , CH_RCBR        , CH_LABK        ,

                           CH_EURO        , CH_GRV         , CH_CIRC        , CH_BSLS        , CH_LBRC        , CH_RBRC        , CH_RABK        , XXXXXXX        ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),

    [FUN0] = LAYOUT_split_10(
                                        LCTL_T(ALGR(KC_H)) , ALGR(KC_L)  ,LSFT_T(ALGR(KC_B)) , ALGR(KC_F4)    , ALGR(KC_F5)    , ALGR(KC_F6)    , 

                           ALGR(KC_ENT)   , ALGR(KC_P)     , ALGR(KC_M)     , ALGR(KC_T)     , ALGR(KC_F1)    , ALGR(KC_F2)    , ALGR(KC_F3)    , KC_LGUI        ,

                                            _______        , MO(FUN1)       , _______        , _______        , MO(FUN1)       , _______
                           ),
    
    [FUN1] = LAYOUT_split_10(
                                        LCTL_T(ALGR(KC_D)) , ALGR(KC_I)     , KC_LSFT        , KC_F10         , KC_F11         , KC_F12         ,

                         ALGR(LSFT(KC_C)) , XXXXXXX        , ALGR(KC_K)     , ALGR(KC_J)     , ALGR(KC_F7)    , ALGR(KC_F8)    , ALGR(KC_F9)    , ALGR(LSFT(KC_Q)),

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
};
                               

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;

// Initialize variables holding the bitfield
// representation of active modifiers.
uint8_t mod_state;
uint8_t oneshot_mod_state;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != REPEAT) {
        // Early return when holding down a pure layer key
        // to retain modifiers
        switch (keycode) {
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                return;
        }
        last_modifier = oneshot_mod_state > mod_state ? oneshot_mod_state : mod_state;
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed) {
                    last_keycode = GET_TAP_KC(keycode);
                }
                break;
            default:
                if (record->event.pressed) {
                    last_keycode = keycode;
                }
                break;
        }
    } else { // keycode == REPEAT
        if (record->event.pressed) {
            register_mods(last_modifier);
            register_code16(last_keycode);
        } else {
            unregister_code16(last_keycode);
            unregister_mods(last_modifier);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_repeat_key(keycode, record);
    // It's important to update the mod variables *after* calling process_repeat_key, or else
    // only a single modifier from the previous key is repeated (e.g. Ctrl+Shift+T then Repeat produces Shift+T)
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    switch (keycode) {

    case RALT_T(ALGR(KC_T)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_T));
        return false;        // Return false to ignore further processing of key
      }
      break;

    case RALT_T(ALGR(KC_K)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_K));
        return false;        // Return false to ignore further processing of key
      }
      break;

    case LSFT_T(ALGR(KC_P)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_P));
        return false;        // Return false to ignore further processing of key
      }
      break;
    }
    return true;
};
