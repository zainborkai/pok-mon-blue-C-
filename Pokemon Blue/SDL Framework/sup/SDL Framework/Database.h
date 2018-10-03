#ifndef DATABASE_H
#define DATABASE_H

#include "Item.h"
#include <map>


class Database {
public:
	static Database* Instance();
	
	void AddItem(Item* Q);
	Item* GetItem(std::string index); // ??? <-- Not a very good way of getting items! Change later...

	enum Ailment {
		Poison,
		Burn,
		Sleep,
		Freeze,
		Paralysis,
		ALL,
	};
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

private:
	Database();

	static Database* sInstance;
	std::map<std::string, Item*> allItems;
};
#endif
