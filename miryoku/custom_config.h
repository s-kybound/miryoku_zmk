// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku

#include "../zmk-helpers/keypos_def/keypos_42keys.h"
#include "../zmk-helpers/helper.h"

#define MIRYOKU_KLUDGE_MOUSEKEYSPR

#define HM_TAPPING_TERM 260
#define HM_TAPPING_TERM_FAST 175
#define HM_PRIOR_IDLE_MS 150

#define KEYS_L LT0 LT1 LT2 LT3 LT4 LT5 LM0 LM1 LM2 LM3 LM4 LM5 LB0 LB1 LB2 LB3 LB4 LB5
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RT5 RM0 RM1 RM2 RM3 RM4 RM5 RB0 RB1 RB2 RB3 RB4 RB5

// charybdis has 5 thumb keys, not 6: RH2 does not exist
#if defined (MIRYOKU_KEYBOARD_CHARYBDIS)
#define KEYS_T LH2 LH1 LH0 RH0 RH1
#else
#define KEYS_T LH2 LH1 LH0 RH0 RH1 RH2
#endif

/* left-hand HRMs */
ZMK_BEHAVIOR(hml, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <HM_TAPPING_TERM>;
    quick-tap-ms = <HM_TAPPING_TERM_FAST>;                // repeat on tap-into-hold
    require-prior-idle-ms = <HM_PRIOR_IDLE_MS>;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_R KEYS_T>;
    hold-trigger-on-release;             // delay positional check until key-release
)

/* right-hand HRMs */
ZMK_BEHAVIOR(hmr, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <HM_TAPPING_TERM>;
    quick-tap-ms = <HM_TAPPING_TERM_FAST>;                // repeat on tap-into-hold
    require-prior-idle-ms = <HM_PRIOR_IDLE_MS>;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_L KEYS_T>;
    hold-trigger-on-release;             // delay positional check until key-release
)

/* thumb layers */
ZMK_BEHAVIOR(u_lt, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <HM_TAPPING_TERM>;
    quick-tap-ms = <HM_TAPPING_TERM_FAST>;                // repeat on tap-into-hold
    require-prior-idle-ms = <HM_PRIOR_IDLE_MS>;
    bindings = <&mo>, <&kp>;
    hold-trigger-key-positions = <KEYS_T>;
    hold-trigger-on-release;             // delay positional check until key-release
)

// redefine the home row mods to use hand-specific configurations
#define U_HML(MOD, TAP) &hml MOD TAP
#define U_HMR(MOD, TAP) &hmr MOD TAP

// expanded here rather than inside a deferred layer macro, so the key code
// definitions have to already be in scope
#include <dt-bindings/zmk/keys.h>

/* tap = caps word, double tap = caps lock */
ZMK_BEHAVIOR(td_caps, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&caps_word>, <&kp CAPS>;
)

#if defined (MIRYOKU_KEYBOARD_CHARYBDIS)
/* hold D for the trackball layer. only the clicks (19 20) and the snipe and
   scroll keys (26 27) can trigger the hold, so D stays a plain D otherwise */
ZMK_BEHAVIOR(u_ball, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <HM_TAPPING_TERM_FAST>;
    require-prior-idle-ms = <HM_PRIOR_IDLE_MS>;
    bindings = <&mo>, <&kp>;
    hold-trigger-key-positions = <19 20 26 27>;
)

#define U_BALL_D &u_ball U_BALL D
#else
#define U_BALL_D &kp D
#endif

#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,                \
U_HML(LGUI, A),    U_HML(LALT, R),    U_HML(LCTRL, S),   U_HML(LSHFT, T),   &kp G,             &kp M,             U_HMR(LSHFT, N),   U_HMR(LCTRL, E),   U_HMR(LALT, I),    U_HMR(LGUI, O),         \
U_LT(U_BUTTON, Z), U_HML(RALT, X),    &kp C,             U_BALL_D,          &kp V,             &kp K,             &kp H,             &kp COMMA,         U_HMR(RALT, DOT),  U_LT(U_BUTTON, SLASH),  \
U_NP,              U_NP,              U_LT(U_MEDIA, ESC),U_LT(U_NAV, SPACE),U_LT(U_MOUSE, TAB),U_LT(U_SYM, RET),  U_LT(U_NUM, BSPC), U_LT(U_FUN, DEL),  U_NP,              U_NP

// we repurpose the mouse layer for a code layer, replacing all of the symbols
// i hated myself typing in different layers
#define MIRYOKU_LAYER_MOUSE \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      U_NA,              &kp MINUS,         &kp UNDER,         &kp TILDE,         &kp GRAVE,         &kp PIPE, \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              &td_caps,          &kp LPAR,          &kp LBKT,          &kp RBKT,          &kp RPAR, \
U_NA,              &kp RALT,          &u_to_U_SYM,       &u_to_U_MOUSE,     U_NA,              &kp AMPS,          &kp LT,            &kp LBRC,          &kp RBRC,          &kp GT, \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp EQUAL,         &kp COLON,         U_NA,              U_NP,              U_NP

// move bluetooth clear to the innermost upper left hand key - its too easy to press otherwise
#define MIRYOKU_LAYER_MEDIA \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      &bt BT_CLR,        U_RGB_TOG,         U_RGB_EFF,         U_RGB_HUI,         U_RGB_SAI,         U_RGB_BRI,         \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              U_EP_TOG,          &kp C_PREV,        &kp C_VOL_DN,      &kp C_VOL_UP,      &kp C_NEXT,        \
U_NA,              &kp RALT,          &u_to_U_FUN,       &u_to_U_MEDIA,     U_NA,              &u_out_tog,        &u_bt_sel_0,       &u_bt_sel_1,       &u_bt_sel_2,       &u_bt_sel_3,       \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp C_STOP,        &kp C_PP,          &kp C_MUTE,        U_NP,              U_NP

// add a new layer for gaming
#if defined (MIRYOKU_KEYBOARD_CHARYBDIS)
#include "../config/boards/shields/charybdis_common/charybdis_layers.h"
#define U_LAYER_LIST_BALL \
MIRYOKU_X(BALL,   "Ball")     \
MIRYOKU_X(SNIPE,  "Snipe")    \
MIRYOKU_X(SCROLL, "Scroll")
#else
#define U_LAYER_LIST_BALL
#endif

#undef MIRYOKU_LAYER_LIST
#define MIRYOKU_LAYER_LIST    \
MIRYOKU_X(BASE,   "Base")     \
MIRYOKU_X(EXTRA,  "Extra")    \
MIRYOKU_X(TAP,    "Tap")      \
MIRYOKU_X(BUTTON, "Button")   \
MIRYOKU_X(NAV,    "Nav")      \
MIRYOKU_X(MOUSE,  "Code")    \
MIRYOKU_X(MEDIA,  "Media")    \
MIRYOKU_X(NUM,    "Num")      \
MIRYOKU_X(SYM,    "Sym")      \
MIRYOKU_X(FUN,    "Fun")      \
MIRYOKU_X(GAME,   "Game")     \
U_LAYER_LIST_BALL

#define U_BASE   0
#define U_EXTRA  1
#define U_TAP    2
#define U_BUTTON 3
#define U_NAV    4
#define U_MOUSE  5
#define U_MEDIA  6
#define U_NUM    7
#define U_SYM    8
#define U_FUN    9
#define U_GAME  10

#define MIRYOKU_LAYER_GAME \
&kp R,             &kp Q,             &kp W,             &kp E,             &kp T,             &kp Y,             &kp U,             &kp I,             &kp O,             &kp P,           \
&kp F,             &kp A,             &kp S,             &kp D,             &kp G,             &kp H,             U_BTN1,            U_BTN2,            &kp L,             &kp SEMI,        \
&kp Z,             &kp X,             &kp C,             &kp V,             &kp B,             &kp N,             &kp M,             &kp COMMA,         &kp DOT,           &kp SLASH,       \
U_NP,              U_NP,              &kp ESC,           &kp SPACE,         &kp TAB,           &kp RET,           &kp BSPC,          &kp DEL,           U_NP,              U_NP

// charybdis is a corne with a trackball in place of the right outer thumb, so
// it takes the same 6th-column fills with that one key dropped
#if defined (MIRYOKU_KEYBOARD_CHARYBDIS)
#define U_THUMBS(T0, T1, T2, T3, T4, T5) T0  T1  T2       T3  T4
#else
#define U_THUMBS(T0, T1, T2, T3, T4, T5) T0  T1  T2       T3  T4  T5
#endif

#if defined (MIRYOKU_KEYBOARD_CORNE) || defined (MIRYOKU_KEYBOARD_CHARYBDIS)

// extend the functionality of the corne to include the 6th
// column keys
#define MIRYOKU_LAYERMAPPING_BASE( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&kp MINUS K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp BSLH \
&td_caps  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp SEMI \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

// add gaming layer here - putting it on the base layer to sacrifice "-" is too painful
#define MIRYOKU_LAYERMAPPING_MEDIA( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&to 10    K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &bt BT_NXT   \
&none     K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &bt BT_PRV   \
&none     K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &bt BT_SEL 4 \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

// add gaming layer here
#define MIRYOKU_LAYERMAPPING_NAV( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&to 10    K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &none   \
&none     K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &none   \
&none     K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &none   \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

// add gaming layer here
#define MIRYOKU_LAYERMAPPING_MOUSE( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&to 10    K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &none   \
&none     K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &none   \
&none     K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &none   \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

// aforementioned gaming layer
#define MIRYOKU_LAYERMAPPING_GAME( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&to 0     K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp BSLH  \
&kp LCTRL K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RET   \
&kp LSHFT K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RSHFT \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

#define MIRYOKU_LAYERMAPPING_SYM( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&kp LBRC  K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp RBRC \
&kp LBKT  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RBKT \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

#define MIRYOKU_LAYERMAPPING_NUM( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&kp LBRC  K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp RBRC \
&kp LBKT  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RBKT \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

#define MIRYOKU_LAYERMAPPING_FUN( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&kp LBRC  K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp RBRC \
&kp LBKT  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RBKT \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    U_THUMBS(K32, K33, K34, K35, K36, K37)

// allow the third thumb button (ESC and DEL) to be mimicked
// by pressing the first and second buttons simultaneously
#define MIRYOKU_KLUDGE_THUMBCOMBOS_LEFT 37 38
#define MIRYOKU_KLUDGE_THUMBCOMBOS_RIGHT 39 40
#define MIRYOKU_KLUDGE_THUMBCOMBOS

// both index fingers on the home row for caps word
/ {
  combos {
    compatible = "zmk,combos";

    combo_td_caps {
      bindings = <&td_caps>;
      key-positions = <16 19>;
      layers = <U_BASE>;
      timeout-ms = <50>;
    };
  };
};
#endif

#if defined (MIRYOKU_KEYBOARD_CHARYBDIS)

/* trackball layer: right index home = left click, right middle home = right
   click. everything else falls through to the layer below */
#define MIRYOKU_LAYER_BALL \
&trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans, \
&trans,            &trans,            &trans,            &trans,            &trans,            &trans,            U_BTN1,            U_BTN2,            &trans,            &trans, \
&trans,            &mo U_SNIPE,       &mo U_SCROLL,      &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans, \
U_NP,              U_NP,              &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            U_NP,              U_NP

#define MIRYOKU_LAYERMAPPING_BALL( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&trans    K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &trans \
&trans    K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &trans \
&trans    K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &trans \
                    K32  K33  K34       K35  K36

/* snipe and scroll change nothing about the keys; the trackball listener
   overrides its processor chain on these layers. see charybdis_trackball.dtsi */
#define MIRYOKU_LAYER_SNIPE  MIRYOKU_LAYER_PASSTHROUGH
#define MIRYOKU_LAYER_SCROLL MIRYOKU_LAYER_PASSTHROUGH
#define MIRYOKU_LAYERMAPPING_SNIPE  MIRYOKU_LAYERMAPPING_BALL
#define MIRYOKU_LAYERMAPPING_SCROLL MIRYOKU_LAYERMAPPING_BALL

#define MIRYOKU_LAYER_PASSTHROUGH \
&trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans, \
&trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans, \
&trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            &trans, \
U_NP,              U_NP,              &trans,            &trans,            &trans,            &trans,            &trans,            &trans,            U_NP,              U_NP

#endif
