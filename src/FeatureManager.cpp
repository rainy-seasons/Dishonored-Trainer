#include "FeatureManager.h"

FeatureManager::FeatureManager()
{
	if (!Mem.Process()) { std::cout << " \nMem.Process() Fail\n"; }
	m_BaseAddr   = Mem.Module("Dishonored.exe");

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

	m_InfiniteBolts.vec_offsets    = { 0x0103CC9C, 0x20, 0x24, 0x54, 0xBC, 0x10 };
	m_InfiniteBolts.dw_Base        = FeatureManager::InitOffsets(m_InfiniteBolts.vec_offsets);
	m_InfiniteBolts.l_MaxValue     = 90;
	m_InfiniteBolts.b_ActiveState  = true;
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

	if (m_InfiniteBolts.b_ActiveState)
		InfResource(m_InfiniteBolts.dw_Base, m_InfiniteBolts.vec_offsets, m_InfiniteBolts.l_MaxValue);
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
