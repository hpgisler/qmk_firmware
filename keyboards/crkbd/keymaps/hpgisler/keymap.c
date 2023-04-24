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
    MODS,
};

enum layers {
  ALA0,
  ALA1,
  ALA2,
  ALA3,
  ALA4,
  NAS0,
  NAS1,
  NAS2,
  FUN0,
  FUN1,
  FUN2,
  MODL,
  MODR,
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

// REPEAT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALA0] = LAYOUT_split_10(
                                            KC_R           , KC_H           , KC_D           , KC_U           , KC_O           , KC_A,

                            OSM(MOD_LSFT) , KC_N           , KC_S           , KC_T           , KC_SPC         , KC_E           , KC_I           , CTL_T(KC_ESC) /* KC_CAPS */ /*OSM(MOD_LCTL)*/ ,

                                            XXXXXXX        , OSL(ALA2)      , OSL(NAS0)      , OSL(FUN0)      , OSL(ALA1)      , XXXXXXX
                           ),

    [ALA1] = LAYOUT_split_10(
                                            KC_X           , KC_M           , KC_B           , CH_UDIA        , CH_ODIA        , CH_ADIA        ,   

                            _______       , KC_L           , KC_F           , KC_G           , KC_C           , OSM(MOD_LALT)  , CH_MINS        , _______         , 
           
                                            _______        , MO(ALA3)       , MO(NAS1)       , _______        , _______        , _______
                           ),
    
    [ALA2] = LAYOUT_split_10(
                                            KC_J           , KC_K           , KC_V           , KC_Q           , CH_QUES        , CH_SLSH        ,               

                            _______       , KC_W           , CH_Z           , KC_P           , CH_Y           , CH_COMM        , CH_DOT         , _______         ,

                                            _______        , _______        , _______        , MO(FUN1)       , MO(ALA4)       , _______                        
                           ),
    
    [ALA3] = LAYOUT_split_10(
                                            CH_PLUS        , CH_LABK        , CH_RABK        , CH_LCBR        , CH_RCBR        , XXXXXXX        ,

                            _______       , CH_AT          , CH_LBRC        , CH_RBRC        , CH_LPRN        , CH_RPRN        , CH_DQUO        , _______        ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),

    [ALA4] = LAYOUT_split_10(
                                            KC_1           , KC_2           , KC_3           , KC_4           , KC_5           , KC_6           ,

                            _______       , KC_7           , KC_8           , KC_9           , KC_0           , CH_ASTR        , CH_QUOT        , _______        ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),


    [NAS0] = LAYOUT_split_10(
                                            CH_PERC        , CH_AMPR       , CH_CIRC         , KC_BSPC        , KC_LEFT        , KC_RIGHT       ,

                            _______       , MODS           , CH_TILD       , KC_TAB          , KC_DOWN        , KC_UP          , KC_ENT         , _______        , 

                                            _______        , _______       , _______         , MO(NAS2)       , MO(NAS1)       , _______
                           ),
    

    [NAS1] = LAYOUT_split_10(
                                            CH_EURO        , CH_DLR        , CH_PND          , KC_DEL         , KC_HOME        , KC_END         ,

                            _______       , CH_DEG         , CH_HASH       , CH_PIPE         , KC_PGDN        , KC_PGUP        , CH_EQL         , _______        ,

                                            _______        , _______       , _______         , _______        , _______        , _______
                           ),


    [NAS2] = LAYOUT_split_10(
                                            XXXXXXX        , XXXXXXX       , KC_PSCR         , CH_SECT        , XXXXXXX        , CH_AGRV         ,

                            _______       , XXXXXXX        , XXXXXXX       , KC_SCRL         , CH_CCED        , CH_EACU        , CH_EGRV         , _______        ,

                                            _______        , _______       , _______         , _______        , _______        , _______
                           ),


    [FUN0] = LAYOUT_split_10(
                                            ALGR(KC_F1)    , ALGR(KC_F2)   , ALGR(KC_F3)     , ALGR(KC_F4)    , ALGR(KC_F5)    , ALGR(KC_F6)    ,

                            _______       , ALGR(KC_F7)    , ALGR(KC_F8)   , ALGR(KC_F9)     , ALGR(KC_J )    , ALGR(KC_K )    , ALGR(KC_P )    , _______        ,

                                            _______        , MO(FUN1)      , MO(FUN2)        , _______        , _______        , _______
                           ),


    [FUN1] = LAYOUT_split_10(
                                           ALGR(LSFT(KC_Q)),ALGR(LSFT(KC_C)), KC_LGUI        , ALGR(KC_B)     , ALGR(KC_H)     , ALGR(KC_L)     ,

                            _______       , _______        , _______        , KC_CAPS        , ALGR(KC_I)     , ALGR(KC_D)     , _______        , _______      ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),

    
    [FUN2] = LAYOUT_split_10(
                                            KC_F1          , KC_F2         , KC_F3           , KC_F4          , KC_F5          , KC_F6          ,

                            _______       , KC_F7          , KC_F8         , KC_F9           , KC_F10         , KC_F11         , KC_F12         , _______        ,

                                            _______        , _______       , _______         , _______        , _______        , _______
                           ),

    
    [MODL] = LAYOUT_split_10(
                                            KC_RALT        , _______       , KC_LGUI         , _______        , _______        , _______        ,

                            _______       , KC_LALT        , KC_LSFT       , KC_LCTL         , _______        , _______        , _______        , TG(MODL)       ,

                                            _______        , _______       , _______         , _______        , _______        , _______
                            ),

    
    [MODR] = LAYOUT_split_10(
                                            _______        , _______       , _______         , KC_RGUI        , _______        , KC_RALT        ,

                            _______       , _______        , _______       , _______         , KC_RCTL        , KC_RSFT        , KC_LALT        , TG(MODR)       ,

                                            _______        , _______       , _______         , _______        , _______        , _______
                            )
};
                               
// SHIFT overrides
// ===============

// ALA0
// ----

// ALA1
// ----
const key_override_t ko_ala1_0  = ko_make_basic(MOD_MASK_SHIFT, CH_MINS, CH_UNDS); // - : _

// ALA2
// ----
const key_override_t ko_ala2_0  = ko_make_basic(MOD_MASK_SHIFT, CH_QUES, CH_EXLM); // ? : !
const key_override_t ko_ala2_1  = ko_make_basic(MOD_MASK_SHIFT, CH_SLSH, CH_BSLS); // / : \ .
const key_override_t ko_ala2_2  = ko_make_basic(MOD_MASK_SHIFT, CH_COMM, CH_SCLN); // , : ;
const key_override_t ko_ala2_3  = ko_make_basic(MOD_MASK_SHIFT, CH_DOT , CH_COLN); // . : :

// ALA3
// ----

// ALA4
// ----


// NAS0
// ----

// NAS1
// ----

// NAS2
// ----


// FUN0
// ----
const key_override_t ko_fun0_0 = ko_make_basic(MOD_MASK_SHIFT, ALGR(KC_J ), ALGR(KC_M)  ); // dwm next : dwm monocle 
const key_override_t ko_fun0_1 = ko_make_basic(MOD_MASK_SHIFT, ALGR(KC_K ), ALGR(KC_T)  ); // dwm prev : dwm tiled 
const key_override_t ko_fun0_2 = ko_make_basic(MOD_MASK_SHIFT, ALGR(KC_P ), ALGR(KC_ENT)); // dwm new : dwm flip 

// FUN1
// ----

// FUN2
// ----


const key_override_t** key_overrides = (const key_override_t*[]){

   // ALA0
   // ----

   // ALA1
   // ----
   &ko_ala1_0 ,// - : _

   // ALA2
   // ----
   &ko_ala2_0  ,// ? : !
   &ko_ala2_1  ,// / : \ .
   &ko_ala2_2  ,// , : ;
   &ko_ala2_3  ,// . : :

   // ALA3
   // ----
 
   // ALA4
   // ----
 
    
   // NAS0
   // ----
 
   // NAS1
   // ----

   // NAS2
   // ----


   // FUN0
   // ----
   &ko_fun0_0 ,// dwm next : dwm monocle 
   &ko_fun0_1 ,// dwm prev : dwm tiled 
   &ko_fun0_2 ,// dwm new : dwm flip 

   // FUN1
   // ----

   // FUN2
   // ----

   NULL
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
// 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  const uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
  switch (keycode) {
  case MODS:
    if (record->event.pressed ) {
      if(shifted){
        layer_on(MODR);
      }
      else{
        layer_on(MODL);
      }
    }
    break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTL_T(KC_ESC):
      // if locked: unlock CAPS after releasing ESC key (want to fallback to known state)
      if (!record->event.pressed && (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) {
        tap_code16(KC_CAPS);
      }
      break;
  }
}
