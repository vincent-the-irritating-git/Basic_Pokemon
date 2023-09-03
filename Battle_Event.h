#pragma once
#include <iostream>
#include "Pokemon Names.h"
#include "Move Constants.h"
#include "Pokemon.h"
#include "Battle_Pokemon.h"
#include "Pokemon_Pokedex.h"
#include "Move_Pokedex.h"
#include "Move.h"
#include <array>
#include <regex>

static class Battle_Event {
private:
	static std::array<Battle_Pokemon*, 2> turn_order;
	static bool isFainted;
	static Battle_Pokemon* current;
	static Battle_Pokemon* opposing;
	static Battle_Pokemon user;
	static Battle_Pokemon ai;
public:
	static void display_moves(Battle_Pokemon& current);
	static int select_move(Battle_Pokemon& current);
	static void do_move(Battle_Pokemon& current, const Move& chosen_move);
	static void inflict_damage(Battle_Pokemon& bp, const Attack_Move& move);
	static const Move& retrieve_move_from_pokemon_movelist(Battle_Pokemon& bp, int m);
	static bool is_valid_move_choice(int choice);
	static bool is_NULL_MOVE(const Move& move);
	static void DEBUG_SET_USER(Gen1_Pokemon);
	static void DEBUG_SET_ENEMY(Gen1_Pokemon);
	static std::array<Battle_Pokemon*, 2> DEBUG_get_turn_order();
	static bool stun_check(Battle_Pokemon& current);
	static void start_battle();
	static void apply_post_stun(Battle_Pokemon& current);
	//this should be in BP
	static bool is_stunned(Battle_Pokemon& current);
	static bool is_status_effect_a_stun(Battle_Pokemon& current);
	static bool calculate_if_stunned(Battle_Pokemon& current);
	static std::string get_stun_message(Battle_Pokemon& current);
	static void show_stun_message(std::string);
	static std::string normal_stun_message(Battle_Pokemon& current);
	static std::string freeze_stun_message(Battle_Pokemon& current);
	static std::string paralysis_stun_message(Battle_Pokemon& current);
	static std::string sleep_stun_message(Battle_Pokemon& current);
	static void speed_check();
	static std::vector<Battle_Pokemon*>get_targets(const Move& move);
	static void apply_damage(std::vector < Battle_Pokemon*>targets, const Move& move);
	Battle_Event();
	static void select_pokemon_to_battle();
	static void turn(Battle_Pokemon* current, Battle_Pokemon* opposing);
	static void ai_turn(Battle_Pokemon& current);
	static void human_turn(Battle_Pokemon& current);
	static int compare_speeds();
	static void assign_turn_order(int);
	static void random_turn_order();
	static void select_user_pokemon();
	static void select_enemy_pokemon();
	static void battle();
	static int random_power();
};