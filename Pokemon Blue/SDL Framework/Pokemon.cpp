#include "Pokemon.h"


Pokemon::Pokemon() {
	mPos.x = 0;
	mPos.y = 0;


	pokeAttack.open("PokemonBlueAttackDatabase.csv");

	while (!pokeAttack.eof()) {
		std::string temp;
		for (int rows = 0; rows < 166; rows++) {
			for (int col = 0; col < 7;) {

				getline(pokeAttack, temp, ',');
				pokeBattle[rows][col] = temp;
				col++;
			}
		}
	}

	pokeAttack.close();
}

Pokemon::~Pokemon() {}

void Pokemon::BattleFunction() {
	if (isBattle) {
		

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