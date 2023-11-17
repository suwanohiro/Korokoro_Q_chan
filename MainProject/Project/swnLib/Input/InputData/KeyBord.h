#pragma once

#include "Mof.h"
#include "dinput.h"

enum class KeyBord {
	// 数字
	_0 = DIK_0,						// 0
	_1 = DIK_1,						// 1
	_2 = DIK_2,						// 2
	_3 = DIK_3,						// 3
	_4 = DIK_4,						// 4
	_5 = DIK_5,						// 5
	_6 = DIK_6,						// 6
	_7 = DIK_7,						// 7
	_8 = DIK_8,						// 8
	_9 = DIK_9,						// 9

	// 数字(テンキー)
	NumPad_0 = DIK_NUMPAD0,			// (テンキー) 0
	NumPad_1 = DIK_NUMPAD1,			// (テンキー) 1
	NumPad_2 = DIK_NUMPAD2,			// (テンキー) 2
	NumPad_3 = DIK_NUMPAD3,			// (テンキー) 3
	NumPad_4 = DIK_NUMPAD4,			// (テンキー) 4
	NumPad_5 = DIK_NUMPAD5,			// (テンキー) 5
	NumPad_6 = DIK_NUMPAD6,			// (テンキー) 6
	NumPad_7 = DIK_NUMPAD7,			// (テンキー) 7
	NumPad_8 = DIK_NUMPAD8,			// (テンキー) 8
	NumPad_9 = DIK_NUMPAD9,			// (テンキー) 9

	// アルファベット
	A = DIK_A,						// A
	B = DIK_B,						// B
	C = DIK_C,						// C
	D = DIK_D,						// D
	E = DIK_E,						// E
	F = DIK_F,						// F
	G = DIK_G,						// G
	H = DIK_H,						// H
	I = DIK_I,						// I
	J = DIK_J,						// J
	K = DIK_K,						// K
	L = DIK_L,						// L
	M = DIK_M,						// M
	N = DIK_N,						// N
	O = DIK_O,						// O
	P = DIK_P,						// P
	Q = DIK_Q,						// Q
	R = DIK_R,						// R
	S = DIK_S,						// S
	T = DIK_T,						// T
	U = DIK_U,						// U
	V = DIK_V,						// V
	W = DIK_W,						// W
	X = DIK_X,						// X
	Y = DIK_Y,						// Y
	Z = DIK_Z,						// Z

	// ファンクションキー
	F1 = DIK_F1,					// F1
	F2 = DIK_F2,					// F2
	F3 = DIK_F3,					// F3
	F4 = DIK_F4,					// F4
	F5 = DIK_F5,					// F5
	F6 = DIK_F6,					// F6
	F7 = DIK_F7,					// F7
	F8 = DIK_F8,					// F8
	F9 = DIK_F9,					// F9
	F10 = DIK_F10,					// F10
	F11 = DIK_F11,					// F11
	F12 = DIK_F12,					// F12

	// 方向キー
	Up = DIK_UP,					// 上
	Down = DIK_DOWN,				// 下
	Left = DIK_LEFT,				// 左
	Right = DIK_RIGHT,				// 右

	// 特殊キー
	BackSpace = DIK_BACKSPACE,		// BackSpace
	Return = DIK_RETURN,			// Enter
	End = DIK_END,					// End
	Enter = DIK_RETURN,				// Enter
	Esc = DIK_ESCAPE,				// Escape
	Home = DIK_HOME,				// Home
	PageUp = DIK_PGUP,				// PageUp
	PageDown = DIK_PGDN,			// PageDown
	Space = DIK_SPACE,				// Space

};
