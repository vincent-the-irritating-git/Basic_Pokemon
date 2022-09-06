#pragma once
#include "Pokemon Names.h"
#include "Pokemon.h"
#include "Pokemon_Pokedex.h"

//we will need two classes, one for each
class Battle_Pokemon
	//here we have stat modifiers to track how stats have changed
	//when we do the calculation we do (reference_stat*modifier),
	//this will be calculated using both of these and returned in a method, which
	//is what the damage calculation uses
{
private:
	Status_Effect_Change* m_status_effect = &status_effect::NORMAL;
	const Gen1_Pokemon* pokemon_ptr = nullptr;
	int attack_modifier = 1;
	int defence_modifier = 1;
	int speed_modifier = 1;
	int special_modifier = 1;
	int hp=1;
	int critical_hit_ratio = 1;
	int m_stun_chance = 0;
	int sleep_counter=0;
	bool is_human = true;
public:
	std::string get_battle_pokemon_name();
	void DEBUG_set_status_effect(Status_Effect_Change&);
	Battle_Pokemon();
	~Battle_Pokemon();
	Battle_Pokemon(const Gen1_Pokemon&);
	int modified_attack()const;
	int modified_defence()const;
	int modified_speed()const;
	int modified_special()const;
	int modified_critical()const;
	void show_battle_stats()const;
	bool get_is_human() const;
	void set_ai();
	double get_stun_chance();
	Status_Effect_Change& get_status_effect();
	void decrement_sleep_counter();
};

