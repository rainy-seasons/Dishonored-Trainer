#pragma once
class CPlayer
{
	char _pad[0x344];
public:
	int Health;

private:
	char _pad2[0x718];
public:
	int Mana;
};