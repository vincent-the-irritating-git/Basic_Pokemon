#include "Type.h"
#include <iostream>
#include <unordered_map>
#include "Pokemon.h"
#include "Pokemon_Pokedex.h"
#include "Pokemon Names.h"
#include "Stats_n_Status.h"
#include "Move.h"
#include "Move_Pokedex.h"
#include "Move_Names.h"
#include "Battle_Pokemon.h"
#include "Battle_Event.h"

int main() {
	Battle_Pokemon pk(Pokemon_Pokedex::get_gen1_pokemon(PIKACHU));
	Battle_Event::display_moves(pk);
	return 0;
}