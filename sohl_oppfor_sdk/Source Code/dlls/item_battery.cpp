/***
*
*   SPIRIT OF HALF-LIFE 1.9: OPPOSING-FORCE EDITION
*
*   Spirit of Half-Life and their logos are the property of their respective owners.
*   Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*   This product contains software technology licensed from Id
*   Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
*   All Rights Reserved.
*
*   Modifications by Hammermaps.de DEV Team (support@hammermaps.de).
*
***/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"
#include "player.h"
#include "skill.h"
#include "items.h"

extern int gmsgItemPickup;
extern int gEvilImpulse101;

class CItemBattery : public CItem
{
	void Spawn(void)
	{
		Precache();
		if (pev->model)
			SET_MODEL(ENT(pev), STRING(pev->model)); //LRC
		else
			SET_MODEL(ENT(pev), "models/w_battery.mdl");
		CItem::Spawn();
	}

	void Precache(void)
	{
		if (pev->model)
			PRECACHE_MODEL((char*)STRING(pev->model)); //LRC
		else
			PRECACHE_MODEL("models/w_battery.mdl");

		if (pev->noise)
			PRECACHE_SOUND((char*)STRING(pev->noise)); //LRC
		else
			PRECACHE_SOUND("items/gunpickup2.wav");
	}

	BOOL MyTouch(CBasePlayer *pPlayer)
	{
		if (pPlayer->pev->deadflag != DEAD_NO)
		{
			return FALSE;
		}

		float armor = 0;
		if (pev->armorvalue) armor = pev->armorvalue;
		else armor = gSkillData.batteryCapacity;

		if (pPlayer->TakeArmor(armor))
		{
			int pct;
			char szcharge[64];


			if (pev->noise) EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, STRING(pev->noise), 1, ATTN_NORM); //LRC
			else EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/gunpickup2.wav", 1, ATTN_NORM);

			MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, NULL, pPlayer->pev);
			WRITE_STRING(STRING(pev->classname));
			MESSAGE_END();


			if (!gEvilImpulse101)
			{
				// Suit reports new power level
				// For some reason this wasn't working in release build -- round it.
				pct = (int)((float)(pPlayer->pev->armorvalue * 100.0) * (1.0 / MAX_NORMAL_BATTERY) + 0.5);
				pct = (pct / 5);
				if (pct > 0) pct--;

				snprintf(szcharge, 64, "!HEV_%1dP", pct);

				//EMIT_SOUND_SUIT(ENT(pev), szcharge);
				pPlayer->SetSuitUpdate(szcharge, FALSE, SUIT_NEXT_IN_30SEC);
			}

			return TRUE;
		}
		return FALSE;
	}
};

LINK_ENTITY_TO_CLASS(item_battery, CItemBattery);