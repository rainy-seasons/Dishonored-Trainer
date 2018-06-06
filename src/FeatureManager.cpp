#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	m_dbg = TRUE; // debug options

	if (!Mem.Process()) { std::cout << " \nMem.Process() Fail\n"; }
	m_BaseAddr   = Mem.Module("Dishonored.exe");
	m_MaxAmmo = 99;
	m_InfiniteAmmoState = false;

	if (!Settings.FileExists("config.ini"))	
		Settings.WriteDefaults();
	Settings.InitSettings();

	m_CurrentLeftHand.vec_offsets  = { 0x0104CF44, 0x1C, 0xC, 0x5C, 0xD0, 0x238 };
	m_CurrentLeftHand.dw_Base      = FeatureManager::InitOffsets(m_CurrentLeftHand.vec_offsets);

	// These hex values are paths to the desired address, see FeatureManager::InitOffsets().
	m_InfiniteMana   = FeatureManager::Setup(m_InfiniteMana,   { 0x01065184, 0xEC, 0x0, 0x5A8 }, 100, false);
	m_InfiniteGold   = FeatureManager::Setup(m_InfiniteGold,   { 0x01065184, 0xEC, 0x0, 0xE4, 0xC8, 0x88 }, 999, false);
	m_InfiniteHealth = FeatureManager::Setup(m_InfiniteHealth, { 0x0103CC84, 0x8, 0x24, 0x15C, 0x344 }, 90, false);
}

FeatureManager::~FeatureManager()
{
}

Feature FeatureManager::Setup(Feature feature, std::vector<DWORD> v_offsets, int MaxValue, bool ActiveState)
{
	feature.vec_offsets   = v_offsets;
	feature.dw_Base       = FeatureManager::InitOffsets(feature.vec_offsets);
	feature.l_MaxValue    = MaxValue;
	feature.b_ActiveState = ActiveState;
	return feature;
}

void FeatureManager::Run()
{
 	FeatureManager::CheckInput();

	if (m_InfiniteMana.b_ActiveState)
		InfResource(m_InfiniteMana);

	if (m_InfiniteHealth.b_ActiveState)
		InfResource(m_InfiniteHealth);

	if (m_InfiniteGold.b_ActiveState)
		InfResource(m_InfiniteGold);

	if (m_InfiniteAmmoState)
		InfAmmo();
}

void FeatureManager::CheckInput()
{
	if (m_dbg)
	{
		if (GetAsyncKeyState(VK_INSERT))
		{
			DebugOutput();
			Sleep(150);
		}
	}

	if (GetAsyncKeyState(Settings.GetHealthKey()))
	{
		m_InfiniteHealth.b_ActiveState = !m_InfiniteHealth.b_ActiveState;
		std::cout << "Infinite Health = " << m_InfiniteHealth.b_ActiveState << std::endl;
		Sleep(150);
	}

	if (GetAsyncKeyState(Settings.GetManaKey()))	
	{
		m_InfiniteMana.b_ActiveState = !m_InfiniteMana.b_ActiveState;
		std::cout << "Infinite Mana = " << m_InfiniteMana.b_ActiveState << std::endl;
		Sleep(150);
	}

	if (GetAsyncKeyState(Settings.GetGoldKey()))
	{
		m_InfiniteGold.b_ActiveState = !m_InfiniteGold.b_ActiveState;
		std::cout << "Infinite Gold = " << m_InfiniteGold.b_ActiveState << std::endl;
		Sleep(150);
	}

	if (GetAsyncKeyState(Settings.GetAmmoKey()))
	{
		m_InfiniteAmmoState = !m_InfiniteAmmoState;
		std::cout << "Infinite Ammo = " << m_InfiniteAmmoState << std::endl;
		Sleep(150);
	}
}

DWORD FeatureManager::InitOffsets(std::vector<DWORD> v_offsets)
{
	DWORD BaseAddress = m_BaseAddr;

	// stop at the 2nd to last element to add it on later, 
	// do this because we want the address instead of the value when we go to write to it.
	for (std::vector<DWORD>::iterator itr = v_offsets.begin(); itr < v_offsets.end() - 1; ++itr)
	{
		BaseAddress = Mem.Read<DWORD>(BaseAddress + *itr);
	}

	return BaseAddress;
}

void FeatureManager::InfResource(Feature feature)
{
	DWORD dw_Resource = Mem.Read<DWORD>(feature.dw_Base + feature.vec_offsets.back());
	if (dw_Resource < feature.l_MaxValue)
	{
		Mem.Write<DWORD>(feature.dw_Base + feature.vec_offsets.back(), feature.l_MaxValue);
	}
}

void FeatureManager::SetAmmo(WeaponOffset offset)
{
	DWORD dw_AmmoBase = InitOffsets(m_vecWeaponAmmoBase);
	DWORD dw_Ammo = Mem.Read<DWORD>(dw_AmmoBase + offset);

	if (dw_Ammo < m_MaxAmmo)
	{
		Mem.Write<DWORD>(dw_AmmoBase + offset, m_MaxAmmo);
	}
}

void FeatureManager::InfAmmo()
{
	switch (Mem.Read<DWORD>(m_CurrentLeftHand.dw_Base + m_CurrentLeftHand.vec_offsets.back())) // Get the current held weapon
	{
		case 0:
			FeatureManager::SetAmmo(e_Pistol);
			break;
		case 1:
			FeatureManager::SetAmmo(e_RegBolts);
			break;
		case 2:
			FeatureManager::SetAmmo(e_SpringRazor);
			break;
		case 3:
			FeatureManager::SetAmmo(e_SleepBolts);
			break;
		case 4:
			FeatureManager::SetAmmo(e_IncenBolts);
			break;
		case 6:    // blink
			break;
	}
}

void FeatureManager::DebugOutput()
{
	printf("Current Health: %d\n", GetHealth());
}

int FeatureManager::GetHealth()
{
	return Mem.Read<int>(m_InfiniteHealth.dw_Base + m_InfiniteHealth.vec_offsets.back());
}
