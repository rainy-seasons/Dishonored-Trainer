#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "SettingManager.h"
#include "../lib/ParseINI.h"

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

	KEY_INF_HEALTH = std::stoi(m_Cfg.ReadString("KeyBinds", "InfiniteHealth"), 0, 16);
	KEY_INF_MANA = std::stoi(m_Cfg.ReadString("KeyBinds", "InfiniteMana"), 0, 16);
	KEY_INF_AMMO = std::stoi(m_Cfg.ReadString("KeyBinds", "InfiniteAmmo"), 0, 16);
	KEY_INF_GOLD = std::stoi(m_Cfg.ReadString("KeyBinds", "InfiniteAmmo"), 0, 16);
}

DWORD SettingManager::GetHealthKey() { return KEY_INF_HEALTH;}
DWORD SettingManager::GetManaKey()   { return KEY_INF_MANA; }
DWORD SettingManager::GetAmmoKey()   { return KEY_INF_AMMO; }
DWORD SettingManager::GetGoldKey()   { return KEY_INF_GOLD; }
