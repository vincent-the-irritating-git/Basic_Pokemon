#include "Type.h"
#include <iostream>
#include <unordered_map>
#include "Pokemon.h"
#include "Pokemon_Pokedex.h"
#include "Constants.h"
#include "Stats_n_Status.h"
#include "Move.h"
#include "Move_Pokedex.h"
#include "Battle_Pokemon.h"

using namespace Move_names;

int main() {
	for (auto m : Move_Pokedex::gen1_moves) {
		std::cout << m.first << std::endl;
	}
	const Move* m = Move_Pokedex::get_gen1_moves(DEFENCE_CURL);
	m->show_move_values();
}