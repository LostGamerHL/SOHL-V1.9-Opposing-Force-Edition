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
#include "animation.h"
#include "effects.h"
#include "baseactanimating.h"
#include "xen_hull.h"
#include "xen_spore.h"

//=========================================================
// Link Entity to Class
//=========================================================
LINK_ENTITY_TO_CLASS(xen_spore_small, CXenSporeSmall);
LINK_ENTITY_TO_CLASS(xen_spore_medium, CXenSporeMed);
LINK_ENTITY_TO_CLASS(xen_spore_large, CXenSporeLarge);

const char *CXenSpore::pModelNames[] = {
	"models/fungus(small).mdl",
	"models/fungus.mdl",
	"models/fungus(large).mdl"
};

// I just eyeballed these -- fill in hulls for the legs
const Vector CXenSporeLarge::m_hullSizes[] = {
	Vector(90, -25, 0),
	Vector(25, 75, 0),
	Vector(-15, -100, 0),
	Vector(-90, -35, 0),
	Vector(-90, 60, 0),
};

//=========================================================
// Spawn
//=========================================================
void CXenSpore::Spawn(void) {
	Precache();

	SET_MODEL(ENT(pev), pModelNames[pev->skin]);
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_BBOX;
	pev->takedamage = DAMAGE_YES;

	//	SetActivity( ACT_IDLE );
	pev->sequence = 0;
	pev->frame = RANDOM_FLOAT(0, 255);
	pev->framerate = RANDOM_FLOAT(0.7, 1.4);
	ResetSequenceInfo();
	SetNextThink(RANDOM_FLOAT(0.1, 0.4));	// Load balance these a bit
}

void CXenSporeSmall::Spawn(void) {
	pev->skin = 0;
	CXenSpore::Spawn();
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 64));
}

void CXenSporeMed::Spawn(void) {
	pev->skin = 1;
	CXenSpore::Spawn();
	UTIL_SetSize(pev, Vector(-40, -40, 0), Vector(40, 40, 120));
}

void CXenSporeLarge::Spawn(void) {
	pev->skin = 2;
	CXenSpore::Spawn();
	UTIL_SetSize(pev, Vector(-48, -48, 110), Vector(48, 48, 240));

	Vector forward, right;

	UTIL_MakeVectorsPrivate(pev->angles, forward, right, NULL);

	// Rotate the leg hulls into position
	for (int i = 0; i < HL_ARRAYSIZE(m_hullSizes); i++)
		CXenHull::CreateHull(this, Vector(-12, -12, 0), Vector(12, 12, 120), (m_hullSizes[i].x * forward) + (m_hullSizes[i].y * right));
}

//=========================================================
// Precache
//=========================================================
void CXenSpore::Precache(void)
{
	PRECACHE_MODEL((char *)pModelNames[pev->skin]);
}

//=========================================================
// Think
//=========================================================
void CXenSpore::Think(void)
{
	float flInterval = StudioFrameAdvance();
	SetNextThink(0.1);
}