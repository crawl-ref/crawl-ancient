/*
 *  File:       beam.cc
 *  Summary:    Functions related to ranged attacks.
 *  Written by: Linley Henzell
 *
 *  Change History (most recent first):
 *
 *               <1>     -/--/--        LRH             Created
 */


#ifndef BEAM_H
#define BEAM_H


#include "externs.h"


/* ***********************************************************************
 * called from: bang - it_use2 - monstuff - mstuff2
 * *********************************************************************** */
void beam(struct bolt &pbolt, int inv_number = -1);


// last updated 12may2000 {dlb}
/* ***********************************************************************
 * called from: ability - it_use3 - item_use - mstuff2 - religion -
 *              spells - spells4
 * *********************************************************************** */
void explosion(struct bolt &pbolt);


// last updated 22jan2001 {gdl}
/* ***********************************************************************
 * called from: effects - spells2 - spells4
 * *********************************************************************** */
int mons_adjust_flavoured(struct monsters *monster, struct bolt &pbolt,
    int hurted, bool doFlavouredEffects = true);


/* ***********************************************************************
 * called from: effects
 * *********************************************************************** */
bool check_mons_magres(struct monsters *monster, int pow);


/* ***********************************************************************
 * called from: ability - item_use - spell
 * *********************************************************************** */
void mass_enchantment(int wh_enchant, int pow);


/* ***********************************************************************
 * called from: fight - monstuff - mstuff2
 * *********************************************************************** */
int mons_ench_f2(struct monsters *monster, struct bolt &pbolt);


/* ***********************************************************************
 * called from: fight - monstuff - spells2
 * *********************************************************************** */
void poison_monster(struct monsters *monster, bool fromPlayer);


/* ***********************************************************************
 * called from: fight - monstuff - spells - spells1 - spells2
 * *********************************************************************** */
void place_cloud(unsigned char cl_type, unsigned char ctarget_x, unsigned char ctarget_y, unsigned char cl_range);


/* ***********************************************************************
 * called from: monstuff
 * *********************************************************************** */
void fire_tracer(struct monsters *monster, struct bolt &pbolt);


/* ***********************************************************************
 * called from: monstuff
 * *********************************************************************** */
void mimic_alert(struct monsters *mimic);


#endif