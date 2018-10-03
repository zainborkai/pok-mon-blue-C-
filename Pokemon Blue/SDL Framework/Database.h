#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <vector>
#include "Helper.h"
#include <iostream>
#include <fstream>

#include "Item.h"


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
	None = 0,
	Poison = 1,
	Paralysis = 2,
	Sleep = 3,
	Frozen = 4,
	Burn = 5,
	KO = 6,
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


// ===========================================================================================================
// *** Loi

enum class DataPokeType {
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
static std::map<std::string, DataPokeType> strToPokeType = {
	{ "NORMAL",		DataPokeType::NORMAL },
	{ "FIGHTER",	DataPokeType::FIGHTER },
	{ "FLYING",		DataPokeType::FLYING },
	{ "POISON",		DataPokeType::POISON },
	{ "GROUND",		DataPokeType::GROUND },
	{ "ROCK",		DataPokeType::ROCK },
	{ "BUG",		DataPokeType::BUG },
	{ "GHOST",		DataPokeType::GHOST },
	{ "FIRE",		DataPokeType::FIRE },
	{ "WATER",		DataPokeType::WATER },
	{ "GRASS",		DataPokeType::GRASS },
	{ "ELECTRIC",	DataPokeType::ELECTRIC },
	{ "PSYCHIC",	DataPokeType::PSYCHIC },
	{ "ICE",		DataPokeType::ICE },
	{ "NONE",		DataPokeType::NONE }
};

enum class MoveEffect
{
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
	TypeRelation();
	~TypeRelation();
	static float effectiveChart[4];

	TypeRelation(DataPokeType, DataPokeType, float);
	DataPokeType attacking;
	DataPokeType defending;
	float effect;
};
class DataPokeMove {
public:
	DataPokeMove();
	~DataPokeMove();
	DataPokeMove(std::string, std::string, int, int, int, bool, int, DataPokeType, int, int, MoveEffect, bool);
	std::string GetName() { return name; };



private:
	std::string name;
	std::string mode; // ??? <-- HUH?!
	int uses;
	int power;
	int accuracy;
	bool criticalRate;
	int priority;
	DataPokeType type;
	int hitCounts;
	int procRates;
	MoveEffect procEffect;
	bool useWorld;


};
class DataPokeInfo {
	std::string pokename;
	int hitpoint;
	int attack;
	int defense;
	int special;
	int speed;
	DataPokeType typeI;
	DataPokeType typeII;
	float mass;
	int captureRate;
	int exp;


public:
	DataPokeInfo();
	~DataPokeInfo();
	DataPokeInfo(std::string, int, int, int, int, int, DataPokeType, DataPokeType, float, int, int);
	std::string GetPokeData() { return pokename; }
};

// ===========================================================================================================
// *** Ace Dragonair


enum EvolveStone {
	Fire,
	Leaf,
	Moon,
	Thunder,
	Water,
};
enum Pokeball {
	Pokeball,
	GreatBall,
	UltraBall,
	MasterBall,
	SafariBall,
};

// ===========================================================================================================

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

	static std::map<StatusEffects, std::string> statusEffectShorthand;
	

private:
	Database();
	static Database* sInstance;

	std::map<int, PokeData*>* allPokeData;



	// ~~~~~~~~~~~~~~~~~ Loi's part ~~~~~~~~~~~~~~~~~
public:
	bool initialized = false;
	void Initialize();
	void FillDataPokeMove();

	std::vector<DataPokeMove*> pokemonAttacks;
	void AddPokemonAttack(std::string nam, std::string mod, int use, int pow, int acc, bool critRate, int pri, DataPokeType typ, int hitCnt, int procRt, MoveEffect procEff, bool useWrld);
	DataPokeMove* GetPokemonAttack(std::string id) {
		for (DataPokeMove* Q : pokemonAttacks) {
			if (Q->GetName() == id) {
				return Q;
			}
		}
		//
		return nullptr;
	}

	std::vector<DataPokeInfo*> pokedata;
	void AddPokeData(std::string, int, int, int, int, int, DataPokeType, DataPokeType, float, int, int);
	DataPokeInfo* GetPokeData(std::string pkd) {
		for (DataPokeInfo* Q : pokedata) {
			if (Q->GetPokeData() == pkd) {
				return Q;
			}
		}
		return nullptr;
	}
	void FillDataPokeInfo();

	std::vector<TypeRelation*> typeRelations;
	void AddTypeRelation(DataPokeType, DataPokeType, float);
	float GetTypeEffectiveness(DataPokeType, DataPokeType);
private:
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// *** Ace Dragonair ***
public:
	void AddItem(Item* Q);
	Item* GetItem(std::string index);

private:
	std::map<std::string, Item*> allItems;
};


#endif
