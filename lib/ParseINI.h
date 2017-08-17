#pragma once
#include <Windows.h>
#include <string>
#include <stdio.h>

class ParseINI
{
public:
	std::string Config = GetDir();

	std::string ReadString(const char* iniSection, const char* iniKey)
	{
		char buffer[128];
		if (GetPrivateProfileStringA(iniSection, iniKey, "", buffer, 128, Config.c_str()))
		{
			char bStr[128];
			sprintf(bStr, buffer);
			return std::string(bStr);
		}
		return nullptr;
	}

	int ReadInt(const char* iniSection, const char* iniKey)
	{
		char buffer[128];
		if (GetPrivateProfileStringA(iniSection, iniKey, "", buffer, 128, Config.c_str()))
		{
			char bStr[128];
			sprintf(bStr, buffer);
			return std::stoi(bStr);
		}	
		return -1;
	}

	float ReadFloat(const char* iniSection, const char* iniKey)
	{
		char buffer[128];
		if (GetPrivateProfileStringA(iniSection, iniKey, "", buffer, 128, Config.c_str()))
		{
			char bStr[128];
			sprintf(bStr, buffer);
			return std::stof(bStr);
		}
		return -1.f;
	}

	void Write(const char* iniSection, const char* iniKey, const char* Value)
	{
		WritePrivateProfileStringA(iniSection, iniKey, Value, Config.c_str());
	}

	std::string GetDir()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0, pos) + "\\config.ini";
	}

	bool SectionExists(const char* iniSection)
	{
		char res[100];
		long val = GetPrivateProfileStringA(iniSection, NULL, "", res, 90, Config.c_str());
		return (val > 0);
	}
};
