#pragma once
#include "CAmmo.h"

// This seems to have pointers to things like the Ammo array
// and an item array. 
// TODO:
// Do more reversing on this and rename to something more fitting.
class CInventory
{
public:
	char pad_0x0000[0xBC]; //0x0000
	CAmmo* Ammo; //0x00BC 
	char pad_0x00C0[0x344]; //0x00C0

}; //Size=0x0404