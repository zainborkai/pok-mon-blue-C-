
#include "BattleManager.h"
#include "TiledTexture.h"
#include "TextArea.h"





void BattleAnimation::Run() {
	BattleManager* bm = BattleManager::Instance();
	if (!finished) {
		animTime++;
		//
		Actor* attacker = nullptr;
		Actor* defender = nullptr;
		int facing = 1;
		if (who == PlayerSlot::PLAYER) {
			attacker = bm->playerSprite;
			defender = bm->enemySprite;
			facing = 1;
		}
		else if (who == PlayerSlot::OPPONENT) {
			attacker = bm->enemySprite;
			defender = bm->playerSprite;
			facing = -1;
		}
		

		// *** UpdateHP values
		float rollRate = 10 / SECOND;
		float diff;
		Graphics* g = Graphics::Instance();
		//
		switch (animID) {
		case BattleAnimations::PokeballAppear:
			if (animTime > SECOND) {
				attacker->visible = true;
				//
				finished = true;
			}
			break;
		case BattleAnimations::ScreenShake:
			g->GamePos.y = 8 * (1 - longevity(animTime, 0, SECOND)) * sin(PI*modsicle(animTime, SECOND / 8));

			if (animTime > SECOND) {
				g->GamePos.x = 0;
				g->GamePos.y = 0;

				finished = true;
			}
			break;
		case BattleAnimations::ScreenShudder:
			g->GamePos.x = 8 * sin(PI*modsicle(animTime, SECOND / 8));

			if (animTime > SECOND / 1) {
				g->GamePos.x = 0;
				g->GamePos.y = 0;

				finished = true;
			}
			break;
		case BattleAnimations::PokemonInjured:
			defender->visible = modsicle(animTime, SECOND / 8) < 0.5f;
			//
			if (animTime > SECOND / 1) {
				defender->visible = true;
				
				finished = true;
			}
			break;
		case BattleAnimations::UpdateHP:
			if (who == PlayerSlot::PLAYER) {
				float eHP = bm->enemyBattler->GetHP();
				//
				diff = eHP - bm->enemyHP;
				//
				bm->enemyHP += std::min(abs(diff), rollRate) * signOf(diff);
				//
				bm->enemyHealthDisp->SetValue(bm->enemyHP / bm->enemyBattler->GetMaxHP());
				//
				if (abs(diff) < 1) {
					finished = true;
				}
			}
			else if (who == PlayerSlot::OPPONENT) {
				float pHP = bm->playerBattler->GetHP();
				//
				diff = pHP - bm->playerHP;
				//
				bm->playerHP += std::min(abs(diff), rollRate) * signOf(diff);
				//
				bm->playerHealthDisp->SetValue(bm->playerHP / bm->playerBattler->GetMaxHP());
				bm->healthNumberDisplay->FeedString(std::to_string((int)bm->playerHP) + "/" + std::to_string(bm->playerBattler->GetMaxHP()));
				//
				if (abs(diff) < 1) {
					finished = true;
				}
			}
			else {
				finished = true;
			}
			break;

		case BattleAnimations::Tackle:
			if (animTime < SECOND / 5) {
				attacker->Translate(Vector2(-30 / SECOND * facing, 0));
			}
			else if (animTime < SECOND / 5 * 2) {
				attacker->Translate(Vector2(+60 / SECOND * facing, 0));
			}
			//
			if (animTime > SECOND /5 *3) {
				finished = true;
			}
			break;
		}
		//
		if (finished) {
			// *** Reset the sprites (in case we really messed them up)
			bm->playerSprite->Pos(Vector2(bm->playerBattlerX, bm->playerBattlerY));
			bm->enemySprite->Pos(Vector2(bm->enemyBattlerX, bm->enemyBattlerY));
		}
	}
}





BattleManager* BattleManager::sInstance = nullptr;


std::vector<BattleManager::ChooserClass*> BattleManager::ChooserClass::allChoosers;
BattleManager::Chooser_Action* BattleManager::Chooser_Action::sInstance = nullptr;
BattleManager::Chooser_Move* BattleManager::Chooser_Move::sInstance = nullptr;
BattleManager::Chooser_Item* BattleManager::Chooser_Item::sInstance = nullptr;
BattleManager::Chooser_PokeBench* BattleManager::Chooser_PokeBench::sInstance = nullptr;
BattleManager::Chooser_Pokemon_Action* BattleManager::Chooser_Pokemon_Action::sInstance = nullptr;

BattleManager::BattleManager() : Actor() {
	Database::Instance(); // ??? <-- To ensure that it is constructed!

	GameSystem* gs = GameSystem::Instance();
	
	// *** Player Bench
	for (int i = 0; i < gs->data->bench.size(); i++) {
		playerBench.push_back(new Battler(gs->data->bench[i]));
	}
	//
	Battler* bat;
	Pokemon* poke;
	// --------------
	// *** Opponent Bench
	// ??? <-- ... Hard-coded atm...
	bat = new Battler(new Pokemon(121));
	enemyBench.push_back(bat);
	//
	bat = new Battler(new Pokemon(46));
	enemyBench.push_back(bat);
	//
	bat = new Battler(new Pokemon(4));
	enemyBench.push_back(bat);
	//===================================================



	SECOND = GameManager::Instance()->GetFrameRate();
	
	
	playerSprite = new Actor();
	enemySprite = new Actor();
	messageBar = new Actor();
	messagePointer = new Actor();
	//
	messageBar->AssignTexture("battle/messageBar_blank.png");
	messagePointer->AssignTexture("battle/menustuff.png", 64, 0, 8, 8);
	messagePointer->visible = false;
	//
	playerSprite->Scale(Vector2(1, 1));
	enemySprite->Scale(Vector2(1, 1));
	//
	playerSprite->Translate(Vector2(playerBattlerX, playerBattlerY));
	enemySprite->Translate(Vector2(enemyBattlerX, enemyBattlerY));
	messageBar->Translate(Vector2(0, 144 - 48));
	messagePointer->Translate(Vector2(144, 128));


	TiledTexture* Q = new TiledTexture("PokemonSpriteSheet.png");
	// Q->Add(0, 0, 0, 0, 64, 64, 1, 3);
	// Q->Add(16, 16, 0, 64, 64, 64);
	// Q->Add(32, 32, 0, 128, 64, 64, 10, 1);

	
	//
	messageText = new TextArea("");
	messageText->textSpeed = 5;
	messageText->Translate(Vector2(8, 112));
	// --------------------------------------------------------------------------------------------------
	statusBorders = new TiledTexture("battle/status_borders.png");
	// *** Player borders
	statusBorders->Add(72, 88, 0 * 8, 0, 8, 8);
	statusBorders->Add(80, 88, 5 * 8, 0, 8, 8, 8, 1);
	statusBorders->Add(144, 88, 2 * 8, 0, 8, 8);
	statusBorders->Add(144, 80, 4 * 8, 0, 8, 8);
	// *** Opponent borders
	statusBorders->Add(8, 16, 4 * 8, 0, 8, 8);
	statusBorders->Add(8, 24, 3 * 8, 0, 8, 8);
	statusBorders->Add(16, 24, 5 * 8, 0, 8, 8, 8, 1);
	statusBorders->Add(16 +(8*8), 24, 1 * 8, 0, 8, 8);
	// --------------------------------------------------------------------------------------------------
	playerPokeBalls = new TiledTexture("battle/pokeball_states.png");
	enemyPokeBalls = new TiledTexture("battle/pokeball_states.png");
	healthNumberDisplay = new TextArea(""); // ??? <-- BAD!
	healthNumberDisplay->textSpeed = 0;
	healthNumberDisplay->Translate(Vector2(88, 80));

	enemyNameDisp = new TextArea("");
	enemyNameDisp->Translate(Vector2(8, 0));
	enemyLevelDisp = new TextArea("");
	enemyLevelDisp->Translate(Vector2(8+24, 0+8));
	playerNameDisp = new TextArea("");
	playerNameDisp->Translate(Vector2(80, 56));
	playerLevelDisp = new TextArea("");
	playerLevelDisp->Translate(Vector2(80+32, 56+8));

	enemyHealthDisp = new HPGauge(0.0f);
	enemyHealthDisp->Translate(Vector2(16, 16));
	playerHealthDisp = new HPGauge(0.0f, true);
	playerHealthDisp->Translate(Vector2(80, 72));
	// *** Player pokemon
	int locatex, locatey;
	int status;
	Battler* battler;
	battler = playerBattler;
	//
	locatex = 88;
	locatey = 80;
	for (int i = 0; i < 6; i++) {
		if (i >= playerBench.size()) {
			status = 0; // Absent
		}
		else {

			if (playerBench[i]->_pokeData->statusEff != StatusEffects::None) {
				status = 2; // Sick
			}
			else {
				status = 1; // Fine
			}
		}
		//
		playerPokeBalls->Add(locatex + i * 8, locatey, status * 8, 0, 8, 8);
	}

	locatex = 24;
	locatey = 16;
	for (int i = 0; i < 6; i++) {
		if (i >= enemyBench.size()) {
			status = 0; // Absent
		}
		else {

			if (enemyBench[i]->_pokeData->statusEff != StatusEffects::None) {
				status = 2; // Sick
			}
			else {
				status = 1; // Fine
			}
		}
		//
		enemyPokeBalls->Add(locatex + i * 8, locatey, status * 8, 0, 8, 8);
	}





	_Battle_RefreshSprites();
}


void BattleManager::ChangePhase(Phases phase) {
	// Phase is ending...
	switch (currentPhase) {
	case Phases::BattleFirst:
		break;
	}
	//
	phaseTime = 0;
	currentPhase = phase;
	//
	// Phase is beginning...
	switch (currentPhase) {
	case Phases::BattlePreparing:
		Battle_Prepare(true);
		//
		messageText->FeedString("");
		break;
	}
}


void BattleManager::Update() {
	
	if (playerBattler != nullptr) {
		// healthNumberDisplay->FeedString(std::to_string(playerBattler->GetStat(Stats::Health) - playerBattler->_pokeData->damage) + "/" + std::to_string(playerBattler->GetStat(Stats::Health)));
	}



	Phases lastPhase = currentPhase;
	//
	int messageDuration;
	if (messageOn) {
		if (messageText->textPercent < 1.0f) {
			messagePointer->visible = false;
		}
		else {
			messagePointer->visible = (messageWait && modsicle(messageText->textTime, 50) < 0.5f);
			//
			InputManager* im = InputManager::Instance();
			if (im->KeyPressed(GameSystem::KEY_AFFIRM) || (!messageWait && messageText->textTime > messageText->textDuration + SECOND)) {
				messagePointer->visible = false;
				//
				messageOn = false;
			}
		}
	}
	else if (battleAnim != nullptr) {
		battleAnim->Run();
		
		// *** We wait... Until it's done.
		if (battleAnim->finished) {
			battleAnim->Destroy();
			battleAnim = nullptr;
		}
	}
	else if (events.size() > 0) {
		BattleEvent* Q = events[0];
		switch (Q->type) {
		case BattleEvents::BattleText:
			messageOn = true;
			messageWait = false;
			messageText->FeedString(Q->str, 18, 16);
			break;
		case BattleEvents::ReadMessage:
			messageOn = true;
			messageWait = true;
			messageText->FeedString(Q->str, 18, 16);
			break;
		case BattleEvents::Animation:
			battleAnim = new BattleAnimation(static_cast<BattleAnimations>((int)Q->num), (Q->str == "PLAYER" ? PlayerSlot::PLAYER : PlayerSlot::OPPONENT));
			break;
		}
		//
		events.erase(events.begin() + 0);
	}
	else {
		bool isBusy;

		switch (currentPhase) {
		case Phases::Initialize:
			ChangePhase(Phases::Introduction); // Phases::Introduction
			break;
			//
		case Phases::Introduction:
			playerSprite->Pos(Vector2(playerBattlerX - 80 * (1 - longevity(phaseTime, 0, SECOND*1.5)), playerBattlerY));
			enemySprite->Pos(Vector2(enemyBattlerX + 80 * (1 - longevity(phaseTime, 0, SECOND*1.5)), enemyBattlerY));

			if (phaseTime > SECOND * 2) {
				ChangePhase(Phases::IntroMessage);
			}
			break;
		case Phases::IntroMessage:
			if (phaseTime == 0) {
				
				Battle_Message("GARY wants to fight!", true);
			}
			else {
				ChangePhase(Phases::IntroEnd);
			}
			break;
		case Phases::IntroEnd:
			playerSprite->Pos(Vector2(playerBattlerX - 80 * (longevity(phaseTime, 0, SECOND / 2)), playerBattlerY));
			enemySprite->Pos(Vector2(enemyBattlerX + 80 * (longevity(phaseTime, 0, SECOND / 2)), enemyBattlerY));

			if (phaseTime > SECOND) {
				playerSprite->visible = false;
				enemySprite->visible = false;
				//
				ChangePhase(Phases::BattleFirst);
			}
			break;
			//
		case Phases::BattleFirst:
			playerSprite->Pos(Vector2(playerBattlerX, playerBattlerY));
			enemySprite->Pos(Vector2(enemyBattlerX, enemyBattlerY));
			//
			turnCount++;
			selectAction = BattleActions::NA;
			//
			ChangePhase(Phases::BattlePreparing);
			break;
		case Phases::BattlePreparing:
			Battle_CalculateAction(PlayerSlot::OPPONENT); // *** Just to prove I'm not cheating, the AI will come up with an action BEFORE you. (:3)
			// ??? <-- ... Although, it seems the opponent is technically supposed to decide AFTER you (since you can switch/run/item before it can)
			Battle_CalculateAction(PlayerSlot::PLAYER);
			//
			if (Check_ReadyToCombat()) {
				ChooserClass::DeactivateAll();
				//
				ChangePhase(Phases::BattleResolve);
			}
			break;

		case Phases::BattleResolve:
			Battle_InitiateCombat();
			//
			Battle_ConcludeCombat();
			//
			ChangePhase(Phases::BattleAnimate);
			break;

		case Phases::BattleAnimate:
			// ??? <-- This is the cool part where we "animate" all the stuff that happened when combat resolved.
			isBusy = false;

			
			for (int i = 0; i < allChoices.size(); i++) {
				if (!allChoices[i]->animated) {
					Battle_Animate(allChoices[i]);
					//
					allChoices[i]->animated = true;
					//
					isBusy = true;
					break;
				}
			}
			//
			if (!isBusy) {
				ChangePhase(Phases::BattleLast);
			}
			break;

		case Phases::BattleLast:
			// ??? <-- Did we win? Did we lose?
			//
			// *** ... If no one has won, we go to the next turn of battle!


			//
			ChangePhase(Phases::BattleFirst);
		}
	}
	//
	if (currentPhase != lastPhase) { return; }


	phaseTime++;
}
void BattleManager::Render() {

}


void BattleManager::Battle_Prepare(bool forced) {
	
	if (enemyBattler != nullptr && enemyBattler->_pokeData->IsDead()) {
		Battle_Message("Enemy "+ enemyBattler->_pokeData->GetName() + " fainted!", true);
		//
		Battle_Disengage(PlayerSlot::OPPONENT);
	}
	//
	if (playerBattler != nullptr && playerBattler->_pokeData->IsDead()) {
		Battle_Message(enemyBattler->_pokeData->GetName() + " fainted!", true);
		//
		Battle_Disengage(PlayerSlot::PLAYER);
	}
	
	
	
	std::vector<Battler*> availableBattlers;
	
	if (playerBattler == nullptr) {
		availableBattlers.clear();
		for (int i = 0; i < playerBench.size(); i++) {
			if (!playerBench[i]->_pokeData->IsDead()) {
				availableBattlers.push_back(playerBench[i]);
			}
		}
		//
		if (availableBattlers.size() == 0) {
			Battle_DeclareDefeat();
		}
		else if (availableBattlers.size() == 1 || forced) {
			Battle_Engage(PlayerSlot::PLAYER, availableBattlers[0]);
		}
		else {
			Battler* battler = Battle_ChooseBattler(PlayerSlot::PLAYER);
			if (battler == nullptr) {
				// ??? <--
			}
			else {
				Battle_Engage(PlayerSlot::PLAYER, battler);
			}
		}

	}
	//
	if (enemyBattler == nullptr) {
		availableBattlers.clear();
		for (int i = 0; i < enemyBench.size(); i++) {
			if (!enemyBench[i]->_pokeData->IsDead()) {
				availableBattlers.push_back(enemyBench[i]);
			}
		}
		//
		if (availableBattlers.size() == 0) {
			Battle_DeclareVictory();
		}
		else if (availableBattlers.size() == 1 || forced) {
			Battle_Engage(PlayerSlot::OPPONENT, availableBattlers[0]);
		}
		else {
			Battler* battler = Battle_ChooseBattler(PlayerSlot::OPPONENT);
			if (battler == nullptr) {
				// ??? <--
			}
			else {
				Battle_Engage(PlayerSlot::OPPONENT, battler);
			}
		}

	}
}

void BattleManager::Battle_CalculateAction(PlayerSlot who) {
	if (_GetChoice(who) != nullptr) {
		return;
	}


	selectAction = Battle_ChooseBattleAction(who);
	//
	Battle_SelectBattleAction(who, selectAction);
}

void BattleManager::Battle_PerformChoice(ChoiceLog* cl) {
	allChoices.push_back(cl);
}
void BattleManager::Battle_ResolveChoices() {
	for (int i = 0; i < allChoices.size(); i++) {
		ChoiceLog* Q = allChoices[i];
		if (!Q->initiated) {
			switch (Q->action) {
			case BattleActions::Attack:
				Battle_PerformMove(Q);
				break;
			case BattleActions::Switch:
				Battle_PerformSwitch(Q->who, Q->battler);
				break;
			case BattleActions::Item:
				Battle_PerformItem(Q);
				break;
			case BattleActions::Run:
				if (Battle_TryEscape(Q->who)) {
					Battle_DoEscape(Q->who);
				}
				else {
					Battle_NoCanDo("Can't run away!");
				}
				break;
			}
			//
			Q->initiated = true;
			//
			//
			// ??? <-- We want to check if the battle is still valid at this point!
			// (For example, if a pokemon dies from an attack, we have to interrupt this in order to let that player switch!)
			// (We also need to "invalidate" their action if we end up killing the thing that's trying to attack)
		}
	}
	//
	queuedChoices.clear();
}


void BattleManager::Battle_InitiateCombat() {
	ChoiceLog* playerChoice = _GetChoice(PlayerSlot::PLAYER);
	ChoiceLog* enemyChoice = _GetChoice(PlayerSlot::OPPONENT);
	//
	if (playerChoice->action == BattleActions::Attack && playerChoice->action != BattleActions::Attack) {
		// *** Enemy goes first!
		Battle_PerformChoice(enemyChoice);
		//
		Battle_PerformChoice(playerChoice);
	}
	else if (playerChoice->action != BattleActions::Attack && playerChoice->action == BattleActions::Attack) {
		// *** Player goes first!
		Battle_PerformChoice(playerChoice);
		//
		Battle_PerformChoice(enemyChoice);
	}
	else if (playerChoice->action != BattleActions::Attack && playerChoice->action != BattleActions::Attack) {
		// *** Player still always goes first!
		Battle_PerformChoice(playerChoice);
		//
		Battle_PerformChoice(enemyChoice);
	}
	else {
		if (playerBattler->GetAdjustedStat(Stats::Speed) > enemyBattler->GetAdjustedStat(Stats::Speed)) {
			Battle_PerformChoice(playerChoice);
			//
			Battle_PerformChoice(enemyChoice);
		}
		else if (playerBattler->GetAdjustedStat(Stats::Speed) < enemyBattler->GetAdjustedStat(Stats::Speed)) {
			Battle_PerformChoice(enemyChoice);
			//
			Battle_PerformChoice(playerChoice);
		}
		else {
			if (FlipACoin()) {
				Battle_PerformChoice(playerChoice);
				//
				Battle_PerformChoice(enemyChoice);
			}
			else {
				Battle_PerformChoice(enemyChoice);
				//
				Battle_PerformChoice(playerChoice);
			}
		}
	}
	//
	//
	Battle_ResolveChoices();
}
void BattleManager::Battle_ConcludeCombat() {
	// *** A bunch of crap that happens at end of combat (like sandstorms or poison or whatever)
	// ... Too lazy to do that now.
}

void BattleManager::Battle_DeclareVictory() {
	ChangePhase(Phases::Victory);
}
void BattleManager::Battle_DeclareDefeat() {
	ChangePhase(Phases::Defeat);
}
void BattleManager::Battle_Engage(PlayerSlot who, Battler* battler) {
	Battle_PerformChoice(who, BattleActions::Switch, PokeMoves::NA, battler, PokeItems::NA, false);
}
void BattleManager::Battle_Disengage(PlayerSlot who) {
	Battle_PerformChoice(who, BattleActions::Switch, PokeMoves::NA, nullptr, PokeItems::NA, false);
}


BattleActions BattleManager::Battle_ChooseBattleAction(PlayerSlot who) {
	if (who == PlayerSlot::PLAYER) {
		Chooser_Action* ca = Chooser_Action::Activate(ChooserClass::ChooseContext::None);
		//
		ca->Run();
		//
		if (ca->is_done) {
			auto ret = ca->result;
			//
			return ret;
		}
		else {
			return BattleActions::NA;
		}
	}
	else if (who == PlayerSlot::OPPONENT) {
		return BattleActions::Attack; // ??? <-- For now.
	}
	else {
		return BattleActions::NA;
	}
}
void BattleManager::Battle_SelectBattleAction(PlayerSlot who, BattleActions ba) {
	PokeMoves pm;
	std::pair<PokeItems, Battler*>* pi;
	Battler* b;
	
	// ??? <--
	switch (ba) {
	case BattleActions::Attack:
		pm = Battle_ChooseMove(who);
		if (pm != PokeMoves::NA) {
			Battle_QueueChoice(who, ba, pm, nullptr, PokeItems::NA, false);
			selectAction = BattleActions::NA; // ??? <-- A bit cheesy, but eh.
		}
		break;
	case BattleActions::Switch:
		b = Battle_ChooseBattler(who);
		if (b != nullptr) {
			Battle_QueueChoice(who, ba, PokeMoves::NA, b, PokeItems::NA, false);
			selectAction = BattleActions::NA; // ??? <-- A bit cheesy, but eh.
		}
		break;
	case BattleActions::Item:
		pi = Battle_ChooseItem(who);
		if (pi != nullptr) {
			Battle_QueueChoice(who, ba, PokeMoves::NA, pi->second, pi->first, false);
			selectAction = BattleActions::NA; // ??? <-- A bit cheesy, but eh.
		}
		break;
	case BattleActions::Run:
		Battle_QueueChoice(who, ba, PokeMoves::NA, nullptr, PokeItems::NA, true);
		selectAction = BattleActions::NA; // ??? <-- A bit cheesy, but eh.
		break;
	}
}
PokeMoves BattleManager::Battle_ChooseMove(PlayerSlot who) {
	if (who == PlayerSlot::PLAYER) {
		Chooser_Move* cm = Chooser_Move::Activate(ChooserClass::ChooseContext::None);
		//
		cm->Run();
		//
		if (cm->is_cancel) {
			Chooser_Move::Deactivate();
			//
			Chooser_Action::Reactivate();
			//
			return PokeMoves::NA;
		}
		else if (cm->is_done) {
			return playerBattler->_pokeData->moves[cm->result];
		}
		else {
			return PokeMoves::NA;
		}
	}
	else if (who == PlayerSlot::OPPONENT) {
		return PokeMoves::Tackle; // ??? <-- For now.
	}
	else {
		return PokeMoves::NA;
	}
}
void BattleManager::Battle_PerformMove(ChoiceLog* Q) {
	PlayerSlot who = Q->who;
	PokeMoves move = Q->move;
	//
	Battler* attacker = nullptr;
	Battler* defender = nullptr;
	if (who == PlayerSlot::PLAYER) { attacker = playerBattler; defender = enemyBattler;	}
	else if (who == PlayerSlot::OPPONENT) { attacker = enemyBattler; defender = playerBattler; }
	//
	Database* db = Database::Instance();
	switch (move) {
	case PokeMoves::Tackle:
		Q->result = attacker->DoAttack(defender, db->GetPokeMovePower(move), db->GetPokeMoveAccuracy(move), Q->hitLuck, Q->crtLuck, Q->vryLuck);
		break;
	}
	//
	switch (Q->result) {
	case CombatResult::Hit:
	case CombatResult::Critical:
		Q->efficacy = db->Check_TypeEfficacy(defender->_pokeData->GetPokeID(), db->GetPokeMoveTyping(move));
		// *** Adjust the efficacy so that we know to mention that it was super effective!
		break;
	}
}
BattleManager::Battler* BattleManager::Battle_ChooseBattler(PlayerSlot who) {
	if (who == PlayerSlot::PLAYER) {
		Chooser_PokeBench* cpb = Chooser_PokeBench::Activate(ChooserClass::ChooseContext::Switching);
		//
		cpb->Run();
		//
		if (cpb->is_cancel) {
			Chooser_PokeBench::Deactivate();
			//
			Chooser_Action::Reactivate();
			//
			return nullptr;
		}
		else if (cpb->is_done) {
			int ret = cpb->result; // ??? <-- use the index to get the battler's move.
			//
			if (ret >= 0) {
				return playerBench[ret];
			}
			else {
				return nullptr;
			}
		}
		else {
			return nullptr;
		}
	}
	else if (who == PlayerSlot::OPPONENT) {
		return enemyBench[0]; // ??? <-- For now.
	}
	else {
		return nullptr;
	}
}
void BattleManager::Battle_PerformSwitch(PlayerSlot who, Battler* b) {
	if (who == PlayerSlot::PLAYER) {
		playerBattler = b;
	}
	else if (who == PlayerSlot::OPPONENT) {
		enemyBattler = b;
	}
	//
	_Battle_RefreshSprites();
}
std::pair<PokeItems, BattleManager::Battler*>* BattleManager::Battle_ChooseItem(PlayerSlot who) {
	if (who == PlayerSlot::PLAYER) {
		Chooser_Item* ci = Chooser_Item::Activate(ChooserClass::ChooseContext::BattleIteming);
		//
		ci->Run();
		//
		if (ci->is_cancel) {
			Chooser_Item::Deactivate();
			//
			Chooser_Action::Reactivate();
			//
			return nullptr;
		}
		else if (ci->is_done) {
			if (true) { // ??? <-- Is this item inappropriate right now??
				Battle_NoCanDo("OAK: <player>! This isn't the time to use that!");
				//
				Chooser_Item::Reactivate();
			}
			else if (true) { // ??? <-- Does this item require a target?
				Chooser_PokeBench* cpb = Chooser_PokeBench::Activate(ChooserClass::ChooseContext::BattleIteming);
				if (cpb->is_cancel) {
					Chooser_PokeBench::Deactivate();
					//
					Chooser_Item::Reactivate();
					//
					return nullptr;
				}
				else if (ci->is_done) {
					return new std::pair<PokeItems, Battler*>(ci->result, playerBench[cpb->result]);
				}
				else {
					return nullptr;
				}
			}
			else {
				return new std::pair<PokeItems, Battler*>(ci->result, nullptr);
			}
		}
		
		return nullptr;
	}
	else if (who == PlayerSlot::OPPONENT) {
		return new std::pair<PokeItems, Battler*>(PokeItems::Potion, nullptr); // ??? <-- For now.
	}
	else {
		return nullptr;
	}
}
void BattleManager::Battle_PerformItem(ChoiceLog* Q) {
	PlayerSlot who = Q->who;
	PokeItems item = Q->item;
	Battler* battler = Q->battler;
	
	if (battler == nullptr) {
		if (who == PlayerSlot::PLAYER) { battler = playerBattler; }
		else if (who == PlayerSlot::OPPONENT) { battler = enemyBattler; }
	}
	//
	// ??? <-- Activate the item!
}
//
void BattleManager::Battle_NoCanDo(std::string message) {
	Battle_Message(message, true);
}
bool BattleManager::Battle_TryEscape(PlayerSlot who) {
	return false; // ??? <--
}
void BattleManager::Battle_DoEscape(PlayerSlot who) {

}


void BattleManager::_Battle_RefreshSprites() {
	int pokeID;
	if (playerBattler == nullptr) {
		playerSprite->AssignTexture("battle/trainer_player_back.png", 0, 0, 64, 64);
	}
	else {
		pokeID = playerBattler->_pokeData->GetPokeID();
		playerSprite->AssignTexture("battle/pokemon_back.png", 64 * ((pokeID - 1) % 16), 64 * ((pokeID - 1) / 16), 64, 64);
	}
	//
	if (enemyBattler == nullptr) {
		enemySprite->AssignTexture("battle/trainer_gary_front.png", 0, 0, 64, 64);
	}
	else {
		pokeID = enemyBattler->_pokeData->GetPokeID();
		enemySprite->AssignTexture("battle/pokemon_front.png", 64 * ((pokeID - 1) % 16), 64 * ((pokeID - 1) / 16), 64, 64);
	}


	if (playerBattler == nullptr) {
		playerPokeBalls->visible = true;
		healthNumberDisplay->visible = false;
		playerHealthDisp->visible = false;
		playerNameDisp->visible = false;
		playerLevelDisp->visible = false;
	}
	else {
		playerPokeBalls->visible = false;
		healthNumberDisplay->visible = true;
		playerHealthDisp->visible = true;
		playerNameDisp->visible = true;
		playerLevelDisp->visible = true;

		playerNameDisp->FeedString(playerBattler->_pokeData->GetName());
		playerLevelDisp->FeedString("L" + std::to_string(playerBattler->_pokeData->GetLevel()));
		playerHP = playerBattler->GetHP();
		//
		playerHealthDisp->SetValue(playerHP/playerBattler->GetMaxHP());
		healthNumberDisplay->FeedString(std::to_string((int)playerHP) + "/" + std::to_string(playerBattler->GetMaxHP()));
	}
	
	if (enemyBattler == nullptr) {
		enemyPokeBalls->visible = true;
		enemyHealthDisp->visible = false;
		enemyNameDisp->visible = false;
		enemyLevelDisp->visible = false;
	}
	else {
		enemyPokeBalls->visible = false;
		enemyHealthDisp->visible = true;
		enemyNameDisp->visible = true;
		enemyLevelDisp->visible = true;

		enemyNameDisp->FeedString(enemyBattler->_pokeData->GetName());
		enemyLevelDisp->FeedString("L" + std::to_string(enemyBattler->_pokeData->GetLevel()));
		enemyHP = enemyBattler->GetHP();
		//
		enemyHealthDisp->SetValue(enemyHP / enemyBattler->GetMaxHP());
	}
}



void BattleManager::Battle_Animate(ChoiceLog* Q) {
	animating = true;
	//
	Database* db = Database::Instance();

	switch (Q->action) {
	case BattleActions::Attack:
		if (Q->who == PlayerSlot::PLAYER) {
			Battle_Message(GetBattler(Q->who)->_pokeData->GetName() + " used " + ToUppercase(db->GetPokeMoveName(Q->move)) + "!", false);
		}
		else if (Q->who == PlayerSlot::OPPONENT) {
			Battle_Message("Enemy "+ GetBattler(Q->who)->_pokeData->GetName() + " used " + ToUppercase(db->GetPokeMoveName(Q->move))+"!", false);
		}
		//
		switch (Q->result) {
		case CombatResult::Worked:
		case CombatResult::Hit:
		case CombatResult::Critical:
			AddEvent(new BattleEvent(BattleEvents::Animation, BattleAnimations::Tackle, Q->who));
			//
			if (Q->who == PlayerSlot::PLAYER) {
				AddEvent(new BattleEvent(BattleEvents::Animation, BattleAnimations::PokemonInjured, Q->who));
			}
			else {
				AddEvent(new BattleEvent(BattleEvents::Animation, BattleAnimations::ScreenShake, Q->who));
			}
			//
			AddEvent(new BattleEvent(BattleEvents::Animation, BattleAnimations::UpdateHP, Q->who));
			break;
		case CombatResult::Missed:
			Battle_Message("The move missed.", true); // ??? <-- Wrong text...
			break;
		case CombatResult::Redundant:
			Battle_Message("It didn't work on " + Q->battler->_pokeData->GetName() + ".", true); // ??? <-- Wrong text...
			break;
		}
		//
		if (Q->result == CombatResult::Critical) {
			Battle_Message("Critical hit!", true);
		}
		//
		switch (Q->result) {
		case CombatResult::Worked:
		case CombatResult::Hit:
		case CombatResult::Critical:
			if (Q->efficacy == TypeEfficacy::Resistant) {
				Battle_Message("It's not very effective...", false);
			}
			else if (Q->efficacy == TypeEfficacy::Immune) {
				Battle_Message("It has no effect on "+Q->battler->_pokeData->GetName() +".", false);
			}
			else if (Q->efficacy == TypeEfficacy::Effective) {
				Battle_Message("It's super effective!", false);
			}
			break;;
		}
		

		animating = false;
		break;
	case BattleActions::Item:
		animating = false;
		break;
	case BattleActions::Switch:
		if (Q->who == PlayerSlot::PLAYER) {
			if (playerBattler != nullptr) {
				Battle_Message("Go! " + GetBattler(Q->who)->_pokeData->GetName() + "!", false);
				//
				battleAnim = new BattleAnimation(BattleAnimations::PokeballAppear, Q->who);
			}
		}
		else if (Q->who == PlayerSlot::OPPONENT) {
			if (enemyBattler != nullptr) {
				Battle_Message("<ENEMY> sent out " + GetBattler(Q->who)->_pokeData->GetName() + "!", false);
				//
				battleAnim = new BattleAnimation(BattleAnimations::PokeballAppear, Q->who);
			}
		}
		// ??? <--

		
		animating = false;
		break;
	case BattleActions::Run:
		animating = false;
		break;
	}
}

void BattleManager::Battle_Message(std::string str, bool wait) {
	AddEvent(new BattleEvent((wait ? BattleEvents::ReadMessage : BattleEvents::BattleText), str));
}
