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
// NPC: AH-64 Apache * http://half-life.wikia.com/wiki/AH-64_Apache
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================
#ifndef MONSTER_APACHE_H
#define MONSTER_APACHE_H

class CApache : public CBaseMonster
{
	public:
		virtual void Spawn(void);
		virtual void Precache(void);
		virtual int  Classify(void);
		virtual int  BloodColor(void) { return DONT_BLEED; }
		virtual void Killed(entvars_t *pevAttacker, int iGib);
		virtual void GibMonster(void) { return; };
		virtual int  TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
		virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
		virtual void SetObjectCollisionBox(void);

		void EXPORT HuntThink(void);
		void EXPORT FlyTouch(CBaseEntity *pOther);
		void EXPORT CrashTouch(CBaseEntity *pOther);
		void EXPORT DyingThink(void);
		void EXPORT StartupUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
		void EXPORT NullThink(void);

		virtual void ShowDamage(void);
		virtual void Flight(void);
		virtual void FireRocket(void);
		virtual BOOL FireGun(void);

		virtual int	Save(CSave &save);
		virtual int	Restore(CRestore &restore);

		static	TYPEDESCRIPTION m_SaveData[];

		static const char *pRotorSounds[];
		static const char *pDebrisSounds[];
		static const char *pExplodeSounds[];
	protected:
		int m_iRockets;
		float m_flForce;
		float m_flNextRocket;

		Vector m_vecTarget;
		Vector m_posTarget;

		Vector m_vecDesired;
		Vector m_posDesired;

		Vector m_vecGoal;

		Vector m_angGun;
		float m_flLastSeen;
		float m_flPrevSeen;

		bool m_flDebug;

		int m_iSoundState; // don't save this

		int m_iSpriteTexture;
		int m_iExplode;
		int m_iBodyGibs;
		int m_iRotorSound;

		float m_flGoalSpeed;

		int m_iDoSmokePuff;
};

#endif // MONSTER_APACHE_H