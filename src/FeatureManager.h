#include <vector>
#include <string>
#include "PMemory.h"

struct Feature 
{
	bool b_ActiveState;
	std::vector<DWORD> vec_offsets {};
	DWORD dw_Base;
	int l_MaxValue;
};

struct ReadOnlyValue
{
	std::vector<DWORD> vec_offsets {};
	DWORD dw_Base;
};

class FeatureManager
{
public:
	FeatureManager();
	~FeatureManager();
	void InfResource(DWORD ResourceBase, std::vector<DWORD> v_offsets, int MaxValue);
	DWORD InitOffsets(std::vector<DWORD> v_offsets);
	void CheckInput();
	void Run();

private:
	PMemory Mem;
	DWORD m_BaseAddr;
	ReadOnlyValue m_CurrentLeftHand;
	Feature m_InfiniteMana;
	Feature m_InfiniteHealth;
	Feature m_InfiniteBolts;
};
