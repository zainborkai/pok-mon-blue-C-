#ifndef POKEMONBATTLE_H
#define POKEMONBATTLE_H

#include "Pokemon.h"



class PokemonBattle : public DataPokeInfo {
private:

	//std::ifstream pokemonAttack;
	

protected:
	//variables

	int mod;
	bool check;


public:
	PokemonBattle(){}
	~PokemonBattle() {}
	void PokemonDamage(double, Database*);
	void PokemonSTAB(float, TypeRelation*);
	void PokemonMovePriority(DataPokeMove*, DataPokeMove*);
	void PokemonOHKO(DataPokeMove*, Database*);
	void PokemonResistance(TypeRelation*, TypeRelation*);
	void Substitute(float, Database*, Database*);

	//
	/*
	void SetHP(int s_hp) { hp = s_hp; }
	int GetHp() { return hp; }

	void SetPokeType(DataPokeType s_pokeType) { pokeType = s_pokeType; }
	DataPokeType GetPokeType() { return pokeType; }

	void SetSpeed(int s_speed) { speed = s_speed; }
	int GetSpeed() { return speed; }

	void SetBaseAttack(int s_bAttack) { baseATK = s_bAttack; }
	int GetBaseAttack() { return baseATK; }

	void SetSpecAttack(int s_sAttack) { specAttack = s_sAttack; }
	int GetSpecAttack() { return specAttack; }

	void SetDefense(int s_defense) { defense = s_defense; }
	int GetDefense() { return defense; }

	void SetLevel(int s_level) { level = s_level; }
	int GetLevel() { return level; }

	void SetMaxHp(int s_maxHP) { maxHP = s_maxHP; }
	int GetMaxHp() { return maxHP; }
	
	*/
	


};

#endif // !POKEMONBATTLE_H
