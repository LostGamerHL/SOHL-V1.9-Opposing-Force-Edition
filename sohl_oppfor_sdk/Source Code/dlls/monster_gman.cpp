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
// GMan - misunderstood servant of the people
//=========================================================
#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"weapons.h"
#include	"monster_gman.h"

//=========================================================
// Monster's Anim Events Go Here
//=========================================================

LINK_ENTITY_TO_CLASS( monster_gman, CGMan );

TYPEDESCRIPTION	CGMan::m_SaveData[] = 
{
	DEFINE_FIELD( CGMan, m_hTalkTarget, FIELD_EHANDLE ),
	DEFINE_FIELD( CGMan, m_flTalkTime, FIELD_TIME ),
};
IMPLEMENT_SAVERESTORE( CGMan, CBaseMonster );


//=========================================================
// Classify - indicates this monster's place in the 
// relationship table.
//=========================================================
int	CGMan :: Classify ( void )
{
	return m_iClass?m_iClass:CLASS_NONE;
}

//=========================================================
// SetYawSpeed - allows each sequence to have a different
// turn rate associated with it.
//=========================================================
void CGMan :: SetYawSpeed ( void )
{
	int ys;

	switch ( m_Activity )
	{
	case ACT_IDLE:
	default:
		ys = 90;
	}

	pev->yaw_speed = ys;
}

//=========================================================
// HandleAnimEvent - catches the monster-specific messages
// that occur when tagged animation frames are played.
//=========================================================
void CGMan :: HandleAnimEvent( MonsterEvent_t *pEvent )
{
	switch( pEvent->event )
	{
	case 0:
	default:
		CBaseMonster::HandleAnimEvent( pEvent );
		break;
	}
}

//=========================================================
// ISoundMask - generic monster can't hear.
//=========================================================
int CGMan :: ISoundMask ( void )
{
	return	NULL;
}

//=========================================================
// Spawn
//=========================================================
void CGMan :: Spawn()
{
	Precache();

	if (pev->model)
		SET_MODEL(ENT(pev), STRING(pev->model)); //LRC
	else
		SET_MODEL( ENT(pev), "models/gman.mdl" );

	UTIL_SetSize(pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX);

	pev->solid			= SOLID_SLIDEBOX;
	pev->movetype		= MOVETYPE_STEP;
	m_bloodColor		= DONT_BLEED;
	pev->health			= 100;
	m_flFieldOfView		= 0.5;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState		= MONSTERSTATE_NONE;

	MonsterInit();
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CGMan :: Precache()
{
	if (pev->model)
		PRECACHE_MODEL((char*)STRING(pev->model)); //LRC
	else
		PRECACHE_MODEL( "models/gman.mdl" );
}	


//=========================================================
// AI Schedules Specific to this monster
//=========================================================


void CGMan :: StartTask( Task_t *pTask )
{
	switch( pTask->iTask )
	{
	case TASK_WAIT:
		if (m_hPlayer == NULL)
		{
			m_hPlayer = UTIL_FindEntityByClassname( NULL, "player" );
		}
		break;
	}
	CBaseMonster::StartTask( pTask );
}

void CGMan :: RunTask( Task_t *pTask )
{
	switch( pTask->iTask )
	{
	case TASK_WAIT:
		// look at who I'm talking to
		if (m_flTalkTime > UTIL_GlobalTimeBase() && m_hTalkTarget != NULL)
		{
			float yaw = VecToYaw(m_hTalkTarget->pev->origin - pev->origin) - pev->angles.y;

			if (yaw > 180) yaw -= 360;
			if (yaw < -180) yaw += 360;

			// turn towards vector
			SetBoneController( 0, yaw );
		}
		// look at player, but only if playing a "safe" idle animation
		else if (m_hPlayer != NULL && pev->sequence == 0)
		{
			float yaw = VecToYaw(m_hPlayer->pev->origin - pev->origin) - pev->angles.y;

			if (yaw > 180) yaw -= 360;
			if (yaw < -180) yaw += 360;

			// turn towards vector
			SetBoneController( 0, yaw );
		}
		else 
		{
			SetBoneController( 0, 0 );
		}
		CBaseMonster::RunTask( pTask );
		break;
	default:
		SetBoneController( 0, 0 );
		CBaseMonster::RunTask( pTask );
		break;
	}
}


//=========================================================
// Override all damage
//=========================================================
int CGMan :: TakeDamage( entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType )
{
	pev->health = pev->max_health / 2; // always trigger the 50% damage aitrigger

	if ( flDamage > 0 )
	{
		SetConditions(bits_COND_LIGHT_DAMAGE);
	}

	if ( flDamage >= 20 )
	{
		SetConditions(bits_COND_HEAVY_DAMAGE);
	}
	return TRUE;
}


void CGMan::TraceAttack( entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	UTIL_Ricochet( ptr->vecEndPos, 1.0 );
	AddMultiDamage( pevAttacker, this, flDamage, bitsDamageType );
}


void CGMan::PlayScriptedSentence( const char *pszSentence, float duration, float volume, float attenuation, BOOL bConcurrent, CBaseEntity *pListener )
{
	CBaseMonster::PlayScriptedSentence( pszSentence, duration, volume, attenuation, bConcurrent, pListener );

	m_flTalkTime = UTIL_GlobalTimeBase() + duration;
	m_hTalkTarget = pListener;
}
