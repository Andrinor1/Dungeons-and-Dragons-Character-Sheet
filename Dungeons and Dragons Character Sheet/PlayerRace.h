#pragma once
#include <string>

class PlayerRace
{
private:
	int stat_bonuses[6] = { 0,0,0,0,0,0 };
	std::string name;
	int ID;
public:
	PlayerRace();
	PlayerRace(int arr[6], std::string name, int ID);

	std::string get_name();
	int* get_bonuses();
	int get_ID();


	void set_halfelf_bonuses();

	void print();
};

