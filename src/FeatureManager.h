#include <vector>
#include "PMemory.h"

class FeatureManager
{
public:
	FeatureManager();
	~FeatureManager();
	void InfResource(DWORD ResourceBase, std::vector<DWORD> v_offsets, int MaxValue);
	DWORD InitOffsets(std::vector<DWORD> v_offsets);
	DWORD GetManaBase();
	DWORD GetHealthBase();
	std::vector<DWORD> GetManaOffsets();
	std::vector<DWORD> GetHealthOffsets();

private:
	PMemory Mem;
	std::vector<DWORD> v_oMana   { 0x01065184, 0xEC, 0x0, 0x5A8 };
	std::vector<DWORD> v_oHealth { 0x0103CC84, 0x8, 0x24, 0x15C, 0x344 };
	DWORD m_BaseAddr;
	DWORD m_ManaBase;
	DWORD m_HealthBase;
};
