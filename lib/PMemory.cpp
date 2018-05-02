#include "PMemory.h"
#include <stdio.h>

PMemory::PMemory()
{
}

PMemory::~PMemory()
{
}

bool PMemory::Process()
{
	m_pEntry.dwSize = sizeof(m_pEntry);

	HWND Found = FindWindow(NULL, "Dishonored");
	if (Found)
	{
		GetWindowThreadProcessId(Found, &m_PID);
		m_pHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, m_PID);
		return true;
	}
	
	return FALSE;
}

DWORD PMemory::Module(LPSTR ModuleName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_PID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do
	{
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	} while (Module32Next(hModule, &mEntry));

	CloseHandle(hModule);

	std::cout << "\nCould not attach to process..\n\n";
	return 0;
}

HANDLE PMemory::GetHandle()
{
	return m_pHandle;
}
