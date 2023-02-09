#include "PlayerCharacter.h"
#include "PlayerRace.h"
#include "PlayerClass.h"
#include <string>
#include <iostream>

PlayerCharacter::PlayerCharacter() {
	this->strength = 0;
	this->dexterity = 0;
	this->constitution = 0;
	this->intelligence = 0;
	this->wisdom = 0;
	this->charisma = 0;
	this->hp = 0;
	this->max_hp = 0;
}
PlayerCharacter::PlayerCharacter(int statArray[], PlayerRace race, PlayerClass player_class, std::string name, bool loaded) {
	this->player_class = player_class;
	this->race = race;
	this->name = name;
	if (!loaded) {
		int* race_bonuses = race.get_bonuses();
		for (int i = 0; i < 6; i++) {
			statArray[i] += race_bonuses[i];
		}
	}
	this->strength = statArray[0];
	this->dexterity = statArray[1];
	this->constitution = statArray[2];
	this->intelligence = statArray[3];
	this->wisdom = statArray[4];
	this->charisma = statArray[5];
	this->spells = std::vector<std::vector<std::string>>{ {"None"} };

	this->max_hp = player_class.get_hitdie() + std::floor((this->constitution - 10) / 2);
	this->hp = this->max_hp;
}

int PlayerCharacter::get_strength() {
	return this->strength;
}
int PlayerCharacter::get_dexterity() {
	return this->dexterity;
}
int PlayerCharacter::get_constitution() {
	return this->constitution;
}
int PlayerCharacter::get_intelligence() {
	return this->intelligence;
}
int PlayerCharacter::get_wisdom() {
	return this->wisdom;
}
int PlayerCharacter::get_charisma() {
	return this->charisma;
}
std::string PlayerCharacter::get_class_name() {
	return player_class.get_name();
}
int PlayerCharacter::get_class_ID() {
	return player_class.get_ID();
}
std::string PlayerCharacter::get_race_name() {
	return race.get_name();
}
int PlayerCharacter::get_race_ID() {
	return race.get_ID();
}
int PlayerCharacter::get_level() {
	return player_class.get_level();
}
std::string PlayerCharacter::get_name() {
	return name;
}
std::vector<std::vector<std::string>> PlayerCharacter::get_proficiencies() {
	return proficiencies;
}
std::vector<std::vector<std::string>> PlayerCharacter::get_spells() {
	return spells;
}

void PlayerCharacter::set_strength(int s) {
	this->strength = s;
}
void PlayerCharacter::set_dexterity(int d) {
	this->dexterity = d;
}
void PlayerCharacter::set_constitution(int c) {
	this->constitution = c;
}
void PlayerCharacter::set_intelligence(int d) {
	this->intelligence = d;
}
void PlayerCharacter::set_wisdom(int w) {
	this->wisdom = w;
}
void PlayerCharacter::set_charisma(int ch) {
	this->charisma = ch;
}
void PlayerCharacter::adjust_hp(int hp) {
	this->hp += hp;
	if (this->hp > this->max_hp) {
		this->hp = this->max_hp;
	}
	if (this->hp < 1) {
		std::cout << "You are down!" << std::endl;
		this->hp = 0;
	}
}
void PlayerCharacter::set_proficiencies(std::vector<std::vector<std::string>> new_proficiencies) {
	proficiencies = new_proficiencies;
}
void PlayerCharacter::set_spells(std::vector<std::vector<std::string>> new_spells) {
	spells = new_spells;
}

void PlayerCharacter::print_sheet() {
	std::cout << name << std::endl
		<< "Level " << player_class.get_level() << " "
		<< race.get_name() << " "
		<< player_class.get_name() << std::endl;
	std::cout << "Health: " << hp << "/" << max_hp << std::endl;
	std::cout << "Strength: " << this->get_strength() << std::endl
		<< "Dexterity: " << this->get_dexterity() << std::endl
		<< "Constitution: " << this->get_constitution() << std::endl
		<< "Intelligence: " << this->get_intelligence() << std::endl
		<< "Wisdom: " << this->get_wisdom() << std::endl
		<< "Charisma: " << this->get_charisma() << std::endl;
	std::cout << std::endl << "Class Features" << std::endl;
	player_class.print_features();
	
	std::cout << std::endl << "Proficiencies:" << std::endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < proficiencies.at(i).size(); j++) {
			std::cout << proficiencies.at(i).at(j) << std::endl;
		}
	}
	std::cout << std::endl << "Spells:" << std::endl << std::endl;
	for (int i = 0; i < spells.size(); i++) {
		if (i == 0) {
			std::cout << "Cantrips" << std::endl;
		} else {
			std::cout << "Level " << i << " spells" << std::endl;
		}

		for (int j = 0; j < spells.at(i).size(); j++) {
			std::cout << spells.at(i).at(j) << std::endl;
		}

		std::cout << std::endl;
	}
}

