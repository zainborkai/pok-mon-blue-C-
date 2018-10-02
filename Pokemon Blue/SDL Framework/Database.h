#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <vector>
#include "Helper.h"


enum Stats {
	Health,
	Attack,
	Defense,
	Speed,
	SAttack,
	SDefense,
	Accuracy,
	Evasion,
	Count,
};
enum VolatileAilments {
	Bound, // Wrap, Bind, Clamp, etc...
	Confused,
	LeechSeed,
	Flying, // Forced to use the "real" Fly attack on the next turn
	Digging, // Forced to use the "real" Dig attack on the next turn
	Recharging, // The rest period after using Hyper Beam.
	Counter, // Will reciprocate 200% of physical damage it received since starting this to the opponent when this ends
	MirrorCoat, // Will reciprocate 200% of special damage it received since starting this to the opponent when this ends
	Bide, // Will reciprocate 300% of any damage it received since starting this to the opponent when this ends
};
enum class StatusEffects {
	None,
	Poison,
	Paralysis,
	Sleep,
	Frozen,
	Burn,
};
enum class PokeTypings {
	NA,
	Normal,
	Fire,
	Grass,
	Water,
	Ghost,
	Bug,
	Poison,
	Ground,
	Psychic,
};


enum class PokeMoves {
	NA,
	Tackle,
};
enum class PokeItems {
	NA,
	Potion,
	TownMap,
	PokeBall,
	Antidote,
	ParalHeal,
	BurnHeal,
};

enum class TypeEfficacy {
	Immune,
	Resistant,
	Normal,
	Effective,
};

// ----------------------------------------------------------------------------

class InventoryItem {
public:
	InventoryItem(PokeItems Q, int n) { item = Q; quantity = n; }
	PokeItems item;
	int quantity;
};

class PokeData {
public:
	PokeData(int id, std::string nam, PokeTypings t1, PokeTypings t2) {
		identification = id;
		name = nam;
		type1 = t1;
		type2 = t2;
	}
	int identification;
	std::string name;
	PokeTypings type1;
	PokeTypings type2;
};

class Database {
public:
	static Database* Instance();


	PokeData* GetPokeData(int id) {	return (*allPokeData)[id]; };


	std::string GetPokeMoveName(PokeMoves Q);
	std::string GetPokeMoveType(PokeMoves Q);
	PokeTypings GetPokeMoveTyping(PokeMoves Q);
	int GetPokeMovePP(PokeMoves Q);
	int GetPokeMovePower(PokeMoves Q);
	int GetPokeMoveAccuracy(PokeMoves Q);

	std::string GetPokeItemName(PokeItems Q);


	TypeEfficacy Check_TypeEfficacy(int id, PokeTypings typing);
	

private:
	Database();
	static Database* sInstance;

	std::map<int, PokeData*>* allPokeData;
};







class Pokemon {
public:
	std::map<Stats, int> stats;
	int GetStat(Stats stat) { return stats[stat]; }
	int GetHP() { return GetStat(Stats::Health) - damage; }

	int damage; // Total damage received.
	StatusEffects statusEff = StatusEffects::None;

	std::string nickname = "";

	std::string GetName() {
		if (nickname == "") {
			return ToUppercase(Database::Instance()->GetPokeData(pokeID)->name);
		}
		else {
			return nickname;
		}
	}
	int GetLevel() { return 50; }
	int GetPokeID() { return pokeID; }

	/// *** 0 = fainted, 1 = critical, 2 = injured, 3 = aching, 4 = fine
	int GetVigorStatus() { return ceil(GetHP() / (1.0f*GetStat(Stats::Health) / 4)); }

	PokeMoves moves[4] = { PokeMoves::Tackle, PokeMoves::NA, PokeMoves::NA, PokeMoves::NA };
	int movesPP[4] = { 10, 10, 10, 10 };
private:
	int pokeID;
public:
	Pokemon(int id) {
		pokeID = id;
		//
		for (int i = 0; i < Stats::Count; i++) {
			stats[(Stats)i] = 100;
		}
	}

	bool IsDead() { return damage >= GetStat(Stats::Health); }
};


#endif
