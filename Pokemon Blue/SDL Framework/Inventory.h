#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include "Item.h"
#include <vector>
#include "Database.h"


class Inventory {
	class InventoryItem {
	public:
		//this make the item =1, this also make Q equals item
		InventoryItem(Item* Q) { item = Q; quantity = 1; }
		//quantity of the item in th einventory
		int quantity;

		Item* GetItem() { return item; }
	private:
		Item* item;
	};

	void AddItem(Item* Q);
	void SubItem(Item* Q);
private:
	static const int CAPACITY = 20;
	//allthethins is the inventory holder
	std::vector<InventoryItem*> allTheThings;


	//the constant amount the array can hold(inventory)
	int numOfItem;
	std::string nameOfItem;
	

public:
	Inventory();
	~Inventory();
	Inventory(int[], std::string, int&);
	//@param int - fill this array
	//@param string - name od item
	//@param int - amount of item
	
	//allocator
	int getNumOfItem() { return numOfItem; }
	std::string getNameOfItem() { return nameOfItem; }

	//mutator
	inline void setNumOfItem(int s_numOfItem) { numOfItem = s_numOfItem; }
	inline void setNameOfItem(int s_nameOfItem) { nameOfItem = s_nameOfItem; }

	//the array holding the item 
	//create a function thatholds the array - function decleration
	


};

#endif // !INVENTORY_H
