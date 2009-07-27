// a simple DK class by rrtn :)

#include "PlayerbotDeathKnightAI.h"

class PlayerbotAI;
PlayerbotDeathKnightAI::PlayerbotDeathKnightAI(Player* const master, Player* const bot, PlayerbotAI* const ai): PlayerbotClassAI(master, bot, ai) {

   PLAGUE_STRIKE     = ai->getSpellId("plague strike"); // Unholy
   BONE_SHIELD		 = ai->getSpellId("bone shield");
   DEATH_GRIP        = ai->getSpellId("death grip");
   DEATH_COIL        = ai->getSpellId("death coil");
   DEATH_STRIKE      = ai->getSpellId("death strike");
   UNHOLY_BLIGHT     = ai->getSpellId("unholy blight");
   SCOURGE_STRIKE    = ai->getSpellId("scourge strike");
   ICY_TOUCH         = ai->getSpellId("icy touch"); // Frost
   OBLITERATE        = ai->getSpellId("obliterate");
   HOWLING_BLAST     = ai->getSpellId("howling blast");
   FROST_STRIKE      = ai->getSpellId("frost strike");
   FROSTFEVER        = ai->getSpellId("frostfever");
   RUNE_STRIKE       = ai->getSpellId("rune strike");
   ICY_CLUTCH        = ai->getSpellId("icy clutch");
   BLOOD_STRIKE      = ai->getSpellId("blood strike"); // Blood
   PESTILENCE        = ai->getSpellId("pestilence");
   STRANGULATE       = ai->getSpellId("strangulate");
   BLOOD_BOIL        = ai->getSpellId("blood boil");
   HEART_STRIKE      = ai->getSpellId("heart strike");
   MARK_OF_BLOOD     = ai->getSpellId("mark of blood"); // buffs
   KILLING_MACHINE   = ai->getSpellId("killing machine");
   HORN_OF_WINTER    = ai->getSpellId("horn of winter");
   RUNE_TAP			 = ai->getSpellId("rune tap");//
   UNHOLY_PRESENCE   = ai->getSpellId("unholy presence");//48265; // presence
   FROST_PRESENCE    = ai->getSpellId("frost presence");//48263;
   BLOOD_PRESENCE    = ai->getSpellId("blood presence");//48266;
   RAISE_DEAD        = ai->getSpellId("raise dead"); // pets (TODO: check for pets exist)
   SUMMON_GARGOYLE   = ai->getSpellId("summon gargoyle"); //49206;
   ARMY_OF_THE_DEAD  = ai->getSpellId("army of the dead"); //42650;
}

PlayerbotDeathKnightAI::~PlayerbotDeathKnightAI() {}

void PlayerbotDeathKnightAI::DoNextCombatManeuver(Unit *pTarget)
{
   PlayerbotAI* ai = GetAI();
   if (!ai)
       return; 

   switch (ai->GetScenarioType())
   {
       case PlayerbotAI::SCENARIO_DUEL:
           ai->CastSpell(PLAGUE_STRIKE);
           return;
   }

   // ------- Non Duel combat ----------


   // DK Attcks: Unholy, Frost & Blood

   // damage spells
   ai->SetInFront( pTarget );//<---
   Player *m_bot = GetPlayerBot();
   Unit* pVictim = pTarget->getVictim();

   switch (SpellSequence)
   {
       case SPELL_DK_UNHOLY:
		   if(BONE_SHIELD > 0 && LastSpellUnholyDK < 1)
			  (!m_bot->HasAura(BONE_SHIELD, 0) && ai->CastSpell (BONE_SHIELD, *m_bot));

		   if (ARMY_OF_THE_DEAD > 0 && ai->GetAttackerCount()>=5 && LastSpellUnholyDK < 2)
           {
			   ai->TellMaster("summoning Army of the Dead!");
               ai->CastSpell(ARMY_OF_THE_DEAD);
			   if (ARMY_OF_THE_DEAD > 0 && m_bot->HasAura(ARMY_OF_THE_DEAD, 0))
				   ai->SetIgnoreUpdateTime(7);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
		  
		   if(UNHOLY_PRESENCE > 0 && LastSpellUnholyDK < 3)
           {
               ai->CastSpell(UNHOLY_PRESENCE, *m_bot);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if(PLAGUE_STRIKE > 0 && LastSpellUnholyDK < 4)
           {
               ai->CastSpell(PLAGUE_STRIKE, *pTarget);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
		   }
		   else if (DEATH_GRIP > 0 && LastSpellUnholyDK < 5)
           {
               ai->CastSpell(DEATH_GRIP);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if (DEATH_COIL > 0 && LastSpellUnholyDK <6 && ai->GetRunicPower() >= 40)
           {
               ai->CastSpell(DEATH_COIL);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if (DEATH_STRIKE > 0 && !pTarget->HasAura(DEATH_STRIKE, 0) && LastSpellUnholyDK < 7)
           {
               ai->CastSpell(DEATH_STRIKE);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if (UNHOLY_BLIGHT > 0 && !m_bot->HasAura(UNHOLY_BLIGHT, 0) && !pTarget->HasAura(UNHOLY_BLIGHT, 0) && LastSpellUnholyDK < 8 && ai->GetRunicPower() >= 40)
           {
               ai->CastSpell(UNHOLY_BLIGHT);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if (SCOURGE_STRIKE > 0 && LastSpellUnholyDK < 9)
           {
               ai->CastSpell(SCOURGE_STRIKE);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
		   else if (DEATH_AND_DECAY > 0 && ai->GetAttackerCount()>=3 && !pTarget->HasAura(DEATH_AND_DECAY, 0) && LastSpellUnholyDK < 10)
           {
               ai->CastSpell(DEATH_AND_DECAY);
			   ai->SetIgnoreUpdateTime(1);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
		   else if (SUMMON_GARGOYLE > 0 && !m_bot->HasAura(ARMY_OF_THE_DEAD, 0) && LastSpellUnholyDK < 11 && ai->GetRunicPower() >= 50)
           {
			   //ai->TellMaster("summoning gargoyle.");
               ai->CastSpell(SUMMON_GARGOYLE);
			   ai->SetIgnoreUpdateTime(2);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if (RAISE_DEAD > 0 && !m_bot->HasAura(ARMY_OF_THE_DEAD, 0) && LastSpellUnholyDK < 12)
           {
			   //ai->TellMaster("summoning ghoul.");
               ai->CastSpell(RAISE_DEAD);
               SpellSequence = SPELL_DK_FROST;
               LastSpellUnholyDK = LastSpellUnholyDK +1;
               break;
           }
           else if (LastSpellUnholyDK > 13)
           {
               LastSpellUnholyDK = 0;
               SpellSequence = SPELL_DK_FROST;
               break;
           }

           LastSpellUnholyDK = 0;

       case SPELL_DK_FROST:
           if (KILLING_MACHINE > 0)
               (!m_bot->HasAura(KILLING_MACHINE, 0) && ai->CastSpell (KILLING_MACHINE, *m_bot));

		   if (FROST_PRESENCE > 0 && LastSpellFrostDK < 1)
           {
               ai->CastSpell(FROST_PRESENCE, *m_bot);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           if (ICY_TOUCH > 0 && LastSpellFrostDK < 2)
           {
               ai->CastSpell(ICY_TOUCH, *pTarget);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (OBLITERATE > 0 && LastSpellFrostDK < 3)
           {
               ai->CastSpell(OBLITERATE);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (FROST_STRIKE > 0 && LastSpellFrostDK < 4 && ai->GetRunicPower() >= 32)
           {
               ai->CastSpell(FROST_STRIKE);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (HOWLING_BLAST > 0 && LastSpellFrostDK < 5)
           {
               ai->CastSpell(HOWLING_BLAST);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (RUNE_STRIKE > 0 && LastSpellFrostDK < 6 && ai->GetRunicPower() >= 20)
           {
               ai->CastSpell(RUNE_STRIKE);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (FROSTFEVER > 0 && LastSpellFrostDK < 7)
           {
               ai->CastSpell(FROSTFEVER);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (ICY_CLUTCH > 0 && LastSpellFrostDK < 8)
           {
               ai->CastSpell(ICY_CLUTCH, *pTarget);
               SpellSequence = SPELL_DK_BLOOD;
               LastSpellFrostDK = LastSpellFrostDK +1;
               break;
           }
           else if (LastSpellFrostDK > 9)
           {
               LastSpellFrostDK = 0;
               SpellSequence = SPELL_DK_BLOOD;
               break;
           }

           LastSpellFrostDK = 0;

       case SPELL_DK_BLOOD:
           if (MARK_OF_BLOOD > 0)
               (!m_bot->HasAura(MARK_OF_BLOOD, 0) && ai->CastSpell (MARK_OF_BLOOD, *m_bot));

		   if (BLOOD_PRESENCE > 0 && LastSpellBloodDK < 1)
           {
               ai->CastSpell(BLOOD_PRESENCE, *m_bot);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK =  LastSpellBloodDK +1;
               break;
           }
           if (BLOOD_STRIKE > 0 && LastSpellBloodDK < 2)
           {
               ai->CastSpell(BLOOD_STRIKE, *pTarget);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK =  LastSpellBloodDK +1;
               break;
           }
           else if (PESTILENCE > 0 && LastSpellBloodDK < 3)
           {
               ai->CastSpell(PESTILENCE);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK = LastSpellBloodDK +1;
               break;
           }
           else if (STRANGULATE > 0 && LastSpellBloodDK < 4)
           {
               ai->CastSpell(STRANGULATE);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK = LastSpellBloodDK +1;
               break;
           }
           else if (BLOOD_BOIL > 0 && LastSpellBloodDK < 5)
           {
               ai->CastSpell(BLOOD_BOIL);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK = LastSpellBloodDK +1;
               break;
           }
           else if (RUNE_TAP > 0 && LastSpellBloodDK < 6)
           {
			   ai->CastSpell(RUNE_TAP);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK = LastSpellBloodDK +1;
               break;
           }
           else if (HEART_STRIKE > 0 && LastSpellBloodDK < 7)
           {
               ai->CastSpell(HEART_STRIKE);
               SpellSequence = SPELL_DK_UNHOLY;
               LastSpellBloodDK = LastSpellBloodDK +1;
               break;
           }
           else if (LastSpellBloodDK > 8)
           {
               LastSpellBloodDK = 0;
               SpellSequence = SPELL_DK_UNHOLY;
               break;
           }
               LastSpellBloodDK = 0;
               SpellSequence = SPELL_DK_UNHOLY;// <------
           }
    
} // end DoNextCombatManeuver

void PlayerbotDeathKnightAI::DoNonCombatActions()
{
   PlayerbotAI* ai = GetAI();
    Player * m_bot = GetPlayerBot();
    if (!m_bot)
        return;

   SpellSequence = SPELL_DK_BLOOD;

       // buff myself (Blood DK) NO more Horn of winter
       if (BLOOD_PRESENCE > 0)
               (!m_bot->HasAura(BLOOD_PRESENCE, 0) && ai->CastSpell (BLOOD_PRESENCE, *m_bot));

   // buff master with HORN_OF_WINTER
   if (HORN_OF_WINTER> 0)
       (!GetMaster()->HasAura(HORN_OF_WINTER,0) && ai->CastSpell (HORN_OF_WINTER, *(GetMaster())) );

   // hp check
   if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
       m_bot->SetStandState(UNIT_STAND_STATE_STAND);

   Item* pItem = ai->FindFood();

   if (pItem != NULL && ai->GetHealthPercent() < 30)
   {
       ai->TellMaster("I could use some food.");
       ai->UseItem(*pItem);
       ai->SetIgnoreUpdateTime(30);
       return;
   }
} // end DoNonCombatActions
