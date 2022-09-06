#include "Battle_Pokemon.h"

using namespace status_and_stats;

Battle_Pokemon::Battle_Pokemon() {

}

Battle_Pokemon::~Battle_Pokemon()
{
	//TODO makes test fail
	//delete pokemon_ptr;
}

//TODO finish copying all stats in
Battle_Pokemon::Battle_Pokemon(const Gen1_Pokemon& pokemon) {
	pokemon_ptr = &(Pokemon_Pokedex::get_gen1_pokemon(pokemon.get_pokemon_name()));
	hp = pokemon_ptr->get_m_stats().at(stats_value::HP);

}

std::string Battle_Pokemon::get_battle_pokemon_name()
{
	return pokemon_ptr->get_pokemon_name();
}

void Battle_Pokemon::DEBUG_set_status_effect(Status_Effect_Change& sv){
	m_status_effect = &sv;
}

int Battle_Pokemon::modified_attack()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::ATTACK) * attack_modifier;
}

int Battle_Pokemon::modified_defence()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::DEFENCE) * defence_modifier;
}

int Battle_Pokemon::modified_speed()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::SPEED)* speed_modifier;
}

int Battle_Pokemon::modified_special()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::SPECIAL)* special_modifier;
}

int Battle_Pokemon::modified_critical()const {
	return pokemon_ptr->get_m_stats().at(stats_value::CRITICAL_HIT_RATIO) * critical_hit_ratio;
}

double Battle_Pokemon::get_stun_chance()
{
	return m_stun_chance;
}

Status_Effect_Change& Battle_Pokemon::get_status_effect()
{
	return *m_status_effect;
}

void Battle_Pokemon::show_battle_stats()const
{
	std::cout << "HP is " << hp << std::endl;
	std::cout << "Attack is "<< modified_attack()<<std::endl;
	std::cout << "Defence is " << modified_defence() << std::endl;
	std::cout << "Speed is " << modified_speed() << std::endl;
	std::cout << "Special is " << modified_special() << std::endl;
	std::cout << "Critical hit ratio is " << critical_hit_ratio << std::endl;
	std::cout << std::endl;
}

bool Battle_Pokemon::get_is_human() const
{
	return is_human;
}

void Battle_Pokemon::set_ai()
{
	is_human = false;
}

void Battle_Pokemon::decrement_sleep_counter() {
	--this->sleep_counter;
}
