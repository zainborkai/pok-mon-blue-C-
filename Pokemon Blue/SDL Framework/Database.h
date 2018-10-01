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
	NONE = 14,
	COUNT = 15
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
	{ "NONE",		PokeType::NONE }
};

enum class MoveEffect {
	Absorb,
	SpeedDown,
	Poison,
	Paralyzes,
	Counter,
	Crashes,
	Flinch,
	Recoil,
	Burn,
	FireSpin,
	FlyState,
	SkyState,
	Confuse,
	Nightmare,
	Seed,
	PetalDance,
	Sleep,
	SolarBeam,
	Dig,
	OHKO,
	AccuracyDown,
	AttackDown,
	Freeze,
	Mist,
	Bide,
	StatReset,
	Bind,
	Conversion,
	DefenseUp,
	Disable,
	EvasionUp,
	Suicide,
	FocusEnergy,
	SpecialUp,
	DefenseDown,
	Mimic,
	PayDay,
	Rage,
	RazorWind,
	Heal,
	Switch,
	DefenseDownBig,
	AttackUp,
	SkullBash,
	Splash,
	Substitute,
	CutHP,
	AttackUpBig,
	Thrash,
	Transforming,
	Wrap,
	DefenseUpBig,
	Toxic,
	SpeedUpBig,
	LightScreen,
	SpecialDown,
	Reflect,
	Rest,
	Escape,
	Clamp,
	DefenseUP,
	NA
};

static std::map<std::string, MoveEffect> strToMoveEffect = {
	{ "Absorb",			MoveEffect::Absorb },
	{ "SpeedDown",		MoveEffect::SpeedDown },
	{ "Poison",			MoveEffect::Poison },
	{ "Paralyzes",		MoveEffect::Paralyzes },
	{ "Counter",		MoveEffect::Counter },
	{ "Crashes",		MoveEffect::Crashes },
	{ "Flinch",			MoveEffect::Flinch },
	{ "Recoil",			MoveEffect::Recoil },
	{ "Burn",			MoveEffect::Burn },
	{ "FireSpin",		MoveEffect::FireSpin },
	{ "FlyState",		MoveEffect::FlyState },
	{ "SkyState",		MoveEffect::SkyState },
	{ "Confuse",		MoveEffect::Confuse },
	{ "Nightmare",		MoveEffect::Nightmare },
	{ "Seed",			MoveEffect::Seed },
	{ "PetalDance",		MoveEffect::PetalDance },
	{ "Sleep",			MoveEffect::Sleep },
	{ "SolarBeam",		MoveEffect::SolarBeam },
	{ "Dig",			MoveEffect::Dig },
	{ "OHKO",			MoveEffect::OHKO },
	{ "AccuracyDown",	MoveEffect::AccuracyDown },
	{ "AttackDown",		MoveEffect::AttackDown },
	{ "Freeze",			MoveEffect::Freeze },
	{ "Mist",			MoveEffect::Mist },
	{ "Bide",			MoveEffect::Bide },
	{ "StatReset",		MoveEffect::StatReset },
	{ "Bind",			MoveEffect::Bind },
	{ "Conversion",		MoveEffect::Conversion },
	{ "DefenseUp",		MoveEffect::DefenseUp },
	{ "Disable",		MoveEffect::Disable },
	{ "EvasionUp",		MoveEffect::EvasionUp },
	{ "Suicide",		MoveEffect::Suicide },
	{ "FocusEnergy",	MoveEffect::FocusEnergy },
	{ "SpecialUp",		MoveEffect::SpecialUp },
	{ "DefenseDown",	MoveEffect::DefenseDown },
	{ "Mimic",			MoveEffect::Mimic },
	{ "PayDay",			MoveEffect::PayDay },
	{ "Rage",			MoveEffect::Rage },
	{ "RazorWind",		MoveEffect::RazorWind },
	{ "Heal",			MoveEffect::Heal },
	{ "Switch",			MoveEffect::Switch },
	{ "DefenseDownBig", MoveEffect::DefenseDownBig },
	{ "AttackUp",		MoveEffect::AttackUp },
	{ "SkullBash",		MoveEffect::SkullBash },
	{ "Splash",			MoveEffect::Splash },
	{ "Substitute",		MoveEffect::Substitute },
	{ "CutHP",			MoveEffect::CutHP },
	{ "AttackUpBig",	MoveEffect::AttackUpBig },
	{ "Thrash",			MoveEffect::Thrash },
	{ "Transforming",	MoveEffect::Transforming },
	{ "Wrap",			MoveEffect::Wrap },
	{ "DefenseUpBig",	MoveEffect::DefenseUpBig },
	{ "Toxic",			MoveEffect::Toxic },
	{ "SpeedUpBig",		MoveEffect::SpeedUpBig },
	{ "LightScreen",	MoveEffect::LightScreen },
	{ "SpecialDown",	MoveEffect::SpecialDown },
	{ "Reflect",		MoveEffect::Reflect },
	{ "Rest",			MoveEffect::Rest },
	{ "Escape",			MoveEffect::Escape },
	{ "Clamp",			MoveEffect::Clamp },
	{ "DefenseUP",		MoveEffect::DefenseUP },
	{ "NA",				MoveEffect::NA },
};

/*
enum class PokemonType {
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
NONE = 14
};

static std::map<std::string, PokemonType> strToPokemonType = {
{ "NORMAL",		PokemonType::NORMAL },
{ "FIGHTER",	PokemonType::FIGHTER },
{ "FLYING",		PokemonType::FLYING },
{ "POISON",		PokemonType::POISON },
{ "GROUND",		PokemonType::GROUND },
{ "ROCK",		PokemonType::ROCK },
{ "BUG",		PokemonType::BUG },
{ "GHOST",		PokemonType::GHOST },
{ "FIRE",		PokemonType::FIRE },
{ "WATER",		PokemonType::WATER },
{ "GRASS",		PokemonType::GRASS },
{ "ELECTRIC",	PokemonType::ELECTRIC },
{ "PSYCHIC",	PokemonType::PSYCHIC },
{ "ICE",		PokemonType::ICE },
{ "NONE",		PokemonType::NONE}
};



*/


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
	PokeAttack(std::string nam, std::string mod, int use, int pow, int acc, bool critRate, int pri, PokeType typ, int hitCnt, int procRt, MoveEffect procEff, bool useWrld) {
		name = nam;
		mode = mod;
		uses = use;
		power = pow;
		accuracy = acc;
		criticalRate = critRate;
		priority = pri;
		type = typ;
		hitCounts = hitCnt;
		procRates = procRt;
		procEffect = procEff;
		useWorld = useWrld;

	}

	std::string GetName() { return name; };
private:
	std::string name;
	std::string mode; // ??? <-- HUH?!
	int uses;
	int power;
	int accuracy;
	bool criticalRate;
	int priority;
	PokeType type;
	int hitCounts;
	int procRates;
	MoveEffect procEffect;
	bool useWorld;
};

class PokeData {
	std::string pokename;
	int hitpoint;
	int attack;
	int defense;
	int special;
	int speed;
	PokeType typeI;
	PokeType typeII;
	float mass;
	int captureRate;
	int exp;
	

public:
	PokeData(std::string pknam, int hp, int atk, int def, int spc, int spd, PokeType tyI, PokeType tyII, float ms, int cr, int xp) {
		pokename = pknam;
		hitpoint = hp;
		attack = atk;
		defense = def;
		special = spc;
		speed = spd;
		typeI = tyI;
		typeII = tyII;
		mass = ms;
		captureRate = cr;
		exp = xp;
		
	}

	std::string GetPokeData() { return pokename; }

};


class Database {
public:
	static Database* Instance();
	Database();
	~Database() {}

	std::ifstream readfile;

#pragma region TypeRelation
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
#pragma endregion

#pragma region PokeAttack
	std::vector<PokeAttack*> pokemonAttacks;
	void AddPokemonAttack(std::string nam, std::string mod, int use, int pow, int acc, bool critRate, int pri, PokeType typ, int hitCnt, int procRt, MoveEffect procEff, bool useWrld) {
		pokemonAttacks.push_back(new PokeAttack(nam, mod, use, pow, acc, critRate, pri, typ, hitCnt, procRt, procEff, useWrld));
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
#pragma endregion

#pragma region PokemonDatabase
	std::vector<PokeData*> pokeData;
	void AddPokeData(std::string pknam, int hp, int atk, int def, int spc, int spd, PokeType tyI, PokeType tyII, float ms, int cr, int xp) {
		pokeData.push_back(new PokeData(pknam, hp, atk, def, spc, spd, tyI, tyII, ms, cr, xp));
	}
	PokeData* GetPokeData(std::string pkd) {
		for (PokeData* Q : pokeData) {
			if (Q->GetPokeData() == pkd) {
				return Q;
			}
		}
		return nullptr;
	}
#pragma endregion

private:
	static Database* sInstance;
};


#endif // !DATABASE_H
