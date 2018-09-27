#include "PokemonBattle.h"

PokemonBattle::PokemonBattle() {}

void PokemonBattle::PokemonDamage(double damage, Pokemon* pokemon) {

	damage = ((((2 * pokemon->GetLevel() / 5 + 2) * pokemon->GetSpecAttack() * pokemon->GetBaseAttack() / pokemon->GetDefense()) / 50 + 2) * mod);
	pokemon->SetHP(pokemon->GetHp() - damage);
}

void PokemonBattle::PokemonSTAB(float stab, Pokemon* pokemon) {
	
	stab = (pokemon->GetBaseAttack() * .50f) + pokemon->GetBaseAttack();
	pokemon->SetHP(pokemon->GetHp() - stab);

}

void PokemonBattle::PokemonMovePriority(Pokemon* player, Pokemon* enemy) {
	
	
	if (player->GetSpeed() > enemy->GetSpeed()) {
		//player gets to attack first
	}
	else {
		//opponent gets to attack first
	}
}

void PokemonBattle::PokemonOHKO(Pokemon* player, Pokemon* enemy) {
	//needs two types to compare speed
	

}

void PokemonBattle::PokemonResistance(Pokemon* player, Pokemon* enemy) {
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

void PokemonBattle::Substitute(float subs, Pokemon* player, Pokemon* enemy) {
	subs = player->GetMaxHp() * .25f;

	if (subs > player->GetHp()) {
		//substitute will fail
	}
	else if (subs == player->GetHp()) {
		//pokemon will faint
	}
	else if (subs < 3) {
		
	}
}
