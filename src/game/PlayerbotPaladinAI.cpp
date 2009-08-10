    /*
    Name    : PlayerbotPaladinAI.cpp
    Complete: maybe around 27% :D
    Author  : Natsukawa
    Version : 0.35
    */

#include "PlayerbotPaladinAI.h"

class PlayerbotAI;

PlayerbotPaladinAI::PlayerbotPaladinAI(Player* const master, Player* const bot, PlayerbotAI* const ai): PlayerbotClassAI(master, bot, ai)
{

    RETRIBUTION_AURA             = ai->getSpellId("retribution aura");
    SHADOW_RESISTANCE_AURA       = ai->getSpellId("shadow resistance aura");
    DEVOTION_AURA                = ai->getSpellId("devotion aura");
    FIRE_RESISTANCE_AURA         = ai->getSpellId("fire resistance aura");
    FROST_RESISTANCE_AURA        = ai->getSpellId("frost resistance aura");
    CONCENTRATION_AURA           = ai->getSpellId("concentration aura");
    CRUSADER_AURA                = ai->getSpellId("crusader aura");
    CRUSADER_STRIKE              = ai->getSpellId("crusader strike");
    SEAL_OF_COMMAND              = 20375; //For some reason getSpellId was not working. Replaced with spell id
	SEAL_OF_WISDOM				 = ai->getSpellId("seal of wisdom"); // if not 20166
    JUDGEMENT_OF_LIGHT           = ai->getSpellId("judgement of light");
    JUDGEMENT_OF_WISDOM          = ai->getSpellId("judgement of wisdom");
    FLASH_OF_LIGHT               = ai->getSpellId("flash of light");
    HOLY_LIGHT                   = ai->getSpellId("holy light");
    DIVINE_SHIELD                = 642; // ai->getSpellId("divine shield");
    HAND_OF_PROTECTION           = 10278;
    BLESSING_OF_MIGHT            = ai->getSpellId("blessing of might");
    GREATER_BLESSING_OF_MIGHT    = ai->getSpellId("greater blessing of might");
    BLESSING_OF_WISDOM           = ai->getSpellId("blessing of wisdom");
    GREATER_BLESSING_OF_WISDOM   = ai->getSpellId("greater blessing of wisdom");
    BLESSING_OF_KINGS            = ai->getSpellId("blessing of kings");
    GREATER_BLESSING_OF_KINGS    = ai->getSpellId("greater blessing of kings");
    HAMMER_OF_JUSTICE            = ai->getSpellId("hammer of justice");
    RIGHTEOUS_FURY               = ai->getSpellId("righteous fury");
    CONSECRATION                 = ai->getSpellId("consecration");
    AVENGING_WRATH               = ai->getSpellId("avenging wrath");
    HAMMER_OF_WRATH              = ai->getSpellId("hammer of wrath");
	REDEMPTION                   = ai->getSpellId("redemption");
}

PlayerbotPaladinAI::~PlayerbotPaladinAI() {}

void PlayerbotPaladinAI::HealTarget(Unit &target, uint8 hp)
{        
    PlayerbotAI* ai = GetAI();
    if (hp < 25 && HOLY_LIGHT > 0 && ai->GetManaPercent() >= 20)
    {
        GetAI()->TellMaster("I'm casting Holy light.");
        ai->CastSpell(HOLY_LIGHT, target);
    }
    else if (hp < 30 && FLASH_OF_LIGHT > 0 && ai->GetManaPercent() >= 36)
    {
        GetAI()->TellMaster("I'm casting Flash heal.");
        ai->CastSpell(FLASH_OF_LIGHT, target);
    }
}

void PlayerbotPaladinAI::DoNextCombatManeuver(Unit *pTarget)
{
    PlayerbotAI* ai = GetAI();
    if (!ai)
        return;

    switch (ai->GetScenarioType())
    {
        case PlayerbotAI::SCENARIO_DUEL:
            if (HAMMER_OF_JUSTICE > 0)
                ai->CastSpell(HAMMER_OF_JUSTICE);
            return;
    }

    // damage spells
    ai->SetInFront( pTarget );
    Player *m_bot = GetPlayerBot();

    //Shield master if low hp.
    uint32 masterHP = GetMaster()->GetHealth()*100 / GetMaster()->GetMaxHealth();

    if (GetMaster()->isAlive())
        if (masterHP < 25 && HAND_OF_PROTECTION > 0 && !GetMaster()->HasAura(HAND_OF_PROTECTION, 0))
                ai->CastSpell(HAND_OF_PROTECTION, *(GetMaster()));

    if (SHADOW_RESISTANCE_AURA > 0 && !m_bot->HasAura(SHADOW_RESISTANCE_AURA, 0) && pTarget->getClass() == CLASS_WARLOCK)
        ai->CastSpell (SHADOW_RESISTANCE_AURA, *m_bot);

    if (DEVOTION_AURA > 0 && !m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_WARRIOR)
        ai->CastSpell (DEVOTION_AURA, *m_bot);

    if (FIRE_RESISTANCE_AURA > 0 && !m_bot->HasAura(FIRE_RESISTANCE_AURA, 0) && pTarget->getClass() == CLASS_MAGE)
        ai->CastSpell (FIRE_RESISTANCE_AURA, *m_bot);

    if (RETRIBUTION_AURA > 0 && !m_bot->HasAura(RETRIBUTION_AURA, 0) && pTarget->getClass() == CLASS_PRIEST)
        ai->CastSpell (RETRIBUTION_AURA, *m_bot);

    if (DEVOTION_AURA > 0 && !m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_SHAMAN)
        ai->CastSpell (DEVOTION_AURA, *m_bot);

    if (DEVOTION_AURA > 0 && !m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_ROGUE)
        ai->CastSpell (DEVOTION_AURA, *m_bot);

    if (DEVOTION_AURA > 0 && !m_bot->HasAura(DEVOTION_AURA, 0) && pTarget->getClass() == CLASS_PALADIN)
        ai->CastSpell (DEVOTION_AURA, *m_bot);

    if (ai->GetHealthPercent() < 55)
        SpellSequence = Healing;
    else
        SpellSequence = Combat;

    switch (SpellSequence)
    {
        case Combat:
            //ai->TellMaster("Combat");
            if (JUDGEMENT_OF_LIGHT > 0 && CombatCounter < 1 && ai->GetManaPercent() >=15)
            {
                ai->CastSpell (JUDGEMENT_OF_LIGHT, *pTarget);
                //ai->TellMaster("Judgement");
                CombatCounter++;
                break;
            }
            else if (SEAL_OF_COMMAND > 0 && CombatCounter < 2 && ai->GetManaPercent() >= 25)
            {
                ai->CastSpell (SEAL_OF_COMMAND, *m_bot);
                //ai->TellMaster("SealC");
                CombatCounter++;
                break;
            }
            else if (HAMMER_OF_JUSTICE > 0 && CombatCounter < 3 && ai->GetManaPercent() >=15)
            {
                ai->CastSpell (HAMMER_OF_JUSTICE, *pTarget);
                //ai->TellMaster("Hammer");
                CombatCounter++;
                break;
            }
            else if (CRUSADER_STRIKE > 0 && CombatCounter < 4 && ai->GetManaPercent() >=15)
            {
                ai->CastSpell (CRUSADER_STRIKE, *pTarget);
                //ai->TellMaster("CStrike");
                CombatCounter++;
                break;
            }
            else if (CombatCounter < 5)
            {
                CombatCounter = 0;
                //ai->TellMaster("CombatCounter Reset");
                break;
            }
            else
            {
                CombatCounter = 0;
                //ai->TellMaster("Counter = 0");
                break;
            }

        case Healing:
            //ai->TellMaster("Healing");
            if (HOLY_LIGHT > 0 && HealCounter < 1 && ai->GetHealthPercent() < 45 && ai->GetManaPercent() >= 20)
            {
                ai->CastSpell (HOLY_LIGHT);
                //ai->TellMaster("HLight1");
                HealCounter++;
                break;
            }
            else if (HOLY_LIGHT > 0 && HealCounter < 2 && ai->GetHealthPercent() < 75 && ai->GetManaPercent() >= 20)
            {
                ai->CastSpell (HOLY_LIGHT);
                //ai->TellMaster("Hlight2");
                HealCounter++;
                break;
            }
            else if (HealCounter < 3)
            {
                HealCounter = 0;
                //ai->TellMaster("HealCounter Reset");
                break;
            }
            else
            {
                HealCounter = 0;
                //ai->TellMaster("Counter = 0");
                break;
            }
    }

    if (HAMMER_OF_WRATH > 0 && pTarget->GetHealth() < pTarget->GetMaxHealth()*0.2 && ai->GetManaPercent() >=15)
        ai->CastSpell(HAMMER_OF_WRATH, *pTarget);

    if (AVENGING_WRATH > 0 && ai->GetManaPercent() >= 8)
        ai->CastSpell(AVENGING_WRATH);

    if (DIVINE_SHIELD > 0 && ai->GetHealthPercent() < 30 && ai->GetManaPercent() >= 3)
        ai->CastSpell(DIVINE_SHIELD, *m_bot);
}

// CHANGE IT SO IT HEAL BOTH MASTER AND GROUP

void PlayerbotPaladinAI::DoNonCombatActions()
{
    PlayerbotAI* ai = GetAI();
    Player * m_bot = GetPlayerBot();
    if (!m_bot)
        return;

    // buff myself
    if (GREATER_BLESSING_OF_WISDOM > 0 && !m_bot->GetAura(GREATER_BLESSING_OF_WISDOM, 0))
        ai->CastSpell (GREATER_BLESSING_OF_WISDOM, *m_bot);
    
	if (SEAL_OF_WISDOM > 0 && !m_bot->GetAura(SEAL_OF_WISDOM, 0))
		ai->CastSpell (SEAL_OF_WISDOM, *m_bot);



    //Select Class buff seq.
    ///Process Who is my master --> get the player class --> aura already present if not then proced --> cast the spell
    //Priest
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PRIEST && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->GetAura(BLESSING_OF_WISDOM, 0))
        ai->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PRIEST && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0))
        ai->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Mage
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_MAGE && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->GetAura(BLESSING_OF_WISDOM, 0))
        ai->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_MAGE && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0))
        ai->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Paladin
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PALADIN && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->GetAura(BLESSING_OF_WISDOM, 0))
        ai->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PALADIN && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0))
        ai->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Warlock
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_WARLOCK && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->GetAura(BLESSING_OF_WISDOM, 0))
        ai->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_WARLOCK && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0))
        ai->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Warrior
    if (BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_WARRIOR && !GetMaster()->GetAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->GetAura(BLESSING_OF_KINGS, 0))
        ai->CastSpell (BLESSING_OF_KINGS, *(GetMaster()));

    if (GREATER_BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_WARRIOR && !GetMaster()->GetAura(GREATER_BLESSING_OF_KINGS, 0))
        ai->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster()));

    //Rogue
    if (BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_ROGUE && !GetMaster()->GetAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->GetAura(BLESSING_OF_MIGHT, 0))
        ai->CastSpell (BLESSING_OF_MIGHT, *(GetMaster()));

    if (GREATER_BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_ROGUE && !GetMaster()->GetAura(GREATER_BLESSING_OF_MIGHT, 0))
        ai->CastSpell (GREATER_BLESSING_OF_MIGHT, *(GetMaster()));

    //Shaman
    if (BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_SHAMAN && !GetMaster()->GetAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->GetAura(BLESSING_OF_WISDOM, 0))
        ai->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_SHAMAN && !GetMaster()->GetAura(GREATER_BLESSING_OF_WISDOM, 0))
        ai->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

	//DEATH KNIGHT
    if (BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DEATH_KNIGHT && !GetMaster()->GetAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->GetAura(BLESSING_OF_KINGS, 0))
        ai->CastSpell (BLESSING_OF_KINGS, *(GetMaster()));

    if (GREATER_BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DEATH_KNIGHT && !GetMaster()->GetAura(GREATER_BLESSING_OF_KINGS, 0))
        ai->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster()));

	//DRUID
    if (BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DRUID && !GetMaster()->GetAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->GetAura(BLESSING_OF_KINGS, 0))
        ai->CastSpell (BLESSING_OF_KINGS, *(GetMaster()));

    if (GREATER_BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DRUID && !GetMaster()->GetAura(GREATER_BLESSING_OF_KINGS, 0))
        ai->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster()));
    
    // mana check
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    Item* pItem = ai->FindDrink();

    if (pItem != NULL && ai->GetManaPercent() < 50)
    {
        ai->TellMaster("I could use a drink.");
        ai->UseItem(*pItem);
        ai->SetIgnoreUpdateTime(30);
        return;
    }

    // hp check original
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    pItem = ai->FindFood();

    if (pItem != NULL && ai->GetHealthPercent() < 40)
    {
        ai->TellMaster("I could use some food.");
        ai->UseItem(*pItem);
        ai->SetIgnoreUpdateTime(30);
        return;
    }

    // buff and heal master's group
    if (GetMaster()->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = GetMaster()->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *tPlayer = objmgr.GetPlayer(uint64 (itr->guid));
            if( !tPlayer )
                continue;

	       // first rezz em
           if ( !tPlayer->isAlive() && !tPlayer->GetPlayerbotAI() )
           {
              std::string msg = "rezzing ";
              msg += tPlayer->GetName();
              GetPlayerBot()->Say(msg, LANG_UNIVERSAL);
              ai->CastSpell(REDEMPTION, *tPlayer);
              // rez is only 10 sec, but give time for lag
              ai->SetIgnoreUpdateTime(17);
           }
           else if( tPlayer->isAlive() )
           {
           (HealTarget(*tPlayer, tPlayer->GetHealth()*100 / tPlayer->GetMaxHealth())); // need to heal group also not just master, so this line is add in
           return;
		   }
		}
	 }
} // end DoNonCombatActions

void PlayerbotPaladinAI::BuffPlayer(Player* target)
{
    GetAI()->CastSpell(BLESSING_OF_KINGS, *target);
}
