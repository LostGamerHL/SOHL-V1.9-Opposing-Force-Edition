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
//=========================================================
// DEAD Skeleton PROP
//=========================================================

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include    "monster_skeleton_dead.h"

char *CSkeleton::m_szPoses[] = { "s_onback", "s_sitting", "dead_against_wall", "dead_stomach" };

void CSkeleton::KeyValue(KeyValueData *pkvd) {
	if (FStrEq(pkvd->szKeyName, "pose")) {
		m_iPose = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	} else
		CBaseMonster::KeyValue(pkvd);
}

LINK_ENTITY_TO_CLASS(monster_skeleton_dead, CSkeleton);

//=========================================================
// ********** Skeleton SPAWN **********
//=========================================================
void CSkeleton::Spawn(void) {
	PRECACHE_MODEL("models/skeleton.mdl");
	SET_MODEL(ENT(pev), "models/skeleton.mdl");

	pev->effects = 0;
	pev->yaw_speed = 8;
	pev->sequence = 0;
	pev->body = 1;
	m_bloodColor = BLOOD_COLOR_RED;

	pev->sequence = LookupSequence(m_szPoses[m_iPose]);

	if (pev->sequence == -1) {
		ALERT(at_console, "Skeleton with bad pose\n");
		pev->sequence = 0;
		pev->effects = EF_BRIGHTFIELD;
	}

	// Corpses have less health
	pev->health = 8;

	MonsterInitDead();
}
