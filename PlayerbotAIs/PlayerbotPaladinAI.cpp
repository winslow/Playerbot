    /* 
	Name	: PlayerbotPaladinAI.cpp
    Complete: maybe around 24% :D
    Author	: Natsukawa
	Version : 0.20
    */

#include "PlayerbotPaladinAI.h"

class PlayerbotAI;
PlayerbotPaladinAI::PlayerbotPaladinAI(Player* const master, Player* const bot, PlayerbotAI* const ai): PlayerbotClassAI(master, bot, ai) {
	
	RETRIBUTION_AURA			= ai->getSpellId("retribution aura");
	SHADOW_RESISTANCE_AURA		= ai->getSpellId("shadow resistance aura");
	DEVOTION_AURA				= ai->getSpellId("devotion aura");
	FIRE_RESISTANCE_AURA		= ai->getSpellId("fire resistance aura");
	FROST_RESISTANCE_AURA		= ai->getSpellId("frost resistance aura");
	CONCENTRATION_AURA			= ai->getSpellId("concentration aura");
	CRUSADER_AURA				= ai->getSpellId("crusader aura");
	SEAL_OF_COMMAND				= 20375; //For some reason getSpellId was not working. Replaced with spell id
	JUDGEMENT_OF_LIGHT			= ai->getSpellId("judgement of light");
	FLASH_OF_LIGHT				= ai->getSpellId("flash of light");
	HOLY_LIGHT					= ai->getSpellId("holy light");
	DIVINE_SHIELD				= 642; // ai->getSpellId("divine shield");
	HAND_OF_PROTECTION			= 10278;
	BLESSING_OF_MIGHT			= ai->getSpellId("blessing of might");
	GREATER_BLESSING_OF_MIGHT	= ai->getSpellId("greater blessing of might");
	BLESSING_OF_WISDOM			= ai->getSpellId("blessing of wisdom");
	GREATER_BLESSING_OF_WISDOM	= ai->getSpellId("greater blessing of wisdom");
	BLESSING_OF_KINGS			= ai->getSpellId("blessing of kings");
	GREATER_BLESSING_OF_KINGS	= ai->getSpellId("greater blessing of kings");
	HAMMER_OF_JUSTICE			= ai->getSpellId("hammer of justice");
	RIGHTEOUS_FURY				= ai->getSpellId("righteous fury");
	CONSECRATION				= ai->getSpellId("consecration");
	AVENGING_WRATH				= ai->getSpellId("avenging wrath");
	HAMMER_OF_WRATH				= ai->getSpellId("hammer of wrath");
	DEFENSIVE_STANCE			= 71; //Deff Stance
	BERSERKER_STANCE			= 2458; //Ber Stance
	BATTLE_STANCE				= 2457; //Bat Stance
}

PlayerbotPaladinAI::~PlayerbotPaladinAI() {}


void PlayerbotPaladinAI::DoNextCombatManeuver(Unit *pTarget){
	PlayerbotAI* ai = GetAI();
	if (!ai) return;
	switch (ai->GetScenarioType()) {
		
		case SCENARIO_DUEL:

				if (HAMMER_OF_JUSTICE > 0) {
						ai->CastSpell(HAMMER_OF_JUSTICE);
				}
			return;
	}
  Player *m_bot = GetPlayerBot();
	if( !m_bot->HasInArc(M_PI, pTarget)) {
	    m_bot->SetInFront(pTarget);
	}
	//Shield master if low hp.
	uint32 masterHP = GetMaster()->GetHealth()*100 / GetMaster()->GetMaxHealth();

	if (GetMaster()->isAlive()) {
		if (masterHP < 25 && HAND_OF_PROTECTION > 0 && !GetMaster()->HasAura(HAND_OF_PROTECTION, 0)) {
				ai->CastSpell(HAND_OF_PROTECTION, *(GetMaster()));
		}
	}
	if (SHADOW_RESISTANCE_AURA > 0) {
		(!m_bot->HasAura(SHADOW_RESISTANCE_AURA, 0) && pTarget->getClass() == CLASS_WARLOCK && GetAI()->CastSpell (SHADOW_RESISTANCE_AURA, *m_bot));
	}

	if (DEVOTION_AURA > 0) {
		(!m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_WARRIOR && GetAI()->CastSpell (DEVOTION_AURA, *m_bot));
	}

	if (FIRE_RESISTANCE_AURA > 0) {
		(!m_bot->HasAura(FIRE_RESISTANCE_AURA, 0) && pTarget->getClass() == CLASS_MAGE && GetAI()->CastSpell (FIRE_RESISTANCE_AURA, *m_bot));
	}

	if (RETRIBUTION_AURA > 0) {
		(!m_bot->HasAura(RETRIBUTION_AURA, 0) && pTarget->getClass() == CLASS_PRIEST && GetAI()->CastSpell (RETRIBUTION_AURA, *m_bot));
	}

	if (DEVOTION_AURA > 0) {
		(!m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_SHAMAN && GetAI()->CastSpell (DEVOTION_AURA, *m_bot));
	}

	if (DEVOTION_AURA > 0) {
		(!m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_ROGUE && GetAI()->CastSpell (DEVOTION_AURA, *m_bot));
	}

	if (DEVOTION_AURA > 0) {
		(!m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_PALADIN && GetAI()->CastSpell (DEVOTION_AURA, *m_bot));
	}
	
	
	switch (SpellSequence) {
	
		case SPELL_RET:
				if (SEAL_OF_COMMAND > 0 && LastSpellRet < 1 && ai->GetManaPercent() >= 25) {
			
						ai->CastSpell(SEAL_OF_COMMAND, *pTarget);
						SpellSequence = SPELL_HOLYP;
						LastSpellRet++;
						break;
				
				}
				else if (JUDGEMENT_OF_LIGHT > 0 && LastSpellRet < 2 && ai->GetManaPercent() >=15) {
        						
						ai->CastSpell(JUDGEMENT_OF_LIGHT, *pTarget);
						ai->CastSpell(SEAL_OF_COMMAND, *pTarget);
						SpellSequence = SPELL_HOLYP;
						LastSpellRet++;
						break;
				}
				else if (HAMMER_OF_JUSTICE > 0 && LastSpellRet < 3 && ai->GetManaPercent() >=15) {
						
						ai->CastSpell(HAMMER_OF_JUSTICE, *pTarget);
						SpellSequence = SPELL_HOLYP;
						LastSpellRet++;
						break;
				}

					LastSpellRet = 0;

		case SPELL_HOLYP:
				if (HOLY_LIGHT > 0 && LastSpellHolyp < 1 && ai->GetHealthPercent() < 45 && ai->GetManaPercent() >= 20) {
						ai->CastSpell(HOLY_LIGHT);
						SpellSequence = SPELL_RET;
						LastSpellHolyp++;
						break;
				}
				else if (FLASH_OF_LIGHT > 0 && LastSpellHolyp < 2 && ai->GetHealthPercent() < 75 && ai->GetManaPercent() >= 20) {
						ai->CastSpell(FLASH_OF_LIGHT);
						SpellSequence = SPELL_RET;
						LastSpellHolyp++;
						break;
				}

				else {
					LastSpellHolyp = 0;
					SpellSequence = SPELL_RET;
				}
				
	}
				

	if (HAMMER_OF_WRATH > 0 && pTarget->GetHealth() < pTarget->GetMaxHealth()*0.2 && ai->GetManaPercent() >=15) {
		ai->CastSpell(HAMMER_OF_WRATH, *pTarget);
	}
	if (AVENGING_WRATH > 0 && ai->GetManaPercent() >= 8) {
		ai->CastSpell(AVENGING_WRATH);
	}
	if (DIVINE_SHIELD > 0 && ai->GetHealthPercent() < 30 && ai->GetManaPercent() >= 3) {
		GetAI()->CastSpell(DIVINE_SHIELD, *m_bot);
	}

}

void PlayerbotPaladinAI::DoNonCombatActions(){
	Player * m_bot = GetPlayerBot();
	if (!m_bot) {
		return;
	}

	SpellSequence = SPELL_RET;

	// buff myself
	if (BLESSING_OF_MIGHT > 0) {
		(!m_bot->HasAura(BLESSING_OF_MIGHT, 0) && GetAI()->CastSpell (BLESSING_OF_MIGHT, *m_bot));
	}
	if (RIGHTEOUS_FURY > 0) {
		(!m_bot->HasAura(RIGHTEOUS_FURY, 0) && GetAI()->CastSpell (RIGHTEOUS_FURY, *m_bot));
	}
	if (SEAL_OF_COMMAND > 0) {
		GetAI()->CastSpell (SEAL_OF_COMMAND, *m_bot);
	}
		
		// buff master... original buff seq.
			//	if (BLESSING_OF_MIGHT > 0) {
			//		(!GetMaster()->HasAura(BLESSING_OF_MIGHT,0) && GetAI()->CastSpell (BLESSING_OF_MIGHT, *(GetMaster())) );
			//	}

		//Select Class buff seq.
		///Process Who is my master --> get the player class --> aura already present if not then proced --> cast the spell
	//Priest 
	if (BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_PRIEST && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_PRIEST && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	//Mage
	if (BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_MAGE && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_MAGE && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	//Paladin
	if (BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_PALADIN && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_PALADIN && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	//Warlock
	if (BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_WARLOCK && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_WISDOM > 0) {
				((GetMaster()->getClass()) == CLASS_WARLOCK && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster())) );
			}
	//Warrior
	if (BLESSING_OF_MIGHT > 0) {
				((GetMaster()->getClass()) == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(DEFENSIVE_STANCE, 0) && GetAI()->CastSpell (BLESSING_OF_MIGHT, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_MIGHT > 0) {
				((GetMaster()->getClass()) == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(DEFENSIVE_STANCE, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_MIGHT, *(GetMaster())) );
			}
	if (BLESSING_OF_KINGS > 0) {
				((GetMaster()->getClass()) == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->HasAura(BLESSING_OF_KINGS, 0) && !GetMaster()->HasAura(BERSERKER_STANCE, 0) && !GetMaster()->HasAura(BATTLE_STANCE, 0) && GetAI()->CastSpell (BLESSING_OF_KINGS, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_KINGS > 0) {
				((GetMaster()->getClass()) == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->HasAura(BERSERKER_STANCE, 0) && !GetMaster()->HasAura(BATTLE_STANCE, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster())) );
			}
	//Rogue
	if (BLESSING_OF_MIGHT > 0) {
				((GetMaster()->getClass()) == CLASS_ROGUE && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(BLESSING_OF_MIGHT, 0) && GetAI()->CastSpell (BLESSING_OF_MIGHT, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_MIGHT > 0) {
				((GetMaster()->getClass()) == CLASS_ROGUE && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_MIGHT, *(GetMaster())) );
			}
	//Shaman
	if (BLESSING_OF_MIGHT > 0) {
				((GetMaster()->getClass()) == CLASS_SHAMAN && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(BLESSING_OF_MIGHT, 0) && GetAI()->CastSpell (BLESSING_OF_MIGHT, *(GetMaster())) );
			}
	if (GREATER_BLESSING_OF_MIGHT > 0) {
				((GetMaster()->getClass()) == CLASS_SHAMAN && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && GetAI()->CastSpell (GREATER_BLESSING_OF_MIGHT, *(GetMaster())) );
			}


	// mana check
	if (m_bot->getStandState() != PLAYER_STATE_NONE)
		m_bot->SetStandState(PLAYER_STATE_NONE);

	Item* pItem = GetAI()->FindDrink();

	if (pItem != NULL && GetAI()->GetManaPercent() < 40) {
		GetAI()->TellMaster("I could use a drink.");
		GetAI()->UseItem(*pItem);
		GetAI()->SetIgnoreUpdateTime(30);
		return;
	}

	// hp check original
	if (m_bot->getStandState() != PLAYER_STATE_NONE)
		m_bot->SetStandState(PLAYER_STATE_NONE);

	pItem = GetAI()->FindFood();

	if (pItem != NULL && GetAI()->GetHealthPercent() < 80) {
		GetAI()->TellMaster("I could use some food.");
		GetAI()->UseItem(*pItem);
		GetAI()->SetIgnoreUpdateTime(30);
		return;
	}

	//This is a paladin, self healing maybe? ;D Out of combat he can take car of him self, no ned to be healed.
	//Causes server to crash in some cases /disabled for now/
/*	if (m_bot->getStandState() != PLAYER_STATE_NONE)
		m_bot->SetStandState(PLAYER_STATE_NONE);

	if (HOLY_LIGHT > 0 && GetAI()->GetHealthPercent() < 98 && GetAI()->GetManaPercent() >= 41) {
						GetAI()->CastSpell(HOLY_LIGHT);
				}

*/
}

void PlayerbotPaladinAI::BuffPlayer(Player* target) {
	GetAI()->CastSpell(BLESSING_OF_MIGHT, *target);
}