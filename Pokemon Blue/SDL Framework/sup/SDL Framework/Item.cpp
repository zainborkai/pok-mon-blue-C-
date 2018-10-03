#include "Item.h"



Item::Item() {
	std::string list[72][5];
	std::vector<std::string>ItemEx;
	std::ifstream Itemfunc;
	
	Itemfunc.open("Poke_Item.csv");
	if (!Itemfunc.eof()) {
		std::string p;
		
		for (int row = 0; row < 72; row++) {
			
			for (int col = 0; col < 5;) {
				getline(Itemfunc, p, ',');
				list[row][col] = p;
				//ItemEx.push_back(p);
				std::cout << p;
				col++;
			}
		}
	}
}
Item::~Item() {}

Item::Item(std::string nam, ItemEffects eff, int amo = 0, int pri = 0) {
	name = nam;
	effect = eff;
	amount = amo;
	price = pri;
}