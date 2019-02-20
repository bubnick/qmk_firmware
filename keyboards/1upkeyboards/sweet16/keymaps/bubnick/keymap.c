#include "sweet16.h"

#define _BASE 0
#define _L1_ARROW 1
#define _L2_MACRO 2
#define _L3_FUNC  3
#define _L4_MISC  4

enum custom_keycodes {
  UP_URL = SAFE_RANGE
};

//Tap Dance Declarations
enum {
  TD_PEQL_ENT = 0,
  TD_PPLS_L1 = 1,
  TD_PMNS_L2 = 2,
  TD_PAST_L3 = 3,
  TD_PSLS_L4 = 4,
  TD_NO_BASE = 5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_4x4(
      KC_7, KC_8,   KC_9,            TD(TD_PSLS_L4),
      KC_4, KC_5,   KC_6,            TD(TD_PAST_L3),
      KC_1, KC_2,   KC_3,            TD(TD_PMNS_L2),
      KC_0, KC_DOT, TD(TD_PEQL_ENT), TD(TD_PPLS_L1)
  ),

  [_L1_ARROW] = LAYOUT_ortho_4x4(
      KC_HOME, KC_UP, KC_PGUP, KC_TAB,
      KC_LEFT, KC_ENT, KC_RIGHT, KC_NO,
      KC_END, KC_DOWN, KC_PGDN, KC_NO,
      KC_PSCR, KC_DEL, KC_SCROLLLOCK, TD(TD_NO_BASE)
  ),

  [_L2_MACRO] = LAYOUT_ortho_4x4(
      KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, TG(_L2_MACRO),
      KC_NO, KC_NO, KC_NO, KC_NO
  ),

  [_L3_FUNC] = LAYOUT_ortho_4x4(
      KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, TG(_L3_FUNC),
      KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO
  ),

  [_L4_MISC] = LAYOUT_ortho_4x4(
      KC_NO, KC_NO, KC_NO, TG(_L4_MISC),
      KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO
  )
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_PEQL_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_ENT),
  [TD_PPLS_L1] = ACTION_TAP_DANCE_DUAL_ROLE(KC_PPLS, _L1_ARROW),
  [TD_PMNS_L2] = ACTION_TAP_DANCE_DUAL_ROLE(KC_PMNS, _L2_MACRO),
  [TD_PAST_L3] = ACTION_TAP_DANCE_DUAL_ROLE(KC_PAST, _L3_FUNC),
  [TD_PSLS_L4] = ACTION_TAP_DANCE_DUAL_ROLE(KC_PSLS, _L4_MISC),
  [TD_NO_BASE] = ACTION_TAP_DANCE_DUAL_ROLE(KC_NO, _BASE)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboards.com");
            }
            return false;
            break;
    }
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _L1_ARROW:
        rgblight_setrgb(0, 16, 0); //green
        break;
    case _L2_MACRO:
        rgblight_setrgb(0, 0, 16); //blue
        break;
    case _L3_FUNC:
        rgblight_setrgb (16, 0, 16); //purple
        break;
    case _L4_MISC:
        rgblight_setrgb(0, 16, 16); //teal
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (16, 0, 0); //red
        break;
    }
  return state;
}
