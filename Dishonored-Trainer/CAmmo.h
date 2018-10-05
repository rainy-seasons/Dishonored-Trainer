#pragma once

// This is an array of the ammo values
// TODO:
// Do more reversing on this and rename to something more fitting
class CAmmo
{
public:
	__int32 Pistol; //0x0000 
	__int32 PistolAmmo_Max; //0x0004 
	char pad_0x0008[0x8]; //0x0008
	__int32 CrossbowStd; //0x0010 
	__int32 CrossbowStd_Max; //0x0014 
	__int32 SleepDarts; //0x0018 
	__int32 SlepDarts_Max; //0x001C 
	__int32 IncenBolts; //0x0020 
	__int32 IncenBolts_Max; //0x0024 
	__int32 SpringRazor; //0x0028 
	__int32 SpringRazor_Max; //0x002C 
	char pad_0x0030[0x3D4]; //0x0030

}; //Size=0x0404