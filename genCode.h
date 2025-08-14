#pragma once

#include <math.h>
#include <windows.h>
#include <string>

#include "geom.h"

class Player
{
public:
	//void* vtable;
	Vector3 o; //origin
	Vector3 vel; //0x0010
	Vector3 N0000006E; //0x001C
	Vector3 pos; //0x0028
	Vector3 ypr;
	//float yaw; //0x0034
	//float pitch; //0x0038
	//float roll; //0x003C
	char pad_0040[172]; //0x0040
	INT32 health; //0x00EC
	char pad_00F0[120]; //0x00F0


	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0118


class EntityList
{
public:
	Player* players[64];
private:
};