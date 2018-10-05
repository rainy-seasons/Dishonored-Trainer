#include "CInventory.h"

class CPlayer
{
public:
	char pad_0x0000[0x344]; //0x0000
	__int32 Health; //0x0344 
	__int32 MaxHealth; //0x0348 
	char pad_0x034C[0x250]; //0x034C
	CInventory* Inventory; //0x059C -- Array of pointers to things like ammo array, item array, etc. ???
	char pad_0x05A0[0x4C0]; //0x05A0
	__int32 Mana; //0x0A60 
	__int32 MaxMana; //0x0A64 
	char pad_0x0A68[0xDD8]; //0x0A68
}; //Size=0x1840