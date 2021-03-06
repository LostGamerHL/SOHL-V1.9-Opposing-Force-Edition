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
*	Base Source-Code written by Raven City and Marc-Antoine Lortie (https://github.com/malortie).
*   Modifications by Hammermaps.de DEV Team (support@hammermaps.de).
*
***/

//========================================
//Rope
//========================================
#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"player.h"
#include	"weapons.h"
#include	"env_rope_segment.h"
#include	"env_rope.h"

//LINK_ENTITY_TO_CLASS(env_electrified_wire, CRope);
LINK_ENTITY_TO_CLASS(env_rope, CRope);

TYPEDESCRIPTION	CRope::m_SaveData[] =
{
	DEFINE_FIELD(CRope, m_iSegments, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CRope, CBaseEntity);

void CRope::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "segments"))
	{
		m_iSegments = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "bodymodel"))
	{
		m_iszBodyModel = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "endingmodel"))
	{
		m_iszEndingModel = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "disable"))
	{
		m_disable = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "zforce"))
	{
		m_zforce = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "yforce"))
	{
		m_yforce = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "xforce"))
	{
		m_xforce = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "lightningfrequency"))
	{
		m_ilightningfrequency = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "bodysparkfrequency"))
	{
		m_ibodysparkfrequency = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	if (FStrEq(pkvd->szKeyName, "sparkfrequency"))
	{
		m_isparkfrequency = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CRope::Spawn(void)
{
	Precache();

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;

	for (int i = 0; i < MAX_ROPE_SEGMENTS; i++)
		m_pSegments[i] = NULL;

	SetThink(&CRope::StartupThink);
	pev->nextthink = UTIL_GlobalTimeBase() + 0.1;
}

void CRope::Precache(void)
{

	PRECACHE_MODEL("models/rope16.mdl");
	PRECACHE_MODEL("models/rope24.mdl");
	PRECACHE_MODEL("models/rope32.mdl");

	UTIL_PrecacheOther("rope_segment");
}

void CRope::StartupThink(void)
{
	pev->nextthink = UTIL_GlobalTimeBase() + 0.1;

	CreateSegments();

	SetThink(&CRope::RopeThink);
}

//===============================================
// Use binary search for closest point.
//===============================================
int CRope::FindClosestSegment(Vector vecTo, float epsilon, int iMin, int iMax)
{
	if (iMax < iMin)
		return -1;
	else
	{
		int middle = iMin + ((iMax - iMin) / 2);

		if (vecTo.z >(m_pSegments[middle]->pev->origin.z + epsilon))
		{
			return FindClosestSegment(vecTo, epsilon, iMin, middle - 1); // Higher ropes are at vector head.
		}
		else if (vecTo.z < (m_pSegments[middle]->pev->origin.z - epsilon))
		{
			return FindClosestSegment(vecTo, epsilon, middle + 1, iMax); // Lower ropes are at vector tail.
		}
		else
		{
			return middle;
		}
	}
}

static void Functor_SetSegmentFxGlow(CRopeSegment* pSegment)
{
	pSegment->pev->renderfx = kRenderFxGlowShell;
}

static void Functor_SetSegmentFxNormal(CRopeSegment* pSegment)
{
	pSegment->pev->renderfx = kRenderFxNone;
}

void CRope::RopeThink(void)
{
	pev->nextthink = UTIL_GlobalTimeBase() + 0.1;

	CBaseEntity* pEntity = UTIL_PlayerByIndex(1);
	if (pEntity)
	{
		if ((pEntity->pev->origin - pev->origin).Length() > 384)
			return;

		ApplyFunctor(Functor_SetSegmentFxNormal);

		int index = FindClosestSegment(((CBasePlayer*)pEntity)->GetGunPosition(), 16, 0, m_nSegments - 1);
		if (index >= 0 && index < m_nSegments)
		{
			CRopeSegment* pClosestSegment = m_pSegments[index];

			if (pClosestSegment)
			{
				pClosestSegment->SetTouch(&CRopeSegment::SegmentTouch);
				pClosestSegment->pev->renderfx = kRenderFxGlowShell;
				pClosestSegment->pev->rendercolor = Vector(255, 0, 0);
				ALERT(at_console, "Rope joint closest is %d at %f\n", index, pClosestSegment->pev->origin.z);
			}
		}
	}
}

//===============================================
// Create all rope segments.
//===============================================
void CRope::CreateSegments()
{
	CRopeSegment* pRopeSegment = NULL;
	Vector down = Vector(0, 0, -1);
	Vector angles = Vector(0, 0, -90);

	Vector joint;

	joint = pev->origin + (down * 16);

	m_pSegments[0] = (CRopeSegment*)CBaseEntity::Create("rope_segment",joint,angles);
	m_pSegments[0]->m_vecJointPos = joint;
	m_pSegments[0]->m_pPrev = NULL;

	int i;
	for (i = 1; i < m_nSegments; i++)
	{
		joint = pev->origin + (down * 16 * i);

		m_pSegments[i] = (CRopeSegment*)CBaseEntity::Create("rope_segment", joint, angles);

		m_pSegments[i]->m_vecJointPos = joint;

		m_pSegments[i - 1]->m_pNext = m_pSegments[i];
		m_pSegments[i]->m_pPrev = m_pSegments[i - 1];
		m_pSegments[i]->m_pNext = NULL;
	}
}

//===============================================
// Destroy all rope segments
//===============================================
void CRope::DestroySegments(void)
{
	int i;
	for (i = 0; i < m_nSegments; i++)
	{
		if (m_pSegments[i])
		{
			UTIL_Remove(m_pSegments[i]);
			m_pSegments[i] = NULL;
		}
	}
}

//===============================================
// Apply a functor to a range of segments.
//===============================================
void CRope::ApplyFunctor(void(*functor)(CRopeSegment* pSegment), int startIndex, int endIndex)
{
	// No functor? Return.
	if (!functor)
		return;

	// To pass -1 as value for endindex means to apply the functor to all segments.
	int endindex = (endIndex != -1) ? endIndex : (m_nSegments - 1);

	// Apply functor to all segments.
	int i;
	for (i = 0; i <= endindex; i++)
	{
		// Apply functor.
		if (m_pSegments[i])
			functor(m_pSegments[i]);
	}
}

//===============================================
// Apply a functor to all segments.
//===============================================
void CRope::ApplyFunctor(void(*functor)(CRopeSegment* pSegment))
{
	ApplyFunctor(functor, 0, -1);
}