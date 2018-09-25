#include "PokemonBattle.h"

PokemonBattle::PokemonBattle() {
	pokemonAttack.open("PokemonBlueAttackDatabase.csv");

	while (!pokemonAttack.eof()) {
		std::string temp;
		getline(pokemonAttack, temp, ',');
		pokeBattle.push_back(temp);
		std::cout << temp;
	}

	pokemonAttack.close();
}

void PokemonBattle::PokemonDamage(double damage) {
	damage = ((((2 * level / 5 + 2) * specAttack * baseATK / defense) / 50 + 2) * mod);
}

void PokemonBattle::PokemonSTAB(float stab) {
	stab = (baseATK * .50f) + baseATK;

}

void PokemonBattle::PokemonMovePriority() {

}

void PokemonBattle::PokemonOHKO() {

}

void PokemonBattle::PokemonResistance() {


}

void PokemonBattle::Substitute(float subs) {
	subs = maxHP * .25f;

	if (subs > maxHP) {

	}
}
