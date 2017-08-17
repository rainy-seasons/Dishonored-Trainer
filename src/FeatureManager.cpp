#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	if (!Mem.Process()) { std::cout << " \nMem.Process() Fail\n"; }
	m_BaseAddr   = Mem.Module("Dishonored.exe");
	m_MaxAmmo = 99;
	m_InfiniteAmmoState = false;

	m_CurrentLeftHand.vec_offsets  = { 0x0104CF44, 0x1C, 0xC, 0x5C, 0xD0, 0x238 };
	m_CurrentLeftHand.dw_Base      = FeatureManager::InitOffsets(m_CurrentLeftHand.vec_offsets);

	m_InfiniteMana.vec_offsets     = { 0x01065184, 0xEC, 0x0, 0x5A8 };
	m_InfiniteMana.dw_Base         = FeatureManager::InitOffsets(m_InfiniteMana.vec_offsets);
	m_InfiniteMana.l_MaxValue      = 100;
	m_InfiniteMana.b_ActiveState   = false;

	m_InfiniteHealth.vec_offsets   = { 0x0103CC84, 0x8, 0x24, 0x15C, 0x344 };
	m_InfiniteHealth.dw_Base       = FeatureManager::InitOffsets(m_InfiniteHealth.vec_offsets);
	m_InfiniteHealth.l_MaxValue    = 90;
	m_InfiniteHealth.b_ActiveState = false;

	m_InfiniteGold.vec_offsets     = { 0x01065184, 0xEC, 0x0, 0xE4, 0xC8, 0x88 };
	m_InfiniteGold.dw_Base         = FeatureManager::InitOffsets(m_InfiniteGold.vec_offsets);
	m_InfiniteGold.l_MaxValue      = 999;
	m_InfiniteGold.b_ActiveState   = false;
}

FeatureManager::~FeatureManager()
{
}

void FeatureManager::Run()
{
	FeatureManager::CheckInput();

	if (m_InfiniteMana.b_ActiveState)
		InfResource(m_InfiniteMana.dw_Base, m_InfiniteMana.vec_offsets, m_InfiniteMana.l_MaxValue);

	if (m_InfiniteHealth.b_ActiveState)
		InfResource(m_InfiniteHealth.dw_Base, m_InfiniteHealth.vec_offsets, m_InfiniteHealth.l_MaxValue);
	
	if (m_InfiniteGold.b_ActiveState)
		InfResource(m_InfiniteGold.dw_Base, m_InfiniteGold.vec_offsets, m_InfiniteGold.l_MaxValue);

	if (m_InfiniteAmmoState)
		InfAmmo();
}

void FeatureManager::CheckInput()
{
	if (GetAsyncKeyState(VK_RIGHT))	
	{
		m_InfiniteHealth.b_ActiveState = !m_InfiniteHealth.b_ActiveState;
		std::cout << "Infinite Health = " << m_InfiniteHealth.b_ActiveState << std::endl;
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_LEFT))	
	{
		m_InfiniteMana.b_ActiveState = !m_InfiniteMana.b_ActiveState;
		std::cout << "Infinite Mana = " << m_InfiniteMana.b_ActiveState << std::endl;
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_InfiniteGold.b_ActiveState = !m_InfiniteGold.b_ActiveState;
		std::cout << "Infinite Gold = " << m_InfiniteGold.b_ActiveState << std::endl;
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_UP))
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
	// do this because we want the address instead of the value when we go to write to it
	for (std::vector<DWORD>::iterator itr = v_offsets.begin(); itr < v_offsets.end() - 1; ++itr)
	{
		BaseAddress = Mem.Read<DWORD>(BaseAddress + *itr);
	}
	return BaseAddress;
}

void FeatureManager::InfResource(DWORD ResourceBase, std::vector<DWORD> v_offsets, int MaxValue)
{
	DWORD dw_Resource = Mem.Read<DWORD>(ResourceBase + v_offsets.back());
	if (dw_Resource < MaxValue)
	{
		Mem.Write<DWORD>(ResourceBase + v_offsets.back(), MaxValue);
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
		case 0:    // pistol
			FeatureManager::SetAmmo(e_Pistol);
			break;
		case 1:    // regular bolts
			FeatureManager::SetAmmo(e_RegBolts);
			break;
		case 2:    // springrazor
			FeatureManager::SetAmmo(e_SpringRazor);
			break;
		case 3:    // sleep bolts
			FeatureManager::SetAmmo(e_SleepBolts);
			break;
		case 4:    // incendiary bolts
			FeatureManager::SetAmmo(e_IncenBolts);
			break;
		case 6:    // blink
			break;
	}
}
