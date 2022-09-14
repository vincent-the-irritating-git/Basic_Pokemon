#include "Battle_Pokemon.h"

using namespace status_and_stats;

Battle_Pokemon::Battle_Pokemon() {

}

Battle_Pokemon::~Battle_Pokemon()
{
	//TODO makes test fail
	//delete pokemon_ptr;
}

Battle_Pokemon::Battle_Pokemon(const Gen1_Pokemon& pokemon) {
	pokemon_ptr = &(Pokemon_Pokedex::get_gen1_pokemon(pokemon.get_pokemon_name()));
	hp = pokemon_ptr->get_m_stats().at(stats_value::HP);
}

std::unordered_map<status_and_stats::stats_value, int> Battle_Pokemon::stats_modifiers{
	{stats_value::ATTACK, 1},
	{stats_value::DEFENCE, 1},
	{stats_value::SPEED, 1},
	{stats_value::SPECIAL, 1},
	//TODO these need to be calibrated later
	{stats_value::CRITICAL_HIT_RATIO, 1},
	{stats_value::ACCURACY, 1},
	{stats_value::EVASION, 1}
};

std::string Battle_Pokemon::get_battle_pokemon_name()
{
	return pokemon_ptr->get_pokemon_name();
}

void Battle_Pokemon::DEBUG_set_status_effect(Status_Effect_Change& sv){
	m_status_effect = &sv;
}

int Battle_Pokemon::modified_attack()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::ATTACK) * Battle_Pokemon::stats_modifiers.at(stats_value::ATTACK);
}

int Battle_Pokemon::modified_defence()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::DEFENCE) * Battle_Pokemon::stats_modifiers.at(stats_value::DEFENCE);
}

int Battle_Pokemon::modified_speed()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::SPEED)* Battle_Pokemon::stats_modifiers.at(stats_value::SPEED);
}

int Battle_Pokemon::modified_special()const
{
	return pokemon_ptr->get_m_stats().at(stats_value::SPECIAL)* Battle_Pokemon::stats_modifiers.at(stats_value::SPECIAL);
}

int Battle_Pokemon::modified_critical()const {
	return 1 * Battle_Pokemon::stats_modifiers.at(stats_value::CRITICAL_HIT_RATIO);
}

int Battle_Pokemon::modified_accuracy()const {
	return 1 * Battle_Pokemon::stats_modifiers.at(stats_value::ACCURACY);
}

int Battle_Pokemon::modified_evasion()const {
	return 1 * Battle_Pokemon::stats_modifiers.at(stats_value::EVASION);
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
	std::cout << "Critical hit ratio is " << modified_critical() << std::endl;
	std::cout << "Accuracy is " << modified_accuracy() << std::endl;
	std::cout << "Evasion is " << modified_evasion() << std::endl;
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
	this->sleep_counter;
}

void Battle_Pokemon::reset_all_stats()
{
	for (auto m : Battle_Pokemon::stats_modifiers)
		m.second = 0;
}