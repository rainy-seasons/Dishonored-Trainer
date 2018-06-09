#include <vector>
#include <string>
#include "SettingManager.h"
#include "../lib/PMemory.h"

// ReadOnly refers to the behavior of the members
// in relation to memory of the target process. 
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
	PISTOL      = 0x0,
	REGBOLTS    = 0x10,
	SLEEPBOLTS  = 0x18,
	INCENBOLTS  = 0x20,
	SPRINGRAZOR = 0x28,
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
	void SetAmmo(WeaponOffset offset);
	void InfAmmo();
	void CheckInput();
	void Run();

private:
	PMemory Mem;
	SettingManager Settings;
	Feature m_InfiniteMana;
	Feature m_InfiniteGold;
	Feature m_InfiniteHealth;
	FeatureReadOnly m_CurrentLeftHand;

	void DebugOutput();
	int GetHealth();
	int GetMana();

	int m_MaxAmmo;
	DWORD m_BaseAddr;
	bool m_InfiniteAmmoState;
	bool m_dbg;

	std::vector<DWORD> m_vecWeaponAmmoBase = { 0x0103CC9C, 0x20, 0x24, 0x54, 0xBC, 0x0 };
};
