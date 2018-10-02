#include "FeatureManager.h"
#include "WeaponEnum.h"

FeatureManager::FeatureManager()
{
	m_dbg = TRUE;
	m_BaseAddr = (DWORD)GetModuleHandle("Dishonored.exe");
	m_MaxAmmo = 99;

	m_InfiniteMana = FeatureManager::Setup(m_InfiniteMana, { 0xA60 }, 100, false);
	m_InfiniteHealth = FeatureManager::Setup(m_InfiniteHealth, { 0x344 }, 90, false);
}

FeatureManager::~FeatureManager()
{
}

Feature FeatureManager::Setup(Feature feature, std::vector<DWORD> v_offsets, int MaxValue, bool ActiveState)
{
	feature.vec_offsets = v_offsets;
	feature.dw_Base = FeatureManager::InitOffsets(feature.vec_offsets);
	feature.l_MaxValue = MaxValue;
	feature.b_ActiveState = ActiveState;
	return feature;
}

void FeatureManager::Run()
{
	FeatureManager::CheckInput();

	if (m_InfiniteMana.b_ActiveState)
	{
		Mem.WriteMemory<int>((*(uintptr_t*)m_Offset.PlayerBase) + m_InfiniteMana.vec_offsets.back(), 100);
	}

	if (m_InfiniteHealth.b_ActiveState)
	{
		Mem.WriteMemory<int>((*(uintptr_t*)m_Offset.PlayerBase) + m_InfiniteHealth.vec_offsets.back(), 100);
	}
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

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_InfiniteHealth.b_ActiveState = !m_InfiniteHealth.b_ActiveState;
		printf("Infinite Health = %d\n", m_InfiniteHealth.b_ActiveState);
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_InfiniteMana.b_ActiveState = !m_InfiniteMana.b_ActiveState;
		printf("Infinite Mana = %d\n", m_InfiniteMana.b_ActiveState);
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
		BaseAddress = Mem.ReadMemory<DWORD>((BaseAddress + *itr));
	}

	return BaseAddress;
}

void FeatureManager::InfResource(Feature feature)
{
	DWORD dw_Resource = Mem.ReadMemory<DWORD>(feature.dw_Base + feature.vec_offsets.back());
	if (dw_Resource < feature.l_MaxValue)
	{
		Mem.WriteMemory<DWORD>(feature.dw_Base + feature.vec_offsets.back(), feature.l_MaxValue);
	}
}

void FeatureManager::DebugOutput()
{
	printf("Current Health: %d\n", GetHealth());
	printf("Current Mana:   %d\n", GetMana());
}

bool FeatureManager::IsDebug()  { return m_dbg; }
int FeatureManager::GetHealth() { return Mem.ReadMemory<int>((*(uintptr_t*)m_Offset.PlayerBase) + m_InfiniteHealth.vec_offsets.back()); }
int FeatureManager::GetMana() { return Mem.ReadMemory<int>((*(uintptr_t*)m_Offset.PlayerBase) + m_InfiniteMana.vec_offsets.back()); }