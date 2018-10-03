#ifndef POKEMON_H
#define POKEMON_H

#include "Database.h"


class Pokemon {
public:
	std::map<Stats, int> stats;
	int GetStat(Stats stat) { return stats[stat]; }
	int GetHP() { return std::max(0, GetStat(Stats::Health) - damage); }
	int GetAtk() { return GetStat(Stats::Attack); }
	int GetDef() { return GetStat(Stats::Defense); }
	int GetSpd() { return GetStat(Stats::Speed); }
	int GetStk() { return GetStat(Stats::SAttack); }
	int GetSdf() { return GetStat(Stats::SAttack); } // SDefense // *** There isn't actually a "sdefense" stat in Gen 1.

	int damage; // Total damage received.
	StatusEffects statusEff = StatusEffects::None;

	std::string nickname = "";

	void DoDamage(int val) {
		damage += val;
		//
		if (IsDead()) {
			statusEff = StatusEffects::KO; // *** Become "KO'd" if you have no more HP!
		}
		else if (statusEff == StatusEffects::KO) {
			statusEff = StatusEffects::None; // *** Lift "Dead" status if you still have HP
		}
	}
	void DoHeal(int val) { DoDamage(-val); }

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



	// ===================================================================
public:
	void PokemonDamage(double, Pokemon*);
	void PokemonSTAB(float, Pokemon*);
	void PokemonMovePriority(Pokemon*, Pokemon*);
	void PokemonOHKO(Pokemon*, Pokemon*);
	void PokemonResistance(Pokemon*, Pokemon*);
	void Substitute(float, Pokemon*, Pokemon*);
};


#endif
