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
#include "features/achordion.h"

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
  FUN2,
  FUN3,
  SPC0,
};


// just for demo purposes..
/* const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_ALT, KC_BSPC,  KC_DEL);  // Shift bspc is del   */
/* const key_override_t** key_overrides = (const key_override_t*[]){ */
/*     &bspc_key_override, */
/*     NULL */
/* }; */

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
                                            LCTL_T(KC_L)   , LT(FUN0 ,KC_D) , LALT_T(KC_G)   , LALT_T(KC_H)   , LT(FUN0 ,KC_U) , RCTL_T(KC_O)   ,

                           LSFT_T(KC_I)   , LT(NUM0,KC_S)  , LT(SYM0,KC_T)  , LT(SYS0 ,KC_R) , LT(SYS0, KC_N) , LT(SYM0, KC_E) , LT(NUM0,KC_A)  , RSFT_T(KC_C)   ,

                                            XXXXXXX        ,KC_SPC          , OSL(ALA1)      , REPEAT         , OSL(ALA2)      , XXXXXXX
                           ),

    [ALA1] = LAYOUT_split_10(
                                            LSFT(KC_L)     , LSFT(KC_D)     , LSFT(KC_G)     , LSFT(KC_H)     , LSFT(KC_U)     , LSFT(CH_O)     ,

                           LSFT(KC_I)     , LSFT(KC_S)     , LSFT(KC_T)     , LSFT(KC_R)     , LSFT(KC_N)     , LSFT(KC_E)     , LSFT(KC_A)     , LSFT(CH_C)     ,
           
                                            _______        , _______        , _______        , _______        , MO(ALA3)                                                           , _______
                                            //_______        , _______        , _______        , _______        , OSL(ALA3)      , _______
                           ),
    
    [ALA2] = LAYOUT_split_10(
                                            KC_V           , KC_M           , KC_W           , KC_F           , CH_COMM        , CH_Z           ,               

                           KC_Q           , KC_J           , LCTL_T(KC_K)   , LALT_T(KC_P)   , RALT_T(KC_B)   , LCTL_T(CH_DOT) , KC_X           , CH_Y           ,

                                            //_______        , _______        , OSL(ALA3)       , _______        , _______        , _______                        
                                            _______        , _______        , MO(ALA3)       , _______        , _______        , _______                        
                           ),
 
    [ALA3] = LAYOUT_split_10(
                                            LSFT(KC_V)     , LSFT(KC_M)     , LSFT(KC_W)     , LSFT(KC_F)     , CH_SCLN        , LSFT(CH_Z)     ,

                            LSFT(KC_Q)    , LSFT(KC_J)     , LSFT(KC_K)     , LSFT(KC_P)     , LSFT(KC_B)     , CH_COLN        , LSFT(KC_X)     , LSFT(CH_Y)     ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [SYS0] = LAYOUT_split_10(
                                            KC_SCRL        , XXXXXXX        , XXXXXXX        , KC_TAB         , KC_LEFT        , KC_RIGHT       ,

                            KC_LSFT       , KC_LCTL        , KC_LALT        , LCTL(KC_G)     , KC_DOWN        , KC_UP          , KC_BSPC        , KC_ENT         ,

                                            _______        , MO(SYS1)       , _______        , _______        , MO(SYS1)       , _______
                           ),
    

    [SYS1] = LAYOUT_split_10(
                                            KC_PSCR        , XXXXXXX        , XXXXXXX        , LSFT(KC_TAB)   , KC_HOME        , KC_END         ,

                            KC_LSFT       , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_PGDN        , KC_PGUP        , KC_DEL         , LSFT(KC_ENT)   ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    
    [NUM0] = LAYOUT_split_10(
                                            CH_EGRV        , CH_AGRV        , CH_EACU        , KC_4           , KC_5           , KC_6           , 

                           XXXXXXX        , CH_ODIA        , CH_ADIA        , CH_UDIA        , KC_1           , KC_2           , KC_3           , KC_0          ,

                                            _______        , MO(NUM1)       , _______        , _______        , MO(NUM1)       , _______
                           ),
    
    [NUM1] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_7           , KC_8           , KC_9           ,

                           XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , CH_LABK        , CH_RABK        , KC_BSPC        , KC_ENT         ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [SYM0] = LAYOUT_split_10(
                                            CH_AT          , CH_PIPE        , CH_QUES        , CH_PERC        , CH_LPRN        , CH_RPRN        , 

                           CH_EURO        , CH_TILD        , CH_QUOT        , CH_DQUO        , CH_MINS        , CH_SLSH        , CH_ASTR        , CH_PLUS        , 

                                            _______        , MO(SYM1)       , _______        , _______        , MO(SYM1)       , _______
                           ),
    
    [SYM1] = LAYOUT_split_10(
                                            XXXXXXX        , CH_HASH        , CH_EXLM        , CH_AMPR        , CH_LCBR        , CH_RCBR        ,

                           CH_DLR         , CH_BSLS        , CH_GRV         , CH_CIRC        , CH_UNDS        , CH_LBRC        , CH_RBRC        , CH_EQL         ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),

    [FUN0] = LAYOUT_split_10(
                                             LCTL_T(KC_F6) , KC_F5        ,LSFT_T(KC_F4) ,RSFT_T(ALGR(KC_F4)) ,ALGR(KC_F5) ,RCTL_T(ALGR(KC_F6)) , 

                           XXXXXXX        , KC_F3          , KC_F2          , KC_F1          , ALGR(KC_F1)    , ALGR(KC_F2)    , ALGR(KC_F3)    , ALGR(KC_P)     ,

                                            _______        , MO(FUN2)       , _______        , _______        , MO(FUN1)       , _______
                           ),

    [FUN1] = LAYOUT_split_10(
                                            LCTL_T(KC_F9)  , KC_F8        ,LSFT_T(KC_F7) ,RSFT_T(ALGR(KC_B))  , ALGR(KC_H) ,RCTL_T(ALGR(KC_L))  ,

                           XXXXXXX        , KC_F12         , KC_F11         , KC_F10         , ALGR(KC_J)     , ALGR(KC_K)     , ALGR(KC_ENT)   , ALGR(KC_P)     ,

                                            _______        , MO(FUN3)       , _______        , _______        , _______        , _______
                           ),

    [FUN2] = LAYOUT_split_10(
                                            KC_LCTL        , XXXXXXX        , KC_LSFT        ,ALGR(KC_F7)     , ALGR(KC_F8) ,ALGR(KC_F9) ,                     

                           XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,ALGR(KC_F10)  , ALGR_T(KC_F11) , ALGR_T(KC_F12)  , KC_LGUI       ,    

                                            _______        , _______        , _______        , _______        , MO(FUN3)       , _______        
                           ),
                                            
    [FUN3] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , ALGR(KC_I)     , ALGR(KC_D)     , 

                           ALGR(LSFT(KC_Q)),XXXXXXX        , XXXXXXX        , XXXXXXX        , ALGR(KC_M)     , ALGR(KC_T)     , XXXXXXX      ,ALGR(LSFT(KC_C)) , 

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),

    [SPC0] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        ,

                           XXXXXXX        , XXXXXXX        , XXXXXXX        , XXXXXXX        , KC_ENT         , KC_BSPC        , KC_DEL         , XXXXXXX        , 

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
};
                               

const uint16_t PROGMEM esc_combo[] = {LT(SYS0 ,KC_R) , LT(SYS0, KC_N), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(esc_combo, KC_ESC),
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      ;;        case LT(SPC0, KC_SPC):
      ;;      return TAPPING_TERM + 1000;
        default:
            return TAPPING_TERM;
    }
}

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
    if (!process_achordion(keycode, record)) {
      return false;
    }

    // It's important to update the mod variables *after* calling process_repeat_key, or else
    // only a single modifier from the previous key is repeated (e.g. Ctrl+Shift+T then Repeat produces Shift+T)
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    switch (keycode) {

    case RSFT_T(ALGR(KC_F4)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_F4));
        return false;        // Return false to ignore further processing of key
      }
      
    case RCTL_T(ALGR(KC_F6)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_F6));
        return false;        // Return false to ignore further processing of key
      }
      break;

    case RSFT_T(ALGR(KC_B)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_B));
        return false;        // Return false to ignore further processing of key
      }
      break;
      
    case RCTL_T(ALGR(KC_L)):
      if (record->tap.count && record->event.pressed) {
        tap_code16(ALGR(KC_L));
        return false;        // Return false to ignore further processing of key
      }
      break;
    }
    return true;
};

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they are on the same hand.
  /* switch (tap_hold_keycode) { */
  /*   case HOME_A:  // A + U. */
  /*     if (other_keycode == HOME_U) { return true; } */
  /*     break; */

  /*   case HOME_S:  // S + H and S + G. */
  /*     if (other_keycode == HOME_H || other_keycode == KC_G) { return true; } */
  /*     break; */
  /* } */

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3 /*thumbs rows*/) {
    return true;
  }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}
