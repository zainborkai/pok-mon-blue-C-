#include "Database.h"

float TypeRelation::effectiveChart[4] = { 0.25f, 0.5f, 1.0f, 4.0f };

Database* Database::sInstance = nullptr;
Database* Database::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Database();
	}

	return sInstance;
}



Database::Database() {
	readfile.open("PokemonResistanceChart.csv");

	int lineNum = 0;
	std::string temp;
	//
	while (!readfile.eof()) {
		for (int i = 0; i < 14; i++) {
			getline(readfile, temp, ',');
			//
			if (lineNum > 0) {
				AddTypeRelation(static_cast<PokeType>(lineNum-1), static_cast<PokeType>(i), TypeRelation::effectiveChart[stoi(temp)]);
				// pokeResist[i][j] = temp;
			}
		}
		//
		lineNum++;
	}
	readfile.close();

	readfile.open("PokemonBlueAttackDatabase.csv");

	std::string columns[7] = { "Name", "Mode", "Uses", "Power", "Accuracy", "Priority", "Type" };
	

	int row = 0;
	while (!readfile.eof()) {
		std::string nam;
		std::string mod;
		int use;
		int pow;
		int acc;
		int pri;
		PokeType typ;

		getline(readfile, nam, ',');
		getline(readfile, mod, ',');
		getline(readfile, temp, ','); use = stoi(temp);
		getline(readfile, temp, ','); pow = stoi(temp);
		getline(readfile, temp, ','); acc = stoi(temp);
		getline(readfile, temp, ','); pri = stoi(temp);
		getline(readfile, temp, ','); typ = strToPokeType[temp];
		//
		AddPokemonAttack(nam, mod, use, pow, acc, pri, typ);
	}

	readfile.close();

}