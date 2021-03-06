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

#ifndef MONSTER_HGRUNT_H
#define MONSTER_HGRUNT_H

class CHGrunt : public CSquadMonster
{
public:
	void Spawn(void);
	void Precache(void);
	void SetYawSpeed(void);
	int  Classify(void);
	int ISoundMask(void);
	void HandleAnimEvent(MonsterEvent_t *pEvent);
	BOOL FCanCheckAttacks(void);
	BOOL CheckMeleeAttack1(float flDot, float flDist);
	BOOL CheckRangeAttack1(float flDot, float flDist);
	BOOL CheckRangeAttack2(float flDot, float flDist);
	void CheckAmmo(void);
	void SetActivity(Activity NewActivity);
	void StartTask(Task_t *pTask);
	void RunTask(Task_t *pTask);
	void DeathSound(void);
	void PainSound(void);
	void IdleSound(void);
	Vector GetGunPosition(void);
	void ShootMP5(void);
	void ShootShotgun(void);
	void ShootShotgunDouble(void);
	void PrescheduleThink(void);
	void GibMonster(void);
	void SpeakSentence(void);
	void KeyValue(KeyValueData *pkvd);

	int	Save(CSave &save);
	int Restore(CRestore &restore);

	CBaseEntity	*Kick(void);
	Schedule_t	*GetSchedule(void);
	Schedule_t  *GetScheduleOfType(int Type);
	void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);

	int IRelationship(CBaseEntity *pTarget);

	BOOL FOkToSpeak(void);
	void JustSpoke(void);

	CUSTOM_SCHEDULES;
	static TYPEDESCRIPTION m_SaveData[];

	// checking the feasibility of a grenade toss is kind of costly, so we do it every couple of seconds,
	// not every server frame.
	float m_flNextGrenadeCheck;
	float m_flNextPainTime;
	float m_flLastEnemySightTime;

	Vector	m_vecTossVelocity;

	BOOL	m_fThrowGrenade;
	BOOL	m_fStanding;
	BOOL	m_fFirstEncounter;// only put on the handsign show in the squad's first encounter.
	int		m_cClipSize;

	static const char *pPainSounds[];
	static const char *pDeathSounds[];
	static const char *pAttackSoundsMP5[];

	int m_voicePitch;

	int		m_iBrassShell;
	int		m_iShotgunShell;
	float	m_fLockShootTime;
	float	m_nShotgunDouble;
	int		m_iSentence;
	int		g_fGruntQuestion; // true if an idle grunt asked a question. Cleared when someone answers.
	int		m_iszSpeakAs; // Change the prefix for all this monster's speeches LRC

	static const char *pGruntSentences[];
};

class CHGruntRepel : public CBaseMonster
{
public:
	void Spawn(void);
	void Precache(void);
	void EXPORT RepelUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	int m_iSpriteTexture;	// Don't save, precache
};

#endif // MONSTER_HGRUNT_H