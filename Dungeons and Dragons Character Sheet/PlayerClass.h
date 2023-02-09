#pragma once
#include <string>
#include <iostream>
#include <vector>

class PlayerClass
{
private:
	std::string name;
	int hitpoint_die_size;
	int level = 1;
	std::vector <std::string> features;
	int ID;
public:
	PlayerClass();
	PlayerClass(std::string name, int hitdie, std::vector <std::string> features,int ID);
	std::string get_name();
	int get_hitdie();
	int get_level();
	std::vector <std::string> get_features();
	void print_features();
	int get_ID();
};

