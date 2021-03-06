/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   This source code contains proprietary and confidential information of
*   Valve LLC and its suppliers.  Access to this code is restricted to
*   persons who have executed a written SDK license with Valve.  Any access,
*   use or distribution of this code by or to any unlicensed person is illegal.
*
****/

#ifndef MONSTER_BABYHEADCRAB_H
#define MONSTER_BABYHEADCRAB_H

#include "monster_headcrab.h"

class CBabyCrab : public CHeadCrab
{
public:
	void Spawn(void);
	void Precache(void);
	void SetYawSpeed(void);
	float GetDamageAmount(void) { return gSkillData.headcrabDmgBite * 0.3; }
	BOOL CheckRangeAttack1(float flDot, float flDist);
	Schedule_t* GetScheduleOfType(int Type);
	virtual int GetVoicePitch(void) { return PITCH_NORM + RANDOM_LONG(40, 50); }
	virtual float GetSoundVolue(void) { return 0.8; }
};

#endif // MONSTER_BABYHEADCRAB_H