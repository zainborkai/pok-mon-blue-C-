#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


enum class PokeType {
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
	ICE = 13,
	COUNT = 14
};
static std::map<std::string, PokeType> strToPokeType = {
	{ "NORMAL",		PokeType::NORMAL },
	{ "FIGHTER",	PokeType::FIGHTER },
	{ "FLYING",		PokeType::FLYING },
	{ "POISON",		PokeType::POISON },
	{ "GROUND",		PokeType::GROUND },
	{ "ROCK",		PokeType::ROCK },
	{ "BUG",		PokeType::BUG },
	{ "GHOST",		PokeType::GHOST },
	{ "FIRE",		PokeType::FIRE },
	{ "WATER",		PokeType::WATER },
	{ "GRASS",		PokeType::GRASS },
	{ "ELECTRIC",	PokeType::ELECTRIC },
	{ "PSYCHIC",	PokeType::PSYCHIC },
	{ "ICE",		PokeType::ICE },
};



class TypeRelation {
public:
	static float effectiveChart[4];

	TypeRelation(PokeType atk, PokeType def, float eff) {
		attacking = atk;
		defending = def;
		effect = eff;
	}
	PokeType attacking;
	PokeType defending;
	float effect;
};
class PokeAttack {
public:
	PokeAttack(std::string nam, std::string mod, int use, int pow, int acc, int pri, PokeType typ) {
		name = nam;
		mode = mod;
		uses = use;
		power = pow;
		accuracy = acc;
		priority = pri;
		type = typ;
	}

	std::string GetName() { return name; };
private:
	std::string name;
	std::string mode; // ??? <-- HUH?!
	int uses;
	int power;
	int accuracy;
	int priority;
	PokeType type;
};

class Database {
	

public:
	static Database* Instance();
	Database();
	~Database() {}

	std::ifstream readfile;

	std::vector<TypeRelation*> typeRelations;
	void AddTypeRelation(PokeType atk, PokeType def, float eff) {
		typeRelations.push_back(new TypeRelation(atk, def, eff));
	};
	float GetTypeEffectiveness(PokeType attacking, PokeType defending) {
		for (TypeRelation* Q : typeRelations) {
			if (Q->attacking == attacking && Q->defending == defending) {
				return Q->effect;
			}
		}
		//
		return 1.00;
	}

	std::vector<PokeAttack*> pokemonAttacks;
	void AddPokemonAttack(std::string nam, std::string mod, int use, int pow, int acc, int pri, PokeType typ) {
		pokemonAttacks.push_back(new PokeAttack(nam, mod, use, pow, acc, pri, typ));
	};
	PokeAttack* GetPokemonAttack(std::string id) {
		for (PokeAttack* Q : pokemonAttacks) {
			if (Q->GetName() == id) {
				return Q;
			}
		}
		//
		return nullptr;
	}
private:
	static Database* sInstance;
	std::string pokeBattle[166][7];
	std::string pokeResist[14][14];
};
#endif // !DATABASE_H
