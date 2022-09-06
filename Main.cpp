#include "Type.h"
#include <iostream>
#include <unordered_map>
#include "Pokemon.h"
#include "Pokemon_Pokedex.h"
#include "Pokemon Names.h"
#include "Stats_n_Status.h"
#include "Move.h"
#include "Move_Pokedex.h"
#include "Battle_Pokemon.h"

int main() {

	std::cout << std::endl;
	const Move* m = Move_Pokedex::get_gen1_moves("Growl");
	m->show_move_values();

	for(const Move* m:Move_Pokedex::get_gen1_default_movesets("Pikachu"))
		std::cout<<m->m_name<<std::endl;
}