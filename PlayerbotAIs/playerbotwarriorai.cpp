
#include "PlayerbotWarriorAI.h"

class PlayerbotAI;
PlayerbotWarriorAI::PlayerbotWarriorAI(Player* const master, Player* const bot, PlayerbotAI* const ai): PlayerbotClassAI(master, bot, ai) {
	
	HEROIC_STRIKE = ai->getSpellId("heroic strike"); //ARMS
	REND = ai->getSpellId("rend"); //ARMS
	THUNDER_CLAP = ai->getSpellId("thunder clap");  //ARMS
	HAMSTRING = ai->getSpellId("hamstring");  //ARMS
	MOCKING_BLOW = ai->getSpellId("mocking blow");  //ARMS
	RETALIATION = ai->getSpellId("retaliation");  //ARMS
	SWEEPING_STRIKES = ai->getSpellId("sweeping strikes"); //ARMS
	MORTAL_STRIKE = ai->getSpellId("mortal strike");  //ARMS
	BLADESTORM = ai->getSpellId("bladestorm");  //ARMS
	HEROIC_THROW = ai->getSpellId("heroic throw");  //ARMS
	BLOODRAGE = ai->getSpellId("bloodrage"); //PROTECTION
	DEFENSIVE_STANCE = ai->getSpellId("defensive stance"); //PROTECTION
	SUNDER_ARMOR = ai->getSpellId("sunder armor"); //PROTECTION
	TAUNT = ai->getSpellId("taunt"); //PROTECTION
	SHIELD_BASH = ai->getSpellId("shield bash"); //PROTECTION
	REVENGE = ai->getSpellId("revenge"); //PROTECTION
	SHIELD_BLOCK = ai->getSpellId("shield block"); //PROTECTION
	DISARM = ai->getSpellId("disarm"); //PROTECTION
	SHIELD_WALL = ai->getSpellId("shield wall"); //PROTECTION
	SHIELD_SLAM = ai->getSpellId("shield slam"); //PROTECTION
	VIGILANCE = ai->getSpellId("vigilance"); //PROTECTION
	DEVASTATE = ai->getSpellId("devastate"); //PROTECTION
	SHOCKWAVE = ai->getSpellId("shockwave"); //PROTECTION
	SPELL_REFLECTION = ai->getSpellId("spell reflection"); //PROTECTION
	BATTLE_SHOUT = ai->getSpellId("battle shout"); //FURY
	DEMORALIZING_SHOUT = ai->getSpellId("demoralizing shout"); //FURY
	CLEAVE = ai->getSpellId("cleave"); //FURY
	INTIMIDATING_SHOUT = ai->getSpellId("intimidating shout"); //FURY
	EXECUTE = ai->getSpellId("execute"); //FURY
	CHALLENGING_SHOUT = ai->getSpellId("challenging shout"); //FURY
	SLAM = ai->getSpellId("slam"); //FURY
	BERSERKER_STANCE = ai->getSpellId("berserker stance"); //FURY
	INTERCEPT = ai->getSpellId("intercept"); //FURY
	DEATH_WISH = ai->getSpellId("death wish");//FURY
	BERSERKER_RAGE = ai->getSpellId("berserker rage");//FURY
	WHIRLWIND = ai->getSpellId("whirlwind");//FURY
	PUMMEL = ai->getSpellId("pummel"); //FURY
	BLOODTHIRST = ai->getSpellId("bloodthirst"); //FURY
	RECKLESSNESS = ai->getSpellId("recklessness"); //FURY
	RAMPAGE = ai->getSpellId("rampage"); //FURY
	HEROIC_FURY = ai->getSpellId("heroic fury"); //FURY
	COMMANDING_SHOUT = ai->getSpellId("commanding shout"); //FURY
	ENRAGED_REGENERATION = ai->getSpellId("enraged regeneration"); //FURY
}
PlayerbotWarriorAI::~PlayerbotWarriorAI() {}

void PlayerbotWarriorAI::DoNextCombatManeuver(Unit *pTarget){
	PlayerbotAI* ai = GetAI();
	if (!ai) return;
	switch (ai->GetScenarioType()) {
		case SCENARIO_DUEL:

			if (HEROIC_STRIKE > 0) {
				ai->CastSpell(HEROIC_STRIKE);
			}
			return;
	}

	// ------- Non Duel combat ----------

	//ai->Follow(*GetMaster()); // dont want to melee mob

	// Damage Attacks
	
  Player *m_bot = GetPlayerBot();
	if( !m_bot->HasInArc(M_PI, pTarget)) {
	    m_bot->SetInFront(pTarget);
	}
	switch (SpellSequence) {
	
	  case SPELL_PROTECTION:
			if (DEFENSIVE_STANCE > 0 && LastSpellProtection < 1) {
			
						ai->CastSpell(DEFENSIVE_STANCE);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
				break;
				
			}
			  else	if (SUNDER_ARMOR > 0 && LastSpellProtection < 2 && ai->GetRageAmount() >= 15) {
						
						ai->CastSpell(SUNDER_ARMOR, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
			  else if (TAUNT > 0 && LastSpellProtection < 3) {
						
						ai->CastSpell(TAUNT, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (SHIELD_BASH > 0 && LastSpellProtection < 5 && ai->GetRageAmount() >= 10) {
						
						ai->CastSpell(SHIELD_BASH, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (REVENGE > 0 && LastSpellProtection < 6 && ai->GetRageAmount() >= 5) {
						
						ai->CastSpell(REVENGE, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (SHIELD_BLOCK > 0 && LastSpellProtection < 7) {
						
						ai->CastSpell(SHIELD_BLOCK);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (DISARM > 0 && LastSpellProtection < 8 && ai->GetRageAmount() >= 15) {
						
						ai->CastSpell(DISARM, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (SHIELD_WALL > 0 && LastSpellProtection < 9) {
						
						ai->CastSpell(SHIELD_WALL);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (SHIELD_SLAM > 0 && LastSpellProtection < 10 && ai->GetRageAmount() >= 20) {
						
						ai->CastSpell(SHIELD_SLAM, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (VIGILANCE > 0 && LastSpellProtection < 11) {
						
						ai->CastSpell(VIGILANCE, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (DEVASTATE > 0 && LastSpellProtection < 12 && ai->GetRageAmount() >= 15) {
						
						ai->CastSpell(DEVASTATE, *pTarget);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (SHOCKWAVE > 0 && LastSpellProtection < 13 && ai->GetRageAmount() >= 15) {
						
						ai->CastSpell(SHOCKWAVE);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				else if (SPELL_REFLECTION > 0 && LastSpellProtection < 14 && ai->GetRageAmount() >= 15) {
						
						ai->CastSpell(SPELL_REFLECTION);
						SpellSequence = SPELL_FURY;
						(LastSpellProtection = LastSpellProtection +1);
						break;
				  }
				

					LastSpellProtection = 0;
					//SpellSequence = SPELL_FURY;
				//break;
				
			
		
		case SPELL_FURY:
			if (DEMORALIZING_SHOUT > 0 && LastSpellFury < 1 && ai->GetRageAmount() >= 10) {
						ai->CastSpell(DEMORALIZING_SHOUT);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
				break;
				  }
				else if (CLEAVE > 0 && LastSpellFury < 2 && ai->GetRageAmount() >= 20) {
						ai->CastSpell(CLEAVE, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				
				else if (INTIMIDATING_SHOUT > 0 && LastSpellFury < 4 && ai->GetRageAmount() >= 25) {
						ai->CastSpell(INTIMIDATING_SHOUT, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (EXECUTE > 0 && LastSpellFury < 5 && ai->GetRageAmount() >= 15) {
						ai->CastSpell(EXECUTE, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (CHALLENGING_SHOUT > 0 && LastSpellFury < 6 && ai->GetRageAmount() >= 5) {
						ai->CastSpell(CHALLENGING_SHOUT);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (SLAM > 0 && LastSpellFury < 7 && ai->GetRageAmount() >= 15) {
						ai->CastSpell(SLAM, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				/*
				else if (BERSERKER_STANCE > 0 && LastSpellFury < 8) {
						ai->CastSpell(BERSERKER_STANCE, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				*/
				else if (INTERCEPT > 0 && LastSpellFury < 9 && ai->GetRageAmount() >= 10) {
						ai->CastSpell(INTERCEPT, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (DEATH_WISH > 0 && LastSpellFury < 10 && ai->GetRageAmount() >= 10) {
						ai->CastSpell(DEATH_WISH);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (BERSERKER_RAGE > 0 && LastSpellFury < 11) {
						ai->CastSpell(BERSERKER_RAGE);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (WHIRLWIND > 0 && LastSpellFury < 12 && ai->GetRageAmount() >= 25) {
						ai->CastSpell(WHIRLWIND);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (PUMMEL > 0 && LastSpellFury < 12 && ai->GetRageAmount() >= 10) {
						ai->CastSpell(PUMMEL, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (BLOODTHIRST > 0 && LastSpellFury < 12 && ai->GetRageAmount() >= 30) {
						ai->CastSpell(BLOODTHIRST, *pTarget);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (RECKLESSNESS > 0 && LastSpellFury < 12) {
						ai->CastSpell(RECKLESSNESS);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (RAMPAGE > 0 && LastSpellFury < 12) {
						ai->CastSpell(RAMPAGE);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (HEROIC_FURY > 0 && LastSpellFury < 12) {
						ai->CastSpell(HEROIC_FURY);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (COMMANDING_SHOUT > 0 && LastSpellFury < 12 && ai->GetRageAmount() >= 10) {
						ai->CastSpell(COMMANDING_SHOUT);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }
				else if (ENRAGED_REGENERATION > 0 && LastSpellFury < 12 && ai->GetRageAmount() >= 15) {
						ai->CastSpell(ENRAGED_REGENERATION);
						SpellSequence = SPELL_ARMS;
						(LastSpellFury = LastSpellFury +1);
						break;
				  }

				LastSpellFury = 0;
				//SpellSequence = SPELL_ARMS;
				//break;
				
			

		  case SPELL_ARMS:
			if (HEROIC_STRIKE > 0 && LastSpellArms < 1 && ai->GetRageAmount() >= 15) {
				ai->CastSpell(HEROIC_STRIKE, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (REND > 0 && LastSpellArms < 2 && ai->GetRageAmount() >= 10 && !ai->HasAura(REND, *pTarget)) {
				ai->CastSpell(REND, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (THUNDER_CLAP > 0 && LastSpellArms < 3 && ai->GetRageAmount() >= 20) {
				ai->CastSpell(THUNDER_CLAP, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (HAMSTRING > 0 && LastSpellArms < 4 && ai->GetRageAmount() >= 15 && !ai->HasAura(HAMSTRING, *pTarget)) {
				ai->CastSpell(HAMSTRING, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (MOCKING_BLOW > 0 && LastSpellArms < 5 && ai->GetRageAmount() >= 10) {
				ai->CastSpell(MOCKING_BLOW, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (RETALIATION > 0 && LastSpellArms < 6) {
				ai->CastSpell(RETALIATION, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (SWEEPING_STRIKES > 0 && LastSpellArms < 7 && ai->GetRageAmount() >= 30) {
				ai->CastSpell(SWEEPING_STRIKES);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else if (MORTAL_STRIKE > 0 && LastSpellArms < 8 && ai->GetRageAmount() >= 30) {
				ai->CastSpell(MORTAL_STRIKE, *pTarget);
				SpellSequence = SPELL_PROTECTION;
				(LastSpellArms = LastSpellArms + 1);
				break;
			}
			else {
				LastSpellArms = 0;
				SpellSequence = SPELL_PROTECTION;
			}
	}

} // end DoNextCombatManeuver

void PlayerbotWarriorAI::DoNonCombatActions(){
	Player * m_bot = GetPlayerBot();
	if (!m_bot) {
		return;
	}

	SpellSequence = SPELL_PROTECTION;
	
	
  if (BATTLE_SHOUT > 0 && !m_bot->HasAura(BATTLE_SHOUT, 0)) {
		if (BLOODRAGE > 0) {
			GetAI()->CastSpell (BLOODRAGE, *m_bot);
		}		
	}

	if (BATTLE_SHOUT > 0 && !m_bot->HasAura(BATTLE_SHOUT, 0)) {
		GetAI()->CastSpell (BATTLE_SHOUT, *m_bot);
	}

	// hp check
	if (m_bot->getStandState() != PLAYER_STATE_NONE)
		m_bot->SetStandState(PLAYER_STATE_NONE);

	Item* pItem = GetAI()->FindFood();

	if (pItem != NULL && GetAI()->GetHealthPercent() < 30) {
		GetAI()->TellMaster("I could use some food.");
		GetAI()->UseItem(*pItem);
		GetAI()->SetIgnoreUpdateTime(30);
		return;
	}


} // end DoNonCombatActions

void PlayerbotWarriorAI::BuffPlayer(Player* target) {
	
}