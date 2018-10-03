#pragma once
#include <vector>
#include <string>
#include <windows.h>
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
	FeatureStates State;
	CPlayer* Player;

	void DebugOutput();

	DWORD m_BaseAddr;
	bool m_dbg;
};

