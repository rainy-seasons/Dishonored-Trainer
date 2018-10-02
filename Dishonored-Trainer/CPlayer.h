#pragma once
class CPlayer
{
private:
	char _pad[0x344];

public:
	int Health; // 0x344
	int Max_Health; // 0x348

private:
	char _pad2[0x714];

public:
	int Mana; // 0xA60
	int Max_Mana; // 0xA64
};