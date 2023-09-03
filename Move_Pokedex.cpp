#include "Move_Pokedex.h"
#include "Move_Names.h"
#include "Move.h"

	namespace moves {
		Attack_Move DEFAULT_MOVE(NULL_MOVE, 0, 0, Type::NONE, 0);
		//Damage_Status_Effect poison_powder("Poison Powder", 15, 75, Type::POISON, 0, Status_Effect_Change(status_effect_value::POISON, status_and_stats::stats_value::HP,xx));
		Stats_Value_Attack_Move growl(GROWL, 40, 100, Type::NORMAL, 0, Stats_Change(status_and_stats::stats_value::ATTACK, -50));
		Status_Effect_Attack_Move thundershock(THUNDER_SHOCK, 30, 100, Type::ELECTRIC, 40, status_effect::PARALYSIS, 10);
		Attack_Move tackle(TACKLE, 35, 95, Type::NORMAL, 35);
		Defence_Move defence_curl(DEFENCE_CURL, 40, 100, Type::NORMAL, Stats_Change(status_and_stats::stats_value::DEFENCE, 50));
		Status_Effect_Attack_Move thunder_wave(THUNDER_WAVE, 20, 100, Type::ELECTRIC, 0, status_effect::PARALYSIS,100);
	}

const std::unordered_map<std::string, Move*> Move_Pokedex::initialise_gen1_moves()
{
	using namespace moves;
	std::unordered_map<std::string, Move*> m;
	//Status_Effect_Attack_Move* ptr_poison_powder = std::make_shared <Status_Effect_Attack_Move>(poison_powder);
	Status_Effect_Attack_Move* ptr_thundershock = &thundershock;
	Stats_Value_Attack_Move* ptr_growl = &growl;
	Attack_Move* ptr_DEFAULT_MOVE = &moves::DEFAULT_MOVE;
	Attack_Move* ptr_tackle = &tackle;
	Defence_Move* ptr_defence_curl = &defence_curl;
	Status_Effect_Attack_Move* ptr_thunder_wave = &thunder_wave;
	//m.insert({ poison_powder.m_name,ptr_poison_powder });
	m.insert({ GROWL, ptr_growl });
	m.insert({ NULL_MOVE, ptr_DEFAULT_MOVE });
	m.insert({ THUNDER_SHOCK, ptr_thundershock });
	m.insert({ TACKLE, ptr_tackle });
	m.insert({ DEFENCE_CURL, ptr_defence_curl });
	m.insert({ THUNDER_WAVE, ptr_thunder_wave });
	return m;
}

const std::unordered_map<std::string, const std::array<const Move*, MAX_MOVES>> Move_Pokedex::initialise_gen1_default_movesets()
{
	std::unordered_map<std::string, const std::array<const Move*, 4>>m;
	std::array<const Move*, MAX_MOVES>pikachu_moves{
		Move_Pokedex::gen1_moves.at(TACKLE),
		Move_Pokedex::gen1_moves.at(THUNDER_SHOCK),
		Move_Pokedex::gen1_moves.at(THUNDER_WAVE),
		Move_Pokedex::gen1_moves.at(NULL_MOVE)
	};

	std::array<const Move*, MAX_MOVES>pinsir_moves{
	Move_Pokedex::gen1_moves.at(TACKLE),
	Move_Pokedex::gen1_moves.at(DEFENCE_CURL),
	Move_Pokedex::gen1_moves.at(GROWL),
	Move_Pokedex::gen1_moves.at(NULL_MOVE)
	};

	std::array<const Move*, MAX_MOVES>missingo_moves{
		Move_Pokedex::gen1_moves.at(NULL_MOVE),
		Move_Pokedex::gen1_moves.at(NULL_MOVE),
		Move_Pokedex::gen1_moves.at(NULL_MOVE),
		Move_Pokedex::gen1_moves.at(NULL_MOVE)
	};
	m.insert({ PIKACHU, pikachu_moves });
	m.insert({ MISSINGNO, missingo_moves });
	m.insert({ PINSIR, pinsir_moves });
	return m;
}

const std::unordered_map<std::string, Move*> Move_Pokedex::gen1_moves{ Move_Pokedex::initialise_gen1_moves() };
const std::unordered_map < std::string, const std::array<const Move*, MAX_MOVES>>Move_Pokedex::gen1_default_movesets{ Move_Pokedex::initialise_gen1_default_movesets() };

bool Move_Pokedex::is_move_in_map(std::string name)
{
	try {
		Move_Pokedex::gen1_moves.at(name);
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

bool Move_Pokedex::is_default_moveset_in_map(std::string name)
{
	try {
		Move_Pokedex::gen1_default_movesets.at(name);
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

const Move* Move_Pokedex::get_gen1_moves(std::string name)
{
	try {
		return Move_Pokedex::gen1_moves.at(name);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::cout << "No such move found.";
	}
	return Move_Pokedex::gen1_moves.at(NULL_MOVE);
}

const std::array<const Move*, MAX_MOVES>& Move_Pokedex::get_gen1_default_movesets(std::string name)
{
	try {
		return Move_Pokedex::gen1_default_movesets.at(name);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::cout << "No such moveset found.";
	}
	return Move_Pokedex::gen1_default_movesets.at(MISSINGNO);
}