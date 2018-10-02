
#include "Database.h"

Database* Database::sInstance = nullptr;



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
