#include "Battle_Event.h"
using namespace status_and_stats;

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
	srand(time(NULL));
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
	const Move& chosen_move = retrieve_move_from_pokemon_movelist(bp, user_move_choice);
	if (Battle_Event::stun_check(bp)) {
		show_stun_message(NULL);
		Battle_Event::apply_post_stun(bp);
		return;
	}
	//determine_move_class(chosen_move);
	//check_fainted();
	//apply_post_turn_effects();
}

const Move& Battle_Event::retrieve_move_from_pokemon_movelist(Battle_Pokemon& bp, int m) {
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
	//inflict damage
	//inflict_status_effect();
	//inflict_stats_change();
}

void Battle_Event::display_moves(Battle_Pokemon& bp) {
	std::string name = bp.get_battle_pokemon_name();
	const int MAKE_ARRAY_HUMAN_READABLE = 1;
	for (int x = 0; x < MAX_MOVES; ++x)
		std::cout << x + MAKE_ARRAY_HUMAN_READABLE << ": " << Move_Pokedex::get_gen1_default_movesets(name).at(x)->get_move_name() << std::endl;
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
	if (move.get_move_name() == NULL_MOVE)
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
	srand(time(NULL));
	const int LOWER_LIMIT = 1;
	const int MAX_LIMIT = 100;
	int chance = rand() % (MAX_LIMIT + 1 - LOWER_LIMIT) + LOWER_LIMIT;
	if (chance <= bp.get_stun_chance())
		return true;
	return false;
}

void Battle_Event::show_stun_message(std::string message) {
	std::cout << message;
}

std::string Battle_Event::get_stun_message(Battle_Pokemon& bp) {
	//TODO this needs redoing
	return "Stunned!";
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

std::vector<Battle_Pokemon*> Battle_Event::get_targets(const Move& move)
{
	std::vector<Battle_Pokemon*>targets;
	//enemy
	if (move.get_is_target_enemy())
		targets.push_back(Battle_Event::opposing);
	//self
	if (move.get_is_target_self())
		targets.push_back(Battle_Event::current);
	//both
	return targets;
}

int Battle_Event::random_power() {
	srand(time(NULL));
	const int LOWER_LIMIT = 75;
	const int MAX_LIMIT = 100;
	int chance = rand() % (MAX_LIMIT + 1 - LOWER_LIMIT) + LOWER_LIMIT;
	return chance;
}

void Battle_Event::apply_damage(std::vector<Battle_Pokemon*> targets, const Move& move)
{
	for (int x = 0; x < targets.size(); ++x)
		int damage = (move.get_power() * Battle_Event::current->modified_attack() / Battle_Event::opposing->modified_defence())
		/ 50 + 2 * Battle_Event::current->modified_critical() * random_power() * /*/STAB /*/move.get_type()->get_matchup_value(targets[x]->get_pokemon()->get_type1().get_type()).get_effectiveness();//* burn();
}

void Battle_Event::battle() {

}