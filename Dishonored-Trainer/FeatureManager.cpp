#include "FeatureManager.h"

FeatureManager::FeatureManager()
	: m_dbg(TRUE), 
	m_BaseAddr((DWORD)GetModuleHandle(L"Dishonored.exe")),
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

	if (State.InfAmmo)
	{
		// TODO: 
		// Find pointer to active weapon and update this accordingly.

		if( ( Player->Inventory == nullptr ) || ( Player->Inventory->Ammo == nullptr ) )
		{
			printf( "Player point is invalid!" );
			return;
		}

		Player->Inventory->Ammo->Pistol = Player->Inventory->Ammo->CrossbowStd_Max;
		Player->Inventory->Ammo->CrossbowStd = Player->Inventory->Ammo->CrossbowStd_Max;
		Player->Inventory->Ammo->SleepDarts = Player->Inventory->Ammo->CrossbowStd_Max;
		Player->Inventory->Ammo->IncenBolts = Player->Inventory->Ammo->CrossbowStd_Max;
		Player->Inventory->Ammo->SpringRazor = Player->Inventory->Ammo->CrossbowStd_Max;
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

	if (GetAsyncKeyState(VK_UP))
	{
		State.InfAmmo = !State.InfAmmo;
		printf("Infinite Ammo = %d\n", State.InfAmmo);
		Sleep(150);
	}
}


void FeatureManager::DebugOutput()
{
	printf("Current Health: %d\n", Player->Health);
	printf("Current Mana:   %d\n", Player->Mana);
}

bool FeatureManager::IsDebug()  { return m_dbg; }
