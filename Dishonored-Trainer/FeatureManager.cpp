#include "FeatureManager.h"
#include "WeaponEnum.h"

FeatureManager::FeatureManager()
	: m_dbg(TRUE), 
	m_BaseAddr((DWORD)GetModuleHandle("Dishonored.exe")), 
	Player(*(CPlayer**)0x1452DE8)
{
}

void FeatureManager::Run()
{
	FeatureManager::CheckInput();

	if (State.InfHealth)
	{
		Player->Health = Player->MaxHealth;
	}

	if (State.InfMana)
	{
		Player->Mana = Player->MaxMana;
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
		State.InfHealth = !State.InfHealth;
		printf("Infinite Health = %d\n", State.InfHealth);
		Sleep(150);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		State.InfMana = !State.InfMana;
		printf("Infinite Mana = %d\n", State.InfMana);
		Sleep(150);
	}
}


void FeatureManager::DebugOutput()
{
	printf("Current Health: %d\n", Player->Health);
	printf("Current Mana:   %d\n", Player->Mana);
}

bool FeatureManager::IsDebug()  { return m_dbg; }
