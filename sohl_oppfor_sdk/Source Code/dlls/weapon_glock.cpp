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
// Weapon: Glock 17 * http://half-life.wikia.com/wiki/Glock_17
// For Spirit of Half-Life v1.9: Opposing-Force Edition
// Version: 1.0 / Build: 00001 / Date: 23.01.2016
//=========================================================

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "weapon_glock.h"

//=========================================================
// Link ENTITY
//=========================================================
LINK_ENTITY_TO_CLASS( weapon_glock, CGlock );
LINK_ENTITY_TO_CLASS( weapon_9mmhandgun, CGlock );

//=========================================================
// Spawn Glock 17
//=========================================================
void CGlock::Spawn( ) {
	Precache();
	m_iId = WEAPON_GLOCK;

	SET_MODEL(ENT(pev), "models/w_9mmhandgun.mdl");
	m_iDefaultAmmo = GLOCK_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}

//=========================================================
// Precache - precaches all resources this weapon needs
//=========================================================
void CGlock::Precache( void ) {
	PRECACHE_MODEL("models/v_9mmhandgun.mdl");
	PRECACHE_MODEL("models/w_9mmhandgun.mdl");
	PRECACHE_MODEL("models/p_9mmhandgun.mdl");

	PRECACHE_MODEL("models/shell.mdl");// brass shell

	PRECACHE_SOUND("items/9mmclip1.wav"); //by model
	PRECACHE_SOUND("items/9mmclip2.wav"); //by model
	PRECACHE_SOUND("weapons/pl_gun3.wav");

	m_usFireGlock = PRECACHE_EVENT( 1, "events/glock.sc" );
}

//=========================================================
// GetItemInfo - give all Infos for this weapon
//=========================================================
int CGlock::GetItemInfo(ItemInfo *p) {
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = _9MM_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = GLOCK_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 0;
	p->iFlags = 0;
	p->iId = m_iId = WEAPON_GLOCK;
	p->iWeight = GLOCK_WEIGHT;
	return 1;
}

//=========================================================
// PrimaryAttack
//=========================================================
void CGlock::PrimaryAttack(void) {
	GlockFire(0.01, 0.35, true);
}

//=========================================================
// SecondaryAttack
//=========================================================
void CGlock::SecondaryAttack( void ) {
	GlockFire(0.1, 0.25, false);
}

//=========================================================
// GlockFire
//=========================================================
void CGlock::GlockFire(float flSpread, float flCycleTime, bool fUseAutoAim) {
	//don't fire underwater
	if (m_iClip && m_pPlayer->pev->waterlevel != 3) {
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
		m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

		m_iClip--;

		Vector vecSrc = m_pPlayer->GetGunPosition();
		Vector vecAiming;

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

		if (fUseAutoAim) {
			vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
		} else {
			vecAiming = gpGlobals->v_forward;
		}

		Vector vecDir;
		vecDir = m_pPlayer->FireBulletsPlayer(1, vecSrc, vecAiming, Vector(flSpread, flSpread, flSpread), 8192, BULLET_PLAYER_9MM, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);

		PLAYBACK_EVENT_FULL(0, m_pPlayer->edict(), m_usFireGlock, 0.0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, pev->body, 0, m_iClip, 0);

		m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);

		if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0) {
			// HEV suit - indicate out of ammo condition
			m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
		}
	}
	else {
		PlayEmptySound(); Reload();
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.7;
	}
}

//=========================================================
// Deploy
//=========================================================
BOOL CGlock::Deploy() {
	return DefaultDeploy("models/v_9mmhandgun.mdl", "models/p_9mmhandgun.mdl", (int)GLOCK_DRAW::sequence,
		"onehanded", CalculateWeaponTime((int)GLOCK_DRAW::frames, (int)GLOCK_DRAW::fps));
}

//=========================================================
// Holster
//=========================================================
void CGlock::Holster() {
	m_fInReload = FALSE;// cancel any reload in progress.
	SendWeaponAnim((int)GLOCK_HOLSTER::sequence);
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() +
		CalculateWeaponTime((int)GLOCK_HOLSTER::frames, (int)GLOCK_HOLSTER::fps);
}

//=========================================================
// Reload
//=========================================================
void CGlock::Reload(void) {
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] == 0) {
		return;
	}

	if (m_iClip == 0) {
		DefaultReload(GLOCK_MAX_CLIP, (int)GLOCK_RELOAD::sequence,
			CalculateWeaponTime((int)GLOCK_RELOAD::frames, (int)GLOCK_RELOAD::fps));
	} else {
		DefaultReload(GLOCK_MAX_CLIP, (int)GLOCK_RELOAD_NOT_EMPTY::sequence,
			CalculateWeaponTime((int)GLOCK_RELOAD_NOT_EMPTY::frames, (int)GLOCK_RELOAD_NOT_EMPTY::fps));
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT ( 10, 15 );
}

//=========================================================
// WeaponIdle Animation
//=========================================================
void CGlock::WeaponIdle( void ) {
	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase() ||
			m_flTimeWeaponIdleLock > UTIL_WeaponTimeBase()) {
		return;
	}

	// only idle if the slid isn't back
	if (m_iClip) {
		int iAnim;
		float flRand = RANDOM_FLOAT(0, 1);
		if (flRand <= 0.5) {
			iAnim = (int)GLOCK_IDLE1::sequence;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() +
				CalculateWeaponTime((int)GLOCK_IDLE1::frames, (int)GLOCK_IDLE1::fps);
			m_flTimeWeaponIdleLock = m_flTimeWeaponIdle + RANDOM_FLOAT(2, 10);
		} else if (flRand <= 0.7) {
			iAnim = (int)GLOCK_IDLE2::sequence;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() +
				CalculateWeaponTime((int)GLOCK_IDLE2::frames, (int)GLOCK_IDLE2::fps);
			m_flTimeWeaponIdleLock = m_flTimeWeaponIdle + RANDOM_FLOAT(2, 10);
		} else if (flRand <= 0.9) {
			iAnim = (int)GLOCK_IDLE3::sequence;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() +
				CalculateWeaponTime((int)GLOCK_IDLE3::frames, (int)GLOCK_IDLE3::fps);
			m_flTimeWeaponIdleLock = m_flTimeWeaponIdle + RANDOM_FLOAT(2, 10);
		} else {
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
			m_flTimeWeaponIdleLock = UTIL_WeaponTimeBase();
		}

		SendWeaponAnim(iAnim);
	}
}