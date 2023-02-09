#include "Global_Functions.h"
#include <iostream>
#include <fstream>
#include <string>

int player_num_input(int max) {
	std::string playerchoice_str;
	std::getline(std::cin, playerchoice_str);
	int playerchoice = std::stoi(playerchoice_str) - 1;
	while (playerchoice < 0 || playerchoice >= max) {
		std::cout << "Invalid choice." << std::endl;
		std::getline(std::cin, playerchoice_str);
		playerchoice = std::stoi(playerchoice_str) - 1;
	}
	std::cout << std::endl;
	return playerchoice;
}

int get_num_lines(std::string path) {
	std::ifstream file_in;
	file_in.open(path);
	if (!file_in.is_open()) {
		std::cout << "Unable to locate file." << std::endl;
		return 1;
	}

	int num_lines = 0;

	std::string a;
	std::getline(file_in, a);
	while (std::getline(file_in, a)) {
		num_lines++;
	}
	file_in.close();
	return num_lines;
}