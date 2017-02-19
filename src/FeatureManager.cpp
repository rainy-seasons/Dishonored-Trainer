#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	if (!Mem.Process()) { std::cout << " \nMem.Process() Fail\n"; }
	m_BaseAddr   = Mem.Module("Dishonored.exe");
//	m_ManaBase   = FeatureManager::InitOffsets(v_oMana);
//	m_HealthBase = FeatureManager::InitOffsets(v_oHealth);

	//Feature InfiniteMana;
	InfiniteMana.vec_offsets   = { 0x01065184, 0xEC, 0x0, 0x5A8 };
	InfiniteMana.dw_Base       = FeatureManager::InitOffsets(InfiniteMana.vec_offsets);
	InfiniteMana.l_MaxValue    = 100;
	InfiniteMana.b_ActiveState = true;

	//Feature InfiniteHealth;
	InfiniteHealth.vec_offsets   = { 0x0103CC84, 0x8, 0x24, 0x15C, 0x344 };
	InfiniteHealth.dw_Base       = FeatureManager::InitOffsets(InfiniteHealth.vec_offsets);
	InfiniteHealth.l_MaxValue    = 90;
	InfiniteHealth.b_ActiveState = true;
}

FeatureManager::~FeatureManager()
{
}

void FeatureManager::Run()
{
	if (InfiniteMana.b_ActiveState)
		InfResource(InfiniteMana.dw_Base, InfiniteMana.vec_offsets, InfiniteMana.l_MaxValue);

	if (InfiniteHealth.b_ActiveState)
		InfResource(InfiniteHealth.dw_Base, InfiniteHealth.vec_offsets, InfiniteHealth.l_MaxValue);
}

void FeatureManager::ChangeState(std::string szFeature)
{
			
}

DWORD FeatureManager::InitOffsets(std::vector<DWORD> v_offsets)
{
	DWORD BaseAddress = m_BaseAddr;

	// stop at the 2nd to last element to add it on later, 
	// do this because we don't want the 'read' value when we go to write to it
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
