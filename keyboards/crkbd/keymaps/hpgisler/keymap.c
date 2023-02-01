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
#include "oneshot.h"
#include "swapper.h"

enum layers {
  AL1,
  AL1U,
  AL2,
  AL2U,
  SYM1,
  SYM2,
  NUM,
  SYS,
  FUN,
  FUNHi,
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
    REPEAT,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

const key_override_t left_key_override = ko_make_basic(MOD_MASK_ALT, KC_LEFT,  KC_HOME); // Shift Left is Home
const key_override_t down_key_override = ko_make_basic(MOD_MASK_ALT, KC_DOWN,  KC_PGDN); // Shift down is PgDn
const key_override_t up_key_override   = ko_make_basic(MOD_MASK_ALT, KC_UP,    KC_PGUP); // Shift up is PgUp 
const key_override_t right_key_override= ko_make_basic(MOD_MASK_ALT, KC_RIGHT, KC_END);  // Shift right is End 
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_ALT, KC_BSPC,  KC_DEL);  // Shift bspc is del  


/* const uint16_t PROGMEM test_combo1[] = {KC_K, KC_L, COMBO_END}; */
/* const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END}; */
/* combo_t key_combos[COMBO_COUNT] = { */
/*     COMBO(test_combo1, OS_ALT), */
/*     COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too! */
/* }; */
const key_override_t** key_overrides = (const key_override_t*[]){
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
    [AL1] = LAYOUT_split_10(
                                            LT(FUN,KC_L)   , LALT_T(KC_G)   , LCTL_T(KC_D)   , RCTL_T(KC_H)   , LALT_T(KC_U)   , LT(FUN,KC_O)   ,

                           LT(NUM, KC_I)  , LT(SYM2, KC_S) , LT(SYM1, KC_R) , LT(SYS , KC_T) , LT(SYS , KC_N) , LT(SYM1, KC_E) , LT(SYM2, KC_A) , LT(NUM, KC_C)  ,

                                            REPEAT         , KC_SPC         , OSL(AL1U)      , OSL(AL2U)      , OSL(AL2)       , KC_ALGR
                           ),

    [AL1U] = LAYOUT_split_10(
                                            LSFT(KC_L)     , LSFT(KC_G)     , LSFT(KC_D)     , LSFT(KC_H)     , LSFT(KC_U)     , LSFT(CH_O)     ,

                           LSFT(KC_I)     , LSFT(KC_S)     , LSFT(KC_R)     , LSFT(KC_T)     , LSFT(KC_N)     , LSFT(KC_E)     , LSFT(KC_A)     , LSFT(CH_C)     ,

                                            _______        , _______        , _______        , _______        , _______         , _______
                           ),
 
    [AL2] = LAYOUT_split_10(
                                            KC_V           , LALT_T(KC_W)   , LCTL_T(KC_M)   , RCTL_T(KC_F)   , LALT_T(CH_QUOT), CH_Z           ,

                           KC_Q           , KC_J           , KC_P           , KC_K           , KC_B           , CH_DOT         , KC_X           , CH_Y           ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [AL2U] = LAYOUT_split_10(
                                            LSFT(KC_V)     , LSFT(KC_W)     , LSFT(KC_M)     , LSFT(KC_F)     , CH_DQUO        , LSFT(CH_Z)     ,

                            LSFT(KC_Q)    , LSFT(KC_J)     , LSFT(KC_P)     , LSFT(KC_K)     , LSFT(KC_B)     , CH_COMM        , LSFT(KC_X)     , LSFT(CH_Y)     ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
 
    [SYM1] = LAYOUT_split_10(
                                            CH_EURO        , CH_HASH        , CH_DLR         , CH_LABK        , CH_RABK        , CH_CIRC        ,

                           CH_GRV         , CH_TILD        , CH_UNDS        , CH_BSLS        , CH_LBRC        , CH_RBRC        , CH_PIPE        , CH_SLSH        ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [SYM2] = LAYOUT_split_10(
                                            CH_AT          , XXXXXXX        , CH_QUES        , CH_LPRN        , CH_RPRN        , CH_SCLN        ,

                           CH_ASTR        , CH_PERC        , CH_EXLM        , CH_DQUO        , CH_LCBR        , CH_RCBR        , CH_AMPR        , CH_COLN        ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
      
    [NUM] = LAYOUT_split_10(
                                            KC_1           , KC_2           , KC_3           , KC_4           , KC_5           , KC_6           ,

                           CH_PLUS        , CH_EQL         , KC_DOT         , KC_0           , KC_7           , KC_8           , KC_9           , CH_MINS        ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    [SYS] = LAYOUT_split_10(
                                            KC_ESC         , KC_LALT        , KC_LCTL        , KC_DOWN        , KC_UP          , KC_RIGHT       ,

                                  XXXXXXX        , XXXXXXX , LSFT(KC_TAB)   , KC_TAB         , KC_LEFT        , KC_DEL         , KC_BSPC        , KC_ENT         ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
    
    [FUN] = LAYOUT_split_10(
                                            KC_F1          , RALT_T(KC_F2)  , LCTL_T(KC_F3)  , RCTL_T(KC_F4)  , RALT_T(KC_F5)  , KC_F6          ,

                           KC_LGUI        , KC_F10         , KC_F11         , KC_F12         , KC_F7          , KC_F8          , KC_F9          , XXXXXXX        ,

                                            _______        , -------        , MO(FUNHi)      , MO(FUNHi)      , -------        , _______
                           ),
    
    [FUNHi] = LAYOUT_split_10(

                          ALGR(LSFT(KC_C)), XXXXXXX        , XXXXXXX        , ALGR(KC_J)     , ALGR(KC_K)     , ALGR(KC_L)     ,

                          ALGR(LSFT(KC_Q)), ALGR(KC_D)     , ALGR(KC_I)     , ALGR(KC_B)     , ALGR(KC_H)     , ALGR(KC_T)     , ALGR(KC_M)     , ALGR(KC_P)     ,

                                            _______        , _______        , _______        , _______        , _______        , _______
                           ),
    
};
                               

/*
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
*/
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
    return true;
};
