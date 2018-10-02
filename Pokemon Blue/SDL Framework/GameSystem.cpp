
#include "GameSystem.h"


GameSystem* GameSystem::sInstance = nullptr;
SDL_Scancode GameSystem::KEY_AFFIRM = SDL_Scancode::SDL_SCANCODE_Z;
SDL_Scancode GameSystem::KEY_CANCEL = SDL_Scancode::SDL_SCANCODE_X;

GameSystem::GameSystem() {
	data = new GameData();
	//
	//
	// ??? <-- Debugging.
	data->playerInventory.push_back(new InventoryItem(PokeItems::TownMap, 1));
	data->playerInventory.push_back(new InventoryItem(PokeItems::PokeBall, 10));
	data->playerInventory.push_back(new InventoryItem(PokeItems::Antidote, 3));
	data->playerInventory.push_back(new InventoryItem(PokeItems::ParalHeal, 1));
	data->playerInventory.push_back(new InventoryItem(PokeItems::BurnHeal, 1));


	// *** Player's pokemon
	Pokemon* Q;
	Q = new Pokemon(34);
	Q->damage = Q->GetHP() *0.4;
	data->bench.push_back(Q);
	Q = new Pokemon(12);
	Q->damage = Q->GetHP() *0.1;
	data->bench.push_back(Q);
	Q = new Pokemon(1);
	Q->damage = Q->GetHP() *0.9;
	data->bench.push_back(Q);
}
