#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <time.h>
#include "common.h"
#include "functions.h"
#include "oyastate.h"

// 平手（ノーマル）状態での配列定義
KEYMAP_INFO oyakanaTableRomajiDefault[] = {
	// 左手最上段 
	{KEY_1, MOJI_1},
	{KEY_2, MOJI_2},
	{KEY_3, MOJI_3},
	{KEY_4, MOJI_4},
	{KEY_5, MOJI_5},

	// 左手上段 
	{KEY_Q, MOJI_PERIOD},
	{KEY_W, MOJI_NA},
	{KEY_E, MOJI_TE},
	{KEY_R, MOJI_RU},
	{KEY_T, MOJI_HE},

	// 左手中段 
	{KEY_A, MOJI_KO},
	{KEY_S, MOJI_TA},
	{KEY_D, MOJI_KA},
	{KEY_F, MOJI_U},
	{KEY_G, MOJI_HA},

	// 左手下段 
	{KEY_Z, MOJI_MO},
	{KEY_X, MOJI_HO},
	{KEY_C, MOJI_MA},
	{KEY_V, MOJI_SA},
	{KEY_B, MOJI_NAKAGURO},

	// 右手最上段 
	{KEY_6, MOJI_6},
	{KEY_7, MOJI_7},
	{KEY_8, MOJI_8},
	{KEY_9, MOJI_9},
	{KEY_0, MOJI_0},
	{KEY_MINUS, MOJI_MINUS},
	{KEY_EQUAL, MOJI_EQUAL},

	// 右手上段 
	{KEY_Y, MOJI_SLASH},
	{KEY_U, MOJI_HI},
	{KEY_I, MOJI_NO},
	{KEY_O, MOJI_NI},
	{KEY_P, MOJI_PU},
	{KEY_LEFTBRACE, MOJI_COMMA},

	// 右手中段 
	{KEY_H, MOJI_MINUS},
	{KEY_J, MOJI_NN},
	{KEY_K, MOJI_I},
	{KEY_L, MOJI_SI},
	{KEY_SEMICOLON, MOJI_TO},
	{KEY_APOSTROPHE, MOJI_BS},

	// 右手下段 
	{KEY_N, MOJI_XTU},
	{KEY_M, MOJI_O},
	{KEY_COMMA, MOJI_SU},
	{KEY_DOT, MOJI_RA},
	{KEY_SLASH, MOJI_SE},
	{KEY_RO, MOJI_SEMICOLON}
};

// 右中指キー同時打鍵の配列定義
KEYMAP_INFO oyakanaKTableRomajiDefault[] = {
	// 左手上段  
	{KEY_Q, MOJI_NU},
	{KEY_W, MOJI_KE},
	{KEY_E, MOJI_YO},
	{KEY_R, MOJI_TI},
	{KEY_T, MOJI_PE},

	// 左手中段 
	{KEY_A, MOJI_XI},
	{KEY_S, MOJI_YA},
	{KEY_D, MOJI_KU},
	{KEY_F, MOJI_RO},
	{KEY_G, MOJI_PA},

	// 左手下段 
	{KEY_Z, MOJI_YU},
	{KEY_X, MOJI_PO},
	{KEY_C, MOJI_HU},
	{KEY_V, MOJI_NE},

	{KEY_SPACE, MOJI_GU}
};

// 左中指キー同時打鍵の配列定義
KEYMAP_INFO oyakanaDTableRomajiDefault[] = {
	// 右手上段 
	{KEY_U, MOJI_PI},
	{KEY_I, MOJI_KI},
	{KEY_O, MOJI_E},

	// 右手中段 
	{KEY_H, MOJI_A},
	{KEY_J, MOJI_RE},
	{KEY_K, MOJI_KU},
	{KEY_L, MOJI_RI},
	{KEY_SEMICOLON, MOJI_ME},

	// 右手下段  
	{KEY_N, MOJI_TU},
	{KEY_M, MOJI_MU},
	{KEY_COMMA, MOJI_WA},
	{KEY_DOT, MOJI_SO},
	{KEY_SLASH, MOJI_MI},

	{KEY_SPACE, MOJI_GA}
};

// 右小指キー同時打鍵の配列定義
KEYMAP_INFO oyakanaSCTableRomajiDefault[] = {
	// 左手上段  
	{KEY_W, MOJI_XKE},
	{KEY_E, MOJI_XYO},
	{KEY_T, MOJI_WYE},

	// 左手中段 
	{KEY_A, MOJI_WO},
	{KEY_S, MOJI_XYA},
	{KEY_D, MOJI_ME},
	{KEY_F, MOJI_XU},

	// 左手下段 
	{KEY_Z, MOJI_XYU},

	{KEY_SPACE, MOJI_DO}
};

// 左小指キー同時打鍵の配列定義
KEYMAP_INFO oyakanaATableRomajiDefault[] = {
	// 右手上段 
	{KEY_Y, MOJI_WYI},
	{KEY_O, MOJI_XE},

	// 右手中段 
	{KEY_H, MOJI_XA},
	{KEY_K, MOJI_XI},
	{KEY_SEMICOLON, MOJI_WO},

	// 右手下段  
	{KEY_M, MOJI_XO},
	{KEY_COMMA, MOJI_XWA},

	{KEY_SPACE, MOJI_GO}
};

// 親指キー同時打鍵の配列定義
KEYMAP_INFO oyakanaSPTableRomajiDefault[] = {
	// 左手上段 
	{KEY_W, MOJI_GE},
	{KEY_E, MOJI_DE},
	{KEY_R, MOJI_DI},
	{KEY_T, MOJI_BE},

	// 左手中段 
	{KEY_A, MOJI_GO},
	{KEY_S, MOJI_DA},
	{KEY_D, MOJI_GA},
	{KEY_F, MOJI_VU},
	{KEY_G, MOJI_BA},

	// 左手下段 
	{KEY_X, MOJI_BO},
	{KEY_C, MOJI_BU},
	{KEY_V, MOJI_ZA},
	{KEY_B, MOJI_ELLIPSIS},

	// 右手上段 
	{KEY_Y, MOJI_YEN},
	{KEY_U, MOJI_BI},
	{KEY_I, MOJI_GI},
	{KEY_LEFTBRACE, MOJI_ATMARK},

	// 右手中段 
	{KEY_H, MOJI_TILDE},
	{KEY_K, MOJI_GU},
	{KEY_L, MOJI_ZI},
	{KEY_SEMICOLON, MOJI_DO},

	// 右手下段 
	{KEY_N, MOJI_DU},
	{KEY_COMMA, MOJI_ZU},
	{KEY_DOT, MOJI_ZO},
	{KEY_SLASH, MOJI_ZE},
	{KEY_RO, MOJI_COLON}
};

ROMAJI_INFO romaKeys[] = {
	[MOJI_UNDEF] = {0,0,0}, /* undef */
	[MOJI_A] = {KEY_A,0,0}, /* MOJI_A 1 */
	[MOJI_I] = {KEY_I,0,0}, /* MOJI_I 2 */
	[MOJI_U] = {KEY_U,0,0}, /* MOJI_U 3 */
	[MOJI_E] = {KEY_E,0,0}, /* MOJI_E 4 */
	[MOJI_O] = {KEY_O,0,0}, /* MOJI_O 5 */
	[MOJI_KA] = {KEY_K,KEY_A,0}, /* MOJI_KA 6 */
	[MOJI_KI] = {KEY_K,KEY_I,0}, /* MOJI_KI 7 */
	[MOJI_KU] = {KEY_K,KEY_U,0}, /* MOJI_KU 8 */
	[MOJI_KE] = {KEY_K,KEY_E,0}, /* MOJI_KE 9 */
	[MOJI_KO] = {KEY_K,KEY_O,0}, /* MOJI_KO 10 */
	[MOJI_SA] = {KEY_S,KEY_A,0}, /* MOJI_SA 11 */
	[MOJI_SI] = {KEY_S,KEY_I,0}, /* MOJI_SI 12 */
	[MOJI_SU] = {KEY_S,KEY_U,0}, /* MOJI_SU 13 */
	[MOJI_SE] = {KEY_S,KEY_E,0}, /* MOJI_SE 14 */
	[MOJI_SO] = {KEY_S,KEY_O,0}, /* MOJI_SO 15 */
	[MOJI_TA] = {KEY_T,KEY_A,0}, /* MOJI_TA 16 */
	[MOJI_TI] = {KEY_T,KEY_I,0}, /* MOJI_TI 17 */
	[MOJI_TU] = {KEY_T,KEY_U,0}, /* MOJI_TU 18 */
	[MOJI_TE] = {KEY_T,KEY_E,0}, /* MOJI_TE 19 */
	[MOJI_TO] = {KEY_T,KEY_O,0}, /* MOJI_TO 20 */
	[MOJI_NA] = {KEY_N,KEY_A,0}, /* MOJI_NA 21 */
	[MOJI_NI] = {KEY_N,KEY_I,0}, /* MOJI_NI 22 */
	[MOJI_NU] = {KEY_N,KEY_U,0}, /* MOJI_NU 23 */
	[MOJI_NE] = {KEY_N,KEY_E,0}, /* MOJI_NE 24 */
	[MOJI_NO] = {KEY_N,KEY_O,0}, /* MOJI_NO 25 */
	[MOJI_HA] = {KEY_H,KEY_A,0}, /* MOJI_HA 26 */
	[MOJI_HI] = {KEY_H,KEY_I,0}, /* MOJI_HI 27 */
	[MOJI_HU] = {KEY_H,KEY_U,0}, /* MOJI_HU 28 */
	[MOJI_HE] = {KEY_H,KEY_E,0}, /* MOJI_HE 29 */
	[MOJI_HO] = {KEY_H,KEY_O,0}, /* MOJI_HO 30 */
	[MOJI_MA] = {KEY_M,KEY_A,0}, /* MOJI_MA 31 */
	[MOJI_MI] = {KEY_M,KEY_I,0}, /* MOJI_MI 32 */
	[MOJI_MU] = {KEY_M,KEY_U,0}, /* MOJI_MU 33 */
	[MOJI_ME] = {KEY_M,KEY_E,0}, /* MOJI_ME 34 */
	[MOJI_MO] = {KEY_M,KEY_O,0}, /* MOJI_MO 35 */
	[MOJI_YA] = {KEY_Y,KEY_A,0}, /* MOJI_YA 36 */
	[MOJI_YI] = {KEY_Y,KEY_I,0}, /* MOJI_YI 37 */
	[MOJI_YU] = {KEY_Y,KEY_U,0}, /* MOJI_YU 38 */
	[MOJI_YE] = {KEY_Y,KEY_E,0}, /* MOJI_YE 39 */
	[MOJI_YO] = {KEY_Y,KEY_O,0}, /* MOJI_YO 40 */
	[MOJI_RA] = {KEY_R,KEY_A,0}, /* MOJI_RA 41 */
	[MOJI_RI] = {KEY_R,KEY_I,0}, /* MOJI_RI 42 */
	[MOJI_RU] = {KEY_R,KEY_U,0}, /* MOJI_RU 43 */
	[MOJI_RE] = {KEY_R,KEY_E,0}, /* MOJI_RE 44 */
	[MOJI_RO] = {KEY_R,KEY_O,0}, /* MOJI_RO 45 */
	[MOJI_GA] = {KEY_G,KEY_A,0}, /* MOJI_GA 46 */
	[MOJI_GI] = {KEY_G,KEY_I,0}, /* MOJI_GI 47 */
	[MOJI_GU] = {KEY_G,KEY_U,0}, /* MOJI_GU 48 */
	[MOJI_GE] = {KEY_G,KEY_E,0}, /* MOJI_GE 49 */
	[MOJI_GO] = {KEY_G,KEY_O,0}, /* MOJI_GO 50 */
	[MOJI_ZA] = {KEY_Z,KEY_A,0}, /* MOJI_ZA 51 */
	[MOJI_ZI] = {KEY_Z,KEY_I,0}, /* MOJI_ZI 52 */
	[MOJI_ZU] = {KEY_Z,KEY_U,0}, /* MOJI_ZU 53 */
	[MOJI_ZE] = {KEY_Z,KEY_E,0}, /* MOJI_ZE 54 */
	[MOJI_ZO] = {KEY_Z,KEY_O,0}, /* MOJI_ZO 55 */
	[MOJI_DA] = {KEY_D,KEY_A,0}, /* MOJI_DA 56 */
	[MOJI_DI] = {KEY_D,KEY_I,0}, /* MOJI_DI 57 */
	[MOJI_DU] = {KEY_D,KEY_U,0}, /* MOJI_DU 58 */
	[MOJI_DE] = {KEY_D,KEY_E,0}, /* MOJI_DE 59 */
	[MOJI_DO] = {KEY_D,KEY_O,0}, /* MOJI_DO 60 */
	[MOJI_BA] = {KEY_B,KEY_A,0}, /* MOJI_BA 61 */
	[MOJI_BI] = {KEY_B,KEY_I,0}, /* MOJI_BI 62 */
	[MOJI_BU] = {KEY_B,KEY_U,0}, /* MOJI_BU 63 */
	[MOJI_BE] = {KEY_B,KEY_E,0}, /* MOJI_BE 64 */
	[MOJI_BO] = {KEY_B,KEY_O,0}, /* MOJI_BO 65 */
	[MOJI_PA] = {KEY_P,KEY_A,0}, /* MOJI_PA 66 */
	[MOJI_PI] = {KEY_P,KEY_I,0}, /* MOJI_PI 67 */
	[MOJI_PU] = {KEY_P,KEY_U,0}, /* MOJI_PU 68 */
	[MOJI_PE] = {KEY_P,KEY_E,0}, /* MOJI_PE 69 */
	[MOJI_PO] = {KEY_P,KEY_O,0}, /* MOJI_PO 70 */
	[MOJI_WA] = {KEY_W,KEY_A,0}, /* MOJI_WA 71 */
	[MOJI_WI] = {KEY_W,KEY_I,0}, /* MOJI_WI 72 */
	[MOJI_WU] = {KEY_W,KEY_U,0}, /* MOJI_WU 73 */
	[MOJI_WE] = {KEY_W,KEY_E,0}, /* MOJI_WE 74 */
	[MOJI_WO] = {KEY_W,KEY_O,0}, /* MOJI_WO 75 */
	[MOJI_XA] = {KEY_X,KEY_A,0}, /* MOJI_XA 76 */
	[MOJI_XI] = {KEY_X,KEY_I,0}, /* MOJI_XI 77 */
	[MOJI_XU] = {KEY_X,KEY_U,0}, /* MOJI_XU 78 */
	[MOJI_XE] = {KEY_X,KEY_E,0}, /* MOJI_XE 79 */
	[MOJI_XO] = {KEY_X,KEY_O,0}, /* MOJI_XO 80 */
	[MOJI_XYA] = {KEY_X,KEY_Y,KEY_A}, /* MOJI_XYA 81 */
	[MOJI_XYI] = {KEY_X,KEY_Y,KEY_I}, /* MOJI_XYI 82 */
	[MOJI_XYU] = {KEY_X,KEY_Y,KEY_U}, /* MOJI_XYU 83 */
	[MOJI_XYE] = {KEY_X,KEY_Y,KEY_E}, /* MOJI_XYE 84 */
	[MOJI_XYO] = {KEY_X,KEY_Y,KEY_O}, /* MOJI_XYO 85 */
	[MOJI_XTU] = {KEY_X,KEY_T,KEY_U}, /* MOJI_XTU 86 */
	[MOJI_NN] = {KEY_N,KEY_N,0}, /* MOJI_NN 87 */
	[MOJI_VU] = {KEY_V,KEY_U,0}, /* MOJI_VU 88 */
	[MOJI_XKE] = {KEY_X,KEY_K,KEY_E}, /* MOJI_XYA 89 */
	[MOJI_XWA] = {KEY_X,KEY_W,KEY_A}, /* MOJI_XYI 90 */
	[MOJI_WYI] = {KEY_W,KEY_Y,KEY_I}, /* MOJI_XYU 91 */
	[MOJI_WYE] = {KEY_W,KEY_Y,KEY_E}, /* MOJI_XYE 92 */
	[MOJI_DEL] = {KEY_DELETE,0,0}, /* MOJI_DEL 93 */
	[MOJI_BS] = {KEY_BACKSPACE,0,0}, /* MOJI_BS 94 */
	[MOJI_MINUS] = {KEY_MINUS,0,0}, /* MOJI_MINUS 95 */
	[MOJI_PERIOD] = {KEY_DOT,0,0}, /* MOJI_PERIOD 96 */
	[MOJI_COMMA] = {KEY_COMMA,0,0}, /* MOJI_COMMA 97 */
	[MOJI_DAKUTEN] = {0,0,0}, /* MOJI_DAKUTEN 98 */
	[MOJI_HANDAKUTEN] = {0,0,0}, /* MOJI_HANDAKUTEN 99 */
	[MOJI_0] = {KEY_0,0,0}, /* MOJI_0 100 */
	[MOJI_1] = {KEY_1,0,0}, /* MOJI_1 101 */
	[MOJI_2] = {KEY_2,0,0}, /* MOJI_2 102 */
	[MOJI_3] = {KEY_3,0,0}, /* MOJI_3 103 */
	[MOJI_4] = {KEY_4,0,0}, /* MOJI_4 104 */
	[MOJI_5] = {KEY_5,0,0}, /* MOJI_5 105 */
	[MOJI_6] = {KEY_6,0,0}, /* MOJI_6 106 */
	[MOJI_7] = {KEY_7,0,0}, /* MOJI_7 107 */
	[MOJI_8] = {KEY_8,0,0}, /* MOJI_8 108 */
	[MOJI_9] = {KEY_9,0,0}, /* MOJI_9 109 */
	[MOJI_EQUAL] = {KEY_EQUAL,0,0}, /* MOJI_EQUAL 110 */
	[MOJI_YEN] = {KEY_YEN,0,0}, /* MOJI_YEN 111 */
	[MOJI_ATMARK] = {KEY_LEFTBRACE,0,0}, /* MOJI_ATMARK 112 */
	[MOJI_LKAKKO] = {KEY_RIGHTBRACE,0,0}, /* MOJI_LKAKKO 113 */
	[MOJI_RKAKKO] = {KEY_BACKSLASH,0,0}, /* MOJI_RKAKKO 114 */
	[MOJI_SEMICOLON] = {KEY_SEMICOLON,0,0}, /* MOJI_SEMICOLON 115 */
	[MOJI_COLON] = {KEY_APOSTROPHE,0,0}, /* MOJI_COLON 116 */
	[MOJI_SLASH] = {KEY_SLASH,0,0}, /* MOJI_SLASH 117 */
	[MOJI_QUESTION] = {KEY_LEFTSHIFT,KEY_SLASH,0}, /* MOJI_QUESTION 118 */
	[MOJI_LBRACKET] = {KEY_LEFTSHIFT,KEY_RIGHTBRACE,0}, /* MOJI_LBRACKET 119 */
	[MOJI_RBRACKET] = {KEY_LEFTSHIFT,KEY_BACKSLASH,0}, /* MOJI_RBRACKET 120 */
	[MOJI_LPAREN] = {KEY_LEFTSHIFT,KEY_8,0}, /* MOJI_LPAREN 121 */
	[MOJI_RPAREN] = {KEY_LEFTSHIFT,KEY_9,0}, /* MOJI_RPAREN 122 */
	[MOJI_ACCENTGRAVE] = {KEY_LEFTSHIFT,KEY_LEFTBRACE,0}, /* MOJI_ACCENTGRAVE 123 */
	[MOJI_PLUS] = {KEY_LEFTSHIFT,KEY_SEMICOLON,0}, /* MOJI_PLUS 124 */
	[MOJI_ASTERISK] = {KEY_LEFTSHIFT,KEY_APOSTROPHE,0}, /* MOJI_ASTERISK 125 */
	[MOJI_UNDERSCORE] = {KEY_LEFTSHIFT,KEY_RO,0}, /* MOJI_UNDERSCORE 126 */
	[MOJI_TILDE] = {KEY_Z,KEY_MINUS,0}, /* MOJI_TILDE 127 */
	[MOJI_LKAGI] = {KEY_Z,KEY_RIGHTBRACE,0}, /* MOJI_LKAGI 128 */
	[MOJI_RKAGI] = {KEY_Z,KEY_BACKSLASH,0}, /* MOJI_RKAGI 129 */
	[MOJI_ELLIPSIS] = {KEY_Z,KEY_DOT,0}, /* MOJI_ELLIPSIS 130 */
	[MOJI_NAKAGURO] = {KEY_Z,KEY_SLASH,0} /* MOJI_NAKAGURO 131 */
};

// 内部変数
KEYMAP_INFO* oyakanaTableRomaji;
KEYMAP_INFO* oyakanaDTableRomaji;
KEYMAP_INFO* oyakanaKTableRomaji;
KEYMAP_INFO* oyakanaATableRomaji;
KEYMAP_INFO* oyakanaSCTableRomaji;
KEYMAP_INFO* oyakanaSPTableRomaji;
int oyakanaTableRomajiSize = 0;
int oyakanaDTableRomajiSize = 0;
int oyakanaKTableRomajiSize = 0;
int oyakanaATableRomajiSize = 0;
int oyakanaSCTableRomajiSize = 0;
int oyakanaSPTableRomajiSize = 0;
static __u16* mojiKeyTable = 0;
static int mojiKeyTableSize = 0;
static int		_state;
static __u16	_moji; //	文字キーを記憶するための変数
static __u16	_repeat_moji; //	リピートする文字キーを記憶するための変数
static __u16	_oyayubi; //	親指キー記憶するための変数
static __u16	_repeat_oyayubi; //	リピートする親指キー記憶するための変数
static long _time1 = 0L; //	イベント発生時刻を記憶するための変数
static long _time2 = 0L; //	イベント発生時刻を記憶するための変数
static long _event_timer = 0L; //	時刻の経過に伴ってリニアにデクリメントされるタイマ変数。値が0になった時点で、ステートマシンに対してタイマイベントを発生する（ワンショット）。なお、ステートマシンに対して簡易ロジックを指定している場合、_event_timerへの値のセットは行われません。
static long last_time;

// 外部からセットされる変数
long e_charTime = 50; //	文字->親指同時打鍵検出許容期間（簡易ロジックでは無効）
long e_oyaTime = 50; //	親指->文字同時打鍵検出許容期間（簡易ロジックでは無効）
long e_nicolaTime = 50; //	親指単独打鍵みなし期間

// 親指シフトキーとみなすキーコード
__u16 e_lnaka_keycode = KEY_D; 
__u16 e_rnaka_keycode = KEY_K;
__u16 e_lko_keycode = KEY_A;
__u16 e_rko_keycode = KEY_SEMICOLON;
__u16 e_oya_keycode = KEY_SPACE;


static OYAYUBI_EVENT timer_ev;
static OYAYUBI_EVENT otherkey_ev;

void set_left_nakakey(__u16 kc) {
	if (kc != 0) {
		e_lnaka_keycode = kc;
	}
}

void set_right_nakakey(__u16 kc) {
	if (kc != 0) {
		e_rnaka_keycode = kc;
	}
}

void set_left_kokey(__u16 kc) {
	if (kc != 0) {
		e_lko_keycode = kc;
	}
}

void set_right_kokey(__u16 kc) {
	if (kc != 0) {
		e_rko_keycode = kc;
	}
}

void set_oyakey(__u16 kc) {
	if (kc != 0) {
		e_oya_keycode = kc;
	}
}

void set_char_time(long char_time){
	if (char_time <= 0 || char_time >= 2000) return;
	e_charTime = char_time;
}

void set_oya_time(long oya_time){
	if (oya_time <= 0 || oya_time >= 2000) return;
	e_oyaTime = oya_time;
}

void set_nicola_time(long nicola_time){
	if (nicola_time <= 0 || nicola_time >= 1000) return;
	e_nicolaTime = nicola_time;
}

void oyayubi_state_init() {
	oyakanaTableRomaji = (KEYMAP_INFO*)malloc(sizeof(oyakanaTableRomajiDefault));
	oyakanaDTableRomaji = (KEYMAP_INFO*)malloc(sizeof(oyakanaDTableRomajiDefault));
	oyakanaKTableRomaji = (KEYMAP_INFO*)malloc(sizeof(oyakanaKTableRomajiDefault));
	oyakanaATableRomaji = (KEYMAP_INFO*)malloc(sizeof(oyakanaATableRomajiDefault));
	oyakanaSCTableRomaji = (KEYMAP_INFO*)malloc(sizeof(oyakanaSCTableRomajiDefault));
	oyakanaSPTableRomaji = (KEYMAP_INFO*)malloc(sizeof(oyakanaSPTableRomajiDefault));
	memcpy(oyakanaTableRomaji, oyakanaTableRomajiDefault, sizeof(oyakanaTableRomajiDefault));
	memcpy(oyakanaDTableRomaji, oyakanaDTableRomajiDefault, sizeof(oyakanaDTableRomajiDefault));
	memcpy(oyakanaKTableRomaji, oyakanaKTableRomajiDefault, sizeof(oyakanaKTableRomajiDefault));
	memcpy(oyakanaATableRomaji, oyakanaATableRomajiDefault, sizeof(oyakanaATableRomajiDefault));
	memcpy(oyakanaSCTableRomaji, oyakanaSCTableRomajiDefault, sizeof(oyakanaSCTableRomajiDefault));
	memcpy(oyakanaSPTableRomaji, oyakanaSPTableRomajiDefault, sizeof(oyakanaSPTableRomajiDefault));
	oyakanaTableRomajiSize = sizeof(oyakanaTableRomajiDefault) / sizeof(KEYMAP_INFO);
	oyakanaDTableRomajiSize = sizeof(oyakanaDTableRomajiDefault) / sizeof(KEYMAP_INFO);
	oyakanaKTableRomajiSize = sizeof(oyakanaKTableRomajiDefault) / sizeof(KEYMAP_INFO);
	oyakanaATableRomajiSize = sizeof(oyakanaATableRomajiDefault) / sizeof(KEYMAP_INFO);
	oyakanaSCTableRomajiSize = sizeof(oyakanaSCTableRomajiDefault) / sizeof(KEYMAP_INFO);
	oyakanaSPTableRomajiSize = sizeof(oyakanaSPTableRomajiDefault) / sizeof(KEYMAP_INFO);

	_state = STATE_FIRST;
	_moji = 0;
	_oyayubi = 0;
	_repeat_moji = 0;
	_repeat_oyayubi = 0;
	_time1 = 0l;
	_time2 = 0l;
	_event_timer = 0;

	last_time = get_current_time();
}

Boolean is_moji_key(__u16 code) {
	if (
		code == e_lnaka_keycode || code == e_rnaka_keycode ||
		code == e_lko_keycode || code == e_rko_keycode ||
		code == e_oya_keycode
	) {
		return FALSE;
	}
	for(int i = 0; i < mojiKeyTableSize; i++) {
		__u16 m = mojiKeyTable[i];
		if(code == m) {
			return TRUE;
		}
	}
	return FALSE;
}

void add_key_moji(__u16 kc, int m){
	for(int i = 0; i < oyakanaTableRomajiSize; i++) {
		KEYMAP_INFO *p = oyakanaTableRomaji + i;
		if (p->keyCode == kc) {
			p->moji = m;
			return;
		}
	}

	KEYMAP_INFO* newtbl = (KEYMAP_INFO*)malloc((oyakanaTableRomajiSize + 1)*sizeof(KEYMAP_INFO));
	memcpy(newtbl, oyakanaTableRomaji, oyakanaTableRomajiSize * sizeof(KEYMAP_INFO));
	free(oyakanaTableRomaji);
	oyakanaTableRomaji = newtbl;

	KEYMAP_INFO new_keymap_info = { kc, m };
	oyakanaTableRomaji[oyakanaTableRomajiSize] = new_keymap_info;
	oyakanaTableRomajiSize++;
}

void add_left_key_moji(__u16 kc, int m){
	for(int i = 0; i < oyakanaDTableRomajiSize; i++) {
		KEYMAP_INFO *p = oyakanaDTableRomaji + i;
		if (p->keyCode == kc) {
			p->moji = m;
			return;
		}
	}

	KEYMAP_INFO* newtbl = (KEYMAP_INFO*)malloc((oyakanaDTableRomajiSize + 1)*sizeof(KEYMAP_INFO));
	memcpy(newtbl, oyakanaDTableRomaji, oyakanaDTableRomajiSize * sizeof(KEYMAP_INFO));
	free(oyakanaDTableRomaji);
	oyakanaDTableRomaji = newtbl;

	KEYMAP_INFO new_keymap_info = { kc, m };
	oyakanaDTableRomaji[oyakanaDTableRomajiSize] = new_keymap_info;
	oyakanaDTableRomajiSize++;
}

void add_right_key_moji(__u16 kc, int m){
	for(int i = 0; i < oyakanaKTableRomajiSize; i++) {
		KEYMAP_INFO *p = oyakanaKTableRomaji + i;
		if (p->keyCode == kc) {
			p->moji = m;
			return;
		}
	}

	KEYMAP_INFO* newtbl = (KEYMAP_INFO*)malloc((oyakanaKTableRomajiSize + 1)*sizeof(KEYMAP_INFO));
	memcpy(newtbl, oyakanaKTableRomaji, oyakanaKTableRomajiSize * sizeof(KEYMAP_INFO));
	free(oyakanaKTableRomaji);
	oyakanaKTableRomaji = newtbl;

	KEYMAP_INFO new_keymap_info = { kc, m };
	oyakanaKTableRomaji[oyakanaKTableRomajiSize] = new_keymap_info;
	oyakanaKTableRomajiSize++;
}

void add_leftk_key_moji(__u16 kc, int m){
	for(int i = 0; i < oyakanaATableRomajiSize; i++) {
		KEYMAP_INFO *p = oyakanaATableRomaji + i;
		if (p->keyCode == kc) {
			p->moji = m;
			return;
		}
	}

	KEYMAP_INFO* newtbl = (KEYMAP_INFO*)malloc((oyakanaATableRomajiSize + 1)*sizeof(KEYMAP_INFO));
	memcpy(newtbl, oyakanaATableRomaji, oyakanaATableRomajiSize * sizeof(KEYMAP_INFO));
	free(oyakanaATableRomaji);
	oyakanaATableRomaji = newtbl;

	KEYMAP_INFO new_keymap_info = { kc, m };
	oyakanaATableRomaji[oyakanaATableRomajiSize] = new_keymap_info;
	oyakanaATableRomajiSize++;
}

void add_rightk_key_moji(__u16 kc, int m){
	for(int i = 0; i < oyakanaSCTableRomajiSize; i++) {
		KEYMAP_INFO *p = oyakanaSCTableRomaji + i;
		if (p->keyCode == kc) {
			p->moji = m;
			return;
		}
	}

	KEYMAP_INFO* newtbl = (KEYMAP_INFO*)malloc((oyakanaSCTableRomajiSize + 1)*sizeof(KEYMAP_INFO));
	memcpy(newtbl, oyakanaSCTableRomaji, oyakanaSCTableRomajiSize * sizeof(KEYMAP_INFO));
	free(oyakanaSCTableRomaji);
	oyakanaSCTableRomaji = newtbl;

	KEYMAP_INFO new_keymap_info = { kc, m };
	oyakanaSCTableRomaji[oyakanaSCTableRomajiSize] = new_keymap_info;
	oyakanaSCTableRomajiSize++;
}

void add_space_key_moji(__u16 kc, int m){
	for(int i = 0; i < oyakanaSPTableRomajiSize; i++) {
		KEYMAP_INFO *p = oyakanaSPTableRomaji + i;
		if (p->keyCode == kc) {
			p->moji = m;
			return;
		}
	}

	KEYMAP_INFO* newtbl = (KEYMAP_INFO*)malloc((oyakanaSPTableRomajiSize + 1)*sizeof(KEYMAP_INFO));
	memcpy(newtbl, oyakanaSPTableRomaji, oyakanaSPTableRomajiSize * sizeof(KEYMAP_INFO));
	free(oyakanaSPTableRomaji);
	oyakanaSPTableRomaji = newtbl;

	KEYMAP_INFO new_keymap_info = { kc, m };
	oyakanaSPTableRomaji[oyakanaSPTableRomajiSize] = new_keymap_info;
	oyakanaSPTableRomajiSize++;
}

void create_infotables() {
	__u16 buffer[BUFSIZE];
	__u16 *p = buffer;

	int len = oyakanaTableRomajiSize;
	for(int i=0; i < len; i++) {
		if (p - buffer >=BUFSIZE) break;
		KEYMAP_INFO *ki = oyakanaTableRomaji + i;
		if(ki->keyCode != 0) {
			Boolean find_flg = FALSE;
			for(__u16 *c = buffer ; c < p ; c++) {
				if(*c == ki->keyCode) {
					find_flg = TRUE;
				}
			}
			if (! find_flg) {
				*p++ = ki->keyCode;
			}
		}
	}
	len = oyakanaDTableRomajiSize;
	for(int i = 0; i < len; i++) {
		if (p - buffer >=BUFSIZE) break;
		KEYMAP_INFO *ki = oyakanaDTableRomaji + i;
		if(ki->keyCode != 0) {
			Boolean find_flg = FALSE;
			for(__u16 *c = buffer ; c < p ; c++) {
				if(*c == ki->keyCode) {
					find_flg = TRUE;
				}
			}
			if (! find_flg) {
				*p++ = ki->keyCode;
			}
		}
	}
	len = oyakanaKTableRomajiSize;
	for(int i = 0; i < len; i++) {
		if (p - buffer >=BUFSIZE) break;
		KEYMAP_INFO *ki = oyakanaKTableRomaji + i;
		if(ki->keyCode != 0) {
			Boolean find_flg = FALSE;
			for(__u16 *c = buffer ; c < p ; c++) {
				if(*c == ki->keyCode) {
					find_flg = TRUE;
				}
			}
			if (! find_flg) {
				*p++ = ki->keyCode;
			}
		}
	}
	len = oyakanaATableRomajiSize;
	for(int i = 0; i < len; i++) {
		if (p - buffer >=BUFSIZE) break;
		KEYMAP_INFO *ki = oyakanaATableRomaji + i;
		if(ki->keyCode != 0) {
			Boolean find_flg = FALSE;
			for(__u16 *c = buffer ; c < p ; c++) {
				if(*c == ki->keyCode) {
					find_flg = TRUE;
				}
			}
			if (! find_flg) {
				*p++ = ki->keyCode;
			}
		}
	}
	len = oyakanaSCTableRomajiSize;
	for(int i = 0; i < len; i++) {
		if (p - buffer >=BUFSIZE) break;
		KEYMAP_INFO *ki = oyakanaSCTableRomaji + i;
		if(ki->keyCode != 0) {
			Boolean find_flg = FALSE;
			for(__u16 *c = buffer ; c < p ; c++) {
				if(*c == ki->keyCode) {
					find_flg = TRUE;
				}
			}
			if (! find_flg) {
				*p++ = ki->keyCode;
			}
		}
	}
	len = oyakanaSPTableRomajiSize;
	for(int i = 0; i < len; i++) {
		if (p - buffer >=BUFSIZE) break;
		KEYMAP_INFO *ki = oyakanaSPTableRomaji + i;
		if(ki->keyCode != 0) {
			Boolean find_flg = FALSE;
			for(__u16 *c = buffer ; c < p ; c++) {
				if(*c == ki->keyCode) {
					find_flg = TRUE;
				}
			}
			if (! find_flg) {
				*p++ = ki->keyCode;
			}
		}
	}
	mojiKeyTableSize = (p-buffer);
	mojiKeyTable = (__u16*)malloc(mojiKeyTableSize*sizeof(__u16));
	__u16 *d = mojiKeyTable;
	for(__u16 *c = buffer; c < p; c++, d++) {
		*d = *c;
	}
}

void close_oya_state() {
	free(oyakanaTableRomaji) ;
	free(oyakanaDTableRomaji);
	free(oyakanaKTableRomaji);
	free(oyakanaATableRomaji);
	free(oyakanaSCTableRomaji);
	free(oyakanaSPTableRomaji);
	free(mojiKeyTable);
	mojiKeyTable = NULL;
	mojiKeyTableSize = 0;
}

Boolean is_moji_down(OYAYUBI_EVENT ev) {
	if(! is_moji_key(ev.keyCode) ) {
		return FALSE;
	}
	if (ev.eventType == ET_KEYDOWN && ! ev.isRepeat) {
		return TRUE;
	}
	return FALSE;
}

Boolean is_moji_repeat(OYAYUBI_EVENT ev) {
	if(! is_moji_key(ev.keyCode)) {
		return FALSE;
	}
	if (ev.eventType == ET_KEYDOWN && ev.isRepeat) {
		return TRUE;
	}
	return FALSE;
}

Boolean is_moji_up(OYAYUBI_EVENT ev) {
	if(! is_moji_key(ev.keyCode) ) {
		return FALSE;
	}
	if (ev.eventType == ET_KEYUP) {
		return TRUE;
	}
	return FALSE;
}

Boolean is_oya_down(OYAYUBI_EVENT ev) {
	if(
		ev.keyCode != e_lnaka_keycode && ev.keyCode != e_rnaka_keycode &&
		ev.keyCode != e_lko_keycode && ev.keyCode != e_rko_keycode &&
		ev.keyCode != e_oya_keycode
	) {
		return FALSE;
	}
	if (ev.eventType == ET_KEYDOWN && ! ev.isRepeat) {
		return TRUE;
	}
	return FALSE;
}

Boolean is_oya_repeat(OYAYUBI_EVENT ev) {
	if(
		ev.keyCode != e_lnaka_keycode && ev.keyCode != e_rnaka_keycode &&
		ev.keyCode != e_lko_keycode && ev.keyCode != e_rko_keycode &&
		ev.keyCode != e_oya_keycode
	) {
		return FALSE;
	}
	if (ev.eventType == ET_KEYDOWN && ev.isRepeat) {
		return TRUE;
	}
	return FALSE;
}

Boolean is_oya_up(OYAYUBI_EVENT ev) {
	if(
		ev.keyCode != e_lnaka_keycode && ev.keyCode != e_rnaka_keycode &&
		ev.keyCode != e_lko_keycode && ev.keyCode != e_rko_keycode &&
		ev.keyCode != e_oya_keycode
	) {
		return FALSE;
	}
	if (ev.eventType == ET_KEYUP) {
		return TRUE;
	}
	return FALSE;
}

Boolean is_otherkey_down(OYAYUBI_EVENT ev) {
	if(is_moji_key(ev.keyCode)) {
		return FALSE;
	}
	if (
		ev.keyCode == e_lnaka_keycode || ev.keyCode == e_rnaka_keycode ||
		ev.keyCode == e_lko_keycode || ev.keyCode == e_rko_keycode ||
		ev.keyCode == e_oya_keycode
	) {
		return FALSE;
	}
	return TRUE;
}

Boolean is_timer(OYAYUBI_EVENT ev) {
	if (ev.eventType == ET_TIMER) {
		return TRUE;
	}
	return FALSE;
}

long get_current_time() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

int is_state_first() {
	return (_state == STATE_FIRST);
}

void output_moji(__u16 m) {
	int len = oyakanaTableRomajiSize;
	for(int i=0; i < len; i++) {
		KEYMAP_INFO *ki = oyakanaTableRomaji + i;
		if(ki->keyCode == m && ki->moji <= MOJI_MAX) {
			ROMAJI_INFO *ri = romaKeys + ki->moji;
			put_romaji(*ri);
			break;
		}
	}
}

void output_oya(__u16 o) {
	if (
		o == e_lnaka_keycode || o == e_rnaka_keycode ||
		o == e_lko_keycode || o == e_rko_keycode 
	) {
		output_moji(o);
	} else {
		output_char(o);
	}
}

void output_oya_moji(__u16 okey, __u16 mkey) {
	if (okey == e_lnaka_keycode) {
		// 左中指シフト
		int len = oyakanaDTableRomajiSize;
		for(int i = 0; i < len; i++) {
			KEYMAP_INFO *ki = oyakanaDTableRomaji + i;
			if(ki->keyCode == mkey && ki->moji <= MOJI_MAX) {
				ROMAJI_INFO *ri = romaKeys + ki->moji;
				put_romaji(*ri);
				return;
			}
		}
	}
	else if (okey == e_rnaka_keycode) {
		// 右中指シフト
		int len = oyakanaKTableRomajiSize;
		for(int i = 0; i < len; i++) {
			KEYMAP_INFO *ki = oyakanaKTableRomaji + i;
			if(ki->keyCode == mkey && ki->moji <= MOJI_MAX) {
				ROMAJI_INFO *ri = romaKeys + ki->moji;
				put_romaji(*ri);
				return;
			}
		}
	}
	else if (okey == e_lko_keycode) {
		// 左小指シフト
		int len = oyakanaATableRomajiSize;
		for(int i = 0; i < len; i++) {
			KEYMAP_INFO *ki = oyakanaATableRomaji + i;
			if(ki->keyCode == mkey && ki->moji <= MOJI_MAX) {
				ROMAJI_INFO *ri = romaKeys + ki->moji;
				put_romaji(*ri);
				return;
			}
		}
	}
	else if (okey == e_rko_keycode) {
		// 右小指シフト
		int len = oyakanaSCTableRomajiSize;
		for(int i = 0; i < len; i++) {
			KEYMAP_INFO *ki = oyakanaSCTableRomaji + i;
			if(ki->keyCode == mkey && ki->moji <= MOJI_MAX) {
				ROMAJI_INFO *ri = romaKeys + ki->moji;
				put_romaji(*ri);
				return;
			}
		}
	}
	else if (okey == e_oya_keycode) {
		// 親指シフト
		int len = oyakanaSPTableRomajiSize;
		for(int i = 0; i < len; i++) {
			KEYMAP_INFO *ki = oyakanaSPTableRomaji + i;
			if(ki->keyCode == mkey && ki->moji <= MOJI_MAX) {
				ROMAJI_INFO *ri = romaKeys + ki->moji;
				put_romaji(*ri);
				return;
			}
		}
	}
}

Boolean is_acceptable(int keycode) {
	if(is_moji_key(keycode) ) {
		return TRUE;
	}
	if (
		keycode == e_lnaka_keycode || keycode == e_rnaka_keycode ||
		keycode == e_lko_keycode || keycode == e_rko_keycode ||
		keycode == e_oya_keycode
	) {
		return TRUE;
	}
	return FALSE;
}

void update_event_timer() {
	long current_time = get_current_time();
	long millis = current_time - last_time;

	if (_event_timer > 0) {
		_event_timer -= millis;
		if (_event_timer <= 0) {
			memset(&timer_ev, 0, sizeof(timer_ev));
			timer_ev.eventType = ET_TIMER;
			handle_oyayubi_event(timer_ev);
		}
	}
	if (_event_timer <= 0) {
		_event_timer = 0;
	}
	last_time = current_time;
}

void on_otherkey_down(__u16 kc) {
	memset(&otherkey_ev, 0, sizeof(otherkey_ev));
	otherkey_ev.eventType = ET_KEYDOWN;
	otherkey_ev.isRepeat = 0;
	otherkey_ev.keyCode = kc;
	handle_oyayubi_event(otherkey_ev);
}

void handle_oyayubi_event(OYAYUBI_EVENT ev) {
	long current_time = get_current_time();
	switch(_state) {
	case STATE_FIRST: // 初期状態

		//E11 文字キーの押下を検出。検出した文字キーをmojiにセット。_time1に時刻を記憶。_event_timerにe_charTimeをセット。
		if (is_moji_down(ev)) {
			_moji = ev.keyCode;
			_time1 = current_time;
			_event_timer = e_charTime;
			_state = STATE_MOJIHOLD;
			break;
		}

		//E12 親指キーの押下を検出。検出した親指キーをoyayubiにセット。_time2に時刻を記憶。_event_timerにe_oyaTimeをセット。
		if (is_oya_down(ev)) {
			_oyayubi = ev.keyCode;
			_time2 = current_time;
			_event_timer = e_oyaTime;
			_state = STATE_OYAHOLD;
			break;
		}
		break;

	case STATE_MOJIHOLD: // 文字キー押下中状態

		//E21 文字キーのリリースを検出。または、対象外のキー入力を検出。mojiを出力。初期状態に遷移
		if (is_moji_up(ev) || is_otherkey_down(ev)) {
			output_moji(_moji);
			_repeat_moji = 0;
			_repeat_oyayubi = 0;
			_state = STATE_FIRST;
			break;
		}

		//E22 キーボードリピートを検出。mojiを出力。mojiをrepeat_mojiにセット。リピート状態に遷移
		if (is_moji_repeat(ev) || is_oya_repeat(ev)) {
			output_moji(_moji);
			_repeat_moji = _moji;
			_state = STATE_REPEAT;
			break;
		}

		//E23 タイマイベントを検出。mojiを出力。mojiをrepeatmojiにセット。リピート状態に遷移。
		//簡易ロジックでは、このイベントは発生しません。
		if (is_timer(ev)) {
			output_moji(_moji);
			_repeat_moji = _moji;
			_state = STATE_REPEAT;
			break;
		}

		//E24 親指キーの押下を検出。検出した親指キーをoyayubiにセット。_time2に時刻を記憶。_event_timerにe-oyaTimeをセット。文字キー親指キー押下中状態に遷移
		if (is_oya_down(ev)) {
			_oyayubi = ev.keyCode;
			_time2 = current_time;
			_event_timer = e_oyaTime;
			_state = STATE_MOJIOYAHOLD;
			break;
		}

		//E25 文字キーの押下を検出。mojiを出力。検出した文字キーをmojiにセット。_time1に時刻を記憶。_event_timerにe-charTimeをセット。文字キー押下中状態に遷移
		if (is_moji_down(ev)) {
			output_moji(_moji);
			_moji = ev.keyCode;
			_time1 = current_time;
			_event_timer = e_charTime;
			_state = STATE_MOJIHOLD;
			break;
		}

		break;

	case STATE_OYAHOLD: // 親指キー押下中状態

		//E31 親指キーのリピートを検出。oyayubiをrepeat_oyayubiにセット。リピート状態に遷移
		if (is_oya_repeat(ev)) {
			_repeat_oyayubi = _oyayubi;
			_state = STATE_REPEAT;
			break;
		}

		//E32 タイマイベントを検出。oyayubiを出力。oyayubiをrepeat_oyayubiにセット。リピート状態に遷移。
		//簡易ロジックでは、このイベントは発生しません。
		if (is_timer(ev)) {
			output_oya(_oyayubi);
			_state = STATE_REPEAT;
			break;
		}

		//E33 文字キーの押下を検出。検出した文字キーをmojiにセット。moji+oyayubiを出力。oyayubiをrepeat_oyayubiにセット。mojiをrepeat_mojiにセット。リピート状態に遷移
		if (is_moji_down(ev) || is_oya_down(ev)) {
			_moji = ev.keyCode;
			output_oya_moji(_oyayubi, _moji);
			_repeat_oyayubi = _oyayubi;
			_repeat_moji = _moji;
			_state = STATE_REPEAT;
			break;
		}

		//E34 親指キーの押下を検出。oyayubiを出力。検出した親指キーをoyayubiにセット。_time2に時刻を記憶。_event_timerにe-oyaTimeをセット。文字キー親指キー押下中状態に遷移
		/*
		if (is_oya_down(ev)) {
			output_oya(_oyayubi);
			_oyayubi = ev.keyCode;
			_time2 = current_time;
			_event_timer = e_oyaTime;
			_state = STATE_MOJIOYAHOLD;
			break;
		}
		*/
		
		//E35 親指キーのリリースを検出。または、対象外のキーの押下を検出。oyayubiを出力。初期状態に遷移
		if (is_oya_up(ev) || is_otherkey_down(ev)) {
			output_oya(_oyayubi);
			_repeat_moji = 0;
			_repeat_oyayubi = 0;
			_state = STATE_FIRST;
			break;
		}
		break;

	case STATE_MOJIOYAHOLD: // 文字キー親指キー押下中状態

		//E41 キーのリピートを検出(親指キーのみしかあり得ない)。moji+oyayubiを出力。mojiをrepeat_mojiにセット。oyayubiをrepeat_oyayubiにセット。リピート状態に遷移
		if (is_oya_repeat(ev) || is_moji_repeat(ev)) {
			output_oya_moji(_oyayubi, _moji);
			_repeat_moji = _moji;
			_repeat_oyayubi = _oyayubi;
			_state = STATE_REPEAT;
			break;
		}

		//E42 タイマイベントを検出。moji+oyayubiを出力。oyayubiをrepeat_oyayubiにセット。mojiをrepeat_mojiにセット。リピート状態に遷移。
		//簡易ロジックでは、このイベントは発生しません。
		if (is_timer(ev)) {
			output_oya_moji(_oyayubi, _moji);
			_repeat_oyayubi = _oyayubi;
			_repeat_moji = _moji;
			_state = STATE_REPEAT;
			break;
		}

		//E43 文字キーの押下を検出し、current_time - _time2 < _time2 - _time1を満たす場合。mojiを出力。oyayubi+検出した文字を出力。oyayubiをrepeat_oyayubiにセット。検出した文字キーをrepeat_mojiにセット。リピート状態に遷移
		if (is_moji_down(ev) && (current_time - _time2 < _time2 - _time1)) {
			output_moji(_moji);
			output_oya_moji(_oyayubi, ev.keyCode);
			_repeat_oyayubi = _oyayubi;
			_repeat_moji = ev.keyCode;
			_state = STATE_REPEAT;
			break;
		}

		//E44 親指キーの押下を検出。moji+oyayubiを出力。検出した親指キーをoyayubiにセット。_time2に時刻を記憶。_event_timerにe-oyaTimeをセット。親指キー押下中状態に遷移
		if (is_oya_down(ev)) {
			output_oya_moji(_oyayubi, _moji);
			_oyayubi = ev.keyCode;
			_time2 = current_time;
			_event_timer = e_oyaTime;
			_state = STATE_OYAHOLD;
			break;
		}

		//E45 親指キーのリリースを検出。または、対象外のキーの押下を検出 moji+oyayubiを出力。初期状態に遷移
		if (is_oya_up(ev) || is_otherkey_down(ev)) {
			output_oya_moji(_oyayubi, _moji);
			_repeat_moji = 0;
			_repeat_oyayubi = 0;
			_state = STATE_FIRST;
			break;
		}

		//E46 文字キーのリリースを検出し、(current_time - _time2 <= e_nicolaTime) && (_time2 - _time1 > current_time - _time2 ) を満たす場合。	mojiを出力。親指キー押下中状態に遷移。oyayubiが維持されていることに注意
		if (is_moji_up(ev) && (current_time - _time2 <= e_nicolaTime) && (_time2 - _time1 > current_time - _time2)) {
			output_moji(_moji);
			_state = STATE_OYAHOLD;
			break;
		}
		else if (is_moji_up(ev)) {
			//E47 文字キーのリリースを検出。E46の条件を満たさない場合。moji+oyayubiを出力。初期状態に遷移
			output_oya_moji(_oyayubi, _moji);
			_repeat_moji = 0;
			_repeat_oyayubi = 0;
			_state = STATE_FIRST;
			break;
		}

		//E48 文字キーの押下を検出し、current_time - _time2 >= _time2 - _time1を満たす場合。moji+oyayubiを出力。検出した文字キーをmojiにセット。_event_timerにe-charTimeをセット。文字キー押下中状態に遷移
		if (is_moji_down(ev) && (current_time - _time2 >= _time2 - _time1)) {
			output_oya_moji(_oyayubi, _moji);
			_moji = ev.keyCode;
			_event_timer = e_charTime;
			_state = STATE_MOJIHOLD;
			break;
		}
		break;

	case STATE_REPEAT: // リピート中状態

		//E51 リピートを検出 repeat_oyayubi+repeat_mojiを出力。リピート中状態に遷移。repeat_oyayubiまたはrepeat_mojiのいずれかがセットされていない場合は、セットされている側の単独出力となる
		if (is_oya_repeat(ev) || is_moji_repeat(ev)) {
			if (_repeat_oyayubi != 0 && _repeat_moji != 0) {
				output_oya_moji(_repeat_oyayubi, _repeat_moji);
			}
			else if (_repeat_oyayubi != 0) {
				output_oya(_repeat_oyayubi);
			}
			else if (_repeat_moji != 0) {
				output_moji(_repeat_moji);
			}
			_state = STATE_REPEAT;
			break;
		}

		//E52 親指キーのリリースを検出。または対象外のキー入力を検出。初期状態に遷移
		if (is_oya_up(ev) || is_otherkey_down(ev)) {
			_repeat_moji = 0;
			_repeat_oyayubi = 0;
			_state = STATE_FIRST;
			break;
		}

		//E53 文字キーのリリースを検出。初期状態に遷移
		if (is_moji_up(ev)) {
			_repeat_moji = 0;
			_repeat_oyayubi = 0;
			_state = STATE_FIRST;
			break;
		}

		//E54 親指キーの押下を検出（リピート中以外のキーしか発生しない）検出した親指キーをoyayubiにセット。_time2に時刻を記憶。_event_timerにe-oyaTimeをセット。親指キー押下中状態に遷移
		if (is_oya_down(ev)) {
			_oyayubi = ev.keyCode;
			_time2 = current_time;
			_event_timer = e_oyaTime;
			_state = STATE_OYAHOLD;
			break;
		}

		//E55 文字キーの押下を検出（リピート中以外のキーしか発生しない）検出した文字キーをmojiにセット。_time1に時刻を記憶。_event_timerにe-charTimeをセット。文字キー押下中状態に遷移
		if (is_moji_down(ev)) {
			_moji = ev.keyCode;
			_time1 = current_time;
			_event_timer = e_charTime;
			_state = STATE_MOJIHOLD;
			break;
		}
		break;

	default:
		_state = STATE_FIRST;
		break;
	}
}
