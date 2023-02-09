#include "PlayerClass.h"
#include <string>
#include <iostream>
#include <vector>

PlayerClass::PlayerClass() {
	this->name = "null";
	this->hitpoint_die_size = 0;
	this->features = std::vector <std::string>{};
	this->ID = -1;
}

PlayerClass::PlayerClass(std::string name, int hitdie, std::vector <std::string> abilities, int ID) {
	this->name = name;
	this->hitpoint_die_size = hitdie;
	this->features = abilities;
	this->ID = ID;
}

std::string PlayerClass::get_name() {
	return name;
}

int PlayerClass::get_hitdie() {
	return hitpoint_die_size;
}

int PlayerClass::get_level() {
	return level;
}

std::vector <std::string> PlayerClass::get_features() {
	return features;
}

int PlayerClass::get_ID() {
	return ID;
}

void PlayerClass::print_features() {
	// this causes a crash, or does not print the correct number of features for some reason. I need some help!
	// Always thinks that there is only one item in the features array.
	for (int i = 0; i < features.size(); i++) {
		std::cout << features.at(i) << std::endl;
	}
}