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
// DEAD OTIS PROP
//=========================================================

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include    "monster_otis_dead.h"

//=========================================================
// Monster's Anim Events Go Here
//=========================================================
char *CDeadOtis::m_szPoses[] = { "lying_on_back", "lying_on_side", "lying_on_stomach", "stuffed_in_vent" ,"dead_sitting" };

#define	NUM_OTIS_HEADS		4

#define	GUN_GROUP			1
#define	HEAD_GROUP			2

#define	HEAD_HAIR			0
#define	HEAD_BALD			1
#define	HEAD_HELMET			2
#define	HEAD_JOE			3

#define	GUN_NONE			0
#define	GUN_EAGLE			1
#define	GUN_NO_GUN			2
#define	GUN_DONUT			3

//=========================================================
// Monster's link to Class
//=========================================================
LINK_ENTITY_TO_CLASS(monster_otis_dead, CDeadOtis);

//=========================================================
// KeyValue
//=========================================================
void CDeadOtis::KeyValue(KeyValueData *pkvd) {
	if (FStrEq(pkvd->szKeyName, "pose")) {
		m_iPose = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	} else if (FStrEq(pkvd->szKeyName, "head")) {
		head = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	} else
		CDeadBarney::KeyValue(pkvd);
}

//=========================================================
// ********** DeadBarney SPAWN **********
//=========================================================
void CDeadOtis::Spawn() {
	PRECACHE_MODEL("models/otis.mdl");
	SET_MODEL(ENT(pev), "models/otis.mdl");

	pev->effects = 0;
	pev->yaw_speed = 8;
	pev->sequence = 0;
	m_bloodColor = BLOOD_COLOR_RED;

	m_iBaseBody = pev->body; //LRC
	SetBodygroup(GUN_GROUP, GUN_NONE);

	// Make sure hands are white.
	if (m_iBaseBody) {
		SetBodygroup(HEAD_GROUP, m_iBaseBody);
	}
	else {
		SetBodygroup(HEAD_GROUP, RANDOM_LONG(0, NUM_OTIS_HEADS - 1));
	}

	if (head != -1 && !m_iBaseBody) {
		SetBodygroup(HEAD_GROUP, head);
	}

	pev->sequence = LookupSequence(m_szPoses[m_iPose]);
	if (pev->sequence == -1) {
		ALERT(at_console, "Dead otis with bad pose\n");
	}

	// Corpses have less health
	pev->health = 8;
	MonsterInitDead();
}