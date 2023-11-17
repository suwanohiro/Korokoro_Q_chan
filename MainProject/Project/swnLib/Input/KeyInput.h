#pragma once
#include "Mof.h"
#include "InputData/KeyBord.h"

class KeyInput {
public:
	static bool isPush(KeyBord Key) {
		return g_pInput->IsKeyPush((unsigned char)Key);
	}

	static bool isPull(KeyBord Key) {
		return g_pInput->IsKeyPull((unsigned char)Key);
	}

	static bool isHold(KeyBord Key) {
		return g_pInput->IsKeyHold((unsigned char)Key);
	}
};