#include "Move.h"
#include <string>

using namespace status_and_stats;

Move::Move() {};

Move::Move(std::string name, int pp, int accuracy, Type_Data& type) : m_name(name), m_pp(pp), m_accuracy(accuracy), m_type(&type) {
	m_name = name;
	m_pp = pp;
	m_accuracy = accuracy;
	m_type = &type;
}

std::string Move::get_move_name() const
{
	return m_name;
}

bool Move::get_is_target_enemy()const {
	return is_target_enemy;
}

bool Move::get_is_target_self()const {
	return is_target_self;
}

Attack_Move::Attack_Move(std::string name, int pp, int accuracy, Type_Data& type, int power):Move(name,pp,accuracy,type),m_power(power){
	m_power = power;
}

void Attack_Move::show_move_values()const {
	printf("Move: %s\nType: %s\nPP: %d\nAccuracy: %d\nPower: %d\n", m_name.c_str(), m_type->get_type_name().c_str() , m_pp, m_accuracy, m_power);
	std::cout << std::endl;
}

int Attack_Move::get_power()const { 
	return m_power; 
}

Type_Data* Move::get_type() const {
	return m_type;
}


Status_Effect_Attack_Move::Status_Effect_Attack_Move(std::string name, int pp, int accuracy, Type_Data& type, int power, Status_Effect_Change& stats_effect, int status_effect_chance) :Attack_Move(name, pp, accuracy, type, power), m_status_effect_change(&stats_effect), m_status_effect_chance(status_effect_chance){
	is_status_inflicting = true;
	m_status_effect_change = &stats_effect;
	m_status_effect_chance = status_effect_chance;
}

void Status_Effect_Attack_Move::show_move_values()const {
	std::cout << "Move: " << m_name << std::endl;
	std::cout << "Type: " << m_type->get_type_name() << std::endl;
	std::cout << "PP " << m_pp << std::endl;
	std::cout << "Accuracy " << m_accuracy << std::endl;
	std::cout << "Power: " << m_power << std::endl;
	std::cout << "Status effect: " << m_status_effect_change->get_status_effect_name() << std::endl;
	std::cout << "Chance: " << m_status_effect_chance << std::endl;
	std::cout << std::endl;
}

Stats_Value_Attack_Move::Stats_Value_Attack_Move(std::string name, int pp, int accuracy, Type_Data& type, int power, Stats_Change stats_change) :Attack_Move(name, pp, accuracy, type, power), m_stats_change(stats_change) {
	is_stats_changing = true;
	m_stats_change = stats_change;
}

void Stats_Value_Attack_Move::show_move_values()const {
	std::cout << "Move: " << m_name << std::endl;
	std::cout << "Type: " << m_type->get_type_name() << std::endl;
	std::cout << "PP " << m_pp << std::endl;
	std::cout << "Accuracy " << m_accuracy << std::endl;
	std::cout << "Power: " << m_power << std::endl;
	std::cout << "Stats change: " << m_stats_change.get_stats_value_name()<< std::endl;
	std::cout << "Stages changed: " << m_stats_change.get_stats_stages() << std::endl;
	std::cout << std::endl;
}

Defence_Move::Defence_Move(std::string name, int pp, int accuracy, Type_Data& type, Stats_Change stats) : Move(name, pp, accuracy, type), m_stats_change(stats) {
	is_target_enemy = false;
	is_stats_changing = true;
	m_stats_change = stats;
}

void Defence_Move::show_move_values()const {
	std::cout << "Move: " << m_name << std::endl;
	std::cout << "Type: " << m_type->get_type_name() << std::endl;
	std::cout << "PP " << m_pp << std::endl;
	std::cout << "Accuracy " << m_accuracy << std::endl;
	std::cout << "Stats change: " << m_stats_change.get_stats_value_name()<< std::endl;
	std::cout << "Stages changed: " << m_stats_change.get_stats_stages() << std::endl;
	std::cout << std::endl;
}

bool Move::operator==(const Move& other)const {
	if (this == &other)
		return true;
	else
		return false;
}