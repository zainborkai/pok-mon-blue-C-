
#include "Pokemon.h"


void Pokemon::PokemonDamage(double damage, Pokemon* pokemon) {

	// damage = ((((2 * pokemon->GetLevel() / 5 + 2) * pokemon->GetSpecAttack() * pokemon->GetBaseAttack() / pokemon->GetDefense()) / 50 + 2) * mod);
	// pokemon->SetHP(pokemon->GetHp() - damage);
}

void Pokemon::PokemonSTAB(float stab, Pokemon* pokemon) {

	// stab = (pokemon->GetBaseAttack() * .50f) + pokemon->GetBaseAttack();
	// pokemon->SetHP(pokemon->GetHp() - stab);

}

void Pokemon::PokemonMovePriority(Pokemon* player, Pokemon* enemy) {


	if (player->GetSpd() > enemy->GetSpd()) {
		//player gets to attack first
	}
	else {
		//opponent gets to attack first
	}
}

void Pokemon::PokemonOHKO(Pokemon* player, Pokemon* enemy) {
	//needs two types to compare speed


}

void Pokemon::PokemonResistance(Pokemon* player, Pokemon* enemy) {
	/*
	if (pokeResist[player->GetPokeType()][enemy->GetPokeType()] == "0.5") {
		mod = 0.5f;
	}else if (pokeResist[player->GetPokeType()][enemy->GetPokeType()] == "1") {
		mod = 1;
	}else if (pokeResist[player->GetPokeType()][enemy->GetPokeType()] == "2") {
		mod = 2;
	}
	else
	{
		mod = 0;
	}
	 */

}

void Pokemon::Substitute(float subs, Pokemon* player, Pokemon* enemy) {
	/*
	subs = player->GetMaxHp() * .25f;

	if (subs > player->GetHp()) {
		//substitute will fail
	}
	else if (subs == player->GetHp()) {
		//pokemon will faint
	}
	else if (subs < 3) {

	}
	*/
}
