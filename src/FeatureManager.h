#include <vector>
#include <string>
#include "SettingManager.h"
#include "../lib/PMemory.h"

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

enum WeaponOffset
{
	e_Pistol      = 0x0,
	e_RegBolts    = 0x10,
	e_SleepBolts  = 0x18,
	e_IncenBolts  = 0x20,
	e_SpringRazor = 0x28,
};

class FeatureManager
{
public:
	FeatureManager();
	~FeatureManager();
	Feature Setup(Feature feature, std::vector<DWORD> v_offsets, int MaxValue, bool ActiveState);
	void InfResource(DWORD ResourceBase, std::vector<DWORD> v_offsets, int MaxValue);
	void SetAmmo(WeaponOffset offset);
	void InfAmmo();
	DWORD InitOffsets(std::vector<DWORD> v_offsets);
	void CheckInput();
	void Run();

private:
	PMemory Mem;
	SettingManager Settings;
	Feature m_InfiniteMana;
	Feature m_InfiniteGold;
	Feature m_InfiniteHealth;
	FeatureReadOnly m_CurrentLeftHand;

	int m_MaxAmmo;
	DWORD m_BaseAddr;
	bool m_InfiniteAmmoState;

	std::vector<DWORD> m_vecWeaponAmmoBase = { 0x0103CC9C, 0x20, 0x24, 0x54, 0xBC, 0x0 };
};
