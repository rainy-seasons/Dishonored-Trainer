#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "PMemory.h"
#include "Offsets.h"

struct FeatureReadOnly
{
	std::vector<DWORD> vec_offsets {};
	DWORD dw_Base;
};

struct Feature : FeatureReadOnly
{
	bool b_ActiveState;
	int l_MaxValue;
};

class FeatureManager
{
public:
	FeatureManager();
	~FeatureManager();
	Feature Setup(Feature feature, std::vector<DWORD> v_offsets, int MaxValue, bool ActiveState);
	DWORD InitOffsets(std::vector<DWORD> v_offsets);
	bool IsDebug();
	void InfResource(Feature feature);
	void CheckInput();
	void Run();

private:
	PMemory Mem;
	Feature m_InfiniteMana;
	Feature m_InfiniteHealth;
	FeatureReadOnly m_CurrentLeftHand;
	Offsets m_Offset;

	void DebugOutput();
	int GetHealth();
	int GetMana();

	int m_MaxAmmo;
	DWORD m_BaseAddr;
	bool m_InfiniteAmmoState;
	bool m_dbg;

	std::vector<DWORD> m_vecWeaponAmmoBase = { 0x0103CC9C, 0x20, 0x24, 0x54, 0xBC, 0x0 };
};

