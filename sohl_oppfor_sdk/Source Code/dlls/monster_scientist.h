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

#ifndef MONSTER_SCIENTIST_H
#define MONSTER_SCIENTIST_H

enum
{
	SCHED_HIDE = LAST_TALKMONSTER_SCHEDULE + 1,
	SCHED_FEAR,
	SCHED_PANIC,
	SCHED_STARTLE,
	SCHED_TARGET_CHASE_SCARED,
	SCHED_TARGET_FACE_SCARED,
};

enum
{
	TASK_SAY_HEAL = LAST_TALKMONSTER_TASK + 1,
	TASK_HEAL,
	TASK_SAY_FEAR,
	TASK_RUN_PATH_SCARED,
	TASK_SCREAM,
	TASK_RANDOM_SCREAM,
	TASK_MOVE_TO_TARGET_RANGE_SCARED,
};

class CScientist : public CTalkMonster
{
public:
	void Spawn(void);
	void Precache(void);

	void SetYawSpeed(void);
	int  Classify(void);
	void HandleAnimEvent(MonsterEvent_t *pEvent);
	void RunTask(Task_t *pTask);
	void StartTask(Task_t *pTask);
	int	ObjectCaps(void) { return CTalkMonster::ObjectCaps() | FCAP_IMPULSE_USE; }
	int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
	virtual int FriendNumber(int arrayNumber);
	void SetActivity(Activity newActivity);
	Activity GetStoppedActivity(void);
	int ISoundMask(void);
	void DeclineFollowing(void);

	float	CoverRadius(void) { return 1200; }		// Need more room for cover because scientists want to get far away!
	BOOL	DisregardEnemy(CBaseEntity *pEnemy) { return !pEnemy->IsAlive() || (UTIL_GlobalTimeBase() - m_fearTime) > 15; }

	BOOL	CanHeal(void);
	void	Heal(void);
	void	Scream(void);

	// Override these to set behavior
	Schedule_t *GetScheduleOfType(int Type);
	Schedule_t *GetSchedule(void);
	MONSTERSTATE GetIdealState(void);

	void DeathSound(void);
	void PainSound(void);

	void TalkInit(void);

	void			Killed(entvars_t *pevAttacker, int iGib);

	virtual int		Save(CSave &save);
	virtual int		Restore(CRestore &restore);
	static	TYPEDESCRIPTION m_SaveData[];

	CUSTOM_SCHEDULES;

private:
	float m_painTime;
	float m_healTime;
	float m_fearTime;
};

class CDeadScientist : public CBaseMonster
{
public:
	void Spawn(void);
	int	Classify(void) { return	CLASS_HUMAN_PASSIVE; }

	void KeyValue(KeyValueData *pkvd);
	int	m_iPose;// which sequence to display
	static char *m_szPoses[7];
};

class CSittingScientist : public CScientist // kdb: changed from public CBaseMonster so he can speak
{
public:
	void Spawn(void);
	void  Precache(void);

	void EXPORT SittingThink(void);
	int	Classify(void);
	virtual int		Save(CSave &save);
	virtual int		Restore(CRestore &restore);
	static	TYPEDESCRIPTION m_SaveData[];

	virtual void SetAnswerQuestion(CTalkMonster *pSpeaker);
	int FriendNumber(int arrayNumber);

	int FIdleSpeak(void);
	int		m_baseSequence;
	int		m_headTurn;
	float	m_flResponseDelay;
};

#endif // MONSTER_SCIENTIST_H