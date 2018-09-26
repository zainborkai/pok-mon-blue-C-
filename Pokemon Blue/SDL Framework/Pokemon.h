#ifndef POKEMON_H
#define POKEMON_H

#include "Texture.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class Pokemon : public Texture {
private:
	unsigned int level;
	unsigned int exp;
	unsigned int maxHP;
	int hp;

	unsigned int attack;
	unsigned int accuracy;
	unsigned int evasion;
	unsigned int speed;
	unsigned int defense;
	int specAttack;
	int baseATK;

	float crit;

	std::string pokeBattle[166][7];
	Vector2 mPos;
#pragma region AAAA
	/*
	float fireResistance;
	float iceResistance;
	float elecResistance;
	float waterResistance;
	float grassResistance;
	float rockResistance;
	float bugResistance;
	float psychResistance;
	float ghostResistance;
	float flyResistance;

	*/
#pragma endregion

	
	enum PokeType {
		NORMAL = 0,
		FIGHTER = 1,
		FLYING = 2,
		POISON = 3,
		GROUND = 4,
		ROCK = 5,
		BUG = 6,
		GHOST = 7,
		FIRE = 8,
		WATER = 9,
		GRASS = 10,
		ELECTRIC = 11,
		PSYCHIC = 12,
		ICE = 13
	};

	enum Ailments {
		TOXIC,
		BURN,
		PARALYZE,
		FREEZE,
		SLEEP,
		CONFUSION,
		BIND,
		FLINCH
	};

	enum States {
		FIGHT = 0,
		POKEMON = 1,
		ITEM = 2,
		RUN = 3,
	};

	PokeType pokeType;
	//std::vector<std::string>pokeType;

public:
	Pokemon();
	~Pokemon();

	void BattleFunction();

	void Update();
	void Render();

	void SetHP(int s_hp) { hp = s_hp; }
	int GetHp() { return hp; }

	void SetPokeType(PokeType s_pokeType) { pokeType = s_pokeType; }
	PokeType GetPokeType() { return pokeType; }

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

	std::ifstream pokeAttack;


	bool isBattle = true;

};
#endif // !POKEMON_H
