#include "Battle_Event.h"

using namespace status_and_stats;
using namespace Pokemon_names;

Battle_Event::Battle_Event() {

}

bool Battle_Event::isFainted = false;
Battle_Pokemon Battle_Event::user;
Battle_Pokemon Battle_Event::ai;
Battle_Pokemon* Battle_Event::current;
Battle_Pokemon* Battle_Event::opposing;
std::array<Battle_Pokemon*, 2> Battle_Event::turn_order;

void Battle_Event::start_battle() {
	//gen_selection(){};
// gen_selection will return a map
//pass the map from gen_selection to select_pokemon_to_battle etc
	select_pokemon_to_battle();
	while (!isFainted) {
		speed_check();
		turn(turn_order[0], turn_order[1]);
		turn(turn_order[1], turn_order[0]);
	}
}

void Battle_Event::DEBUG_SET_USER(Gen1_Pokemon b){
	user = Battle_Pokemon(b);
}

void Battle_Event::DEBUG_SET_ENEMY(Gen1_Pokemon b) {
	ai = Battle_Pokemon(b);
	ai.set_ai();
}

std::array<Battle_Pokemon*,2> Battle_Event::DEBUG_get_turn_order() {
	return turn_order;
}

void Battle_Event::speed_check() {
	assign_turn_order(compare_speeds());
}

void Battle_Event::random_turn_order() {
	int random_number = rand() % 2;
	if (random_number == 0)
		turn_order[0] = &user, turn_order[1] = &ai;
	else
		turn_order[1] = &user, turn_order[0] = &ai;
}

int Battle_Event::compare_speeds() {
	if (user.modified_speed() > ai.modified_speed())
		return 1;
	if (user.modified_speed() < ai.modified_speed())
		return -1;
	if (user.modified_speed() == ai.modified_speed())
		return 0;
	return 99;
}

void Battle_Event::assign_turn_order(int i) {
	if (i == 1)
		turn_order[0] = &user, turn_order[1] = &ai;
	if (i == -1)
		turn_order[1] = &user, turn_order[0] = &ai;
	if (i == 0)
		random_turn_order();
}

//TODO this should be two functions
void Battle_Event::turn(Battle_Pokemon* current, Battle_Pokemon* opposing) {
	Battle_Event::current = current;
	Battle_Event::opposing = opposing;
	if (current->get_is_human())
		human_turn(*current);
	else
		ai_turn(*current);
	//display_moves();
	//select_move();
}

void Battle_Event::human_turn(Battle_Pokemon& bp) {
	display_moves(bp);
	int user_move_choice = select_move(bp);
	const Move& chosen_move = retrieve_move_from_map(bp, user_move_choice);
	if (Battle_Event::stun_check(bp)) {
		//show_stun_message();
		Battle_Event::apply_post_stun(bp);
		return;
	}
	//break()
	//determine_move_class(chosen_move);
	//check_fainted();
	//apply_post_turn_effects();
}

const Move& Battle_Event::retrieve_move_from_map(Battle_Pokemon& bp, int m) {
	std::string name = bp.get_battle_pokemon_name();
	const Move& move = *(Move_Pokedex::get_gen1_default_movesets(name).at(m));
	if (!is_NULL_MOVE(move))
		return *(Move_Pokedex::get_gen1_default_movesets(name).at(m));
	else 
		select_move(bp);
}

void Battle_Event::ai_turn(Battle_Pokemon& bp) {

}

void Battle_Event::do_move(Battle_Pokemon& bp, const Move& chosen_move) {
	//inflict_status_effect();
	//inflict_stats_change();
}

void Battle_Event::inflict_damage(Battle_Pokemon& bp, const Attack_Move& move) {
	//int damage = (move->m_power * bp->modified_attack() / defending.defence) / 50 + 2 * critical() * random() * STAB * type * burn;
}

//TODO we're only couting pointer address
void Battle_Event::display_moves(Battle_Pokemon& bp) {
	std::string name = bp.get_battle_pokemon_name();
	const int MAKE_ARRRAY_HUMAN_READABLE = 1;
	for (int x = 0; x < Move_constants::MAX_MOVES; ++x)
		std::cout << x + MAKE_ARRRAY_HUMAN_READABLE << ": " << Move_Pokedex::get_gen1_default_movesets(name).at(x)->m_name << std::endl;
}

int Battle_Event::select_move(Battle_Pokemon& bp)
{
	int choice;
	const int MAKE_ARRAY_ORDERING_HUMAN_READABLE = -1;
	//TODO probably needs try catch stuff
	std::cin >> choice;
	if (is_valid_move_choice(choice))
		return choice + MAKE_ARRAY_ORDERING_HUMAN_READABLE;
	else
		select_move(bp);
}

bool Battle_Event::is_valid_move_choice(int choice) {
	std::regex r("[1-4]+");
	std::string string_choice = std::to_string(choice);
	return std::regex_match(string_choice, r);
}

bool Battle_Event::is_NULL_MOVE(const Move& move) {
	if (move.m_name == " ")
		return true;
	return false;
}

bool Battle_Event::stun_check(Battle_Pokemon& bp) {
	if (Battle_Event::is_status_effect_a_stun(bp))
		return Battle_Event::calculate_if_stunned(bp);
}

void Battle_Event::apply_post_stun(Battle_Pokemon& bp) {
	if (bp.get_status_effect().get_status_effect_name() == status_effect::SLEEP.get_status_effect_name())
		bp.decrement_sleep_counter();
}

bool Battle_Event::is_stunned(Battle_Pokemon& bp) {
	return calculate_if_stunned(bp);
}

bool Battle_Event::is_status_effect_a_stun(Battle_Pokemon& bp) {
	if (&bp.get_status_effect() == &status_effect::FREEZE)
		return true;
	if (&bp.get_status_effect() == &status_effect::PARALYSIS)
		return true;
	if (&bp.get_status_effect() == &status_effect::SLEEP)
		return true;
	return false;
}

bool Battle_Event::calculate_if_stunned(Battle_Pokemon& bp) {
	int lower_limit = 1;
	int max_limit = 100;
	int chance = rand() % max_limit + lower_limit;
	if (chance <= bp.get_stun_chance())
		return true;
	return false;
}

void Battle_Event::show_stun_message(std::string message) {
	std::cout << message;
}

std::string Battle_Event::get_stun_message(Battle_Pokemon& bp) {
	//TODO this needs redoing
	return "what raging fire shall flood the soul?";
}

std::string Battle_Event::normal_stun_message(Battle_Pokemon& current) {
	return current.get_battle_pokemon_name() + " " + "is fine!\n";
}
std::string Battle_Event::freeze_stun_message(Battle_Pokemon& current) {
	return current.get_battle_pokemon_name()+" "+"is frozen!\n";
}
std::string Battle_Event::paralysis_stun_message(Battle_Pokemon& current) {
	return current.get_battle_pokemon_name() + " " + "is paralysed!\n";
}
std::string Battle_Event::sleep_stun_message(Battle_Pokemon& current) {
	return current.get_battle_pokemon_name() + " " + "is sleeping!\n";
}

void Battle_Event::select_pokemon_to_battle() {
	select_user_pokemon();
	select_enemy_pokemon();
}

void Battle_Event::select_user_pokemon()
{
	std::cout << "Select user's pokemon: ";
	std::string choice;
	std::cin >> choice;
	if (!Pokemon_Pokedex::is_pokemon_in_map(choice)) {
		select_user_pokemon();
		return;
	}
	const Gen1_Pokemon& pokemon = Pokemon_Pokedex::get_gen1_pokemon(choice);
	user = Battle_Pokemon(pokemon);
}

void Battle_Event::select_enemy_pokemon()
{
	std::cout << "Select enemy's pokemon: ";
	std::string choice;
	std::cin >> choice;
	if (!Pokemon_Pokedex::is_pokemon_in_map(choice)) {
		select_enemy_pokemon();
		return;
	}
	const Gen1_Pokemon pokemon = (Pokemon_Pokedex::get_gen1_pokemon(choice));
	ai = Battle_Pokemon(pokemon);
	ai.set_ai();
}

void Battle_Event::battle() {

}