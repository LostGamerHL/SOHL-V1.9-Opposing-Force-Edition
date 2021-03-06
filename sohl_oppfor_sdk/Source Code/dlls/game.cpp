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

#include "extdll.h"
#include "eiface.h"
#include "util.h"
#include "game.h"

cvar_t	displaysoundlist = {"displaysoundlist","0"};

// multiplayer server rules
cvar_t	fragsleft	= {"mp_fragsleft","0", FCVAR_SERVER | FCVAR_UNLOGGED };	  // Don't spam console/log files/users with this changing
cvar_t	timeleft	= {"mp_timeleft","0" , FCVAR_SERVER | FCVAR_UNLOGGED };	  // "      "

// multiplayer server rules
cvar_t	teamplay	= {"mp_teamplay","0", FCVAR_SERVER };
cvar_t	fraglimit	= {"mp_fraglimit","0", FCVAR_SERVER };
cvar_t	timelimit	= {"mp_timelimit","0", FCVAR_SERVER };
cvar_t	friendlyfire= {"mp_friendlyfire","0", FCVAR_SERVER };
cvar_t	falldamage	= {"mp_falldamage","0", FCVAR_SERVER };
cvar_t	weaponstay	= {"mp_weaponstay","0", FCVAR_SERVER };
cvar_t	forcerespawn= {"mp_forcerespawn","1", FCVAR_SERVER };
cvar_t	flashlight	= {"mp_flashlight","0", FCVAR_SERVER };
cvar_t	aimcrosshair= {"mp_autocrosshair","1", FCVAR_SERVER };
cvar_t	decalfrequency = {"decalfrequency","30", FCVAR_SERVER };
cvar_t	teamlist = {"mp_teamlist","hgrunt;scientist", FCVAR_SERVER };
cvar_t	teamoverride = {"mp_teamoverride","1" };
cvar_t	defaultteam = {"mp_defaultteam","0" };
cvar_t	allowmonsters={"mp_allowmonsters","0", FCVAR_SERVER };

cvar_t	impulsetarget={"sohl_impulsetarget","0", FCVAR_SERVER }; //LRC - trigger ents manually
cvar_t	mw_debug={"sohl_mwdebug","0", FCVAR_SERVER }; //LRC - debug info. for MoveWith. (probably not useful for most people.)

cvar_t  mp_chattime = {"mp_chattime","10", FCVAR_SERVER };

// Engine Cvars
cvar_t 	*g_psv_gravity = NULL;
cvar_t	*g_psv_aim = NULL;
cvar_t	*g_footsteps = NULL;

//CVARS FOR SKILL LEVEL SETTINGS
// Agrunt
cvar_t	sk_agrunt_health1 = {"sk_agrunt_health1","0"};
cvar_t	sk_agrunt_health2 = {"sk_agrunt_health2","0"};
cvar_t	sk_agrunt_health3 = {"sk_agrunt_health3","0"};

cvar_t	sk_agrunt_dmg_punch1 = {"sk_agrunt_dmg_punch1","0"};
cvar_t	sk_agrunt_dmg_punch2 = {"sk_agrunt_dmg_punch2","0"};
cvar_t	sk_agrunt_dmg_punch3 = {"sk_agrunt_dmg_punch3","0"};

// Apache
cvar_t	sk_apache_health1	= {"sk_apache_health1","0"};
cvar_t	sk_apache_health2	= {"sk_apache_health2","0"};
cvar_t	sk_apache_health3	= {"sk_apache_health3","0"};

// Osprey
cvar_t	sk_osprey_health1 = { "sk_osprey_health1","0" };
cvar_t	sk_osprey_health2 = { "sk_osprey_health2","0" };
cvar_t	sk_osprey_health3 = { "sk_osprey_health3","0" };

// Apache BlackOP
cvar_t	sk_apache_blkop_health1 = { "sk_apache_blkop_health1","0" };
cvar_t	sk_apache_blkop_health2 = { "sk_apache_blkop_health2","0" };
cvar_t	sk_apache_blkop_health3 = { "sk_apache_blkop_health3","0" };

// Osprey BlackOP
cvar_t	sk_osprey_blkop_health1 = { "sk_osprey_blkop_health1","0" };
cvar_t	sk_osprey_blkop_health2 = { "sk_osprey_blkop_health2","0" };
cvar_t	sk_osprey_blkop_health3 = { "sk_osprey_blkop_health3","0" };

// Barney
cvar_t	sk_barney_health1	= {"sk_barney_health1","0"};
cvar_t	sk_barney_health2	= {"sk_barney_health2","0"};
cvar_t	sk_barney_health3	= {"sk_barney_health3","0"};

cvar_t	sk_barney_head1 = { "sk_barney_head1","0" };
cvar_t	sk_barney_head2 = { "sk_barney_head2","0" };
cvar_t	sk_barney_head3 = { "sk_barney_head3","0" };

cvar_t	sk_barney_chest1 = { "sk_barney_chest1","0" };
cvar_t	sk_barney_chest2 = { "sk_barney_chest2","0" };
cvar_t	sk_barney_chest3 = { "sk_barney_chest3","0" };

cvar_t	sk_barney_stomach1 = { "sk_barney_stomach1","0" };
cvar_t	sk_barney_stomach2 = { "sk_barney_stomach2","0" };
cvar_t	sk_barney_stomach3 = { "sk_barney_stomach3","0" };

cvar_t	sk_barney_leg1 = { "sk_barney_leg1","0" };
cvar_t	sk_barney_leg2 = { "sk_barney_leg2","0" };
cvar_t	sk_barney_leg3 = { "sk_barney_leg3","0" };

cvar_t	sk_barney_arm1 = { "sk_barney_arm1","0" };
cvar_t	sk_barney_arm2 = { "sk_barney_arm2","0" };
cvar_t	sk_barney_arm3 = { "sk_barney_arm3","0" };

// Barniel
cvar_t	sk_barniel_health1 = { "sk_barniel_health1","0" };
cvar_t	sk_barniel_health2 = { "sk_barniel_health2","0" };
cvar_t	sk_barniel_health3 = { "sk_barniel_health3","0" };

cvar_t	sk_barniel_head1 = { "sk_barniel_head1","0" };
cvar_t	sk_barniel_head2 = { "sk_barniel_head2","0" };
cvar_t	sk_barniel_head3 = { "sk_barniel_head3","0" };

cvar_t	sk_barniel_chest1 = { "sk_barniel_chest1","0" };
cvar_t	sk_barniel_chest2 = { "sk_barniel_chest2","0" };
cvar_t	sk_barniel_chest3 = { "sk_barniel_chest3","0" };

cvar_t	sk_barniel_stomach1 = { "sk_barniel_stomach1","0" };
cvar_t	sk_barniel_stomach2 = { "sk_barniel_stomach2","0" };
cvar_t	sk_barniel_stomach3 = { "sk_barniel_stomach3","0" };

cvar_t	sk_barniel_leg1 = { "sk_barniel_leg1","0" };
cvar_t	sk_barniel_leg2 = { "sk_barniel_leg2","0" };
cvar_t	sk_barniel_leg3 = { "sk_barniel_leg3","0" };

cvar_t	sk_barniel_arm1 = { "sk_barniel_arm1","0" };
cvar_t	sk_barniel_arm2 = { "sk_barniel_arm2","0" };
cvar_t	sk_barniel_arm3 = { "sk_barniel_arm3","0" };

// Otis Laurey
cvar_t	sk_otis_health1 = { "sk_otis_health1","0" };
cvar_t	sk_otis_health2 = { "sk_otis_health2","0" };
cvar_t	sk_otis_health3 = { "sk_otis_health3","0" };

cvar_t	sk_otis_head1 = { "sk_otis_head1","0" };
cvar_t	sk_otis_head2 = { "sk_otis_head2","0" };
cvar_t	sk_otis_head3 = { "sk_otis_head3","0" };

cvar_t	sk_otis_chest1 = { "sk_otis_chest1","0" };
cvar_t	sk_otis_chest2 = { "sk_otis_chest2","0" };
cvar_t	sk_otis_chest3 = { "sk_otis_chest3","0" };

cvar_t	sk_otis_stomach1 = { "sk_otis_stomach1","0" };
cvar_t	sk_otis_stomach2 = { "sk_otis_stomach2","0" };
cvar_t	sk_otis_stomach3 = { "sk_otis_stomach3","0" };

cvar_t	sk_otis_leg1 = { "sk_otis_leg1","0" };
cvar_t	sk_otis_leg2 = { "sk_otis_leg2","0" };
cvar_t	sk_otis_leg3 = { "sk_otis_leg3","0" };

cvar_t	sk_otis_arm1 = { "sk_otis_arm1","0" };
cvar_t	sk_otis_arm2 = { "sk_otis_arm2","0" };
cvar_t	sk_otis_arm3 = { "sk_otis_arm3","0" };

// Bullsquid
cvar_t	sk_bullsquid_health1 = {"sk_bullsquid_health1","0"};
cvar_t	sk_bullsquid_health2 = {"sk_bullsquid_health2","0"};
cvar_t	sk_bullsquid_health3 = {"sk_bullsquid_health3","0"};

cvar_t	sk_bullsquid_dmg_bite1 = {"sk_bullsquid_dmg_bite1","0"};
cvar_t	sk_bullsquid_dmg_bite2 = {"sk_bullsquid_dmg_bite2","0"};
cvar_t	sk_bullsquid_dmg_bite3 = {"sk_bullsquid_dmg_bite3","0"};

cvar_t	sk_bullsquid_dmg_whip1 = {"sk_bullsquid_dmg_whip1","0"};
cvar_t	sk_bullsquid_dmg_whip2 = {"sk_bullsquid_dmg_whip2","0"};
cvar_t	sk_bullsquid_dmg_whip3 = {"sk_bullsquid_dmg_whip3","0"};

cvar_t	sk_bullsquid_dmg_spit1 = {"sk_bullsquid_dmg_spit1","0"};
cvar_t	sk_bullsquid_dmg_spit2 = {"sk_bullsquid_dmg_spit2","0"};
cvar_t	sk_bullsquid_dmg_spit3 = {"sk_bullsquid_dmg_spit3","0"};

// Big Momma
cvar_t	sk_bigmomma_health_factor1 = {"sk_bigmomma_health_factor1","1.0"};
cvar_t	sk_bigmomma_health_factor2 = {"sk_bigmomma_health_factor2","1.0"};
cvar_t	sk_bigmomma_health_factor3 = {"sk_bigmomma_health_factor3","1.0"};

cvar_t	sk_bigmomma_dmg_slash1 = {"sk_bigmomma_dmg_slash1","50"};
cvar_t	sk_bigmomma_dmg_slash2 = {"sk_bigmomma_dmg_slash2","50"};
cvar_t	sk_bigmomma_dmg_slash3 = {"sk_bigmomma_dmg_slash3","50"};

cvar_t	sk_bigmomma_dmg_blast1 = {"sk_bigmomma_dmg_blast1","100"};
cvar_t	sk_bigmomma_dmg_blast2 = {"sk_bigmomma_dmg_blast2","100"};
cvar_t	sk_bigmomma_dmg_blast3 = {"sk_bigmomma_dmg_blast3","100"};

cvar_t	sk_bigmomma_radius_blast1 = {"sk_bigmomma_radius_blast1","250"};
cvar_t	sk_bigmomma_radius_blast2 = {"sk_bigmomma_radius_blast2","250"};
cvar_t	sk_bigmomma_radius_blast3 = {"sk_bigmomma_radius_blast3","250"};

// Gargantua
cvar_t	sk_gargantua_health1 = {"sk_gargantua_health1","0"};
cvar_t	sk_gargantua_health2 = {"sk_gargantua_health2","0"};
cvar_t	sk_gargantua_health3 = {"sk_gargantua_health3","0"};

cvar_t	sk_gargantua_dmg_slash1	= {"sk_gargantua_dmg_slash1","0"};
cvar_t	sk_gargantua_dmg_slash2	= {"sk_gargantua_dmg_slash2","0"};
cvar_t	sk_gargantua_dmg_slash3	= {"sk_gargantua_dmg_slash3","0"};

cvar_t	sk_gargantua_dmg_fire1 = {"sk_gargantua_dmg_fire1","0"};
cvar_t	sk_gargantua_dmg_fire2 = {"sk_gargantua_dmg_fire2","0"};
cvar_t	sk_gargantua_dmg_fire3 = {"sk_gargantua_dmg_fire3","0"};

cvar_t	sk_gargantua_dmg_stomp1	= {"sk_gargantua_dmg_stomp1","0"};
cvar_t	sk_gargantua_dmg_stomp2	= {"sk_gargantua_dmg_stomp2","0"};
cvar_t	sk_gargantua_dmg_stomp3	= {"sk_gargantua_dmg_stomp3","0"};

// Hassassin
cvar_t	sk_hassassin_health1 = {"sk_hassassin_health1","0"};
cvar_t	sk_hassassin_health2 = {"sk_hassassin_health2","0"};
cvar_t	sk_hassassin_health3 = {"sk_hassassin_health3","0"};

// Headcrab
cvar_t	sk_headcrab_health1 = {"sk_headcrab_health1","0"};
cvar_t	sk_headcrab_health2 = {"sk_headcrab_health2","0"};
cvar_t	sk_headcrab_health3 = {"sk_headcrab_health3","0"};

cvar_t	sk_headcrab_dmg_bite1 = {"sk_headcrab_dmg_bite1","0"};
cvar_t	sk_headcrab_dmg_bite2 = {"sk_headcrab_dmg_bite2","0"};
cvar_t	sk_headcrab_dmg_bite3 = {"sk_headcrab_dmg_bite3","0"};

// Hgrunt 
cvar_t	sk_hgrunt_health1 = {"sk_hgrunt_health1","0"};
cvar_t	sk_hgrunt_health2 = {"sk_hgrunt_health2","0"};
cvar_t	sk_hgrunt_health3 = {"sk_hgrunt_health3","0"};

cvar_t	sk_hgrunt_kick1 = {"sk_hgrunt_kick1","0"};
cvar_t	sk_hgrunt_kick2 = {"sk_hgrunt_kick2","0"};
cvar_t	sk_hgrunt_kick3 = {"sk_hgrunt_kick3","0"};

cvar_t	sk_hgrunt_pellets1 = {"sk_hgrunt_pellets1","0"};
cvar_t	sk_hgrunt_pellets2 = {"sk_hgrunt_pellets2","0"};
cvar_t	sk_hgrunt_pellets3 = {"sk_hgrunt_pellets3","0"};

cvar_t	sk_hgrunt_gspeed1 = {"sk_hgrunt_gspeed1","0"};
cvar_t	sk_hgrunt_gspeed2 = {"sk_hgrunt_gspeed2","0"};
cvar_t	sk_hgrunt_gspeed3 = {"sk_hgrunt_gspeed3","0"};

// Houndeye
cvar_t	sk_houndeye_health1 = {"sk_houndeye_health1","0"};
cvar_t	sk_houndeye_health2 = {"sk_houndeye_health2","0"};
cvar_t	sk_houndeye_health3 = {"sk_houndeye_health3","0"};

cvar_t	sk_houndeye_dmg_blast1 = {"sk_houndeye_dmg_blast1","0"};
cvar_t	sk_houndeye_dmg_blast2 = {"sk_houndeye_dmg_blast2","0"};
cvar_t	sk_houndeye_dmg_blast3 = {"sk_houndeye_dmg_blast3","0"};

// ISlave
cvar_t	sk_islave_health1 = {"sk_islave_health1","0"};
cvar_t	sk_islave_health2 = {"sk_islave_health2","0"};
cvar_t	sk_islave_health3 = {"sk_islave_health3","0"};

cvar_t	sk_islave_dmg_claw1 = {"sk_islave_dmg_claw1","0"};
cvar_t	sk_islave_dmg_claw2 = {"sk_islave_dmg_claw2","0"};
cvar_t	sk_islave_dmg_claw3 = {"sk_islave_dmg_claw3","0"};

cvar_t	sk_islave_dmg_clawrake1	= {"sk_islave_dmg_clawrake1","0"};
cvar_t	sk_islave_dmg_clawrake2	= {"sk_islave_dmg_clawrake2","0"};
cvar_t	sk_islave_dmg_clawrake3	= {"sk_islave_dmg_clawrake3","0"};
	
cvar_t	sk_islave_dmg_zap1 = {"sk_islave_dmg_zap1","0"};
cvar_t	sk_islave_dmg_zap2 = {"sk_islave_dmg_zap2","0"};
cvar_t	sk_islave_dmg_zap3 = {"sk_islave_dmg_zap3","0"};

// Icthyosaur
cvar_t	sk_ichthyosaur_health1	= {"sk_ichthyosaur_health1","0"};
cvar_t	sk_ichthyosaur_health2	= {"sk_ichthyosaur_health2","0"};
cvar_t	sk_ichthyosaur_health3	= {"sk_ichthyosaur_health3","0"};

cvar_t	sk_ichthyosaur_shake1	= {"sk_ichthyosaur_shake1","0"};
cvar_t	sk_ichthyosaur_shake2	= {"sk_ichthyosaur_shake2","0"};
cvar_t	sk_ichthyosaur_shake3	= {"sk_ichthyosaur_shake3","0"};

// Leech
cvar_t	sk_leech_health1 = {"sk_leech_health1","0"};
cvar_t	sk_leech_health2 = {"sk_leech_health2","0"};
cvar_t	sk_leech_health3 = {"sk_leech_health3","0"};

cvar_t	sk_leech_dmg_bite1 = {"sk_leech_dmg_bite1","0"};
cvar_t	sk_leech_dmg_bite2 = {"sk_leech_dmg_bite2","0"};
cvar_t	sk_leech_dmg_bite3 = {"sk_leech_dmg_bite3","0"};

// Controller
cvar_t	sk_controller_health1 = {"sk_controller_health1","0"};
cvar_t	sk_controller_health2 = {"sk_controller_health2","0"};
cvar_t	sk_controller_health3 = {"sk_controller_health3","0"};

cvar_t	sk_controller_dmgzap1 = {"sk_controller_dmgzap1","0"};
cvar_t	sk_controller_dmgzap2 = {"sk_controller_dmgzap2","0"};
cvar_t	sk_controller_dmgzap3 = {"sk_controller_dmgzap3","0"};

cvar_t	sk_controller_speedball1 = {"sk_controller_speedball1","0"};
cvar_t	sk_controller_speedball2 = {"sk_controller_speedball2","0"};
cvar_t	sk_controller_speedball3 = {"sk_controller_speedball3","0"};

cvar_t	sk_controller_dmgball1 = {"sk_controller_dmgball1","0"};
cvar_t	sk_controller_dmgball2 = {"sk_controller_dmgball2","0"};
cvar_t	sk_controller_dmgball3 = {"sk_controller_dmgball3","0"};

// Nihilanth
cvar_t	sk_nihilanth_health1 = {"sk_nihilanth_health1","0"};
cvar_t	sk_nihilanth_health2 = {"sk_nihilanth_health2","0"};
cvar_t	sk_nihilanth_health3 = {"sk_nihilanth_health3","0"};

cvar_t	sk_nihilanth_zap1 = {"sk_nihilanth_zap1","0"};
cvar_t	sk_nihilanth_zap2 = {"sk_nihilanth_zap2","0"};
cvar_t	sk_nihilanth_zap3 = {"sk_nihilanth_zap3","0"};

// Scientist
cvar_t	sk_scientist_health1 = {"sk_scientist_health1","0"};
cvar_t	sk_scientist_health2 = {"sk_scientist_health2","0"};
cvar_t	sk_scientist_health3 = {"sk_scientist_health3","0"};

// Construction
cvar_t	sk_construction_health1 = { "sk_construction_health1","0" };
cvar_t	sk_construction_health2 = { "sk_construction_health2","0" };
cvar_t	sk_construction_health3 = { "sk_construction_health3","0" };

cvar_t	sk_construction_head1 = { "sk_construction_head1","0" };
cvar_t	sk_construction_head2 = { "sk_construction_head2","0" };
cvar_t	sk_construction_head3 = { "sk_construction_head3","0" };

cvar_t	sk_construction_chest1 = { "sk_construction_chest1","0" };
cvar_t	sk_construction_chest2 = { "sk_construction_chest2","0" };
cvar_t	sk_construction_chest3 = { "sk_construction_chest3","0" };

cvar_t	sk_construction_stomach1 = { "sk_construction_stomach1","0" };
cvar_t	sk_construction_stomach2 = { "sk_construction_stomach2","0" };
cvar_t	sk_construction_stomach3 = { "sk_construction_stomach3","0" };

cvar_t	sk_construction_leg1 = { "sk_construction_leg1","0" };
cvar_t	sk_construction_leg2 = { "sk_construction_leg2","0" };
cvar_t	sk_construction_leg3 = { "sk_construction_leg3","0" };

cvar_t	sk_construction_arm1 = { "sk_construction_arm1","0" };
cvar_t	sk_construction_arm2 = { "sk_construction_arm2","0" };
cvar_t	sk_construction_arm3 = { "sk_construction_arm3","0" };

// Snark
cvar_t	sk_snark_health1 = {"sk_snark_health1","0"};
cvar_t	sk_snark_health2 = {"sk_snark_health2","0"};
cvar_t	sk_snark_health3 = {"sk_snark_health3","0"};

cvar_t	sk_snark_dmg_bite1 = {"sk_snark_dmg_bite1","0"};
cvar_t	sk_snark_dmg_bite2 = {"sk_snark_dmg_bite2","0"};
cvar_t	sk_snark_dmg_bite3 = {"sk_snark_dmg_bite3","0"};

cvar_t	sk_snark_dmg_pop1 = {"sk_snark_dmg_pop1","0"};
cvar_t	sk_snark_dmg_pop2 = {"sk_snark_dmg_pop2","0"};
cvar_t	sk_snark_dmg_pop3 = {"sk_snark_dmg_pop3","0"};

//=========================================================
// NPCs: Diablo
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================
cvar_t	sk_diablo_health1 = { "sk_diablo_health1","0" };
cvar_t	sk_diablo_health2 = { "sk_diablo_health2","0" };
cvar_t	sk_diablo_health3 = { "sk_diablo_health3","0" };

cvar_t	sk_diablo_dmg_one_slash1 = { "sk_diablo_dmg_one_slash1","0" };
cvar_t	sk_diablo_dmg_one_slash2 = { "sk_diablo_dmg_one_slash2","0" };
cvar_t	sk_diablo_dmg_one_slash3 = { "sk_diablo_dmg_one_slash3","0" };

cvar_t	sk_diablo_dmg_both_slash1 = { "sk_diablo_dmg_both_slash1","0" };
cvar_t	sk_diablo_dmg_both_slash2 = { "sk_diablo_dmg_both_slash2","0" };
cvar_t	sk_diablo_dmg_both_slash3 = { "sk_diablo_dmg_both_slash3","0" };

cvar_t	sk_diablo_head1 = { "sk_diablo_head1","0" };
cvar_t	sk_diablo_head2 = { "sk_diablo_head2","0" };
cvar_t	sk_diablo_head3 = { "sk_diablo_head3","0" };

cvar_t	sk_diablo_chest1 = { "sk_diablo_chest1","0" };
cvar_t	sk_diablo_chest2 = { "sk_diablo_chest2","0" };
cvar_t	sk_diablo_chest3 = { "sk_diablo_chest3","0" };

cvar_t	sk_diablo_stomach1 = { "sk_diablo_stomach1","0" };
cvar_t	sk_diablo_stomach2 = { "sk_diablo_stomach2","0" };
cvar_t	sk_diablo_stomach3 = { "sk_diablo_stomach3","0" };

cvar_t	sk_diablo_leg1 = { "sk_diablo_leg1","0" };
cvar_t	sk_diablo_leg2 = { "sk_diablo_leg2","0" };
cvar_t	sk_diablo_leg3 = { "sk_diablo_leg3","0" };

//=========================================================
// NPCs: Zombie,Zombie Soldier,Zombie Barney
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================

// Zombie Scientist
cvar_t	sk_zombie_health1 = { "sk_zombie_health1","0" };
cvar_t	sk_zombie_health2 = { "sk_zombie_health2","0" };
cvar_t	sk_zombie_health3 = { "sk_zombie_health3","0" };

cvar_t	sk_zombie_dmg_one_slash1 = { "sk_zombie_dmg_one_slash1","0" };
cvar_t	sk_zombie_dmg_one_slash2 = { "sk_zombie_dmg_one_slash2","0" };
cvar_t	sk_zombie_dmg_one_slash3 = { "sk_zombie_dmg_one_slash3","0" };

cvar_t	sk_zombie_dmg_both_slash1 = { "sk_zombie_dmg_both_slash1","0" };
cvar_t	sk_zombie_dmg_both_slash2 = { "sk_zombie_dmg_both_slash2","0" };
cvar_t	sk_zombie_dmg_both_slash3 = { "sk_zombie_dmg_both_slash3","0" };

cvar_t	sk_zombie_head1 = { "sk_zombie_head1","0" };
cvar_t	sk_zombie_head2 = { "sk_zombie_head2","0" };
cvar_t	sk_zombie_head3 = { "sk_zombie_head3","0" };

cvar_t	sk_zombie_chest1 = { "sk_zombie_chest1","0" };
cvar_t	sk_zombie_chest2 = { "sk_zombie_chest2","0" };
cvar_t	sk_zombie_chest3 = { "sk_zombie_chest3","0" };

cvar_t	sk_zombie_stomach1 = { "sk_zombie_stomach1","0" };
cvar_t	sk_zombie_stomach2 = { "sk_zombie_stomach2","0" };
cvar_t	sk_zombie_stomach3 = { "sk_zombie_stomach3","0" };

cvar_t	sk_zombie_leg1 = { "sk_zombie_leg1","0" };
cvar_t	sk_zombie_leg2 = { "sk_zombie_leg2","0" };
cvar_t	sk_zombie_leg3 = { "sk_zombie_leg3","0" };

cvar_t	sk_zombie_arm1 = { "sk_zombie_arm1","0" };
cvar_t	sk_zombie_arm2 = { "sk_zombie_arm2","0" };
cvar_t	sk_zombie_arm3 = { "sk_zombie_arm3","0" };

// Zombie Soldier
cvar_t	sk_zombie_soldier_health1 = { "sk_zombie_soldier_health1","0" };
cvar_t	sk_zombie_soldier_health2 = { "sk_zombie_soldier_health2","0" };
cvar_t	sk_zombie_soldier_health3 = { "sk_zombie_soldier_health3","0" };

cvar_t	sk_zombie_soldier_dmg_one_slash1 = { "sk_zombie_soldier_dmg_one_slash1","0" };
cvar_t	sk_zombie_soldier_dmg_one_slash2 = { "sk_zombie_soldier_dmg_one_slash2","0" };
cvar_t	sk_zombie_soldier_dmg_one_slash3 = { "sk_zombie_soldier_dmg_one_slash3","0" };

cvar_t	sk_zombie_soldier_dmg_both_slash1 = { "sk_zombie_soldier_dmg_both_slash1","0" };
cvar_t	sk_zombie_soldier_dmg_both_slash2 = { "sk_zombie_soldier_dmg_both_slash2","0" };
cvar_t	sk_zombie_soldier_dmg_both_slash3 = { "sk_zombie_soldier_dmg_both_slash3","0" };

cvar_t	sk_zombie_soldier_head1 = { "sk_zombie_soldier_head1","0" };
cvar_t	sk_zombie_soldier_head2 = { "sk_zombie_soldier_head2","0" };
cvar_t	sk_zombie_soldier_head3 = { "sk_zombie_soldier_head3","0" };

cvar_t	sk_zombie_soldier_chest1 = { "sk_zombie_soldier_chest1","0" };
cvar_t	sk_zombie_soldier_chest2 = { "sk_zombie_soldier_chest2","0" };
cvar_t	sk_zombie_soldier_chest3 = { "sk_zombie_soldier_chest3","0" };

cvar_t	sk_zombie_soldier_stomach1 = { "sk_zombie_soldier_stomach1","0" };
cvar_t	sk_zombie_soldier_stomach2 = { "sk_zombie_soldier_stomach2","0" };
cvar_t	sk_zombie_soldier_stomach3 = { "sk_zombie_soldier_stomach3","0" };

cvar_t	sk_zombie_soldier_leg1 = { "sk_zombie_soldier_leg1","0" };
cvar_t	sk_zombie_soldier_leg2 = { "sk_zombie_soldier_leg2","0" };
cvar_t	sk_zombie_soldier_leg3 = { "sk_zombie_soldier_leg3","0" };

cvar_t	sk_zombie_soldier_arm1 = { "sk_zombie_soldier_arm1","0" };
cvar_t	sk_zombie_soldier_arm2 = { "sk_zombie_soldier_arm2","0" };
cvar_t	sk_zombie_soldier_arm3 = { "sk_zombie_soldier_arm3","0" };

// Zombie Barney
cvar_t	sk_zombie_barney_health1 = { "sk_zombie_barney_health1","0" };
cvar_t	sk_zombie_barney_health2 = { "sk_zombie_barney_health2","0" };
cvar_t	sk_zombie_barney_health3 = { "sk_zombie_barney_health3","0" };

cvar_t	sk_zombie_barney_dmg_one_slash1 = { "sk_zombie_barney_dmg_one_slash1","0" };
cvar_t	sk_zombie_barney_dmg_one_slash2 = { "sk_zombie_barney_dmg_one_slash2","0" };
cvar_t	sk_zombie_barney_dmg_one_slash3 = { "sk_zombie_barney_dmg_one_slash3","0" };

cvar_t	sk_zombie_barney_dmg_both_slash1 = { "sk_zombie_barney_dmg_both_slash1","0" };
cvar_t	sk_zombie_barney_dmg_both_slash2 = { "sk_zombie_barney_dmg_both_slash2","0" };
cvar_t	sk_zombie_barney_dmg_both_slash3 = { "sk_zombie_barney_dmg_both_slash3","0" };

cvar_t	sk_zombie_barney_head1 = { "sk_zombie_barney_head1","0" };
cvar_t	sk_zombie_barney_head2 = { "sk_zombie_barney_head2","0" };
cvar_t	sk_zombie_barney_head3 = { "sk_zombie_barney_head3","0" };

cvar_t	sk_zombie_barney_chest1 = { "sk_zombie_barney_chest1","0" };
cvar_t	sk_zombie_barney_chest2 = { "sk_zombie_barney_chest2","0" };
cvar_t	sk_zombie_barney_chest3 = { "sk_zombie_barney_chest3","0" };

cvar_t	sk_zombie_barney_stomach1 = { "sk_zombie_barney_stomach1","0" };
cvar_t	sk_zombie_barney_stomach2 = { "sk_zombie_barney_stomach2","0" };
cvar_t	sk_zombie_barney_stomach3 = { "sk_zombie_barney_stomach3","0" };

cvar_t	sk_zombie_barney_leg1 = { "sk_zombie_barney_leg1","0" };
cvar_t	sk_zombie_barney_leg2 = { "sk_zombie_barney_leg2","0" };
cvar_t	sk_zombie_barney_leg3 = { "sk_zombie_barney_leg3","0" };

cvar_t	sk_zombie_barney_arm1 = { "sk_zombie_barney_arm1","0" };
cvar_t	sk_zombie_barney_arm2 = { "sk_zombie_barney_arm2","0" };
cvar_t	sk_zombie_barney_arm3 = { "sk_zombie_barney_arm3","0" };

// Zombie Construction
cvar_t	sk_zombie_construction_health1 = { "sk_zombie_construction_health1","0" };
cvar_t	sk_zombie_construction_health2 = { "sk_zombie_construction_health2","0" };
cvar_t	sk_zombie_construction_health3 = { "sk_zombie_construction_health3","0" };

cvar_t	sk_zombie_construction_dmg_one_slash1 = { "sk_zombie_construction_dmg_one_slash1","0" };
cvar_t	sk_zombie_construction_dmg_one_slash2 = { "sk_zombie_construction_dmg_one_slash2","0" };
cvar_t	sk_zombie_construction_dmg_one_slash3 = { "sk_zombie_construction_dmg_one_slash3","0" };

cvar_t	sk_zombie_construction_dmg_both_slash1 = { "sk_zombie_construction_dmg_both_slash1","0" };
cvar_t	sk_zombie_construction_dmg_both_slash2 = { "sk_zombie_construction_dmg_both_slash2","0" };
cvar_t	sk_zombie_construction_dmg_both_slash3 = { "sk_zombie_construction_dmg_both_slash3","0" };

cvar_t	sk_zombie_construction_head1 = { "sk_zombie_construction_head1","0" };
cvar_t	sk_zombie_construction_head2 = { "sk_zombie_construction_head2","0" };
cvar_t	sk_zombie_construction_head3 = { "sk_zombie_construction_head3","0" };

cvar_t	sk_zombie_construction_chest1 = { "sk_zombie_construction_chest1","0" };
cvar_t	sk_zombie_construction_chest2 = { "sk_zombie_construction_chest2","0" };
cvar_t	sk_zombie_construction_chest3 = { "sk_zombie_construction_chest3","0" };

cvar_t	sk_zombie_construction_stomach1 = { "sk_zombie_construction_stomach1","0" };
cvar_t	sk_zombie_construction_stomach2 = { "sk_zombie_construction_stomach2","0" };
cvar_t	sk_zombie_construction_stomach3 = { "sk_zombie_construction_stomach3","0" };

cvar_t	sk_zombie_construction_leg1 = { "sk_zombie_construction_leg1","0" };
cvar_t	sk_zombie_construction_leg2 = { "sk_zombie_construction_leg2","0" };
cvar_t	sk_zombie_construction_leg3 = { "sk_zombie_construction_leg3","0" };

cvar_t	sk_zombie_construction_arm1 = { "sk_zombie_construction_arm1","0" };
cvar_t	sk_zombie_construction_arm2 = { "sk_zombie_construction_arm2","0" };
cvar_t	sk_zombie_construction_arm3 = { "sk_zombie_construction_arm3","0" };

//=========================================================
// NPCs: Pit Drone
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================
cvar_t	sk_pitdrone_health1 = { "sk_pitdrone_health1", "0" };
cvar_t	sk_pitdrone_health2 = { "sk_pitdrone_health2", "0" };
cvar_t	sk_pitdrone_health3 = { "sk_pitdrone_health3", "0" };

cvar_t	sk_pitdrone_dmg_bite1 = { "sk_pitdrone_dmg_bite1", "0" };
cvar_t	sk_pitdrone_dmg_bite2 = { "sk_pitdrone_dmg_bite2", "0" };
cvar_t	sk_pitdrone_dmg_bite3 = { "sk_pitdrone_dmg_bite3", "0" };

cvar_t	sk_pitdrone_dmg_whip1 = { "sk_pitdrone_dmg_whip1", "0" };
cvar_t	sk_pitdrone_dmg_whip2 = { "sk_pitdrone_dmg_whip2", "0" };
cvar_t	sk_pitdrone_dmg_whip3 = { "sk_pitdrone_dmg_whip3", "0" };

cvar_t	sk_pitdrone_dmg_spit1 = { "sk_pitdrone_dmg_spit1", "0" };
cvar_t	sk_pitdrone_dmg_spit2 = { "sk_pitdrone_dmg_spit2", "0" };
cvar_t	sk_pitdrone_dmg_spit3 = { "sk_pitdrone_dmg_spit3", "0" };

cvar_t	sk_pitdrone_head1 = { "sk_pitdrone_head1","0" };
cvar_t	sk_pitdrone_head2 = { "sk_pitdrone_head2","0" };
cvar_t	sk_pitdrone_head3 = { "sk_pitdrone_head3","0" };

cvar_t	sk_pitdrone_chest1 = { "sk_pitdrone_chest1","0" };
cvar_t	sk_pitdrone_chest2 = { "sk_pitdrone_chest2","0" };
cvar_t	sk_pitdrone_chest3 = { "sk_pitdrone_chest3","0" };

cvar_t	sk_pitdrone_stomach1 = { "sk_pitdrone_stomach1","0" };
cvar_t	sk_pitdrone_stomach2 = { "sk_pitdrone_stomach2","0" };
cvar_t	sk_pitdrone_stomach3 = { "sk_pitdrone_stomach3","0" };

cvar_t	sk_pitdrone_leg1 = { "sk_pitdrone_leg1","0" };
cvar_t	sk_pitdrone_leg2 = { "sk_pitdrone_leg2","0" };
cvar_t	sk_pitdrone_leg3 = { "sk_pitdrone_leg3","0" };

cvar_t	sk_pitdrone_arm1 = { "sk_pitdrone_arm1","0" };
cvar_t	sk_pitdrone_arm2 = { "sk_pitdrone_arm2","0" };
cvar_t	sk_pitdrone_arm3 = { "sk_pitdrone_arm3","0" };

//=========================================================
// NPCs: Voltigore
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================
cvar_t	sk_voltigore_health1 = { "sk_voltigore_health1", "0" };
cvar_t	sk_voltigore_health2 = { "sk_voltigore_health2", "0" };
cvar_t	sk_voltigore_health3 = { "sk_voltigore_health3", "0" };

cvar_t	sk_voltigore_dmg_punch1 = { "sk_voltigore_dmg_punch1", "0" };
cvar_t	sk_voltigore_dmg_punch2 = { "sk_voltigore_dmg_punch2", "0" };
cvar_t	sk_voltigore_dmg_punch3 = { "sk_voltigore_dmg_punch3", "0" };

cvar_t	sk_voltigore_dmg_beam1 = { "sk_voltigore_dmg_beam1", "0" };
cvar_t	sk_voltigore_dmg_beam2 = { "sk_voltigore_dmg_beam2", "0" };
cvar_t	sk_voltigore_dmg_beam3 = { "sk_voltigore_dmg_beam3", "0" };

cvar_t	sk_voltigore_head1 = { "sk_voltigore_head1","0" };
cvar_t	sk_voltigore_head2 = { "sk_voltigore_head2","0" };
cvar_t	sk_voltigore_head3 = { "sk_voltigore_head3","0" };

cvar_t	sk_voltigore_chest1 = { "sk_voltigore_chest1","0" };
cvar_t	sk_voltigore_chest2 = { "sk_voltigore_chest2","0" };
cvar_t	sk_voltigore_chest3 = { "sk_voltigore_chest3","0" };

cvar_t	sk_voltigore_stomach1 = { "sk_voltigore_stomach1","0" };
cvar_t	sk_voltigore_stomach2 = { "sk_voltigore_stomach2","0" };
cvar_t	sk_voltigore_stomach3 = { "sk_voltigore_stomach3","0" };

cvar_t	sk_voltigore_leg1 = { "sk_voltigore_leg1","0" };
cvar_t	sk_voltigore_leg2 = { "sk_voltigore_leg2","0" };
cvar_t	sk_voltigore_leg3 = { "sk_voltigore_leg3","0" };

cvar_t	sk_voltigore_arm1 = { "sk_voltigore_arm1","0" };
cvar_t	sk_voltigore_arm2 = { "sk_voltigore_arm2","0" };
cvar_t	sk_voltigore_arm3 = { "sk_voltigore_arm3","0" };

//=========================================================
// NPCs: #########################
// For Spirit of Half-Life v1.9: Opposing-Force Edition
//=========================================================

// Opposing-Force
// Ally Grunt 
cvar_t	sk_hgrunt_ally_health1 = {"sk_hgrunt_ally_health1","0"};
cvar_t	sk_hgrunt_ally_health2 = {"sk_hgrunt_ally_health2","0"};
cvar_t	sk_hgrunt_ally_health3 = {"sk_hgrunt_ally_health3","0"};

cvar_t	sk_hgrunt_ally_kick1 = {"sk_hgrunt_ally_kick1","0"};
cvar_t	sk_hgrunt_ally_kick2 = {"sk_hgrunt_ally_kick2","0"};
cvar_t	sk_hgrunt_ally_kick3 = {"sk_hgrunt_ally_kick3","0"};

cvar_t	sk_hgrunt_ally_pellets1 = {"sk_hgrunt_ally_pellets1","0"};
cvar_t	sk_hgrunt_ally_pellets2 = {"sk_hgrunt_ally_pellets2","0"};
cvar_t	sk_hgrunt_ally_pellets3 = {"sk_hgrunt_ally_pellets3","0"};

cvar_t	sk_hgrunt_ally_gspeed1 = {"sk_hgrunt_ally_gspeed1","0"};
cvar_t	sk_hgrunt_ally_gspeed2 = {"sk_hgrunt_ally_gspeed2","0"};
cvar_t	sk_hgrunt_ally_gspeed3 = {"sk_hgrunt_ally_gspeed3","0"};

cvar_t	sk_hgrunt_ally_head1 = { "sk_hgrunt_ally_head1","0" };
cvar_t	sk_hgrunt_ally_head2 = { "sk_hgrunt_ally_head2","0" };
cvar_t	sk_hgrunt_ally_head3 = { "sk_hgrunt_ally_head3","0" };

cvar_t	sk_hgrunt_ally_chest1 = { "sk_hgrunt_ally_chest1","0" };
cvar_t	sk_hgrunt_ally_chest2 = { "sk_hgrunt_ally_chest2","0" };
cvar_t	sk_hgrunt_ally_chest3 = { "sk_hgrunt_ally_chest3","0" };

cvar_t	sk_hgrunt_ally_stomach1 = { "sk_hgrunt_ally_stomach1","0" };
cvar_t	sk_hgrunt_ally_stomach2 = { "sk_hgrunt_ally_stomach2","0" };
cvar_t	sk_hgrunt_ally_stomach3 = { "sk_hgrunt_ally_stomach3","0" };

cvar_t	sk_hgrunt_ally_leg1 = { "sk_hgrunt_ally_leg1","0" };
cvar_t	sk_hgrunt_ally_leg2 = { "sk_hgrunt_ally_leg2","0" };
cvar_t	sk_hgrunt_ally_leg3 = { "sk_hgrunt_ally_leg3","0" };

cvar_t	sk_hgrunt_ally_arm1 = { "sk_hgrunt_ally_arm1","0" };
cvar_t	sk_hgrunt_ally_arm2 = { "sk_hgrunt_ally_arm2","0" };
cvar_t	sk_hgrunt_ally_arm3 = { "sk_hgrunt_ally_arm3","0" };

// Ally Grunt Medic
cvar_t	sk_medic_ally_health1 = {"sk_medic_ally_health1","0"};
cvar_t	sk_medic_ally_health2 = {"sk_medic_ally_health2","0"};
cvar_t	sk_medic_ally_health3 = {"sk_medic_ally_health3","0"};

cvar_t	sk_medic_ally_kick1 = {"sk_medic_ally_kick1","0"};
cvar_t	sk_medic_ally_kick2 = {"sk_medic_ally_kick2","0"};
cvar_t	sk_medic_ally_kick3 = {"sk_medic_ally_kick3","0"};

cvar_t	sk_medic_ally_heal1 = {"sk_medic_ally_heal1","0"};
cvar_t	sk_medic_ally_heal2 = {"sk_medic_ally_heal2","0"};
cvar_t	sk_medic_ally_heal3 = {"sk_medic_ally_heal3","0"};

// Ally Grunt Torch
cvar_t	sk_torch_ally_health1 = {"sk_torch_ally_health1","0"};
cvar_t	sk_torch_ally_health2 = {"sk_torch_ally_health2","0"};
cvar_t	sk_torch_ally_health3 = {"sk_torch_ally_health3","0"};

cvar_t	sk_torch_ally_kick1 = {"sk_torch_ally_kick1","0"};
cvar_t	sk_torch_ally_kick2 = {"sk_torch_ally_kick2","0"};
cvar_t	sk_torch_ally_kick3 = {"sk_torch_ally_kick3","0"};

// Pitworm
cvar_t	sk_pitworm_health1 = { "sk_pitworm_health1", "0" };
cvar_t	sk_pitworm_health2 = { "sk_pitworm_health2", "0" };
cvar_t	sk_pitworm_health3 = { "sk_pitworm_health3", "0" };

cvar_t	sk_pitworm_dmg_swipe1 = { "sk_pitworm_dmg_swipe1", "0" };
cvar_t	sk_pitworm_dmg_swipe2 = { "sk_pitworm_dmg_swipe2", "0" };
cvar_t	sk_pitworm_dmg_swipe3 = { "sk_pitworm_dmg_swipe3", "0" };

cvar_t	sk_pitworm_dmg_beam1 = { "sk_pitworm_dmg_beam1", "0" };
cvar_t	sk_pitworm_dmg_beam2 = { "sk_pitworm_dmg_beam2", "0" };
cvar_t	sk_pitworm_dmg_beam3 = { "sk_pitworm_dmg_beam3", "0" };

// Shock Roach
cvar_t	sk_shockroach_health1 = { "sk_shockroach_health1", "0" };
cvar_t	sk_shockroach_health2 = { "sk_shockroach_health2", "0" };
cvar_t	sk_shockroach_health3 = { "sk_shockroach_health3", "0" };

cvar_t	sk_shockroach_dmg_bite1 = { "sk_shockroach_dmg_bite1", "0" };
cvar_t	sk_shockroach_dmg_bite2 = { "sk_shockroach_dmg_bite2", "0" };
cvar_t	sk_shockroach_dmg_bite3 = { "sk_shockroach_dmg_bite3", "0" };

cvar_t	sk_shockroach_lifespan1 = { "sk_shockroach_lifespan1", "0" };
cvar_t	sk_shockroach_lifespan2 = { "sk_shockroach_lifespan2", "0" };
cvar_t	sk_shockroach_lifespan3 = { "sk_shockroach_lifespan3", "0" };

// Gonome
cvar_t	sk_gonome_health1 = { "sk_gonome_health1", "0" };
cvar_t	sk_gonome_health2 = { "sk_gonome_health2", "0" };
cvar_t	sk_gonome_health3 = { "sk_gonome_health3", "0" };

cvar_t	sk_gonome_dmg_one_slash1 = { "sk_gonome_dmg_one_slash1", "0" };
cvar_t	sk_gonome_dmg_one_slash2 = { "sk_gonome_dmg_one_slash2", "0" };
cvar_t	sk_gonome_dmg_one_slash3 = { "sk_gonome_dmg_one_slash3", "0" };

cvar_t	sk_gonome_dmg_guts1 = { "sk_gonome_dmg_guts1", "0" };
cvar_t	sk_gonome_dmg_guts2 = { "sk_gonome_dmg_guts2", "0" };
cvar_t	sk_gonome_dmg_guts3 = { "sk_gonome_dmg_guts3", "0" };

cvar_t	sk_gonome_dmg_one_bite1 = { "sk_gonome_dmg_one_bite1", "0" };
cvar_t	sk_gonome_dmg_one_bite2 = { "sk_gonome_dmg_one_bite2", "0" };
cvar_t	sk_gonome_dmg_one_bite3 = { "sk_gonome_dmg_one_bite3", "0" };

// ShockTrooper 
cvar_t	sk_shocktrooper_health1 = { "sk_shocktrooper_health1", "0" };
cvar_t	sk_shocktrooper_health2 = { "sk_shocktrooper_health2", "0" };
cvar_t	sk_shocktrooper_health3 = { "sk_shocktrooper_health3", "0" };

cvar_t	sk_shocktrooper_kick1 = { "sk_shocktrooper_kick1", "0" };
cvar_t	sk_shocktrooper_kick2 = { "sk_shocktrooper_kick2", "0" };
cvar_t	sk_shocktrooper_kick3 = { "sk_shocktrooper_kick3", "0" };

cvar_t	sk_shocktrooper_gspeed1 = { "sk_shocktrooper_gspeed1", "0" };
cvar_t	sk_shocktrooper_gspeed2 = { "sk_shocktrooper_gspeed2", "0" };
cvar_t	sk_shocktrooper_gspeed3 = { "sk_shocktrooper_gspeed3", "0" };

cvar_t	sk_shocktrooper_maxcharge1 = { "sk_shocktrooper_maxcharge1", "0" };
cvar_t	sk_shocktrooper_maxcharge2 = { "sk_shocktrooper_maxcharge2", "0" };
cvar_t	sk_shocktrooper_maxcharge3 = { "sk_shocktrooper_maxcharge3", "0" };

cvar_t	sk_shocktrooper_rchgspeed1 = { "sk_shocktrooper_rchgspeed1", "0" };
cvar_t	sk_shocktrooper_rchgspeed2 = { "sk_shocktrooper_rchgspeed2", "0" };
cvar_t	sk_shocktrooper_rchgspeed3 = { "sk_shocktrooper_rchgspeed3", "0" };

//Turret
cvar_t	sk_turret_health1 = {"sk_turret_health1","0"};
cvar_t	sk_turret_health2 = {"sk_turret_health2","0"};
cvar_t	sk_turret_health3 = {"sk_turret_health3","0"};

// MiniTurret
cvar_t	sk_miniturret_health1 = {"sk_miniturret_health1","0"};
cvar_t	sk_miniturret_health2 = {"sk_miniturret_health2","0"};
cvar_t	sk_miniturret_health3 = {"sk_miniturret_health3","0"};

// Sentry Turret
cvar_t	sk_sentry_health1 = {"sk_sentry_health1","0"};
cvar_t	sk_sentry_health2 = {"sk_sentry_health2","0"};
cvar_t	sk_sentry_health3 = {"sk_sentry_health3","0"};

// PLAYER WEAPONS

// Crowbar whack
cvar_t	sk_plr_crowbar1 = {"sk_plr_crowbar1","0"};
cvar_t	sk_plr_crowbar2 = {"sk_plr_crowbar2","0"};
cvar_t	sk_plr_crowbar3 = {"sk_plr_crowbar3","0"};

// Pipe Wrench
cvar_t	sk_plr_pipewrench1 = { "sk_plr_pipewrench1","0" };
cvar_t	sk_plr_pipewrench2 = { "sk_plr_pipewrench2","0" };
cvar_t	sk_plr_pipewrench3 = { "sk_plr_pipewrench3","0" };

// Knife whack
cvar_t	sk_plr_knife1 = { "sk_plr_knife1","0" };
cvar_t	sk_plr_knife2 = { "sk_plr_knife2","0" };
cvar_t	sk_plr_knife3 = { "sk_plr_knife3","0" };

cvar_t	sk_plr_knife_charge1 = { "sk_plr_knife_charge1","0" };
cvar_t	sk_plr_knife_charge2 = { "sk_plr_knife_charge2","0" };
cvar_t	sk_plr_knife_charge3 = { "sk_plr_knife_charge3","0" };

// Glock Round
cvar_t	sk_plr_9mm_bullet1 = {"sk_plr_9mm_bullet1","0"};
cvar_t	sk_plr_9mm_bullet2 = {"sk_plr_9mm_bullet2","0"};
cvar_t	sk_plr_9mm_bullet3 = {"sk_plr_9mm_bullet3","0"};

// 357 Round
cvar_t	sk_plr_357_bullet1 = {"sk_plr_357_bullet1","0"};
cvar_t	sk_plr_357_bullet2 = {"sk_plr_357_bullet2","0"};
cvar_t	sk_plr_357_bullet3 = {"sk_plr_357_bullet3","0"};

// 762 Round
cvar_t	sk_plr_762_bullet1 = { "sk_plr_762_bullet1","0" };
cvar_t	sk_plr_762_bullet2 = { "sk_plr_762_bullet2","0" };
cvar_t	sk_plr_762_bullet3 = { "sk_plr_762_bullet3","0" };

// MP5 Round
cvar_t	sk_plr_9mmAR_bullet1 = {"sk_plr_9mmAR_bullet1","0"};
cvar_t	sk_plr_9mmAR_bullet2 = {"sk_plr_9mmAR_bullet2","0"};
cvar_t	sk_plr_9mmAR_bullet3 = {"sk_plr_9mmAR_bullet3","0"};

// M203 grenade
cvar_t	sk_plr_9mmAR_grenade1 = {"sk_plr_9mmAR_grenade1","0"};
cvar_t	sk_plr_9mmAR_grenade2 = {"sk_plr_9mmAR_grenade2","0"};
cvar_t	sk_plr_9mmAR_grenade3 = {"sk_plr_9mmAR_grenade3","0"};

// Shotgun buckshot
cvar_t	sk_plr_buckshot1 = {"sk_plr_buckshot1","0"};
cvar_t	sk_plr_buckshot2 = {"sk_plr_buckshot2","0"};
cvar_t	sk_plr_buckshot3 = {"sk_plr_buckshot3","0"};

// Crossbow
cvar_t	sk_plr_xbow_bolt_client1 = {"sk_plr_xbow_bolt_client1","0"};
cvar_t	sk_plr_xbow_bolt_client2 = {"sk_plr_xbow_bolt_client2","0"};
cvar_t	sk_plr_xbow_bolt_client3 = {"sk_plr_xbow_bolt_client3","0"};

cvar_t	sk_plr_xbow_bolt_monster1 = {"sk_plr_xbow_bolt_monster1","0"};
cvar_t	sk_plr_xbow_bolt_monster2 = {"sk_plr_xbow_bolt_monster2","0"};
cvar_t	sk_plr_xbow_bolt_monster3 = {"sk_plr_xbow_bolt_monster3","0"};

// RPG
cvar_t	sk_plr_rpg1 = {"sk_plr_rpg1","0"};
cvar_t	sk_plr_rpg2 = {"sk_plr_rpg2","0"};
cvar_t	sk_plr_rpg3 = {"sk_plr_rpg3","0"};

// Zero Point Generator
cvar_t	sk_plr_gauss1 = {"sk_plr_gauss1","0"};
cvar_t	sk_plr_gauss2 = {"sk_plr_gauss2","0"};
cvar_t	sk_plr_gauss3 = {"sk_plr_gauss3","0"};

// Tau Cannon
cvar_t	sk_plr_egon_narrow1 = {"sk_plr_egon_narrow1","0"};
cvar_t	sk_plr_egon_narrow2 = {"sk_plr_egon_narrow2","0"};
cvar_t	sk_plr_egon_narrow3 = {"sk_plr_egon_narrow3","0"};

cvar_t	sk_plr_egon_wide1 = {"sk_plr_egon_wide1","0"};
cvar_t	sk_plr_egon_wide2 = {"sk_plr_egon_wide2","0"};
cvar_t	sk_plr_egon_wide3 = {"sk_plr_egon_wide3","0"};

// Hand Grendade
cvar_t	sk_plr_hand_grenade1 = {"sk_plr_hand_grenade1","0"};
cvar_t	sk_plr_hand_grenade2 = {"sk_plr_hand_grenade2","0"};
cvar_t	sk_plr_hand_grenade3 = {"sk_plr_hand_grenade3","0"};

// Satchel Charge
cvar_t	sk_plr_satchel1	= {"sk_plr_satchel1","0"};
cvar_t	sk_plr_satchel2	= {"sk_plr_satchel2","0"};
cvar_t	sk_plr_satchel3	= {"sk_plr_satchel3","0"};

// Tripmine
cvar_t	sk_plr_tripmine1 = {"sk_plr_tripmine1","0"};
cvar_t	sk_plr_tripmine2 = {"sk_plr_tripmine2","0"};
cvar_t	sk_plr_tripmine3 = {"sk_plr_tripmine3","0"};

// 556
cvar_t	sk_plr_556_bullet1 = { "sk_plr_556_bullet1", "0" };
cvar_t	sk_plr_556_bullet2 = { "sk_plr_556_bullet2", "0" };
cvar_t	sk_plr_556_bullet3 = { "sk_plr_556_bullet3", "0" };

// WORLD WEAPONS
cvar_t	sk_12mm_bullet1 = {"sk_12mm_bullet1","0"};
cvar_t	sk_12mm_bullet2 = {"sk_12mm_bullet2","0"};
cvar_t	sk_12mm_bullet3 = {"sk_12mm_bullet3","0"};

cvar_t	sk_9mmAR_bullet1 = {"sk_9mmAR_bullet1","0"};
cvar_t	sk_9mmAR_bullet2 = {"sk_9mmAR_bullet2","0"};
cvar_t	sk_9mmAR_bullet3 = {"sk_9mmAR_bullet3","0"};

cvar_t	sk_9mm_bullet1 = {"sk_9mm_bullet1","0"};
cvar_t	sk_9mm_bullet2 = {"sk_9mm_bullet2","0"};
cvar_t	sk_9mm_bullet3 = {"sk_9mm_bullet3","0"};

// 556
cvar_t	sk_556_bullet1 = { "sk_556_bullet1", "0" };
cvar_t	sk_556_bullet2 = { "sk_556_bullet2", "0" };
cvar_t	sk_556_bullet3 = { "sk_556_bullet3", "0" };

// HORNET
cvar_t	sk_hornet_dmg1 = {"sk_hornet_dmg1","0"};
cvar_t	sk_hornet_dmg2 = {"sk_hornet_dmg2","0"};
cvar_t	sk_hornet_dmg3 = {"sk_hornet_dmg3","0"};

// SHOCKROACH
cvar_t	sk_plr_shockroachs1 = { "sk_plr_shockroachs1", "0" };
cvar_t	sk_plr_shockroachs2 = { "sk_plr_shockroachs2", "0" };
cvar_t	sk_plr_shockroachs3 = { "sk_plr_shockroachs3", "0" };

cvar_t	sk_plr_shockroachm1 = { "sk_plr_shockroachm1", "0" };
cvar_t	sk_plr_shockroachm2 = { "sk_plr_shockroachm2", "0" };
cvar_t	sk_plr_shockroachm3 = { "sk_plr_shockroachm3", "0" };

// SPOREGRENADE
cvar_t	sk_plr_spore1 = { "sk_plr_spore1", "0" };
cvar_t	sk_plr_spore2 = { "sk_plr_spore2", "0" };
cvar_t	sk_plr_spore3 = { "sk_plr_spore3", "0" };

// HEALTH/CHARGE
cvar_t	sk_suitcharger1	= { "sk_suitcharger1","0" };
cvar_t	sk_suitcharger2	= { "sk_suitcharger2","0" };		
cvar_t	sk_suitcharger3	= { "sk_suitcharger3","0" };		

cvar_t	sk_battery1	= { "sk_battery1","0" };			
cvar_t	sk_battery2	= { "sk_battery2","0" };			
cvar_t	sk_battery3	= { "sk_battery3","0" };			

cvar_t	sk_healthcharger1	= { "sk_healthcharger1","0" };		
cvar_t	sk_healthcharger2	= { "sk_healthcharger2","0" };		
cvar_t	sk_healthcharger3	= { "sk_healthcharger3","0" };		

cvar_t	sk_healthkit1	= { "sk_healthkit1","0" };		
cvar_t	sk_healthkit2	= { "sk_healthkit2","0" };		
cvar_t	sk_healthkit3	= { "sk_healthkit3","0" };		

cvar_t	sk_scientist_heal1	= { "sk_scientist_heal1","0" };	
cvar_t	sk_scientist_heal2	= { "sk_scientist_heal2","0" };	
cvar_t	sk_scientist_heal3	= { "sk_scientist_heal3","0" };	

// FLASHLIGHT CHARGE VALUE
cvar_t	sk_flashcharge1	= { "sk_flashcharge1","0" };
cvar_t	sk_flashcharge2	= { "sk_flashcharge2","0" };		
cvar_t	sk_flashcharge3	= { "sk_flashcharge3","0" };

// monster damage adjusters
cvar_t	sk_monster_head1	= { "sk_monster_head1","2" };
cvar_t	sk_monster_head2	= { "sk_monster_head2","2" };
cvar_t	sk_monster_head3	= { "sk_monster_head3","2" };

cvar_t	sk_monster_chest1	= { "sk_monster_chest1","1" };
cvar_t	sk_monster_chest2	= { "sk_monster_chest2","1" };
cvar_t	sk_monster_chest3	= { "sk_monster_chest3","1" };

cvar_t	sk_monster_stomach1	= { "sk_monster_stomach1","1" };
cvar_t	sk_monster_stomach2	= { "sk_monster_stomach2","1" };
cvar_t	sk_monster_stomach3	= { "sk_monster_stomach3","1" };

cvar_t	sk_monster_arm1	= { "sk_monster_arm1","1" };
cvar_t	sk_monster_arm2	= { "sk_monster_arm2","1" };
cvar_t	sk_monster_arm3	= { "sk_monster_arm3","1" };

cvar_t	sk_monster_leg1	= { "sk_monster_leg1","1" };
cvar_t	sk_monster_leg2	= { "sk_monster_leg2","1" };
cvar_t	sk_monster_leg3	= { "sk_monster_leg3","1" };

// player damage adjusters
cvar_t	sk_player_head1	= { "sk_player_head1","2" };
cvar_t	sk_player_head2	= { "sk_player_head2","2" };
cvar_t	sk_player_head3	= { "sk_player_head3","2" };

cvar_t	sk_player_chest1	= { "sk_player_chest1","1" };
cvar_t	sk_player_chest2	= { "sk_player_chest2","1" };
cvar_t	sk_player_chest3	= { "sk_player_chest3","1" };

cvar_t	sk_player_stomach1	= { "sk_player_stomach1","1" };
cvar_t	sk_player_stomach2	= { "sk_player_stomach2","1" };
cvar_t	sk_player_stomach3	= { "sk_player_stomach3","1" };

cvar_t	sk_player_arm1	= { "sk_player_arm1","1" };
cvar_t	sk_player_arm2	= { "sk_player_arm2","1" };
cvar_t	sk_player_arm3	= { "sk_player_arm3","1" };

cvar_t	sk_player_leg1	= { "sk_player_leg1","1" };
cvar_t	sk_player_leg2	= { "sk_player_leg2","1" };
cvar_t	sk_player_leg3	= { "sk_player_leg3","1" };

// END Cvars for Skill Level settings

// Register your console variables here
// This gets called one time when the game is initialied
void GameDLLInit( void )
{
	// Register cvars here:
	g_psv_gravity = CVAR_GET_POINTER( "sv_gravity" );
	g_psv_aim = CVAR_GET_POINTER( "sv_aim" );
	g_footsteps = CVAR_GET_POINTER( "mp_footsteps" );

	CVAR_REGISTER (&displaysoundlist);

	CVAR_REGISTER (&teamplay);
	CVAR_REGISTER (&fraglimit);
	CVAR_REGISTER (&timelimit);

	CVAR_REGISTER (&fragsleft);
	CVAR_REGISTER (&timeleft);

	CVAR_REGISTER (&friendlyfire);
	CVAR_REGISTER (&falldamage);
	CVAR_REGISTER (&weaponstay);
	CVAR_REGISTER (&forcerespawn);
	CVAR_REGISTER (&flashlight);
	CVAR_REGISTER (&aimcrosshair);
	CVAR_REGISTER (&decalfrequency);
	CVAR_REGISTER (&teamlist);
	CVAR_REGISTER (&teamoverride);
	CVAR_REGISTER (&defaultteam);
	CVAR_REGISTER (&allowmonsters);
	CVAR_REGISTER (&impulsetarget); //LRC
	CVAR_REGISTER (&mw_debug); //LRC
	CVAR_REGISTER (&mp_chattime);

// REGISTER CVARS FOR SKILL LEVEL STUFF
	// Agrunt
	CVAR_REGISTER ( &sk_agrunt_health1 );
	CVAR_REGISTER ( &sk_agrunt_health2 );
	CVAR_REGISTER ( &sk_agrunt_health3 );

	CVAR_REGISTER ( &sk_agrunt_dmg_punch1 );
	CVAR_REGISTER ( &sk_agrunt_dmg_punch2 );
	CVAR_REGISTER ( &sk_agrunt_dmg_punch3 );

	// Apache
	CVAR_REGISTER ( &sk_apache_health1 );
	CVAR_REGISTER ( &sk_apache_health2 );
	CVAR_REGISTER ( &sk_apache_health3 );

	// Osprey
	CVAR_REGISTER(&sk_osprey_health1);
	CVAR_REGISTER(&sk_osprey_health2);
	CVAR_REGISTER(&sk_osprey_health3);

	// Apache BlackOP
	CVAR_REGISTER(&sk_apache_blkop_health1);
	CVAR_REGISTER(&sk_apache_blkop_health2);
	CVAR_REGISTER(&sk_apache_blkop_health3);

	// Osprey BlackOP
	CVAR_REGISTER(&sk_osprey_blkop_health1);
	CVAR_REGISTER(&sk_osprey_blkop_health2);
	CVAR_REGISTER(&sk_osprey_blkop_health3);

	// Barney
	CVAR_REGISTER ( &sk_barney_health1 );
	CVAR_REGISTER ( &sk_barney_health2 );
	CVAR_REGISTER ( &sk_barney_health3 );

	CVAR_REGISTER(&sk_barney_head1);
	CVAR_REGISTER(&sk_barney_head2);
	CVAR_REGISTER(&sk_barney_head3);

	CVAR_REGISTER(&sk_barney_chest1);
	CVAR_REGISTER(&sk_barney_chest2);
	CVAR_REGISTER(&sk_barney_chest3);

	CVAR_REGISTER(&sk_barney_stomach1);
	CVAR_REGISTER(&sk_barney_stomach2);
	CVAR_REGISTER(&sk_barney_stomach3);

	CVAR_REGISTER(&sk_barney_leg1);
	CVAR_REGISTER(&sk_barney_leg2);
	CVAR_REGISTER(&sk_barney_leg3);

	CVAR_REGISTER(&sk_barney_arm1);
	CVAR_REGISTER(&sk_barney_arm2);
	CVAR_REGISTER(&sk_barney_arm3);

	// Barniel
	CVAR_REGISTER(&sk_barniel_health1);
	CVAR_REGISTER(&sk_barniel_health2);
	CVAR_REGISTER(&sk_barniel_health3);

	CVAR_REGISTER(&sk_barniel_head1);
	CVAR_REGISTER(&sk_barniel_head2);
	CVAR_REGISTER(&sk_barniel_head3);

	CVAR_REGISTER(&sk_barniel_chest1);
	CVAR_REGISTER(&sk_barniel_chest2);
	CVAR_REGISTER(&sk_barniel_chest3);

	CVAR_REGISTER(&sk_barniel_stomach1);
	CVAR_REGISTER(&sk_barniel_stomach2);
	CVAR_REGISTER(&sk_barniel_stomach3);

	CVAR_REGISTER(&sk_barniel_leg1);
	CVAR_REGISTER(&sk_barniel_leg2);
	CVAR_REGISTER(&sk_barniel_leg3);

	CVAR_REGISTER(&sk_barniel_arm1);
	CVAR_REGISTER(&sk_barniel_arm2);
	CVAR_REGISTER(&sk_barniel_arm3);

	// Otis Laurey
	CVAR_REGISTER(&sk_otis_health1);
	CVAR_REGISTER(&sk_otis_health2);
	CVAR_REGISTER(&sk_otis_health3);

	CVAR_REGISTER(&sk_otis_head1);
	CVAR_REGISTER(&sk_otis_head2);
	CVAR_REGISTER(&sk_otis_head3);

	CVAR_REGISTER(&sk_otis_chest1);
	CVAR_REGISTER(&sk_otis_chest2);
	CVAR_REGISTER(&sk_otis_chest3);

	CVAR_REGISTER(&sk_otis_stomach1);
	CVAR_REGISTER(&sk_otis_stomach2);
	CVAR_REGISTER(&sk_otis_stomach3);

	CVAR_REGISTER(&sk_otis_leg1);
	CVAR_REGISTER(&sk_otis_leg2);
	CVAR_REGISTER(&sk_otis_leg3);

	CVAR_REGISTER(&sk_otis_arm1);
	CVAR_REGISTER(&sk_otis_arm2);
	CVAR_REGISTER(&sk_otis_arm3);

	// Bullsquid
	CVAR_REGISTER ( &sk_bullsquid_health1 );
	CVAR_REGISTER ( &sk_bullsquid_health2 );
	CVAR_REGISTER ( &sk_bullsquid_health3 );

	CVAR_REGISTER ( &sk_bullsquid_dmg_bite1 );
	CVAR_REGISTER ( &sk_bullsquid_dmg_bite2 );
	CVAR_REGISTER ( &sk_bullsquid_dmg_bite3 );

	CVAR_REGISTER ( &sk_bullsquid_dmg_whip1 );
	CVAR_REGISTER ( &sk_bullsquid_dmg_whip2 );
	CVAR_REGISTER ( &sk_bullsquid_dmg_whip3 );

	CVAR_REGISTER ( &sk_bullsquid_dmg_spit1 );
	CVAR_REGISTER ( &sk_bullsquid_dmg_spit2 );
	CVAR_REGISTER ( &sk_bullsquid_dmg_spit3 );

	// Bigmomma
	CVAR_REGISTER ( &sk_bigmomma_health_factor1 );
	CVAR_REGISTER ( &sk_bigmomma_health_factor2 );
	CVAR_REGISTER ( &sk_bigmomma_health_factor3 );

	CVAR_REGISTER ( &sk_bigmomma_dmg_slash1 );
	CVAR_REGISTER ( &sk_bigmomma_dmg_slash2 );
	CVAR_REGISTER ( &sk_bigmomma_dmg_slash3 );

	CVAR_REGISTER ( &sk_bigmomma_dmg_blast1 );
	CVAR_REGISTER ( &sk_bigmomma_dmg_blast2 );
	CVAR_REGISTER ( &sk_bigmomma_dmg_blast3 );

	CVAR_REGISTER ( &sk_bigmomma_radius_blast1 );
	CVAR_REGISTER ( &sk_bigmomma_radius_blast2 );
	CVAR_REGISTER ( &sk_bigmomma_radius_blast3 );

	// Gargantua
	CVAR_REGISTER ( &sk_gargantua_health1 );
	CVAR_REGISTER ( &sk_gargantua_health2 );
	CVAR_REGISTER ( &sk_gargantua_health3 );

	CVAR_REGISTER ( &sk_gargantua_dmg_slash1 );
	CVAR_REGISTER ( &sk_gargantua_dmg_slash2 );
	CVAR_REGISTER ( &sk_gargantua_dmg_slash3 );

	CVAR_REGISTER ( &sk_gargantua_dmg_fire1 );
	CVAR_REGISTER ( &sk_gargantua_dmg_fire2 );
	CVAR_REGISTER ( &sk_gargantua_dmg_fire3 );

	CVAR_REGISTER ( &sk_gargantua_dmg_stomp1 );
	CVAR_REGISTER ( &sk_gargantua_dmg_stomp2 );
	CVAR_REGISTER ( &sk_gargantua_dmg_stomp3);

	// Hassassin
	CVAR_REGISTER ( &sk_hassassin_health1 );
	CVAR_REGISTER ( &sk_hassassin_health2 );
	CVAR_REGISTER ( &sk_hassassin_health3 );

	// Headcrab
	CVAR_REGISTER ( &sk_headcrab_health1 );
	CVAR_REGISTER ( &sk_headcrab_health2 );
	CVAR_REGISTER ( &sk_headcrab_health3 );

	CVAR_REGISTER ( &sk_headcrab_dmg_bite1 );
	CVAR_REGISTER ( &sk_headcrab_dmg_bite2 );
	CVAR_REGISTER ( &sk_headcrab_dmg_bite3 );

	// Hgrunt 
	CVAR_REGISTER ( &sk_hgrunt_health1 );
	CVAR_REGISTER ( &sk_hgrunt_health2 );
	CVAR_REGISTER ( &sk_hgrunt_health3 );

	CVAR_REGISTER ( &sk_hgrunt_kick1 );
	CVAR_REGISTER ( &sk_hgrunt_kick2 );
	CVAR_REGISTER ( &sk_hgrunt_kick3 );

	CVAR_REGISTER ( &sk_hgrunt_pellets1 );
	CVAR_REGISTER ( &sk_hgrunt_pellets2 );
	CVAR_REGISTER ( &sk_hgrunt_pellets3 );

	CVAR_REGISTER ( &sk_hgrunt_gspeed1 );
	CVAR_REGISTER ( &sk_hgrunt_gspeed2 );
	CVAR_REGISTER ( &sk_hgrunt_gspeed3 );

	// Houndeye
	CVAR_REGISTER ( &sk_houndeye_health1 );
	CVAR_REGISTER ( &sk_houndeye_health2 );
	CVAR_REGISTER ( &sk_houndeye_health3 );

	CVAR_REGISTER ( &sk_houndeye_dmg_blast1 );
	CVAR_REGISTER ( &sk_houndeye_dmg_blast2 );
	CVAR_REGISTER ( &sk_houndeye_dmg_blast3 );

	// ISlave
	CVAR_REGISTER ( &sk_islave_health1 );
	CVAR_REGISTER ( &sk_islave_health2 );
	CVAR_REGISTER ( &sk_islave_health3 );

	CVAR_REGISTER ( &sk_islave_dmg_claw1 );
	CVAR_REGISTER ( &sk_islave_dmg_claw2 );
	CVAR_REGISTER ( &sk_islave_dmg_claw3 );

	CVAR_REGISTER ( &sk_islave_dmg_clawrake1);
	CVAR_REGISTER ( &sk_islave_dmg_clawrake2);
	CVAR_REGISTER ( &sk_islave_dmg_clawrake3);
		
	CVAR_REGISTER ( &sk_islave_dmg_zap1 );
	CVAR_REGISTER ( &sk_islave_dmg_zap2 );
	CVAR_REGISTER ( &sk_islave_dmg_zap3 );

	// Icthyosaur
	CVAR_REGISTER ( &sk_ichthyosaur_health1	);
	CVAR_REGISTER ( &sk_ichthyosaur_health2	);
	CVAR_REGISTER ( &sk_ichthyosaur_health3	);

	CVAR_REGISTER ( &sk_ichthyosaur_shake1	);
	CVAR_REGISTER ( &sk_ichthyosaur_shake2	);
	CVAR_REGISTER ( &sk_ichthyosaur_shake3	);

	// Leech
	CVAR_REGISTER ( &sk_leech_health1 );
	CVAR_REGISTER ( &sk_leech_health2 );
	CVAR_REGISTER ( &sk_leech_health3 );

	CVAR_REGISTER ( &sk_leech_dmg_bite1 );
	CVAR_REGISTER ( &sk_leech_dmg_bite2 );
	CVAR_REGISTER ( &sk_leech_dmg_bite3 );

	// Controller
	CVAR_REGISTER ( &sk_controller_health1 );
	CVAR_REGISTER ( &sk_controller_health2 );
	CVAR_REGISTER ( &sk_controller_health3 );

	CVAR_REGISTER ( &sk_controller_dmgzap1 );
	CVAR_REGISTER ( &sk_controller_dmgzap2 );
	CVAR_REGISTER ( &sk_controller_dmgzap3 );

	CVAR_REGISTER ( &sk_controller_speedball1 );
	CVAR_REGISTER ( &sk_controller_speedball2 );
	CVAR_REGISTER ( &sk_controller_speedball3 );

	CVAR_REGISTER ( &sk_controller_dmgball1 );
	CVAR_REGISTER ( &sk_controller_dmgball2 );
	CVAR_REGISTER ( &sk_controller_dmgball3 );

	// Nihilanth
	CVAR_REGISTER ( &sk_nihilanth_health1 );
	CVAR_REGISTER ( &sk_nihilanth_health2 );
	CVAR_REGISTER ( &sk_nihilanth_health3 );

	CVAR_REGISTER ( &sk_nihilanth_zap1 );
	CVAR_REGISTER ( &sk_nihilanth_zap2 );
	CVAR_REGISTER ( &sk_nihilanth_zap3 );

	// Scientist
	CVAR_REGISTER ( &sk_scientist_health1 );
	CVAR_REGISTER ( &sk_scientist_health2 );
	CVAR_REGISTER ( &sk_scientist_health3 );

	// Construction
	CVAR_REGISTER(&sk_construction_health1);
	CVAR_REGISTER(&sk_construction_health2);
	CVAR_REGISTER(&sk_construction_health3);


	CVAR_REGISTER(&sk_construction_head1);
	CVAR_REGISTER(&sk_construction_head2);
	CVAR_REGISTER(&sk_construction_head3);

	CVAR_REGISTER(&sk_construction_chest1);
	CVAR_REGISTER(&sk_construction_chest2);
	CVAR_REGISTER(&sk_construction_chest3);

	CVAR_REGISTER(&sk_construction_stomach1);
	CVAR_REGISTER(&sk_construction_stomach2);
	CVAR_REGISTER(&sk_construction_stomach3);

	CVAR_REGISTER(&sk_construction_leg1);
	CVAR_REGISTER(&sk_construction_leg2);
	CVAR_REGISTER(&sk_construction_leg3);

	CVAR_REGISTER(&sk_construction_arm1);
	CVAR_REGISTER(&sk_construction_arm2);
	CVAR_REGISTER(&sk_construction_arm3);

	// Snark
	CVAR_REGISTER ( &sk_snark_health1 );
	CVAR_REGISTER ( &sk_snark_health2 );
	CVAR_REGISTER ( &sk_snark_health3 );

	CVAR_REGISTER ( &sk_snark_dmg_bite1 );
	CVAR_REGISTER ( &sk_snark_dmg_bite2 );
	CVAR_REGISTER ( &sk_snark_dmg_bite3 );

	CVAR_REGISTER ( &sk_snark_dmg_pop1 );
	CVAR_REGISTER ( &sk_snark_dmg_pop2 );
	CVAR_REGISTER ( &sk_snark_dmg_pop3 );

	//=========================================================
	// NPCs: Diablo
	// For Spirit of Half-Life v1.9: Opposing-Force Edition
	//=========================================================
	CVAR_REGISTER(&sk_diablo_health1);
	CVAR_REGISTER(&sk_diablo_health2);
	CVAR_REGISTER(&sk_diablo_health3);

	CVAR_REGISTER(&sk_diablo_dmg_one_slash1);
	CVAR_REGISTER(&sk_diablo_dmg_one_slash2);
	CVAR_REGISTER(&sk_diablo_dmg_one_slash3);

	CVAR_REGISTER(&sk_diablo_dmg_both_slash1);
	CVAR_REGISTER(&sk_diablo_dmg_both_slash2);
	CVAR_REGISTER(&sk_diablo_dmg_both_slash3);

	CVAR_REGISTER(&sk_diablo_head1);
	CVAR_REGISTER(&sk_diablo_head2);
	CVAR_REGISTER(&sk_diablo_head3);

	CVAR_REGISTER(&sk_diablo_chest1);
	CVAR_REGISTER(&sk_diablo_chest2);
	CVAR_REGISTER(&sk_diablo_chest3);

	CVAR_REGISTER(&sk_diablo_stomach1);
	CVAR_REGISTER(&sk_diablo_stomach2);
	CVAR_REGISTER(&sk_diablo_stomach3);

	CVAR_REGISTER(&sk_diablo_leg1);
	CVAR_REGISTER(&sk_diablo_leg2);
	CVAR_REGISTER(&sk_diablo_leg3);

	//=========================================================
	// NPCs: Zombie,Zombie Soldier,Zombie Barney
	// For Spirit of Half-Life v1.9: Opposing-Force Edition
	//=========================================================

	// Zombie Scientist
	CVAR_REGISTER (&sk_zombie_health1);
	CVAR_REGISTER (&sk_zombie_health2);
	CVAR_REGISTER (&sk_zombie_health3);

	CVAR_REGISTER (&sk_zombie_dmg_one_slash1);
	CVAR_REGISTER (&sk_zombie_dmg_one_slash2);
	CVAR_REGISTER (&sk_zombie_dmg_one_slash3);

	CVAR_REGISTER (&sk_zombie_dmg_both_slash1);
	CVAR_REGISTER (&sk_zombie_dmg_both_slash2);
	CVAR_REGISTER (&sk_zombie_dmg_both_slash3);

	CVAR_REGISTER(&sk_zombie_head1);
	CVAR_REGISTER(&sk_zombie_head2);
	CVAR_REGISTER(&sk_zombie_head3);

	CVAR_REGISTER(&sk_zombie_chest1);
	CVAR_REGISTER(&sk_zombie_chest2);
	CVAR_REGISTER(&sk_zombie_chest3);

	CVAR_REGISTER(&sk_zombie_stomach1);
	CVAR_REGISTER(&sk_zombie_stomach2);
	CVAR_REGISTER(&sk_zombie_stomach3);

	CVAR_REGISTER(&sk_zombie_leg1);
	CVAR_REGISTER(&sk_zombie_leg2);
	CVAR_REGISTER(&sk_zombie_leg3);

	CVAR_REGISTER(&sk_zombie_arm1);
	CVAR_REGISTER(&sk_zombie_arm2);
	CVAR_REGISTER(&sk_zombie_arm3);

	// Zombie Soldier
	CVAR_REGISTER (&sk_zombie_soldier_health1);
	CVAR_REGISTER (&sk_zombie_soldier_health2);
	CVAR_REGISTER (&sk_zombie_soldier_health3);

	CVAR_REGISTER (&sk_zombie_soldier_dmg_one_slash1);
	CVAR_REGISTER (&sk_zombie_soldier_dmg_one_slash2);
	CVAR_REGISTER (&sk_zombie_soldier_dmg_one_slash3);

	CVAR_REGISTER (&sk_zombie_soldier_dmg_both_slash1);
	CVAR_REGISTER (&sk_zombie_soldier_dmg_both_slash2);
	CVAR_REGISTER (&sk_zombie_soldier_dmg_both_slash3);

	CVAR_REGISTER(&sk_zombie_soldier_head1);
	CVAR_REGISTER(&sk_zombie_soldier_head2);
	CVAR_REGISTER(&sk_zombie_soldier_head3);

	CVAR_REGISTER(&sk_zombie_soldier_chest1);
	CVAR_REGISTER(&sk_zombie_soldier_chest2);
	CVAR_REGISTER(&sk_zombie_soldier_chest3);

	CVAR_REGISTER(&sk_zombie_soldier_stomach1);
	CVAR_REGISTER(&sk_zombie_soldier_stomach2);
	CVAR_REGISTER(&sk_zombie_soldier_stomach3);

	CVAR_REGISTER(&sk_zombie_soldier_leg1);
	CVAR_REGISTER(&sk_zombie_soldier_leg2);
	CVAR_REGISTER(&sk_zombie_soldier_leg3);

	CVAR_REGISTER(&sk_zombie_soldier_arm1);
	CVAR_REGISTER(&sk_zombie_soldier_arm2);
	CVAR_REGISTER(&sk_zombie_soldier_arm3);

	// Zombie Construction
	CVAR_REGISTER(&sk_zombie_construction_health1);
	CVAR_REGISTER(&sk_zombie_construction_health2);
	CVAR_REGISTER(&sk_zombie_construction_health3);

	CVAR_REGISTER(&sk_zombie_construction_dmg_one_slash1);
	CVAR_REGISTER(&sk_zombie_construction_dmg_one_slash2);
	CVAR_REGISTER(&sk_zombie_construction_dmg_one_slash3);

	CVAR_REGISTER(&sk_zombie_construction_dmg_both_slash1);
	CVAR_REGISTER(&sk_zombie_construction_dmg_both_slash2);
	CVAR_REGISTER(&sk_zombie_construction_dmg_both_slash3);

	CVAR_REGISTER(&sk_zombie_construction_head1);
	CVAR_REGISTER(&sk_zombie_construction_head2);
	CVAR_REGISTER(&sk_zombie_construction_head3);

	CVAR_REGISTER(&sk_zombie_construction_chest1);
	CVAR_REGISTER(&sk_zombie_construction_chest2);
	CVAR_REGISTER(&sk_zombie_construction_chest3);

	CVAR_REGISTER(&sk_zombie_construction_stomach1);
	CVAR_REGISTER(&sk_zombie_construction_stomach2);
	CVAR_REGISTER(&sk_zombie_construction_stomach3);

	CVAR_REGISTER(&sk_zombie_construction_leg1);
	CVAR_REGISTER(&sk_zombie_construction_leg2);
	CVAR_REGISTER(&sk_zombie_construction_leg3);

	CVAR_REGISTER(&sk_zombie_construction_arm1);
	CVAR_REGISTER(&sk_zombie_construction_arm2);
	CVAR_REGISTER(&sk_zombie_construction_arm3);

	// Zombie Barney
	CVAR_REGISTER(&sk_zombie_barney_health1);
	CVAR_REGISTER(&sk_zombie_barney_health2);
	CVAR_REGISTER(&sk_zombie_barney_health3);

	CVAR_REGISTER(&sk_zombie_barney_dmg_one_slash1);
	CVAR_REGISTER(&sk_zombie_barney_dmg_one_slash2);
	CVAR_REGISTER(&sk_zombie_barney_dmg_one_slash3);

	CVAR_REGISTER(&sk_zombie_barney_dmg_both_slash1);
	CVAR_REGISTER(&sk_zombie_barney_dmg_both_slash2);
	CVAR_REGISTER(&sk_zombie_barney_dmg_both_slash3);

	CVAR_REGISTER(&sk_zombie_barney_head1);
	CVAR_REGISTER(&sk_zombie_barney_head2);
	CVAR_REGISTER(&sk_zombie_barney_head3);

	CVAR_REGISTER(&sk_zombie_barney_chest1);
	CVAR_REGISTER(&sk_zombie_barney_chest2);
	CVAR_REGISTER(&sk_zombie_barney_chest3);

	CVAR_REGISTER(&sk_zombie_barney_stomach1);
	CVAR_REGISTER(&sk_zombie_barney_stomach2);
	CVAR_REGISTER(&sk_zombie_barney_stomach3);

	CVAR_REGISTER(&sk_zombie_barney_leg1);
	CVAR_REGISTER(&sk_zombie_barney_leg2);
	CVAR_REGISTER(&sk_zombie_barney_leg3);

	CVAR_REGISTER(&sk_zombie_barney_arm1);
	CVAR_REGISTER(&sk_zombie_barney_arm2);
	CVAR_REGISTER(&sk_zombie_barney_arm3);

	//=========================================================
	// NPCs: Pit Drone
	// For Spirit of Half-Life v1.9: Opposing-Force Edition
	//=========================================================
	CVAR_REGISTER(&sk_pitdrone_health1);
	CVAR_REGISTER(&sk_pitdrone_health2);
	CVAR_REGISTER(&sk_pitdrone_health3);

	CVAR_REGISTER(&sk_pitdrone_dmg_bite1);
	CVAR_REGISTER(&sk_pitdrone_dmg_bite2);
	CVAR_REGISTER(&sk_pitdrone_dmg_bite3);

	CVAR_REGISTER(&sk_pitdrone_dmg_whip1);
	CVAR_REGISTER(&sk_pitdrone_dmg_whip2);
	CVAR_REGISTER(&sk_pitdrone_dmg_whip3);

	CVAR_REGISTER(&sk_pitdrone_dmg_spit1);
	CVAR_REGISTER(&sk_pitdrone_dmg_spit2);
	CVAR_REGISTER(&sk_pitdrone_dmg_spit3);

	CVAR_REGISTER(&sk_pitdrone_head1);
	CVAR_REGISTER(&sk_pitdrone_head2);
	CVAR_REGISTER(&sk_pitdrone_head3);

	CVAR_REGISTER(&sk_pitdrone_chest1);
	CVAR_REGISTER(&sk_pitdrone_chest2);
	CVAR_REGISTER(&sk_pitdrone_chest3);

	CVAR_REGISTER(&sk_pitdrone_stomach1);
	CVAR_REGISTER(&sk_pitdrone_stomach2);
	CVAR_REGISTER(&sk_pitdrone_stomach3);

	CVAR_REGISTER(&sk_pitdrone_leg1);
	CVAR_REGISTER(&sk_pitdrone_leg2);
	CVAR_REGISTER(&sk_pitdrone_leg3);

	CVAR_REGISTER(&sk_pitdrone_arm1);
	CVAR_REGISTER(&sk_pitdrone_arm2);
	CVAR_REGISTER(&sk_pitdrone_arm3);

	//=========================================================
	// NPCs: Voltigore
	// For Spirit of Half-Life v1.9: Opposing-Force Edition
	//=========================================================
	CVAR_REGISTER(&sk_voltigore_health1);
	CVAR_REGISTER(&sk_voltigore_health2);
	CVAR_REGISTER(&sk_voltigore_health3);

	CVAR_REGISTER(&sk_voltigore_dmg_punch1);
	CVAR_REGISTER(&sk_voltigore_dmg_punch2);
	CVAR_REGISTER(&sk_voltigore_dmg_punch3);

	CVAR_REGISTER(&sk_voltigore_dmg_beam1);
	CVAR_REGISTER(&sk_voltigore_dmg_beam2);
	CVAR_REGISTER(&sk_voltigore_dmg_beam3);

	CVAR_REGISTER(&sk_voltigore_head1);
	CVAR_REGISTER(&sk_voltigore_head2);
	CVAR_REGISTER(&sk_voltigore_head3);

	CVAR_REGISTER(&sk_voltigore_chest1);
	CVAR_REGISTER(&sk_voltigore_chest2);
	CVAR_REGISTER(&sk_voltigore_chest3);

	CVAR_REGISTER(&sk_voltigore_stomach1);
	CVAR_REGISTER(&sk_voltigore_stomach2);
	CVAR_REGISTER(&sk_voltigore_stomach3);

	CVAR_REGISTER(&sk_voltigore_leg1);
	CVAR_REGISTER(&sk_voltigore_leg2);
	CVAR_REGISTER(&sk_voltigore_leg3);

	CVAR_REGISTER(&sk_voltigore_arm1);
	CVAR_REGISTER(&sk_voltigore_arm2);
	CVAR_REGISTER(&sk_voltigore_arm3);

	//=========================================================
	// NPCs: #########################
	// For Spirit of Half-Life v1.9: Opposing-Force Edition
	//=========================================================

	// Opposing-Force
	// Ally Grunt
	CVAR_REGISTER (&sk_hgrunt_ally_health1);
	CVAR_REGISTER (&sk_hgrunt_ally_health2);
	CVAR_REGISTER (&sk_hgrunt_ally_health3);

	CVAR_REGISTER (&sk_hgrunt_ally_kick1);
	CVAR_REGISTER (&sk_hgrunt_ally_kick2);
	CVAR_REGISTER (&sk_hgrunt_ally_kick3);

	CVAR_REGISTER (&sk_hgrunt_ally_pellets1);
	CVAR_REGISTER (&sk_hgrunt_ally_pellets2);
	CVAR_REGISTER (&sk_hgrunt_ally_pellets3);

	CVAR_REGISTER (&sk_hgrunt_ally_gspeed1);
	CVAR_REGISTER (&sk_hgrunt_ally_gspeed2);
	CVAR_REGISTER (&sk_hgrunt_ally_gspeed3);

	CVAR_REGISTER(&sk_hgrunt_ally_head1);
	CVAR_REGISTER(&sk_hgrunt_ally_head2);
	CVAR_REGISTER(&sk_hgrunt_ally_head3);

	CVAR_REGISTER(&sk_hgrunt_ally_chest1);
	CVAR_REGISTER(&sk_hgrunt_ally_chest2);
	CVAR_REGISTER(&sk_hgrunt_ally_chest3);

	CVAR_REGISTER(&sk_hgrunt_ally_stomach1);
	CVAR_REGISTER(&sk_hgrunt_ally_stomach2);
	CVAR_REGISTER(&sk_hgrunt_ally_stomach3);

	CVAR_REGISTER(&sk_hgrunt_ally_leg1);
	CVAR_REGISTER(&sk_hgrunt_ally_leg2);
	CVAR_REGISTER(&sk_hgrunt_ally_leg3);

	CVAR_REGISTER(&sk_hgrunt_ally_arm1);
	CVAR_REGISTER(&sk_hgrunt_ally_arm2);
	CVAR_REGISTER(&sk_hgrunt_ally_arm3);

	// Ally Grunt Medic
	CVAR_REGISTER ( &sk_medic_ally_health1 );
	CVAR_REGISTER ( &sk_medic_ally_health2 );
	CVAR_REGISTER ( &sk_medic_ally_health3 );

	CVAR_REGISTER ( &sk_medic_ally_kick1 );
	CVAR_REGISTER ( &sk_medic_ally_kick2 );
	CVAR_REGISTER ( &sk_medic_ally_kick3 );

	CVAR_REGISTER ( &sk_medic_ally_heal1 );
	CVAR_REGISTER ( &sk_medic_ally_heal2 );
	CVAR_REGISTER ( &sk_medic_ally_heal3 );

	// Ally Grunt Torch 
	CVAR_REGISTER ( &sk_torch_ally_health1 );
	CVAR_REGISTER ( &sk_torch_ally_health2 );
	CVAR_REGISTER ( &sk_torch_ally_health3 );

	CVAR_REGISTER ( &sk_torch_ally_kick1 );
	CVAR_REGISTER ( &sk_torch_ally_kick2 );
	CVAR_REGISTER ( &sk_torch_ally_kick3 );

	// Pitworm
	CVAR_REGISTER(&sk_pitworm_health1);
	CVAR_REGISTER(&sk_pitworm_health2);
	CVAR_REGISTER(&sk_pitworm_health3);

	CVAR_REGISTER(&sk_pitworm_dmg_swipe1);
	CVAR_REGISTER(&sk_pitworm_dmg_swipe2);
	CVAR_REGISTER(&sk_pitworm_dmg_swipe3);

	CVAR_REGISTER(&sk_pitworm_dmg_beam1);
	CVAR_REGISTER(&sk_pitworm_dmg_beam2);
	CVAR_REGISTER(&sk_pitworm_dmg_beam3);

	// Shock Roach
	CVAR_REGISTER(&sk_shockroach_health1);
	CVAR_REGISTER(&sk_shockroach_health2);
	CVAR_REGISTER(&sk_shockroach_health3);

	CVAR_REGISTER(&sk_shockroach_dmg_bite1);
	CVAR_REGISTER(&sk_shockroach_dmg_bite2);
	CVAR_REGISTER(&sk_shockroach_dmg_bite3);

	CVAR_REGISTER(&sk_shockroach_lifespan1);
	CVAR_REGISTER(&sk_shockroach_lifespan2);
	CVAR_REGISTER(&sk_shockroach_lifespan3);

	// Gonome
	CVAR_REGISTER(&sk_gonome_health1);
	CVAR_REGISTER(&sk_gonome_health2);
	CVAR_REGISTER(&sk_gonome_health3);

	CVAR_REGISTER(&sk_gonome_dmg_one_slash1);
	CVAR_REGISTER(&sk_gonome_dmg_one_slash2);
	CVAR_REGISTER(&sk_gonome_dmg_one_slash3);

	CVAR_REGISTER(&sk_gonome_dmg_guts1);
	CVAR_REGISTER(&sk_gonome_dmg_guts2);
	CVAR_REGISTER(&sk_gonome_dmg_guts3);

	CVAR_REGISTER(&sk_gonome_dmg_one_bite1);
	CVAR_REGISTER(&sk_gonome_dmg_one_bite2);
	CVAR_REGISTER(&sk_gonome_dmg_one_bite3);

	// ShockTrooper 
	CVAR_REGISTER(&sk_shocktrooper_health1);
	CVAR_REGISTER(&sk_shocktrooper_health2);
	CVAR_REGISTER(&sk_shocktrooper_health3);

	CVAR_REGISTER(&sk_shocktrooper_kick1);
	CVAR_REGISTER(&sk_shocktrooper_kick2);
	CVAR_REGISTER(&sk_shocktrooper_kick3);

	CVAR_REGISTER(&sk_shocktrooper_gspeed1);
	CVAR_REGISTER(&sk_shocktrooper_gspeed2);
	CVAR_REGISTER(&sk_shocktrooper_gspeed3);

	CVAR_REGISTER(&sk_shocktrooper_maxcharge1);
	CVAR_REGISTER(&sk_shocktrooper_maxcharge2);
	CVAR_REGISTER(&sk_shocktrooper_maxcharge3);

	CVAR_REGISTER(&sk_shocktrooper_rchgspeed1);
	CVAR_REGISTER(&sk_shocktrooper_rchgspeed2);
	CVAR_REGISTER(&sk_shocktrooper_rchgspeed3);

	//Turret
	CVAR_REGISTER ( &sk_turret_health1 );
	CVAR_REGISTER ( &sk_turret_health2 );
	CVAR_REGISTER ( &sk_turret_health3 );

	// MiniTurret
	CVAR_REGISTER ( &sk_miniturret_health1 );
	CVAR_REGISTER ( &sk_miniturret_health2 );
	CVAR_REGISTER ( &sk_miniturret_health3 );

	// Sentry Turret
	CVAR_REGISTER ( &sk_sentry_health1 );
	CVAR_REGISTER ( &sk_sentry_health2 );
	CVAR_REGISTER ( &sk_sentry_health3 );

	// PLAYER WEAPONS

	// Crowbar whack
	CVAR_REGISTER ( &sk_plr_crowbar1 );
	CVAR_REGISTER ( &sk_plr_crowbar2 );
	CVAR_REGISTER ( &sk_plr_crowbar3 );

	// Pipe Wrench
	CVAR_REGISTER(&sk_plr_pipewrench1);
	CVAR_REGISTER(&sk_plr_pipewrench2);
	CVAR_REGISTER(&sk_plr_pipewrench3);

	// Knife whack
	CVAR_REGISTER(&sk_plr_knife1);
	CVAR_REGISTER(&sk_plr_knife2);
	CVAR_REGISTER(&sk_plr_knife3);

	CVAR_REGISTER(&sk_plr_knife_charge1);
	CVAR_REGISTER(&sk_plr_knife_charge2);
	CVAR_REGISTER(&sk_plr_knife_charge3);

	// Glock Round
	CVAR_REGISTER ( &sk_plr_9mm_bullet1 );
	CVAR_REGISTER ( &sk_plr_9mm_bullet2 );
	CVAR_REGISTER ( &sk_plr_9mm_bullet3 );

	// 357 Round
	CVAR_REGISTER ( &sk_plr_357_bullet1 );
	CVAR_REGISTER ( &sk_plr_357_bullet2 );
	CVAR_REGISTER ( &sk_plr_357_bullet3 );

	// 762 Round
	CVAR_REGISTER(&sk_plr_762_bullet1);
	CVAR_REGISTER(&sk_plr_762_bullet2);
	CVAR_REGISTER(&sk_plr_762_bullet3);

	// MP5 Round
	CVAR_REGISTER ( &sk_plr_9mmAR_bullet1 );
	CVAR_REGISTER ( &sk_plr_9mmAR_bullet2 );
	CVAR_REGISTER ( &sk_plr_9mmAR_bullet3 );

	// M203 grenade
	CVAR_REGISTER ( &sk_plr_9mmAR_grenade1 );
	CVAR_REGISTER ( &sk_plr_9mmAR_grenade2 );
	CVAR_REGISTER ( &sk_plr_9mmAR_grenade3 );

	// Shotgun buckshot
	CVAR_REGISTER ( &sk_plr_buckshot1 );
	CVAR_REGISTER ( &sk_plr_buckshot2 );
	CVAR_REGISTER ( &sk_plr_buckshot3 );

	// Crossbow
	CVAR_REGISTER ( &sk_plr_xbow_bolt_monster1 );
	CVAR_REGISTER ( &sk_plr_xbow_bolt_monster2 );
	CVAR_REGISTER ( &sk_plr_xbow_bolt_monster3 );

	CVAR_REGISTER ( &sk_plr_xbow_bolt_client1 );
	CVAR_REGISTER ( &sk_plr_xbow_bolt_client2 );
	CVAR_REGISTER ( &sk_plr_xbow_bolt_client3 );

	// RPG
	CVAR_REGISTER ( &sk_plr_rpg1 );
	CVAR_REGISTER ( &sk_plr_rpg2 );
	CVAR_REGISTER ( &sk_plr_rpg3 );

	// Gauss Gun
	CVAR_REGISTER ( &sk_plr_gauss1 );
	CVAR_REGISTER ( &sk_plr_gauss2 );
	CVAR_REGISTER ( &sk_plr_gauss3 );

	// Egon Gun
	CVAR_REGISTER ( &sk_plr_egon_narrow1 );
	CVAR_REGISTER ( &sk_plr_egon_narrow2 );
	CVAR_REGISTER ( &sk_plr_egon_narrow3 );

	CVAR_REGISTER ( &sk_plr_egon_wide1 );
	CVAR_REGISTER ( &sk_plr_egon_wide2 );
	CVAR_REGISTER ( &sk_plr_egon_wide3 );

	// Hand Grendade
	CVAR_REGISTER ( &sk_plr_hand_grenade1 );
	CVAR_REGISTER ( &sk_plr_hand_grenade2 );
	CVAR_REGISTER ( &sk_plr_hand_grenade3 );

	// Satchel Charge
	CVAR_REGISTER ( &sk_plr_satchel1 );
	CVAR_REGISTER ( &sk_plr_satchel2 );
	CVAR_REGISTER ( &sk_plr_satchel3 );

	// Tripmine
	CVAR_REGISTER ( &sk_plr_tripmine1 );
	CVAR_REGISTER ( &sk_plr_tripmine2 );
	CVAR_REGISTER ( &sk_plr_tripmine3 );

	// 556
	CVAR_REGISTER(&sk_plr_556_bullet1);
	CVAR_REGISTER(&sk_plr_556_bullet2);
	CVAR_REGISTER(&sk_plr_556_bullet3);

	// WORLD WEAPONS
	CVAR_REGISTER ( &sk_12mm_bullet1 );
	CVAR_REGISTER ( &sk_12mm_bullet2 );
	CVAR_REGISTER ( &sk_12mm_bullet3 );

	CVAR_REGISTER ( &sk_9mmAR_bullet1 );
	CVAR_REGISTER ( &sk_9mmAR_bullet2 );
	CVAR_REGISTER ( &sk_9mmAR_bullet3 );

	CVAR_REGISTER ( &sk_9mm_bullet1 );
	CVAR_REGISTER ( &sk_9mm_bullet2 );
	CVAR_REGISTER ( &sk_9mm_bullet3 );

	// 556
	CVAR_REGISTER(&sk_556_bullet1);
	CVAR_REGISTER(&sk_556_bullet2);
	CVAR_REGISTER(&sk_556_bullet3);

	// HORNET
	CVAR_REGISTER ( &sk_hornet_dmg1 );
	CVAR_REGISTER ( &sk_hornet_dmg2 );
	CVAR_REGISTER ( &sk_hornet_dmg3 );

	// SHOCKROACH
	CVAR_REGISTER(&sk_plr_shockroachs1);
	CVAR_REGISTER(&sk_plr_shockroachs2);
	CVAR_REGISTER(&sk_plr_shockroachs3);

	CVAR_REGISTER(&sk_plr_shockroachm1);
	CVAR_REGISTER(&sk_plr_shockroachm2);
	CVAR_REGISTER(&sk_plr_shockroachm3);

	// SPOREGRENADE
	CVAR_REGISTER(&sk_plr_spore1);
	CVAR_REGISTER(&sk_plr_spore2);
	CVAR_REGISTER(&sk_plr_spore3);

	// HEALTH/SUIT CHARGE DISTRIBUTION
	CVAR_REGISTER ( &sk_suitcharger1 );
	CVAR_REGISTER ( &sk_suitcharger2 );
	CVAR_REGISTER ( &sk_suitcharger3 );

	CVAR_REGISTER ( &sk_battery1 );
	CVAR_REGISTER ( &sk_battery2 );
	CVAR_REGISTER ( &sk_battery3 );

	CVAR_REGISTER ( &sk_healthcharger1 );
	CVAR_REGISTER ( &sk_healthcharger2 );
	CVAR_REGISTER ( &sk_healthcharger3 );

	CVAR_REGISTER ( &sk_healthkit1 );
	CVAR_REGISTER ( &sk_healthkit2 );
	CVAR_REGISTER ( &sk_healthkit3 );

	CVAR_REGISTER ( &sk_scientist_heal1 );
	CVAR_REGISTER ( &sk_scientist_heal2 );
	CVAR_REGISTER ( &sk_scientist_heal3 );
	
	CVAR_REGISTER ( &sk_flashcharge1 );
	CVAR_REGISTER ( &sk_flashcharge2 );
	CVAR_REGISTER ( &sk_flashcharge3 );
	
	// monster damage adjusters
	CVAR_REGISTER ( &sk_monster_head1 );
	CVAR_REGISTER ( &sk_monster_head2 );
	CVAR_REGISTER ( &sk_monster_head3 );

	CVAR_REGISTER ( &sk_monster_chest1 );
	CVAR_REGISTER ( &sk_monster_chest2 );
	CVAR_REGISTER ( &sk_monster_chest3 );

	CVAR_REGISTER ( &sk_monster_stomach1 );
	CVAR_REGISTER ( &sk_monster_stomach2 );
	CVAR_REGISTER ( &sk_monster_stomach3 );

	CVAR_REGISTER ( &sk_monster_arm1 );
	CVAR_REGISTER ( &sk_monster_arm2 );
	CVAR_REGISTER ( &sk_monster_arm3 );

	CVAR_REGISTER ( &sk_monster_leg1 );
	CVAR_REGISTER ( &sk_monster_leg2 );
	CVAR_REGISTER ( &sk_monster_leg3 );

	// player damage adjusters
	CVAR_REGISTER ( &sk_player_head1 );
	CVAR_REGISTER ( &sk_player_head2 );
	CVAR_REGISTER ( &sk_player_head3 );

	CVAR_REGISTER ( &sk_player_chest1 );
	CVAR_REGISTER ( &sk_player_chest2 );
	CVAR_REGISTER ( &sk_player_chest3 );

	CVAR_REGISTER ( &sk_player_stomach1 );
	CVAR_REGISTER ( &sk_player_stomach2 );
	CVAR_REGISTER ( &sk_player_stomach3 );

	CVAR_REGISTER ( &sk_player_arm1 );
	CVAR_REGISTER ( &sk_player_arm2 );
	CVAR_REGISTER ( &sk_player_arm3 );

	CVAR_REGISTER ( &sk_player_leg1 );
	CVAR_REGISTER ( &sk_player_leg2 );
	CVAR_REGISTER ( &sk_player_leg3 );

	// END REGISTER CVARS FOR SKILL LEVEL STUFF
	SERVER_COMMAND( "exec skill.cfg\n" );
	SERVER_COMMAND( "exec skill_opfor.cfg\n" ); // Opposing-Force
	SERVER_COMMAND( "exec skill_hitgroups.cfg\n"); // Hitgroups
}

