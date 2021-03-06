/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//=========================================================
// Weapon: Crowbar * http://half-life.wikia.com/wiki/Crowbar
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================

#ifndef WEAPON_CROWBAR_H
#define WEAPON_CROWBAR_H

//Crowbar Hit-Volume
#define	CROWBAR_BODYHIT_VOLUME 128
#define	CROWBAR_WALLHIT_VOLUME 512

#define	CROWBAR_ATTACK_BOOST   60

//Model Animations | Sequence-ID | Frames | FPS
enum class CROWBAR_IDLE1	   { sequence = 0,  frames = 36, fps = 13 };
enum class CROWBAR_IDLE2	   { sequence = 1,  frames = 81, fps = 15 };
enum class CROWBAR_IDLE3	   { sequence = 2,  frames = 81, fps = 15 };
enum class CROWBAR_DRAW		   { sequence = 3,  frames = 13, fps = 24 };
enum class CROWBAR_HOLSTER	   { sequence = 4,  frames = 13, fps = 24 };
enum class CROWBAR_ATTACK1     { sequence = 5,  frames = 11, fps = 22 };
enum class CROWBAR_ATTACK1MISS { sequence = 6,  frames = 11, fps = 22 };
enum class CROWBAR_ATTACK2	   { sequence = 7,  frames = 14, fps = 22 };
enum class CROWBAR_ATTACK2MISS { sequence = 8,  frames = 14, fps = 22 };
enum class CROWBAR_ATTACK3	   { sequence = 9,  frames = 19, fps = 22 };
enum class CROWBAR_ATTACK3MISS { sequence = 10, frames = 19, fps = 22 };

#ifndef CLIENT_DLL //Only in Server-DLL
//Crowbar Base-Class | Base | Attack | Animations | Vars | Events
class CCrowbar : public CBasePlayerWeapon {
	public:
		//Base
		void Spawn(void);
		void Precache(void);
		int GetItemInfo(ItemInfo *p);

		//Attack
		void PrimaryAttack(void);
		void SecondaryAttack(void);
		int Swing(int fFirst);

		//Animations
		BOOL Deploy(void);
		void Holster(void);
		void WeaponIdle(void);

		//Vars
		BOOL bHit;
	private:
		//Events
		unsigned int m_usCrowbar;
};
#endif

#endif // WEAPON_CROWBAR_H