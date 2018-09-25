#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class PokemonBattle {
private:
	std::vector<std::string> pokeBattle;
	std::ifstream pokemonAttack;

protected:
	//variables
	unsigned int maxHP;
	unsigned int hp;
	unsigned int baseATK;
	unsigned int level;

	int specAttack;
	int defense;
	int baseSpeed;
	float accuracy;
	float evasion;
	float crit;
	int mod;


public:
	PokemonBattle();
	~PokemonBattle() {};
	void PokemonDamage(double);
	void PokemonSTAB(float);
	void PokemonMovePriority();
	void PokemonOHKO();
	void PokemonResistance();
	void Substitute(float);


};

#endif // !POKEMONBATTLE_H
