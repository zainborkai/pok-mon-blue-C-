
#include "Database.h"
Database* Database::sInstance = nullptr;

Database::Database() {
	AddItem(new Item("Potion", Item::ItemEffects::RecoversHP, 20, 200));
	AddItem(new Item("Antidote", Item::ItemEffects::CureAilments, 1, 100));
	AddItem(new Item("Paral Heal", Item::ItemEffects::CureAilments, 2, 100));
}
Database* Database::Instance() {

	if (sInstance == nullptr) {
		sInstance = new Database();
	}

	return sInstance;
}
void Database::AddItem(Item* Q) {
	allItems[Q->GetName()] = Q;

}
Item* Database::GetItem(std::string index) {
	return allItems[index];
}
