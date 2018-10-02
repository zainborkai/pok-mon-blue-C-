#ifndef POKEMON_H
#define POKEMON_H

#include "Texture.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Database.h"


class Pokemon : public Texture {
private:
	int level;
	int exp;
	int maxHP;
	int hp;

	int attack;
	int accuracy;
	int evasion;
	int speed;
	int defense;
	int specAttack;
	int baseATK;

	float crit;
	

	
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

	
	

	enum class Ailments {
		POISON, // ??? <-- The "Toxic" status is actually a "volatile" status that amplifies damage
		BURN,
		PARALYZE,
		FREEZE,
		SLEEP,
		CONFUSION,
		BIND,
		FLINCH
	};

	enum class States {
		FIGHT = 0,
		POKEMON = 1,
		ITEM = 2,
		RUN = 3,
	};

	DataPokeType pokeType;
	//std::vector<std::string>pokeType;

public:
	Pokemon();
	~Pokemon();

	void BattleFunction();

	void Update();
	void Render();

	
	
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
	
	

	


	bool isBattle = true;

};
#endif // !POKEMON_H
