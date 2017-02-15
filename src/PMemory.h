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

	template <class mDat>
	mDat Read(mDat dwAddress)
	{
		mDat mRead;
		ReadProcessMemory(m_pHandle, (LPVOID)dwAddress, &mRead, sizeof(mDat), NULL);
		return mRead;
	}

	template <class mDat>
	void Write(mDat dwAddress, mDat value)
	{
		WriteProcessMemory(m_pHandle, (LPVOID)dwAddress, &value, sizeof(value), NULL);
	}

private:
	DWORD m_PID;
	HANDLE m_pHandle;
	PROCESSENTRY32 m_pEntry;
};
