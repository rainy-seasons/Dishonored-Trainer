#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "PMemory.h"
#include "CPlayer.h"

struct FeatureStates
{
	bool InfHealth = FALSE;
	bool InfMana   = FALSE;
};

class FeatureManager
{
public:
	FeatureManager();
	bool IsDebug();
	void CheckInput();
	void Run();

private:
	PMemory Mem;
	FeatureStates State;
	CPlayer* Player;

	void DebugOutput();
	int GetHealth();
	int GetMana();

	DWORD m_BaseAddr;
	bool m_dbg;
};

