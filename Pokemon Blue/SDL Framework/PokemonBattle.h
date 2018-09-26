#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include "Pokemon.h"


class PokemonBattle {
private:

	std::ifstream pokemonAttack;
	std::string pokeResist[14][14];

protected:
	//variables

	int mod;
	bool check;


public:
	PokemonBattle();
	~PokemonBattle() {};
	void PokemonDamage(double, Pokemon*);
	void PokemonSTAB(float, Pokemon*);
	void PokemonMovePriority(Pokemon*, Pokemon*);
	void PokemonOHKO(Pokemon*, Pokemon*);
	void PokemonResistance(Pokemon*, Pokemon*);
	void Substitute(float, Pokemon*, Pokemon*);


};

#endif // !POKEMONBATTLE_H
