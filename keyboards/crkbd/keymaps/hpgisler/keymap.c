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
  BA, // base layer, includes shifted keycodes
  L1, // 1st lower layer
  L2, // 2nd lower layer, includes shifted keycodes
  U1, // 1st upper layer
  U2  // 2nd upper layer, includes shifted keycodes
};

#define MOU1_SPC   LT(U1, KC_SPC)

#define LCTL_T(kc) MT(MOD_LCTL, kc)

#define RCTL_T(kc) MT(MOD_RCTL, kc)
#define CTL_T(kc) LCTL_T(kc)

#define LSFT_T(kc) MT(MOD_LSFT, kc)
#define RSFT_T(kc) MT(MOD_RSFT, kc)
#define SFT_T(kc) LSFT_T(kc)

#define LALT_T(kc) MT(MOD_LALT, kc)
#define RALT_T(kc) MT(MOD_RALT, kc)
#define LOPT_T(kc) LALT_T(kc)
#define ROPT_T(kc) RALT_T(kc)
#define ALGR_T(kc) RALT_T(kc)
#define ALT_T(kc) LALT_T(kc)
#define OPT_T(kc) LOPT_T(kc)


// --------------------------------------------------

#define LA_NUM MO(L1)
#define LA_NAV MO(L2)
#define LA_EXT MO(L3)
#define LA_DWM MO(L4)

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
#define RALT_B   RALT(KC_B)
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

const key_override_t grv_key_override  = ko_make_basic(MOD_MASK_SHIFT, CH_GRV,   CH_ACUT); // Shift ` is ´
const key_override_t euro_key_override = ko_make_basic(MOD_MASK_SHIFT, CH_EURO,  CH_SECT); // Shift € is §
const key_override_t left_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT,  KC_HOME); // Shift Left is Home
const key_override_t down_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOWN,  KC_PGDN); // Shift down is PgDn
const key_override_t up_key_override   = ko_make_basic(MOD_MASK_SHIFT, KC_UP,    KC_PGUP); // Shift up is PgUp 
const key_override_t right_key_override= ko_make_basic(MOD_MASK_SHIFT, KC_RIGHT, KC_END);  // Shift right is End 
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC,  KC_DEL);  // Shift bspc is del  


/* const uint16_t PROGMEM test_combo1[] = {KC_K, KC_L, COMBO_END}; */
/* const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END}; */
/* combo_t key_combos[COMBO_COUNT] = { */
/*     COMBO(test_combo1, OS_ALT), */
/*     COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too! */
/* }; */
const key_override_t** key_overrides = (const key_override_t*[]){
    &grv_key_override,
    &euro_key_override,
    &left_key_override,
    &down_key_override,
    &up_key_override,
    &right_key_override,
    &bspc_key_override,

    NULL
};

/* bool caps_word_press_user(uint16_t keycode) { */
/*     switch (keycode) { */
/*         Keycodes that continue Caps Word, with shift applied. */
/*         case KC_A ... KC_Z: */
/*         case CH_MINS: */
/*             add_weak_mods(MOD_BIT(KC_LSFT));  Apply shift to next key. */
/*             return true; */

/*         Keycodes that continue Caps Word, without shifting. */
/*         case KC_1 ... KC_0: */
/*         case KC_BSPC: */
/*         case KC_LSFT: */
/*         case KC_DEL: */
/*         case CH_UNDS: */
/*             return true; */

/*         default: */
/*             return false;  Deactivate Caps Word. */
/*     } */
/* } */

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
    [BA] = LAYOUT_split_3x5_3(
                               
     // (qQ)      wW        eE        (rR)      (tT)      (zZ)      (uU)      iI        oO        (pP)
        KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , CH_Z    , KC_U    , KC_I    , KC_O    , KC_P    ,

     // aA        Ctl_sS    Sft_dD    Alt_fF    gG        hH        Alt_jJ    Sft_kK    Ctl_lL    ü
        KC_A,LCTL_T(KC_S),LSFT_T(KC_D),LALT_T(KC_F),ALGR_T(KC_G),ALGR_T(KC_H),LALT_T(KC_J),RSFT_T(KC_K),RCTL_T(KC_L),CH_UDIA,

     // yY        xX        cC        AGr_vV    (bB)      (nN)      AGr_mM    ,;        .:        -_ 
        CH_Y    , KC_X    , KC_C    , KC_V    ,KC_B     , KC_N    , KC_M    , KC_COMM , KC_DOT  , CH_MINS ,

     //                               L2        L1        U1 SPC    U2
                            XXXXXXX , MO(L2)  , MO(L1)  , MOU1_SPC, MO(U2)  , XXXXXXX
    ),

    [L1] = LAYOUT_split_3x5_3(
                               
     //           (         )                                                 9         0
        XXXXXXX , CH_LPRN , CH_RPRN , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_9    , KC_0    , XXXXXXX ,

     // `´        "         '         &         |                   5         6         7         8
        CH_GRV  , CH_DQUO , CH_QUOT , CH_AMPR , CH_PIPE , XXXXXXX , KC_5    , KC_6    , KC_7    , KC_8    ,

     // °         [         ]         %                             1         2         3         4
        CH_DEG  , CH_LBRC , CH_RBRC , CH_PERC , XXXXXXX , XXXXXXX , KC_1    , KC_2    , KC_3    , KC_4    ,


                            XXXXXXX , XXXXXXX , _______ , _______ , XXXXXXX , XXXXXXX
    ),

    [L2] = LAYOUT_split_3x5_3(
                               
     //           Q         P                                                 ?         !
        XXXXXXX , KC_Q    , KC_P    , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , CH_QUES , CH_EXLM , XXXXXXX ,

     // zZ        LCtl bB   LSft rR   LAlt tT                       LAlt nN   RSft uU   RCtl ä    ö
        KC_Z,LCTL_T(KC_B),LSFT_T(KC_R),LALT_T(KC_T),XXXXXXX,XXXXXXX,LALT_T(KC_N),RSFT_T(KC_U),RCTL_T(CH_ADIA),CH_ODIA ,

     //           €§        @         #                             
        XXXXXXX , CH_EURO , CH_AT   , CH_HASH , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,   


                            XXXXXXX , _______ , XXXXXXX , _______ , XXXXXXX , XXXXXXX
    ),

    [U1] = LAYOUT_split_3x5_3(
                               
     //                                                                       {         }
        XXXXXXX , KC_F10  , KC_F9   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , CH_LCBR , CH_RCBR , XXXXXXX ,

     //                                                   ^         *         +         =         $
        KC_F8   , KC_F7   , KC_F6   , KC_F5   , XXXXXXX , CH_CIRC , CH_ASTR , CH_PLUS , CH_EQL  , CH_DLR  ,

     //                                                             /         <         >         '\'
        KC_F4   , KC_F3   , KC_F2   , KC_F1   , XXXXXXX , XXXXXXX , CH_SLSH , CH_LABK , CH_RABK , KC_BSLS ,


                            XXXXXXX , XXXXXXX , XXXXXXX , _______ , XXXXXXX , XXXXXXX
    ),

    [U2] = LAYOUT_split_3x5_3(
                               
     // 
        XXXXXXX , KC_ESC  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC , XXXXXXX ,

     //
        XXXXXXX , XXXXXXX , KC_LSFT , XXXXXXX , XXXXXXX , KC_LEFT ,KC_DOWN,RSFT_T(KC_UP),KC_RIGHT, KC_ENT ,

     //
        XXXXXXX , XXXXXXX , KC_F12  , KC_F11  , XXXXXXX , XXXXXXX , XXXXXXX , KC_TAB  , XXXXXXX , XXXXXXX ,


                            XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , XXXXXXX
    ),
};

/* bool is_oneshot_cancel_key(uint16_t keycode) { */
/*     switch (keycode) { */
/*     case LA_NUM: */
/*     // case LA_NAV: */
/*         return true; */
/*     default: */
/*         return false; */
/*     } */
/* } */

/* bool is_oneshot_ignored_key(uint16_t keycode) { */
/*     switch (keycode) { */
/*     case LA_NUM: */
/*     case LA_NAV: */
/*     case KC_LSFT: */
/*     case OS_SHFT: */
/*     case OS_CTRL: */
/*     case OS_ALT: */
/*     case OS_CMD: */
/*         return true; */
/*     default: */
/*         return false; */
/*     } */
/* } */

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*     update_swapper( */
/*         &sw_win_active, KC_LGUI, KC_TAB, SW_WIN, */
/*         keycode, record */
/*     ); */
/*     update_swapper( */
/*         &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG, */
/*         keycode, record */
/*     ); */

/*     update_oneshot( */
/*         &os_shft_state, KC_LSFT, OS_SHFT, */
/*         keycode, record */
/*     ); */
/*     update_oneshot( */
/*         &os_ctrl_state, KC_LCTL, OS_CTRL, */
/*         keycode, record */
/*     ); */
/*     update_oneshot( */
/*         &os_alt_state, KC_LALT, OS_ALT, */
/*         keycode, record */
/*     ); */
/*     update_oneshot( */
/*         &os_cmd_state, KC_LCMD, OS_CMD, */
/*         keycode, record */
/*     ); */

/*     return true; */
/* } */

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*   return update_tri_layer_state(state, L1, L2, U1); */
/* } */
