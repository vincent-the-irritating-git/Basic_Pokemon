#pragma once
#include <array>
#include "Move Constants.h"
#include "Move.h"
#include "Pokemon Names.h"

class Move_Pokedex {
private:
	const static std::unordered_map<std::string, Move*>gen1_moves;
	const static std::unordered_map < std::string, const std::array<const Move*, 4>>gen1_default_movesets;
public:
	const static std::unordered_map<std::string, Move*>initialise_gen1_moves();
	const static std::unordered_map < std::string, const std::array<const Move*, 4>>initialise_gen1_default_movesets();
	static const std::array<const Move*,MAX_MOVES>& get_gen1_default_movesets(std::string name);
	static const Move* get_gen1_moves(std::string name);
	static bool is_move_in_map(std::string name);
	static bool is_default_moveset_in_map(std::string name);
};