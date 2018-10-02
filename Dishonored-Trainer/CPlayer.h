#pragma once
class CPlayer
{
	char _pad[0x344];
public:
	int Health; // 0x344

private:
	char _pad2[0x718];
public:
	int Mana; // 0xA60
};