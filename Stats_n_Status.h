#pragma once
#include <iostream>
#include <array>
#include <unordered_map>

namespace status_and_stats {
	enum class status_effect_value {
		NORMAL, PARALYSIS, BURN, POISON, FREEZE, SLEEP
	};

	enum class stats_value {
		HP, ATTACK, DEFENCE, SPEED, SPECIAL, SPECIAL_ATTACK, SPECIAL_DEFENCE, CRITICAL_HIT_RATIO, ACCURACY, EVASION
	};
}

struct Stats_Change {
private:
	status_and_stats::stats_value m_stats_value = status_and_stats::stats_value::CRITICAL_HIT_RATIO;
	float m_stages_or_per_cent = 0.00f;
public:
	Stats_Change(status_and_stats::stats_value, float);
	Stats_Change();
	float get_stats_stages()const;
	status_and_stats::stats_value get_stats_value()const;
	std::string get_stats_value_name()const;
};

struct Status_Effect_Change {
private:
	status_and_stats::status_effect_value m_status_effect = status_and_stats::status_effect_value::NORMAL;
public:
	Status_Effect_Change(status_and_stats::status_effect_value status_effect);
	std::string get_status_effect_name()const;
	virtual int get_stun()const;
	virtual int get_lower_limit()const;
	virtual int get_upper_limit()const;
	virtual Stats_Change get_stats_change()const;
	virtual Stats_Change get_stats_change2()const;
};

struct Stun_Status_Effect :Status_Effect_Change {
private:
	int m_stun=-1;
	int m_lower_limit = -1;
	int m_upper_limit = -1;
	status_and_stats::stats_value m_stat=status_and_stats::stats_value::ATTACK;
public:
	Stun_Status_Effect(status_and_stats::status_effect_value status_effect, int stun);
	Stun_Status_Effect(status_and_stats::status_effect_value status_effect, int stun, int lower_limit, int upper_limit);
	Stun_Status_Effect(status_and_stats::status_effect_value status_effect, status_and_stats::stats_value stats, int stun);
	virtual int get_stun()const override;
	virtual int get_lower_limit()const override;
	virtual int get_upper_limit()const override;
};

struct Damage_Status_Effect :Status_Effect_Change {
private:
	Stats_Change m_stats;
	Stats_Change m_stat2;
public:
	Damage_Status_Effect(status_and_stats::status_effect_value status_effect, Stats_Change stat);
	Damage_Status_Effect(status_and_stats::status_effect_value status_effect, Stats_Change stat, Stats_Change stat2);
	virtual Stats_Change get_stats_change()const override;
	virtual Stats_Change get_stats_change2()const override;
};

namespace status_effect {
	extern Status_Effect_Change& NORMAL;
	extern Status_Effect_Change& FREEZE;
	extern Status_Effect_Change& PARALYSIS;
	extern Status_Effect_Change& BURN;
	extern Status_Effect_Change& POISON;
	extern Status_Effect_Change& SLEEP;
	extern Status_Effect_Change& REST;
}