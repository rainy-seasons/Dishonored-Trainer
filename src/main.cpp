#include "PMemory.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

PMemory Mem;

void DebugDisplay();
void MainLoop();
void infMana();
void infHealth();
DWORD initOffsets(DWORD BaseAddr, std::vector<DWORD> v_offsets);

std::vector<DWORD> v_oMana { 0x01065184, 0xEC, 0x0 };
std::vector<DWORD> v_oHealth { 0x0103CC84, 0x8, 0x24, 0x15C };

const DWORD oMana   = 0x5A8;
const DWORD oHealth = 0x344;

DWORD BaseAddr      = 0;
DWORD ManaBase      = 0;
DWORD HealthBase    = 0;

int main()
{
	do
	{
		system("cls");
		cout << ("Waiting for dishonored..") << endl;
		Sleep(300);
	} while (!Mem.Process());

	cout << "Found Dishonored!" << endl;

	DWORD BaseAddr = Mem.Module("Dishonored.exe");
	ManaBase = BaseAddr;
	HealthBase = BaseAddr;

	ManaBase = initOffsets(ManaBase, v_oMana);
	HealthBase = initOffsets(HealthBase, v_oHealth);

	/*
	ManaBase = BaseAddr;
	ManaBase = Mem.Read<DWORD>(ManaBase + 0x01065184);
	ManaBase = Mem.Read<DWORD>(ManaBase + 0xEC);
	ManaBase = Mem.Read<DWORD>(ManaBase + 0x0);

	HealthBase = BaseAddr;
	HealthBase = Mem.Read<DWORD>(HealthBase + 0x0103CC84);
	HealthBase = Mem.Read<DWORD>(HealthBase + 0x8);
	HealthBase = Mem.Read<DWORD>(HealthBase + 0x24);
	HealthBase = Mem.Read<DWORD>(HealthBase + 0x15C);
	*/

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

// Returns the addres with offsets applied
DWORD initOffsets(DWORD BaseAddr, std::vector<DWORD> v_offsets)
{
	for (std::vector<DWORD>::iterator itr = v_offsets.begin(); itr != v_offsets.end(); ++itr)
	{
		BaseAddr = Mem.Read<DWORD>(BaseAddr + *itr);
	}
	return BaseAddr;
}

void DebugDisplay()
{
	cout << "Base Address --> ";
	cout << hex << ManaBase << std::endl;

	printf("Mana Offset  --> 0x5A8\n");
	cout << "Current mana --> ";
	cout << dec << Mem.Read<DWORD>(ManaBase + oMana) << endl;

	cout << "Current health --> ";
	cout << Mem.Read<DWORD>(HealthBase + oHealth) << "\n" << endl;
}

void infMana()
{
	DWORD l_Mana = Mem.Read<DWORD>(ManaBase + oMana);
	if (l_Mana < 100)
	{
		cout << "\nMagic Replenished! ";
		cout << l_Mana;
		cout << " --> 100";
		Mem.Write<DWORD>(ManaBase + oMana, 100);
	}
}

void infHealth()
{
	DWORD l_Health = Mem.Read<DWORD>(HealthBase + oHealth);
	if (l_Health < 90)
	{
		cout << "\nHealth Replenished! ";
		cout << l_Health;
		cout << " --> 100";
		Mem.Write<DWORD>(HealthBase + oHealth, 90);
	}
}
