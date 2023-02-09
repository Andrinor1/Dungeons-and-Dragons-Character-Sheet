#include "PlayerRace.h"
//#include "Character Maker.cpp"
#include <string>
#include <iostream>
#include "Global_Functions.h"

PlayerRace::PlayerRace(int arr[6], std::string name, int ID) {
	for (int i = 0; i < 6; i++) {
		stat_bonuses[i] = arr[i];
	}
	this->name = name;
	this->ID = ID;
}

PlayerRace::PlayerRace() {
	this->name = "null";
	this->ID = -1;
}

std::string PlayerRace::get_name() {
	return name;
}

int* PlayerRace::get_bonuses() {
	return this->stat_bonuses;
}

void PlayerRace::set_halfelf_bonuses() {
	std::cout << "As a Half-elf, you get to choose two statistics to increase." << std::endl
		<< "Choose the first statistic by number." << std::endl
		<< "1. Strength" << std::endl
		<< "2. Dexterity" << std::endl
		<< "3. Constitution" << std::endl
		<< "4. Intelligence" << std::endl
		<< "5. Wisdom" << std::endl
		<< "6. Charisma" << std::endl << std::endl;
	stat_bonuses[player_num_input(6)] += 1;
	std::cout << "Choose the second statistic by number." << std::endl
		<< "1. Strength" << std::endl
		<< "2. Dexterity" << std::endl
		<< "3. Constitution" << std::endl
		<< "4. Intelligence" << std::endl
		<< "5. Wisdom" << std::endl
		<< "6. Charisma" << std::endl << std::endl;
	stat_bonuses[player_num_input(6)] += 1;
}

void PlayerRace::print() {
	std::cout << name << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cout << "Stat " << i << ": " << stat_bonuses[i] << std::endl;
	}

}

int PlayerRace::get_ID() {
	return ID;
}