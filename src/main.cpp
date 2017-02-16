#include "PMemory.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

PMemory Mem;

void DebugDisplay();
void MainLoop();
void infMana();
void infHealth();
DWORD initOffsets(std::vector<DWORD> v_offsets);

// offset lists to navigate to the needed pointer from the
// module base address
std::vector<DWORD> v_oMana { 0x01065184, 0xEC, 0x0, 0x5A8 };
std::vector<DWORD> v_oHealth { 0x0103CC84, 0x8, 0x24, 0x15C, 0x344 };

DWORD BaseAddr      = 0;
DWORD ManaBase      = 0;
DWORD HealthBase    = 0;

int main()
{
	do
	{
		system("cls");
		std::cout << ("Waiting for dishonored..") << std::endl;
		Sleep(300);
	} while (!Mem.Process());

	std::cout << "Found Dishonored!" << std::endl;

	BaseAddr = Mem.Module("Dishonored.exe");
	ManaBase = initOffsets(v_oMana);
	HealthBase = initOffsets(v_oHealth);

	DebugDisplay();

	for (;;)
	{
		MainLoop();
	}

	return 0;
}

void MainLoop()
{
	infMana();
	infHealth();
}

// Returns the address with offsets applied
DWORD initOffsets(std::vector<DWORD> v_offsets)
{
	DWORD BaseAddress = BaseAddr;

	// stop at the 2nd to last element to add it on later, 
	// do this because we don't want the 'read' value when we go to write to it
	for (std::vector<DWORD>::iterator itr = v_offsets.begin(); itr < v_offsets.end() - 1; ++itr)
	{
		BaseAddress = Mem.Read<DWORD>(BaseAddress + *itr);
	}
	return BaseAddress;
}

void DebugDisplay()
{
	std::cout << "Base Address --> ";
	std::cout << std::hex << ManaBase << std::endl;

	printf("Mana Offset  --> 0x5A8\n");
	std::cout << "Current mana --> ";
	std::cout << std::dec << Mem.Read<DWORD>(ManaBase + v_oMana.back()) << std::endl;

	std::cout << "Current health --> ";
	std::cout << Mem.Read<DWORD>(HealthBase + v_oHealth.back()) << "\n" << std::endl;
}

void infMana()
{
	DWORD l_Mana = Mem.Read<DWORD>(ManaBase + v_oMana.back());
	if (l_Mana < 100)
	{
		std::cout << "\nMagic Replenished! ";
		std::cout << l_Mana;
		std::cout << " --> 100";
		Mem.Write<DWORD>(ManaBase + v_oMana.back(), 100);
	}
}

void infHealth()
{
	DWORD l_Health = Mem.Read<DWORD>(HealthBase + v_oHealth.back());
	if (l_Health < 90)
	{
		std::cout << "\nHealth Replenished! ";
		std::cout << l_Health;
		std::cout << " --> 100";
		Mem.Write<DWORD>(HealthBase + v_oHealth.back(), 100);
	}
}
