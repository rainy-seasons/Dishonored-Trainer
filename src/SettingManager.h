#include <Windows.h>
#include <iostream>
#include <string>
#include "../lib/parseINI.h"

struct KEY
{
	DWORD INF_MANA;
	DWORD INF_AMMO;
	DWORD INF_GOLD;
	DWORD INF_HEALTH;
};

class SettingManager
{
public:
	SettingManager();
	~SettingManager();
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
	KEY k;
	KEY* Key;
};
