#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include "Pokemon.h"



class PokemonBattle : public Database {
private:

	//std::ifstream pokemonAttack;
	

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

	//



};

#endif // !POKEMONBATTLE_H
