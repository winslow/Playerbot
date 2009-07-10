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
	SEAL_OF_COMMAND              = ai->getSpellId("seal of command"); // if not change it back to = 20375
	SEAL_OF_RIGHTEOUSNESS        = ai->getSpellId("seal of righteousness"); // if not 21084 
	SEAL_OF_LIGHT				 = ai->getSpellId("seal of light"); // if not 20165
	SEAL_OF_WISDOM				 = ai->getSpellId("seal of wisdom"); // if not 20166
	JUDGEMENT_OF_LIGHT           = ai->getSpellId("judgement of light");
    JUDGEMENT_OF_WISDOM          = ai->getSpellId("judgement of wisdom");
    FLASH_OF_LIGHT               = ai->getSpellId("flash of light");
    HOLY_LIGHT                   = ai->getSpellId("holy light");
    DIVINE_SHIELD                = ai->getSpellId("divine shield"); // if not change it back to = 642
	HAND_OF_PROTECTION           = ai->getSpellId("hand of protection");
    BLESSING_OF_MIGHT            = ai->getSpellId("blessing of might");
    GREATER_BLESSING_OF_MIGHT    = ai->getSpellId("greater blessing of might");
    BLESSING_OF_WISDOM           = ai->getSpellId("blessing of wisdom");
    GREATER_BLESSING_OF_WISDOM   = ai->getSpellId("greater blessing of wisdom");
    BLESSING_OF_KINGS            = ai->getSpellId("blessing of kings");
    GREATER_BLESSING_OF_KINGS    = ai->getSpellId("greater blessing of kings");
	LAY_ON_HANDS				 = ai->getSpellId("lay on hands");
	HAMMER_OF_JUSTICE            = ai->getSpellId("hammer of justice");
    RIGHTEOUS_FURY               = ai->getSpellId("righteous fury");
    CONSECRATION                 = ai->getSpellId("consecration");
    AVENGING_WRATH               = ai->getSpellId("avenging wrath");
    HAMMER_OF_WRATH              = ai->getSpellId("hammer of wrath");
    EXORCISM					 = ai->getSpellId("exorcism");
    HOLY_WRATH					 = ai->getSpellId("holy wrath");
    DIVINE_PLEA					 = ai->getSpellId("divine plea");
    HAND_OF_RECKONING            = ai->getSpellId("hand of reckoning");
    SHIELD_OF_RIGHTEOUSNESS		 = ai->getSpellId("shield of righteousness");
    AVENGERS_SHIELD				 = ai->getSpellId("avengers shield");
    HAMMER_OF_RIGHTEOUS			 = ai->getSpellId("hammer of righteous");
    HOLY_SHEILD					 = ai->getSpellId("holy sheild");
    DIVINE_STORM				 = ai->getSpellId("divine storm");
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

	// ------- Non Duel combat ----------
    
        // damage spells
    ai->SetInFront( pTarget );
    Player *m_bot = GetPlayerBot();
	Group *m_group = m_bot->GetGroup();
            
	uint32 masterHP = GetMaster()->GetHealth()*100 / GetMaster()->GetMaxHealth();
    if (GetMaster()->isAlive())
    {
		if (masterHP < 80)
            HealTarget (*GetMaster(), masterHP);
    }

    // Heal group
    if( m_group )
    {
        Group::MemberSlotList const& groupSlot = m_group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *m_groupMember = objmgr.GetPlayer( itr->guid );
            if( !m_groupMember || !m_groupMember->isAlive() )
                continue;

            uint32 memberHP = m_groupMember->GetHealth()*100 / m_groupMember->GetMaxHealth();
            if( memberHP < 25 )
                HealTarget( *m_groupMember, memberHP );
        }
    }

    //Shield master if low hp.
    
    if (GetMaster()->isAlive())
	  
        if (masterHP < 25 && HAND_OF_PROTECTION > 0 && !GetMaster()->HasAura(HAND_OF_PROTECTION, 0))
                ai->CastSpell(HAND_OF_PROTECTION, *(GetMaster()));
	    else if (masterHP < 25 && LAY_ON_HANDS > 0 && !GetMaster()->HasAura(LAY_ON_HANDS, 0))
				ai->CastSpell(LAY_ON_HANDS, *(GetMaster()));
	    
   // COMBAT

    switch (SpellSequence)
    {
        case SPELL_HOLY2:
            if (CONCENTRATION_AURA > 0 && LastSpellHoly2 <= 1)
            {
				GetAI()->TellMaster("I'm casting CONSECRATION AURA");
                ai->CastSpell(CONCENTRATION_AURA);
                SpellSequence = SPELL_PROTECTION2;
                LastSpellHoly2 = LastSpellHoly2 +1;
                break;
            }
			else if (CONSECRATION > 0 && LastSpellHoly2 <= 2)
            {
				GetAI()->TellMaster("I'm casting CONSECRATION");
                ai->CastSpell(CONSECRATION);
                SpellSequence = SPELL_PROTECTION2;
                LastSpellHoly2 = LastSpellHoly2 +1;
                break;
            }
            else if (EXORCISM > 0 && LastSpellHoly2 <3)
            {
				GetAI()->TellMaster("I'm casting exorcism");
                ai->CastSpell(EXORCISM);
                SpellSequence = SPELL_PROTECTION2;
                LastSpellHoly2 = LastSpellHoly2 +1;
                break;
            }
            else if (HOLY_WRATH > 0 && LastSpellHoly2 <4)
            {
                GetAI()->TellMaster("I'm casting holy wrath");
                ai->CastSpell(HOLY_WRATH);
                SpellSequence = SPELL_PROTECTION2;
                LastSpellHoly2 = LastSpellHoly2 +1;
                break;
             }
             else if (DIVINE_PLEA > 0 && LastSpellHoly2 <5)
             {
                 GetAI()->TellMaster("I'm casting divine plea");
                 ai->CastSpell(DIVINE_PLEA);
                 SpellSequence = SPELL_PROTECTION2;
                 LastSpellHoly2 = LastSpellHoly2 +1;
                 break;
             }
            else if (LastSpellHoly2 > 6)
            {
                LastSpellHoly2 = 0;
                SpellSequence = SPELL_PROTECTION2;
                break;
            }
            LastSpellHoly2 = LastSpellHoly2 +1;

        case SPELL_PROTECTION2:
			if (DEVOTION_AURA > 0 && LastSpellProtection2 <1)
            {
                GetAI()->TellMaster("I'm casting hand of DEVOTION AURA");
                ai->CastSpell(DEVOTION_AURA);
                SpellSequence = SPELL_RETRIBUTION;
                LastSpellProtection2 = LastSpellProtection2 +1;
                break;
            }
            else if (HAND_OF_RECKONING > 0 && LastSpellProtection2 <2)
            {
                GetAI()->TellMaster("I'm casting hand of reckoning");
                ai->CastSpell(HAND_OF_RECKONING);
                SpellSequence = SPELL_RETRIBUTION;
                LastSpellProtection2 = LastSpellProtection2 +1;
                break;
            }
            else if (SHIELD_OF_RIGHTEOUSNESS > 0 && LastSpellProtection2 <3)
            {
                GetAI()->TellMaster("I'm casting shield of righteousness");
                ai->CastSpell(SHIELD_OF_RIGHTEOUSNESS);
                SpellSequence = SPELL_RETRIBUTION;
                LastSpellProtection2 = LastSpellProtection2 +1;
                break;
            }
           else if (AVENGERS_SHIELD > 0 && LastSpellProtection2 <4)
            {
                GetAI()->TellMaster("I'm casting avengers shield.");
                ai->CastSpell(AVENGERS_SHIELD);
                SpellSequence = SPELL_RETRIBUTION;
                (LastSpellProtection2 = LastSpellProtection2 +1);
                break;
            }
            else if (HAMMER_OF_JUSTICE > 0 && LastSpellProtection2 <5)
            {
                GetAI()->TellMaster("I'm casting hammer of justice.");
                ai->CastSpell(HAMMER_OF_JUSTICE);
                SpellSequence = SPELL_RETRIBUTION;
                LastSpellProtection2 = LastSpellProtection2 +1;
                break;
            }
            else if (HAMMER_OF_RIGHTEOUS > 0 && LastSpellProtection2 <6)
            {
				GetAI()->TellMaster("I'm casting hammer of righteous.");
                ai->CastSpell(HAMMER_OF_RIGHTEOUS);
                SpellSequence = SPELL_RETRIBUTION;
                LastSpellProtection2 = LastSpellProtection2 +1;
                break;
            }
            else if (HOLY_SHEILD > 0 && LastSpellProtection2 <7)
            {
				GetAI()->TellMaster("I'm casting holy sheild.");
                ai->CastSpell(HOLY_SHEILD);
                SpellSequence = SPELL_RETRIBUTION;
                LastSpellProtection2 = LastSpellProtection2 +1;
                break;
            }
            else if (LastSpellProtection2 > 8)
            {
                LastSpellProtection2 = 0;
                SpellSequence = SPELL_RETRIBUTION;
                break;
            }
            LastSpellProtection2 = LastSpellProtection2 +1;

        case SPELL_RETRIBUTION:
			if (RETRIBUTION_AURA > 0 && LastSpellRetribution <1)
            {
                GetAI()->TellMaster("I'm casting judgement of RETRIBUTION AURA");
                ai->CastSpell(RETRIBUTION_AURA);
                SpellSequence = SPELL_HOLY2;
                LastSpellRetribution = LastSpellRetribution + 1;
                break;
            }
            else if (JUDGEMENT_OF_LIGHT > 0 && LastSpellRetribution <2)
            {
                GetAI()->TellMaster("I'm casting judgement of light");
                ai->CastSpell(JUDGEMENT_OF_LIGHT);
                SpellSequence = SPELL_HOLY2;
                LastSpellRetribution = LastSpellRetribution + 1;
                break;
            }
            else if (CRUSADER_STRIKE > 0 && LastSpellRetribution <3)
            {
                GetAI()->TellMaster("I'm casting crusader strike");
                ai->CastSpell(CRUSADER_STRIKE);
                SpellSequence = SPELL_HOLY2;
                LastSpellRetribution = LastSpellRetribution + 1;
                break;
            }
            else if (HAMMER_OF_WRATH > 0 && LastSpellRetribution <4)
            {
                GetAI()->TellMaster("I'm casting hammer of wrath");
                ai->CastSpell(HAMMER_OF_WRATH);
                SpellSequence = SPELL_HOLY2;
                LastSpellRetribution = LastSpellRetribution + 1;
                break;
            }
            else if (DIVINE_STORM > 0 && LastSpellRetribution <5)
            {
                GetAI()->TellMaster("I'm casting divine storm");
                ai->CastSpell(DIVINE_STORM);
                SpellSequence = SPELL_HOLY2;
                LastSpellRetribution = LastSpellRetribution + 1;
                break;
            }
            else if (LastSpellRetribution > 6)
            {
                LastSpellRetribution = 0;
                SpellSequence = SPELL_HOLY2;
                break;
            }
            else
            {
                LastSpellRetribution = LastSpellRetribution + 1;
                SpellSequence = SPELL_HOLY2;
            }
    }
}
// CHANGE IT SO IT HEAL BOTH MASTER AND GROUP

void PlayerbotPaladinAI::DoNonCombatActions()
{
    Player * m_bot = GetPlayerBot();
    if (!m_bot)
        return;

    // buff myself
    if (GREATER_BLESSING_OF_WISDOM > 0 && !m_bot->HasAura(GREATER_BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *m_bot);

    if (BLESSING_OF_MIGHT > 0 && !m_bot->HasAura(BLESSING_OF_MIGHT, 0))
        GetAI()->CastSpell (BLESSING_OF_MIGHT, *m_bot);
    
	if (SEAL_OF_WISDOM > 0 && !m_bot->HasAura(SEAL_OF_WISDOM, 0))
		GetAI()->CastSpell (SEAL_OF_WISDOM, *m_bot);

	if (RIGHTEOUS_FURY > 0 && !m_bot->HasAura(RIGHTEOUS_FURY, 0))
        GetAI()->CastSpell (RIGHTEOUS_FURY, *m_bot);


    //Select Class buff seq.
    ///Process Who is my master --> get the player class --> aura already present if not then proced --> cast the spell
    //Priest
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PRIEST && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PRIEST && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Mage
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_MAGE && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_MAGE && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Paladin
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PALADIN && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_PALADIN && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Warlock
    if (BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_WARLOCK && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_WISDOM > 0 && GetMaster()->getClass() == CLASS_WARLOCK && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

    //Warrior
    if (BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(BLESSING_OF_MIGHT, 0))
        GetAI()->CastSpell (BLESSING_OF_MIGHT, *(GetMaster()));

    if (GREATER_BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_MIGHT, *(GetMaster()));

    if (BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->HasAura(BLESSING_OF_KINGS, 0))
        GetAI()->CastSpell (BLESSING_OF_KINGS, *(GetMaster()));

    if (GREATER_BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_WARRIOR && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster()));

    //Rogue
    if (BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_ROGUE && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(BLESSING_OF_MIGHT, 0))
        GetAI()->CastSpell (BLESSING_OF_MIGHT, *(GetMaster()));

    if (GREATER_BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_ROGUE && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_MIGHT, *(GetMaster()));

    //Shaman
    if (BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_SHAMAN && !GetMaster()->HasAura(GREATER_BLESSING_OF_MIGHT, 0) && !GetMaster()->HasAura(BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (BLESSING_OF_WISDOM, *(GetMaster()));

    if (GREATER_BLESSING_OF_MIGHT > 0 && GetMaster()->getClass() == CLASS_SHAMAN && !GetMaster()->HasAura(GREATER_BLESSING_OF_WISDOM, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_WISDOM, *(GetMaster()));

	//DEATH KNIGHT
    if (BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DEATH_KNIGHT && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->HasAura(BLESSING_OF_KINGS, 0))
        GetAI()->CastSpell (BLESSING_OF_KINGS, *(GetMaster()));

    if (GREATER_BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DEATH_KNIGHT && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster()));

	//DRUID
    if (BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DRUID && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0) && !GetMaster()->HasAura(BLESSING_OF_KINGS, 0))
        GetAI()->CastSpell (BLESSING_OF_KINGS, *(GetMaster()));

    if (GREATER_BLESSING_OF_KINGS > 0 && GetMaster()->getClass() == CLASS_DRUID && !GetMaster()->HasAura(GREATER_BLESSING_OF_KINGS, 0))
        GetAI()->CastSpell (GREATER_BLESSING_OF_KINGS, *(GetMaster()));
    
    // mana check
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    Item* pItem = GetAI()->FindDrink();

    if (pItem != NULL && GetAI()->GetManaPercent() < 40)
    {
        GetAI()->TellMaster("I could use a drink.");
        GetAI()->UseItem(*pItem);
        GetAI()->SetIgnoreUpdateTime(30);
        return;
    }

    // hp check original
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    pItem = GetAI()->FindFood();

    if (pItem != NULL && GetAI()->GetHealthPercent() < 80)
    {
        GetAI()->TellMaster("I could use some food.");
        GetAI()->UseItem(*pItem);
        GetAI()->SetIgnoreUpdateTime(30);
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
           if ( !tPlayer->isAlive() && !tPlayer->IsPlayerbot() )
           {
              std::string msg = "rezzing ";
              msg += tPlayer->GetName();
              GetPlayerBot()->Say(msg, LANG_UNIVERSAL);
              GetAI()->CastSpell(REDEMPTION, *tPlayer);
              // rez is only 10 sec, but give time for lag
              GetAI()->SetIgnoreUpdateTime(17);
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
