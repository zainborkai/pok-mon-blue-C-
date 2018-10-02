#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "GameManager.h"
#include <vector>
#include <map>
#include <algorithm>
#include "Actor.h"
#include "Helper.h"
#include "TextArea.h"
#include "HPGauge.h"
#include "MenuBox.h"
#include "Database.h"
#include "GameSystem.h"



enum class Phases {
	None,
	//
	Initialize,
	Introduction,
	IntroMessage,
	IntroEnd,
	//
	BattleFirst,
	BattlePreparing,
	BattleResolve,
	BattleAnimate,
	BattleLast,
	//
	Victory,
	Outroduction,
	OutroMessage,
	Rewards,
	OutroEnd,
	//
	Defeat,
};
enum class BattleActions {
	NA,
	Attack,
	Switch,
	Item,
	Run,
};
enum class PlayerSlot {
	PLAYER,
	OPPONENT,
};

enum class CombatResult {
	Hit, // The attack hit
	Worked, // It worked (this is different from "hitting" because it does not display crit/efficacy messages)
	Critical, // It worked, as well as gaining extra potency
	Missed, // It failed due to inaccuracy
	Immuned, // The target's typing nullified the move
	Redundant, // It did nothing due to it already being in effect
};

enum class BattleAnimations {
	None = 0,
	PokeballAppear = 1,
	//
	Tackle = 2,
};

enum class BattleEvents {
	Wait,
	ReadMessage,
	BattleText,
	Animation,
};

class BattleEvent {
public:
	BattleEvent(BattleEvents t, std::string s) { type = t; str = s; }
	BattleEvent(BattleEvents t, float n) { type = t; num = n; }
	BattleEvent(BattleEvents t, BattleAnimations anim, PlayerSlot ps) {
		type = t;
		num = static_cast<int>(anim);
		str = (ps == PlayerSlot::PLAYER ? "PLAYER" : "OPPONENT");
	}
	BattleEvents type;
	float num;
	std::string str;
};

class BattleAnimation : public Actor {
public:
	float SECOND;

public:
	BattleAnimation(BattleAnimations id, PlayerSlot wh) {
		animID = id;
		who = wh;
		//
		animTime = 0;
		visible = false;


		SECOND = GameManager::Instance()->GetFrameRate();
	}

	PlayerSlot who;
	BattleAnimations animID;
	int animTime;
	bool finished;

	void Run();
};

class BattleManager : public Actor {
public:
	class Battler {
	public:
		Battler(Pokemon* poke) {
			_pokeData = poke;
			//
			for (int i = 0; i < Stats::Count; i++) {
				statChanges[(Stats)i] = 0;
			}
		};

		Pokemon * _pokeData;
		int GetStat(Stats stat) { return _pokeData->GetStat(stat); }
		float GetHPStatus() { return _pokeData->GetHP() / (1.0f*GetStat(Stats::Health)); }
		
		std::map<Stats, int> statChanges;

		int counterPoint; // Your damage upon beginning a counter attack move

		CombatResult DoAttack(Battler* target, int power, int accuracy, int hitLuck = raffle(), int crtLuck = raffle(), int vryLuck = raffle()) {
			if (hitLuck < accuracy) {
				if (crtLuck < 12) { // ??? <-- This is NOT the crit chance rate!
					target->_pokeData->damage += (2 * power) / 4 * (0.8f + 0.4*(vryLuck / 100.0f));
					return CombatResult::Critical;
				}
				else {
					target->_pokeData->damage += power / 4 * (0.8f + 0.4*(vryLuck / 100.0f));
					return CombatResult::Hit;
				}
				// ??? <-- This is totally NOT how damage is calculated! (xP)
			}
			else {
				return CombatResult::Missed;
			}
		}

		void DoStatChange(Stats stat, int change) {
			int temp = statChanges[stat];
			//
			temp += change;
			//
			temp = std::min(temp, 6);
			temp = std::max(-6, temp);
			//
			statChanges[stat] = temp;
		}
		int GetAdjustedStat(Stats stat) {
			int adjustmentChart[13] = {
				25, // -6
				29,
				33,
				40,
				50,
				66,
				100, // 0
				150,
				200,
				250,
				300,
				350,
				400, // +6
			};

			switch (stat) {
			case Stats::Health: // Health is NEVER "adjusted"!
				return _pokeData->stats[stat];

				// !!! <-- I THINK these are supposed to behave different when adjusted, but meh...
			case Stats::Accuracy:
			case Stats::Evasion:

			default:
				return _pokeData->GetStat(stat) * adjustmentChart[6 + statChanges[stat]];
			}
		}
	};

public:
	class ChoiceLog {
	public:
		std::string ToString() { return "Whoa"; }
		ChoiceLog(PlayerSlot ps, BattleActions ba, int turn, PokeMoves pm = PokeMoves::NA, Battler* b = nullptr, PokeItems pi = PokeItems::NA, bool areRunning = false) {
			who = ps;
			action = ba;
			turnNumber = turn;
			//
			move = pm;
			battler = b;
			item = pi;
			running = areRunning;
			//
			hitLuck = raffle(); // *** The "accuracy" of the attack is pre-determined.
			crtLuck = raffle(); // *** The "critting" of the attack is pre-determined.
			effLuck = raffle(); // *** The "potency" of the additional effect is pre-determined.
			vryLuck = raffle(); // *** The "variance" of damage is pre-determined.
		}

		BattleActions action;
		PokeMoves move;
		PokeItems item;
		Battler* battler;
		bool running;

		PlayerSlot who;
		bool initiated = false;
		bool animated = false;

		int hitLuck;
		int crtLuck;
		int effLuck;
		int vryLuck;

		CombatResult result = CombatResult::Hit;
		TypeEfficacy efficacy = TypeEfficacy::Normal;
	private:
		int turnNumber;
	};
	std::vector<ChoiceLog*> queuedChoices;
	std::vector<ChoiceLog*> allChoices;

	class ChooserClass {
	public:
		enum class ChooseContext {
			None, // *** Context sometimes doesn't matter.
			Switching, // *** You are switching pokemon in the middle of a battle
			BattleIteming, // *** You are using an item mid-battle
			WorldIteming, // *** You are using an item in the world
			Examining, // *** You are checking your pokemon on the map
		};
	public:
		static std::vector<ChooserClass*> allChoosers;

		ChooserClass(ChooseContext Q) {
			context = Q;
			//
			allChoosers.push_back(this);
		}
		~ChooserClass() {
			// ??? <-- I wonder if there's a more efficient way...
			for (int i = 0; i < allChoosers.size(); i++) {
				if (this == allChoosers[i]) {
					allChoosers.erase(allChoosers.begin() + i);
					break;
				}
			}
		}

		static void DeactivateAll() {
			std::vector<ChooserClass*> copyList(allChoosers);
			for (auto Q : copyList) {
				Q->_Deactivate();
			}
		}

		virtual void _Deactivate() {};

		virtual void Run() {
			runTime++;
			//
			if (runTime > 2) { // *** This prevents the input from falling in instantly (IE: a menu leading to another menu)
				if (!is_done && !is_cancel) {
					InputManager* im = InputManager::Instance();
					jist_hori = im->KeyPressed(SDL_Scancode::SDL_SCANCODE_LEFT)*(-1) + (+1) * im->KeyPressed(SDL_Scancode::SDL_SCANCODE_RIGHT);
					jist_vert = im->KeyPressed(SDL_Scancode::SDL_SCANCODE_UP)*(-1) + (+1) * im->KeyPressed(SDL_Scancode::SDL_SCANCODE_DOWN);
					jist_affirm = im->KeyPressed(SDL_Scancode::SDL_SCANCODE_Z);
					jist_cancel = im->KeyPressed(SDL_Scancode::SDL_SCANCODE_X);
				}
			}
		};
		int jist_hori, jist_vert;
		bool jist_affirm, jist_cancel;
		int index = 0;

		bool is_done = false;
		bool is_cancel = false;
		int runTime = 0;

		void Resolve() {
			is_done = true;
		};
		void Cancel() {
			is_cancel = true;
		};

		ChooseContext context = ChooseContext::None;
	};
	class Chooser_Action : public ChooserClass {
	public:
		static Chooser_Action* Activate(ChooseContext Q) {
			if (!sInstance) { sInstance = new Chooser_Action(Q); }
			return sInstance;
		}
		static void Reactivate() {
			if (sInstance != nullptr) {
				sInstance->is_done = false;
				sInstance->is_cancel = false;
			}
		}
		static void Deactivate() {
			if (sInstance) {
				delete sInstance;
				sInstance = nullptr;
			}
		}

		BattleActions result = BattleActions::Run;

		void Run() {
			ChooserClass::Run();
			//
			index += 1 * jist_hori + 2 * jist_vert;
			index = roundabout(index, 4);
			//
			_cursor->Pos(Vector2(72 + (8 * 6)*(index % 2), 112 + (8 * 2)* (index / 2)));
			//
			if (jist_affirm) {
				switch (index) {
				case 0: // Fight
					result = BattleActions::Attack;
					break;
				case 1: // Switch
					result = BattleActions::Switch;
					break;
				case 2: // Item
					result = BattleActions::Item;
					break;
				case 3: // Run
					result = BattleActions::Run;
					break;
				}
				//
				Resolve();
			}
		};

	private:
		void _Deactivate() { Chooser_Action::Deactivate(); }
		Chooser_Action(ChooseContext Q) :
			ChooserClass(Q) {
			_back = new MenuBox(10, 4);
			_back->Translate(Vector2(64, 96));

			_fightText = new TextArea("FIGHT");
			_fightText->Translate(Vector2(80, 112));
			_pokeText = new TextArea("PK");
			_pokeText->Translate(Vector2(128, 112));
			_itemText = new TextArea("ITEM");
			_itemText->Translate(Vector2(80, 112 + 16));
			_runText = new TextArea("RUN");
			_runText->Translate(Vector2(128, 112 + 16));
			_cursor = new Actor();
			_cursor->AssignTexture("battle/menustuff.png", 48, 0, 8, 8);
		}
		~Chooser_Action() {
			_back->Destroy();
			_back = nullptr;

			_fightText->Destroy();
			_fightText = nullptr;
			_pokeText->Destroy();
			_pokeText = nullptr;
			_itemText->Destroy();
			_itemText = nullptr;
			_runText->Destroy();
			_runText = nullptr;

			_cursor->Destroy();
			_cursor = nullptr;
		}
		static Chooser_Action* sInstance;

		TiledTexture* _back;
		TextArea* _fightText;
		TextArea* _pokeText;
		TextArea* _itemText;
		TextArea* _runText;
		Actor* _cursor;
	};
	class Chooser_Move : public ChooserClass {
	public:
		static Chooser_Move* Activate(ChooseContext Q) {
			if (!sInstance) { sInstance = new Chooser_Move(Q); }
			return sInstance;
		}
		static void Reactivate() {
			if (sInstance != nullptr) {
				sInstance->is_done = false;
				sInstance->is_cancel = false;
			}
		}
		static void Deactivate() {
			if (sInstance) {
				delete sInstance;
				sInstance = nullptr;
			}
		}

		int result = 0;

		void Run() {
			ChooserClass::Run();
			//
			int count = 1; // ??? <-- The number of NOT-VOID moves you have...
			//
			index += 1 * jist_vert;
			index = roundabout(index, 4);
			//
			if (jist_vert != 0) {
				UpdateMoveBox();
			}
			//
			_cursor->Pos(Vector2(40, 104 + (8)* index));
			//
			if (jist_affirm) {
				// ??? <-- The index of the move the "battler" knows.
				result = index;
				//
				Resolve();
			}
			else if (jist_cancel) {
				Cancel();
			}
		};

	private:
		MenuBox* _moves;
		MenuBox* _info;
		TextArea* _info_stype;
		TextArea* _info_typing;
		TextArea* _info_powerpoints;
		std::vector<TextArea*> _allMoves;
		Actor* _cursor;


		void UpdateMoveBox() {
			Database* db = Database::Instance();
			PokeMoves currentMove = BattleManager::Instance()->playerBattler->_pokeData->moves[index];
			
			std::string str;
			str = "Type/";
			_info_stype->FeedString(str);
			//
			str = db->GetPokeMoveType(currentMove);
			_info_typing->FeedString(" " + str);
			//
			int val = db->GetPokeMovePP(currentMove);
			if (val > 0) {
				str = std::to_string(BattleManager::Instance()->playerBattler->_pokeData->movesPP[index]) + "/" + std::to_string(db->GetPokeMovePP(currentMove));
			}
			else {
				str = "-/-";
			}
			_info_powerpoints->FeedString("    " + str);
		}

		void _Deactivate() { Chooser_Move::Deactivate(); }
		Chooser_Move(ChooseContext Q) :
			ChooserClass(Q) {
			Database* db = Database::Instance();
			_moves = new MenuBox(14, 4);
			_moves->Translate(Vector2(32, 96));
			//
			_info = new MenuBox(9, 3);
			_info->Translate(Vector2(0, 64));
			//
			_info_stype = new TextArea("");
			_info_stype->Translate(Vector2(8, 72));
			_info_typing = new TextArea("");
			_info_typing->Translate(Vector2(8, 80));
			_info_powerpoints = new TextArea("");
			_info_powerpoints->Translate(Vector2(8, 88));
			//
			UpdateMoveBox();
			

			
			for (int i = 0; i < 4; i++) {
				TextArea* Q = new TextArea(db->GetPokeMoveName(
					BattleManager::Instance()->playerBattler->_pokeData->moves[i]
				));
				//
				Q->Translate(Vector2(48, 104 + i * 8));
				//
				_allMoves.push_back(Q);
			}


			_cursor = new Actor();
			_cursor->AssignTexture("battle/menustuff.png", 48, 0, 8, 8);
		}
		~Chooser_Move() {
			_moves->Destroy();
			_moves = nullptr;

			_info->Destroy();
			_info = nullptr;

			_info_stype->Destroy();
			_info_stype = nullptr;
			_info_typing->Destroy();
			_info_typing = nullptr;
			_info_powerpoints->Destroy();
			_info_powerpoints = nullptr;

			for (auto Q : _allMoves) { Q->Destroy(); }
			_allMoves.clear();

			_cursor->Destroy();
			_cursor = nullptr;
		}
		static Chooser_Move* sInstance;
	};

	class Chooser_Item : public ChooserClass {
	public:
		static Chooser_Item* Activate(ChooseContext Q) {
			if (!sInstance) { sInstance = new Chooser_Item(Q); }
			return sInstance;
		}
		static void Reactivate() {
			if (sInstance != nullptr) {
				sInstance->is_done = false;
				sInstance->is_cancel = false;
			}
		}
		static void Deactivate() {
			if (sInstance) {
				delete sInstance;
				sInstance = nullptr;
			}
		}

		PokeItems result = PokeItems::Potion;

		void Run() {
			ChooserClass::Run();
			//
			std::vector<InventoryItem*> inventory = BattleManager::Instance()->GetInventory(PlayerSlot::PLAYER);
			//
			index += 1 * jist_vert;
			int count = inventory.size();
			if (index > count - menuPush) {
				index = count - menuPush;
			}
			else if (index > 2) {
				menuPush += (index - 2);
				//
				index = 2;
			}
			else if (index < 0) {
				menuPush += (index - 0);
				menuPush = std::max(0, menuPush);
				//
				index = 0;
			}
			//
			if (jist_vert != 0) {
				UpdateMenuInfo();
			}
			//
			_cursor->Pos(Vector2(40, 32 + (16)* index));
			_pointer->visible = modsicle(runTime, 50) < 0.5f;
			//
			if (jist_affirm) {
				int n = menuPush + index;
				if (n == inventory.size()) { // *** We are on the "cancel" option...
					Cancel();
				}
				else {
					result = inventory[n]->item;
					Resolve();
				}
			}
			else if (jist_cancel) {
				Cancel();
			}
		};

	private:
		void _Deactivate() { Chooser_Item::Deactivate(); }
		Chooser_Item(ChooseContext Q) :
			ChooserClass(Q) {
			_back = new MenuBox(14, 9);
			_back->Translate(Vector2(32, 16));

			for (int i = 0; i < 4; i++) {
				_menuItem[i] = new TextArea("");
				_menuItem[i]->Translate(Vector2(48, 32 + 16 * i));
				_menuCount[i] = new TextArea("");
				_menuCount[i]->Translate(Vector2(112, 40 + 16 * i));

			}
			UpdateMenuInfo();
			//
			_cursor = new Actor();
			_cursor->AssignTexture("battle/menustuff.png", 48, 0, 8, 8);

			_pointer = new Actor();
			_pointer->Translate(Vector2(144, 88));
			_pointer->AssignTexture("battle/menustuff.png", 64, 0, 8, 8);
		}
		~Chooser_Item() {
			_back->Destroy();
			_back = nullptr;
			for (int i = 0; i < 4; i++) {
				_menuItem[i]->Destroy();
				_menuItem[i] = nullptr;
				_menuCount[i]->Destroy();
				_menuCount[i] = nullptr;
			}
			_cursor->Destroy();
			_cursor = nullptr;
			_pointer->Destroy();
			_pointer = nullptr;
		}
		static Chooser_Item* sInstance;

		int menuPush = 0;

		TiledTexture* _back;
		TextArea* _menuItem[4];
		TextArea* _menuCount[4];
		Actor* _cursor;
		Actor* _pointer;

		void UpdateMenuInfo() {
			Database* db = Database::Instance();

			std::vector<InventoryItem*> inventory = BattleManager::Instance()->GetInventory(PlayerSlot::PLAYER);

			for (int i = 0; i < 4; i++) {
				int n = menuPush + i;
				//
				if (n == inventory.size()) {
					_menuItem[i]->FeedString("CANCEL");
					_menuCount[i]->FeedString("");
				}
				else if (n > inventory.size()) {
					_menuItem[i]->FeedString("");
					_menuCount[i]->FeedString("");
				}
				else {
					_menuItem[i]->FeedString(db->GetPokeItemName(inventory[n]->item));
					if (false) { // ??? <-- Is it a key item...?
						_menuCount[i]->FeedString("");
					}
					else {
						_menuCount[i]->FeedString("x" + std::to_string(inventory[n]->quantity));
						// ??? <-- Note to self: The game uses a "Special" x for the quantity...
					}
				}
			}
		}
	};
	class Chooser_PokeBench : public ChooserClass {
	public:
		static Chooser_PokeBench* Activate(ChooseContext Q) {
			if (!sInstance) { sInstance = new Chooser_PokeBench(Q); }
			return sInstance;
		}
		static void Reactivate() {
			if (sInstance != nullptr) {
				sInstance->is_done = false;
				sInstance->is_cancel = false;
			}
		}
		static void Deactivate() {
			if (sInstance) {
				delete sInstance;
				sInstance = nullptr;
			}
		}

		int pokeIndex = -1;
		int result = -1;

		void Run() {
			if (is_done) {
				Chooser_Pokemon_Action* cpa = Chooser_Pokemon_Action::Activate(context);
				//
				cpa->Run();
				//
				if (cpa->is_cancel) {
					Chooser_Pokemon_Action::Deactivate();
					//
					Chooser_PokeBench::Reactivate();
					//
					result = -1;
				}
				else if (cpa->is_done) {
					switch (cpa->result)
					{
					case Chooser_Pokemon_Action::PokeActions::BattleSwitch:
						result = pokeIndex;
						break;
						// ??? <-- It gets messier from here as we continue to nest more and more...
					}
				}
				else {
					result = -1;
				}
				return;
			}

			GameSystem* gs = GameSystem::Instance();

			ChooserClass::Run();
			//
			int count = gs->data->bench.size();
			//
			index += 1 * jist_vert;
			index = roundabout(index, count);
			//
			if (jist_vert != 0) {
				UpdatePokemonBox();
			}
			//
			_cursor->Pos(Vector2(0, 8 + (16)* index));
			//
			if (jist_affirm) {
				pokeIndex = index;
				//
				Resolve();
			}
			else if (jist_cancel) {
				Cancel();
			}
		};

	private:
		MenuBox* _back; // = new MenuBox(20, 18);
		MenuBox* _message;
		TextArea* _messageText;
		Actor* _pokeIcons[GameSystem::MAXBENCHCOUNT];
		TextArea* _pokeNames[GameSystem::MAXBENCHCOUNT];
		HPGauge* _pokeGauges[GameSystem::MAXBENCHCOUNT];
		TextArea* _pokeLevels[GameSystem::MAXBENCHCOUNT];
		TextArea* _pokeHPs[GameSystem::MAXBENCHCOUNT];
		Actor* _cursor;


		void UpdatePokemonBox() {
			GameSystem* gs = GameSystem::Instance();
			for (int i = 0; i < gs->data->bench.size(); i++) {
				float animSpd;
				if (i == index) {
					animSpd = (5.0f / 120.0f) *(1+gs->data->bench[i]->GetVigorStatus())/5.0f;
				}
				else {
					animSpd = 0;
				}
				//
				_pokeIcons[i]->AssignData(0, 0, 16, 16, 2, animSpd, ANIM_DIR::HORIZONTAL);
			}
		}

		void _Deactivate() { Chooser_PokeBench::Deactivate(); }
		Chooser_PokeBench(ChooseContext Q) :
			ChooserClass(Q) {
			_back = new MenuBox(20, 18);
			_back->Translate(Vector2(-8, -8)); // *** A bit lazy, but meh. (lol)

			_message = new MenuBox(18, 4);
			_message->Translate(Vector2(0, 96));

			_messageText = new TextArea("Choose a POKeMON.");
			_messageText->Translate(Vector2(8, 112));

			GameSystem* gs = GameSystem::Instance();
			Database* db = Database::Instance();
			for (int i = 0; i < GameSystem::MAXBENCHCOUNT; i++) {
				Pokemon* poke;


				_pokeIcons[i] = new Actor();
				_pokeIcons[i]->Translate(Vector2(8, 0 + (16)*i));
				_pokeNames[i] = new TextArea("");
				_pokeNames[i]->Translate(Vector2(24, 0 + (16)*i));
				_pokeGauges[i] = new HPGauge(0.0f);
				_pokeGauges[i]->Translate(Vector2(32, 8 + (16)*i));
				_pokeLevels[i] = new TextArea("");
				_pokeLevels[i]->Translate(Vector2(104, 0 + (16)*i));
				_pokeHPs[i] = new TextArea("");
				_pokeHPs[i]->Translate(Vector2(104, 8 + (16)*i));
				//
				//
				if (i < gs->data->bench.size()) {
					poke = gs->data->bench[i];
					//
					_pokeIcons[i]->visible = true;
					_pokeIcons[i]->AssignTexture("pokemonIcons.png", 0, 0, 16, 16); // ??? <-- Same icon for everyone... For now.
					_pokeNames[i]->visible = true;
					_pokeNames[i]->FeedString(poke->GetName());
					_pokeGauges[i]->visible = true;
					_pokeGauges[i]->SetValue(poke->GetHP() / (1.0f*poke->GetStat(Stats::Health)));
					_pokeLevels[i]->visible = true;
					_pokeLevels[i]->FeedString("L" + std::to_string(poke->GetLevel())); // ??? <-- Wrong symbol for "L"...
					_pokeHPs[i]->visible = true;
					_pokeHPs[i]->FeedString(std::to_string(poke->GetHP()) + "/" + std::to_string(poke->GetStat(Stats::Health))); // ??? <-- Note to self: Pad these two 3 spaces per number...
				}
				else {
					_pokeIcons[i]->visible = false;
					_pokeNames[i]->visible = false;
					_pokeGauges[i]->visible = false;
					_pokeLevels[i]->visible = false;
					_pokeHPs[i]->visible = false;
				}
			}
			
			_cursor = new Actor();
			_cursor->AssignTexture("battle/menustuff.png", 48, 0, 8, 8);
			//
			UpdatePokemonBox();
		}
		~Chooser_PokeBench() {
			_back->Destroy(); // = new MenuBox(20, 18);
			_back = nullptr;
			_message->Destroy();
			_message = nullptr;
			_messageText->Destroy();
			_messageText = nullptr;
			for (int i = 0; i < GameSystem::MAXBENCHCOUNT; i++) {
				_pokeIcons[i]->Destroy();
				_pokeIcons[i] = nullptr;
				_pokeNames[i]->Destroy();
				_pokeNames[i] = nullptr;
				_pokeGauges[i]->Destroy();
				_pokeGauges[i] = nullptr;
				_pokeLevels[i]->Destroy();
				_pokeLevels[i] = nullptr;
				_pokeHPs[i]->Destroy();
				_pokeHPs[i] = nullptr;
			}
			_cursor->Destroy();
			_cursor = nullptr;
		}
		static Chooser_PokeBench* sInstance;
	};
	class Chooser_Pokemon_Action : public ChooserClass {
	public:
		enum class PokeActions {
			NA,
			Cancel,
			Stats,
			BattleSwitch, // *** Makes this your current battler.
			WorldSwitch, // *** Allows you to change their order on your bench.
			COUNT
		};
		std::string actionsStr[6] = { // ??? <-- This hard-coded length is gross...
			"",
			"CANCEL",
			"STATS",
			"SWITCH",
			"SWITCH",
			"",
		};
		// *** HEY! Order matters here! No touchy!
	public:
		static Chooser_Pokemon_Action* Activate(ChooseContext Q) {
			if (!sInstance) { sInstance = new Chooser_Pokemon_Action(Q); }
			return sInstance;
		}
		static void Reactivate() {
			if (sInstance != nullptr) {
				sInstance->is_done = false;
				sInstance->is_cancel = false;
			}
		}
		static void Deactivate() {
			if (sInstance) {
				delete sInstance;
				sInstance = nullptr;
			}
		}

		PokeActions result = PokeActions::NA;

		void Run() {
			ChooserClass::Run();
			//
			int count = actions.size(); // ??? <-- The number of NOT-VOID moves you have...
			//
			index += 1 * jist_vert;
			index = roundabout(index, count);
			//
			_cursor->Pos(Vector2(96, 96 + (16)* index));
			//
			if (jist_affirm) {
				if (actions[index] == PokeActions::Cancel) {
					Cancel();
				}
				else {
					result = actions[index];
					//
					Resolve();
				}
			}
			else if (jist_cancel) {
				Cancel();
			}
		};

	private:
		MenuBox* _back;
		std::vector<TextArea*> _allActions;
		Actor* _cursor;

		
		std::vector<PokeActions> actions;

		void _Deactivate() { Chooser_Pokemon_Action::Deactivate(); }
		Chooser_Pokemon_Action(ChooseContext Q) :
			ChooserClass(Q) {
			actions.push_back(PokeActions::Stats);
			actions.push_back(PokeActions::BattleSwitch);
			actions.push_back(PokeActions::Cancel);

			// -----------------------------------------------------
			
			_back = new MenuBox(7, (2 * actions.size()) - 1);
			_back->Translate(Vector2(88, 88));
			//
			for (int i = 0; i < actions.size(); i++) {
				TextArea* Q = new TextArea(actionsStr[static_cast<int>(actions[i])]);
				//
				Q->Translate(Vector2(104, 96 + (16)*i));
				//
				_allActions.push_back(Q);
			}

			_cursor = new Actor();
			_cursor->AssignTexture("battle/menustuff.png", 48, 0, 8, 8);
		}
		~Chooser_Pokemon_Action() {
			_back->Destroy();
			_back = nullptr;

			for (auto Q : _allActions) { Q->Destroy(); }
			_allActions.clear();

			_cursor->Destroy();
			_cursor = nullptr;
		}
		static Chooser_Pokemon_Action* sInstance;
	};



public:
	std::vector<BattleEvent*> events;
	void AddEvent(BattleEvent* Q) { events.push_back(Q); }
public:
	static BattleManager* Instance() { // <-- Public
		if (sInstance == nullptr) { sInstance = new BattleManager(); }
		return sInstance;
	}
	

	float SECOND;

	const int MESSAGEBOX_WIDTH = 160;
	const int MESSAGEBOX_HEIGHT = 48;
	int playerBattlerX = 8;
	int playerBattlerY = 144 - 48 - 64;
	int enemyBattlerX = 160 - 64 - 8;
	int enemyBattlerY = 0;

	Actor* playerSprite;
	Actor* enemySprite;
	TiledTexture* statusBorders;
	TiledTexture* playerPokeBalls;
	TiledTexture* enemyPokeBalls;
	TextArea* healthNumberDisplay;
	TextArea* enemyNameDisp;
	TextArea* enemyLevelDisp;
	TextArea* playerNameDisp;
	TextArea* playerLevelDisp;
	HPGauge* enemyHealthDisp;
	HPGauge* playerHealthDisp;
	BattleAnimation* battleAnim;


	Battler* playerBattler = nullptr;
	Battler* enemyBattler = nullptr;
	std::vector<Battler*> playerBench;
	std::vector<Battler*> enemyBench;


	int turnCount = 0;
	int phaseTime;
	int textTime;
	
	Phases currentPhase = Phases::Initialize;
	void ChangePhase(Phases phase);

	void Update();
	void Render();



	std::vector<InventoryItem*> playerInventory;
	std::vector<InventoryItem*> GetInventory(PlayerSlot who) {
		if (who == PlayerSlot::PLAYER) {
			return GameSystem::Instance()->GetInventory();
		}
		else if (who == PlayerSlot::OPPONENT) {
			return {};
			// ??? <-- Sometimes, opponents will have an inventory they will not hesitate to use! For now, it does not, though.
		}
	}

	BattleActions selectAction = BattleActions::NA;

	void Battle_Prepare(bool forced);
	void Battle_CalculateAction(PlayerSlot who);
	void Battle_InitiateCombat();
	void Battle_ConcludeCombat();
	//
	void Battle_DeclareVictory();
	void Battle_DeclareDefeat();
	BattleActions Battle_ChooseBattleAction(PlayerSlot who);
	void Battle_SelectBattleAction(PlayerSlot who, BattleActions ba);
	PokeMoves Battle_ChooseMove(PlayerSlot who);
	Battler* Battle_ChooseBattler(PlayerSlot who);
	std::pair<PokeItems, Battler*>* Battle_ChooseItem(PlayerSlot who);
	bool Battle_TryEscape(PlayerSlot who);
	//
	void Battle_QueueChoice(PlayerSlot who, BattleActions ba, PokeMoves pm = PokeMoves::NA, Battler* b = nullptr, PokeItems pi = PokeItems::NA, bool areRunning = false) {
		ChoiceLog* cl = new ChoiceLog(who, ba, turnCount, pm, b, pi, areRunning);
		//
		queuedChoices.push_back(cl);
	}
	//
	void Battle_PerformChoice(PlayerSlot who, BattleActions ba, PokeMoves pm = PokeMoves::NA, Battler* b = nullptr, PokeItems pi = PokeItems::NA, bool areRunning = false) {
		Battle_PerformChoice(new ChoiceLog(who, ba, turnCount, pm, b, pi, areRunning));
	}
	void Battle_PerformChoice(ChoiceLog* cl);
	void Battle_ResolveChoices();
	void Battle_PerformMove(ChoiceLog* Q);
	void Battle_Engage(PlayerSlot who, Battler* battler);
	void Battle_Disengage(PlayerSlot who);
	void Battle_PerformSwitch(PlayerSlot who, Battler* b);
	void Battle_PerformItem(ChoiceLog* Q);
	void Battle_DoEscape(PlayerSlot who);
	//
	void Battle_NoCanDo(std::string message);
	//
	ChoiceLog* _GetChoice(PlayerSlot who) {
		for (ChoiceLog* Q : allChoices) {
			if (Q->who == who && !Q->initiated) { return Q; }
		}
		//
		for (ChoiceLog* Q : queuedChoices) {
			if (Q->who == who && !Q->initiated) { return Q; }
		}
		//
		return nullptr;
	}
	bool Check_ReadyToCombat() {
		return (_GetChoice(PlayerSlot::PLAYER) != nullptr && _GetChoice(PlayerSlot::OPPONENT) != nullptr);
		//
		return false;
	}
	Battler* GetBattler(PlayerSlot who) {
		if (who == PlayerSlot::PLAYER) { return playerBattler; }
		else if (who == PlayerSlot::OPPONENT) { return enemyBattler; }
		//
		return nullptr;
	}

	bool animating = false;
	void Battle_Animate(ChoiceLog* Q);

	Actor* messageBar;
	TextArea* messageText;
	Actor* messagePointer;
	bool messageWait;
	bool messageOn;
	void Battle_Message(std::string str, bool wait);
	

private:
	BattleManager(); // <-- Construct, but PRIVATE
	static BattleManager* sInstance; // <-- Private
	void _Battle_RefreshSprites();
};


#endif
