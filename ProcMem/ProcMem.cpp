#include "ProcMem.h"

namespace ProcMem
{
	bool PMemory::Process(LPSTR procName)
	{
		m_pEntry.dwSize = sizeof(m_pEntry);

		HWND Found = FindWindow(NULL, procName);
		if (Found)
		{
			GetWindowThreadProcessId(Found, &m_PID);
			m_pHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, m_PID);
			return true;
		}

		std::cout << "Could not attach to target process: " << procName << std::endl;
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

		std::cout << "Could not locate module: " << ModuleName << std::endl;
	}

	HANDLE PMemory::GetHandle() { return m_pHandle; }
	void PMemory::CleanHandle() { CloseHandle(m_pHandle); }

}
