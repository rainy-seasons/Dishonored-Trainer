#include <stdio.h>
#include <iostream>
#include <string>
#include "FeatureManager.h"

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

	FeatureManager Feature;

	for (;;)
	{
		Feature.Run();
	}

	return 0;
}
