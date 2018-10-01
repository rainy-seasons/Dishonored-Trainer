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

	//template<class T>
	//DWORD protectMemory(LPVOID addr, DWORD prot)
	//{
	//	DWORD oldProt;
	//	VirtualProtectEx(m_pHandle, addr, sizeof(T), prot, &oldProt);
	//	return oldProt;
	//}

	//template<int SIZE>
	//void writeNop(DWORD addr)
	//{
	//	auto oldProt = protectMemory<BYTE[SIZE]>(addr, PAGE_EXECUTE_READWRITE);
	//	for (int i = 0; i < SIZE; i++)
	//	{
	//		Write<BYTE>(addr + i, 0x90);
	//	}
	//}

private:
	DWORD m_PID;
	HANDLE m_pHandle;
	PROCESSENTRY32 m_pEntry;
};
