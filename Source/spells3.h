/*
 *  File:       spells3.cc
 *  Summary:    Implementations of some additional spells.
 *  Written by: Linley Henzell
 *
 *  Change History (most recent first):
 *
 *               <1>     -/--/--        LRH             Created
 */


#ifndef SPELLS3_H
#define SPELLS3_H


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spells1 - spells3
 * *********************************************************************** */
bool allow_control_teleport(void);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
bool airstrike(int power);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
bool cast_bone_shards(int power);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell - spells1
 * *********************************************************************** */
bool cast_death_channel(int power);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
void cast_poison_ammo(void);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: ability - spell
 * *********************************************************************** */
void cast_selective_amnesia(bool force);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: ability - spell
 * *********************************************************************** */
bool cast_smiting(int power);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
bool create_noise(void);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: religion - spell
 * *********************************************************************** */
void dancing_weapon(int pow, bool force_hostile);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: item_use - spell
 * *********************************************************************** */
bool detect_curse(bool suppress_msg);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: decks - spell
 * *********************************************************************** */
bool entomb(void);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
void portal(void);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: ability - spell
 * *********************************************************************** */
bool recall(char type_recalled);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: item_use - spell
 * *********************************************************************** */
bool remove_curse(bool suppress_msg);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
void sublimation(int power);


// updated Oct 2 -- bwr
/* ***********************************************************************
 * called from: spell
 * *********************************************************************** */
void simulacrum(int power);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: ability - beam - decks - fight - item_use - spell
 * *********************************************************************** */
void you_teleport(void);


// updated 24may2000 {dlb}
/* ***********************************************************************
 * called from: ability - acr - decks - effects - fight - misc - spells
 * *********************************************************************** */
void you_teleport2(bool allow_control);


#endif
