#include <stdio.h>
#include <iostream>
#include <string>
#include "FeatureManager.h"

void Display();

PMemory Mem;

int main()
{
	do
	{
		system("cls");
		std::cout << ("Waiting for dishonored..") << std::endl;
		Sleep(300);
	} while (!Mem.Process());
	std::cout << "Found Dishonored!\n\n" << std::endl;
	Display();

	FeatureManager Feature;

	for (;;)
	{
		Feature.Run();
	}

	return 0;
}

void Display()
{
	Sleep(200);
	system("cls");
	std::cout << "||	  	  Honored		  ||\n";
	std::cout << "--------------------------------------------\n";
	std::cout << "|| [ R ARROW ] --> Toggle Infinite Health ||\n";
	std::cout << "|| [ L ARROW ] --> Toggle Infinite Mana	  ||\n";
	std::cout << "|| [ U ARROW ] --> Toggle Infinite Ammo   ||\n";
	std::cout << "--------------------------------------------\n\n";
}
