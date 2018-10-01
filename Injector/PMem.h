#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

class PMemory
{

public:
	PMemory();
	~PMemory();

	bool Process();
	DWORD Module(LPSTR ModuleName);
	HANDLE GetHandle();

private:
	DWORD m_PID;
	HANDLE m_pHandle;
	PROCESSENTRY32 m_pEntry;
};
