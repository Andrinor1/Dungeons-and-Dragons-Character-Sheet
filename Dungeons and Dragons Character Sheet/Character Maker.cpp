#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "PlayerCharacter.h"
#include "PlayerRace.h"
#include "Global_Functions.h"



PlayerRace** get_races_from_file(std::string path) {
	std::ifstream file_in;
	file_in.open(path);
	if (!file_in.is_open()) {
		std::cout << "Unable to locate race file." << std::endl;
		exit(1);
	}
	int num_lines = get_num_lines(path);

	PlayerRace** race_list = new PlayerRace * [num_lines];

	std::string line;
	std::getline(file_in, line);

	for (int i = 0; i < num_lines; i++) {
		std::getline(file_in, line);
		std::stringstream ss(line);

		std::string name;
		std::getline(ss, name, ',');

		int stats[6] = { 0,0,0,0,0,0 };

		for (int j = 0; j < 6; j++) {
			std::string stat_str;
			std::getline(ss, stat_str, ',');
			stats[j] = std::stoi(stat_str);
		}

		race_list[i] = new PlayerRace(stats, name, i);
	}

	return race_list;

	file_in.close();
}

PlayerClass** create_player_classes() {
	std::vector <std::string> barbarian_abilities{ "Rage","Unarmored Defense" };
	std::vector <std::string> bard_abilities{ "Spellcasting","Bardic Inspiration (d6)" };
	std::vector <std::string> cleric_abilities{ "Spellcasting","Divine Domain" };
	std::vector <std::string> druid_abilities{ "Spellcasting","Druidic" };
	std::vector <std::string> fighter_abilities{ "Fighting Style","Second Wind" };
	std::vector <std::string> monk_abilities{ "Martial Arts","Unarmored Defense" };
	std::vector <std::string> paladin_abilities{ "Divine Sense","Lay on Hands" };
	std::vector <std::string> ranger_abilities{ "Favored Enemy","Natural Explorer" };
	std::vector <std::string> rogue_abilities{ "Expertise","Sneak Attack","Thieves' Cant" };
	std::vector <std::string> sorcerer_abilities{ "Spellcasting","Sorcerous Origin" };
	std::vector <std::string> warlock_abilities{ "Otherworldly Patron","Pact Magic" };
	std::vector <std::string> wizard_abilities{ "Spellcasting","Arcane Recovery" };

	PlayerClass** class_list = new PlayerClass * [12] {
		new PlayerClass(std::string{ "Barbarian" }, 12, barbarian_abilities, 0),
			new PlayerClass(std::string{ "Bard" }, 8, bard_abilities, 1),
			new PlayerClass(std::string{ "Cleric" }, 8, cleric_abilities, 2),
			new PlayerClass(std::string{ "Druid" }, 8, druid_abilities, 3),
			new PlayerClass(std::string{ "Fighter" }, 10, fighter_abilities, 4),
			new PlayerClass(std::string{ "Monk" }, 8, monk_abilities, 5),
			new PlayerClass(std::string{ "Paladin" }, 10, paladin_abilities, 6),
			new PlayerClass(std::string{ "Ranger" }, 10, ranger_abilities, 7),
			new PlayerClass(std::string{ "Rogue" }, 8, rogue_abilities, 8),
			new PlayerClass(std::string{ "Sorcerer" }, 6, sorcerer_abilities, 9),
			new PlayerClass(std::string{ "Warlock" }, 8, warlock_abilities, 10),
			new PlayerClass(std::string{ "Wizard" }, 6, wizard_abilities, 11)
	};
	return class_list;
}

int* set_new_stats() {
	int statisticArray[6] = { 15, 14, 13, 12, 10, 8 };
	std::cout << "Would you like rolled stats or standard array?" << std::endl << "1. Standard Array" << std::endl << "2. Rolled Stats" << std::endl;
	int player_choice = player_num_input(2);
	if (player_choice) {
		std::srand(time(NULL)); // random seed based on time
		for (int i = 0; i < 6; i++) {
			int dice[4];
			for (int j = 0; j < 4; j++) {
				int die = rand() % 6 + 1;
				dice[j] = die;
			}
			std::sort(dice, dice + 4);
			statisticArray[i] = dice[1] + dice[2] + dice[3];
		}
		std::sort(statisticArray, statisticArray + 6, std::greater<int>());
	}
	int* characterArray = new int[6] {0, 0, 0, 0, 0, 0};
	std::cout << "To create a character, you must assign your statistics from highest to lowest." << std::endl << std::endl
		<< "Sorted Stats: " << statisticArray[0] << ", " << statisticArray[1] << ", " << statisticArray[2] << ", " << statisticArray[3] << ", " << statisticArray[4] << ", " << statisticArray[5] << std::endl;
	std::cout << "1. Strength: " << characterArray[0] << std::endl
		<< "2. Dexterity: " << characterArray[1] << std::endl
		<< "3. Constitution: " << characterArray[2] << std::endl
		<< "4. Intelligence: " << characterArray[3] << std::endl
		<< "5. Wisdom: " << characterArray[4] << std::endl
		<< "6. Charisma: " << characterArray[5] << std::endl << std::endl;

	for (int i = 0; i < 6; i++) {
		std::string input_str;

		while (true) {
			std::cout << "Choose where to put your " << statisticArray[i] << " (Type in 1-6):\t";
			std::getline(std::cin, input_str);
			int input_num = std::stoi(input_str);

			if (input_num > 6) {
				std::cout << "Invalid selection." << std::endl;
				continue;
			}

			if (characterArray[input_num - 1] > 0) {
				std::cout << "Statistic already assigned. Try again." << std::endl;
			}
			else {
				characterArray[input_num - 1] = statisticArray[i];
				break;
			}
		}
		std::cout << "1. Strength: " << characterArray[0] << std::endl
			<< "2. Dexterity: " << characterArray[1] << std::endl
			<< "3. Constitution: " << characterArray[2] << std::endl
			<< "4. Intelligence: " << characterArray[3] << std::endl
			<< "5. Wisdom: " << characterArray[4] << std::endl
			<< "6. Charisma: " << characterArray[5] << std::endl << std::endl;
	}
	return characterArray;
}

PlayerRace set_race(PlayerRace** race_list) {
	std::cout << "Now, you must choose your race. Select a number from the following." << std::endl;
	int num_races = get_num_lines("data\\races.csv");
	for (int i = 0; i < num_races;i++) {
		std::cout << i + 1 << ": " << race_list[i]->get_name() << std::endl;
	}
	int playerchoice = player_num_input(num_races);
	return *race_list[playerchoice];
}

PlayerClass set_player_class() {
	PlayerClass** class_list = create_player_classes();
	std::cout << "Now, you must choose your class. Select a number from the following." << std::endl;
	for (int i = 0; i < 12;i++) {
		std::cout << i + 1 << ": " << class_list[i]->get_name() << std::endl;
	}
	int playerchoice = player_num_input(12);
	return *class_list[playerchoice];
}

std::vector<std::string> new_option_item(std::vector<std::string> current_items, std::vector<std::string> item_options) {
	for (int i = 0; i < current_items.size(); i++) {
		for (int j = 0; j < item_options.size();j++) {
			if (item_options.at(j) == current_items.at(i)) {
				item_options.erase(item_options.begin() + j);
			}
		}
	}
	if (item_options.size() == 0) {
		std::cout << "Whoops! You already have all available options." << std::endl;
		return current_items;
	}
	for (int i = 0; i < item_options.size(); i++) {
		std::cout << i + 1 << ": " << item_options.at(i) << std::endl;
	}
	int choice = player_num_input((int)item_options.size());
	current_items.push_back(item_options.at(choice));
	return current_items;
}

void set_proficiencies(PlayerCharacter* user) {
	std::vector<std::string> saves, skills, languages, armors, weapons, tools;

	std::vector<std::string> dwarf_langs{ "Common", "Dwarvish" };
	std::vector<std::string> dwarf_weapons{ "Battleaxes","Handaxes","Light Hammers", "Warhammers" };
	std::vector<std::string> mountain_dwarf_armors{ "Light Armor","Medium Armor" };
	std::vector<std::string> dwarf_tools; // Custom choice

	std::vector<std::string> elf_langs{ "Common", "Elvish" };
	std::vector<std::string> elf_skills{ "(Wis) Perception" };
	std::vector<std::string> high_elf_langs; // Custom choice
	std::vector<std::string> wood_elf_weapons{ "Longswords","Shortswords","Longbows","Shortbows" };

	std::vector<std::string> halfling_langs{ "Common", "Halfling" };

	std::vector<std::string> human_langs{ "Common" }; // Custom choice

	std::vector<std::string> dragonborn_langs{ "Common" , "Draconic" };

	std::vector<std::string> gnome_langs{ "Common" , "Gnomish" };
	std::vector<std::string> gnome_tools{ "Tinker's Tools" };

	std::vector<std::string> half_elf_langs; // Custom choice
	std::vector<std::string> half_elf_skills; // Custom choice x2

	std::vector<std::string> half_orc_langs{ "Common" , "Orc" };
	std::vector<std::string> half_orc_skills{ "(Cha) Intimidation" };

	std::vector<std::string> tiefling_langs{ "Common" , "Infernal" };

	std::vector<std::string> dwarf_tool_choice{ "Smith's Tools","Brewer's Supplies","Mason's Tools" };
	std::vector<std::string> language_choice{ "Common","Dwarvish","Elvish","Giant","Gnomish","Goblin","Halfling","Orc","Abyssal","Celestial","Draconic","Deep Speech","Infernal","Primordial","Sylvan","Undercommon" };
	std::vector<std::string> skill_choice{ "(Str) Athletics","(Dex) Acrobatics","(Dex) Sleight of Hand","(Dex) Stealth","(Int) Arcana","(Int) History","(Int) Investigation","(Int) Nature","(Int) Religion","(Wis) Animal Handling","(Wis) Insight","(Wis) Medicine","(Wis) Perception","(Wis) Survival","(Cha) Deception","(Cha) Intimidation","(Cha) Performance","(Cha) Persuasion" };

	switch (user->get_race_ID()) {
	case 0:
		//Hill Dwarf
	{
		std::cout << "Hill Dwarves get a free tool proficiency from the following" << std::endl;
		dwarf_tools = new_option_item(tools, dwarf_tool_choice);
		languages.insert(languages.end(), dwarf_langs.begin(), dwarf_langs.end());
		weapons.insert(weapons.end(), dwarf_weapons.begin(), dwarf_weapons.end());
		tools.insert(tools.end(), dwarf_tools.begin(), dwarf_tools.end());
		break;
	}
	case 1:
		//Mtn. Dwarf
	{
		std::cout << "Hill Dwarves get a free tool proficiency from the following" << std::endl;
		dwarf_tools = new_option_item(tools, dwarf_tool_choice);
		languages.insert(languages.end(), dwarf_langs.begin(), dwarf_langs.end());
		weapons.insert(weapons.end(), dwarf_weapons.begin(), dwarf_weapons.end());
		armors.insert(armors.end(), mountain_dwarf_armors.begin(), mountain_dwarf_armors.end());
		tools.insert(tools.end(), dwarf_tools.begin(), dwarf_tools.end());
		break;
	}
	case 2:
		//High Elf
	{
		std::cout << "High elves get a free language proficiency from the following" << std::endl;
		elf_langs = new_option_item(elf_langs, language_choice);
		languages.insert(languages.end(), elf_langs.begin(), elf_langs.end());
		skills.insert(skills.end(), elf_skills.begin(), elf_skills.end());
		break;
	}
	case 3:
		//Wood Elf
	{
		languages.insert(languages.end(), elf_langs.begin(), elf_langs.end());
		skills.insert(skills.end(), elf_skills.begin(), elf_skills.end());
		weapons.insert(weapons.end(), wood_elf_weapons.begin(), wood_elf_weapons.end());
		break;
	}
	case 4:
		//Stout Halfling
	{
		languages.insert(languages.end(), halfling_langs.begin(), halfling_langs.end());
		break;
	}
	case 5:
		//Human
	{
		std::cout << "Humans get a free language proficiency from the following" << std::endl;
		human_langs = new_option_item(human_langs, language_choice);
		languages.insert(languages.end(), human_langs.begin(), human_langs.end());
		break;
	}
	case 6:
		//Dragonborn
	{
		languages.insert(languages.end(), dragonborn_langs.begin(), dragonborn_langs.end());
		break;
	}
	case 7:
		//Gnome
	{
		languages.insert(languages.end(), gnome_langs.begin(), gnome_langs.end());
		tools.insert(tools.end(), gnome_tools.begin(), gnome_tools.end());
		break;
	}
	case 8:
		//Half-elf
	{
		std::cout << "Half-elves get 2 free skills proficiency from the following. Select the first one:" << std::endl;
		half_elf_skills = new_option_item(half_elf_skills, skill_choice);
		std::cout << "Half-elves get 2 free skills proficiency from the following. Select the second one:" << std::endl;
		half_elf_skills = new_option_item(half_elf_skills, skill_choice);
		std::cout << "Half-elves also get a free language proficiency from the following" << std::endl;
		half_elf_langs = new_option_item(elf_langs, language_choice);
		languages.insert(languages.end(), half_elf_langs.begin(), half_elf_langs.end());
		skills.insert(skills.end(), half_elf_skills.begin(), half_elf_skills.end());
		break;
	}
	case 9:
		//Half-orc
	{
		languages.insert(languages.end(), half_orc_langs.begin(), half_orc_langs.end());
		skills.insert(skills.end(), half_orc_skills.begin(), half_orc_skills.end());
		break;
	}
	case 10:
		//Tiefling
	{
		languages.insert(languages.end(), tiefling_langs.begin(), tiefling_langs.end());
		break;
	}
	}

	std::vector<std::string> martial_weapon_profs{ "Martial Weapons","Simple Weapons" };
	std::vector<std::string> simple_weapon_profs{ "Simple Weapons" };
	std::vector<std::string> light_armor_profs{ "Light Armor" };
	std::vector<std::string> medium_armor_profs{ "Light Armor","Medium Armor","Shields" };
	std::vector<std::string> heavy_armor_profs{ "Light Armor","Medium Armor","Heavy Armor","Shields" };
	std::vector<std::string> instrument_choice{ "Bagpipes","Drum","Dulcimer","Flute","Lute","Lyre","Horn","Pan Flute","Shawm","Viol" };
	std::vector<std::string> tool_choice{ "Alchemist's Supplies","Brewer's Supplies","Calligrapher's Supplies","Carpenter's Tools","Cartographer's Tools","Cobbler's Tools","Cook's Utensils","Glassblower's Tools","Jeweler's Tools","Leatherworker's Tools","Mason's Tools","Navigator's Tools","Painter's Supplies","Potter's Tools","Smith's Tools","Tinker's Tools","Thieves' Tools","Land Vehicles","Water Vehicles","Weaver's Tools","Woodcarver's Tools" };


	std::vector<std::string> barbarian_skills{ "(Wis) Animal Handling" , "(Str) Athletics" , "(Cha) Intimidation" , "(Wis) Nature" , "(Wis) Perception" , "(Wis) Survival" };
	// Bards get every skill as an option!
	std::vector<std::string> cleric_skills{ "(Int) History","(Wis) Insight","(Wis) Medicine","(Cha) Persuasion","(Int) Religion" };
	std::vector<std::string> druid_skills{ "(Int) Arcana","(Wis) Animal Handling","(Wis) Insight","(Wis) Medicine","(Int) Nature","(Wis) Perception","(Int) Religion","(Wis) Survival" };
	std::vector<std::string> fighter_skills{ "(Dex) Acrobatics","(Wis) Animal Handling" ,"(Str) Athletics" ,"(Int) History" ,"(Wis) Insight" ,"(Cha) Intimidation" ,"(Wis) Perception" ,"(Wis) Survival" };
	std::vector<std::string> monk_skills{ "(Dex) Acrobatics","(Str) Athletics" ,"(Int) History" ,"(Wis) Insight","(Int) Religion","(Dex) Stealth" };
	std::vector<std::string> paladin_skills{ "(Str) Athletics" ,"(Wis) Insight","(Cha) Intimidation","(Int) Religion","(Wis) Medicine","(Cha) Persuasion","(Dex) Stealth" };
	std::vector<std::string> ranger_skills{ "(Wis) Animal Handling","(Str) Athletics","(Wis) Insight","(Int) Investigation","(Int) Nature","(Wis) Perception","(Dex) Stealth","(Wis) Survival" };
	std::vector<std::string> rogue_skills{ "(Dex) Acrobatics","(Str) Athletics","(Cha) Deception","(Wis) Insight","(Cha) Intimidation","(Int) Investigation","(Wis) Perception","(Cha) Performance","(Cha) Persuasion","(Dex) Sleight of Hand","(Dex) Stealth" };
	std::vector<std::string> sorcerer_skills{ "(Int) Arcana" ,"(Cha) Deception" ,"(Wis) Insight","(Cha) Intimidation" ,"(Cha) Persuasion", "(Int) Religion" };
	std::vector<std::string> warlock_skills{ "(Int) Arcana" ,"(Cha) Deception" ,"(Int) History","(Cha) Intimidation" ,"(Int) Investigation","(Int) Nature", "(Int) Religion" };
	std::vector<std::string> wizard_skills{ "(Int) Arcana" ,"(Int) History","(Wis) Insight" ,"(Int) Investigation","(Wis) Medicine", "(Int) Religion" };

	std::vector<std::string> class_skills;
	std::vector<std::string> class_tools;

	switch (user->get_class_ID())
	{
	case 0:
		// BARBARIAN
	{
		saves.push_back("Strength Saving Throws");
		saves.push_back("Constitution Saving Throws");
		std::cout << "Barbarians get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, barbarian_skills);
		std::cout << "Barbarians get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, barbarian_skills);
		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), medium_armor_profs.begin(), medium_armor_profs.end());
		weapons.insert(weapons.begin(), martial_weapon_profs.begin(), martial_weapon_profs.end());
		break;
	}
	case 1:
		// BARD
	{
		saves.push_back("Dexterity Saving Throws");
		saves.push_back("Charisma Saving Throws");
		std::cout << "Bards get 3 skill proficiencies from the following. (1/3):" << std::endl;
		class_skills = new_option_item(skills, skill_choice);
		std::cout << "Bards get 3 skill proficiencies from the following. (2/3):" << std::endl;
		class_skills = new_option_item(class_skills, skill_choice);
		std::cout << "Bards get 3 skill proficiencies from the following. (3/3):" << std::endl;
		class_skills = new_option_item(class_skills, skill_choice);
		std::cout << "Bards get 3 Instrument proficiencies from the following. (1/3):" << std::endl;
		class_tools = new_option_item(tools, instrument_choice);
		std::cout << "Bards get 3 Instrument proficiencies from the following. (2/3):" << std::endl;
		class_tools = new_option_item(class_tools, instrument_choice);
		std::cout << "Bards get 3 Instrument proficiencies from the following. (3/3):" << std::endl;
		class_tools = new_option_item(class_tools, instrument_choice);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), light_armor_profs.begin(), light_armor_profs.end());
		weapons.insert(weapons.begin(), simple_weapon_profs.begin(), simple_weapon_profs.end());
		weapons.insert(weapons.begin(), { "Hand Crossbows","Longswords","Shortswords","Rapiers" });
		tools.insert(tools.begin(), class_tools.begin(), class_tools.end());
		break;
	}
	case 2:
		// CLERIC
	{
		saves.push_back("Wisdom Saving Throws");
		saves.push_back("Charisma Saving Throws");
		std::cout << "Clerics get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, cleric_skills);
		std::cout << "Clerics get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, cleric_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), medium_armor_profs.begin(), medium_armor_profs.end());
		weapons.insert(weapons.begin(), martial_weapon_profs.begin(), martial_weapon_profs.end());
		break;
	}
	case 3:
		// DRUID
	{
		saves.push_back("Intelligence Saving Throws");
		saves.push_back("Wisdom Saving Throws");
		std::cout << "Druids get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, druid_skills);
		std::cout << "Druids get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, druid_skills);
		class_tools.push_back("Herbalism Kit");

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), { "Light Armor (Nonmetal)", "Medium Armor (Nonmetal)", "Shields (Nonmetal)" });
		weapons.insert(weapons.begin(), { "Clubs","Daggers","Darts","Javelins","Maces","Quarterstaffs","Scimitars","Sickles","Slings","Spears" });
		tools.insert(tools.begin(), class_tools.begin(), class_tools.end());
		break;
	}
	case 4:
		// FIGHTER
	{
		saves.push_back("Strength Saving Throws");
		saves.push_back("Constitution Saving Throws");
		std::cout << "Fighters get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, fighter_skills);
		std::cout << "Fighters get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, fighter_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), heavy_armor_profs.begin(), heavy_armor_profs.end());
		weapons.insert(weapons.begin(), martial_weapon_profs.begin(), martial_weapon_profs.end());
		break;
	}
	case 5:
		// MONK
	{
		saves.push_back("Strength Saving Throws");
		saves.push_back("Dexterity Saving Throws");
		std::cout << "Monks get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, monk_skills);
		std::cout << "Monks get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, monk_skills);

		std::vector<std::string> monk_tool_choice;
		monk_tool_choice.insert(monk_tool_choice.begin(), instrument_choice.begin(), instrument_choice.end());
		monk_tool_choice.insert(monk_tool_choice.begin(), tool_choice.begin(), tool_choice.end());

		std::cout << "Monks get 1 tool or instrument proficiency from the following:" << std::endl;
		class_tools = new_option_item(tools, monk_tool_choice);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		weapons.insert(weapons.begin(), { "Simple Weapons","Shortswords" });
		tools.insert(tools.begin(), class_tools.begin(), class_tools.end());
		break;
	}
	case 6:
		// PALADIN
	{
		saves.push_back("Wisdom Saving Throws");
		saves.push_back("Charisma Saving Throws");
		std::cout << "Paladins get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, paladin_skills);
		std::cout << "Paladins get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, paladin_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), heavy_armor_profs.begin(), heavy_armor_profs.end());
		weapons.insert(weapons.begin(), martial_weapon_profs.begin(), martial_weapon_profs.end());
		break;
	}
	case 7:
		// RANGER
	{
		saves.push_back("Strength Saving Throws");
		saves.push_back("Constitution Saving Throws");
		std::cout << "Rangers get 3 skill proficiencies from the following. (1/3):" << std::endl;
		class_skills = new_option_item(skills, ranger_skills);
		std::cout << "Rangers get 3 skill proficiencies from the following. (2/3):" << std::endl;
		class_skills = new_option_item(class_skills, ranger_skills);
		std::cout << "Rangers get 3 skill proficiencies from the following. (3/3):" << std::endl;
		class_skills = new_option_item(class_skills, ranger_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), medium_armor_profs.begin(), medium_armor_profs.end());
		weapons.insert(weapons.begin(), martial_weapon_profs.begin(), martial_weapon_profs.end());
		break;
	}
	case 8:
		// ROGUE
	{
		saves.push_back("Dexterity Saving Throws");
		saves.push_back("Intelligence Saving Throws");
		std::cout << "Rogues get 4 skill proficiencies from the following. (1/4):" << std::endl;
		class_skills = new_option_item(skills, rogue_skills);
		std::cout << "Rogues get 4 skill proficiencies from the following. (2/4):" << std::endl;
		class_skills = new_option_item(class_skills, rogue_skills);
		std::cout << "Rogues get 4 skill proficiencies from the following. (3/4):" << std::endl;
		class_skills = new_option_item(class_skills, rogue_skills);
		std::cout << "Rogues get 4 skill proficiencies from the following. (4/4):" << std::endl;
		class_skills = new_option_item(class_skills, rogue_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), light_armor_profs.begin(), light_armor_profs.end());
		weapons.insert(weapons.begin(), simple_weapon_profs.begin(), simple_weapon_profs.end());
		weapons.insert(weapons.begin(), { "Hand Crossbows","Longswords","Shortswords","Rapiers" });
		tools.push_back("Thieves' Tools");
		break;
	}
	case 9:
		// SORCERER
	{
		saves.push_back("Constitution Saving Throws");
		saves.push_back("Charisma Saving Throws");
		std::cout << "Sorcerers get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, sorcerer_skills);
		std::cout << "Sorcerers get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, sorcerer_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		weapons.insert(weapons.begin(), { "Daggers","Darts","Slings","Quarterstaffs","Light Crossbows" });
		break;
	}
	case 10:
		// WARLOCK
	{
		saves.push_back("Wisdom Saving Throws");
		saves.push_back("Charisma Saving Throws");
		std::cout << "Warlocks get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, warlock_skills);
		std::cout << "Warlocks get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, warlock_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		armors.insert(armors.begin(), light_armor_profs.begin(), light_armor_profs.end());
		weapons.insert(weapons.begin(), simple_weapon_profs.begin(), simple_weapon_profs.end());
		break;
	}
	case 11:
		// WIZARD
	{
		saves.push_back("Intelligence Saving Throws");
		saves.push_back("Wisdom Saving Throws");
		std::cout << "Wizards get 2 skill proficiencies from the following. (1/2):" << std::endl;
		class_skills = new_option_item(skills, wizard_skills);
		std::cout << "Wizards get 2 skill proficiencies from the following. (2/2):" << std::endl;
		class_skills = new_option_item(class_skills, wizard_skills);

		skills.insert(skills.begin(), class_skills.begin(), class_skills.end());
		weapons.insert(weapons.begin(), { "Daggers","Darts","Slings","Quarterstaffs","Light Crossbows" });
		break;
	}
	}

	std::cout << "Now, time for your background!" << std::endl << "Every hero starts from somewhere. What have skills have you learned ? (1/2)" << std::endl << std::endl;
	skills = new_option_item(skills, skill_choice);
	std::cout << "Every hero starts from somewhere. What have skills have you learned? (2/2)" << std::endl << std::endl;
	skills = new_option_item(skills, skill_choice);
	for (int i = 0; i < 2; i++) {
		std::cout << "And, what two tools or languages have you picked up along the way? (" << i + 1 << "/2)" << std::endl << std::endl;
		std::cout << "1. Tool" << std::endl << "2. Language" << std::endl;
		if (player_num_input(2)) {
			languages = new_option_item(languages, language_choice);
		}
		else {
			tools = new_option_item(tools, tool_choice);
		}
	}

	std::vector<std::vector<std::string>> final {saves, skills, languages, armors, weapons, tools};

	for (int i = 0; i < final.size(); i++) {
		std::vector<std::string> v = final.at(i);
		std::sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
		final.at(i) = v;
	}

	user->set_proficiencies(std::vector<std::vector<std::string>>{saves, skills, languages, armors, weapons, tools});
}

void set_spells(PlayerCharacter* user) {
	std::vector<std::string> cantrip_options, lev1_spell_options, cantrips, lev1_spells;
	int known_num_cantrips, known_num_lev1_spells;
	std::string spell_type = "known";
	switch (user->get_class_ID()) {
	case 1: // bard
	{
		known_num_cantrips = 2;
		known_num_lev1_spells = 4;
		cantrip_options.insert(cantrip_options.begin(), { "Light", "Mage Hand", "Message", "Prestidigitation", "Vicious Mockery" });
		lev1_spell_options.insert(lev1_spell_options.begin(), { "Charm Person","Comprehend Languages","Cure Wounds","Disguise Self","Healing Word","Heroism","Identify","Silent Image","Sleep","Speak with Animals" });
		break;
	}
	case 2: // cleric
	{
		spell_type = "prepared";
		int wis_mod = std::floor((user->get_wisdom() - 10) / 2); // Wisdom modifier used to determine prepared spells
		known_num_cantrips = 3;
		known_num_lev1_spells = 1 + wis_mod;
		if (known_num_lev1_spells < 1) {
			known_num_lev1_spells = 1;
		}
		cantrip_options.insert(cantrip_options.begin(), { "Guidance","Light","Mending","Resistance","Sacred Flame","Spare the Dying" });
		lev1_spell_options.insert(lev1_spell_options.begin(), { "Bane","Bless","Command","Cure Wounds","Detect Evil and Good","Detect Magic","Detect Poison and Disease","Guiding Bolt","Healing Word","Inflict Wounds","Sanctuary","Shield of Faith" });
		break;
	}
	case 3: // druid
	{
		spell_type = "prepared";
		int wis_mod = std::floor((user->get_wisdom() - 10) / 2);
		known_num_cantrips = 2;
		known_num_lev1_spells = 1 + wis_mod; // Wisdom modifier used to determine prepared spells
		if (known_num_lev1_spells < 1) {
			known_num_lev1_spells = 1;
		}
		cantrip_options.insert(cantrip_options.begin(), { "Druidcraft","Guidance","Mending","Poison Spray","Produce Flame","Resistance","Shillelagh" });
		lev1_spell_options.insert(lev1_spell_options.begin(), { "Animal Friendship","Create or Destroy Water","Cure Wounds","Detect Poison and Disease","Entangle","Fog Cloud","Goodberry","Healing Word","Longstrider","Purify Food and Drink","Speak with Animals" });
		break;
	}
	case 9: // sorcerer
	{
		known_num_cantrips = 4;
		known_num_lev1_spells = 2;
		cantrip_options.insert(cantrip_options.begin(), { "Acid Splash","Chill Touch","Dancing Lights","Fire Bolt","Mage Hand","Minor Illusion","Prestidigitation","Ray of Frost","Shocking Grasp" });
		lev1_spell_options.insert(lev1_spell_options.begin(), { "Burning Hands","Color Spray","Detect Magic","Disguise Self","False Life","Feather Fall","Jump","Mage Armor","Magic Missile","Shield","Sleep","Thunderwave" });
		break;
	}
	case 10: // warlock
	{
		known_num_cantrips = 2;
		known_num_lev1_spells = 2;
		cantrip_options.insert(cantrip_options.begin(), { "Chill Touch","Eldritch Blast","Mage Hand","Minor Illusion","Poison Spray","Prestidigitation" });
		lev1_spell_options.insert(lev1_spell_options.begin(), { "Charm Person","Comprehend Languages","Hellish Rebuke","Illusory Script","Protection from Evil and Good","Unseen Servant" });
		break;
	}
	case 11: // wizard
	{
		known_num_cantrips = 3;
		known_num_lev1_spells = 6;
		cantrip_options.insert(cantrip_options.begin(), { "Acid Splash","Chill Touch","Dancing Lights","Fire Bolt","Mage Hand","Minor Illusion","Prestidigitation","Ray of Frost","Shocking Grasp" });
		lev1_spell_options.insert(lev1_spell_options.begin(), { "Alarm", "Burning Hands","Color Spray","Detect Magic","Disguise Self","False Life","Feather Fall","Find Familiar","Grease","Identify","Mage Armor","Magic Missile","Shield","Sleep","Thunderwave" });
		break;
	}
	}
	std::cout << "Because you chose to play as a " << user->get_class_name() << ", you need to choose " << known_num_cantrips << " cantrips and " << known_num_lev1_spells << " " << spell_type << " spells." << std::endl;
	for (int i = 0; i < known_num_cantrips; i++) {
		std::cout << "Select a cantrip (" << i + 1 << "/" << known_num_cantrips << ")" << std::endl;
		cantrips = new_option_item(cantrips, cantrip_options);
	}
	for (int i = 0; i < known_num_lev1_spells; i++) {
		std::cout << "Select a level 1 spell (" << i + 1 << "/" << known_num_lev1_spells << ")" << std::endl;
		lev1_spells = new_option_item(lev1_spells, lev1_spell_options);
	}
	std::vector<std::vector<std::string>> spells{ cantrips,lev1_spells };
	user->set_spells(spells);
}


PlayerCharacter* create_new_pc(PlayerRace** race_list) {
	std::cout << "Name your character." << std::endl;
	std::string character_name;
	std::getline(std::cin, character_name);

	int* stat_array = set_new_stats();

	PlayerRace pc_race = set_race(race_list);
	if (pc_race.get_name() == "Half-elf") {
		pc_race.set_halfelf_bonuses();
	}
	PlayerClass pc_class = set_player_class();

	PlayerCharacter* user = new PlayerCharacter(stat_array, pc_race, pc_class, character_name, false);

	set_proficiencies(user);

	if (pc_class.get_ID() == 1 || pc_class.get_ID() == 2 || pc_class.get_ID() == 3 || pc_class.get_ID() == 9 || pc_class.get_ID() == 10 || pc_class.get_ID() == 11){
		set_spells(user);
	}

	return user;
}

void save_file(PlayerCharacter user_character, std::string path) {
	std::ofstream out_stream;
	out_stream.open(path, std::ios::app);
	if (out_stream.is_open()) {
		std::cout << "Writing to file...";
		out_stream << user_character.get_name() << std::endl;
		out_stream << "Character Stats" << std::endl;
		out_stream << "STR," << "DEX," << "CON," << "INT," << "WIS," << "CHA," << std::endl;
		out_stream << user_character.get_strength() << ","
			<< user_character.get_dexterity() << ","
			<< user_character.get_constitution() << ","
			<< user_character.get_intelligence() << ","
			<< user_character.get_wisdom() << ","
			<< user_character.get_charisma() << "," << std::endl;
		out_stream << user_character.get_race_name() << "," << user_character.get_class_name() << "," << user_character.get_level() << std::endl;
		out_stream << user_character.get_race_ID() << "," << user_character.get_class_ID() << "," << std::endl;

		for (int i = 0; i < 6; i++) {
			int size = user_character.get_proficiencies().at(i).size();
			//std::cout << "PROFICIENCY SAVING: SIZE OF ELEMENT INDEX " << i << ": " << size << std::endl;
			out_stream << size << std::endl;
			for (int j = 0;j < size;j++) {
				out_stream << user_character.get_proficiencies().at(i).at(j) << ',';
			}
			out_stream << std::endl;
		}

		for (int i = 0; i < user_character.get_spells().size(); i++) {
			int size = user_character.get_spells().at(i).size();
			//std::cout << "SPELL SAVING: SIZE OF ELEMENT INDEX " << i << ": " << size << std::endl;
			out_stream << size << std::endl;
			for (int j = 0;j < size;j++) {
				out_stream << user_character.get_spells().at(i).at(j) << ',';
			}
			out_stream << std::endl;
		}

		out_stream.close();
		std::cout << "Done!" << std::endl;
	}
	else {
		std::cout << "Could not write to file." << std::endl;
	}
}

PlayerCharacter load_file(std::string path) {
	std::ifstream in_stream;
	in_stream.open(path);

	if (in_stream.is_open()) {
		std::cout << "Reading character...";
		std::string line;

		std::string name;
		std::getline(in_stream, name);

		std::getline(in_stream, line);
		std::getline(in_stream, line);
		std::getline(in_stream, line);
		std::stringstream ss(line);

		int* stat_array = new int [6] {0, 0, 0, 0, 0, 0};
		for (int i = 0; i < 6; i++) {
			std::string stat_str;
			std::getline(ss, stat_str, ',');
			int stat = std::stoi(stat_str);
			stat_array[i] = stat;
		}

		std::getline(in_stream, line);
		std::string temp_str;
		std::stringstream ss2(line);

		std::getline(ss2, temp_str, ',');
		std::getline(ss2, temp_str, ',');
		std::getline(ss2, temp_str, ',');

		int level = std::stoi(temp_str);

		std::getline(in_stream, line);
		std::stringstream ss3(line);
		std::getline(ss3, temp_str, ',');
		int race_ID = std::stoi(temp_str);
		std::getline(ss3, temp_str, ',');
		int class_ID = std::stoi(temp_str);

		std::cout << "Done!" << std::endl << std::endl;

		PlayerClass** class_list = create_player_classes();
		PlayerRace** race_list = get_races_from_file("data\\races.csv");

		PlayerCharacter user_character(stat_array, *race_list[race_ID], *class_list[class_ID], name, true);
		std::vector<std::string> saves, skills, languages, armors, weapons, tools;
		std::vector<std::vector<std::string>> proficiencies{ saves, skills, languages, armors, weapons, tools };

		for (int i = 0; i < 6; i++) {
			std::getline(in_stream, temp_str);
			int size = std::stoi(temp_str);
			std::getline(in_stream, line);
			std::stringstream ss4(line);
			for (int j = 0;j < size;j++) {
				std::getline(ss4, temp_str, ',');
				proficiencies.at(i).push_back(temp_str);
			}
		}

		std::vector<std::string> cantrips, lev1_spells;
		std::vector<std::vector<std::string>> spells{ cantrips,lev1_spells };

		for (int i = 0; i < 2; i++) {
			std::getline(in_stream, temp_str);
			int size = std::stoi(temp_str);
			std::getline(in_stream, line);
			std::stringstream ss4(line);
			for (int j = 0;j < size;j++) {
				std::getline(ss4, temp_str, ',');
				spells.at(i).push_back(temp_str);
			}
		}

		user_character.set_proficiencies(proficiencies);
		user_character.set_spells(spells);

		return user_character;
	}
	else {
		std::cout << "Could not load player file." << std::endl;
		return PlayerCharacter();
	}
}

int main() {
	std::cout << "Loading race files (Should be located at data\\races.csv ..." << std::endl;
	PlayerRace** race_list = get_races_from_file("data\\races.csv");

	std::cout << "Hello! Welcome to Griffin's D&D 5e Character Creator!" << std::endl;
	std::cout << "(C)reate a character, or (L)oad a character?\t";

	std::string input;
	std::getline(std::cin, input);
	while (input != "c" && input != "l" && input != "C" && input != "L") {
		std::cout << "Invalid answer." << std::endl << "(C)reate a character, or (L)oad a character?\t";
		std::getline(std::cin, input);
	}

	PlayerCharacter userPC;

	if (input == "c" || input == "C") {
		std::cout << std::endl;
		userPC = *create_new_pc(race_list);

		std::cout << std::endl;
		std::string out_path = "data\\character.csv";
		save_file(userPC, out_path);

		userPC.print_sheet();


	}

	if (input == "l" || input == "L") {
		std::cout << std::endl;
		userPC = load_file("data\\character.csv");
		userPC.print_sheet();
	}

	std::srand(time(NULL)); // random seed based on current time

	std::cout << "What would you like to do?" << std::endl << "1. Quit" << std::endl << "2. Roll Dice" << std::endl << "3. Take Damage" << std::endl << "4. Heal" << std::endl << "5. View Sheet" << std::endl;
	int num_input = player_num_input(5);

	while (num_input) {
		std::string temp;
		switch (num_input) {
		case 1:
		{
			std::cout << "How many dice would you like to roll?\t";
			std::getline(std::cin, temp);
			int num_dice = std::stoi(temp);
			while (num_dice < 1) {
				std::cout << "Invalid number of dice. Try again." << std::endl;
				std::getline(std::cin, temp);
				num_dice = std::stoi(temp);
			}
			std::cout << std::endl << "How many sides on the di(c)e you would like to roll?\t";
			std::getline(std::cin, temp);
			int type_dice = std::stoi(temp);
			while (type_dice < 1) {
				std::cout << "Invalid number of sides. Try again." << std::endl;
				std::getline(std::cin, temp);
				type_dice = std::stoi(temp);
			}
			std::cout << std::endl << "How much of a modifier will this roll have? Consider ability score bonuses, proficiency, and magic:\t";
			std::getline(std::cin, temp);
			int roll_modifier = std::stoi(temp);

			int sum = roll_modifier;
			for (int i = 0; i < num_dice; i++) {
				int die = rand() % type_dice + 1;
				std::cout << die << " + ";
				sum += die;
			}
			std::cout << roll_modifier << " = " << sum << " total." << std::endl << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "How much damage?\t";
			std::getline(std::cin, temp);
			int damage = -1 * std::stoi(temp);
			userPC.adjust_hp(damage);
			break;
		}
		case 3:
		{
			std::cout << "How much health?\t";
			std::getline(std::cin, temp);
			int healing = std::stoi(temp);
			userPC.adjust_hp(healing);
			break;
		}
		case 4:
		{
			userPC.print_sheet();
			break;
		}
		}
		std::cout << "What would you like to do?" << std::endl << "1. Quit" << std::endl << "2. Roll Dice" << std::endl << "3. Take Damage" << std::endl << "4. Heal" << std::endl << "5. View Sheet" << std::endl;
		num_input = player_num_input(5);
	}
	return 0;
}