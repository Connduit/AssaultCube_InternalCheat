#include <stdio.h>
#include <iostream>

#include "esp.h"
#include "constants.h"
#include "geom.h"

const float FOV = 90;



// TODO: bool ESP::isInFOV()
bool ESP::isInFov(Player* locPlayerPtr, Vector3 origin)
{
	Vector3 angle = CalcAngle(locPlayerPtr->pos, origin);
	Vector3 playerAngle(locPlayerPtr->ypr.x - 90, locPlayerPtr->ypr.y, 0);
	ESP::normalizeAngle(playerAngle);

	Vector3 angleDiff = playerAngle - angle;
	ESP::normalizeAngle(angleDiff);
	return (fabs(angleDiff.x) <= FOV / 2 && fabs(angleDiff.y) <= FOV / 2);

	//return true;
}

bool isValidTarget(Player* player)
{
	if (player->health > 100 || player->health <= 0 || !ESP::isInFov(localPlayerPtr, player->o))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// TODO: is this function needed? could just do angle.x mod 360, right?
void ESP::normalizeAngle(Vector3 angle)
{
	if (angle.x > 360)
	{
		angle.x -= 360;
	}
	if (angle.x < 0)
	{
		angle.x += 360;
	}
	if (angle.y > 90)
	{
		angle.y -= 90;
	}
	if (angle.y > -90)
	{
		angle.y += 90;
	}
}

Player* ESP::getNearestPlayer()
{
	Player* nearestPlayer = nullptr;
	float nearestDistance = 99999999.0f; // TODO: make this value be the max float value

	for (int i = 1; i < numPlayers + 1; ++i)
	{
		Player* player = players->players[i];
		if (!isValidTarget(player))
		{
			continue;
		}
		float distance = localPlayerPtr->pos.Distance(player->pos);
			if (distance < nearestDistance)
			{
				nearestDistance = distance;
				nearestPlayer = player;
			}
	}
	return nearestPlayer;
}

Player* ESP::getNearestEntityAngle()
{
	std::cout << "getNearestEntityAngle" << std::endl;
	Vector3 playerAngle(localPlayerPtr->ypr.x + 180, localPlayerPtr->ypr.y, 0);
	ESP::normalizeAngle(playerAngle);
	Player* nearestPlayer = nullptr;
	float smallestAngle = 99999999.0f; // TODO: instead of having some max float, make a class or some type called angle... maybe some unit type

	for (int i = 1; i < numPlayers + 1; ++i)
	{
		Player* player = players->players[i];
		if (!isValidTarget(player))
		{
			continue;
		}
		Vector3 targetAngle = CalcAngle(localPlayerPtr->pos, player->pos);
		Vector3 angleDiff = playerAngle - targetAngle;
		ESP::normalizeAngle(angleDiff);
		float angleMagnitude = angleDiff.Length();
		if (angleMagnitude < smallestAngle)
		{
			smallestAngle = angleMagnitude;
			nearestPlayer = player;
		}

	}
	return nearestPlayer;
}

void ESP::aimbot()
{
	if (!GetAsyncKeyState(VK_SHIFT))
	{
		return;
	}

	Player* target = getNearestPlayer();
	if (target == nullptr)
	{
		std::cout << "getNearestPlayer is nullptr" << std::endl;
		return;
	}

	Vector3 angle = CalcAngle(localPlayerPtr->pos, target->pos);
	//std::cout << "before: " << angle.x << std::endl;
	angle.x += 90;
	//std::cout << "after: " << angle.x << std::endl;
	localPlayerPtr->ypr.x = angle.x;
	localPlayerPtr->ypr.y = angle.y;

}