#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "SettingManager.h"

SettingManager::SettingManager()
{
	Key = &k;
	free(&k);
}

SettingManager::~SettingManager()
{
	delete Key;
}

bool SettingManager::FileExists(const std::string &filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
		return true;

	return false;
}

void SettingManager::WriteKeyConfig(char* category, char* bind, char* value)
{
	m_Cfg.Write(category, bind, value);
}

void SettingManager::WriteDefaults()
{
	std::cout << "Writing default config.ini..." << std::endl;

	WriteKeyConfig("Keybinds", "Infinite Health", "0x27"); // 0x27 = VK_RIGHT
	WriteKeyConfig("Keybinds", "Infinite Mana", "0x25");   // 0x25 = VK_LEFT
	WriteKeyConfig("Keybinds", "Infinite Ammo", "0x26");   // 0x26 = VK_UP
	WriteKeyConfig("Keybinds", "Infinite Gold", "0x28");   // 0x28 = VK_DOWN
}

void SettingManager::InitSettings()
{
	std::cout << "Initializing Settings..." << std::endl;

	Key->INF_HEALTH = std::stoi(m_Cfg.ReadString("Keybinds", "Infinite Health"), 0, 16);
	Key->INF_MANA   = std::stoi(m_Cfg.ReadString("Keybinds", "Infinite Mana"), 0, 16);
	Key->INF_AMMO   = std::stoi(m_Cfg.ReadString("Keybinds", "Infinite Ammo"), 0, 16);
	Key->INF_GOLD   = std::stoi(m_Cfg.ReadString("Keybinds", "Infinite Gold"), 0, 16);
}

DWORD SettingManager::GetHealthKey() { return Key->INF_HEALTH;}
DWORD SettingManager::GetManaKey()   { return Key->INF_MANA; }
DWORD SettingManager::GetAmmoKey()   { return Key->INF_AMMO; }
DWORD SettingManager::GetGoldKey()   { return Key->INF_GOLD; }
