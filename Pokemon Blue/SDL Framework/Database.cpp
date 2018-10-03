#include "Database.h"

float TypeRelation::effectiveChart[4] = { 0.25f, 0.5f, 1.0f, 4.0f };

Database* Database::sInstance = nullptr;
Database* Database::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Database();
	}

	return sInstance;
}

void Database::AddTypeRelation(DataPokeType atk, DataPokeType def, float eff) {
	typeRelations.push_back(new TypeRelation(atk, def, eff));
};

float Database::GetTypeEffectiveness(DataPokeType attacking, DataPokeType defending) {
	for (TypeRelation* Q : typeRelations) {
		if (Q->attacking == attacking && Q->defending == defending) {
			return Q->effect;
		}
	}
	//
	return 1.00;
}


TypeRelation::TypeRelation(DataPokeType atk, DataPokeType def, float eff) {
	attacking = atk;
	defending = def;
	effect = eff;
}

void Database::FillDataPokeMove() {
	
	Database* db = Database::Instance();
	
	std::ifstream readfile;

	readfile.open("PokemonBlueAttackDatabase.csv");

	while (!readfile.eof()) {
		int newLine = 0;
		std::string temp;

		std::string nam;
		std::string mod;
		int use;
		int pow;
		int acc;
		bool critRate;
		int pri;
		DataPokeType typ;
		int hitCnt;
		int procRt;
		MoveEffect procEff;
		bool useWrld;

		//std::string columns[7] = { "Name", "Mode", "Uses", "Power", "Accuracy", "CritRate", "Priority", "Type", "HitCount"	"ProcRate	ProcEff	UseWorld};
		//int row = 0;

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


		AddPokemonAttack(nam, mod, use, pow, acc, critRate, pri, typ, hitCnt, procRt, procEff, useWrld);
	}


	readfile.close();

	readfile.open("PokemonDatabase.csv");

	while (!readfile.eof()) {
		int numline = 0;
		std::string temp;

		std::string pknam;
		int hp;
		int atk;
		int def;
		int spc;
		int spd;
		DataPokeType tyI;
		DataPokeType tyII;
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

		db->AddPokeData(pknam, hp, atk, def, spc, spd, tyI, tyII, ms, cr, xp);
		//std::cout << pknam<< std::endl;
	}

	readfile.close();

	readfile.open("PokemonResistanceChart.csv");

	int lineNum = 0;
	std::string temp;
	//
	while (!readfile.eof()) {
		for (int i = 0; i < 15; i++) {
			getline(readfile, temp, ',');
			//
			if (lineNum > 0) {
				AddTypeRelation(static_cast<DataPokeType>(lineNum - 1), static_cast<DataPokeType>(i), TypeRelation::effectiveChart[stoi(temp)]);
				// pokeResist[i][j] = temp;
			}
		}
		//
		lineNum++;
	}
	readfile.close();
}

void Database::AddPokemonAttack(std::string nam, std::string mod, int use, int pow, int acc, bool critRate, int pri, DataPokeType typ, int hitCnt, int procRt, MoveEffect procEff, bool useWrld) {
	pokemonAttacks.push_back(new DataPokeMove(nam, mod, use, pow, acc, critRate, pri, typ, hitCnt, procRt, procEff, useWrld));
};

DataPokeMove::DataPokeMove(std::string nam, std::string mod, int use, int pow, int acc, bool critRate, int pri, DataPokeType typ, int hitCnt, int procRt, MoveEffect procEff, bool useWrld) {
	name = nam;
	mode = mod;
	uses = use;
	power = pow;
	accuracy = acc;
	criticalRate = critRate;
	priority = pri;
	type = typ;
	hitCounts = hitCnt;
	procRates = procRt;
	procEffect = procEff;
	useWorld = useWrld;
}

void Database::AddPokeData(std::string pknam, int hp, int atk, int def, int spc, int spd, DataPokeType tyI, DataPokeType tyII, float ms, int cr, int xp) {
	pokedata.push_back(new DataPokeInfo(pknam, hp, atk, def, spc, spd, tyI, tyII, ms, cr, xp));
}

DataPokeInfo::DataPokeInfo(std::string pknam, int hp, int atk, int def, int spc, int spd, DataPokeType tyI, DataPokeType tyII, float ms, int cr, int xp) {
	pokename = pknam;
	hitpoint = hp;
	attack = atk;
	defense = def;
	special = spc;
	speed = spd;
	typeI = tyI;
	typeII = tyII;
	mass = ms;
	captureRate = cr;
	exp = xp;
}

void Database::Initialize() {

	FillDataPokeMove();
	
	//pokeAtk = new DataPokeMove();
	//pokeData = new DataPokeInfo();
	//pokeType = new DataPokeType();
	//
	int i = 1;
}