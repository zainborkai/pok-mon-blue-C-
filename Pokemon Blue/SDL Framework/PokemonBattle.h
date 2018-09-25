#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include <vector>
#include <fstream>

class PokemonBattle {
private:
	std::vector<std::string> PokeAttack;
	std::ifstream pokemonAttack;

public:
	PokemonBattle();
	~PokemonBattle() {};

};



#endif // !POKEMONBATTLE_H
