#include "Pokemon_Pokedex.h"
#include "Pokemon Names.h"

using namespace status_and_stats;

namespace pokemon_definitions {
	Gen1_Pokemon missingno(-1, MISSINGNO, Type::NONE, Type::NONE, Pokemon::Evolutions(), Gen1_Pokemon::Gen1_Stats(0, 0, 0, 0, 0));
	//Gen1_Pokemon bulbasaur(1, "Bulbasaur", Type::GRASS, Type::POISON, Pokemon::Evolutions(2, 16), Gen1_Pokemon::Gen1_Stats(45, 49, 49, 65, 45));
	Gen1_Pokemon pikachu(25, PIKACHU, Type::ELECTRIC, Type::NONE, Pokemon::Evolutions(), Gen1_Pokemon::Gen1_Stats(35, 55, 30, 50, 90));
	//Gen1_Pokemon alakazam(65, "Alakazam", Type::PSYCHIC, Type::NONE, Pokemon::Evolutions(), Gen1_Pokemon::Gen1_Stats(55, 50, 45, 135, 120));
	Gen1_Pokemon pinsir(127, PINSIR, Type::BUG, Type::NONE, Pokemon::Evolutions(), Gen1_Pokemon::Gen1_Stats(65, 125, 100, 55, 85));
	//Gen1_Pokemon moltres(146, "Moltres", Type::FIRE, Type::FLYING, Pokemon::Evolutions(), Gen1_Pokemon::Gen1_Stats(90, 100, 90, 125, 90));
}

const std::unordered_map<std::string, Gen1_Pokemon> Pokemon_Pokedex::initialise_pokemon_map()
{
	using namespace pokemon_definitions;
	std::unordered_map<std::string, Gen1_Pokemon> m;
	m.insert({ missingno.get_pokemon_name(), missingno });
	m.insert({ pinsir.get_pokemon_name(), pinsir });
	//m.insert({ bulbasaur.get_pokemon_name(),bulbasaur });
	m.insert({ pikachu.get_pokemon_name(),pikachu });
	//m.insert({ moltres.get_pokemon_name(),moltres });
	return m;
}

const std::unordered_map<std::string, Gen1_Pokemon> Pokemon_Pokedex::gen1_Pokemon_map{ Pokemon_Pokedex::initialise_pokemon_map() };

const Gen1_Pokemon& Pokemon_Pokedex::get_gen1_pokemon(std::string name) {
	try {
		return Pokemon_Pokedex::gen1_Pokemon_map.at(name);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::cout << "No such pokemon found.";
	}
	return Pokemon_Pokedex::gen1_Pokemon_map.at(MISSINGNO);
}

bool Pokemon_Pokedex::is_pokemon_in_map(std::string name)
{
	try {
		Pokemon_Pokedex::gen1_Pokemon_map.at(name);
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}