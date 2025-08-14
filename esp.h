#pragma once

#include "genCode.h"

namespace ESP
{
	bool isInFov(Player* locPlayerPtr, Vector3 origin);
	Player* getNearestPlayer();
	Player* getNearestEntityAngle();
	void aimbot();
	void normalizeAngle(Vector3 angle);
}