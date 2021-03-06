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
/*

===== generic grenade.cpp ========================================================

*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "soundent.h"
#include "decals.h"
#include "proj_grenade.h"
#include "particle_defs.h"

#define EXP_SCALE		100
extern int gmsgParticles;//define external message

//===================grenade
LINK_ENTITY_TO_CLASS(grenade, CGrenade);

// Grenades flagged with this will be triggered when the owner calls detonateSatchelCharges
#define SF_DETONATE		0x0001

//
// Grenade Explode
//
void CGrenade::Explode(Vector vecSrc, Vector vecAim)
{
	TraceResult tr;
	UTIL_TraceLine(pev->origin, pev->origin + Vector(0, 0, -32), ignore_monsters, ENT(pev), &tr);
	Explode(&tr, DMG_BLAST);
}

// UNDONE: temporary scorching for PreAlpha - find a less sleazy permenant solution.
void CGrenade::Explode(TraceResult *pTrace, int bitsDamageType)
{
	float	flRndSound;// sound randomizer

	pev->model = iStringNull;//invisible
	pev->solid = SOLID_NOT;// intangible

	pev->takedamage = DAMAGE_NO;

	// Pull out of the wall a bit
	if (pTrace->flFraction != 1.0) {
		pev->origin = pTrace->vecEndPos + (pTrace->vecPlaneNormal * (pev->dmg - 24) * 0.6);
	}

	int iContents = UTIL_PointContents(pev->origin);
	PLAYBACK_EVENT_FULL(FEV_RELIABLE | FEV_GLOBAL, edict(), m_usEfx, 0.0, (float *)&pev->origin, (float *)&g_vecZero, pev->dmg, 0.0, 0, 0, iContents != CONTENTS_WATER ? 0 : 1, 0);

	if (CVAR_GET_FLOAT("cl_expdetail") != 0) {
		if (iContents != CONTENTS_WATER) {
			MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_EXPLOSION);		// This makes a dynamic light and the explosion sprites/sound
			WRITE_COORD(pev->origin.x);	// Send to PAS because of the sound
			WRITE_COORD(pev->origin.y);
			WRITE_COORD(pev->origin.z);
			WRITE_SHORT(g_sModelIndexFireball_0);
			WRITE_BYTE((EXP_SCALE/*pev->dmg*/ - 80) * 0.60); // scale * 10 -50
			WRITE_BYTE(35); // framerate
			WRITE_BYTE(TE_EXPLFLAG_NONE);
			MESSAGE_END();

			MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_EXPLOSION);		// This makes a dynamic light and the explosion sprites/sound
			WRITE_COORD(pev->origin.x);	// Send to PAS because of the sound
			WRITE_COORD(pev->origin.y);
			WRITE_COORD(pev->origin.z);
			WRITE_SHORT(g_sModelIndexFireball_1);
			WRITE_BYTE((EXP_SCALE/*pev->dmg*/ - 50) * 0.60); // scale * 10 -50
			WRITE_BYTE(35); // framerate 15
			WRITE_BYTE(TE_EXPLFLAG_NONE);
			MESSAGE_END();

			// create explosion particle system
			if (CVAR_GET_FLOAT("r_particles") != 0) {
				MESSAGE_BEGIN(MSG_ALL, gmsgParticles);
				WRITE_SHORT(0);
				WRITE_BYTE(0);
				WRITE_COORD(pev->origin.x);
				WRITE_COORD(pev->origin.y);
				WRITE_COORD(pev->origin.z);
				WRITE_COORD(0);
				WRITE_COORD(0);
				WRITE_COORD(0);
				WRITE_SHORT(iExplosionDefault);
				MESSAGE_END();
			}

			// Big Explosion
			MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_GLOWSPRITE);//Big Flare Effect
			WRITE_COORD(pev->origin.x); //where to make the sprite appear on x axis
			WRITE_COORD(pev->origin.y);//where to make the sprite appear on y axis
			WRITE_COORD(pev->origin.z);//where to make the sprite appear on zaxis
			WRITE_SHORT(g_sModelIndexFireballFlash); //Name of the sprite to use, as defined at begining of tut
			WRITE_BYTE(1); // scale
			WRITE_BYTE(30); // framerate 15
			WRITE_BYTE(80); // brightness
			MESSAGE_END();

			TraceResult tr;
			tr.vecEndPos = pev->origin;
			tr.vecPlaneNormal = -1 * pev->velocity.Normalize();
		}

		if (iContents != CONTENTS_WATER) {
			switch (RANDOM_LONG(0, 4)) {
				case 0:	EMIT_SOUND(ENT(pev), CHAN_ITEM, "explosions/explode1.wav", VOL_NORM, ATTN_NORM);	break;
				case 1:	EMIT_SOUND(ENT(pev), CHAN_ITEM, "explosions/explode2.wav", VOL_NORM, ATTN_NORM);	break;
				case 2:	EMIT_SOUND(ENT(pev), CHAN_ITEM, "explosions/explode3.wav", VOL_NORM, ATTN_NORM);	break;
				case 3:	EMIT_SOUND(ENT(pev), CHAN_ITEM, "explosions/explode4.wav", VOL_NORM, ATTN_NORM);	break;
				case 4:	EMIT_SOUND(ENT(pev), CHAN_ITEM, "explosions/explode5.wav", VOL_NORM, ATTN_NORM);	break;
			}
		}

		UTIL_ScreenShake(pev->origin, 12.0, 100.0, 2.0, 1000);

		Vector vecSpot;// shard origin
		Vector vecVelocity;// shard velocity
		CGib *pGib = GetClassPtr((CGib *)NULL);

		pGib->m_bloodColor = DONT_BLEED;
		pGib->pev->origin = pev->origin;
		pGib->pev->velocity = UTIL_RandomBloodVector() * RANDOM_FLOAT(300, 500);

		vecSpot = pev->origin + Vector(0, 0, 8);//move up a bit, and trace down.
		UTIL_RandomBloodVector() * RANDOM_FLOAT(300, 500);

		if (CVAR_GET_FLOAT("sv_grenadegib") == 1) {
			//ALERT( at_console, "Grenade iContents: %i\n", abs(iContents));

			if (iContents != CONTENTS_WATER) {
				//Granate Gibs
				MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecSpot);
				WRITE_BYTE(TE_BREAKMODEL);
				// position
				WRITE_COORD(vecSpot.x);
				WRITE_COORD(vecSpot.y);
				WRITE_COORD(vecSpot.z);

				WRITE_COORD(pev->size.x);
				WRITE_COORD(pev->size.y);
				WRITE_COORD(pev->size.z);

				WRITE_COORD(RANDOM_FLOAT(10, 30));
				WRITE_COORD(RANDOM_FLOAT(10, 30));
				WRITE_COORD(RANDOM_FLOAT(10, 30));

				WRITE_BYTE(RANDOM_FLOAT(15, 30));
				WRITE_SHORT(g_sGrenadeGib);	//model id# //puede dar error esto!
				WRITE_BYTE(35); //2
				WRITE_BYTE(15);// 1 seconds
				WRITE_BYTE(BREAK_CONCRETE);//no?
				MESSAGE_END();
			}
		}
	}

	CSoundEnt::InsertSound(bits_SOUND_COMBAT, pev->origin, NORMAL_EXPLOSION_VOLUME, 3.0);
	entvars_t *pevOwner;
	if (pev->owner)
		pevOwner = VARS(pev->owner);
	else
		pevOwner = NULL;

	pev->owner = NULL; // can't traceline attack owner if this is set
	RadiusDamage(pev, pevOwner, pev->dmg, CLASS_NONE, bitsDamageType);

	CBaseEntity *pHit = CBaseEntity::Instance(pTrace->pHit);
	PLAYBACK_EVENT_FULL(FEV_RELIABLE | FEV_GLOBAL, edict(), m_usDecals, 0.0, (float *)&pTrace->vecEndPos, (float *)&g_vecZero, 0.0, 0.0, pHit->entindex(), 0, 0, 0);
	flRndSound = RANDOM_FLOAT(0, 1);

	switch (RANDOM_LONG(0, 2)) {
		case 0:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/debris1.wav", VOL_LOWER, ATTN_NORM);	break;
		case 1:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/debris2.wav", VOL_LOWER, ATTN_NORM);	break;
		case 2:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/debris3.wav", VOL_LOWER, ATTN_NORM);	break;
	}

	pev->effects |= EF_NODRAW;
	SetThink(&CGrenade::Smoke);
	pev->velocity = g_vecZero;
	SetNextThink(0.3);

	if (iContents != CONTENTS_WATER) {
		int sparkCount = RANDOM_LONG(0, 3);
		Vector mirpos = UTIL_MirrorPos(pev->origin);

		for (int i = 0; i < sparkCount; i++)
			Create("spark_shower", pev->origin, pTrace->vecPlaneNormal, NULL);

		if (mirpos != Vector(0, 0, 0))
			for (int i = 0; i < sparkCount; i++)
				Create("spark_shower", mirpos, pTrace->vecPlaneNormal, NULL);
	}
}

void CGrenade::Smoke(void)
{
	if (UTIL_PointContents(pev->origin) == CONTENTS_WATER) {
		UTIL_Bubbles(pev->origin - Vector(64, 64, 64), pev->origin + Vector(64, 64, 64), 100);
	}
	else {
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
		WRITE_BYTE(TE_SMOKE);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z);
		WRITE_SHORT(g_sModelIndexSmoke);
		WRITE_BYTE((pev->dmg - 50) * 0.80); // scale * 10
		WRITE_BYTE(12); // framerate
		MESSAGE_END();

		Vector mirpos = UTIL_MirrorPos(pev->origin);
		if (mirpos != Vector(0, 0, 0))
		{
			MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_SMOKE);
			WRITE_COORD(mirpos.x);
			WRITE_COORD(mirpos.y);
			WRITE_COORD(mirpos.z);
			WRITE_SHORT(g_sModelIndexSmoke);
			WRITE_BYTE((pev->dmg - 50) * 0.80); // scale * 10
			WRITE_BYTE(12); // framerate
			MESSAGE_END();
		}
	}

	UTIL_Remove(this);
}

void CGrenade::Killed(entvars_t *pevAttacker, int iGib)
{
	Detonate();
}

// Timed grenade, this think is called when time runs out.
void CGrenade::DetonateUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SetThink(&CGrenade::Detonate);
	SetNextThink(0);
}

void CGrenade::PreDetonate(void)
{
	CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin, 400, 0.3);

	SetThink(&CGrenade::Detonate);
	SetNextThink(1);
}


void CGrenade::Detonate(void)
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	vecSpot = pev->origin + Vector(0, 0, 8);
	UTIL_TraceLine(vecSpot, vecSpot + Vector(0, 0, -40), ignore_monsters, ENT(pev), &tr);

	Explode(&tr, DMG_BLAST);
}


//
// Contact grenade, explode when it touches something
// 
void CGrenade::ExplodeTouch(CBaseEntity *pOther)
{
	TraceResult tr;
	Vector		vecSpot;// trace starts here!

	pev->enemy = pOther->edict();

	vecSpot = pev->origin - pev->velocity.Normalize() * 32;
	UTIL_TraceLine(vecSpot, vecSpot + pev->velocity.Normalize() * 64, ignore_monsters, ENT(pev), &tr);

	Explode(&tr, DMG_BLAST);
}


void CGrenade::DangerSoundThink(void)
{
	if (!IsInWorld())
	{
		UTIL_Remove(this);
		return;
	}

	CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin + pev->velocity * 0.5, pev->velocity.Length(), 0.2);
	SetNextThink(0.2);

	if (pev->waterlevel != 0 && pev->watertype > CONTENT_FLYFIELD)
	{
		pev->velocity = pev->velocity * 0.5;
	}
}


void CGrenade::BounceTouch(CBaseEntity *pOther)
{
	// don't hit the guy that launched this grenade
	if (pOther->edict() == pev->owner)
		return;

	// only do damage if we're moving fairly fast
	if (m_flNextAttack < UTIL_GlobalTimeBase() && pev->velocity.Length() > 100)
	{
		entvars_t *pevOwner = VARS(pev->owner);
		if (pevOwner)
		{
			TraceResult tr = UTIL_GetGlobalTrace();
			ClearMultiDamage();
			pOther->TraceAttack(pevOwner, 1, gpGlobals->v_forward, &tr, DMG_CLUB);
			ApplyMultiDamage(pev, pevOwner);
		}
		m_flNextAttack = UTIL_GlobalTimeBase() + 1.0; // debounce
	}

	Vector vecTestVelocity;
	// pev->avelocity = Vector (300, 300, 300);

	// this is my heuristic for modulating the grenade velocity because grenades dropped purely vertical
	// or thrown very far tend to slow down too quickly for me to always catch just by testing velocity. 
	// trimming the Z velocity a bit seems to help quite a bit.
	vecTestVelocity = pev->velocity;
	vecTestVelocity.z *= 0.45;

	if (!m_fRegisteredSound && vecTestVelocity.Length() <= 60)
	{
		//ALERT( at_console, "Grenade Registered!: %f\n", vecTestVelocity.Length() );

		// grenade is moving really slow. It's probably very close to where it will ultimately stop moving. 
		// go ahead and emit the danger sound.

		// register a radius louder than the explosion, so we make sure everyone gets out of the way
		CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin, pev->dmg / 0.4, 0.3);
		m_fRegisteredSound = TRUE;
	}

	if (pev->flags & FL_ONGROUND)
	{
		// add a bit of static friction
		pev->velocity = pev->velocity * 0.8;

		pev->sequence = RANDOM_LONG(1, 1);
	}
	else
	{
		// play bounce sound
		BounceSound();
	}
	pev->framerate = pev->velocity.Length() / 200.0;
	if (pev->framerate > 1.0)
		pev->framerate = 1;
	else if (pev->framerate < 0.5)
		pev->framerate = 0;

}



void CGrenade::SlideTouch(CBaseEntity *pOther)
{
	// don't hit the guy that launched this grenade
	if (pOther->edict() == pev->owner)
		return;

	// pev->avelocity = Vector (300, 300, 300);

	if (pev->flags & FL_ONGROUND)
	{
		// add a bit of static friction
		pev->velocity = pev->velocity * 0.95;

		if (pev->velocity.x != 0 || pev->velocity.y != 0)
		{
			// maintain sliding sound
		}
	}
	else
	{
		BounceSound();
	}
}

void CGrenade::BounceSound(void)
{
	switch (RANDOM_LONG(0, 2))
	{
	case 0:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/grenade_hit1.wav", 0.25, ATTN_NORM);	break;
	case 1:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/grenade_hit2.wav", 0.25, ATTN_NORM);	break;
	case 2:	EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/grenade_hit3.wav", 0.25, ATTN_NORM);	break;
	}
}

void CGrenade::TumbleThink(void)
{
	if (!IsInWorld())
	{
		UTIL_Remove(this);
		return;
	}

	StudioFrameAdvance();
	SetNextThink(0.1);

	if (pev->dmgtime - 1 < UTIL_GlobalTimeBase())
	{
		CSoundEnt::InsertSound(bits_SOUND_DANGER, pev->origin + pev->velocity * (pev->dmgtime - UTIL_GlobalTimeBase()), 400, 0.1);
	}

	if (pev->dmgtime <= UTIL_GlobalTimeBase())
	{
		SetThink(&CGrenade::Detonate);
	}
	if (pev->waterlevel != 0 && pev->watertype > CONTENT_FLYFIELD)
	{
		pev->velocity = pev->velocity * 0.5;
		pev->framerate = 0.2;
	}
}


void CGrenade::Spawn(void)
{
	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING("grenade");

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/grenade.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pev->dmg = 100;
	m_fRegisteredSound = FALSE;
}


CGrenade *CGrenade::ShootContact(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity)
{
	CGrenade *pGrenade = GetClassPtr((CGrenade *)NULL);
	pGrenade->Spawn();
	// contact grenades arc lower
	pGrenade->pev->gravity = 0.5;// lower gravity since grenade is aerodynamic and engine doesn't know it.
	UTIL_SetOrigin(pGrenade, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	// make monsters afaid of it while in the air
	pGrenade->SetThink(&CGrenade::DangerSoundThink);
	pGrenade->SetNextThink(0);

	// Tumble in air
	pGrenade->pev->avelocity.x = RANDOM_FLOAT(-100, -500);

	// Explode on contact
	pGrenade->SetTouch(&CGrenade::ExplodeTouch);

	pGrenade->pev->dmg = gSkillData.plrDmgM203Grenade;

	return pGrenade;
}


CGrenade * CGrenade::ShootTimed(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time)
{
	CGrenade *pGrenade = GetClassPtr((CGrenade *)NULL);
	pGrenade->Spawn();
	UTIL_SetOrigin(pGrenade, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = UTIL_VecToAngles(pGrenade->pev->velocity);
	pGrenade->pev->owner = ENT(pevOwner);

	pGrenade->SetTouch(&CGrenade::BounceTouch);	// Bounce if touched

												// Take one second off of the desired detonation time and set the think to PreDetonate. PreDetonate
												// will insert a DANGER sound into the world sound list and delay detonation for one second so that 
												// the grenade explodes after the exact amount of time specified in the call to ShootTimed(). 

	pGrenade->pev->dmgtime = UTIL_GlobalTimeBase() + time;
	pGrenade->SetThink(&CGrenade::TumbleThink);
	pGrenade->SetNextThink(0.1);
	if (time < 0.1)
	{
		pGrenade->SetNextThink(0);
		pGrenade->pev->velocity = Vector(0, 0, 0);
	}

	pGrenade->pev->sequence = RANDOM_LONG(3, 6);
	pGrenade->pev->framerate = 1.0;

	// Tumble through the air
	// pGrenade->pev->avelocity.x = -400;

	pGrenade->pev->gravity = 0.5;
	pGrenade->pev->friction = 0.8;

	SET_MODEL(ENT(pGrenade->pev), "models/w_grenade.mdl");
	pGrenade->pev->dmg = 100;

	return pGrenade;
}


CGrenade * CGrenade::ShootSatchelCharge(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity)
{
	CGrenade *pGrenade = GetClassPtr((CGrenade *)NULL);
	pGrenade->pev->movetype = MOVETYPE_BOUNCE;
	pGrenade->pev->classname = MAKE_STRING("grenade");

	pGrenade->pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pGrenade->pev), "models/grenade.mdl");	// Change this to satchel charge model

	UTIL_SetSize(pGrenade->pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pGrenade->pev->dmg = 200;
	UTIL_SetOrigin(pGrenade, vecStart);
	pGrenade->pev->velocity = vecVelocity;
	pGrenade->pev->angles = g_vecZero;
	pGrenade->pev->owner = ENT(pevOwner);

	// Detonate in "time" seconds
	pGrenade->SetThink(&CGrenade::SUB_DoNothing);
	pGrenade->SetUse(&CGrenade::DetonateUse);
	pGrenade->SetTouch(&CGrenade::SlideTouch);
	pGrenade->pev->spawnflags = SF_DETONATE;

	pGrenade->pev->friction = 0.9;

	return pGrenade;
}



void CGrenade::UseSatchelCharges(entvars_t *pevOwner, SATCHELCODE code)
{
	edict_t *pentOwner;

	if (!pevOwner)
		return;

	CBaseEntity	*pOwner = CBaseEntity::Instance(pevOwner);

	pentOwner = pOwner->edict();

	CBaseEntity *pEnt = UTIL_FindEntityByClassname(NULL, "grenade");
	while (pEnt)
	{
		if (FBitSet(pEnt->pev->spawnflags, SF_DETONATE) && pEnt->pev->owner == pentOwner)
		{
			if (code == SATCHEL_DETONATE)
				pEnt->Use(pOwner, pOwner, USE_ON, 0);
			else	// SATCHEL_RELEASE
				pEnt->pev->owner = NULL;
		}
		pEnt = UTIL_FindEntityByClassname(pEnt, "grenade");
	}
}

//======================end grenade

