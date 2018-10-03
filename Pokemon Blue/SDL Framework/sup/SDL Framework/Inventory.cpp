#include "Inventory.h"

Inventory::Inventory() {

}
Inventory::~Inventory() {

}

void Inventory::AddItem(Item* Q) {
	//this loops increments the amount of item store in the inventory if a player already have one
	
	for (InventoryItem* invitem : allTheThings) {
		//this calls the item in the inventory
		if (invitem->GetItem() == Q) {
			//if the quantity of the item is less than 99 increment it
			if (invitem->quantity < 100){
				invitem->quantity++;}
			return;
		}
	}
	allTheThings.push_back(new InventoryItem(Q));

}
void Inventory::SubItem(Item* Q) {
	//this loop decrecments the amount of the item store in the inventory 
	
	for (int i = allTheThings.size()-1; i >= 0; i--) {
		InventoryItem* invitem = allTheThings[i];
		//
		if (invitem->GetItem() == Q) {
				invitem->quantity--;
				//
				if (invitem->quantity == 0) {
					allTheThings.erase(allTheThings.begin() + i);
					return;
				}
		}
	}
	
}
Inventory::Inventory(int bagItem[], std::string newItem, int& numOfItem) {

	std::string nameOfItem;
	int amountOfItem;
	
}