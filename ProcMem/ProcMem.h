#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

namespace ProcMem
{
	class PMemory
	{
	public:
		bool Process(LPSTR procName);
		DWORD Module(LPSTR ModuleName);
		HANDLE GetHandle();
		void CleanHandle();

		template<class T>
		T ReadPtr(LPVOID addr)
		{
			return *((T*)addr);
		}

		template<class T>
		void WritePtr(LPVOID addr, T val)
		{
			*((T*)addr) = val;
		}

		template<class T>
		T ReadMem(LPVOID addr)
		{
			T buf;
			ReadProcessMemory(m_pHandle, addr, &buf, sizeof(but), NULL);
			return buf;
		}

		template<class T>
		T WriteMem(LPVOID addr, T val)
		{
			WriteProcessMemory(m_pHandle, addr, &val, sizeof(val), NULL);
		}

		template<class T>
		DWORD ProtectMemory(LPVOID addr, DWORD prot)
		{
			DWORD oldProt;
			VirtualProtectEx(m_pHandle, addr, sizeof(T), prot, &oldProt);
			return oldProt;
		}

		template<int SIZE>
		void WriteNop(LPVOID addr)
		{
			auto oldProt = ProtectMemory<BYTE[SIZE]>(addr, PAGE_EXECUTE_READWRITE);
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
}
