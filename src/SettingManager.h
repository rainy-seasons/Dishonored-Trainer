#include <Windows.h>
#include <iostream>
#include <string>
#include "../lib/parseINI.h"

class SettingManager
{
public:
	void WriteKeyConfig(char* category, char* bind, char* value);
	void WriteDefaults();
	void InitSettings();
	bool FileExists(const std::string &filename);
	DWORD GetHealthKey();
	DWORD GetManaKey();
	DWORD GetAmmoKey();
	DWORD GetGoldKey();

private:
	ParseINI m_Cfg;
	DWORD KEY_INF_HEALTH;
	DWORD KEY_INF_MANA;
	DWORD KEY_INF_AMMO;
	DWORD KEY_INF_GOLD;
};
