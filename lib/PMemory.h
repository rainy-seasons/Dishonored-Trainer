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

	template <class T>
	T Read(T dwAddress)
	{
		T memRead;
		ReadProcessMemory(m_pHandle, (LPVOID)dwAddress, &memRead, sizeof(T), NULL);
		return memRead;
	}

	template <class T>
	void Write(T dwAddress, T value)
	{
		WriteProcessMemory(m_pHandle, (LPVOID)dwAddress, &value, sizeof(value), NULL);
	}

	template<class T>
	DWORD protectMemory(LPVOID addr, DWORD prot)
	{
		DWORD oldProt;
		VirtualProtectEx(m_pHandle, addr, sizeof(T), prot, &oldProt);
		return oldProt;
	}

	template<int SIZE>
	void writeNop(DWORD addr)
	{
		auto oldProt = protectMemory<BYTE[SIZE]>(addr, PAGE_EXECUTE_READWRITE);
		for (int i = 0; i < SIZE; i++)
		{
			Write<BYTE>(addr + i, 0x90);
		}
	}

private:
	DWORD m_PID;
	HANDLE m_pHandle;
	PROCESSENTRY32 m_pEntry;
};
