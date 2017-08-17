#include <vector>
#include <string>
#include "PMemory.h"

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
	void InfResource(DWORD ResourceBase, std::vector<DWORD> v_offsets, int MaxValue);
	void SetAmmo(WeaponOffset offset);
	void InfAmmo();
	DWORD InitOffsets(std::vector<DWORD> v_offsets);
	void CheckInput();
	void Run();

private:
	PMemory Mem;
	DWORD m_BaseAddr;
	bool m_InfiniteAmmoState;
	int m_MaxAmmo;
	FeatureReadOnly m_CurrentLeftHand;
	Feature m_InfiniteMana;
	Feature m_InfiniteHealth;
	Feature m_InfiniteGold;

	std::vector<DWORD> m_vecWeaponAmmoBase = { 0x0103CC9C, 0x20, 0x24, 0x54, 0xBC, 0x0 };
};
