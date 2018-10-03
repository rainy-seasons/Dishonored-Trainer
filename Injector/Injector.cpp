// Injector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include "ProcMem.h"

void InjectDLL();
ProcMem::PMemory Mem;

int main()
{
	do{
		system("cls");
		printf("Waiting for dishonored");
		Sleep(300);
	} while (!Mem.Process("Dishonored"));
	std::cout << "\nFound Dishonored!" << std::endl;
	Sleep(1000);

	InjectDLL();
	return 0;
}

void InjectDLL()
{
	TCHAR full_path[MAX_PATH];
	std::string dllName = "Dishonored-Trainer.dll";
	GetFullPathName((dllName.c_str()), MAX_PATH, full_path, NULL);
	HANDLE process = Mem.GetHandle();
	LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	LPVOID remoteString = VirtualAllocEx(process, NULL, strlen(full_path), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WriteProcessMemory(process, remoteString, full_path, strlen(full_path), NULL);
	HANDLE thread = CreateRemoteThread(process, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, remoteString, 0, NULL);
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	CloseHandle(process);
	std::cout << "---> INJECTED <---" << std::endl;
}