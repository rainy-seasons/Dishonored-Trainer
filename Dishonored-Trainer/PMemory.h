#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

class PMemory
{

public:
	bool Process();
	DWORD Module(LPSTR ModuleName);
	HANDLE GetHandle();
	void CleanHandle();

	template<class T>
	T ReadMemory(DWORD adr)
	{
		return *((T*)adr);
	}

	template<class T>
	void WriteMemory(DWORD adr, T val)
	{
		*((T*)adr) = val;
	}

private:
	DWORD m_PID;
	HANDLE m_pHandle;
	PROCESSENTRY32 m_pEntry;
};
