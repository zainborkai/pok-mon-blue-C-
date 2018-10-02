#include "Pokemon.h"


Pokemon::Pokemon() {
	mPos.x = 0;
	mPos.y = 0;
}

Pokemon::~Pokemon() {}

void Pokemon::BattleFunction() {
	if (isBattle) {
		
		//TypeRelation::GetTypeEffectiveness(PokeType::FIRE, PokeType::BUG);
		//int c;

		//PLAYER CHOOSES FROM OPTIONS
		/*switch (c) {
		case FIGHT:
		AttackFunction();

		case POKEMON:
		PokemonFunction();

		case ITEM:
		break;
		case RUN:
		break;

		}*/
	}
}

void Pokemon::Update() {

}

void Pokemon::Render() {

}