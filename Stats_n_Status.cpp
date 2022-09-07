#include "Stats_n_Status.h"

using namespace status_and_stats;

namespace {
	namespace status_effects {
		Status_Effect_Change NORMAL(status_and_stats::status_effect_value::NORMAL);
		Damage_Status_Effect BURN(status_effect_value::BURN, { Stats_Change(stats_value::HP,6.25f) }, {Stats_Change(stats_value::ATTACK,0.5f)});
		Damage_Status_Effect POISON(status_effect_value::POISON, Stats_Change(stats_value::HP, 6.25f));
		Stun_Status_Effect PARALYSIS(status_effect_value::PARALYSIS, stats_value::SPEED, 25);
		Stun_Status_Effect FREEZE(status_effect_value::FREEZE, 100);
		Stun_Status_Effect SLEEP(status_effect_value::SLEEP, 100, 1, 7);
		//Now we do the miscellaneous ones like rest and toxic
		Stun_Status_Effect REST(status_effect_value::SLEEP, 100, 2, 2);
	}

	namespace stat_names {
		std::unordered_map<stats_value, std::string> stat_names{
			{ stats_value::ATTACK, "ATTACK"},
			{ stats_value::CRITICAL_HIT_RATIO, "CRITICAL HIT RATIO" },
			{ stats_value::DEFENCE, "DEFENCE" },
			{ stats_value::HP, "HP" },
			{ stats_value::SPECIAL, "SPECIAL" },
			{ stats_value::SPECIAL_ATTACK, "SPECIAL ATTACK" },
			{ stats_value::SPECIAL_DEFENCE, "SPECIAL DEFENCE" },
			{ stats_value::SPEED, "SPEED" },
			{stats_value::ACCURACY, "ACCURACY"},
			{stats_value::EVASION, "EVASION"}
		};
	}

		namespace status_effect_names {
			std::unordered_map<status_effect_value, std::string> status_effect_names{
			{ status_effect_value::BURN, "BURN"},
			{ status_effect_value::FREEZE, "FREEZE" },
			{ status_effect_value::NORMAL, "NORMAL" },
			{ status_effect_value::PARALYSIS, "PARALYSIS" },
			{ status_effect_value::POISON, "POISON" },
			{ status_effect_value::SLEEP, "SLEEP" },
			};
		}
}

Status_Effect_Change& status_effect::NORMAL = status_effects::NORMAL;
Status_Effect_Change& status_effect::BURN = status_effects::BURN;
Status_Effect_Change& status_effect::POISON = status_effects::POISON;
Status_Effect_Change& status_effect::PARALYSIS = status_effects::PARALYSIS;
Status_Effect_Change& status_effect::FREEZE = status_effects::FREEZE;
Status_Effect_Change& status_effect::SLEEP = status_effects::SLEEP;
Status_Effect_Change& status_effect::REST = status_effects::REST;

int Status_Effect_Change::get_stun()const {
	return-1;
}

int Status_Effect_Change::get_lower_limit() const {
	return-1;
}

int Status_Effect_Change::get_upper_limit()const {
	return -1;
}

Stats_Change Status_Effect_Change::get_stats_change()const {
	return Stats_Change();
}

Stats_Change Status_Effect_Change::get_stats_change2()const
{
	return Stats_Change();
}

Status_Effect_Change::Status_Effect_Change(status_effect_value status) :m_status_effect(status){
	m_status_effect = status;
}

Stun_Status_Effect::Stun_Status_Effect(status_and_stats::status_effect_value status_effect, int stun): Status_Effect_Change(status_effect), m_stun(stun) {
	m_stun = stun;
}

Stun_Status_Effect::Stun_Status_Effect(status_and_stats::status_effect_value status_effect, int stun, int lower_limit, int upper_limit): Status_Effect_Change(status_effect), m_stun(stun), m_lower_limit(lower_limit), m_upper_limit(upper_limit) {
	m_stun = stun;
	m_lower_limit = lower_limit;
	m_upper_limit = upper_limit;
}

Stun_Status_Effect::Stun_Status_Effect(status_and_stats::status_effect_value status_effect, status_and_stats::stats_value stats_value, int stun) : Status_Effect_Change(status_effect), m_stat(stats_value), m_stun(stun){
	m_stat = stats_value;
	m_stun = stun;
}

int Stun_Status_Effect::get_stun()const
{
	return m_stun;
}

int Stun_Status_Effect::get_lower_limit()const {
	return m_lower_limit;
}

int Stun_Status_Effect::get_upper_limit()const {
	return m_upper_limit;
}

Damage_Status_Effect::Damage_Status_Effect(status_and_stats::status_effect_value status_effect, Stats_Change stat):Status_Effect_Change(status_effect), m_stats(stat){
	m_stats = stat;
}

Damage_Status_Effect::Damage_Status_Effect(status_and_stats::status_effect_value status_effect, Stats_Change stat, Stats_Change stat2): Status_Effect_Change(status_effect),m_stats(stat),m_stat2(stat2){
	m_stats = stat;
	m_stat2 = stat2;
}

Stats_Change Damage_Status_Effect::get_stats_change()const {
	return m_stats;
}

Stats_Change Damage_Status_Effect::get_stats_change2()const {
	return m_stat2;
}

Stats_Change::Stats_Change(stats_value status, float stages_or_per_cent) : m_stats_value(status), m_stages_or_per_cent(stages_or_per_cent)
{
	m_stats_value = status;
	m_stages_or_per_cent = stages_or_per_cent;
}

Stats_Change::Stats_Change() {};

float Stats_Change::get_stats_stages()const
{
	return m_stages_or_per_cent;
}

stats_value Stats_Change::get_stats_value()const
{
	return m_stats_value;
}

std::string Stats_Change::get_stats_value_name()const
{
	try {
		return stat_names::stat_names.at(this->m_stats_value);
	}
	catch (std::exception e) {
		e.what();
		std::cout << std::endl << "No stat name found.";
	}
}

std::string Status_Effect_Change::get_status_effect_name()const
{
	try {
		return status_effect_names::status_effect_names.at(this->m_status_effect);
	}
	catch (std::exception e) {
		e.what();
		std::cout << std::endl << "No status name found.";
	}
}