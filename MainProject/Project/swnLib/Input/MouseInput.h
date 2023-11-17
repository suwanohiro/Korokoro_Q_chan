#pragma once
#include "Mof.h"
#include "InputData/MouseKey.h"

class MouseInput {
public:
	static bool isPush(MouseKey Key) {
		return g_pInput->IsMouseKeyPush((unsigned char)Key);
	}

	static bool isPull(MouseKey Key) {
		return g_pInput->IsMouseKeyPull((unsigned char)Key);
	}

	static bool isHold(MouseKey Key) {
		return g_pInput->IsMouseKeyHold((unsigned char)Key);
	}

	static bool isWheelMove(MouseWheel directions) {
		float mouseWheelMove = g_pInput->GetMouseWheelMove();
		bool flg[3] = {
			mouseWheelMove > 0,
			mouseWheelMove < 0,
			!flg[0] && !flg[1]
		};

		return flg[(int)directions];
	}
};
