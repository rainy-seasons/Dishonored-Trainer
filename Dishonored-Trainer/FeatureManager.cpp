#include "FeatureManager.h"
#include "WeaponEnum.h"

FeatureManager::FeatureManager()
{
	m_dbg = TRUE;
	m_BaseAddr = (DWORD)GetModuleHandle("Dishonored.exe");
	Player = *(CPlayer**)0x1452DE8;
}

void FeatureManager::Run()
{
	FeatureManager::CheckInput();

	if (State.InfHealth)
	{
		Player->Mana = 100;
	}

	if (State.InfMana)
	{
		Player->Health = 90;
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
	printf("Current Health: %d\n", GetHealth());
	printf("Current Mana:   %d\n", GetMana());
}

bool FeatureManager::IsDebug()  { return m_dbg; }
int FeatureManager::GetHealth() { return Player->Health; }
int FeatureManager::GetMana()   { return Player->Mana; }