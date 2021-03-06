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
// Projectile: Spit for Gonome
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================
#ifndef GONOMESPLIT_H
#define GONOMESPLIT_H

class CGonomeSpit : public CBaseEntity {
public:
	void Spawn(void);
	void Precache(void);
	static void Shoot(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity);
	void Touch(CBaseEntity *pOther);
	void EXPORT Animate(void);

	virtual int	Save(CSave &save);
	virtual int	Restore(CRestore &restore);
	static	TYPEDESCRIPTION m_SaveData[];

	int iGonomeSpitSprite;
	int  m_maxFrame;
};

#endif // GONOMESPLIT_H
