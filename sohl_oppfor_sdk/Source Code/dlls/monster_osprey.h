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

#ifndef MONSTER_OSPREY_H
#define MONSTER_OSPREY_H

#define MAX_CARRY	24

typedef struct
{
	int isValid;
	EHANDLE hGrunt;
	Vector	vecOrigin;
	Vector  vecAngles;
} t_ospreygrunt;

class COsprey : public CBaseMonster
{
public:
	int		Save(CSave &save);
	int		Restore(CRestore &restore);
	static	TYPEDESCRIPTION m_SaveData[];
	int		ObjectCaps(void) { return CBaseMonster::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

	virtual void Spawn(void);
	virtual void Precache(void);
	virtual int  Classify(void);
	virtual int  BloodColor(void) { return DONT_BLEED; }
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual void KeyValue(KeyValueData *pkvd);

	virtual void UpdateGoal(void);
	virtual BOOL HasDead(void);
	virtual void EXPORT FlyThink(void);
	virtual void EXPORT DeployThink(void);
	virtual void Flight(void);
	virtual void EXPORT HitTouch(CBaseEntity *pOther);
	virtual void EXPORT FindAllThink(void);
	virtual void EXPORT HoverThink(void);
	CBaseMonster *MakeGrunt(Vector vecSrc);
	virtual void EXPORT CrashTouch(CBaseEntity *pOther);
	virtual void EXPORT DyingThink(void);
	virtual void EXPORT CommandUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

	virtual int  TakeDamage( entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType );
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	virtual void ShowDamage(void);

	CBaseEntity *m_pGoalEnt;
	Vector m_vel1;
	Vector m_vel2;
	Vector m_pos1;
	Vector m_pos2;
	Vector m_ang1;
	Vector m_ang2;
	float m_startTime;
	float m_dTime;
	char * m_monster_spawn;

	Vector m_velocity;

	float m_flIdealtilt;
	float m_flRotortilt;

	float m_flRightHealth;
	float m_flLeftHealth;

	static const char *pDebrisSounds[];
	static const char *pExplodeSounds[];

	int	m_iUnits;
	int	m_iMonster;
	EHANDLE m_hGrunt[MAX_CARRY];
	Vector m_vecOrigin[MAX_CARRY];
	EHANDLE m_hRepel[4];

	int m_iSoundState;
	int m_iSpriteTexture;

	int m_iPitch;

	int m_iExplode;
	int	m_iTailGibs;
	int	m_iBodyGibs;
	int	m_iEngineGibs;

	int m_iDoLeftSmokePuff;
	int m_iDoRightSmokePuff;
};

#endif // MONSTER_OSPREY_H