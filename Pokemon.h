#pragma once
#include <iostream>
#include <array>
#include "Type.h"
#include "Stats_n_Status.h"

class Pokemon {
public:
	//where the pokemon's evolutions and levels they evolve at are held
	struct Evolutions {
		//where the pokemon's evolutions are held and what level they evolve to them at
	public:
		int m_evolution_index_no = 0;
		int m_evolution_level = 0;
	public:
		Evolutions(int m_evolution_index_no, int m_evolution_level);
		Evolutions();
	};
	//member variables for Pokemon class
protected:
	int m_index_no = -1;
	std::string m_name = "";
	Type_Data* m_type = &Type::NONE;
	Type_Data* m_type2 = &Type::NONE;
	Evolutions m_evolution;
public:
	Pokemon();
	/*constructor*/
	Pokemon(int index_no, std::string name, Type_Data& type, Type_Data& type2, Evolutions evolutions);
	//methods
	std::string get_pokemon_name() const;
	Type_Data& get_type1() const;
	Type_Data& get_type2() const;
	void show_base_stats() const;
};

//gen1 Pokemon
class Gen1_Pokemon : public Pokemon {
public:
	//where the pokemon stats are held
	struct Gen1_Stats {
		friend class Gen1_Pokemon;
	public:
		Gen1_Stats();
		Gen1_Stats(int hp, int attack, int defence, int special, int speed);
	private:
		std::unordered_map<status_and_stats::stats_value, int>pokemon_stats{
			{status_and_stats::stats_value::HP,0},
			{status_and_stats::stats_value::ATTACK,0},
			{status_and_stats::stats_value::DEFENCE,0},
			{status_and_stats::stats_value::SPEED,0},
			{status_and_stats::stats_value::SPECIAL,0},
		};
	};
protected:
	Gen1_Stats m_stats;
public:
	Gen1_Pokemon();
	Gen1_Pokemon(int index_no, std::string name, Type_Data& type, Type_Data& type2, Evolutions evolutions, Gen1_Stats stats);
	std::unordered_map<status_and_stats::stats_value, int>get_m_stats()const;
	void show_gen1_pokemon_stats()const;
	bool operator==(const Gen1_Pokemon&)const;
};

//gen2 Pokemon
class Gen2_Pokemon : public Pokemon {
public:
	//where the pokemon stats are held
	struct Gen2_Stats {
		friend class Gen2_Pokemon;
	public:
		Gen2_Stats();
		Gen2_Stats(int hp, int attack, int defence, int special_attack, int special_defence, int speed);
	private:
		std::unordered_map<status_and_stats::stats_value, int>pokemon_stats{ 
			{status_and_stats::stats_value::HP,0},
			{status_and_stats::stats_value::ATTACK,0},
			{status_and_stats::stats_value::DEFENCE,0},
			{status_and_stats::stats_value::SPEED,0},
			{status_and_stats::stats_value::SPECIAL_ATTACK,0},
			{status_and_stats::stats_value::SPECIAL_DEFENCE,0},
			{status_and_stats::stats_value::CRITICAL_HIT_RATIO,0}
		};
	};
protected:
	Gen2_Stats m_stats;
public:
	//constructors
	Gen2_Pokemon();
	Gen2_Pokemon(int index_no, std::string name, Type_Data& type, Type_Data& type2, Evolutions evolutions, Gen2_Stats stats);
	//TODO these need doing
	std::unordered_map<status_and_stats::stats_value, int>get_stats_map();
	void show_gen2_Pokemon_stats();
};