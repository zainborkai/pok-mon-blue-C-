#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include<string>
#include <vector>
#include <fstream>

enum ItemEffects {
	RecoversHP,
	RecoversPP,
	CureAilments,//posion, sleep, burn,
	BoostsStats,//
	PermaIncStats,
	PreventssTATSDec,
	Evolution,
	Repels,
	Revival,
	LevelUp,//evelution stones
	TrainingMachines,
	HyperTrainMachines,//changes stats & changes power
	MoneyItem, // "Nuggets"
	BattleItem, // "Poke Doll"
	FieldItem, // "Escape Rope"
	CaptureItems, // Pokeballs in general
	Bicycle,
	KeyItems, // These are things that do literally nothing, but can't be discarded
	ActivatableItems, // Pokeflute, Itemfinder, Coin Case, Town Map
	FishingRods,
	ExchangeableItems,//Anything that can be excgange for another thing 

};

class Item {
public:
	//defualt constructor
	Item();

	//destructor
	~Item();

	


	/*//allocator
	int getHP() { return iHealth; }
	int getPP() { return iPower; }
	bool getAilment() { return ailment; }
	int getBoost() { return iBoost; }
	int getPerboost() { return iPerboost; }
	bool getPrevent() { return iPrevent; }
	bool getEvolution() { return newpokemon; }
	int getRepel() { return iRepel; }
	bool getRevive() { return iRevive; }
	int getLevelup() { return iLVLUP; }
	//int getMachine(){}
	//int getHymachine(){}
	int getMoney() { return iGold; }
	bool getBattle() { return iEscapebattle; }
	bool getField() { return iField; }
	bool getCapture() { return iPokeball; }
	bool getBicycle() { return iBike; }
	bool getKey() { return iKey; }
	bool getActiveitem() { return iActive; }
	bool getRod() { return iRod; }
	bool getExchange() { return iExchange; }

	//mutator
	inline void setHP(int s_health) { iHealth = s_health; }
	inline void setPP(int s_powepoint) { iPower = s_powepoint; }
	inline void setAilment(bool s_aliment) { ailment = s_aliment; }
	inline void setBoost(int s_boost) { iBoost = s_boost; }
	inline void setPerBoost(int s_perBoost) { iPerboost = s_perBoost; }
	inline void setPrevent(bool s_prevent) { iPrevent = s_prevent; }
	inline void setEvolution(bool s_evolve) { newpokemon = s_evolve; }
	inline void setRepel(int s_repel) { iRepel = s_repel; }
	inline void setRevive(bool s_revive) { iRevive = s_revive; }
	inline void setLevelup(bool s_level) { iLVLUP = s_level; }
	//inline void setMachine(){}
	//inline void setHymachine(){}
	inline void setMoney(int s_gold) { iGold = s_gold; }
	inline void setBattle(bool s_escape) { iEscapebattle = s_escape; }
	inline void setField(bool s_field) { iField = s_field; }
	inline void setCapture(bool s_capture) { iPokeball = s_capture; }
	inline void setBicycle(bool s_bike) { iBike = s_bike; }
	inline void setKey(bool s_key) { iKey = s_key; }
	inline void setActiveitem(bool s_active) { iActive = s_active; }
	inline void setRod(bool s_rod) { iRod = s_rod; }
	inline void setExchange(bool s_exchange) { iExchange = s_exchange; }*/

	Item(std::string nam, ItemEffects eff, int amo, int pri);

	std::string GetName() { return name; }
	
	// member variable 
	std::string name;
	int price;// 0 if it cannot be sold 
	ItemEffects effect;
	int amount;
	


	//int type;
	
	/*int iHealth;
	int iPower;
	bool newpokemon;
	//int ilevel;
	int iGold;
	bool iField;
	bool ailment;
	int iBoost;
	int iPerboost;
	int iRepel;
	bool iRevive;
	bool iLVLUP;
	bool iPokeball;
	bool iKey;
	bool iRod;
	bool iExchange;
	bool iActive;
	bool iPrevent;
	bool iBike;
	bool iEscapebattle;*/

	
	

};

#endif // !ITEM_H
#pragma once
