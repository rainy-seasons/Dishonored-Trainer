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
	std::cout << "Found Dishonored!" << std::endl;

	FeatureManager Feature;

	for (;;)
	{
		Feature.Run();

//		Feature.InfResource(Feature.GetManaBase(), Feature.GetManaOffsets(), 100);
//		Feature.InfResource(Feature.GetHealthBase(), Feature.GetHealthOffsets(), 90);
	}

	return 0;
}
