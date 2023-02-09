#pragma once
#include "PlayerRace.h"
#include "PlayerClass.h"
#include <string>

class PlayerCharacter
{
private:
	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int wisdom;
	int charisma;
	int max_hp;
	int hp;
	PlayerRace race;
	PlayerClass player_class;
	std::string name;
	std::vector<std::vector<std::string>> proficiencies;
	std::vector<std::vector<std::string>> spells;

public:
	PlayerCharacter();
	PlayerCharacter(int statArray[], PlayerRace race, PlayerClass player_class, std::string name, bool loaded);

	int get_strength();
	int get_dexterity();
	int get_constitution();
	int get_intelligence();
	int get_wisdom();
	int get_charisma();
	std::string get_race_name();
	int get_race_ID();
	std::string get_class_name();
	int get_class_ID();
	int get_level();
	std::string get_name();
	std::vector<std::vector<std::string>> get_proficiencies();
	std::vector<std::vector<std::string>> get_spells();

	void set_strength(int s);
	void set_dexterity(int d);
	void set_constitution(int c);
	void set_intelligence(int i);
	void set_wisdom(int w);
	void set_charisma(int ch);
	void adjust_hp(int hp);
	void set_proficiencies(std::vector<std::vector<std::string>> new_proficiencies);
	void set_spells(std::vector<std::vector<std::string>> new_spells);
	void print_sheet();
};

