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
//=========================================================
// NPC: Barney Zombie * http://half-life.wikia.com/wiki/Standard_Zombie
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================
#ifndef MONSTER_ZOMBIE_BARNEY_H
#define MONSTER_ZOMBIE_BARNEY_H

// include
#include "monster_zombie.h"

// class definition
class CZombieBarney : public CZombie {
	public:
		// void
		void Spawn(void);
		void Precache(void);
};

#endif // MONSTER_ZOMBIE_BARNEY_H