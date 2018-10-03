#pragma once

class CPlayer
{
public:
	char pad_0x0000[0x344]; //0x0000

	__int32 Health; //0x0344 
	__int32 MaxHealth; //0x0348 

	char pad_0x034C[0x714]; //0x034C

	__int32 Mana; //0x0A60 
	__int32 MaxMana;

}; //Size=0x0C40

