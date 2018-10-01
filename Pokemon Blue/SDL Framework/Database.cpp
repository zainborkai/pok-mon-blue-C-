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
		for (int i = 0; i < 15; i++) {
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

	//std::string columns[7] = { "Name", "Mode", "Uses", "Power", "Accuracy", "CritRate", "Priority", "Type", "HitCount"	"ProcRate	ProcEff	UseWorld};
	//int row = 0;

	while (!readfile.eof()) {
		std::string nam;
		std::string mod;
		int use;
		int pow;
		int acc;
		bool critRate;
		int pri;
		PokeType typ;
		int hitCnt;
		int procRt;
		MoveEffect procEff;
		bool useWrld;

		getline(readfile, nam, ',');
		getline(readfile, mod, ',');
		getline(readfile, temp, ','); use = stoi(temp);
		getline(readfile, temp, ','); pow = stoi(temp);
		getline(readfile, temp, ','); acc = stoi(temp);
		getline(readfile, temp, ','); critRate = stoi(temp);
		getline(readfile, temp, ','); pri = stoi(temp);
		getline(readfile, temp, ','); typ = strToPokeType[temp];
		getline(readfile, temp, ','); hitCnt = stoi(temp);
		getline(readfile, temp, ','); procRt = stoi(temp);
		getline(readfile, temp, ','); procEff = strToMoveEffect[temp];
		getline(readfile, temp, ','); useWrld = stoi(temp);
	
		
		//
		AddPokemonAttack(nam, mod, use, pow, acc, critRate, pri, typ, hitCnt, procRt, procEff, useWrld);
	}


	readfile.close();


	//std::string columns[11] = { "POKEMON", "HP", "ATK", "DEF", "Special", "Speed", "TYPE I", "TYPE II", "Mass(kG)", "Capture Rate", "Total EXP" };

	readfile.open("PokemonDatabase.csv");

	while (!readfile.eof()) {
		int numline = 0;
		std::string pknam;
		int hp;
		int atk;
		int def;
		int spc;
		int spd;
		PokeType tyI;
		PokeType tyII;
		float ms;
		int cr;
		int xp;

			getline(readfile, pknam, ',');
			getline(readfile, temp, ','); hp = stoi(temp);
			getline(readfile, temp, ','); atk = stoi(temp);
			getline(readfile, temp, ','); def = stoi(temp);
			getline(readfile, temp, ','); spc = stoi(temp);
			getline(readfile, temp, ','); spd = stoi(temp);
			getline(readfile, temp, ','); tyI = strToPokeType[temp];
			getline(readfile, temp, ','); tyII = strToPokeType[temp];
			getline(readfile, temp, ','); ms = stof(temp);
			getline(readfile, temp, ','); cr = stoi(temp);
			getline(readfile, temp, ','); xp = stoi(temp);
		
			AddPokeData(pknam, hp, atk, def, spc, spd, tyI, tyII, ms, cr, xp);		
			//std::cout << pknam<< std::endl;
	}

	readfile.close();

}