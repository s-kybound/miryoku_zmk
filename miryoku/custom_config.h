// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku

#include "../zmk-helpers/keypos_def/keypos_42keys.h"
#include "../zmk-helpers/helper.h"

#define MIRYOKU_KLUDGE_MOUSEKEYSPR

#define HM_TAPPING_TERM 300
#define HM_TAPPING_TERM_FAST 200

#define KEYS_L LT0 LT1 LT2 LT3 LT4 LT5 LM0 LM1 LM2 LM3 LM4 LM5 LB0 LB1 LB2 LB3 LB4 LB5
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RT5 RM0 RM1 RM2 RM3 RM4 RM5 RB0 RB1 RB2 RB3 RB4 RB5
#define KEYS_T LH2 LH1 LH0 RH0 RH1 RH2

/* left-hand HRMs */
ZMK_BEHAVIOR(hml, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <260>;
    quick-tap-ms = <175>;                // repeat on tap-into-hold
    require-prior-idle-ms = <150>;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_R KEYS_T>;
    hold-trigger-on-release;             // delay positional check until key-release
)

/* right-hand HRMs */
ZMK_BEHAVIOR(hmr, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <260>;
    quick-tap-ms = <175>;                // repeat on tap-into-hold
    require-prior-idle-ms = <150>;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_L KEYS_T>;
    hold-trigger-on-release;             // delay positional check until key-release
)

// redefine the home row mods to use hand-specific configurations
#define U_HML(MOD, TAP) &hml MOD TAP
#define U_HMR(MOD, TAP) &hmr MOD TAP

#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,           \
U_HML(LGUI, A),    U_HML(LALT, R),    U_HML(LCTRL, S),   U_HML(LSHFT, T),   &kp G,             &kp M,             U_HMR(LSHFT, N),   U_HMR(LCTRL, E),   U_HMR(LALT, I),    U_HMR(LGUI, O),    \
U_LT(U_BUTTON, Z), U_HML(RALT, X),    &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         U_HMR(RALT, DOT),  U_LT(U_BUTTON, SLASH),\
U_NP,              U_NP,              U_LT(U_MEDIA, ESC),U_LT(U_NAV, SPACE),U_LT(U_MOUSE, TAB),U_LT(U_SYM, RET),  U_LT(U_NUM, BSPC), U_LT(U_FUN, DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_MOUSE \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              U_NU,              U_MS_L,            U_MS_D,            U_MS_U,            U_MS_R,            \
U_NA,              &kp RALT,          &u_to_U_SYM,       &u_to_U_MOUSE,     U_NA,              U_NU,              U_WH_L,            U_WH_D,            U_WH_U,            U_WH_R,            \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_BTN1,            U_BTN2,            U_BTN3,            U_NP,              U_NP

// add a new layer for gaming
#undef MIRYOKU_LAYER_LIST
#define MIRYOKU_LAYER_LIST \
MIRYOKU_X(BASE,   "Base") \
MIRYOKU_X(EXTRA,  "Extra") \
MIRYOKU_X(TAP,    "Tap") \
MIRYOKU_X(BUTTON, "Button") \
MIRYOKU_X(NAV,    "Nav") \
MIRYOKU_X(MOUSE,  "Mouse") \
MIRYOKU_X(MEDIA,  "Media") \
MIRYOKU_X(NUM,    "Num") \
MIRYOKU_X(SYM,    "Sym") \
MIRYOKU_X(FUN,    "Fun") \
MIRYOKU_X(GAME,   "Game")

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
&kp F,             &kp A,             &kp S,             &kp D,             &kp G,             &kp H,             &kp J,             &kp K,             &kp L,             &kp SEMI,        \
&kp Z,             &kp X,             &kp C,             &kp V,             &kp B,             &kp N,             &kp M,             &kp COMMA,         &kp DOT,           &kp SLASH,       \
U_NP,              U_NP,              &kp ESC,           &kp SPACE,         &vkp TAB,          &kp RET,           &kp BSPC,          &kp DEL,           U_NP,              U_NP

#if defined (MIRYOKU_KEYBOARD_CORNE)

// extend the functionality of the corne to include the 6th
// column keys
#define MIRYOKU_LAYERMAPPING_BASE( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&to 10    K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp BSLH \
&kp CAPS  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp SEMI \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    K32  K33  K34       K35  K36  K37

#define MIRYOKU_LAYERMAPPING_GAME( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&to 0     K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp BSLH  \
&kp LCTRL K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RET   \
&kp LSHFT K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RSHFT \
                    K32  K33  K34       K35  K36  K37

// move BT_CLR to the left hand - too easy to mispress with the original position
#define MIRYOKU_LAYERMAPPING_MEDIA( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&bt BT_CLR     K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &none        \
&none          K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &none        \
&none          K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &bt BT_SEL 4 \
                         K32  K33  K34       K35  K36  K37

#define MIRYOKU_LAYERMAPPING_SYM( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&kp LBRC  K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp RBRC \
&kp LBKT  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RBKT \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    K32  K33  K34       K35  K36  K37

#define MIRYOKU_LAYERMAPPING_NUM( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39  \
) \
&kp LBRC  K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  &kp RBRC \
&kp LBKT  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  &kp RBKT \
&kp LPAR  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  &kp RPAR \
                    K32  K33  K34       K35  K36  K37

// allow the third thumb button (ESC and DEL) to be mimicked
// by pressing the first and second buttons simultaneously
#define MIRYOKU_KLUDGE_THUMBCOMBOS_LEFT 37 38
#define MIRYOKU_KLUDGE_THUMBCOMBOS_RIGHT 39 40
#define MIRYOKU_KLUDGE_THUMBCOMBOS
#endif