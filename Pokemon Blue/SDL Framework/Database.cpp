
#include "Database.h"

Database* Database::sInstance = nullptr;

std::map<StatusEffects, std::string> Database::statusEffectShorthand = {
		{StatusEffects::None ,		"   "},
		{StatusEffects::Poison ,	"PSN"},
		{StatusEffects::Paralysis ,	"PAR"},
		{StatusEffects::Sleep ,		"SLP"},
		{StatusEffects::Frozen ,	"FRZ"},
		{StatusEffects::Burn ,		"BRN"},
		{StatusEffects::KO ,		"FNT"},
};



Database::Database() {
	allPokeData = new std::map<int, PokeData*>();
	//
	//
	PokeData* Q;
	Q = new PokeData(1, "Bulbasaur", PokeTypings::Grass, PokeTypings::NA);
	allPokeData->insert({ Q->identification, Q });
	Q = new PokeData(4, "Charmander", PokeTypings::Fire, PokeTypings::NA);
	allPokeData->insert({ Q->identification, Q });
	Q = new PokeData(7, "Squirtle", PokeTypings::Water, PokeTypings::NA);
	allPokeData->insert({ Q->identification, Q });
	Q = new PokeData(12, "Butterfree", PokeTypings::Poison, PokeTypings::NA);
	allPokeData->insert({ Q->identification, Q });
	Q = new PokeData(34, "Nidoking", PokeTypings::Poison, PokeTypings::Ground);
	allPokeData->insert({ Q->identification, Q });
	Q = new PokeData(46, "Paras", PokeTypings::Bug, PokeTypings::Grass);
	allPokeData->insert({ Q->identification, Q });
	Q = new PokeData(121, "Starmie", PokeTypings::Water, PokeTypings::Psychic);
	allPokeData->insert({ Q->identification, Q });
	// ??? <-- Use Loi's information later...


	// ==============================================================================
	// *** Ace Dragonair ***
	AddItem(new Item("POTION", ItemEffects::RecoversHP, 20, 200));
	AddItem(new Item("FULL HEAL", ItemEffects::CureAilments, (int)StatusEffects::None, 100)); // *** We will pretend that "None" means EVERYTHING if you're curing!
	AddItem(new Item("ANTIDOTE", ItemEffects::CureAilments, (int)StatusEffects::Poison, 100));
	AddItem(new Item("PARLYZ HEAL", ItemEffects::CureAilments, (int)StatusEffects::Paralysis, 100));
	AddItem(new Item("BURN HEAL", ItemEffects::CureAilments, (int)StatusEffects::Burn, 100));
	AddItem(new Item("TOWN MAP", ItemEffects::KeyItems, 0, 0));
	AddItem(new Item("POKe BALL", ItemEffects::CaptureItems, 0, 0));
	// *** "I added some entries and cleaned this up a bit. Don't forget to do this AUTOMATICALLY by loading in the CSV file! Look at Loi's code!" ~ Khori



	enum class PokeItems {
		NA,
		Potion,
		TownMap,
		PokeBall,
		Antidote,
		ParalHeal,
		BurnHeal,
	};
}

Database* Database::Instance() {
	if (sInstance == nullptr) { sInstance = new Database(); }
	return sInstance;
}

std::string Database::GetPokeMoveName(PokeMoves Q) {
	if (Q == PokeMoves::NA) {
		return "-";
	}
	else {
		return "Tackle";
	}
}
std::string Database::GetPokeMoveType(PokeMoves Q) {
	if (Q == PokeMoves::NA) {
		return "-";
	}
	else {
		return "Normal";
	}
}
PokeTypings Database::GetPokeMoveTyping(PokeMoves Q) {
	return PokeTypings::Normal; // ??? <--
}
int Database::GetPokeMovePP(PokeMoves Q) {
	if (Q == PokeMoves::NA) {
		return 0;
	}
	else {
		return 35;
	}
}
int Database::GetPokeMovePower(PokeMoves Q) {
	if (Q == PokeMoves::NA) {
		return 0;
	}
	else {
		return 40;
	}
}
int Database::GetPokeMoveAccuracy(PokeMoves Q) {
	if (Q == PokeMoves::NA) {
		return 0;
	}
	else {
		return 50;
	}
}

std::string Database::GetPokeItemName(PokeItems Q) {
	switch (Q) {
	case PokeItems::Potion: return "POTION";
	case PokeItems::TownMap: return "TOWN MAP";
	case PokeItems::PokeBall: return "POKe BALL";
	case PokeItems::Antidote: return "ANTIDOTE";
	case PokeItems::ParalHeal: return "PARLYZ HEAL";
	case PokeItems::BurnHeal: return "BURN HEAL";
	}

	return "";
}


TypeEfficacy Database::Check_TypeEfficacy(int id, PokeTypings typing) {
	PokeData* Q = GetPokeData(id);
	//
	int effectRating = 0;
	//
	if (Q->type1 == PokeTypings::Fire && typing == PokeTypings::Fire) {
		effectRating -= 1;
	}
	// ??? <-- ETC... ETC...
	//
	if (Q->type1 == PokeTypings::Grass && typing == PokeTypings::Fire) {
		effectRating += 1;
	}
	// ??? <-- ETC... ETC...
	//
	if (Q->type1 == PokeTypings::Ghost && typing == PokeTypings::Normal) {
		effectRating -= 100;
	}
	// ??? <-- ETC... ETC...
	//
	if (effectRating < -10) {
		return TypeEfficacy::Immune;
	}
	else if (effectRating < 0) {
		return TypeEfficacy::Resistant;
	}
	else if (effectRating > 0) {
		return TypeEfficacy::Effective;
	}
	else {
		return TypeEfficacy::Normal;
	}
}


// =====================================================================================


void Database::Initialize() {
	if (initialized) { return; }
	initialized = true;

	FillDataPokeMove();
	FillDataPokeInfo();

	//pokeAtk = new DataPokeMove();
	//pokeData = new DataPokeInfo();
	//pokeType = new DataPokeType();
	//
	int i = 1;
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

	/*

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
	*/

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
void Database::AddPokeData(std::string pknam, int hp, int atk, int def, int spc, int spd, DataPokeType tyI, DataPokeType tyII, float ms, int cr, int xp) {
	pokedata.push_back(new DataPokeInfo(pknam, hp, atk, def, spc, spd, tyI, tyII, ms, cr, xp));
}

float TypeRelation::effectiveChart[4] = { 0.25f, 0.5f, 1.0f, 4.0f };
TypeRelation::TypeRelation() {
	std::ifstream readfile;

}
TypeRelation::~TypeRelation() {}
TypeRelation::TypeRelation(DataPokeType atk, DataPokeType def, float eff) {
	attacking = atk;
	defending = def;
	effect = eff;
}

DataPokeMove::DataPokeMove() {}
DataPokeMove::~DataPokeMove() {}
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

void Database::FillDataPokeInfo() {
	std::ifstream readfile;
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

		
		AddPokeData(pknam, hp, atk, def, spc, spd, tyI, tyII, ms, cr, xp);
		//std::cout << pknam<< std::endl;
	}

	readfile.close();
}

DataPokeInfo::DataPokeInfo() {}
DataPokeInfo::~DataPokeInfo() {}
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



// =====================================================================================
// *** Ace Dragonair ***
void Database::AddItem(Item* Q) {
	allItems.insert({ Q->GetName(), Q });
}
Item* Database::GetItem(std::string index) {
	return allItems[index];
}

