#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	if (!Mem.Process()) { std::cout << " \nMem.Process() Fail\n"; }
	m_BaseAddr   = Mem.Module("Dishonored.exe");
	m_ManaBase   = FeatureManager::InitOffsets(v_oMana);
	m_HealthBase = FeatureManager::InitOffsets(v_oHealth);
}

FeatureManager::~FeatureManager()
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

DWORD FeatureManager::GetManaBase()
{
	return m_ManaBase;
}

DWORD FeatureManager::GetHealthBase()
{
	return m_HealthBase;
}

std::vector<DWORD> FeatureManager::GetManaOffsets()
{
	return v_oMana;
}

std::vector<DWORD> FeatureManager::GetHealthOffsets()
{
	return v_oHealth;
}
