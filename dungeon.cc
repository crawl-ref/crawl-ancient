/*
 *  File:       dungeon.cc
 *  Summary:    Functions used when building new levels.
 *  Written by: Linley Henzell
 *
 *  Change History (most recent first):
 *
 *
 *      <5>      8/08/99        BWR             Upped rarity of unique artefacts
 *      <4>      7/13/99        BWR             Made pole arms of speed.
 *      <3>      5/22/99        BWR             Made named artefact weapons
 *                                              rarer, Sword of Power esp.
 *      <2>      5/09/99        LRH             Replaced some sanity checking code in
 *                                              spellbook_template with a corrected version
 *                                              using ASSERTs.
 *      <1>      -/--/--        LRH             Created
 */

#include "AppHdr.h"
#include "dungeon.h"

#include <stdlib.h>

#include <stdio.h>

#ifdef DOS
#include <conio.h>
#endif

#include <string.h>
#include <time.h>
#include <fcntl.h>

#ifdef DOS
#include <io.h>
#include <SYS\STAT.H>
#endif

#include <assert.h>

#include "externs.h"
#include "enum.h"

#include "debug.h"
#include "mons_lev.h"
#include "maps.h"
#include "randart.h"
#include "shopping.h"
#include "mstruct.h"
#include "itemname.h"

#define NUMBER_SPELLBOOKS                       59
#define SPLBOOK_TOME_OF_DEST            35
#define SPLBOOK_MANUALS                         41

unsigned char border_type = DNGN_ROCK_WALL;

int bcount_x;
int bcount_y;
int bi;
int bj;
int bk;
int bp;
int room_x1;
int room_y1;
int room_x2;
int room_y2;
int x_max;
int y_max;
int no_rooms;
int max_doors;
int diag_door = 0;

// these are the variables for individual levels.
int doorlevel;
int corrlength;
int roomsize;
int no_corr;
int intersect_chance = 0;
int bno_mons = 0;

int time_run = 0;               // for repeating search for 1-door rooms

//int many = 0;

int many_many = 0;              // for multiple levels

int x_start, y_start, x_fin, y_fin;
int x_ps;
int y_ps;
int finish = 0;
int length;
int dir_x;
int dir_y;
int old_x = 0;
int old_y = 0;
int dir_x2 = 0;
int dir_y2 = 0;
int rannumber;
int rannum;

int count_x;


int put_x;
int put_y;
int q;

int passout;

//int handle;
char save_file[9];
char whole_line[80];

//int counting;
int leng_str;
char wm_1[5];
char wm_2;

//char gmon_use [200];

int skipped = 0;
int randnum;

int lev_mons = 8;
int band = 0;
int band_no = 0;


int x1, x2, y1, y2;
int cx = 0;
int cy = 0;
int sx = 0;
int sy = 0;
int dx = 0;
int dy = 0;
int rd = 0;

char dung1;
char dung2;

char oblique;
char oblique_max;

char is_a_specroom = 0;

int vsx, vsy;                   /* used in vaults function */

char filenam[80];


/* New array - used for the spellbook_template function - this info is
   roughly the same length as it was when it was one massive switch
   statement, but that switch was getting a little messy, this should
   help out a little.  The new function is only a few lines long now.

   This really needs to go somewhere else.
 */
int spellbook_template_array[NUMBER_SPELLBOOKS][7] =
{
    // Beginning spellbook 1
    {0,
     5,                         // Magic missile
      26,                       // Throw flame
      49,                       // Summon small mammal
      59,                       // Blink
      13,                       // conf fl
      15},                      // Fire bolt

    // Beginning spellbook 2
    {0,
     5,                         // Magic missile
      27,                       // Throw frost
      49,                       // Summon small mammal
      59,                       // Blink
      21,                       // Slow
      16},                      // Cold bolt

    // Beginning spellbook 4
    {0,
     5,                         // Magic missile
      13,                       // Conjure flame
      21,                       // Slow
      59,                       // Blink
      15,                       // Bolt of fire
      30},                      // Mephitic cloud

        // Book of conjurations
    {0,
     5,                         // Magic missile
      26,                       // Throw flame
      13,                       // Conjure flame
      30,                       // Mephitic cloud
      16,                       // Frost bolt
      17},                      // Thunderbolt

        // Book of conjurations
    {0,
     5,                         // Magic missile
      27,                       // Throw frost
      13,                       // Conjure flame
      30,                       // Mephitic cloud
      15,                       // Fire bolt
      6},                       // Fireball

        // Book of flames
    {0,
     75,                        // Burn
      26,                       // Throw flame
      13,                       // Conjure flame
      79,                       // Sticky flame
      15,                       // Fire bolt
      6},                       // Fireball

        // Book of frost
    {0,
     76,                        // Freeze
      27,                       // Throw frost
      81,                       // Ice armour
      SPELL_ICE_BOLT,
      80,                        // Ice beast
      29},                      // freez cloud

        // Book of invocations
    {0,
     146,                       // Recall
      SPELL_SHADOW_CREATURES,
     61,                        // Swarm
      62,                       // Thing
      72,                       // Summon wraiths
      210},

        // Book of fire
    {0,
     124,                       // Fire brand
      77,                       // Summon elemental
      31,                       // Ring of flame
      57,                       // Firestorm
      210,
     210},

    // Book of ice
    {0,
     125,                       // Freezing aura
      77,                       // Summon elemental
      16,                       // Frost bolt
      78,                       // Refrigeration
      SPELL_ICE_STORM,
     210},

    // 10 - Book of surveyance
    {0,
     58,                        // Detect traps
      64,                       // Magic mapping
      73,                       // Detect items
      137,                      // Detect creatures
      210,
     210},

        // Book of spatial translocation
    {0,
     59,                        // Blink
      28,                       // Controlled blink
      139,                      // Controlled teleport
      1,                        // Teleport self
      210,
     210},

    // Book of enchantments - the fourth one
    {0,
     43,                        // Selective amnesia
      52,                       // Levitation
      4,                        // Remove curse
      159,                      // Deflect missiles
      68,                       // Extension
      210},

    // Book of poison
    {0,
     115,                       // Sting
      138,                      // Cure poison
      141,                      // Brand weapon
      30,                       // Mephitic cloud
      35,                       // Venom bolt
      210},

    // Book of fire and storms
    {0,
     17,                        // Thunderbolt
      6,                        // Fireball
      57,                       // Fire storm
      210,
     210,
     210},

    // Book of death
    {0,
     53,                        // Bolt of draining
      112,                      // Bone shards
      122,                      // Rot corpses
      126,                      // Lethal infusion
      148,                      // Agony
      210},

    // Book of hinderance
    {0,
     21,                        // Slow
      23,                       // Paralize
      210,
     210,
     210,
     210},

    // Book of changes
    {0,                         //
      150,                      // Disrupt
      149,                      // Spider form
      152,                      // Blade hands
      14,                       // Dig
      154,                      // Ice beast form
      210},

    // Book of transfigurations
    {0,
     20,                        // Polymorph other
      153,                      // Statue form
      144,                      // Alter self
      155,                      // Dragon form
      156,                      // Lich form
      210},

    // Useful magic
    {0,
     143,                       // Noise 2
      43,                       // Selective amnesia
      48,                       // Detect curse
      14,                       // Dig
      4,                        // Remove curse
      210},

    // Book of war chants
    // Note: If any are added here, must chance Crusader in crawlfnc.cc
    {0,
     124,                       // Fire brand
      125,                      // Freezing aura
      83,                       // Repel missiles
      84,                       // Berserk
      111,                      // Regeneration
      22},                      // Haste

    // Clouds?
    {0,
     30,                        // Mephitic cloud
      13,                       // Conjure flame
      29,                       // Freezing cloud
      56,                       // Poison cloud
      210,
     210},

        // Book of healing
    {0,
     40,                        // Cure poison
      38,                       // Lesser heal
      39,                       // Greater heal
      41,                       // Purification
      210,
     210},

    // Book of necromancy
    {0,
     67,                        // Pain
      70,                       // Animate skeleton
      71,                       // Vampiric draining
      85,                       // Dispel undead
      111,                      // Regeneration
      66},                      // Animate dead

    // Necronomicon
    {0,
     158,                       // Symbol of Torment
      69,                       // Control undead
      42,                       // Death's door
      72,                       // Summon wraiths
      156,                      // Lich form
      157},                     // Death channel

    // Book of summonings
    {0,
     49,                        // Summon small animal
      82,                       // Summon imp
      50,                       // Abjur
      51,                       // Summon scopians
      80,                       // Summon ice beas
      77},                      // Summon elemental

    // Book of charms
    {0,
     83,                        // Repel missiles
      21,                       // Slow
      63,                       // Enslave
      25,                       // Invisibility
      22,                       // Haste
      2},                       // Fear

    // Book of demonology
    {0,
     119,                       // Demon
      120,                      // Demonic horde
      121,                      // Greater demon
      210,
     210,
     210},

    // Book of air
    {0,
     SPELL_ARC,
     133,                       // Swiftness
      83,                       // Repel missiles
//        52,           // Levitation
      30,                       // Mephitic cloud
      132,                      // Shock
      77},                      // Summon elemental

    // Book of the sky
    {0,
     135,                       // Insulation
      SPELL_AIRSTRIKE,
     134,                       // Fly
      159,                      // Deflect missiles
      17,                       // Lightning bolt
      136},                     // Orb of electroc

    // 30 - Book of divinations
    {0,
     48,                        // Detect curse
      0,                        // Identification
      210,
     210,
     210,
     210},

    // Book of the Warp
    {0,
     146,                       // Recall
      37,                       // Teleport away
      113,                      // Banishment
      147,                      // Portal
      210,
     210},

    // Book of venom
    {0,
     140,                       // Poison ammo
      149,                      // Spider form
      51,                       // Summon scorpions
      142,                      // Poison resist
      36,                       // olg tox rad
      56},                      // Poison cloud

    // Book of annihilations
    {0,
     60,                        // Myst bolt
      56,                       // Poison cloud
      136,                      // Orb of electro
      54,                       // Crystal spear
      SPELL_ICE_STORM,
     57},                       // Firestorm

    // Book of unlife
    {0,
     116,                       // Sublimation of Blood
      66,                       // Animate Dead
      110,                      // Twisted Resurrection
      74,                       // Revivification
      210,
     210},

    // 35 is the tome of destruction
    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    // Book of control
    {0,
     24,                        // Confusion
      63,                       // Enslavement
      44,                       // Mass confusion
      69,                       // Control undead
      210,
     210},

    // Book of mutations
    {0,
     20,                        // Polymorph other
      144,                      // Alter self
      114,                      // Degeneration
      210,
     210,
     210},

    // Book of Takumi
    {0,
     117,                       // Takumi's dance
      123,                      // Takumi's vorpal blade
      210,
     210,
     210,
     210},

    // Book of geomancy
    {0,
     127,                       // Crush
      129,                      // Stone arrow
      64,                       // Magic mapping
      14,                       // Dig
      128,                      // Bolt of iron
      77},                      // Summon elemental

    // 40 - Book of earth
    {0,
     131,                       // Stonemail
      130,                      // Tomb
      SPELL_ORB_OF_FRAGMENTATION,
     54,                        // lehudib's crystal sphere
      210,
     210},

    // 41 : manuals
    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    // Book of wizardry
    {0,
     137,                       // Detect creatures
      77,                       // Summon elemental
      1,                        // Teleport
      6,                        // Fireball
      22,                       // Haste
      0},                       // Identification

        // Book of power
    {0,
     64,                        // Magic mapping
      66,                       // Animate dead
      56,                       // Poison cloud
      128,                      // Bolt of iron
      25,                       // Invisibility
      44},                      // Mass confusion

        // 44 to 49 are unused.
    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    {0,
     210,
     210,
     210,
     210,
     210,
     210},

    {0,
     210,
     210,
     210,
     210,
     210,
     210},

        // 50 - Staff of smiting
    {0,
     45,                        // Smiting
      210,
     210,
     210,
     210,
     210},

        // Staff of summoning
    {0,
     61,                        // Swarm
      77,                       // Elemental
      119,                      // Demon
      146,                      // Recall
      210,
     210},

    // Staff of destruction
    {0,
     26,                        // Throw fire
      15,                       // Firebolt
      6,                        // Fireball
      210,
     210,
     210},

    // Staff of destruction
    {0,
     27,                        // Throw frost
      16,                       // Frostbolt
      17,                       // Thunderbolt
      210,
     210,
     210},

        // Staff of destruction
    {0,
     6,                         // Fireball
      17,                       // Thunderbolt
      54,                       // Throw splinters
      210,
     210,
     210},

    // Staff of destruction
    {0,
     15,                        // Frost bolt
      16,                       // Firebolt
      55,                       // Bolt of unaccuracy
      210,
     210,
     210},

    // Staff of warding
    {0,
     46,                        // Repel undead
      2,                        // Cause fear
      50,                       // Abjuration
      210,
     210,
     210},

    // Staff of exploration
    {0,
     58,                        // Detect traps
      64,                       // Magic mapping
      73,                       // Detect items
      210,
     210,
     210},

    // Staff of demonology
    {0,
     119,                       // Demon
      120,                      //
      121,                      //
      146,                      // Recall
      210,
     210}
};



void build_vaults(int force_vault);
void build_minivaults(int force_vault);
int vault_grid(int vx, int vy, int altar_count, char acq_item_class[7], int mons_array[10], char vgrid);


void chequerboard(unsigned char cheq1, unsigned char cheq2, unsigned char deleted, unsigned char chx1, unsigned char chy1, unsigned char chx2, unsigned char chy2);
void spotty_level(char seeded, int iterations, char boxy);



char item_in_shop(char shop_type);

void make_room(void);

void make_trail(void);

int items(unsigned char allow_uniques, int force_class, int force_type,
          int force_place, int many_many, int force_spec);

void give_item(void);

void special_room(void);

int treasure_area(int many_many, unsigned char ta1_x, unsigned char ta2_x,
                  unsigned char ta1_y, unsigned char ta2_y);

void specr_2(void);

void place_traps(void);

int place_specific_trap(unsigned char spec_x, unsigned char spec_y,
                        unsigned char spec_type);


void link_items(void);

void big_room(void);

void diamond_rooms(void);

void octa_room(unsigned char type_floor);

void item_colour(int p);

int random3(unsigned int rmax);

void place_spec_shop(char shop_x, char shop_y, char force_s_type);

void place_shops(void);


void roguey_level(void);

void city_level(void);

void labyrinth_level(void);



void box_room(int bx1, int bx2, int by1, int by2, int wall_type);
void bigger_room(void);
void place_pool(unsigned char pool_type, unsigned char pool_x1, unsigned char pool_y1, unsigned char pool_x2, unsigned char pool_y2);
void many_pools(unsigned char pool_type);
void generate_abyss(void);

void beehive(void);

void check_doors(void);

void morgue(void);

void define_zombie(char not_zombsize,
                   int ztype,
                   int cs);



int builder(unsigned int lev_numb, char level_type);


int place_monster(unsigned char plus_seventy, int typed, int type_place,
              int px, int py, char behaviour, int hitting, char allow_bands,
                  int many_many, int passed[2]);

void clear_area(unsigned char xr1, unsigned char yr1, unsigned char xr2,
        unsigned char yr2, unsigned char deleting, unsigned char replacing);

void spellbook_template(int sbook_type, int func_pass[10]);

void hide_doors(void);

void plan_main(char force_plan);
char plan_1(void);
char plan_2(void);
char plan_3(void);
char plan_4(char forbid_x1, char forbid_y1, char forbid_x2, char forbid_y2,
            unsigned char force_wall);
char plan_5(void);
char plan_6(void);

void join_the_dots(unsigned char dotx1, unsigned char doty1,
   unsigned char dotx2, unsigned char doty2, char forbid_x1, char forbid_y1,
                   char forbid_x2, char forbid_y2);

void place_curse_skull(void);
void place_altar(void);
void prepare_swamp(void);
void prepare_water(void);
char rare_weapon(unsigned char w_type);

/*void item_bugs(void);
   void find_item(unsigned int found); */


int builder(unsigned int lev_numb, char level_type)
{

    int lava_spaces = 0;
    int water_spaces = 0;
    int aq_creatures = 0;
    int type_of_aq = 0;
    int swimming_things[4];

    srandom(time(NULL));

    many_many = lev_numb;

    int done_city = 0;

    dung1 = random3(100);
    dung2 = random3(100);

    border_type = DNGN_ROCK_WALL;
    if (many_many == 60)
        border_type = DNGN_METAL_WALL;

    for (bcount_x = 0; bcount_x < 80; bcount_x++)
    {
        for (bcount_y = 0; bcount_y < 70; bcount_y++)
        {
            grd[bcount_x][bcount_y] = DNGN_ROCK_WALL;        // must be 1

            grd[bcount_x][6] = border_type;
            grd[bcount_x][63] = border_type;
            grd[6][bcount_y] = border_type;
            grd[73][bcount_y] = border_type;
            igrd[bcount_x][bcount_y] = 501;
            mgrd[bcount_x][bcount_y] = MNG;
        }
    }

    for (bcount_x = 0; bcount_x < NTRAPS; bcount_x++)
    {
        env.trap_type[bcount_x] = 100;
        env.trap_x[bcount_x] = 1;
        env.trap_y[bcount_x] = 1;
    }


    for (bcount_x = 0; bcount_x < ITEMS; bcount_x++)
    {
        mitm.base_type[bcount_x] = 100;
        mitm.sub_type[bcount_x] = 0;
        mitm.pluses[bcount_x] = 0;
        mitm.pluses2[bcount_x] = 0;
        mitm.special[bcount_x] = 0;
        bcount_y = 100000;
        mitm.quantity[bcount_x] = 0;
        mitm.colour[bcount_x] = 0;
        mitm.x[bcount_x] = 0;
        mitm.y[bcount_x] = 0;
        mitm.id[bcount_x] = 0;
        mitm.link[bcount_x] = 501;
    }

/*      for (bi = 0; bi < 10; bi ++)
   {
   stair_x [bi] = 1;
   stair_y [bi] = 1;
   } */

    for (bi = 0; bi < MNST; bi++)
    {
        menv[bi].type = -1;
        menv[bi].target_x = random3(80);
        menv[bi].target_y = random3(70);
        menv[bi].behavior = 0;
        menv[bi].enchantment1 = 0;
        menv[bi].enchantment[0] = 0;
        menv[bi].enchantment[1] = 0;
        menv[bi].enchantment[2] = 0;

        if (random3(10) == 0)
            menv[bi].behavior = 1;

        for (bj = 0; bj < 8; bj++)
        {
            menv[bi].inv[bj] = 501;
        }
        menv[bi].number = 250;

    }

    if (level_type == LEVEL_LABYRINTH)
    {
        labyrinth_level();
        return 0;
    }

    if (level_type == LEVEL_ABYSS)
    {
        generate_abyss();
        goto skip_level;
    }

    if (level_type == LEVEL_PANDEMONIUM)
    {
        // Could do spotty_level, but that doesn't always put all paired
        // stairs reachable from each other which isn't a problem in normal
        // dungeon but could be in Pandemonium
        if (random() % 7 == 0)
        {
            char which_demon = 0;

            do
            {
                which_demon = random() % 4;
                if (random() % 4 == 0)
                    goto normal_pan;    // makes these things less likely as you find more

            }
            while (you.unique_creatures[40 + which_demon] == 1);

            you.unique_creatures[40 + which_demon] = 1;
            build_vaults(which_demon + 60);
//              link_items(unique_items, igrd, menv, it);
            // must not call link_items unless returning immediately after
            goto skip_level;

        }

normal_pan:
        plan_main(0);
//          if (random3(3) == 0)
        {
            build_minivaults(300 + random3(9));
            done_city = 1;
            goto skip_level;
        }
        done_city = 1;
        goto skip_level;
    }


    is_a_specroom = 0;
    done_city = 0;


    if (you.where_are_you == BRANCH_HIVE
                    && many_many == you.branch_stairs[STAIRS_HIVE]
                                    + branch_depth(STAIRS_HIVE))
    {
        build_vaults(80);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_SLIME_PITS
                    && many_many == you.branch_stairs[STAIRS_SLIME_PITS]
                                    + branch_depth(STAIRS_SLIME_PITS))
    {
        build_vaults(81);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_VAULTS
                    && many_many == you.branch_stairs[STAIRS_VAULTS]
                                    + branch_depth(STAIRS_VAULTS))
    {
        build_vaults(82);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_HALL_OF_BLADES
                    && many_many == you.branch_stairs[STAIRS_HALL_OF_BLADES]
                                    + branch_depth(STAIRS_HALL_OF_BLADES))
    {
        build_vaults(83);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_HALL_OF_ZOT
                    && many_many == you.branch_stairs[STAIRS_HALL_OF_ZOT]
                                    + branch_depth(STAIRS_HALL_OF_ZOT))
    {
        build_vaults(84);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_ECUMENICAL_TEMPLE
                    && many_many == you.branch_stairs[STAIRS_ECUMENICAL_TEMPLE]
                                    + branch_depth(STAIRS_ECUMENICAL_TEMPLE))
    {
        build_vaults(85);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_SNAKE_PIT
                    && many_many == you.branch_stairs[STAIRS_SNAKE_PIT]
                                    + branch_depth(STAIRS_SNAKE_PIT))
    {
        build_vaults(86);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_ELVEN_HALLS
                    && many_many == you.branch_stairs[STAIRS_ELVEN_HALLS]
                                    + branch_depth(STAIRS_ELVEN_HALLS))
    {
        build_vaults(87);
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_TOMB)
    {
        if (many_many == you.branch_stairs[STAIRS_TOMB] + 1)
        {
            build_vaults(88);
            goto skip_level;
        }
        else if (many_many == you.branch_stairs[STAIRS_TOMB] + 2)
        {
            build_vaults(89);
            goto skip_level;
        }
        else if (many_many == you.branch_stairs[STAIRS_TOMB] + 3)
        {
            build_vaults(90);
            goto skip_level;
        }
    }

    if (you.where_are_you == BRANCH_SWAMP
                    && many_many == you.branch_stairs[STAIRS_SWAMP]
                                    + branch_depth(STAIRS_SWAMP))
    {
        build_vaults(91);
        goto skip_level;
    }


    if (you.where_are_you == BRANCH_SLIME_PITS
                || you.where_are_you == BRANCH_ORCISH_MINES
                || you.where_are_you == BRANCH_HIVE
                || (you.where_are_you == BRANCH_LAIR && random3(3) != 0))
    {
        spotty_level(0, 100 + random3(500), 0);
        done_city = 1;
        goto skip_level;
    }

    if (you.where_are_you == BRANCH_VESTIBULE_OF_HELL)
    {
        build_vaults(50);
        link_items();
        return 0;
    }

    if (you.where_are_you == BRANCH_SWAMP)        // The Swamp

    {
        goto basic_level;
    }


/*      where_are_you == 1 Dis 75 - 79
   where_are_you == 2 Gehenna 80 - 84
   where_are_you == 3 the Vestibule of Hell 60
   where_are_you == 4 Cocytus 85 - 89
   where_are_you == 5 Tartarus 90 - 94 */

//      if (many_many == 84 || many_many == 79 || many_many == 89 || many_many == 94)
    if (many_many == 33 && (you.where_are_you == BRANCH_DIS
                            || you.where_are_you == BRANCH_GEHENNA
                            || you.where_are_you == BRANCH_COCYTUS
                            || you.where_are_you == BRANCH_TARTARUS))
    {
        char which_v = 0;

        switch (you.where_are_you)
        {
        case BRANCH_DIS:
            which_v = 51;
            break;
        case BRANCH_GEHENNA:
            which_v = 52;
            break;
        case BRANCH_COCYTUS:
            which_v = 53;
            break;
        case BRANCH_TARTARUS:
            which_v = 54;
            break;
        }
        build_vaults(which_v);
        goto skip_level;
    }

    if (many_many > 7 && many_many < 23 && random() % 7 == 0
                                && level_type == LEVEL_DUNGEON
                                && you.where_are_you == BRANCH_MAIN_DUNGEON)
    {
        /* Can't have vaults on you.where_are_you != 0 levels */
        build_vaults(100);
        done_city = 1;
        goto skip_level;
    }

    if (random3(3) == 0 && many_many != 65)
        skipped = 1;

    if (you.where_are_you == BRANCH_DIS || you.where_are_you == BRANCH_VAULTS)
    {
        goto do_city;
    }

    if (random3(18) == 0 && many_many > 7 && many_many < 23)
    {
        spotty_level(0, 0, random() % 2);
        done_city = 1;
        goto skip_level;
    }

    if (random3(18) == 0 && many_many > 7 && many_many < 23)
    {
        bigger_room();
        done_city = 1;
        goto skip_level;
    }

    if (random3(3) == 0 && many_many > 2 && many_many < 23)
    {
        plan_main(0);
        if (random3(3) == 0)
            build_minivaults(200);
        done_city = 1;
        goto skip_level;
    }


    //V was 3
    if ((random3(7) == 0 && skipped == 0))
    {

        // is_a_specroom can be changed to 2 in this function:
        // in which case it shouldn't be done again.

        roguey_level();

        if (random3(4) == 0 && many_many > 6
                        && you.where_are_you == BRANCH_MAIN_DUNGEON
                        && you.level_type == LEVEL_DUNGEON)
        {
            build_minivaults(200);
            done_city = 1;
            goto skip_level;
        }

        if (skipped == 1)
            goto skip_level;
    }
    else
    {
        if (random3(8) == 0 && skipped == 0 && many_many > 13
                    && !(you.where_are_you == BRANCH_DIS
                            || you.where_are_you == BRANCH_GEHENNA
                            || you.where_are_you == BRANCH_COCYTUS
                            || you.where_are_you == BRANCH_TARTARUS))
        {
          do_city:
            if (many_many == 33 && you.where_are_you == 1)
                build_vaults(51);
            else if (random() % 3 == 0)
            {
                city_level();
            }
            else
                plan_main(4);

            done_city = 1;
        }
    }



// is_a_specroom: 0 = none, 2 = in roguey_level (no need for specr_2), 1 = special_room (vault)
    if (random3(5) == 0 && is_a_specroom != 2 && many_many > 5
            && done_city == 0
                    && !(you.where_are_you == BRANCH_DIS
                            || you.where_are_you == BRANCH_GEHENNA
                            || you.where_are_you == BRANCH_COCYTUS
                            || you.where_are_you == BRANCH_TARTARUS))
    {
        is_a_specroom = 1;
        special_room();

    }

basic_level:
    doorlevel = random3(11);
    corrlength = random3(14) + 2;
    roomsize = random3(5) + 4 + random3(6);
    no_corr = random3(200) + 30;

    if (random3(100) == 0)
        no_corr = 500 + random3(500);

    intersect_chance = random3(20);

    if (random3(20) == 0)
        intersect_chance = 400;

    if (done_city == 0)
    {
        do
        {
            x_start = random3(30) + 35;
            y_start = random3(20) + 35;
        }
        while (grd[x_start][y_start] != DNGN_ROCK_WALL && grd[x_start][y_start] != DNGN_FLOOR);
        grd[x_start][y_start] = DNGN_STONE_STAIRS_DOWN_I;
        x_ps = x_start;
        y_ps = y_start;
        make_trail();
        grd[x_ps][y_ps] = DNGN_STONE_STAIRS_UP_I;

        do
        {
            x_start = random3(15) + 10;
            y_start = random3(15) + 10;
        }
        while (grd[x_start][y_start] != DNGN_ROCK_WALL && grd[x_start][y_start] != DNGN_FLOOR);
        grd[x_start][y_start] = DNGN_STONE_STAIRS_DOWN_II;
        finish = 0;
        x_ps = x_start;
        y_ps = y_start;
        make_trail();
        grd[x_ps][y_ps] = DNGN_STONE_STAIRS_UP_II;

        do
        {
            x_start = random3(20) + 50;
            y_start = random3(15) + 10;
        }
        while (grd[x_start][y_start] != DNGN_ROCK_WALL && grd[x_start][y_start] != DNGN_FLOOR);
        grd[x_start][y_start] = DNGN_STONE_STAIRS_DOWN_III;
        finish = 0;
        x_ps = x_start;
        y_ps = y_start;
        make_trail();
        grd[x_ps][y_ps] = DNGN_STONE_STAIRS_UP_III;

        if (random3(4) == 0)
        {
            do
            {
                x_start = random3(20) + 10;
                y_start = random3(20) + 40;
            }
            while (grd[x_start][y_start] != DNGN_ROCK_WALL && grd[x_start][y_start] != DNGN_FLOOR);
            grd[x_start][y_start] = DNGN_ROCK_STAIRS_DOWN;
            finish = 0;
            x_ps = x_start;
            y_ps = y_start;
            make_trail();
        }


        if (random3(4) == 0)
        {
            do
            {
                x_start = random3(20) + 50;
                y_start = random3(20) + 40;
            }
            while (grd[x_start][y_start] != DNGN_ROCK_WALL && grd[x_start][y_start] != DNGN_FLOOR);
            grd[x_start][y_start] = DNGN_STONE_STAIRS_UP_III;
            finish = 0;
            x_ps = x_start;
            y_ps = y_start;
            make_trail();
        }

    }                           // end of done_city


    if (random3(16) == 0 && done_city == 0 && many_many > 1)
    {
        big_room();
    }

    if (done_city == 0 && ((random3(many_many) >= 7 && random3(3) == 0) || (you.where_are_you == 1 || you.where_are_you == 2 || you.where_are_you == 4 || you.where_are_you == 5)))
    {
        diamond_rooms();
    }

    no_rooms = random3(15) + random3(15) + 5;


    if (random3(15) == 0)
    {
        no_rooms = 100;
    }

    if (random3(50) == 0)
    {
        no_rooms = 1;
    }

    if (done_city == 1)
        no_rooms = 0;

    max_doors = 2 + random3(8);



    for (bk = 0; bk < no_rooms; bk++)
    {
        room_x1 = random3(50) + 8;
        room_y1 = random3(40) + 8;
        room_x2 = room_x1 + random3(roomsize) + 2;
        room_y2 = room_y1 + random3(roomsize) + 2;

        make_room();
        if (time_run > 30)
        {
            time_run = 0;
            bk++;
            continue;
        }

    }

    no_rooms = random3(3) + 1;
    max_doors = 1;

    if (done_city == 1)
        no_rooms = 0;

    for (bk = 0; bk < no_rooms; bk++)
    {
        room_x1 = random3(55) + 8;
        room_y1 = random3(45) + 8;
        room_x2 = room_x1 + random3(6) + 5;
        room_y2 = room_y1 + random3(6) + 5;

        make_room();
        if (time_run > 30)
        {
            time_run = 0;
            bk++;
            continue;
        }

    }

    if (random3(3) == 0 && many_many > 6 && you.where_are_you == 0 && you.level_type == 0)
    {
        build_minivaults(200);
        done_city = 1;
        goto skip_level;
    }

    if (random3(10) == 0 && many_many > 5 && !(you.where_are_you == 1 || you.where_are_you == 2 || you.where_are_you == 4 || you.where_are_you == 5))
    {
        many_pools(61 + random3(2));
    }

    if (many_many >= 11 && many_many <= 23 && !(you.where_are_you == 1 || you.where_are_you == 2 || you.where_are_you == 4 || you.where_are_you == 5) && random3(15) == 0)
    {
        do
        {
            bi = random3(80);
            bj = random3(70);
            if (random3(500) == 0)
                goto out_of_lab;
        }
        while (grd[bi][bj] != DNGN_FLOOR);
        grd[bi][bj] = DNGN_ENTER_LABYRINTH;
    }

out_of_lab:
    if (is_a_specroom == 1)
        specr_2();


skip_level:
    bi = 0;
/* should goto skip_level if everything is done except:
   items placed, monsters placed, gates etc placed.
   note that there can already be some monsters/items etc present
   Stairs must already be done */

    if (you.where_are_you == 22)
        prepare_swamp();



    bno_mons = 0;

    bno_mons += random3(25) + random3(20) + random3(15);        // + random3 (many_many);// + random3 (15);

    if (you.where_are_you == 1 || you.where_are_you == 2 || you.where_are_you == 4 || you.where_are_you == 5 || you.where_are_you == 16)
        bno_mons += random3(10) + random3(20) + random3(20);
    if (you.where_are_you == 16)
        bno_mons += random3(10) + random3(20) + random3(20);

    if (bno_mons > 120)
        bno_mons = 120;         // unlikely

    if (level_type == 2)
        bno_mons = 0;
    if (you.where_are_you == 18)
        bno_mons = 0;           /* Temple */

    bk = 0;

    int kloppo = 0;

    if (level_type == 3)
        goto finished_monsters;
/*cprintf("1st:");
   if (getch() == 0) getch();
   item_bugs(); */


    for (kloppo = 0; kloppo < bno_mons; kloppo++)
    {
        int passed[2];

        passed[1] = 1;
        kloppo += place_monster(
                                   250,         //1, //plus_seventy,
                                    250,        // typed,
                                    0,  //type_place,
                                    1,  //px,
                                    1,  //py,
                                    0,  //behaviour,
                                    MHITNOT,    //hitting,
                                    1,  //1,//allow_bands
                                    many_many,
                                   passed);

    }

/*cprintf("2nd:");
   if (getch() == 0) getch();
   item_bugs(); */

// keep kloppo for later (aquatic monsters)

// Unique beasties:
do_uniques:
    if (many_many > 0 && !(you.where_are_you == 1 || you.where_are_you == 2 || you.where_are_you == 4 || you.where_are_you == 5 || you.where_are_you == 10 || you.where_are_you == 11 || you.where_are_you == 12 || you.where_are_you == 18) && random() % 3 == 0)
    {

        int which_unique = 0;   //     30 in total


redo_uniques:
        which_unique = 20 + random() % 11;
        if (many_many < 20)
            which_unique = 13 + random() % 10;
        if (many_many < 17)
            which_unique = 9 + random() % 9;
        if (many_many < 14)
            which_unique = 6 + random() % 5;
        if (many_many < 10)
            which_unique = 4 + random() % 4;
        if (many_many < 8)
            which_unique = 2 + random() % 4;
        if (many_many < 4)
            which_unique = random() % 4;

        if (you.unique_creatures[which_unique] != 0)
        {
            if (random() % 3 == 0)
                goto redo_uniques;
            goto finished_uniques;
        }

// note: unique_creatures 40 + used by unique demons

        int passed[2];

        passed[1] = 1;
        kloppo += place_monster(
                                   250,
                                   which_unique + 280,
                                   0,
                                   1,
                                   1,
                                   0,
                                   MHITNOT,
                                   1,
                                   many_many,
                                   passed);

        if (random() % 3 == 0)
            goto do_uniques;

    }




// do aquatic and lava monsters:

finished_uniques:
    for (bcount_x = 0; bcount_x < 80; bcount_x++)
    {
        for (bcount_y = 0; bcount_y < 70; bcount_y++)
        {
            if (grd[bcount_x][bcount_y] == DNGN_LAVA)
                lava_spaces++;
            if (grd[bcount_x][bcount_y] == DNGN_DEEP_WATER || grd[bcount_x][bcount_y] == DNGN_SHALLOW_WATER)
                water_spaces++;
        }
    }

    if (lava_spaces >= 50)
    {
        for (bcount_x = 0; bcount_x < 4; bcount_x++)
        {
            swimming_things[bcount_x] = MLAVA0 + random3(3);
        }
        aq_creatures = random3(5) + random3(5) + random3(lava_spaces) / 10;
        if (aq_creatures > 25)
            aq_creatures = 25;
        for (bcount_x = 0; bcount_x < aq_creatures; bcount_x++)
        {
//  type_of_aq = MLAVA0 + random3(3);
            type_of_aq = swimming_things[random3(4)];
            int passed2[2];

            passed2[1] = 1;
            kloppo += place_monster(
                                       250,     //1, //plus_seventy,
                                        type_of_aq,     // typed,
                                        0,      //type_place,
                                        1,      //px,
                                        1,      //py,
                                        0,      //behaviour,
                                        MHITNOT,        //hitting,
                                        1,      //1,//allow_bands
                                        many_many,
                                       passed2);
            if (kloppo >= 100)
                break;

        }
    }

    if (water_spaces >= 50)
    {
        for (bcount_x = 0; bcount_x < 4; bcount_x++)
        {
            swimming_things[bcount_x] = MWATER0 + random3(4);
            if (you.where_are_you == 22 && random3(3) != 0)
                swimming_things[bcount_x] = MWATER5;
        }
        if (random() % 5 == 0 && many_many >= 25)
            swimming_things[0] = MWATER4;       // water elemental

        if (many_many == 89)
            swimming_things[3] = MWATER4;       // Cocytus

        aq_creatures = random3(5) + random3(5) + random3(water_spaces) / 7;
        if (aq_creatures > 25)
            aq_creatures = 25;
        for (bcount_x = 0; bcount_x < aq_creatures; bcount_x++)
        {
//                      type_of_aq = MWATER0 + random3(4);
            type_of_aq = swimming_things[random3(4)];
            int passed2[2];

            passed2[1] = 1;
            kloppo += place_monster(
                                       250,     //1, //plus_seventy,
                                        type_of_aq,     // typed,
                                        0,      //type_place,
                                        1,      //px,
                                        1,      //py,
                                        0,      //behaviour,
                                        MHITNOT,        //hitting,
                                        1,      //1,//allow_bands
                                        many_many,
                                       passed2);

            if (kloppo >= 100)
                break;
        }
    }







finished_monsters:
    if (many_many >= 20 && many_many <= 27 && level_type == 0 && you.where_are_you == 0)
    {
        do
        {
            bi = random3(70);
            bj = random3(60);
        }
        while (grd[bi][bj] != DNGN_FLOOR || mgrd[bi][bj] != MNG);
        grd[bi][bj] = DNGN_ENTER_HELL;
    }

    if (many_many >= 20 && many_many <= 50 && (many_many == 23 || random() % 4 == 0) && level_type == 0 && you.where_are_you == 0)
    {
        do
        {
            bi = random3(70);
            bj = random3(60);
        }
        while (grd[bi][bj] != DNGN_FLOOR || mgrd[bi][bj] != MNG);
        grd[bi][bj] = DNGN_ENTER_PANDEMONIUM;       // gate to Pandemonium

    }

    if (many_many >= 20 && many_many <= 30 && (many_many == 24 || random() % 3 == 0) && level_type == 0 && you.where_are_you == 0)
    {
        do
        {
            bi = random3(70);
            bj = random3(60);
        }
        while (grd[bi][bj] != DNGN_FLOOR || mgrd[bi][bj] != MNG);
        grd[bi][bj] = DNGN_ENTER_ABYSS;       // gate to Abyss

    }

    for (count_x = 0; count_x < 30; count_x++)
    {
        if (you.branch_stairs[count_x] == 0)
            break;
        if (count_x != 7)
        {
            if ((count_x == 3 && you.where_are_you == 12 && level_type == 0 && many_many == you.branch_stairs[3]) || (count_x == 5 && you.where_are_you == 14 && level_type == 0 && many_many == you.branch_stairs[5]) || (count_x == 6 && you.where_are_you == 15 && level_type == 0 && many_many == you.branch_stairs[6]) || (count_x == 9 && you.where_are_you == 12 && level_type == 0 && many_many == you.branch_stairs[9]) || (count_x == 10 && you.where_are_you == 10 && level_type == 0 && many_many == you.branch_stairs[10]) || (count_x == 11 && you.where_are_you == 15 && level_type == 0 && many_many == you.branch_stairs[11]) || (count_x == 12 && you.where_are_you == 12 && level_type == 0 && many_many == you.branch_stairs[12]))
            {
                do
                {
                    bi = random3(70);
                    bj = random3(60);
                }
                while (grd[bi][bj] != DNGN_FLOOR || mgrd[bi][bj] != MNG);
                grd[bi][bj] = DNGN_ENTER_ORCISH_MINES + count_x;    /* staircase to slime pits */
            }
            else if (many_many == you.branch_stairs[count_x] && level_type == 0 && you.where_are_you == 0)
            {
                do
                {
                    bi = random3(70);
                    bj = random3(60);
                }
                while (grd[bi][bj] != DNGN_FLOOR || mgrd[bi][bj] != MNG);
                grd[bi][bj] = DNGN_ENTER_ORCISH_MINES + count_x;    // staircase to branch level

            }
        }                       // end if (count_x != 7)

    }                           /* end for loop */

    check_doors();
    if (you.where_are_you != 1 && you.where_are_you != 14)
        hide_doors();

    if (you.where_are_you != 18)
        place_traps();

    int no_it = random3(12) + random3(12) + random3(10);

    if (random3(500 - many_many) <= 3 && many_many > 5)
        no_it += random3(100);  // rich level!

    int plojy = 0;
    int specif_type = 250;
    int items_levels = many_many;

    if (you.where_are_you == BRANCH_VAULTS)

    {
        items_levels *= 15;
        items_levels /= 10;
    }

    if (you.where_are_you == BRANCH_ORCISH_MINES)
        specif_type = 15;       /* lots of gold in the orcish mines */

    if (you.where_are_you == BRANCH_DIS
                || you.where_are_you == BRANCH_GEHENNA
                || you.where_are_you == BRANCH_COCYTUS
                || you.where_are_you == BRANCH_TARTARUS
                || you.where_are_you == BRANCH_SLIME_PITS
                || you.where_are_you == BRANCH_HALL_OF_BLADES
                || you.where_are_you == BRANCH_ECUMENICAL_TEMPLE)
    {
        /* No items in hell, the slime pits, the Hall */
        no_it = 0;
    }
    else
    {
        for (plojy = 0; plojy < no_it; plojy++)
        {
            items(1, specif_type, 250, 0, items_levels, 250);
        }

        // Add some guaranteed knives
        if (you.where_are_you == BRANCH_MAIN_DUNGEON
                        && level_type == LEVEL_DUNGEON
                        && many_many < 5 && random3(many_many) == 0)
        {
            int item_no = items(0, OBJ_WEAPONS, WPN_KNIFE, 0, 0, 250);

            // Guarantee that the knife is uncursed and non-special

            if (item_no != 501)
            {
                mitm.pluses[item_no] = 50;
                mitm.pluses2[item_no] = 50;
                mitm.special[item_no] = 0;
            }
        }
    }


    int shcount = 0;

    for (shcount = 0; shcount < 5; shcount++)
    {
        env.sh_type[shcount] = 100;
    }

    if ( !(you.where_are_you == BRANCH_DIS
                || you.where_are_you == BRANCH_GEHENNA
                || you.where_are_you == BRANCH_COCYTUS
                || you.where_are_you == BRANCH_TARTARUS
                || you.where_are_you == BRANCH_LAIR
                || you.where_are_you == BRANCH_ECUMENICAL_TEMPLE)
            && level_type == LEVEL_DUNGEON )
    {
        place_shops();
    }


    for (bcount_x = 0; bcount_x < 80; bcount_x++)
    {
        for (bcount_y = 0; bcount_y < 70; bcount_y++)
        {
            if (grd[bcount_x][bcount_y] == DNGN_STATUE_35)
                grd[bcount_x][bcount_y] = DNGN_ROCK_WALL;
            if (grd[bcount_x][bcount_y] == 47)
                grd[bcount_x][bcount_y] = DNGN_FLOOR;
            if (grd[bcount_x][bcount_y] == 36)
                grd[bcount_x][bcount_y] = DNGN_FLOOR;
/*            if (grd[bcount_x][bcount_y] == DNGN_FLOOR)
                grd[bcount_x][bcount_y] = DNGN_FLOOR;
*/
            if (grd[bcount_x][bcount_y] == DNGN_ENTER_ZOT)
                grd[bcount_x][bcount_y] = DNGN_FLOOR;
            if (grd[bcount_x][bcount_y] == 'i') //do you believe this? DML
                grd[bcount_x][bcount_y] = DNGN_ROCK_WALL;
            if (grd[bcount_x][bcount_y] == 'j')
                grd[bcount_x][bcount_y] = DNGN_FLOOR;

        }
    }


/* If level is part of Dis, make all walls metal. If part of vaults,
   depends on level: */

    if (you.where_are_you == BRANCH_DIS || you.where_are_you == BRANCH_VAULTS
                                || you.where_are_you == BRANCH_CRYPT)
    {
        unsigned char vault_wall = 4;

        if (you.where_are_you == BRANCH_VAULTS)
        {
            vault_wall = 1;
            if (many_many > you.branch_stairs[4] + 2)
                vault_wall = 2;
            if (many_many > you.branch_stairs[4] + 4)
                vault_wall = 4;
            if (many_many > you.branch_stairs[4] + 6 && random3(10) == 0)
                vault_wall = 6;
        }

        if (you.where_are_you == BRANCH_CRYPT)
        {
            vault_wall = 2;
        }

        for (bi = 1; bi < 80; bi++)
        {
            for (bj = 1; bj < 70; bj++)
            {
                if (grd[bi][bj] == DNGN_ROCK_WALL)
                {
                    grd[bi][bj] = vault_wall;
                }
            }
        }
    }



    if (many_many == 26 && level_type == LEVEL_DUNGEON
                            && you.where_are_you == BRANCH_MAIN_DUNGEON)
    {
        for (bi = 1; bi < 80; bi++)
        {
            for (bj = 1; bj < 70; bj++)
            {
                if (grd[bi][bj] >= DNGN_STONE_STAIRS_DOWN_I
                                    && grd[bi][bj] <= DNGN_ROCK_STAIRS_DOWN)
                {
                    grd[bi][bj] = DNGN_ENTER_ZOT;
                }
            }
        }
    } /* replaces all down stairs with staircases to Zot */

    /*
     * top level of branch levels - replaces up stairs with stairs back
     * to dungeon or wherever
     */
    for (count_x = 0; count_x < 30; count_x++)
    {
        if (you.branch_stairs[count_x] == 0)
            break;
        if (many_many == you.branch_stairs[count_x] + 1
                            && level_type == LEVEL_DUNGEON
                            && you.where_are_you == 10 + count_x)
        {
            for (bi = 1; bi < 80; bi++)
            {
                for (bj = 1; bj < 70; bj++)
                {
                    if (grd[bi][bj] >= DNGN_STONE_STAIRS_UP_I && grd[bi][bj] <= DNGN_ROCK_STAIRS_UP)
                    {
                        grd[bi][bj] = DNGN_RETURN_DUNGEON_I + count_x;
                    }
                }
            }
        }
    }

    for (count_x = 0; count_x < 30; count_x++)
    {
        if (many_many == you.branch_stairs[count_x] + branch_depth(count_x)
                                && level_type == LEVEL_DUNGEON
                                && you.where_are_you == 10 + count_x)
        {
            for (bi = 1; bi < 80; bi++)
            {
                for (bj = 1; bj < 70; bj++)
                {
                    if (grd[bi][bj] >= DNGN_STONE_STAIRS_DOWN_I
                                    && grd[bi][bj] <= DNGN_ROCK_STAIRS_DOWN)
                    {
                        grd[bi][bj] = DNGN_ROCK_STAIRS_UP;
                    }
                }
            }
        } /* bottom level of branch - replaces down stairs with up ladders */
    }

    if (you.where_are_you == BRANCH_CRYPT && random3(3) == 0)
        place_curse_skull();
    if (you.where_are_you == BRANCH_CRYPT && random3(7) == 0)
        place_curse_skull();

    if (you.where_are_you >= BRANCH_ORCISH_MINES
                    && you.level_type == LEVEL_DUNGEON && random3(5) == 0)
    {
        place_altar();
    }

    if (you.where_are_you == BRANCH_MAIN_DUNGEON)
    {
        for (bi = 1; bi < 80; bi++)
        {
            for (bj = 1; bj < 70; bj++)
            {
                switch (grd[bi][bj])
                {
                case DNGN_ENTER_SLIME_PITS:
                case DNGN_ENTER_CRYPT_I:
                case DNGN_ENTER_HALL_OF_BLADES:
                case DNGN_ENTER_SNAKE_PIT:
                case DNGN_ENTER_ELVEN_HALLS:
                case DNGN_ENTER_TOMB:
                case DNGN_ENTER_SWAMP:
                    grd[bi][bj] = DNGN_FLOOR;
                    break;      /* this shouldn't be necessary, but is */
                }
            }
        }
    }

    if (you.where_are_you == BRANCH_HALL_OF_BLADES)
    {
        for (bj = 1; bj < 70; bj++)
        {
            for (bi = 1; bi < 80; bi++)
            {
                 //dml stopped here.
                if (grd[bi][bj] >= DNGN_STONE_STAIRS_DOWN_I
                                    && grd[bi][bj] <= DNGN_ROCK_STAIRS_UP)
                {
                    grd[bi][bj] = DNGN_FLOOR;
                }
            }
        }
    }



    link_items();
    prepare_water();

    return 0;

} // end of int builder(unsigned int lev_numb, char level_type)


int place_monster( unsigned char plus_seventy, int typed, int type_place,
                    int px, int py, char behaviour, int hitting,
                    char allow_bands, int many_many, int passed[2])
{

    unsigned char grid_ok = 67;
    int worm = 0;
    int plussed = 0;
    int inv_delete = 0;

    int k = 0;

    band = 0;
    band_no = 0;

    if (typed == 56)
        typed = 19;

start_here:
    for (k = 0; k < MNST; k++)
    {
        if (k == MNST - 1)
            return plussed;
        if (menv[k].type == -1)
            break;
    }

    if (type_place == 1 && mgrd[px][py] != MNG)
    {
        return 0;
    }

    bk = k;
    passed[0] = k;

    for (inv_delete = 0; inv_delete < 8; inv_delete++)
    {
        menv[bk].inv[inv_delete] = 501;
    }

    /* hall of blades */
    if (typed == 250 && you.where_are_you == 16 && you.level_type == 0)
        typed = 144;

    lev_mons = many_many;

    if (typed == 250)
    {
monster_cla:
        if (random3(4) == 0 && you.where_are_you == 0 && lev_mons != 51)
            lev_mons = random3(many_many);
        else
            lev_mons = many_many;

        if (lev_mons <= 27 && you.where_are_you == 0)
        {
            if (random3(5000) == 0)
                lev_mons = random3(27);
            // a potentially nasty surprise, but very rare

            // slightly out of depth monsters are more common:
            if (random3(50) == 0)
                lev_mons += random3(6);
            if (lev_mons >= 27)
                lev_mons = 27;
        }


        /* Abyss or Pandemonium. Almost never called from Pan;
           probably only if a rand demon gets summon anything spell */
        if (lev_mons == 51 || you.level_type == LEVEL_PANDEMONIUM
                                        || you.level_type == LEVEL_ABYSS)
        {
            do
            {
                do
                {
                    menv[bk].type = random3(400);
                }
                while (mons_level_abyss(menv[bk].type) == 0);
//                      if (mons_level_abyss(menv [bk].type) == 0) continue;
            }
            while (random3(50) + random3(51) >
                                       mons_rare_abyss(menv[bk].type));
        }
        else
        {
            do
            {
                do
                {
                    menv[bk].type = random3(400);
                }
                while (mons_rarity(menv[bk].type) == 0);

            }
            while (!(lev_mons > mons_level(menv[bk].type) - 5 &&
                   lev_mons < mons_level(menv[bk].type) + 5 && random3(50) +
                     random3(51) <= mons_rarity(menv[bk].type) -
                     (mons_level(menv[bk].type) - lev_mons) *
                     (mons_level(menv[bk].type) - lev_mons)));
        }

        if (type_place == 1 && menv[bk].type == 19)
            goto monster_cla;

        if (bk > 50 && menv[bk].type == 19)
            goto monster_cla;

    }
    else
        menv[bk].type = typed;


    if (menv[bk].type == 19)
    {
        if (bk >= 170)
            menv[bk].type = 22;
        else if (menv[bk + 1].type != -1 || menv[bk + 2].type != -1 |
                 menv[bk + 3].type != -1 || menv[bk + 4].type != -1)
            menv[bk].type = 22;
    }


    if (menv[bk].type >= MLAVA0)
    {
        menv[bk].number = 0;
        if (menv[bk].type >= MWATER0)
            grid_ok = 62;
        else
            grid_ok = 61;
    }

/*      worm_tail:
   if (worm == 5)
   {
   worm = 0;
   return 5;
   }
   if (worm > 0 && worm < 5)
   {
   if (worm > 1)
   {
   bk ++;
   }
   menv [bk].type = 56;
   worm++;
   }


   if (menv [bk].type == 19)
   {
   worm = 1;
   menv [bk].type = -1;
   while (menv [bk + 1].type != -1 || menv [bk + 2].type != -1 || menv [bk + 3].type != -1 || menv [bk + 4].type != -1)
   {
   bk ++;
   if (bk > MNST - 10) return 0;
   }
   menv [bk].type = 19;
   }
 */


    switch (band)
    {
    case 0:
        break;
    case 1:
        if (band_no > 0)
            menv[bk].type = 36;
        break;
    case 2:
        if (band_no > 0)
            menv[bk].type = 14;
        if (random3(5) == 0)
            menv[bk].type = 54;
        if (random3(7) == 0)
            menv[bk].type = 112;
        break;
    case 12:
    case 3:
        if (band_no > 0)
            switch (random3(16))
            {
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 0:
                menv[bk].type = 14;
                break;
            case 3:
            case 4:
            case 14:
            case 15:
            case 1:
                menv[bk].type = 52;
                break;
            case 2:
                menv[bk].type = 54;
                break;
            case 5:
                menv[bk].type = 40;
                break;
            case 6:
                menv[bk].type = 45;
                break;
            case 7:
                if (random3(2) == 0)
                    menv[bk].type = 14;
                else
                    menv[bk].type = 103;
                break;          // orc sorceror

            case 8:
                menv[bk].type = 112;
                break;          // orc priest

            }
        break;
    case 4:
        if (band_no > 0)
            menv[bk].type = 10;
        break;                  // k bees

    case 5:
        if (band_no > 0)
            menv[bk].type = 72;
        break;                  // flying skulls

    case 6:
        if (band_no > 0)
            menv[bk].type = 76;
        break;                  // slime thing

    case 7:
        if (band_no > 0)
            menv[bk].type = 50;
        break;                  // yak

    case 8:
        if (band_no > 0)
            menv[bk].type = 20;
        if (band_no > 0 && random3(4) == 0 && many_many > 21)
            menv[bk].type = 102;
        break;                  // ugly thing

    case 9:
        if (band_no > 0)
            menv[bk].type = 73;
        break;                  // hell hound

    case 10:
        if (band_no > 0)
            menv[bk].type = 9;
        break;                  // jackal

    case 11:
        if (band_no > 0)
            menv[bk].type = 109;
        if (random3(4) == 0)
            menv[bk].type = 110;
        break;
        // 12 is orc high priest
    case 13:
        if (band_no > 0)
            menv[bk].type = 115;
        break;                  // gnoll

    case 16:
        if (band_no > 0)
            menv[bk].type = 138;
        break;                  // bumblebees

    case 17:
        if (band_no > 0)
            menv[bk].type = 2;
        break;                  // centaur

    case 18:
        if (band_no > 0)
            menv[bk].type = 133;
        break;                  // yaktaur

    case 19:
        if (band_no > 0)
            menv[bk].type = 140;
        break;                  // wisps

    case 20:
        if (band_no > 0)
            menv[bk].type = 40;
        if (random3(3) == 0)
            menv[bk].type = 30;
        break;                  // ogre mage

    case 21:
        if (band_no > 0)
            menv[bk].type = 134;
        break;                  // death yaks

    case 22:
        if (band_no > 0)        // necromancer

            if (band_no > 0)
                switch (random3(13))
                {
                case 0:
                case 1:
                case 2:
                    menv[bk].type = 25;
                    break;
                case 3:
                case 4:
                case 5:
                    menv[bk].type = 51;
                    break;
                case 6:
                case 7:
                case 8:
                    menv[bk].type = 107;
                    break;
                case 9:
                case 10:
                case 11:
                    menv[bk].type = 108;
                    break;
                case 12:
                    menv[bk].type = 13;
                    break;
                }
        break;
    case 23:
        if (band_no > 0)
            menv[bk].type = 225 + random() % 2;
        break;                  // CYAN demon

    case 24:
        if (band_no > 0)
            menv[bk].type = 221;
        break;                  // BROWN demon

    case 25:
        if (band_no > 0)
            menv[bk].type = 23 + (random() % 2) * 26;
        break;                  // DARKGREY demon - either x/X

    case 26:
        if (band_no > 0)
            menv[bk].type = 227 + random() % 2;
        break;                  // LIGHTGREY demons

    case 27:                    // deep elf fighter

        if (band_no > 0)
            switch (random3(11))
            {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 0:
                menv[bk].type = 263;
                break;
            case 6:
                menv[bk].type = 264;
                break;
            case 7:
                menv[bk].type = 265;
                break;
            case 8:
                menv[bk].type = 268;
                break;
            case 9:
                menv[bk].type = 266;
                break;
            case 10:
                menv[bk].type = 269;
                break;
            }
        break;
    case 28:                    // deep elf knight

        switch (random3(13))
        {
        case 1:
        case 2:
        case 0:
            menv[bk].type = 263;
            break;
        case 3:
        case 4:
        case 5:
            menv[bk].type = 264;
            break;
        case 6:
        case 7:
            menv[bk].type = 265;
            break;
        case 8:
            menv[bk].type = 266;
            break;
        case 9:
            menv[bk].type = 267;
            break;
        case 10:
            menv[bk].type = 268;
            break;
        case 11:
            menv[bk].type = 269;
            break;
        case 12:
            if (random() % 4 == 0)
                menv[bk].type = 271 + random() % 4;
            else
                menv[bk].type = 266;
            break;
        }
        break;

    case 29:                    // deep elf high priest

        switch (random3(16))
        {
        case 1:
        case 2:
        case 0:
            menv[bk].type = 263;
            break;
        case 3:
        case 4:
        case 5:
            menv[bk].type = 264;
            break;
        case 6:
        case 7:
            menv[bk].type = 269;
            break;
        case 8:
            menv[bk].type = 269;
            break;
        case 9:
            menv[bk].type = 266;
            break;
        case 10:
            menv[bk].type = 267;
            break;
        case 11:
            menv[bk].type = 268;
            break;
        case 13:
        case 14:
        case 15:
        case 12:
            menv[bk].type = 271 + random() % 4;
        }
        break;
    case 30:
        menv[bk].type = 36;
        if (random3(3) == 0)
            menv[bk].type = 58;
        if (random3(13) == 0)
            menv[bk].type = 53;
        break;
// kobold demonologist
    case 31:                    // Nagas

        menv[bk].type = 161;
        break;
    case 32:                    // war dogs

        menv[bk].type = 150;
        break;
    case 33:                    // grey rats

        menv[bk].type = 151;
        break;
    case 34:                    // green rats

        menv[bk].type = 152;
        break;
    case 35:                    // orange rats

        menv[bk].type = 153;
        break;
    case 36:                    // sheep

        menv[bk].type = 155;
        break;
    case 37:                    // ghoul

        menv[bk].type = 156;
        if (random3(2) != 0)
            menv[bk].type = 13;
        break;
    case 38:                    // deep troll

        menv[bk].type = 168;
        break;
    case 39:                    // hog

        menv[bk].type = 157;
        break;
    case 40:                    // hell-hog

        menv[bk].type = 394;
        break;
    case 41:                    // mosquito

        menv[bk].type = 158;
        break;
    case 42:                    // boggart

        menv[bk].type = 396;
        break;
    case 43:                    // blink frog

        menv[bk].type = 180;
        break;
    case 44:                    // skeletal warrior

        menv[bk].type = 399;
        break;

    }


    if (menv[bk].type < MLAVA0)
        menv[bk].number = 250;

    define_monster(bk, menv);

    if (menv[bk].type >= 280 && menv[bk].type <= 309)
        you.unique_creatures[menv[bk].type - 280] = 1;

    plussed++;

    if (plus_seventy != 250)
        menv[bk].number = plus_seventy;

    if ((menv[bk].type == 25 || menv[bk].type == 107 |
         menv[bk].type == 51 || menv[bk].type == 108 |
         menv[bk].type == 367) && plus_seventy != 250)
    {
        define_zombie(3, plus_seventy, menv[bk].type);
    }
    else if (menv[bk].type == 25 || menv[bk].type == 51 |
             menv[bk].type == 107 || menv[bk].type == 108 |
             menv[bk].type == 367)
        define_zombie(3, 250, 250);

    if (mons_flag(menv[bk].type, M_INVIS))      //menv [bk].type == 46 || menv [bk].type == 141 || menv [bk].type == 240)

    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[2] = 6;
    }

    if (menv[bk].type == 99)
    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[1] = 39;
    }

    if (menv[bk].type == 98)
    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[1] = 38;
    }

    if (menv[bk].type == 66 || menv[bk].type == 21 || menv[bk].type == 244 || menv[bk].type == 141)     // butter, vort, vapour

    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[0] = 5;
    }



//do
    {


        switch (band)
        {
        case 0:         // no band

            passout = 0;
          give_up_on_band:passout = 0;
/*if (menv [bk].type == 19) // assuming can never be summoned
   {
   do
   {
   menv [bk].x = 10 + random3(70);
   menv [bk].y = 10 + random3(60);
   } while (grd [menv [bk].x] [menv [bk].y] < 67 || mgrd [menv [bk].x] [menv [bk].y] != MNG || grd [menv [bk].x + 1] [menv [bk].y] < 67 || mgrd [menv [bk].x + 1] [menv [bk].y] != MNG || grd [menv [bk].x + 2] [menv [bk].y] < 67 || mgrd [menv [bk].x + 2] [menv [bk].y] != MNG || grd [menv [bk].x + 3] [menv [bk].y] < 67 || mgrd [menv [bk].x + 3] [menv [bk].y] != MNG || grd [menv [bk].x + 4] [menv [bk].y] < 67 || mgrd [menv [bk].x + 4] [menv [bk].y] != MNG);
   //(grd [menv [bk].x] [mons [bk].y] < 17 || grd [mons [bk].x] [mons [bk].y] >= 50 || grd [mons [bk].x + 1] [mons [bk].y] < 67 || grd [mons [bk].x + 1] [mons [bk].y] >= 50 || grd [mons [bk].x + 2] [mons [bk].y] < 67 || grd [mons [bk].x + 2] [mons [bk].y] >= 50 || grd [mons [bk].x + 3] [mons [bk].y] < 67 || grd [mons [bk].x + 3] [mons [bk].y] >= 50 || grd [mons [bk].x + 4] [mons [bk].y] < 17 || grd [mons [bk].x + 4] [mons [bk].y] >= 50);
   // forget checking for x_pos/y_pos
   } else */
            if (type_place == 1)        // summoned

            {
                menv[bk].x = px;
                menv[bk].y = py;
            }
            else if (grid_ok == 67)
            {
                do
                {
                    menv[bk].x = 10 + random3(70);
                    menv[bk].y = 10 + random3(60);
//   if (passed [1] == 0 && menv [bk].x < you.x_pos + 7 && menv [bk].x > you.x_pos - 7 && menv [bk].y < you.y_pos + 7 && menv [bk].y > you.y_pos - 7 && random3(100) != 0) continue; // avoids (hopefully) monsters being generated on the same screen as you
                }
                while ((grd[menv[bk].x][menv[bk].y] < 67 |
                        mgrd[menv[bk].x][menv[bk].y] != MNG) |
                       (passed[1] == 0 && menv[bk].x < you.x_pos +
                        7 && menv[bk].x > you.x_pos - 7 &&
                        menv[bk].y < you.y_pos + 7 && menv[bk].y >
                        you.y_pos - 7 && random3(100) != 0));
            }                   // end if

            else
            {
                do
                {
                    menv[bk].x = 10 + random3(70);
                    menv[bk].y = 10 + random3(60);
                }
                while ((grd[menv[bk].x][menv[bk].y] != grid_ok && (grid_ok != 62 || grd[menv[bk].x][menv[bk].y] != 65)) || (menv[bk].x == you.x_pos && menv[bk].y == you.y_pos));
            }

/*if (menv [bk].type == 56) //worm > 1) // worm test
   {
   menv [bk].x = menv [bk - 1].x + 1;
   menv [bk].y = menv [bk - 1].y;
   if (grd [menv [bk].x] [menv [bk].y] == 1) grd [menv [bk].x] [menv [bk].y] = grid_ok;
   bj++;
   mgrd [menv [bk].x] [menv [bk].y] = bk;
   goto worm_tail;
   } */
            bj = 0;

            break;


        case 2:         // orcs following warrior

        case 1:         // kobolds

        default:                //  right?

            menv[bk].x = menv[bk - 1].x;
            menv[bk].y = menv[bk - 1].y;
            passout = 0;

            do
            {
                menv[bk].x += random3(3) - 1;
                menv[bk].y += random3(3) - 1;
                if (menv[bk].x > 79 || menv[bk].x < 5 || menv[bk].y > 69 || menv[bk].y < 5)
                {
                    menv[bk].x = menv[bk - 1].x;
                    menv[bk].y = menv[bk - 1].y;
                }
                passout++;
                if (passout > 10000)
                {
                    band_no--;
                    goto give_up_on_band;
                }
            }
            while (grd[menv[bk].x][menv[bk].y] < 67 || mgrd[menv[bk].x][menv[bk].y] != MNG || (menv[bk].x == you.x_pos && menv[bk].y == you.y_pos));
            band_no--;
// cannot have bands of water creatures!
            break;


        }


        if (allow_bands == 1)
        {
            switch (menv[bk].type)
            {
            case 14:
                if (random3(2) == 0)
                    break;
            case 52:
                if (bk < MNST - 50 && band == 0 && band_no == 0)        // && many_many > 10)

                {
                    band = 2;   // orcs

                    band_no = 2 + random3(3);
                }
                break;

            case 58:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && many_many
                    > 3)
                {
//  menv ly[bk].type = 36;
                    band = 1;   // K

                    band_no = 2 + random3(6);
                }
                break;

            case 262:           // orc warlord

            case 55:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 3;   // orcs + knight

                    band_no = 3 + random3(4);
                }
                break;

            case 10:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 4;   // killer bees

                    band_no = 2 + random3(4);
                }
                break;

            case 72:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 5;   // flying skulls

                    band_no = 2 + random3(4);
                }
                break;

            case 76:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 6;   // slime creatures

                    band_no = 2 + random3(4);
                }
                break;


            case 50:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 7;   // yaks

                    band_no = 2 + random3(4);
                }
                break;


            case 20:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 8;   // ugly things

                    band_no = 2 + random3(4);
                }
                break;


            case 73:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 9;   // hell hound

                    band_no = 2 + random3(3);
                }
                break;

            case 9:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 10;  // jackal

                    band_no = 1 + random3(3);
                }
                break;

            case 309:           // Margery

            case 109:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 11;  // hell knight

                    band_no = 4 + random3(4);
                }
                break;

            case 363:           // vamp mage

            case 294:           // Josephine

            case 110:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 22;  // necromancer

                    band_no = 4 + random3(4);
                }
                break;

            case 113:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 12;  // orc high priest

                    band_no = 4 + random3(4);
                }
                break;

            case 115:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 13;  // gnoll

                    band_no = 2 + random3(2);
                }
                break;

            case 138:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 16;  // bumble bees

                    band_no = 2 + random3(4);
                }
                break;

            case 376:
            case 2:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random3(3) == 0 && many_many > 9)
                {
                    band = 17;  // centaurs

                    band_no = 2 + random3(4);
                }
                break;

            case 377:
            case 133:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random3(2) == 0)
                {
                    band = 18;  // yaktaurs

                    band_no = 2 + random3(3);
                }
                break;

            case 134:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 21;  // death yaks

                    band_no = 2 + random3(4);
                }
                break;


            case 140:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 19;  // wisps

                    band_no = 4 + random3(5);
                }
                break;

            case 142:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 20;  // ogre mage

                    band_no = 4 + random3(4);
                }
                break;

            case 233:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 23;  // RED gr demon

                    band_no = 2 + random3(3);
                }
                break;

            case 234:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 24;  // BROWN gr demon

                    band_no = 1 + random3(3);
                }
                break;

            case 230:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random() % 2 == 0)
                {
                    band = 25;  // DARKGREY gr demon

                    band_no = 1 + random3(3);
                }
                break;

            case 227:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random() % 2 == 0)
                {
                    band = 26;  // LIGHTGREY gr demon

                    band_no = 1 + random3(4);
                }
                break;

            case 264:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random() % 2 == 0)
                {
                    band = 27;  // deep elf warrior

                    band_no = 3 + random3(4);
                }
                break;

            case 265:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random() % 2 == 0)
                {
                    band = 28;  // deep elf knight

                    band_no = 3 + random3(4);
                }
                break;

            case 270:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random() % 2 == 0)
                {
                    band = 29;  // deep elf high priest

                    band_no = 3 + random3(4);
                }
                break;

            case 53:
                if (bk < MNST - 50 && band == 0 && band_no == 0 && random() % 2 == 0)
                {
                    band = 30;  // kobold demonologist

                    band_no = 3 + random3(6);
                }
                break;

            case 260:
            case 261:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 31;  // Nagas

                    band_no = 3 + random3(4);
                }
                break;

            case 150:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 32;  // war dogs

                    band_no = 2 + random3(4);
                }
                break;

            case 151:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 33;  // grey rats

                    band_no = 4 + random3(6);
                }
                break;

            case 152:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 34;  // green rats

                    band_no = 4 + random3(6);
                }
                break;


            case 153:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 35;  // orange rats

                    band_no = 3 + random3(4);
                }
                break;


            case 155:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 36;  // sheep

                    band_no = 3 + random3(5);
                }
                break;

            case 156:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 37;  // ghoul

                    band_no = 2 + random3(3);
                }
                break;

            case 157:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 39;  // hog

                    band_no = 1 + random3(3);
                }
                break;

            case 158:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 41;  // mosquito

                    band_no = 1 + random3(3);
                }
                break;

            case 168:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 38;  // deep troll

                    band_no = 3 + random3(3);
                }
                break;

            case 394:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 40;  // hell-hog

                    band_no = 1 + random3(3);
                }
                break;

            case 396:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 42;  // boggart

                    band_no = 2 + random3(3);
                }
                break;

            case 180:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 43;  // blink frog

                    band_no = 2 + random3(3);
                }
                break;

            case 399:
                if (bk < MNST - 50 && band == 0 && band_no == 0)
                {
                    band = 44;  // skeletal warrior

                    band_no = 2 + random3(3);
                }
                break;




            }                   // end switch

        }                       // end if


        if (band > 0 && band_no == 0)
        {
            band = 0;
        }


    }                           //while (grd [menv [bk].x] [menv [bk].y] != grid_ok);
    // surely I don't need this?!

//if (menv [bk].type < MLAVA0)
    {
        mgrd[menv[bk].x][menv[bk].y] = bk;
    }


    if (gmon_use[menv[bk].type] > 0 || (menv[bk].type == 144 && plus_seventy != 1))
        give_item();

    if (menv[bk].type == 30 || menv[bk].type == 287)
        give_item();



    menv[bk].behavior = behaviour;
    menv[bk].monster_foe = hitting;


    if (menv[bk].type == 99)
    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[1] = 39;
    }

    if (menv[bk].type == 98)
    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[1] = 38;
    }

    if (mons_flag(menv[bk].type, M_INVIS))
    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[2] = 6;
    }

    if (menv[bk].type == 66)
    {
        menv[bk].enchantment1 = 1;
        menv[bk].enchantment[0] = 5;
    }

    if (menv[bk].type == 144)
    {
        menv[bk].number = mitm.colour[menv[bk].inv[0]];
    }

    if (band != 0)
        goto start_here;


    if (menv[bk].type == 0)
    {
//              continue;
    }



    if (worm != 0)
        goto start_here;        //worm_tail; //start_here;


    return plussed;

}                               // end int place_monster






void make_room(void)
{

    int find_door = 0;
    int diag_door = 0;

    for (bcount_x = room_x1; bcount_x < room_x2; bcount_x++)
    {
        if ((grd[bcount_x][room_y1 - 1] > 16 || grd[bcount_x][room_y1 - 1] == 3) && grd[bcount_x][room_y1 - 1] < 100)
            find_door++;
        if ((grd[bcount_x][room_y2] > 16 || grd[bcount_x][room_y2] == 3) && grd[bcount_x][room_y2] < 100)
            find_door++;
    }

    for (bcount_y = room_y1; bcount_y < room_y2; bcount_y++)
    {
        if ((grd[room_x1 - 1][bcount_y] > 16 || grd[room_x1 - 1][bcount_y] == 3) && grd[room_x1 - 1][bcount_y] < 100)
            find_door++;
        if ((grd[room_x2][bcount_y] > 16 || grd[room_x2][bcount_y] == 3) && grd[room_x2][bcount_y] < 100)
            find_door++;
    }

    if (grd[room_x1 - 1][room_y1 - 1] > 16 || grd[room_x1 - 1][room_y1 - 1] == 3)
        diag_door++;
    if (grd[room_x1 - 1][room_y2] > 16 || grd[room_x1 - 1][room_y2] == 3)
        diag_door++;
    if (grd[room_x2][room_y1 - 1] > 16 || grd[room_x2][room_y1 - 1] == 3)
        diag_door++;
    if (grd[room_x2][room_y2] > 16 || grd[room_x2][room_y2] == 3)
        diag_door++;


    if (diag_door + find_door > 1 && max_doors == 1)
    {
        bk--;
        time_run++;
        return;
    }


    if (find_door == 0 || find_door > max_doors)
    {
        bk--;
        time_run++;
        return;
    }

    for (bcount_x = room_x1; bcount_x < room_x2; bcount_x++)
    {
        for (bcount_y = room_y1; bcount_y < room_y2; bcount_y++)
        {
            if (grd[bcount_x][bcount_y] == 105)         //                grd [bcount_x] [bcount_y] = 67;

            {
                bk--;
                time_run++;
                return;
            }
        }
    }


    for (bcount_x = room_x1; bcount_x < room_x2; bcount_x++)
    {
        for (bcount_y = room_y1; bcount_y < room_y2; bcount_y++)
        {
            if (grd[bcount_x][bcount_y] < 68)
                grd[bcount_x][bcount_y] = 67;
        }
    }


    for (bcount_y = room_y1; bcount_y < room_y2; bcount_y++)
    {
        if (grd[room_x1 - 1][bcount_y] == 67 && grd[room_x1 - 1][bcount_y - 1] <= 16 && grd[room_x1 - 1][bcount_y + 1] <= 16 && bcount_y > room_y1 && bcount_y < room_y2)
        {
            if (random3(10) < doorlevel)
                grd[room_x1 - 1][bcount_y] = 3;
        }

        if (grd[room_x2][bcount_y] == 67 && grd[room_x2][bcount_y - 1] <= 16 && grd[room_x2][bcount_y + 1] <= 16 && bcount_y > room_y1 && bcount_y < room_y2)
        {
            if (random3(10) < doorlevel)
                grd[room_x2][bcount_y] = 3;
        }
    }


    for (bcount_x = room_x1; bcount_x < room_x2; bcount_x++)
    {
        if (grd[bcount_x][room_y1 - 1] == 67 && grd[bcount_x - 1][room_y1 - 1] <= 16 && grd[bcount_x + 1][room_y1 - 1] <= 16 && bcount_x > room_x1 && bcount_x < room_x2)
        {
            if (random3(10) < doorlevel)
                grd[bcount_x][room_y1 - 1] = 3;
        }

        if (grd[bcount_x][room_y2] == 67 && grd[bcount_x - 1][room_y2] <= 16 && grd[bcount_x + 1][room_y2] <= 16 && bcount_x > room_x1 && bcount_x < room_x2)
        {
            if (random3(10) < doorlevel)
                grd[bcount_x][room_y2] = 3;
        }
    }




    time_run++;



}                               //end of void make_room()



void big_room(void)
{

    unsigned char type_floor = 67;
    unsigned char type_2 = 67;
    int i, j, k, l;

    if (random3(4) == 0)
    {
        oblique = random3(20) + 5;
        oblique_max = oblique;

        room_x1 = random3(30) + 8;
        room_y1 = random3(22) + 8;
        room_x2 = room_x1 + random3(10) + 20;
        room_y2 = room_y1 + random3(8) + 20;

        if (random3(5) != 0 || many_many <= 7 + random3(8))
        {
            octa_room(67);
//              chequerboard(grd, type_floor, 67, type_floor, room_x1 + 1, room_y1 + 1, room_x2 - 1, room_y2 - 1);
            return;
        }
//              octa_room(grd, 61);
        type_floor = 61;
        if (many_many > 7)      // stops water on level 1

            if (random3(many_many) <= 13)
                type_floor = 62;
            else
                type_floor = 61;

        if (many_many >= 75 && many_many < 80)
            return;             // Dis - Is this even possible?

        if (many_many >= 80 && many_many < 85)
            type_floor = 61;    // G

        if (many_many >= 85 && many_many < 90)
            type_floor = 62;    // C

        if (many_many >= 90 && many_many < 95)
            return;             // T

        octa_room(type_floor);
        return;
    }

    room_x1 = random3(30) + 8;
    room_y1 = random3(22) + 8;
    room_x2 = room_x1 + random3(10) + 20;
    room_y2 = room_y1 + random3(8) + 20;

    for (bi = room_x1; bi < room_x2; bi++)
    {
        for (bj = room_y1; bj < room_y2; bj++)
        {

            if (grd[bi][bj] == 105)
                return;

        }                       // end of for j

    }                           // end of for i

    if (random3(4) == 0 && many_many > 7)
    {
        type_floor = 61;
        if (many_many > 7)      // stops water on level 1

            if (random3(many_many) <= 13)
                type_floor = 62;
            else
                type_floor = 61;
    }

    if (many_many >= 75 && many_many < 80)
        return;                 // Is this even possible?

    if (many_many >= 80 && many_many < 85 && random3(3) != 0)
        type_floor = 61;        // G

    if (many_many >= 85 && many_many < 90 && random3(3) != 0)
        type_floor = 62;        // C
    //  if (many_many >= 90 && many_many < 95) return; // T

    for (bi = room_x1; bi < room_x2; bi++)
    {
        for (bj = room_y1; bj < room_y2; bj++)
        {

            if (grd[bi][bj] == 1 || grd[bi][bj] == 3)
                grd[bi][bj] = type_floor;

        }                       // end of for j

    }                           // end of for i

    if (type_floor == 67)
        type_2 = 1 + random3(4);
    if (random3(4) == 0)
        chequerboard(type_floor, type_2, type_floor, room_x1 + 1, room_y1 + 1, room_x2 - 1, room_y2 - 1);
    else if (random3(6) == 0)
    {
        i = room_x1;
        j = room_y1;
        k = room_x2;
        l = room_y2;
        do
        {
            i = i + 2 + random3(3);
            j = j + 2 + random3(3);
            k = k - 2 - random3(3);
            l = l - 2 - random3(3);
            if (i >= k - 3)
                break;
            if (j >= l - 3)
                break;

            box_room(i, k, j, l, 2);

        }
        while (many_many < 1500);       // ie forever

    }
}                               // end of void big_room(void)


void diamond_rooms(void)
{

    char numb_diam = random3(10) + 1;
    char type_floor = 62;
    int runthru = 0;

    if (many_many >= 6 + random3(5) && random3(2) != 0)
        type_floor = 65;        // shallow water

    if (many_many >= 11 + random3(5) && random3(2) != 0)
        type_floor = 62;        // water

    if (many_many >= 18 && random3(2) == 0)
        type_floor = 61;        // lava

    if (random3(15) == 0 && many_many > 10)
        type_floor = random3(2) + 1;
    if (random3(20) == 0 && many_many > 12)
        type_floor = 4;

    if (you.where_are_you == 2)
        type_floor = 61;        // Gehenna

    if (you.where_are_you == 4)
        type_floor = 62;        // Cocytus

    if (you.where_are_you == 1)
        return;                 // Dis

    if (you.where_are_you == 5)
        return;                 // Tartarus

//      type_floor = 62;

    for (bk = 0; bk < numb_diam; bk++)
    {
        room_x1 = random3(43) + 8;
        room_y1 = random3(35) + 8;
        room_x2 = room_x1 + random3(15) + 5;
        room_y2 = room_y1 + random3(10) + 5;

        oblique = (room_x2 - room_x1) / 2;      //random3(20) + 5;

        oblique_max = oblique;



        for (bi = room_x1; bi < room_x2; bi++)
        {
            for (bj = room_y1 + oblique; bj < room_y2 - oblique; bj++)
            {

                if (grd[bi][bj] == 67)
                    goto draw_it;

            }                   // end of for j

            if (oblique > 0)
                oblique--;
            if (bi > room_x2 - oblique_max)
                oblique += 2;
        }                       // end of for i


        bk--;
        runthru++;
        if (runthru >= 10)
        {
            runthru = 0;
            bk++;
        }
        continue;

//              bk ++;
draw_it:
        octa_room(type_floor);
    }
}                               // end of diamond_rooms()





void octa_room(unsigned char type_floor)
{


    for (bi = room_x1; bi < room_x2; bi++)
    {
        for (bj = room_y1 + oblique; bj < room_y2 - oblique; bj++)
        {
            if (grd[bi][bj] == 105)
                return;
        }                       // end of for j

        if (oblique > 0)
            oblique--;

        if (bi > room_x2 - oblique_max)
            oblique += 2;

    }                           // end of for i

    oblique = oblique_max;


    for (bi = room_x1; bi < room_x2; bi++)
    {
        for (bj = room_y1 + oblique; bj < room_y2 - oblique; bj++)
        {

            //if (bj - room_y1 <= oblique && i - room_x1 <= oblique) continue;

            //if (bj - room_y1 + i - room_x1 < oblique) continue;

            //if ((room_y2 - j) * -1 + room_x2 - 1 < oblique) continue;

            if (grd[bi][bj] == 1)
                grd[bi][bj] = type_floor;
            if (grd[bi][bj] == 67 && type_floor == 65)
                grd[bi][bj] = 65;
            if (type_floor >= 10 && grd[bi][bj] == 3)
                grd[bi][bj] = 67;       // ick
            //                      if (type_floor < 10 && grd [bi] [bj] == 3) grd [bi] [bj] = 1; // ick!


        }                       // end of for j

        if (oblique > 0)
            oblique--;

        if (bi > room_x2 - oblique_max)
            oblique += 2;

    }                           // end of for i

}


void make_trail(void)
{


    do                          // (while finish < no_corr)

    {


        if (x_ps < 15)
            dir_x2 = 1;
        else
            dir_x2 = 0;
        if (x_ps > 65)
            dir_x2 = -1;
        if (y_ps < 15)
            dir_y2 = 1;
        else
            dir_y2 = 0;
        if (y_ps > 55)
            dir_y2 = -1;

        rannumber = random3(10);

        if (random3(2) == 0)    // Put something in to make it go to parts of map it isn't in now

        {
            if (dir_x2 != 0 && rannumber < 6)
                dir_x = dir_x2;
            if (dir_x2 == 0 || rannumber >= 6)
            {
                switch (random3(2))
                {
                case 0:
                    dir_x = -1;
                    break;
                case 1:
                    dir_x = 1;
                    break;
                }
            }
            dir_y = 0;
        }
        else
        {
            if (dir_y2 != 0 && rannumber < 6)
                dir_y = dir_y2;
            if (dir_y2 == 0 || rannumber >= 6)
            {
                switch (random3(2))
                {
                case 0:
                    dir_y = -1;
                    break;
                case 1:
                    dir_y = 1;
                    break;
                }
            }
            dir_x = 0;
        }




        if (dir_x == 0 && dir_y == 0)
            continue;

        if (x_ps < 8)
        {
            dir_x = 1;
            dir_y = 0;
        }

        if (y_ps < 8)
        {
            dir_y = 1;
            dir_x = 0;
        }

        if (x_ps > 72)
        {
            dir_x = -1;
            dir_y = 0;
        }

        if (y_ps > 62)
        {
            dir_y = -1;
            dir_x = 0;
        }


        if (dir_x == 0)
            length = random3(corrlength) + 2;

        bi = 0;
        for (bi = 0; bi < length; bi++)
        {

            //      Below, I've changed the values of the unimportant variable from 0
            //      to random3(3) - 1 to avoid getting stuck on the "stuck!!" bit.

            if (x_ps < 9)
            {
                dir_y = 0;      //random3(3) - 1;

                dir_x = 1;
            }

            if (x_ps > 71)
            {
                dir_y = 0;      //random3(3) - 1;

                dir_x = -1;
            }

            if (y_ps < 9)
            {
                dir_y = 1;
                dir_x = 0;      //random3(3) - 1;

            }

            if (y_ps > 61)
            {
                dir_y = -1;
                dir_x = 0;      //random3(3) - 1;

            }

            // This bit is a near copy of the above:

            if (grd[x_ps + dir_x][y_ps + dir_y] == 105)
                break;


// Shouldn't this be:
            if (grd[x_ps + 2 * dir_x][y_ps + 2 * dir_y] == 67 && random3(intersect_chance) != 0)
                break;

            x_ps += dir_x;
            y_ps += dir_y;

            if (grd[x_ps][y_ps] == 1)
                grd[x_ps][y_ps] = 67;

        }                       // end of (while) i loop



        if (finish == no_corr - 1 && grd[x_ps][y_ps] != 67)
        {
            finish -= 2;
        }






        finish++;


    }
    while (finish < no_corr);   // end of do while finish loop


    finish = 0;


}                               // end of void make_trail(void)


static void set_weapon_special( int bp, int spwpn )
{
    mitm.special[bp] = (mitm.special[bp] / 30) * 30 + spwpn;
}

int items(unsigned char allow_uniques,
          int force_class,
          int force_type,
          int force_place,
          int many_many,        // remember, this is the level of the item, which can be
// different from global many_many eg in treasure vaults.
           int force_spec       // for weapons particular to a race
)
{
    int quant = 0;
    int pot = 0;
    int bkk = 0;
    int fpass[10];

// used in books:
    char strungy[9];
    int icky = 0;
    int numbo = 0;
    int multip = 0;
    int xj = 0;
    int bp;

    int no_unique = 0;


    if (many_many >= 50 && many_many != 351)
        many_many = 50;

    for (bp = 0; bp < 400; bp++)
    {
        /* if (bp == 1) continue; */
        if (mitm.base_type[bp] == 100 || mitm.quantity[bp] == 0)
            break;
        if (bp == 380)
            return 501;
    }
    mitm.base_type[bp] = random3(12);   // + 2;

    mitm.id[bp] = 0;
    mitm.special[bp] = 0;
    mitm.pluses[bp] = 0;
    mitm.pluses2[bp] = 0;
    mitm.sub_type[bp] = 0;


    if (((mitm.base_type[bp] == 3 || mitm.base_type[bp] == 7) && random3(5) < 2))
        mitm.base_type[bp] = 1; // missiles

    if ((mitm.base_type[bp] == 10 || mitm.base_type[bp] == 11) && random3(5) != 0)
        mitm.base_type[bp] = 6;
    if (mitm.base_type[bp] == 11 && random3(2) != 0)
        mitm.base_type[bp] = 6;
    if ((mitm.base_type[bp] == 3 || mitm.base_type[bp] == 7) && random3(4) == 0)
        mitm.base_type[bp] = 1; // missile

    if ((mitm.base_type[bp] == 3 || mitm.base_type[bp] == 7) && random3(4) == 0)
        mitm.base_type[bp] = 5; // potion

    if (random3(15) == 0)
        mitm.base_type[bp] = 15;        // money

    if (random3(20) == 0)
        mitm.base_type[bp] = 4; // food

//      mitm.base_type [bp] = 10;

    if (20 + many_many >= random3(3500) && many_many > 7)
        mitm.base_type[bp] = 13;

//      mitm.base_type [bp] = random3 (3) + 3;

//mitm.base_type [bp] = random3(3);

//              if (random3 (4) == 0) mitm.base_type [bp] = 0;
    //              if (random3 (4) == 0) mitm.base_type [bp] = 1;

//              mitm.base_type [bp] = 10;

    if (force_class != 250)
        mitm.base_type[bp] = force_class;

    switch (mitm.base_type[bp])
    {

    case OBJ_WEAPONS:

     do
     {
                mitm.sub_type [bp] = random3(50);
     } while(random3(11) >= rare_weapon(mitm.sub_type [bp]));


/*        mitm.sub_type[bp] = random3(19);

        if (random3(6) == 0)
        {
            switch (random3(10))
            {
            case 0:
                mitm.sub_type[bp] = WPN_GREAT_FLAIL;
                break;

            case 1:
                mitm.sub_type[bp] = WPN_SPIKED_FLAIL;
                break;

            case 2:
            case 3:
                mitm.sub_type[bp] = WPN_GREAT_MACE;
                break;

            case 4:
            case 5:
            case 6:
                mitm.sub_type[bp] = WPN_AXE;
                break;

            case 7:
            case 8:
            case 9:
                mitm.sub_type[bp] = WPN_TRIDENT;
                break;
            }
        }
*/

        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_KNIFE;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_QUARTERSTAFF;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_SLING;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_SPEAR;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_HAND_AXE;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_DAGGER;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_MACE;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_DAGGER;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_CLUB;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_HAMMER;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_WHIP;
        if (random3(200) < 20 - many_many)
            mitm.sub_type[bp] = WPN_SABRE;

        if (many_many > 6 && random3(100) < 10 + many_many && random3(30) == 0)
        {
             do
             {
                        mitm.sub_type [bp] = random3(50);
             } while(rare_weapon(mitm.sub_type [bp]) > 0 || rare_weapon(mitm.sub_type [bp]) == -1);
        }

        if (allow_uniques == 1)
        {
            // Note there is nothing to stop randarts being reproduced,
            // except vast improbability.
            if (mitm.sub_type[bp] > 0 && random3(2000) <= 100 + many_many * 3
                                        && random3(2) == 0 && many_many > 2)
            {
                if (random3(50) == 0 && you.level_type != LEVEL_ABYSS
                                    && you.level_type != LEVEL_PANDEMONIUM)
                {
                    icky = find_okay_unrandart(OBJ_WEAPONS);
                    if (icky != -1)
                    {
                        quant = 1;
                        make_item_unrandart(icky, bp);
                        break;
                    }
                }

                mitm.special[bp] = 26 + random3(4);
                mitm.pluses[bp] = 50;
                mitm.pluses2[bp] = 50;
                mitm.pluses[bp] += random3(7);
                mitm.pluses2[bp] += random3(7);

                if (random3(3) == 0)
                    mitm.pluses[bp] += random3(7);

                if (random3(3) == 0)
                    mitm.pluses2[bp] += random3(7);

                if (random3(9) == 0)
                    mitm.pluses[bp] -= random3(7);

                if (random3(9) == 0)
                    mitm.pluses2[bp] -= random3(7);

                quant = 1;

                if (random3(4) == 0)
                {
                    mitm.pluses[bp] = 150 - random3(6);
                    mitm.pluses2[bp] = 50 - random3(6);
                }
                else if (random3(3) != 0 && (mitm.pluses[bp] < 50
                                                    || mitm.pluses2[bp] < 50))
                {
                    mitm.pluses[bp] += 100;     /* cursed! nasty */
                }
                break;
            }

            if (random3(3000) <= 30 + many_many * 3
                                    && random3(20) == 0 && many_many > 6)
            {
                no_unique = random3(12);
                if (no_unique <= 6)
                {
                    if (you.unique_items[no_unique] == 1
                            || (many_many == 51
                                    && you.unique_items[no_unique] == 0)
                            || (you.unique_items[no_unique] == 2
                                    && many_many != 51))
                    {
                        goto out_of_uniques;
                    }
                }
                else if (you.unique_items[24 + no_unique - 7] == 1
                         || (many_many == 51
                             && you.unique_items[24 + no_unique - 7] == 0)
                         || (you.unique_items[24 + no_unique - 7] == 2
                             && many_many != 51))
                {
                    goto out_of_uniques;
                }

                /* unique_items: 1 = created and still exists (may be lost underwater etc), 2 = created and lost in the abyss - may be generated again (in the abyss).
                   Problem: a unique can be generated in the abyss and never be seen by the player, then will be classed as lost in the abyss and will only be found again in the abyss */


                mitm.pluses[bp] = 50;
                mitm.pluses2[bp] = 50;
                switch (no_unique)
                {
                case 0:
                    mitm.sub_type[bp] = 6;
                    mitm.special[bp] = NWPN_SINGING_SWORD;
                    mitm.pluses[bp] += 7;
                    mitm.pluses2[bp] += 6;
                    break;
                case 1:
                    mitm.sub_type[bp] = 10;
                    mitm.special[bp] = NWPN_WRATH_OF_TROG;
                    mitm.pluses[bp] += 3;
                    mitm.pluses2[bp] += 11;
                    break;
                case 2:
                    mitm.sub_type[bp] = 19;
                    mitm.special[bp] = NWPN_SCYTHE_OF_CURSES;
                    mitm.pluses[bp] += 11;
                    mitm.pluses2[bp] += 11;
                    break;
                case 3:
                    mitm.sub_type[bp] = 1;
                    mitm.special[bp] = NWPN_MACE_OF_VARIABILITY;
                    mitm.pluses[bp] += random3(12) - 4;
                    mitm.pluses2[bp] += random3(12) - 4;
                    break;
                case 4:
                    mitm.sub_type[bp] = 17;
                    mitm.special[bp] = NWPN_GLAIVE_OF_PRUNE;
                    mitm.pluses[bp] += 0;
                    mitm.pluses2[bp] += 12;
                    break;
                case 5:
                    mitm.sub_type[bp] = 1;
                    mitm.special[bp] = NWPN_SCEPTRE_OF_TORMENT;
                    mitm.pluses[bp] += 7;
                    mitm.pluses2[bp] += 6;
                    break;
                case 6:
                    mitm.sub_type[bp] = 6;
                    mitm.special[bp] = NWPN_SWORD_OF_ZONGULDROK;
                    mitm.pluses[bp] += 9;
                    mitm.pluses2[bp] += 9;
                    break;
                    // dam 188 - sword of Okawaru. This is not a 'unique_items' item because it's only ever generated with Okawaru
                    // talking axe, muttering club, sword of terror?
                case 7:
                    if (random3(2))
                    {
                        mitm.sub_type[bp] = 7;
                        mitm.special[bp] = NWPN_SWORD_OF_POWER;
                        mitm.pluses[bp] += 0;
                        mitm.pluses2[bp] += 0;
                    }
                    else
                    {
                        // must avoid setting flag if not created.
                        goto out_of_uniques;
                    }
                    break;
                case 8:
                    mitm.sub_type[bp] = 3;
                    mitm.special[bp] = NWPN_KNIFE_OF_ACCURACY;
                    mitm.pluses[bp] += 27;
                    mitm.pluses2[bp] -= 1;
                    break;
                case 9:
                    mitm.sub_type[bp] = 18;
                    mitm.special[bp] = NWPN_STAFF_OF_OLGREB;
                    break;
                case 10:
                    mitm.sub_type[bp] = 3;
                    mitm.special[bp] = NWPN_VAMPIRE_S_TOOTH;
                    mitm.pluses[bp] += 3;
                    mitm.pluses2[bp] += 4;
                    break;
                case 11:
                    mitm.sub_type[bp] = 18;
                    mitm.special[bp] = NWPN_STAFF_OF_WUCAD_MU;
                    mitm.pluses[bp] += 0;
                    mitm.pluses2[bp] += 0;
                    break;
                }

                quant = 1;

                if (no_unique <= 6)
                    you.unique_items[no_unique] = 1;
                else
                    you.unique_items[24 + no_unique - 7] = 1;

                break;
            }
        }

out_of_uniques:
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;

        if (many_many == 351 && (mitm.sub_type[bp] == 0
                                            || mitm.sub_type[bp] == 13))

            mitm.sub_type[bp] = 6;
        quant = 1;

        mitm.pluses[bp] = 50;
        mitm.pluses2[bp] = 50;
        mitm.special[bp] = 0;

        if (force_spec == 250 && random() % 2 == 0)
        {
            switch (mitm.sub_type[bp])
            {
            case WPN_CLUB:             // club
                if (random() % 2 == 0)
                    mitm.special[bp] = 90;
                break;

            case WPN_MACE:             // mace
            case WPN_FLAIL:             // flail
            case WPN_SPIKED_FLAIL:
            case WPN_GREAT_MACE:
            case WPN_GREAT_FLAIL:
                if (random() % 3 == 0)
                    mitm.special[bp] = 90;
                if (random() % 4 == 0)
                    mitm.special[bp] = 150;
                if (random() % 6 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_MORNINGSTAR:             // morningstar
            case WPN_HAMMER:            // hammer
                if (random() % 3 == 0)
                    mitm.special[bp] = 90;
                if (random() % 3 == 0)
                    mitm.special[bp] = 150;
                break;

            case WPN_DAGGER:             // dagger
                if (random() % 3 == 0)
                    mitm.special[bp] = 90;
                if (random() % 4 == 0)
                    mitm.special[bp] = 150;
                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_SHORT_SWORD:             // sh sword
                if (random() % 3 == 0)
                    mitm.special[bp] = 90;
                if (random() % 3 == 0)
                    mitm.special[bp] = 150;
                if (random() % 3 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_LONG_SWORD:             // long sword
                if (random() % 4 == 0)
                    mitm.special[bp] = 90;
                if (random() % 2 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_GREAT_SWORD:             // gr sword
                if (random() % 3 == 0)
                    mitm.special[bp] = 90;
                break;

            case WPN_SCIMITAR:             // scimitar
                if (random() % 2 == 0)
                    mitm.special[bp] = 90;
                break;

            case WPN_AXE:
            case WPN_HAND_AXE:             // hand axe
            case WPN_BROAD_AXE:             // hand axe
            case WPN_BATTLEAXE:            // battleaxe
                if (random() % 3 == 0)
                    mitm.special[bp] = 90;
                if (random() % 2 == 0)
                    mitm.special[bp] = 150;
                break;

            case WPN_SPEAR:            // spear
                if (random() % 4 == 0)
                    mitm.special[bp] = 90;
                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_HALBERD:            // halberd
            case WPN_GLAIVE:            // glaive
            case WPN_TRIDENT:            // glaive
            case WPN_EXECUTIONERS_AXE:            // exec axe
                if (random() % 5 == 0)
                    mitm.special[bp] = 90;
                break;

            case WPN_QUICK_BLADE:            // quick blade
                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_KATANA:            // katana
            case WPN_KNIFE:
                mitm.special[bp] = 0;
                break;

                // 13 - sling

            case WPN_BOW:            // bow
                if (random() % 6 == 0)
                    mitm.special[bp] = 90;
                if (random() % 2 == 0)
                    mitm.special[bp] = 120;
                break;

            case WPN_CROSSBOW:            // xbow
                if (random() % 4 == 0)
                    mitm.special[bp] = 90;
                break;

            case WPN_HAND_CROSSBOW:            // hand xbow
                if (random() % 3 == 0)
                    mitm.special[bp] = 120;     // deep elf

                break;

                // 18 - staff
            }
        }

        switch (force_spec)
        {
        case 1:         // elf

            mitm.special[bp] = 120;
            break;

        case 2:         // dwarf

            mitm.special[bp] = 150;
            break;

        case 3:         // orc

            mitm.special[bp] = 90;
            break;
        }

        switch (mitm.special[bp])
        {
        case 120:               // elf

            mitm.pluses[bp] += random() % 2;
            break;

        case 150:               // dwarf

            mitm.pluses2[bp] += random() % 2;
            mitm.pluses[bp] += random() % 2;
            break;

        case 90:                // orc

            mitm.pluses[bp] -= random() % 2;
            mitm.pluses2[bp] += random() % 2;
            break;
        }


        if ((random3(200) <= 50 + many_many || many_many == 351
                        || mitm.sub_type[bp] == 32 || mitm.sub_type[bp] == 33)
                // nobody would bother enchanting a club
                && mitm.sub_type[bp] != WPN_CLUB
                && mitm.sub_type[bp] != WPN_GIANT_CLUB
                && mitm.sub_type[bp] != WPN_GIANT_SPIKED_CLUB)
        {
            if (many_many == 351)
                many_many = 200;
            mitm.pluses[bp] += random3(3);
            mitm.pluses2[bp] += random3(3);
            if (random3(350) <= 20 + many_many)
            {
                mitm.pluses[bp] += random3(3);
                if (random3(350) <= 20 + many_many)
                {
                    mitm.pluses[bp] += random3(3);
                    if (random3(350) <= 20 + many_many)
                        mitm.pluses[bp] += random3(3);
                }
            }

            if (random3(500) <= 50 + many_many)
            {
                mitm.pluses2[bp] += random3(3);
                if (random3(500) <= 50 + many_many)
                {
                    mitm.pluses2[bp] += random3(3);
                    if (random3(500) <= 50 + many_many)
                        mitm.pluses2[bp] += random3(3);
                }
            }

            if (random3(300) <= 100 + many_many
                        || (many_many == 351 && random() % 2 == 0)
                        || mitm.sub_type[bp] == WPN_DEMON_BLADE
                        || mitm.sub_type[bp] == WPN_DEMON_WHIP
                        || mitm.sub_type[bp] == WPN_DEMON_TRIDENT)
            {
                // note: even this doesn't guarantee special enchantment
                switch (mitm.sub_type[bp])
                {
                case WPN_CLUB:
                case WPN_GIANT_CLUB:
                case WPN_GIANT_SPIKED_CLUB:
                case WPN_KATANA:
                case WPN_KNIFE:
                case WPN_QUICK_BLADE:
                    // No standard ego types for these weapons.
                    break;


                case WPN_EVENINGSTAR:
                    if (random() % 2 == 0)
                        set_weapon_special( bp, SPWPN_DRAINING );

                case WPN_MORNINGSTAR:
                    if (random() % 4 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                    if (random() % 4 == 0)
                        set_weapon_special( bp, SPWPN_FLAMING + random3(2) );

                    if (random() % 20 == 0)
                        set_weapon_special( bp, SPWPN_VAMPIRICISM );

                case WPN_MACE:
                case WPN_GREAT_MACE:
                    if ((mitm.sub_type[bp] == WPN_MACE
                                || mitm.sub_type[bp] == WPN_GREAT_MACE)
                            && random() % 4 == 0)
                    {
                        set_weapon_special( bp, SPWPN_DISRUPTION );
                    }

                case WPN_FLAIL:
                case WPN_SPIKED_FLAIL:
                case WPN_GREAT_FLAIL:
                case WPN_HAMMER:
                    if (random() % 15 == 0)
                        set_weapon_special( bp, SPWPN_DISTORTION );

                    if (random() % 25 == 0)
                        set_weapon_special( bp, SPWPN_PAIN );

                    if (random() % 4 == 0)
                        set_weapon_special( bp, SPWPN_HOLY_WRATH );

                    if (random() % 3 == 0)
                        set_weapon_special( bp, SPWPN_PROTECTION );

                    if (random() % 10 == 0)
                        set_weapon_special( bp, SPWPN_DRAINING );

                    if (random() % 3 == 0)
                        set_weapon_special( bp, SPWPN_VORPAL );
                    break;


                case WPN_DAGGER:
                    if (random() % 3 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                    if (random() % 10 == 0)
                        set_weapon_special( bp, SPWPN_VAMPIRICISM );

                case WPN_SHORT_SWORD:
                    if (random() % 8 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                case WPN_SCIMITAR:
                    if (random() % 7 == 0)
                        set_weapon_special( bp, SPWPN_SPEED );

                case WPN_LONG_SWORD:
                    if (random() % 12 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                case WPN_GREAT_SWORD:
                case WPN_DOUBLE_SWORD:
                case WPN_TRIPLE_SWORD:
                    if (random() % 10 == 0)
                        set_weapon_special( bp, SPWPN_VAMPIRICISM );

                    if (random() % 15 == 0)
                        set_weapon_special( bp, SPWPN_DISTORTION );

                    if (random() % 25 == 0)
                        set_weapon_special( bp, SPWPN_PAIN );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_FLAMING + random3(2) );

                    if (random() % 7 == 0)
                        set_weapon_special( bp, SPWPN_ELECTROCUTION );

                    if (random() % 7 == 0)
                        set_weapon_special( bp, SPWPN_PROTECTION );

                    if (random() % 8 == 0)
                        set_weapon_special( bp, SPWPN_ORC_SLAYING );

                    if (random() % 12 == 0)
                        set_weapon_special( bp, SPWPN_DRAINING );

                    if (random() % 4 == 0)
                        set_weapon_special( bp, SPWPN_HOLY_WRATH );

                    if (random() % 2 == 0)
                        set_weapon_special( bp, SPWPN_VORPAL );

                    break;


                case WPN_AXE:
                case WPN_BROAD_AXE:
                case WPN_BATTLEAXE:
                case WPN_EXECUTIONERS_AXE:
                    if (random() % 25 == 0)
                        set_weapon_special( bp, SPWPN_HOLY_WRATH );

                    if (random() % 14 == 0)
                        set_weapon_special( bp, SPWPN_DRAINING );

                case WPN_HAND_AXE:
                    if (random() % 10 == 0)
                        set_weapon_special( bp, SPWPN_VAMPIRICISM );

                    if (random() % 15 == 0)
                        set_weapon_special( bp, SPWPN_DISTORTION );

                    if (random() % 25 == 0)
                        set_weapon_special( bp, SPWPN_PAIN );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_ORC_SLAYING );

                    if (random() % 4 == 0)
                        set_weapon_special( bp, SPWPN_FLAMING + random3(2) );

                    if (random() % 8 == 0)
                        set_weapon_special( bp, SPWPN_ELECTROCUTION );

                    if (random() % 12 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                    if (random() % 2 == 0)
                        set_weapon_special( bp, SPWPN_VORPAL );

                    break;

                case WPN_WHIP:
                    if (random() % 20 == 0)
                        set_weapon_special( bp, SPWPN_DISTORTION );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_FLAMING + random3(2) );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_REACHING );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_SPEED );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_ELECTROCUTION );
                    break;

                case WPN_HALBERD:
                case WPN_GLAIVE:
                    if (random() % 30 == 0)
                        set_weapon_special( bp, SPWPN_HOLY_WRATH );

                    if (random() % 4 == 0)
                        set_weapon_special( bp, SPWPN_PROTECTION );

                case WPN_SCYTHE:
                case WPN_TRIDENT:
                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_SPEED );

                case WPN_SPEAR:
                    if (random() % 10 == 0)
                        set_weapon_special( bp, SPWPN_VAMPIRICISM );

                    if (random() % 20 == 0)
                        set_weapon_special( bp, SPWPN_DISTORTION );

                    if (random() % 25 == 0)
                        set_weapon_special( bp, SPWPN_PAIN );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_ORC_SLAYING );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_FLAMING + random3(2) );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );

                    if (random() % 6 == 0)
                        set_weapon_special( bp, SPWPN_REACHING );

                    if (random() % 3 == 0)
                        set_weapon_special( bp, SPWPN_VORPAL );
                    break;


                case WPN_SLING:
                    if (random() % 4 != 0)
                        break;

                case WPN_HAND_CROSSBOW:
                    if (random() % 2 != 0)
                        break;

                case WPN_BOW:
                case WPN_CROSSBOW:
                    if (random() % 2 == 0)
                        set_weapon_special( bp, SPWPN_FLAME + random3(2) );
                    break;


                // quarterstaff - not powerful, as this would make
                // the 'staves' skill just too good
                case WPN_QUARTERSTAFF:
                    if (random() % 15 == 0)
                        set_weapon_special( bp, SPWPN_DISTORTION );

                    if (random() % 25 == 0)
                        set_weapon_special( bp, SPWPN_PAIN );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_PROTECTION );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_SPEED );
                    break;


                case WPN_DEMON_TRIDENT:
                case WPN_DEMON_WHIP:
                case WPN_DEMON_BLADE:
                    if (mitm.special[bp] >= 90)
                        mitm.special[bp] = mitm.special[bp] % 30;

                    if (random() % 3 == 0
                            && (mitm.sub_type[bp] == WPN_DEMON_WHIP
                                || mitm.sub_type[bp] == WPN_DEMON_TRIDENT))
                    {
                        set_weapon_special( bp, SPWPN_REACHING );
                    }

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_DRAINING );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_FLAMING );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_FREEZING );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_ELECTROCUTION );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_VAMPIRICISM );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_PAIN );

                    if (random() % 5 == 0)
                        set_weapon_special( bp, SPWPN_VENOM );
                    break;
                }
            }                   // end if specially enchanted
        }
        else
        {
            if (random3(12) == 0)
            {
                mitm.pluses[bp] = 150;
                mitm.pluses[bp] -= random3(4);
                mitm.pluses2[bp] = 50;
                mitm.pluses2[bp] -= random3(4);
                mitm.special[bp] = (mitm.special[bp] / 30) * 30;
            }
        }

        if (mitm.special[bp] / 30 == 3)         // orc

        {
            if (mitm.special[bp] % 30 != 0)
                if (random() % 2 == 0 || mitm.special[bp] % 30 == 3
                                            || mitm.special[bp] % 30 == 5)
                {               // no holy wrath or slay orc

                    if (mitm.special[bp] % 30 == 4)
                        mitm.pluses[bp] = 50;
                    mitm.special[bp] = 90;
                }
        }


        if ((mitm.special[bp] != 0
                    || (mitm.pluses[bp] != 50 && random3(3) == 0))
                    && mitm.sub_type[bp] != 0 && mitm.special[bp] / 30 == 0)
        {
            mitm.special[bp] += 30 + random3(2) * 30;
        }
        break;

    case OBJ_MISSILES:
        mitm.pluses[bp] = 0;
        mitm.sub_type[bp] = random3(4);

        if (force_type != 250)
            mitm.sub_type[bp] = force_type;

        if (force_spec != 250)
            switch (force_spec)
            {
            case 1:             // elf

                mitm.special[bp] = 120;
                break;
            case 2:             // dw

                mitm.special[bp] = 150;
                break;
            case 3:             // orc

                mitm.special[bp] = 90;
                break;
            }
        else
        {
            if (random() % 4 == 0
                        && (mitm.sub_type[bp] == 1 || mitm.sub_type[bp] == 3))
                mitm.special[bp] = 120;         // elven

            if (random() % 4 == 0
                        && (mitm.sub_type[bp] == 1 || mitm.sub_type[bp] == 2
                                                || mitm.sub_type[bp] == 3))
                mitm.special[bp] = 90;  // orcish

            if (random() % 6 == 0 && mitm.sub_type[bp] == 3)
                mitm.special[bp] = 150;         // dwarf

        }

        if (random() % 7 == 0 && mitm.sub_type[bp] >= 1
                                                && mitm.sub_type[bp] <= 3)
        {
            mitm.special[bp] = mitm.special[bp] % 30 + 1;
        }

        if (random() % 7 == 0 && mitm.sub_type[bp] >= 1
                                                && mitm.sub_type[bp] <= 3)
        {
            mitm.special[bp] = mitm.special[bp] % 30 + 2;
        }

        if ((random() % 5 == 0 || mitm.special[bp] == 90 && random() % 3 == 0)
                        && mitm.sub_type[bp] >= 1 && mitm.sub_type[bp] <= 3)
        {
            mitm.special[bp] = mitm.special[bp] % 30 + 3;
        }

        quant = random3(9) + random3(12) + random3(15) + random3(12) + 1;
        if (mitm.sub_type [bp] == MI_LARGE_ROCK) quant = 1 + random3(3) + random3(3);

        if (10 + many_many >= random3(100))
            mitm.pluses[bp] = random3(5);

        mitm.pluses[bp] += 50;
        break;

    case OBJ_ARMOUR:
        quant = 1;

        mitm.sub_type[bp] = random3(3);
        mitm.pluses[bp] = 0;
        mitm.pluses2[bp] = 0;
        if (random3(35) <= many_many + 10)
        {
            mitm.sub_type[bp] = random3(5);
            if (random3(4) == 0)
                mitm.sub_type[bp] = 30;         // animal skin

        }
        if (random3(60) <= many_many + 10)
            mitm.sub_type[bp] = random3(8);
        if (10 + many_many >= random3(400) && random3(10) == 0)
            mitm.sub_type[bp] = 15 + random3(7);
        if (10 + many_many >= random3(500) && random3(20) == 0)
        {
            mitm.sub_type[bp] = 22 + random3(11);
            if (mitm.sub_type[bp] == 30)
                mitm.sub_type[bp] = 17;         // replaces animal skin w/ crystal plate

        }
        if (random3(4) == 0)
            mitm.sub_type[bp] = 8 + random3(7);

        if (force_type != 250)
            mitm.sub_type[bp] = force_type;

        if (allow_uniques == 1 && random3(2000) <= 100 + many_many * 3 && random() % 2 == 0 && many_many > 2)
        {

            if (random3(50) == 0 && you.level_type != 2 && you.level_type != 3)
            {
                icky = find_okay_unrandart(OBJ_ARMOUR);
                if (icky != -1)
                {
                    quant = 1;
                    make_item_unrandart(icky, bp);
                    break;
                }
            }

            if (mitm.sub_type[bp] == 15)
                mitm.sub_type[bp] = 18;         /* No troll hides etc */
            if (mitm.sub_type[bp] == 16)
                mitm.sub_type[bp] = 19;
            if (mitm.sub_type[bp] == 20)
                mitm.sub_type[bp] = 21;
            if (mitm.sub_type[bp] == 24)
                mitm.sub_type[bp] = 25;
            if (mitm.sub_type[bp] == 26)
                mitm.sub_type[bp] = 27;
            if (mitm.sub_type[bp] == 28)
                mitm.sub_type[bp] = 29;
            if (mitm.sub_type[bp] == 31)
                mitm.sub_type[bp] = 32;
            mitm.special[bp] = 26 + random3(4);
            mitm.pluses[bp] = 50;
            mitm.pluses2[bp] = random3(150);
            if (mitm.sub_type[bp] == 12)
            {
                mitm.pluses2[bp] = 0;
                if (random3(6) == 0)
                    mitm.pluses2[bp] += random3(3);
            }
            if (mitm.sub_type[bp] == 10)
            {
                mitm.pluses2[bp] = 0;
                if (random3(3) == 0)
                    mitm.pluses2[bp] += random3(4);
            }
            mitm.pluses[bp] += random3(4);
            if (random3(5) == 0)
                mitm.pluses[bp] += random3(4);
            if (random3(6) == 0)
                mitm.pluses[bp] -= random3(8);
            quant = 1;
            if (random3(5) == 0)
            {
                mitm.pluses[bp] = 150 - random3(6);
            }
            else if (random3(3) != 0 && mitm.pluses[bp] < 50)
                mitm.pluses[bp] += 100;         /* cursed! nasty */
            break;
        }

        mitm.pluses[bp] = 0;

        if (mitm.sub_type[bp] == 10 && random3(2) == 0)
        {
            mitm.pluses2[bp] = random3(4);
        }


// 180 - orc, 150 - dwar, 120 - elf

        if (force_spec == 250 && random() % 2 == 0)
        {
            switch (mitm.sub_type[bp])
            {
            case 8:             // shield - must do special things for this!

            case 13:
                if (random() % 4 == 0)
                    mitm.special[bp] = 150;
            case 14:
                if (random() % 3 == 0)
                    mitm.special[bp] = 180;
                break;
            case 9:             // cloak

                if (random() % 4 == 0)
                    mitm.special[bp] = 180;
                if (random() % 4 == 0)
                    mitm.special[bp] = 150;
                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                break;
                // no helmet, for various reasons
            case 11:            // gloves

                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                break;
            case 12:            // boots

                if (random() % 4 == 0)
                {
                    mitm.pluses2[bp] = 1;
                    break;      /* naga barding */
                }
                if (random() % 4 == 0)
                {
                    mitm.pluses2[bp] = 2;
                    break;      /* naga barding */
                }
                if (random() % 4 == 0)
                    mitm.special[bp] = 180;
                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                if (random() % 6 == 0)
                    mitm.special[bp] = 150;
                break;
            case 0:             // robe:

                if (random() % 4 == 0)
                    mitm.special[bp] = 120;
                break;
            default:            // other body armours:

                if (mitm.sub_type[bp] <= 4 && random() % 6 == 0)
                    mitm.special[bp] = 120;
                if (mitm.sub_type[bp] >= 2 && random() % 5 == 0)
                    mitm.special[bp] = 150;
                if (random() % 5 == 0)
                    mitm.special[bp] = 180;
                break;
            }

        }


        switch (force_spec)
        {
        case 1:         // elf

            mitm.special[bp] = 120;
            break;

        case 2:         // dwarf

            mitm.special[bp] = 150;
            mitm.pluses[bp] += random() % 2;
            break;

        case 3:         // orc

            mitm.special[bp] = 180;
            break;
        }




        {
            if (50 + many_many >= random3(250) || (mitm.sub_type[bp] == 10 && mitm.pluses2[bp] == 3))
            {
                mitm.pluses[bp] += random3(3);
                if (mitm.sub_type[bp] <= 7 && 20 + many_many >= random3(300))
                    mitm.pluses[bp] += random3(3);
                if (30 + many_many >= random3(350) && (mitm.special[bp] != 180 || mitm.sub_type[bp] <= 7))
                    switch (mitm.sub_type[bp])
                    {
                    case 8:     // shield - must do special things for this!

                    case 14:
                    case 13:
                        mitm.special[bp] += 13;
                        break;  // prot
                        //break;

                    case 9:     // cloak

                        if (mitm.special[bp] == 150)
                            break;
                        switch (random3(4))
                        {
                        case 0:
                            mitm.special[bp] += 12;
                            break;
                        case 1:
                            mitm.special[bp] += 4;
                            break;
                        case 2:
                            mitm.special[bp] += 6;
                            break;
                        case 3:
                            mitm.special[bp] += 18;
                            break;
                        }
                        break;
                    case 10:    // helmet

                        if (mitm.pluses2[bp] == 2 && random3(4) == 0)
                            mitm.special[bp] += 6;
                        else if (mitm.pluses2[bp] == 3 && random3(4) == 0)
                            mitm.special[bp] += 12;
                        else
                            switch (random3(3))
                            {
                            case 0:
                                mitm.special[bp] += 5;
                                break;
                            case 1:
                                mitm.special[bp] += 6;
                                break;
                            case 2:
                                mitm.special[bp] += 9;
                                break;
                            }
                        break;
                    case 11:    // gloves

                        switch (random3(2))
                        {
                        case 0:
                            mitm.special[bp] += 7;
                            break;
                        case 1:
                            mitm.special[bp] += 8;
                            break;
                        }
                        break;
                    case 12:    // boots

                        switch (random3(3))
                        {
                        case 0:
                            mitm.special[bp] += 1;
                            break;
                        case 1:
                            mitm.special[bp] += 11;
                            break;
                        case 2:
                            mitm.special[bp] += 14;
                            break;
                        }
                        break;
                    case 0:     // robe:

                        switch (random3(4))
                        {
                        case 0:
                            mitm.special[bp] += random3(2) + 2;
                            break;
                        case 1:
                            mitm.special[bp] += 12;
                            break;
                        case 2:
                            mitm.special[bp] += 15 + random3(2);
                            break;
                        case 3:
                            if (force_type != 250 || random() % 50 > many_many + 10 || mitm.special[bp] != 0)
                                break;
                            mitm.special[bp] += 17;     // archmagi
                            //mitm.pluses [bp] = 50;

                        }
                        break;

                    default:    // other body armours:

                        mitm.special[bp] += 2 + random3(2);
                        if (random3(9) == 0)
                            mitm.special[bp] = 16;      /* prot_life */
                        if (random3(5) == 0)
                            mitm.special[bp] = 12;      /* magic res */
                        if (random3(5) == 0)
                            mitm.special[bp] = 4;       /* res poison */
                        if (mitm.sub_type[bp] == 7 && random3(15) == 0)
                        {
                            mitm.special[bp] += 10;
                            mitm.pluses[bp] += 1 + random3(4);
                        }
                        break;
                    }


            }
            else if (random3(12) == 0)
            {
                mitm.pluses[bp] = 99 - random3(2);
                if (random3(5) == 0)
                    mitm.pluses[bp] -= random3(3);
                mitm.special[bp] = 0;   // heh heh heh

            }
        }

        if (mitm.special[bp] < 120 && (mitm.special[bp] != 0 || (mitm.pluses[bp] != 0 && random3(3) == 0)))
            mitm.special[bp] += random3(3) * 30;

        if (mitm.sub_type[bp] > 14)
            mitm.special[bp] = 0;       // sorry about that.

        mitm.pluses[bp] += 50;

        if (many_many == 351)   // make sure you don't get eg a troll hide from a scroll of acquirement

        {
            if (mitm.sub_type[bp] == 15)
                mitm.sub_type[bp] = 18;
            if (mitm.sub_type[bp] == 16)
                mitm.sub_type[bp] = 19;
            if (mitm.sub_type[bp] == 20)
                mitm.sub_type[bp] = 21;
            if (mitm.sub_type[bp] == 24)
                mitm.sub_type[bp] = 25;
            if (mitm.sub_type[bp] == 26)
                mitm.sub_type[bp] = 27;
            if (mitm.sub_type[bp] == 28)
                mitm.sub_type[bp] = 29;
            if (mitm.sub_type[bp] == 31)
                mitm.sub_type[bp] = 32;
        }

        if (mitm.sub_type[bp] >= 15 && mitm.sub_type[bp] <= 30)
            mitm.special[bp] = 0;
        /* skin armours + Crystal PM don't get special enchantments or species, but can be randarts */

        break;

    case OBJ_WANDS:
        mitm.sub_type[bp] = random3(20);
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        mitm.pluses[bp] = random3(6) + random3(6) + random3(6);
        if (mitm.sub_type[bp] < 2 || mitm.sub_type[bp] == 4 || mitm.sub_type[bp] == 18)
            mitm.pluses[bp] = random3(10) + random3(10) + random3(10);
        if (mitm.sub_type[bp] == 5)
            mitm.pluses[bp] = random3(4) + random3(4) + random3(4);     /* healing */
        quant = 1;
        break;

    case OBJ_FOOD:
        mitm.sub_type[bp] = random3(5);
        if (random3(2) == 0)
            mitm.sub_type[bp] = random3(2);
        if (random3(16) == 0)
            mitm.sub_type[bp] = random3(21);
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        quant = 1;
        if (random3(80) == 0)
            quant = random3(3) + 1;
        if (mitm.sub_type[bp] == 12 || mitm.sub_type[bp] == 15 || mitm.sub_type[bp] == 16)
            quant = random3(15) + 3;
        break;

    case 5:
        mitm.base_type[bp] = 8; // potions // This one not finished

        pot = 0;

        pot = random3(9);       // general type of potion;

        quant = 1;
        if (random3(18) == 0)
            quant += 1;
        if (random3(25) == 0)
            quant += 1;

        switch (pot)
        {
        case 0:
        case 1:
        case 2:
        case 8:
            // healing potions
            if (random3(3) == 0)
                mitm.sub_type[bp] = 1;  // wound heal

            else
                mitm.sub_type[bp] = 0;  // healing

            if (random3(20) == 0)
                mitm.sub_type[bp] = 22;         // cure mutation

            break;
        case 3:
        case 4:
            // enhancements
            if (random3(2) == 0)
                mitm.sub_type[bp] = 2;  // speed

            else
                mitm.sub_type[bp] = 3;  // might

            if (random3(10) == 0)
                mitm.sub_type[bp] = 21;         // berserk

            if (random3(5) == 0)
                mitm.sub_type[bp] = 12;         // invis

            if (random3(6) == 0)
                mitm.sub_type[bp] = 7;  // levitation - an enhancement?

            if (random3(30) == 0)
                mitm.sub_type[bp] = 13;         // oatmeal

            break;

        case 5:
            // gain ability
            mitm.sub_type[bp] = 4 + random3(3);         // str/dex/int

            if (random3(10) == 0)
                mitm.sub_type[bp] = 17;
            if (random3(10) == 0)
                mitm.sub_type[bp] = 18;
            if (random3(8) != 0)
                mitm.sub_type[bp] = 19;         // restore abilities

            quant = 1;
            break;

        case 6:
        case 7:
            // bad things
            switch (random3(6))
            {
            case 4:
            case 0:
                if (many_many > 0)
                {
                    mitm.sub_type[bp] = 8;      // poison

                    if (many_many > 10 && random3(4) == 0)
                        mitm.sub_type[bp] = 20;         //str poison

                    break;
                }               // otherwise it just falls through

            case 1:
                mitm.sub_type[bp] = 9;
                break;          // slow

            case 2:
                mitm.sub_type[bp] = 10;
                break;          // para

            case 5:
                if (many_many > 6)
                {
                    mitm.sub_type[bp] = 23;
                    break;      // mutation

                }
            case 3:
                mitm.sub_type[bp] = 11;
                break;          // confus

            }
            if (random3(8) == 0)
                mitm.sub_type[bp] = 14;         // disease

            if (random3(1000) == 0)
                mitm.sub_type[bp] = 15;         // decay! nasty...

            break;

        }

        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        mitm.pluses[bp] = 0;
        break;

    case OBJ_SCROLLS:           // mitm.base_type [bp] = 15; // scrolls

        mitm.sub_type[bp] = random3(23);
        if (random3(6) == 0)
            mitm.sub_type[bp] = 0;      // identify should be very common

        if (random3(10) == 0)
            mitm.sub_type[bp] = 4;      // so should remove curse

        if (many_many < 4 && mitm.sub_type[bp] == 13)
            mitm.sub_type[bp] = 1;
        // having a level 1 character finding a scroll of immolation would be a bit unfair.
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        quant = 1;
        if (random3(16) == 0)
            quant = random3(3) + 1;
        if (mitm.sub_type[bp] == 20 || mitm.sub_type[bp] == 18 || mitm.sub_type[bp] == 9)
            quant = 1;
        if (mitm.sub_type[bp] == 6 && (random3(many_many + 1) < 4 || random3(2) != 0))
            mitm.sub_type[bp] = 5;
        if (mitm.sub_type[bp] == 9 && (random3(many_many + 1) < 7 || random3(2) != 0))
            mitm.sub_type[bp] = 5;
        if (mitm.sub_type[bp] == 20 && (random3(many_many + 1) < 7 || random3(2) != 0))
            mitm.sub_type[bp] = 1;
        if (mitm.sub_type[bp] == 18 && (random3(many_many + 1) < 4 || random3(2) != 0))
            mitm.sub_type[bp] = 1;
        if (mitm.sub_type[bp] == 22 && (random3(many_many + 1) < 4 || random3(2) != 0))
            mitm.sub_type[bp] = 1;
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        mitm.pluses[bp] = 0;
        break;

    case OBJ_JEWELLERY: // rings

        if (random3(2000) <= 100 + many_many * 3 && random() % 4 == 0
                && many_many > 2 && you.level_type != 2 && you.level_type != 3)
        {
            icky = find_okay_unrandart(OBJ_JEWELLERY);
            if (icky != -1)
            {
                quant = 1;
                make_item_unrandart(icky, bp);
                break;
            }
        }

        mitm.sub_type[bp] = random3(24);
        if (random() % 4 == 0)
            mitm.sub_type[bp] = 35 + random() % 10;
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        quant = 1;
        mitm.pluses[bp] = 50;
        if (mitm.sub_type[bp] == 1 || mitm.sub_type[bp] == 5 || mitm.sub_type[bp] == 6 || mitm.sub_type[bp] == 11 || mitm.sub_type[bp] == 14 || mitm.sub_type[bp] == 15)
        {
            mitm.pluses[bp] = 50;
            mitm.pluses[bp] += random3(3) + 1;
            if (random3(3) == 0)
                mitm.pluses[bp] += random3(4);

            if (random3(5) == 0)
            {
                mitm.pluses[bp] = 150;
                mitm.pluses[bp] -= random3(2) + 1;
                if (random3(3) == 0)
                    mitm.pluses[bp] -= random3(4);
            }

            if (mitm.sub_type[bp] == 6)         /* =oslaying */
            {
                mitm.pluses2[bp] = 50;
                mitm.pluses2[bp] += random3(3) + 1;
                if (random3(3) == 0)
                    mitm.pluses2[bp] += random3(4);
                if (random3(5) == 0)
                {
                    mitm.pluses[bp] = 50;
                    mitm.pluses2[bp] += 2;
                }
                else
                {
                    if (random3(5) == 0)
                    {
                        mitm.pluses[bp] = 50;
                        mitm.pluses2[bp] += 2;
                    }
                }
            }

        }
        if (allow_uniques == 1 && random3(2000) <= 100 + many_many * 3 && random() % 2 == 0 && many_many > 2)
        {
            if (mitm.sub_type[bp] == 1)
                mitm.sub_type[bp] = 2 + random3(3);
            if (mitm.sub_type[bp] == 5 || mitm.sub_type[bp] == 6)
                mitm.sub_type[bp] = 7 + random3(4);
            if (mitm.sub_type[bp] == 11)
                mitm.sub_type[bp] = 12;
            if (mitm.sub_type[bp] == 14 || mitm.sub_type[bp] == 15)
                mitm.sub_type[bp] = 16 + random3(8);
            if (mitm.sub_type[bp] == 43)
                mitm.sub_type[bp] = 35 + random3(8);
            /* Can't allow base ring types with +s */
            mitm.special[bp] = 200;
            mitm.pluses[bp] = random3(70);
            mitm.pluses2[bp] = random3(150);
            quant = 1;
            break;
        }
        switch (mitm.sub_type[bp])
        {
        case 9:
        case 10:
            mitm.pluses[bp] = 150;
            break;
        }
        break;

    case OBJ_BOOKS:
create_book:
        do
        {
            mitm.sub_type[bp] = random3(44);
            if (book_rarity(mitm.sub_type[bp]) == 100)
                continue;

            if (mitm.sub_type[bp] != BOOK_DESTRUCTION
                                        && mitm.sub_type[bp] != BOOK_MANUAL)
            {
                if (random3(10) == 0)
                {
                    if (random3(2) == 0)
                        mitm.sub_type[bp] = BOOK_WIZARDRY;
                    else
                        mitm.sub_type[bp] = BOOK_POWER;
                }

                if (random3(many_many + 1) + 1 >= book_rarity(mitm.sub_type[bp])
                                                    || random3(100) == 0)
                {
                    break;
                }
                else
                {
                    mitm.sub_type[bp] = BOOK_DESTRUCTION;
                    continue;
                }
            }
        }
        while (mitm.sub_type[bp] == BOOK_DESTRUCTION
                                        || mitm.sub_type[bp] == BOOK_MANUAL);

        if (book_rarity(mitm.sub_type[bp]) == 100)
            goto create_book;

        mitm.pluses[bp] = 127;
        itoa(127, strungy, 2);

        if (force_type != 250)
            mitm.sub_type[bp] = force_type;

        // shouldn't let spell no 1 be erased

        spellbook_template(mitm.sub_type[bp], fpass);

        for (bkk = 1; bkk < 7; bkk++)
        {
            if (fpass[bkk] == 210)
                strungy[bkk] = '0';
        }

        icky = strlen(strungy);

        multip = 1;
        numbo = 0;

        for (xj = icky; xj >= 1; xj--)
        {
            if (strungy[xj] != '1' && strungy[xj] != '0')
                continue;

            if (strungy[xj] == '0')
            {
                multip *= 2;
                continue;

            }

            if (strungy[xj] == '1')
            {
                numbo += multip;
                multip *= 2;
            }
        }
        strcpy(strungy, "");

        mitm.pluses[bp] = numbo + 64;

        mitm.special[bp] = random3(5);
        if (random3(10) == 0)
            mitm.special[bp] += random3(8) * 10;

        quant = 1;

        // tome of destruction : rare!
        if (force_type == BOOK_DESTRUCTION
                || (random() % 7000 <= many_many + 20 && many_many > 10
                                                    && force_type == 250))
        {
            mitm.sub_type[bp] = BOOK_DESTRUCTION;
        }

        // skill manuals - also rare
        if (force_type == BOOK_MANUAL
                || (random() % 4000 <= many_many + 20 && many_many > 6
                                                    && force_type == 250))
        {
            mitm.sub_type[bp] = BOOK_MANUAL;
            mitm.pluses[bp] = random3(19);
            if (random3(4) == 0)
                mitm.pluses[bp] = 25 + random3(12);
        }
        break;

    case OBJ_STAVES:
        mitm.sub_type[bp] = random3(10);
        if (random3(5) == 0)
            mitm.sub_type[bp] = 10 + random3(9);
        if (random3(15) == 0)
            mitm.sub_type[bp] = 25 + random3(3);

        if (mitm.sub_type[bp] >= 12 && mitm.sub_type[bp] <= 15 && random3(3) == 0)
            mitm.sub_type[bp] = random3(6);
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;
        mitm.special[bp] = random3(9);
        if (mitm.sub_type[bp] >= 10)
        {
            mitm.pluses[bp] = 127;
            if (force_type != 250)
                mitm.sub_type[bp] = force_type;

            itoa(127, strungy, 2);
            if (force_type != 250)
                mitm.sub_type[bp] = force_type;

            spellbook_template(mitm.sub_type[bp] + 40, fpass);

            for (bkk = 1; bkk < 7; bkk++)
            {
                if (fpass[bkk] == 210)
                    strungy[bkk] = '0';
            }

            icky = strlen(strungy);

            multip = 1;
            numbo = 0;

            for (xj = icky; xj >= 1; xj--)
            {
                if (strungy[xj] != '1' && strungy[xj] != '0')
                    continue;
                if (strungy[xj] == '0')
                {
                    multip *= 2;
                    continue;

                }

                if (strungy[xj] == '1')
                {
                    numbo += multip;
                    multip *= 2;
                }
            }
            strcpy(strungy, "");

            mitm.pluses[bp] = numbo + 64;
        }
        quant = 1;
        break;

    case OBJ_ORBS:
        if (force_type != 250)
            mitm.sub_type[bp] = force_type;

        quant = 1;

        if (mitm.sub_type[bp] >= 4 && mitm.sub_type[bp] <= 19)
            you.unique_items[mitm.sub_type[bp] + 3] = 1;
        break;

    case OBJ_MISCELLANY:
        mitm.sub_type[bp] = random3(6);

        if (random3(6) == 0)
            mitm.sub_type[bp] = MISC_BOX_OF_BEASTS + random3(10);

        if (mitm.sub_type[bp] == MISC_RUNE_OF_ZOT)
            mitm.sub_type[bp] = MISC_CRYSTAL_BALL_OF_FIXATION;

        if (mitm.sub_type[bp] == MISC_DECK_OF_POWER)
            if (random3(4) == 0)
                mitm.sub_type[bp] = MISC_DECK_OF_POWER;
            else
                mitm.sub_type[bp] = MISC_DECK_OF_TRICKS;

        if (random3(20) == 0)
            mitm.sub_type[bp] = MISC_DECK_OF_SUMMONINGS;

        if (force_type != 250)
            mitm.sub_type[bp] = force_type;

        if (mitm.sub_type[bp] == MISC_DECK_OF_WONDERS
                        || mitm.sub_type[bp] == MISC_DECK_OF_SUMMONINGS
                        || mitm.sub_type[bp] == MISC_DECK_OF_POWER)
            mitm.pluses[bp] = 4 + random3(10);

        if (mitm.sub_type[bp] == MISC_DECK_OF_TRICKS)
            mitm.pluses[bp] = 6 + random3(8) + random3(8);

        if (mitm.sub_type[bp] == MISC_RUNE_OF_ZOT)
        {
            mitm.pluses[bp] = you.where_are_you;
            if (you.level_type == 3)
                mitm.pluses[bp] = 50;   // pandem

            if (you.level_type == 2)
                mitm.pluses[bp] = 51;   // abyss

        }
        quant = 1;
        break;

    default:                    // money - class = 15
        mitm.base_type[bp] = 15;
        quant = random3(10) + random3(10) + 1 + random3(many_many);     // + random3(many_many) + random3(many_many);

        break;
    }

    mitm.quantity[bp] = quant;

    if (force_place == 1)
    {
        mitm.x[bp] = 1;
        mitm.y[bp] = 1;

    }
    else
    {
        do
        {
            mitm.x[bp] = random3(80);
            mitm.y[bp] = random3(70);
        }
        while (grd[mitm.x[bp]][mitm.y[bp]] != 67);
    }

    item_colour(bp);

    return bp;
}                               // end of void items()


void special_room()
{
    char spec_room_type;

    int thing_created = 0;

    int glopop = 0;

    char depth_max = 1;

    depth_max = 3;
    int mons_alloc[20];

    char lordx = 0;
    char lordy = 0;

    room_x1 = random3(55) + 8;
    room_y1 = random3(45) + 8;
    room_x2 = room_x1 + random3(4) + 6;
    room_y2 = room_y1 + random3(4) + 6;


    for (bcount_x = room_x1; bcount_x < room_x2; bcount_x++)
    {
        for (bcount_y = room_y1; bcount_y < room_y2; bcount_y++)
        {
            grd[bcount_x][bcount_y] = 105;
        }
    }

    x1 = room_x1 + 1;
    x2 = room_x2 - 1;
    y1 = room_y1 + 1;
    y2 = room_y2 - 1;


    for (bcount_x = x1; bcount_x < x2; bcount_x++)
    {
        for (bcount_y = y1; bcount_y < y2; bcount_y++)
        {
            grd[bcount_x][bcount_y] = 117;
        }
    }


/* placing monsters in special room: */

    bno_mons = 0;

    for (bk = 0; bk < MNST; bk++)
    {
        if (menv[bk].type != -1)
            bno_mons++;
    }


    spec_room_type = random3(4);

    if (many_many < 23 && random3(4) == 0)
        spec_room_type = 3;
    if (many_many < 17 && random3(4) == 0)
        spec_room_type = 0;
    if (many_many > 17 && spec_room_type == 1)
        spec_room_type = 0;
    if (many_many < 7)
        spec_room_type = 1;

    switch (spec_room_type)
    {

    case 0:                     // orc lair

        for (bcount_x = x1; bcount_x < x2; bcount_x++)
        {
            for (bcount_y = y1; bcount_y < y2; bcount_y++)
            {
                if (bno_mons > 80)
                    return;

                if (random3(4) == 0)
                    continue;

                for (bk = 0; bk < 85; bk++)
                {
                    if (menv[bk].type == -1)
                        break;
                }

                lev_mons = 3;
                if (many_many < 10)
                    lev_mons = 0;
                if (many_many > 9 && many_many < 16)
                    lev_mons = 1;
                if (many_many > 15 && many_many < 25)
                    lev_mons = 2;
                if (many_many > 24)
                    lev_mons = 3;

                switch (lev_mons)
                {
                case 0:
                    mons_alloc[0] = 14;
                    mons_alloc[1] = 14;
                    mons_alloc[2] = 14;
                    mons_alloc[3] = 14;
                    mons_alloc[4] = 14;
                    mons_alloc[5] = 14;
                    mons_alloc[6] = 14;
                    mons_alloc[7] = 14;
                    mons_alloc[8] = 14;
                    mons_alloc[9] = 52;
                    break;

                case 1:
                    mons_alloc[0] = 14;
                    mons_alloc[1] = 14;
                    mons_alloc[2] = 14;
                    mons_alloc[3] = 14;
                    mons_alloc[4] = 14;
                    mons_alloc[5] = 14;
                    mons_alloc[6] = 14;
                    mons_alloc[7] = 14;
                    mons_alloc[8] = 52;
                    mons_alloc[9] = 52;
                    break;

                case 2:
                    mons_alloc[0] = 14;
                    mons_alloc[1] = 14;
                    mons_alloc[2] = 14;
                    mons_alloc[3] = 14;
                    mons_alloc[4] = 14;
                    mons_alloc[5] = 14;
                    mons_alloc[6] = 55;
                    mons_alloc[7] = 52;
                    mons_alloc[8] = 52;
                    mons_alloc[9] = 40;
                    break;

                case 3:
                    mons_alloc[0] = 14;
                    mons_alloc[1] = 14;
                    mons_alloc[2] = 52;
                    mons_alloc[3] = 52;
                    mons_alloc[4] = 55;
                    mons_alloc[5] = 55;
                    mons_alloc[6] = 52;
                    mons_alloc[7] = 40;
                    mons_alloc[8] = 40;
                    mons_alloc[9] = 45;
                    break;

                }               // end of switch (many_many)


                menv[bk].type = mons_alloc[random3(10)];
                define_monster(bk, menv);

                menv[bk].x = bcount_x;
                menv[bk].y = bcount_y;

                bno_mons++;

                give_item();

                if (menv[bk].type == 30)
                    give_item();

            }
        }
        break;




    case 1:                     // kobold lair

        lordx = x1 + random3(x2 - x1);
        lordy = y1 + random3(y2 - y1);

        for (bcount_x = x1; bcount_x < x2; bcount_x++)
        {
            for (bcount_y = y1; bcount_y < y2; bcount_y++)
            {
                if (bno_mons > 80)
                    return;

                if (random3(4) == 0)
                    continue;

                for (bk = 0; bk < 85; bk++)
                {
                    if (menv[bk].type == -1)
                        break;
                }

                lev_mons = 3;
                if (many_many < 4)
                    lev_mons = 0;
                if (many_many > 3 && many_many < 6)
                    lev_mons = 1;
                if (many_many > 5 && many_many < 9)
                    lev_mons = 2;
                if (many_many > 8 && many_many < 10)
                    lev_mons = 3;

                switch (lev_mons)
                {
                case 0:
                    mons_alloc[0] = 36;
                    mons_alloc[1] = 36;
                    mons_alloc[2] = 36;
                    mons_alloc[3] = 36;
                    mons_alloc[4] = 36;
                    mons_alloc[5] = 36;
                    mons_alloc[6] = 36;
                    mons_alloc[7] = 36;
                    mons_alloc[8] = 58;
                    mons_alloc[9] = 58;
                    break;

                case 1:
                    mons_alloc[0] = 36;
                    mons_alloc[1] = 36;
                    mons_alloc[2] = 36;
                    mons_alloc[3] = 36;
                    mons_alloc[4] = 36;
                    mons_alloc[5] = 36;
                    mons_alloc[6] = 58;
                    mons_alloc[7] = 58;
                    mons_alloc[8] = 58;
                    mons_alloc[9] = 58;
                    break;

                case 2:
                    mons_alloc[0] = 36;
                    mons_alloc[1] = 36;
                    mons_alloc[2] = 36;
                    mons_alloc[3] = 36;
                    mons_alloc[4] = 36;
                    mons_alloc[5] = 58;
                    mons_alloc[6] = 58;
                    mons_alloc[7] = 58;
                    mons_alloc[8] = 58;
                    mons_alloc[9] = 58;
                    break;

                case 3:
                    mons_alloc[0] = 36;
                    mons_alloc[1] = 36;
                    mons_alloc[2] = 36;
                    mons_alloc[3] = 36;
                    mons_alloc[4] = 58;
                    mons_alloc[5] = 58;
                    mons_alloc[6] = 58;
                    mons_alloc[7] = 58;
                    mons_alloc[8] = 58;
                    mons_alloc[9] = 58;
                    break;

                }               // end of switch (many_many)

                menv[bk].type = mons_alloc[random3(10)];

                if (bcount_x == lordx && bcount_y == lordy)     // && many_many < 7

                {
                    menv[bk].type = 58;
                }

                define_monster(bk, menv);

                menv[bk].x = bcount_x;
                menv[bk].y = bcount_y;

                bno_mons++;

//              if (gmon_use [menv [bk].type] > 0)
                give_item();

                if (menv[bk].type == 30)
                    give_item();


            }
        }
        break;


// Maybe have several types of treasure room?
    case 2:                     // Treasure room! should only appear in deep levels, with a guardian


        for (bcount_x = x1; bcount_x < x2; bcount_x++)
        {
            for (bcount_y = y1; bcount_y < y2; bcount_y++)
            {

                switch (random3(11))
                {
                case 9:
                case 0:
                    glopop = 0;
                    break;
                case 1:
                    glopop = 1;
                    break;
                case 10:
                case 2:
                    glopop = 2;
                    break;
                case 3:
                    glopop = 3;
                    break;
                case 4:
                    glopop = 5;
                    break;
                case 5:
                    glopop = 6;
                    break;
                case 6:
                    glopop = 7;
                    break;
                case 7:
                    glopop = 10;
                    break;
                case 8:
                    glopop = 11;
                    break;
                }


                thing_created = items(1, glopop, 250, 1, many_many * 3, 250);

                mitm.x[thing_created] = bcount_x;
                mitm.y[thing_created] = bcount_y;



            }

        }



        // guardian

        for (bk = 0; bk < MNST; bk++)
        {
            if (menv[bk].type == -1)
                break;
            if (bk == MNST - 3)
                return;         // surely this couldn't happen?!

        }

        menv[bk].type = 39;
        define_monster(bk, menv);

        menv[bk].x = x1;
        menv[bk].y = y1;

        bno_mons++;

        break;                  // end of case 2




    case 3:                     // beehive

        beehive();

        break;                  // end of beehive (case 3)

    }                           // end of switch room_type



}




void beehive(void)
{
    long quant;                 // these odd things are to avoid warnings

    for (bcount_x = x1; bcount_x < x2; bcount_x++)
    {
        for (bcount_y = y1; bcount_y < y2; bcount_y++)
        {

//                      if (no_it > 200) return;

            if (random3(2) == 0)
                continue;

            for (bp = 0; bp < 210; bp++)
            {
                if (bp == 200)
                    goto finished_it;
                if (mitm.base_type[bp] == 100)
                    break;
            }

            mitm.base_type[bp] = 4;

            mitm.sub_type[bp] = 5;
            if (random3(25) == 0)
                mitm.sub_type[bp] = 6;  // royal jelly

            quant = 1;

            mitm.quantity[bp] = quant;

            mitm.x[bp] = bcount_x;
            mitm.y[bp] = bcount_y;

            item_colour(bp);

//                      no_it++;

        }
    }


finished_it:
    char queen = 1;

    for (bcount_x = x1; bcount_x < x2; bcount_x++)
    {
        for (bcount_y = y1; bcount_y < y2; bcount_y++)
        {
            if (bno_mons > 100)
                return;

            if (grd[bcount_x][bcount_y] != 67 && grd[bcount_x][bcount_y] != 117)
                continue;       // shouldn't need this, but oh well.
            // 117 for "special rooms"

            for (bk = 0; bk < 85; bk++)
            {
                if (menv[bk].type == -1)
                    break;
            }

            switch (random3(6))
            {
            case 0:
                menv[bk].type = 11;
                break;

            case 5:
                if (queen == 1)
                {
                    menv[bk].type = 42;
                    queen = 0;
                    break;
                }               // otherwise fall through


            case 1:
            case 2:
            case 3:
            case 4:
                menv[bk].type = 10;
                break;
            }

            if (queen == 1 && bcount_x == x2 - 1 && bcount_y == y2 - 1)
            {
                menv[bk].type = 42;
            }

            define_monster(bk, menv);

            menv[bk].x = bcount_x;
            menv[bk].y = bcount_y;

            mgrd[menv[bk].x][menv[bk].y] = bk;
            bno_mons++;

            menv[bk].behavior = 100;    // should be sleeping

        }

    }

}                               // end of void beehive()










void morgue(void)
{

    for (bcount_x = x1; bcount_x < x2; bcount_x++)
    {
        for (bcount_y = y1; bcount_y < y2; bcount_y++)
        {
            if (bno_mons > 100)
                return;

            if (grd[bcount_x][bcount_y] != 67 && grd[bcount_x][bcount_y] != 117)
                continue;       // shouldn't need this, but oh well.
            // 117 for "special rooms"


            for (bk = 0; bk < 85; bk++)
            {
                if (menv[bk].type == -1)
                    break;
            }

            switch (random3(6))
            {

            case 0:
            case 1:
            case 2:
//                      case 3:
                menv[bk].type = 25;
                define_zombie(3, 250, 250);
                //menv [bk].number = random3(2);
                break;

            case 3:
                menv[bk].type = 60;
                define_monster(bk, menv);
                break;


            case 4:
                menv[bk].type = 13;
                define_monster(bk, menv);
                break;

            case 5:
                menv[bk].type = 48;
                if (random3(4) == 0)
                    menv[bk].type = 47;
                define_monster(bk, menv);
                break;

            }

            menv[bk].x = bcount_x;
            menv[bk].y = bcount_y;

            mgrd[menv[bk].x][menv[bk].y] = bk;

            bno_mons++;

            menv[bk].behavior = 100;    // should be sleeping

        }

    }

}                               // end of void morgue()



void define_zombie(char not_zombsize,   /* 1=2, 2=1, 3=1 or 2 */
                   int ztype,
                   int cs)
{
    int mons_sec2 = 0;

    if (ztype == 250)
    {
        do
        {
            menv[bk].number = random3(80);
        }
        while (mons_zombie_size(menv[bk].number) == 0 || mons_zombie_size(menv[bk].number) == not_zombsize || (cs > 100 && mons_skeleton(menv[bk].number) == 0));

        mons_sec2 = menv[bk].number;
    }
    else
    {
        mons_sec2 = ztype;
        menv[bk].number = ztype;
    }

    menv[bk].number = mons_charclass(menv[bk].number);

    menv[bk].type = menv[bk].number;
    define_monster(bk, menv);



    menv[bk].hit_points = hit_points(menv[bk].hit_dice, 6, 5);
    menv[bk].max_hit_points = menv[bk].hit_points;
    menv[bk].armor_class -= 2;
    if (menv[bk].armor_class < 0)
        menv[bk].armor_class = 0;
    menv[bk].evasion -= 5;
    if (menv[bk].evasion < 0)
        menv[bk].evasion = 0;
    menv[bk].speed -= 2;
    if (menv[bk].speed < 3)
        menv[bk].speed = 3;
    menv[bk].speed_increment = 70;

    menv[bk].number = mons_sec2;

    menv[bk].type = 25;

    if (mons_zombie_size((int) menv[bk].number) == 2)
    {
        menv[bk].type = 51;
//              menv [bk].speed = 6;
    }

    if (cs > 100 && cs != 367)
    {
        menv[bk].hit_points = hit_points(menv[bk].hit_dice, 5, 4);
        menv[bk].max_hit_points = menv[bk].hit_points;
        menv[bk].armor_class -= 4;
        if (menv[bk].armor_class < 0)
            menv[bk].armor_class = 0;
        menv[bk].evasion -= 2;
        if (menv[bk].evasion < 0)
            menv[bk].evasion = 0;
        menv[bk].type = 107;
        if (mons_zombie_size(menv[bk].number) == 2)
        {
            menv[bk].type = 108;
//              menv [bk].speed = 6;
        }
    }

    if (cs == 367)
    {
        menv[bk].type = 367;
        menv[bk].hit_points = hit_points(menv[bk].hit_dice, 4, 4);
        menv[bk].max_hit_points = menv[bk].hit_points;
        menv[bk].armor_class += 4;
        menv[bk].type = 367;
    }

    menv[bk].number = mons_sec2;

}




void specr_2(void)
{

    int bkout = 0;

grolko:
    if (bkout > 100)
        return;
    rd = random3(4);
    switch (rd)
    {
    case 0:
        cx = x1 + (random3(x2 - x1));
        cy = y1;
        dx = 0;
        dy = -1;
        break;
    case 1:
        cx = x1 + (random3(x2 - x1));
        cy = y2;
        dx = 0;
        dy = 1;
        break;
    case 2:
        cy = y1 + (random3(y2 - y1));
        cx = x1;
        dx = -1;
        dy = 0;
        break;
    case 3:
        cy = y1 + (random3(y2 - y1));
        cx = x2;
        dx = 1;
        dy = 0;
        break;
    }

    sx = cx;
    sy = cy;

    for (bcount_x = 0; bcount_x < 100; bcount_x++)
    {
        sx += dx;
        sy += dy;
        if (sx < 6 || sx > 73 || sy < 6 || sy > 63)
        {
            bkout++;
            goto grolko;
        }

        if (bcount_x > 0)
        {
            if (grd[sx + 1][sy] == 67)
                break;
            if (grd[sx][sy + 1] == 67)
                break;
            if (grd[sx - 1][sy] == 67)
                break;
            if (grd[sx][sy - 1] == 67)
                break;
        }

    }                           // end of for bcount_x

    sx = cx;
    sy = cy;

    for (bcount_y = 0; bcount_y < bcount_x + 2; bcount_y++)
    {
        if (grd[sx][sy] == 105)
            grd[sx][sy] = 3;    // door

        if (bcount_y > 0 && grd[sx + dx][sy + dy] > 1 && grd[sx + dx][sy + dy] < 67)
        {
            grd[sx][sy] = 89;
        }

        if (grd[sx][sy] == 1)
            grd[sx][sy] = 106;

        sx += dx;
        sy += dy;
    }


}                               // end of specr_2()








void give_item(void)
{

    int iquan = 1;
    int bp = 0;
    int thing_created = 0;
    char hand_used = 0;         // for Ettins etc.

    int xitc = 0;
    int xitt = 0;

    int force_item = 0;
    int force_spec = 250;
    int give_level = many_many;


    for (bp = 0; bp < ITEMS - 100; bp++)
    {
//              if (bp == 1) continue;
        if (mitm.quantity[bp] == 0 || mitm.quantity[bp] == 100)
            break;
    }

    if (bp >= ITEMS - 101)
        return;                 // already too many.

    mitm.quantity[bp] = 0;

    mitm.pluses[bp] = 50;
    mitm.pluses2[bp] = 50;
    mitm.special[bp] = 0;
    mitm.base_type[bp] = 101;
    mitm.x[bp] = 1;
    mitm.y[bp] = 1;

    if (menv[bk].type == 144 && you.where_are_you == 16 && random3(3) == 0)
        give_level = 351;

/* dancing weapon in the Hall of Blades */
    switch (menv[bk].type)
    {
    case MONS_KOBOLD:           // kobold
    case MONS_BIG_KOBOLD:
        if (random3(5) < 3)     // < 1) // give hand weapon
        {
            mitm.base_type[bp] = 0;
            mitm.colour[bp] = 11;
            switch (random3(5))
            {
            case 0:
                mitm.sub_type[bp] = WPN_CLUB;
                mitm.colour[bp] = 6;
                break;
            case 1:
            case 4:
                mitm.sub_type[bp] = WPN_DAGGER;
                break;

            case 2:
            case 3:
                mitm.sub_type[bp] = WPN_SHORT_SWORD;
                break;
            }
        }
        else if (random3(5) < 2)
        {
            force_spec = 100;
            mitm.base_type[bp] = 1;
            mitm.sub_type[bp] = 3;
            mitm.colour[bp] = 11;
            iquan = random3(5) + 1;
        }
        else
            goto give_armour;   //return;

        break;

    case MONS_HOBGOBLIN:        // hobgoblin
        if (random() % 3 == 0)
            force_spec = 3;

        if (random3(5) < 3)     // < 2 // give hand weapon
        {
            mitm.base_type[bp] = 0;
            mitm.sub_type[bp] = 0;
            mitm.colour[bp] = 6;
        }
        else
            goto give_armour;   //return;

        break;

    case MONS_GOBLIN:                     // goblin

        if (random() % 3 == 0)
            force_spec = 3;

    case MONS_JESSICA:                   // Jessica
    case MONS_IJYB:                   // Ijyb
        if (random3(5) < 3)     // < 1 // give hand weapon
        {
            mitm.base_type[bp] = 0;
            mitm.colour[bp] = 11;
            switch (random3(2))
            {
            case 0:
                mitm.sub_type[bp] = WPN_CLUB;
                mitm.colour[bp] = 6;
                break;
            case 1:
                mitm.sub_type[bp] = WPN_DAGGER;
                break;
            }
        }
        else
            goto give_armour;   //return;

        break;


    case MONS_WIGHT:                    // Wight
    case MONS_NORRIS:                   // Norris
        mitm.base_type[bp] = 0;
        mitm.colour[bp] = 11;
        if (random3(6) == 0)
            mitm.sub_type[bp] = WPN_AXE + random3(4);
        else
            mitm.sub_type[bp] = 1 + random3(12);

        if (random3(2) == 0)
        {
            mitm.pluses[bp] += random3(3) + 1;
            if (random3(10) == 0)
                mitm.special[bp] = 2;
        }

        if (random3(3) == 0)
            mitm.pluses[bp] += 100;

        break;

    case MONS_GNOLL:                   // gnoll
    case MONS_OGRE_MAGE:                   // ogre mage
    case MONS_NAGA_WARRIOR:                   // naga warrior
    case MONS_GREATER_NAGA:
    case MONS_EDMUND:                   // Edmund
    case MONS_DUANE:                   // Duane
        force_spec = 100;

        if (random3(5) < 4)
        {
            mitm.base_type[bp] = 0;
            mitm.colour[bp] = 11;

            switch (random3(5))
            {
            case 0:
                mitm.sub_type[bp] = WPN_FLAIL;
                break;
            case 1:
            case 2:
                mitm.sub_type[bp] = WPN_SPEAR;
                break;
            case 3:
                mitm.sub_type[bp] = WPN_HALBERD;
                break;
            case 4:
                mitm.sub_type[bp] = WPN_CLUB;
                break;
            }
        }
        break;

    case MONS_ORC:                    // orc
    case MONS_ORC_PRIEST:                   // orc priest
        force_spec = 3;

    case MONS_TERENCE:                   // Terence
        if (random3(5) < 4)
        {
            mitm.base_type[bp] = 0;
            mitm.colour[bp] = 11;
            switch (random3(8))
            {
            case 0:
                if (random3(10) == 0)
                    mitm.sub_type[bp] = WPN_SPIKED_FLAIL;
                else
                    mitm.sub_type[bp] = WPN_FLAIL;
                break;

            case 1:
                if (random3(3) == 0)
                    mitm.sub_type[bp] = WPN_MORNINGSTAR;
                else
                    mitm.sub_type[bp] = WPN_MACE;
                break;

            case 2:
                if (random3(3) == 0)
                    mitm.sub_type[bp] = WPN_SCIMITAR;
                else
                    mitm.sub_type[bp] = WPN_SHORT_SWORD;
                break;

            case 3:
                if (random3(5) == 0)
                    mitm.sub_type[bp] = WPN_AXE;
                else
                    mitm.sub_type[bp] = WPN_HAND_AXE;
                break;

            case 4:
                if (random3(3) == 0)
                    mitm.sub_type[bp] = WPN_TRIDENT;
                else
                    mitm.sub_type[bp] = WPN_HALBERD;
                break;

            case 5:
                mitm.sub_type[bp] = WPN_DAGGER;
                break;

            case 6:
                mitm.sub_type[bp] = WPN_CLUB;
                break;

            case 7:
                if (random3(3) == 0)
                    mitm.sub_type[bp] = WPN_WHIP;
                else
                    mitm.sub_type[bp] = WPN_HAMMER;
                break;


            }
        }
        else
            goto give_armour;   //return;

        break;


    case MONS_DEEP_ELF_SOLDIER:                  // deep elf soldier
    case MONS_DEEP_ELF_FIGHTER:                  // deep elf fighter
    case MONS_DEEP_ELF_KNIGHT:                   // deep elf knight
    case MONS_DEEP_ELF_PRIEST:                   // deep elf priest
    case MONS_DEEP_ELF_HIGH_PRIEST:              // deep elf high priest
        force_spec = 1;
        mitm.base_type[bp] = 0;
        switch (random3(8))
        {
        case 0:
            mitm.sub_type[bp] = WPN_BOW;
            break;
        case 1:
            mitm.sub_type[bp] = WPN_HAND_CROSSBOW;
            break;
        case 2:
        case 5:
            mitm.sub_type[bp] = WPN_SHORT_SWORD;
            break;
        case 3:
        case 4:
            mitm.sub_type[bp] = WPN_LONG_SWORD;
            break;
        case 6:
            mitm.sub_type[bp] = WPN_MACE;
            break;
        case 7:
            mitm.sub_type[bp] = WPN_SCIMITAR;
            break;
        }
        break;


    case MONS_DEEP_ELF_MAGE:                   // deep elf mage
    case MONS_DEEP_ELF_SUMMONER:               // deep elf summoner
    case MONS_DEEP_ELF_CONJURER:               // deep elf conjurer
    case MONS_DEEP_ELF_DEMONOLOGIST:           // deep elf demonologist
    case MONS_DEEP_ELF_ANNIHILATOR:            // deep elf annihilator
    case MONS_DEEP_ELF_SORCEROR:               // deep elf sorceror
    case MONS_DEEP_ELF_DEATH_MAGE:             // deep elf death mage
        force_spec = 1;
        mitm.base_type[bp] = 0;
        switch (random3(2))
        {
        case 0:
            mitm.sub_type[bp] = WPN_SABRE;
            break;
        case 1:
            mitm.sub_type[bp] = WPN_WHIP;
            break;
        case 2:
            mitm.sub_type[bp] = WPN_SHORT_SWORD;
            break;
        case 3:
        case 6:
            mitm.sub_type[bp] = WPN_LONG_SWORD;
            break;
        case 4:
        case 5:
            mitm.sub_type[bp] = WPN_DAGGER;
            break;
        }
        break;

    case MONS_ORC_WARRIOR:                    // orc warrior
    case MONS_ORC_HIGH_PRIEST:                // orc high priest
    case MONS_BLORK_THE_ORC:                  // Blork the orc
        if (force_spec == 250)
            force_spec = 3;

    case MONS_DANCING_WEAPON:   // note that give_level is adjusted above
    case MONS_MICHAEL:          // Michael
    case MONS_JOSEPH:           // Joseph
    case MONS_HAROLD:           // Harold
    case MONS_LOUISE:           // Louise
    case MONS_FRANCIS:          // Francis
    case MONS_FRANCES:          // Frances
    case MONS_RUPERT:           // Rupert
    case MONS_WAYNE:            // Wayne
    case MONS_NAGA:             // naga
    case MONS_NAGA_MAGE:        // naga mage
    case MONS_SKELETAL_WARRIOR: // skeletal warrior
        mitm.base_type[bp] = 0;
        mitm.colour[bp] = 11;
        switch (random3(12))
        {
        case 0:
            if (random3(10) == 0)
                mitm.sub_type[bp] = WPN_SPIKED_FLAIL;
            else
                mitm.sub_type[bp] = WPN_FLAIL;
            break;
        case 1:
            mitm.sub_type[bp] = WPN_MORNINGSTAR;
            break;
        case 2:
            mitm.sub_type[bp] = WPN_SCIMITAR;
            break;
        case 3:
            mitm.sub_type[bp] = WPN_HAND_AXE;
            break;
        case 4:
            mitm.sub_type[bp] = WPN_HALBERD;
            break;
        case 5:
            mitm.sub_type[bp] = WPN_SHORT_SWORD;
            break;
        case 6:
            mitm.sub_type[bp] = WPN_LONG_SWORD;
            break;
        case 7:
            mitm.sub_type[bp] = WPN_BATTLEAXE;
            break;
        case 8:
            mitm.sub_type[bp] = WPN_GLAIVE;
            break;
        case 9:
            if (random3(10) == 0)
                mitm.sub_type[bp] = WPN_BROAD_AXE;
            else
                mitm.sub_type[bp] = WPN_AXE;
            break;
        case 10:
            mitm.sub_type[bp] = WPN_GREAT_MACE;
            break;
        case 11:
            mitm.sub_type[bp] = WPN_TRIDENT;
            break;
        }
        break;

    case MONS_ORC_KNIGHT:       // orc knight
    case MONS_ORC_WARLORD:      // orc warlord
        force_spec = 3;

    case MONS_NORBERT:          // Norbert
    case MONS_JOZEF:            // Jozef
    case MONS_URUG:             // Urug
    case MONS_VAULT_GUARD:      // vault guard
    case MONS_VAMPIRE_KNIGHT:   // vampire knight
        mitm.base_type[bp] = 0;
        mitm.colour[bp] = LIGHTCYAN;
        switch (random3(6))
        {
        case 0:
            mitm.sub_type[bp] = WPN_LONG_SWORD;
            break;              // long sword

        case 1:
            mitm.sub_type[bp] = WPN_GREAT_SWORD;
            break;              // great sword

        case 2:
            mitm.sub_type[bp] = WPN_BATTLEAXE;
            break;              // battleaxe

        case 3:
            if (random3(2) == 0) mitm.sub_type[bp] = WPN_GREAT_MACE;
             else mitm.sub_type[bp] = WPN_GREAT_FLAIL;
            break;

        case 4:
            if (random3(2) == 0) mitm.sub_type[bp] = WPN_GLAIVE;
             else if (random3(2) == 0) mitm.sub_type[bp] = WPN_HALBERD;
              else mitm.sub_type[bp] = WPN_BROAD_AXE;
            break;

        case 5:
            mitm.sub_type[bp] = WPN_AXE;
            break;

        }

        if (random3(3) == 0)
            mitm.pluses[bp] += random3(4);

        break;

    case MONS_CYCLOPS:                    // Cyclops
    case MONS_STONE_GIANT:                // stone giant
        force_spec = 100;
        mitm.base_type[bp] = 1;
        mitm.sub_type[bp] = 5;
        mitm.colour[bp] = LIGHTGREY;
        iquan = random3(3) + 1;
        break;


    case MONS_TWO_HEADED_OGRE:            // two-headed Ogre
        force_spec = 100;
        hand_used = 0;

        if (menv[bk].inv[0] != 501)
            hand_used = 1;

        mitm.base_type[bp] = 0;
        mitm.colour[bp] = BROWN;
        mitm.sub_type[bp] = WPN_GIANT_CLUB; // giant club

        if (random3(3) == 0)
            mitm.sub_type[bp] = WPN_GIANT_SPIKED_CLUB;

        if (random3(10) == 0)
        {
            mitm.colour[bp] = LIGHTCYAN;

            if (random3(10) == 0)
                mitm.sub_type[bp] = WPN_GREAT_FLAIL;
            else
                mitm.sub_type[bp] = WPN_GREAT_MACE;
        }

        iquan = 1;
        break;

    case MONS_REAPER:                    // reaper devil
    case MONS_SIGMUND:                   // Sigmund
        force_spec = 100;
        mitm.base_type[bp] = OBJ_WEAPONS;
        mitm.sub_type[bp] = WPN_SCYTHE; // scythe

        mitm.colour[bp] = LIGHTCYAN;
        iquan = 1;
        break;

    case MONS_BALRUG:                   // Balrug
        force_spec = 100;
        mitm.base_type[bp] = OBJ_WEAPONS;
        mitm.sub_type[bp] = WPN_DEMON_WHIP; // demon whip
        iquan = 1;
        break;

    case MONS_RED_DEVIL:
        force_spec = 100;
        mitm.base_type[bp] = OBJ_WEAPONS;
        mitm.sub_type[bp] = WPN_DEMON_TRIDENT;
        mitm.colour[bp] = RED;
        iquan = 1;
        break;

    case MONS_OGRE:                    // Ogre
    case MONS_HILL_GIANT:                   // hill giant
    case MONS_EROLCHA:                   // Erolcha
        force_spec = 100;
        mitm.base_type[bp] = OBJ_WEAPONS;
        mitm.colour[bp] = BROWN;
        mitm.sub_type[bp] = WPN_GIANT_CLUB; // giant club

        if (random3(3) == 0)
            mitm.sub_type[bp] = WPN_GIANT_SPIKED_CLUB;

        if (random3(10) == 0)
        {
            mitm.colour[bp] = LIGHTCYAN;

            if (random3(10) == 0)
                mitm.sub_type[bp] = WPN_GREAT_FLAIL;
            else
                mitm.sub_type[bp] = WPN_GREAT_MACE;
        }

        iquan = 1;
        break;

    case MONS_CENTAUR_WARRIOR:
    case MONS_CENTAUR:                   // centaur
        force_spec = 100;
        mitm.base_type[bp] = OBJ_WEAPONS;
        mitm.sub_type[bp] = WPN_BOW;
        mitm.colour[bp] = BROWN;
        iquan = 1;
        break;

    case MONS_YAKTAUR_CAPTAIN:
    case MONS_YAKTAUR:                   // yaktaur
        force_spec = 100;
        mitm.base_type[bp] = OBJ_WEAPONS;
        mitm.sub_type[bp] = WPN_CROSSBOW;
        mitm.colour[bp] = BROWN;
        iquan = 1;
        break;

    case MONS_EFREET:                    // Efreet
    case MONS_ERICA:                     // Erica
        force_spec = 100;
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_SCIMITAR;
        mitm.special[bp] = 1;
        mitm.pluses[bp] = 50 + random3(5);
        mitm.pluses2[bp] = 50 + random3(5);
        mitm.colour[bp] = RED;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_ANGEL:                    // Angel
        mitm.base_type[bp] = 0;

        if (random3(3) == 0)
        {
            if (random3(3) == 0)
                mitm.sub_type[bp] = WPN_GREAT_MACE;
            else
                mitm.sub_type[bp] = WPN_MACE;

            mitm.special[bp] = 74;      /* glowing, disruption */
        }
        else
        {
            mitm.sub_type[bp] = WPN_LONG_SWORD;      /* longsword */
            mitm.special[bp] = 60;      /* glowing */
        }

        mitm.pluses[bp] = 51 + random3(3);
        mitm.pluses2[bp] = 51 + random3(3);

        mitm.colour[bp] = WHITE;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_DAEVA:                   // Daeva
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_LONG_SWORD;
        if (random3(4) == 0) mitm.sub_type[bp] = WPN_GREAT_SWORD;
        mitm.special[bp] = 63;  /* glowing, holy wrath */
        mitm.pluses[bp] = 51 + random3(3);
        mitm.pluses2[bp] = 51 + random3(3);
        mitm.colour[bp] = WHITE;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_HELL_KNIGHT:               // hell knight
    case MONS_MAUD:                      // Maud
    case MONS_ADOLF:                     // Adolf
    case MONS_MARGERY:                   // Margery
        mitm.base_type[bp] = 0;

        // longsword, great sword, scimitar
        mitm.sub_type[bp] = WPN_LONG_SWORD + random3(3);

        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_HALBERD;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_GLAIVE;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_GREAT_MACE;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_BATTLEAXE;
            if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_AXE;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_BROAD_AXE;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_DEMON_TRIDENT;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_DEMON_BLADE;
        if (random3(7) == 0)
            mitm.sub_type[bp] = WPN_DEMON_WHIP;

        mitm.special[bp] = 30 * random3(3);
        if (random3(5) == 0)
            mitm.special[bp] += 1;
        if (random3(5) == 0)
            mitm.special[bp] += 8;
        if (random3(5) == 0)
            mitm.special[bp] += 10;

        mitm.pluses[bp] += random3(6);
        mitm.pluses2[bp] = 50 + random3(6);

        mitm.colour[bp] = RED;
        if (random3(3) == 0)
            mitm.colour[bp] = DARKGREY;
        if (random3(5) == 0)
            mitm.colour[bp] = CYAN;

        iquan = 1;
        force_item = 1;
        break;

    case MONS_FIRE_GIANT:                   // Fire giant
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_GREAT_SWORD;
        mitm.special[bp] = 1;
        mitm.pluses[bp] = 50;
        mitm.pluses2[bp] = 50;
        mitm.colour[bp] = RED;
        if (random3(3) == 0)
            mitm.colour[bp] = DARKGREY;
        if (random3(5) == 0)
            mitm.colour[bp] = CYAN;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_FROST_GIANT:                  // Frost giant
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_BATTLEAXE;
        mitm.special[bp] = 2;
        mitm.pluses[bp] = 50;
        mitm.pluses2[bp] = 50;
        mitm.colour[bp] = CYAN;
        if (random3(3) == 0)
            mitm.colour[bp] = WHITE;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_KOBOLD_DEMONOLOGIST:         // kobold demonologist
    case MONS_ORC_WIZARD:                  // orc wiz
    case MONS_ORC_SORCEROR:                // orc sorc
        force_spec = 3;

    case MONS_NECROMANCER:                 // necromancer
    case MONS_WIZARD:                      // wizard
    case MONS_PSYCHE:                      // Psyche
    case MONS_DONALD:                      // Donald
    case MONS_JOSEPHINE:                   // Josephine
    case MONS_AGNES:                       // Agnes
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_DAGGER;
        iquan = 1;
        break;


    case MONS_CEREBOV:                   // Okawaru
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_GREAT_SWORD;
        mitm.special[bp] = 188;
        mitm.pluses[bp] = 156;
        mitm.pluses2[bp] = 56;
        mitm.colour[bp] = YELLOW;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_DISPATER:                   // Dispater
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_QUARTERSTAFF;
        mitm.special[bp] = 189;
        mitm.pluses[bp] = 54;
        mitm.pluses2[bp] = 54;
        mitm.colour[bp] = YELLOW;
        iquan = 1;
        force_item = 1;
        break;

    case MONS_ASMODEUS:                   // Asmodeus
        mitm.base_type[bp] = 0;
        mitm.sub_type[bp] = WPN_MACE;
        mitm.special[bp] = 190;
        mitm.pluses[bp] = 57;
        mitm.pluses2[bp] = 57;
        mitm.colour[bp] = RED;
        iquan = 1;
        force_item = 1;
        break;


    case MONS_GERYON:                     // Geryon
        mitm.base_type[bp] = 13;
        mitm.sub_type[bp] = 6;
        iquan = 1;
        break;
    }                           // end of switch(menv [bk].type)

    if (mitm.base_type[bp] == 101)
    {
        mitm.base_type[bp] = 100;
        goto give_armour;
    }

    if (force_item != 0)
        mitm.quantity[bp] = iquan;

    xitc = mitm.base_type[bp];
    xitt = mitm.sub_type[bp];
    if (force_item != 0)
        thing_created = bp;
    else
        thing_created = items(0, xitc, xitt, 1, give_level, force_spec);

    mitm.x[thing_created] = 1;
    mitm.y[thing_created] = 1;
    mitm.id[thing_created] = 0;
    if (mitm.base_type[thing_created] == 0)
        menv[bk].inv[hand_used] = thing_created;        // hand_used = 0 unless Ettin's 2nd hand etc.

    if (mitm.base_type[thing_created] == 1)
        menv[bk].inv[1] = thing_created;
    if (mitm.base_type[thing_created] == 6)
        menv[bk].inv[4] = thing_created;
    if (mitm.base_type[thing_created] == 15 || mitm.base_type[thing_created] == 13)
        menv[bk].inv[4] = thing_created;

    if (mitm.base_type[thing_created] == 0 && mitm.special[thing_created] % 30 == 7)
        menv[bk].armor_class += 5;

    if (force_item == 0)
        item_colour(thing_created);


give_armour:

// actually, should be give_ammo now

// this bit gives ammunition to go with missile hand weapons.
    // only gives darts for hand xbows

// note that force_spec is not reset for this section

    if (menv[bk].inv[0] != 501 && mitm.sub_type[menv[bk].inv[0]] >= 13 && mitm.sub_type[menv[bk].inv[0]] <= 16)
    {

        for (bp = 0; bp < ITEMS - 100; bp++)
        {
//                      if (bp == 1) continue;
            if (mitm.quantity[bp] == 0 || mitm.base_type[bp] == 100)
                break;
        }


        if (bp >= ITEMS - 100)
            return;             // already too many.


        mitm.pluses[bp] = 50;
        mitm.pluses2[bp] = 0;
        mitm.special[bp] = 0;
        force_item = 0;

        mitm.base_type[bp] = 1;
        mitm.sub_type[bp] = 1;

        switch (mitm.sub_type[menv[bk].inv[0]])
        {
        case 13:                // sling

            mitm.sub_type[bp] = 0;
            break;
        case 14:                // bow

            mitm.sub_type[bp] = 1;
            break;
        case 15:                // xbow

            mitm.sub_type[bp] = 2;
            break;
        case 16:                // hand xbow

            mitm.sub_type[bp] = 3;
            break;
        }

        mitm.colour[bp] = LIGHTCYAN;
        iquan = 3 + random3(10) + random3(7);

        mitm.special[bp] = (mitm.special[menv[bk].inv[0]] / 30) * 30;

        if (force_item != 0)
            mitm.quantity[bp] = iquan;

        xitc = mitm.base_type[bp];
        xitt = mitm.sub_type[bp];
        if (force_item != 0)
            thing_created = bp;
        else
            thing_created = items(0, xitc, xitt, 1, give_level, force_spec);

        mitm.x[thing_created] = 1;
        mitm.y[thing_created] = 1;
        mitm.id[thing_created] = 0;
        menv[bk].inv[1] = thing_created;

        if (mitm.base_type[thing_created] == 0 && mitm.special[thing_created] % 30 == 7)
            menv[bk].armor_class += 3;
        if (force_item == 0)
            item_colour(thing_created);

    }                           // end if needs ammo


    bp = 0;

    for (bp = 0; bp < ITEMS - 100; bp++)
    {
        if (mitm.quantity[bp] == 0 || mitm.quantity[bp] == 100)
            break;
    }
    if (bp >= ITEMS - 100)
        return;                 // already too many.

/*
   while ((mitm.base_type [bp] != 100 || mitm.quantity [bp] != 0) && bp < ITEMS)
   {
   bp++;
   //        if (bp == 1) continue;
   }

   if (bp > ITEMS - 100) return; // already too many.
 */
    force_spec = 250;

    switch (menv[bk].type)
    {

    case 263:                   // deep elf soldier

    case 264:                   // deep elf fighter

    case 265:                   // deep elf knight

    case 269:                   // deep elf priest

    case 270:                   // deep elf high priest

        force_spec = 1;
    case 14:                    // orc
        //case 36:

    case 282:                   // Blork the orc

        if (force_spec == 250)
            force_spec = 3;
    case 280:                   // Terence

    case 286:                   // Psyche

    case 291:                   // Joseph
        //              case 292:// Anita

    case 293:                   // Erica

    case 294:                   // Josephine

    case 295:                   // Harold

    case 296:                   // Norbert

    case 297:                   // Jozef

        iquan = 1;
        if (random3(5) < 2)
        {
            mitm.base_type[bp] = 2;
            mitm.colour[bp] = 11;
            switch (random3(8))
            {
            case 0:
                mitm.sub_type[bp] = 1;  //break;

            case 1:
                mitm.sub_type[bp] = 1;  //break;

            case 2:
                mitm.sub_type[bp] = 1;  //break;

            case 3:
                mitm.sub_type[bp] = 1;
                mitm.colour[bp] = 6;
                break;
            case 4:
                mitm.sub_type[bp] = 2;
                break;
            case 5:
                mitm.sub_type[bp] = 2;
                break;
            case 6:
                mitm.sub_type[bp] = 3;
                break;
            case 7:
                mitm.sub_type[bp] = 4;
                break;
                //                      case 8: mitm.sub_type [bp] = 5; break;
                //                      case 9: mitm.sub_type [bp] = 14; break;
            }
        }
        else
            return;
        break;

    case 52:                    // orc warrior

        force_spec = 3;
    case 285:                   // Edmund

    case 289:                   // Emily

    case 303:                   // Rupert

    case 304:                   // Wayne

    case 305:                   // Duane

        mitm.base_type[bp] = 2;
        mitm.colour[bp] = 11;
        switch (random3(8))
        {
        case 0:
            mitm.sub_type[bp] = 1;
            mitm.colour[bp] = 6;
            break;
        case 1:
            mitm.sub_type[bp] = 1;
            mitm.colour[bp] = 6;
            break;
        case 2:
            mitm.sub_type[bp] = 2;
            break;
        case 3:
            mitm.sub_type[bp] = 2;
            break;
        case 4:
            mitm.sub_type[bp] = 3;
            break;
        case 5:
            mitm.sub_type[bp] = 3;
            break;
        case 6:
            mitm.sub_type[bp] = 4;
            break;
        case 7:
            mitm.sub_type[bp] = 4;
            break;
        }
        break;

    case 55:                    // orc knight

    case 262:                   // orc warlord

        force_spec = 3;
    case 109:                   // hell knight

    case 299:                   // Maud

    case 300:                   // Louise

    case 308:                   // Adolf

    case 309:                   // Margery

    case 360:                   // vault guard

    case 362:                   // vampire knight

        mitm.base_type[bp] = 2;
        mitm.colour[bp] = 11;
        mitm.sub_type[bp] = 4 + random3(4);
        iquan = 1;
        break;

    case 26:
    case 60:                    // Wight & Angel

    case 283:                   // Sigmund

        force_spec = 100;
        mitm.base_type[bp] = 2;
        mitm.sub_type[bp] = 0;
        mitm.colour[bp] = WHITE;
        iquan = 1;
        break;

    case 161:                   // naga

    case 260:                   // naga mage

    case 261:                   // naga warrior

        if (random3(3) != 0)
            return;
    case 368:
    case 53:                    // kobold demonologist

    case 54:
    case 111:
    case 142:                   // ogre mage

    case 281:                   // Jessica

    case 288:                   // Donald

        force_spec = 100;
        mitm.base_type[bp] = 2;
        mitm.sub_type[bp] = 0;
        mitm.colour[bp] = 1 + random3(15);
        iquan = 1;
        break;

    case 266:                   // deep elf mage

    case 267:                   // deep elf summoner

    case 268:                   // deep elf conjurer

    case 271:                   // deep elf demonologist

    case 272:                   // deep elf annihilator

    case 273:                   // deep elf sorceror

    case 274:                   // deep elf death mage

        force_spec = 1;
    case 103:                   // orc sorc

    case 112:                   // orc pr

    case 113:                   // orc high pr

        if (force_spec == 250)
            force_spec = 3;
    case 110:                   // necr

    case 284:                   // Zachariah

    case 298:                   // Agnes

    case 301:                   // Francis

    case 302:                   // Frances

    case 310:                   // Boris

    case 363:                   // vampire mage

        mitm.base_type[bp] = 2;
        mitm.sub_type[bp] = 0;
        mitm.colour[bp] = DARKGREY;
        iquan = 1;
        break;


    default:
        return;

    }                           // end of switch(menv [bk].type)

    iquan = 1;

    xitc = mitm.base_type[bp];
    xitt = mitm.sub_type[bp];

    thing_created = items(0, xitc, xitt, 1, many_many / 2 + 1, force_spec);


    mitm.x[thing_created] = 1;
    mitm.y[thing_created] = 1;
    menv[bk].inv[2] = thing_created;

    if (menv[bk].type != 60)
        item_colour(thing_created);     // Wights' robes are white

    if (menv[bk].type == 60)
        mitm.colour[thing_created] = WHITE;

    menv[bk].armor_class += property(mitm.base_type[thing_created],
                                            mitm.sub_type[thing_created], 0);

    int armour_plus = 0;
    if (mitm.pluses[thing_created] > 130)
        armour_plus = mitm.pluses[thing_created] - 150;
    else
        armour_plus = mitm.pluses[thing_created] - 50;

    ASSERT( abs( armour_plus ) < 20 );
    if (abs( armour_plus ) < 20)
    {
        menv[bk].armor_class += armour_plus;
    }

    menv[bk].evasion += property(mitm.base_type[thing_created],
                                        mitm.sub_type[thing_created], 1) / 2;

    if (menv[bk].evasion < 1)
        menv[bk].evasion = 1;   // This *shouldn't* happen.
}                               // end of void give_item()


void item_colour(int p)
{
    bp = p;

    int switchnum = 0;


    switch (mitm.base_type[bp])
    {
    case 0:
        if (mitm.special[bp] % 30 == 25)
            break;              /* unrandarts have already been coloured */

        if (mitm.special[bp] > 180)
        {
            switch (mitm.special[bp] - 180)
            {
            case 1:
                mitm.colour[bp] = YELLOW;
                break;
            case 2:
                mitm.colour[bp] = RED;
                break;
            case 3:
                mitm.colour[bp] = DARKGREY;
                break;
            case 4:
                mitm.colour[bp] = random3(15) + 1;
                break;
            case 5:
                mitm.colour[bp] = MAGENTA;
                break;
            case 6:
                mitm.colour[bp] = YELLOW;
                break;
            case 7:
                mitm.colour[bp] = LIGHTGREY;
                break;

            case 11:
                mitm.colour[bp] = RED;
                break;
            case 12:
                mitm.colour[bp] = LIGHTCYAN;
                break;
            case 13:
                mitm.colour[bp] = GREEN;
                break;
            case 14:
                mitm.colour[bp] = WHITE;
                break;
            case 15:
                mitm.colour[bp] = BROWN;
                break;
            }
            break;
        }

        switch (mitm.sub_type[bp])
        {

        case 0:
        case 13:
        case 14:
        case 15:
        case 16:
        case 18:
        case 20:
        case 21:
        case 29:
        case 30:
            mitm.colour[bp] = BROWN;
            break;

        case 23:                // quick blade

            mitm.colour[bp] = LIGHTBLUE;
            break;

        case 25:                // exec axe

            mitm.colour[bp] = RED;
            break;

        case 32:
        case 33:                // demon blade/whip

            mitm.colour[bp] = random3(15) + 1;
            break;

        default:
            mitm.colour[bp] = LIGHTCYAN;
            if (mitm.special[bp] / 30 == 5)
                mitm.colour[bp] = CYAN;         // dwarven

            break;
        }
        if (random3(5) == 0 && mitm.special[bp] % 30 >= 25)
            mitm.colour[bp] = random3(15) + 1;
        break;

    case 1:
        switch (mitm.sub_type[bp])
        {
        case 0:
        case 5:
            mitm.colour[bp] = BROWN;
            break;

        case 10:
            mitm.colour[bp] = LIGHTCYAN;
            if (mitm.pluses2[bp] >= 2)
                mitm.colour[bp] = random3(15) + 1;
            break;

        default:
            mitm.colour[bp] = LIGHTCYAN;
            if (mitm.special[bp] / 30 == 5)
                mitm.colour[bp] = CYAN;
            break;
        }
        break;

    case 2:
        if (mitm.special[bp] % 30 == 25)
            break;              /* unrandarts have already been coloured */
        switch (mitm.sub_type[bp])
        {
        case ARM_ROBE:
        case ARM_CLOAK:
            mitm.colour[bp] = random3(15) + 1;
            break;

        case ARM_HELMET:
            if (mitm.pluses2[bp] == 2 || mitm.pluses2[bp] == 3)
            {
                // caps and wizard's hats are random coloured
                mitm.colour[bp] = random3(15) + 1;
            }
            else
            {
                mitm.colour[bp] = LIGHTCYAN;
            }
            break;

        case ARM_LEATHER_ARMOUR:
        case ARM_GLOVES:
        case ARM_BOOTS:         // maybe more interesting boot colours?
            mitm.colour[bp] = BROWN;
            break;

        case ARM_DRAGON_HIDE:
        case ARM_DRAGON_ARMOUR:
            mitm.colour[bp] = GREEN;
            break;              //strcat(glog , "dragon hide"); break;

        case ARM_TROLL_HIDE:
        case ARM_TROLL_LEATHER_ARMOUR:
            mitm.colour[bp] = BROWN;
            break;              //strcat(glog , "troll hide"); break;

        case ARM_CRYSTAL_PLATE_MAIL:
            mitm.colour[bp] = LIGHTGREY;
            break;              //strcat(glog , "crystal plate mail"); break;

        case ARM_ICE_DRAGON_HIDE:
        case ARM_ICE_DRAGON_ARMOUR:
            mitm.colour[bp] = WHITE;
            break;              //strcat(glog , "ice dragon hide"); break;

        case ARM_STEAM_DRAGON_HIDE:
        case ARM_STEAM_DRAGON_ARMOUR:
            mitm.colour[bp] = LIGHTGREY;
            break;              //strcat(glog , "ste dragon scale mail"); break;

        case ARM_MOTTLED_DRAGON_HIDE:
        case ARM_MOTTLED_DRAGON_ARMOUR:
            mitm.colour[bp] = LIGHTMAGENTA;
            break;              //strcat(glog , "mot dragon scale mail"); break;

        case ARM_STORM_DRAGON_HIDE:
        case ARM_STORM_DRAGON_ARMOUR:
            mitm.colour[bp] = LIGHTBLUE;
            break;              //strcat(glog , "stordragon scale mail"); break;

        case ARM_GOLD_DRAGON_HIDE:
        case ARM_GOLD_DRAGON_ARMOUR:
            mitm.colour[bp] = YELLOW;
            break;              //strcat(glog , "gol dragon scale mail"); break;

        case ARM_ANIMAL_SKIN:
            mitm.colour[bp] = BROWN;
            break;              // animal skin

        case ARM_SWAMP_DRAGON_HIDE:
        case ARM_SWAMP_DRAGON_ARMOUR:
            mitm.colour[bp] = BROWN;
            break;              // swamp dragon skin

        default:
            mitm.colour[bp] = LIGHTCYAN;
            if (mitm.special[bp] / 30 == 5)
                mitm.colour[bp] = CYAN;
            break;
        }

        if (random3(5) == 0 && mitm.special[bp] % 30 >= 25)
            mitm.colour[bp] = random3(15) + 1;
        break;

    case 3:
        mitm.special[bp] = you.item_description[0][mitm.sub_type[bp]];
        switch (mitm.special[bp] % 12)
        {
        case 0:         //strcpy(fake_name [bp], "iron wand");

            mitm.colour[bp] = CYAN;
            break;
        case 1:         //strcpy(fake_name [bp], "brass wand");

            mitm.colour[bp] = YELLOW;
            break;
        case 2:         //strcpy(fake_name [bp], "bone wand");

            mitm.colour[bp] = LIGHTGREY;
            break;
        case 3:         //strcpy(fake_name [bp], "wooden wand");

            mitm.colour[bp] = 6;
            break;
        case 4:         //strcpy(fake_name [bp], "copper wand");

            mitm.colour[bp] = 6;
            break;
        case 5:         //strcpy(fake_name [bp], "gold wand");

            mitm.colour[bp] = 14;
            break;
        case 6:         //strcpy(fake_name [bp], "silver wand");

            mitm.colour[bp] = WHITE;
            break;
        case 7:         //strcpy(fake_name [bp], "bronze wand");

            mitm.colour[bp] = 6;
            break;
        case 8:         //strcpy(fake_name [bp], "ivory wand");

            mitm.colour[bp] = LIGHTGREY;
            break;
        case 9:         //strcpy(fake_name [bp], "glass wand");

            mitm.colour[bp] = 7;
            break;
        case 10:                //strcpy(fake_name [bp], "lead wand");

            mitm.colour[bp] = LIGHTGREY;
            break;
        case 11:                //strcpy(fake_name [bp], "plastic wand");
            //              mitm.colour [bp] = DARKGREY;  break;

            mitm.colour[bp] = random3(15) + 1;
            break;
        }                       // end of switch(randnum)

        if (mitm.special[bp] / 12 == 9)
            mitm.colour[bp] = 8;

        // rare wands (eg disintegration - these will be very rare): maybe only 1 thing, like: crystal, shining, etc.
        break;



    case 8:
        mitm.special[bp] = you.item_description[1][mitm.sub_type[bp]];

        switch (mitm.special[bp] % 14)
        {

        case 0:         //strcpy(fake_name [bp], "clear potion");

            mitm.colour[bp] = 7;
            break;
        case 1:         //strcpy(fake_name [bp], "blue potion");

            mitm.colour[bp] = BLUE;
            break;
        case 2:         //strcpy(fake_name [bp], "black potion");

            mitm.colour[bp] = DARKGREY;
            break;
        case 3:         //strcpy(fake_name [bp], "silvery potion");

            mitm.colour[bp] = WHITE;
            break;
        case 4:         //strcpy(fake_name [bp], "cyan potion");

            mitm.colour[bp] = CYAN;
            break;
        case 5:         //strcpy(fake_name [bp], "purple potion");

            mitm.colour[bp] = MAGENTA;
            break;
        case 6:         //strcpy(fake_name [bp], "orange potion");

            mitm.colour[bp] = LIGHTRED;
            break;
        case 7:         //strcpy(fake_name [bp], "inky potion");

            mitm.colour[bp] = BLUE;
            break;
        case 8:         //strcpy(fake_name [bp], "red potion");

            mitm.colour[bp] = RED;
            break;
        case 9:         //strcpy(fake_name [bp], "yellow potion");

            mitm.colour[bp] = YELLOW;
            break;
        case 10:                //strcpy(fake_name [bp], "green potion");

            mitm.colour[bp] = GREEN;
            break;
        case 11:                //strcpy(fake_name [bp], "brown potion");

            mitm.colour[bp] = BROWN;
            break;
        case 12:                //strcpy(fake_name [bp], "pink potion");

            mitm.colour[bp] = LIGHTMAGENTA;
            break;
        case 13:                //strcpy(fake_name [bp], "white potion");

            mitm.colour[bp] = WHITE;
            break;

        }

        break;

    case 4:                     // food

        mitm.colour[bp] = 6;
        switch (mitm.sub_type[bp])
        {
        case 0:
            mitm.colour[bp] = BROWN;
            break;              //strcpy(fake_name [bp], "meat ration"); break;

        case 1:
            mitm.colour[bp] = BROWN;
            break;              //strcpy(fake_name [bp], "bread ration"); break;

        case 2:
            mitm.colour[bp] = LIGHTGREEN;
            break;              //strcpy(fake_name [bp], "pear"); break;

        case 3:
            switch (random3(2))
            {
            case 0:
                mitm.colour[bp] = GREEN;
                break;
            case 1:
                mitm.colour[bp] = RED;
                break;
            }
            break;
            //strcpy(fake_name [bp], "apple"); break; // make this less common.
        case 4:
            mitm.colour[bp] = GREEN;
            break;              //strcpy(fake_name [bp], "choko"); break;

        case 5:
            mitm.colour[bp] = YELLOW;
            break;              //strcpy(fake_name [bp], "honeycomb"); break;

        case 6:
            mitm.colour[bp] = YELLOW;
            break;              //strcpy(fake_name [bp], "royal jelly"); break;

        case 7:
            mitm.colour[bp] = GREEN;
            break;              // snozzcumber//strcpy(fake_name [bp], ""); break;

        case 8:
            mitm.colour[bp] = YELLOW;
            break;              // pizza???

        case 9:
            mitm.colour[bp] = LIGHTRED;
            break;              // apricot

        case 10:
            mitm.colour[bp] = LIGHTRED;
            break;              // orange

        case 11:
            mitm.colour[bp] = YELLOW;
            break;              // banana

        case 12:
            mitm.colour[bp] = RED;
            break;              // strawberry

        case 13:
            mitm.colour[bp] = BROWN;
            break;              // rambutan

        case 14:
            mitm.colour[bp] = YELLOW;
            break;              // lemon

        case 15:
            switch (random3(2))
            {
            case 0:
                mitm.colour[bp] = GREEN;
                break;
            case 1:
                mitm.colour[bp] = MAGENTA;
                break;          // ???

            }
            break;              // grape

        case 16:
            mitm.colour[bp] = BROWN;
            break;              // sultana

        case 17:
            mitm.colour[bp] = BROWN;
            break;              // lychee

        case 18:
            mitm.colour[bp] = BROWN;
            break;              // beef jerky

        case 19:
            mitm.colour[bp] = YELLOW;
            break;              // cheese

        case 20:
            mitm.colour[bp] = BROWN;
            break;              // saus
            //              case 21: mitm.colour [bp] = BROWN; break;
            //                              case 22: mitm.colour [bp] = BROWN; break;

            //                      break;
        }
        break;

    case OBJ_JEWELLERY: // jewellery

        if (mitm.special[bp] == 200)
        {
            mitm.colour[bp] = 1 + random3(15);
            break;
        }
        if (mitm.special[bp] == 201)
        {
            break;              /* unrandarts have already been coloured */
        }
        mitm.colour[bp] = 14;

        mitm.special[bp] = you.item_description[3][mitm.sub_type[bp]];

        switchnum = mitm.special[bp] % 13;
        switch (switchnum)
        {
        case 0:
            mitm.colour[bp] = BROWN;
            break;
        case 1:
            mitm.colour[bp] = LIGHTGREY;
            break;
        case 2:
            mitm.colour[bp] = YELLOW;
            break;
        case 3:
            mitm.colour[bp] = CYAN;
            break;
        case 4:
            mitm.colour[bp] = CYAN;
            break;
        case 5:
            mitm.colour[bp] = BROWN;
            break;
        case 6:
            mitm.colour[bp] = YELLOW;
            break;
        case 7:
            mitm.colour[bp] = BROWN;
            break;
        case 8:
            mitm.colour[bp] = LIGHTGREY;
            break;
        case 9:
            mitm.colour[bp] = WHITE;
            break;
        case 10:
            mitm.colour[bp] = WHITE;
            break;
        case 11:
            mitm.colour[bp] = LIGHTGREY;
            break;
        case 12:
            mitm.colour[bp] = GREEN;
            break;
        case 13:
            mitm.colour[bp] = LIGHTCYAN;
            break;
            //      case 14: mitm.colour [bp] = BROWN; break;
            //      case 15: mitm.colour [bp] = BROWN; break;
        }

        if (mitm.sub_type[bp] >= 35)
            switch (switchnum)
            {
            case 0:
                mitm.colour[bp] = WHITE;        //zirconium amulet

            case 1:
                mitm.colour[bp] = LIGHTBLUE;    //sapphire amulet

            case 2:
                mitm.colour[bp] = YELLOW;       //"golden amulet

            case 3:
                mitm.colour[bp] = GREEN;        //"emerald amulet

            case 4:
                mitm.colour[bp] = RED;  //"garnet amulet

            case 5:
                mitm.colour[bp] = BROWN;        //"bronze amulet

            case 6:
                mitm.colour[bp] = YELLOW;       //"brass amulet

            case 7:
                mitm.colour[bp] = BROWN;        //"copper amulet

            case 8:
                mitm.colour[bp] = RED;  //"ruby amulet

            case 9:
                mitm.colour[bp] = WHITE;        //"ivory amulet

            case 10:
                mitm.colour[bp] = LIGHTGREY;    //"bone amulet

            case 11:
                mitm.colour[bp] = WHITE;        //"platinum amulet

            case 12:
                mitm.colour[bp] = GREEN;        //"jade amulet

            case 13:
                mitm.colour[bp] = random() % 15 + 1;    //"plastic amulet

            }

        switch (mitm.special[bp] / 13)
        {
        case 5:
            mitm.colour[bp] = DARKGREY;
            break;              // blackened - same for both rings and amulets

        }
        break;


    case 6:                     // scrolls
        mitm.colour[bp] = LIGHTGREY;
        mitm.special[bp] = you.item_description[2][mitm.sub_type[bp]];
        mitm.pluses[bp] = you.item_description[4][mitm.sub_type[bp]];
        break;

    case 10:                    // books
        switch (mitm.special[bp] % 10)
        {
        case 0:         //strcat(glog , "paperback book");
        case 1:         //strcat(glog , "hardcover book");
            mitm.colour[bp] = random3(15) + 1;
            break;

        case 2:
            mitm.colour[bp] = DARKGREY;  //strcat(glog , "leatherbound book");
            if (random3(3) == 0)
                mitm.colour[bp] = BROWN;
            break;

        case 3:
            mitm.colour[bp] = CYAN;     //strcat(glog , "metal-bound book");
            break;

        case 4:
            mitm.colour[bp] = LIGHTGREY;  //strcat(glog , "papyrus book");
            break;

        case 5:         //strcat(glog , " book");
        case 6:         //strcat(glog , " book");
        default:
            break;
        }
        break;

    case 11:                    // staves
        mitm.colour[bp] = BROWN;
        break;

    case 12:                    // Magical Orbs of Power
        mitm.colour[bp] = LIGHTMAGENTA;
/* if (mitm.sub_type [bp] == 1) mitm.colour [bp] = LIGHTBLUE;
   if (mitm.sub_type [bp] == 2) mitm.colour [bp] = CYAN;
   if (mitm.sub_type [bp] == 3) mitm.colour [bp] = DARKGREY;

   if (mitm.sub_type [bp] == 4) mitm.colour [bp] = RED;
   if (mitm.sub_type [bp] == 5) mitm.colour [bp] = LIGHTRED;
   if (mitm.sub_type [bp] == 6) mitm.colour [bp] = LIGHTBLUE;
   if (mitm.sub_type [bp] == 7) mitm.colour [bp] = RED;
   if (mitm.sub_type [bp] == 8) mitm.colour [bp] = LIGHTRED;
   if (mitm.sub_type [bp] == 9) mitm.colour [bp] = LIGHTCYAN;
   if (mitm.sub_type [bp] == 10) mitm.colour [bp] = LIGHTGREEN;
   if (mitm.sub_type [bp] == 11) mitm.colour [bp] = BROWN;
   if (mitm.sub_type [bp] == 12) mitm.colour [bp] = CYAN;
   if (mitm.sub_type [bp] == 13) mitm.colour [bp] = BLUE;
   if (mitm.sub_type [bp] == 14) mitm.colour [bp] = LIGHTBLUE;
   if (mitm.sub_type [bp] == 15) mitm.colour [bp] = GREEN;
   if (mitm.sub_type [bp] == 16) mitm.colour [bp] = LIGHTBLUE;
   if (mitm.sub_type [bp] == 17) mitm.colour [bp] = LIGHTGREY;
   if (mitm.sub_type [bp] == 18) mitm.colour [bp] = LIGHTMAGENTA;
   if (mitm.sub_type [bp] == 19) mitm.colour [bp] = WHITE;

   if (mitm.sub_type [bp] == 20) mitm.colour [bp] = LIGHTMAGENTA;
   if (mitm.sub_type [bp] == 21) mitm.colour [bp] = LIGHTBLUE;
   if (mitm.sub_type [bp] == 22) mitm.colour [bp] = RED;
   if (mitm.sub_type [bp] == 23) mitm.colour [bp] = DARKGREY; */

        break;

    case 13:                    // Misc

        switch (mitm.sub_type[bp])
        {
        case 0:
            mitm.colour[bp] = BROWN;
            break;              // flask

        case 1:
            mitm.colour[bp] = LIGHTGREY;
            break;              // orb

        case 2:
            mitm.colour[bp] = LIGHTGREY;
            break;              //strcat(glog, "fan of air elementals"); break;

        case 3:
            mitm.colour[bp] = YELLOW;
            break;              //strcat(glog, "lamp of fire elementals"); break;

        case 4:
            mitm.colour[bp] = BROWN;
            break;              //strcat(glog, "stone of earth elementals"); break;

        case 5:
            mitm.colour[bp] = LIGHTGREY;
            break;              // bone lantern

        case 6:
            mitm.colour[bp] = LIGHTGREY;
            break;              // horn of Geryon

        case 7:
            mitm.colour[bp] = DARKGREY;
            break;              // box of beasts

        case 9:
        case 8:
            mitm.colour[bp] = random() % 15 + 1;
            break;              // cards

        case 10:
            mitm.colour[bp] = LIGHTGREY;
            break;              // orb of energy

        case 11:
            mitm.colour[bp] = BLACK;
            break;              // empty box

        case 12:
            mitm.colour[bp] = LIGHTGREY;
            break;              // orb of fixation

        case 13:
            mitm.colour[bp] = LIGHTGREY;
            break;              // disc of storms

        case 14:
            mitm.colour[bp] = DARKGREY;
            break;              // rune of Zot

        default:
            mitm.colour[bp] = random() % 15 + 1;
            break;
        }
        break;

    case 14:                    // carrion

        mitm.colour[bp] = RED;
        break;

    }

}                               // end of item_colour



void place_traps(void)
{

    int num_traps = random3(5) + random3(5);

    for (bi = 0; bi < num_traps; bi++)
    {

        if (env.trap_type[bi] != 100)
            continue;           // traps can be placed in vaults

        do
        {
            env.trap_x[bi] = random3(60) + 10;
            env.trap_y[bi] = random3(50) + 10;
        }
        while (grd[env.trap_x[bi]][env.trap_y[bi]] != 67);

        env.trap_type[bi] = 0;

        if (random3(many_many + 1) > 1)
            env.trap_type[bi] = 1;      /* arrow */
        if (random3(many_many + 1) > 3)
            env.trap_type[bi] = 2;      /* spear */
        if (random3(many_many + 1) > 5)
            env.trap_type[bi] = 3;      /* axe */
        if (random3(many_many + 1) > 7)
            env.trap_type[bi] = 7;      /* bolt trap */
        if (random3(many_many + 1) > 11)
            env.trap_type[bi] = 6;      // blade - nasty!

        if ((random3(many_many + 1) > 14 && random3(3) == 0) || (you.where_are_you == 17 && random3(2) == 0))
            env.trap_type[bi] = 8;      /* Zot trap */
        if (random3(20) == 0)
            env.trap_type[bi] = 4;
        if (random3(40) == 0)
            env.trap_type[bi] = 5;

        grd[env.trap_x[bi]][env.trap_y[bi]] = 78;

    }                           // end of for i

}


void link_items(void)
{

    int b = 0;
    int n = 0;
    int m = 0;

    for (bi = 0; bi < ITEMS; bi++)
    {
        if (mitm.base_type[bi] == 100 || mitm.quantity[bi] == 0 || mitm.x[bi] == 1)
        {
            mitm.link[bi] = 501;
            continue;
        }

        if (igrd[mitm.x[bi]][mitm.y[bi]] == 501)
        {
            igrd[mitm.x[bi]][mitm.y[bi]] = bi;
            continue;
        }
        else
        {
            b = igrd[mitm.x[bi]][mitm.y[bi]];

            while (b != 501)
            {
                m = b;
                n = mitm.link[b];
                b = n;
            }                   // end of while

            mitm.link[m] = bi;

        }
    }                           // end of for i

    for (bi = 0; bi < MNST; bi++)
    {
        for (bj = 7; bj >= 0; bj--)
        {
            if (menv[bi].inv[bj] == 501)
                continue;
            if (igrd[mitm.x[menv[bi].inv[bj]]][mitm.y[menv[bi].inv[bj]]] == menv[bi].inv[bj])
            {
                igrd[mitm.x[menv[bi].inv[bj]]][mitm.y[menv[bi].inv[bj]]] = mitm.link[menv[bi].inv[bj]];
            }
        }
    }
}

/*
   void fix_item(int fit, char fx, char fy)
   {




   for (bi = 0; bi < ITEMS; bi ++)
   {
   if (mitm.base_type [bi] == 100 || mitm.quantity [bi] == 0 || mitm.x [bi] == 1)
   {
   mitm.link [bi] = 501;
   continue;
   }

   if (igrd [mitm.x [bi]] [mitm.y [bi]] == 501)
   {
   igrd [mitm.x [bi]] [mitm.y [bi]] = bi;
   continue;
   } else
   {
   b = igrd [mitm.x [bi]] [mitm.y [bi]];

   while(b != 501)
   {
   m = b;
   n = mitm.link [b];
   b = n;
   } // end of while

   mitm.link [m] = bi;

   }
   } // end of for i

   }
 */

void roguey_level(void)
{

    unsigned char rox1[30];
    unsigned char rox2[30];
    unsigned char roy1[30];
    unsigned char roy2[30];
    int cn = 0;

    for (bcount_y = 0; bcount_y < 5; bcount_y++)
    {

        for (bcount_x = 0; bcount_x < 5; bcount_x++)
        {

// rooms:

            rox1[cn] = bcount_x * 13 + random3(4) + 8;
            roy1[cn] = bcount_y * 11 + random3(4) + 8;

            rox2[cn] = rox1[cn] + random3(8) + 3;
            roy2[cn] = roy1[cn] + random3(6) + 3;

            cn++;

        }                       // end of for bcount_y

    }                           // end of for bcount_x

    cn = 0;

    for (bi = 0; bi < 25; bi++)
    {
        for (bcount_x = rox1[bi]; bcount_x < rox2[bi]; bcount_x++)
        {
            for (bcount_y = roy1[bi]; bcount_y < roy2[bi]; bcount_y++)
            {
                // Jesse says this is likely a bug...
                //if (grd [bcount_x] [bcount_y] == 1 && bcount_x < 72);
                if (grd[bcount_x][bcount_y] == 1 && bcount_x < 72)
                    grd[bcount_x][bcount_y] = 67;
            }                   // end of for bcount_y

        }                       // end of for bcount_x

        if (rox2[bi] - rox1[bi] > 5 && roy2[bi] - roy1[bi] > 5)
            if (random3(100 - many_many) < 3)
            {
                if (random3(4) != 0)
                    box_room(rox1[bi] + 2, rox2[bi] - 2, roy1[bi] + 2, roy2[bi] - 2, random3(2) + 1);
                else
                    box_room(rox1[bi] + 2, rox2[bi] - 2, roy1[bi] + 2, roy2[bi] - 2, 4);

                if (random3(2) == 0)
                    treasure_area(many_many, rox1[bi] + 3, rox2[bi] - 3, roy1[bi] + 3, roy2[bi] - 3);
            }
    }                           // end of for i


// Now, join them together:

    char pos[2];
    char jpos[2];

    char doing = 0;

    char last_room = 0;


    for (bp = 0; bp < 2; bp++)
    {

        for (bi = 0; bi < 25; bi++)
        {
            if (bp == 0 && (bi % 5 == 0 || bi == 0))
                continue;

            if (bp == 1 && bi < 5)
                continue;

            switch (bp)
            {
            case 0:
                last_room = bi - 1;
                pos[0] = rox1[bi];      // - 1;

                pos[1] = roy1[bi] + random3(roy2[bi] - roy1[bi]);

                jpos[0] = rox2[last_room];      // + 1;

                jpos[1] = roy1[last_room] + random3(roy2[last_room] - roy1[last_room]);
                break;

            case 1:
                last_room = bi - 5;
                pos[1] = roy1[bi];      // - 1;

                pos[0] = rox1[bi] + random3(rox2[bi] - rox1[bi]);

                jpos[1] = roy2[last_room];      // + 1;

                jpos[0] = rox1[last_room] + random3(rox2[last_room] - rox1[last_room]);
                break;

            }                   // end of switch p

            while (pos[0] != jpos[0] || pos[1] != jpos[1])
            {
                doing = random3(2);

                if (pos[doing] < jpos[doing])
                    pos[doing]++;
                if (pos[doing] > jpos[doing])
                    pos[doing]--;

                if (grd[pos[0]][pos[1]] == 1)
                    grd[pos[0]][pos[1]] = 67;

            }                   // end of while

            if ((grd[pos[0] + 1][pos[1]] == 1 && grd[pos[0] - 1][pos[1]] == 1) || (grd[pos[0]][pos[1] + 1] == 1 && grd[pos[0]][pos[1] - 1] == 1))
            {
                if (grd[pos[0]][pos[1]] == 67)
                    grd[pos[0]][pos[1]] = 103;
            }

        }                       // end of for i

    }                           // end of for p


    if (many_many > 8 && random3(10) == 0)
    {

        int spec_room_done = random3(25);

        x1 = rox1[spec_room_done];
        x2 = rox2[spec_room_done];
        y1 = roy1[spec_room_done];
        y2 = roy2[spec_room_done];
        morgue();

        is_a_specroom = 2;      // ????????????????????????????????????????????????
        // should this be here?

        for (bcount_x = x1 - 1; bcount_x < x2; bcount_x++)
        {
            if (grd[bcount_x][y1 - 1] == 1)
                grd[bcount_x][y1 - 1] = 105;
            if (grd[bcount_x][y1 - 1] == 67 || grd[x1 - 1][bcount_y] == 3)
                grd[bcount_x][y1 - 1] = 117;
            //grd [bcount_x] [y1 - 1] = 105;
            //grd [bcount_x] [y2] = 105;
            if (grd[bcount_x][y2] == 1)
                grd[bcount_x][y2] = 105;
            if (grd[bcount_x][y2] == 67 || grd[x1 - 1][bcount_y] == 3)
                grd[bcount_x][y2] = 117;
        }

        for (bcount_y = y1 - 1; bcount_y < y2; bcount_y++)
        {
            if (grd[x1 - 1][bcount_y] == 1)
                grd[x1 - 1][bcount_y] = 105;
            if (grd[x1 - 1][bcount_y] == 67 || grd[x1 - 1][bcount_y] == 3)
                grd[x1 - 1][bcount_y] = 117;
            //grd [x1 - 1] [bcount_y] = 105;
            if (grd[x2][bcount_y] == 1)
                grd[x2][bcount_y] = 105;
            if (grd[x2][bcount_y] == 67 || grd[x2][bcount_y] == 3)
                grd[x2][bcount_y] = 117;
        }

        if (grd[x2][y2] == 1)
            grd[x2][y2] = 105;

    }

    for (bj = 0; bj < 3 + random3(2); bj++)
    {
        for (bi = 0; bi < 2; bi++)
        {
            //if (bi == 20) break; // ?

            do
            {
                pos[0] = random3(60) + 10;
                pos[1] = random3(50) + 10;
            }
            while (grd[pos[0]][pos[1]] != 67);

            if (bi == 0)
                grd[pos[0]][pos[1]] = 82 + bj;
            else
                grd[pos[0]][pos[1]] = 86 + bj;

        }                       // end for i

    }                           // end for j

}                               // end of void roguey_level()





void city_level(void)
{
    int wall_type = 0;          // remember, can have many wall types in one level

    int xs = 0;
    int ys = 0;
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    char pos[2];

    if (random3(4) != 0)
    {
        wall_type = 1 + random3(2);
    }
    else
        wall_type = 4;

    if (many_many >= 75 && many_many < 80)
        wall_type = 4;

    for (bcount_x = 7; bcount_x < 73; bcount_x++)
    {
        for (bcount_y = 7; bcount_y < 63; bcount_y++)
        {
            grd[bcount_x][bcount_y] = 67;
            igrd[bcount_x][bcount_y] = 501;
        }
    }

    for (bi = 0; bi < 5; bi++)
    {
        for (bj = 0; bj < 4; bj++)
        {

            xs = (bi * 13) + 8;
            ys = (bj * 14) + 8;
            x1 = xs + random3(3) + random3(3);
            y1 = ys + random3(3) + random3(3);
            x2 = xs + 11 - random3(3) - random3(3);
            y2 = ys + 11 - random3(3) - random3(3);

            if (random3(7) != 0)
            {
                if (random3(10) != 0)
                    box_room(x1, x2, y1, y2, wall_type);
                else if (random3(4) != 0)
                    box_room(x1, x2, y1, y2, random3(2) + 1);
                else
                    box_room(x1, x2, y1, y2, 4);
                if (random3(8) == 0 && x2 - x1 > 2 && y2 - y1 > 2)
                    box_room(x1 + 2, x2 - 2, y1 + 2, y2 - 2, wall_type);
                if (random3(4) == 0 && many_many != 59)
                    treasure_area(many_many, x1 + 3, x2 - 3, y1 + 3, y2 - 3);
            }
        }                       // end for j

    }                           // end for i

    for (bj = 0; bj < 1 + random3(2); bj++)
    {
        for (bi = 0; bi < 2; bi++)
        {
            do
            {
                pos[0] = random3(60) + 10;
                pos[1] = random3(50) + 10;
            }
            while (grd[pos[0]][pos[1]] != 67);


            if (bi == 0)
                grd[pos[0]][pos[1]] = 82 + bj;
            else
                grd[pos[0]][pos[1]] = 86 + bj;

        }                       // end for i

    }                           // end for j



}                               // end city_level



void box_room(int bx1, int bx2, int by1, int by2, int wall_type)
{

    for (bcount_x = bx1; bcount_x < bx2 + 1; bcount_x++)
    {
        if (grd[bcount_x][by1] == 67)
            grd[bcount_x][by1] = wall_type;
        if (grd[bcount_x][by2] == 67)
            grd[bcount_x][by2] = wall_type;
    }                           // end bcount_x

    for (bcount_y = by1; bcount_y < by2; bcount_y++)
    {
        if (grd[bx1][bcount_y] == 67)
            grd[bx1][bcount_y] = wall_type;
        if (grd[bx2][bcount_y] == 67)
            grd[bx2][bcount_y] = wall_type;
    }                           // end bcount_y

    if (random3(2) == 0)
    {
        if (random3(2) == 0)
        {
            grd[bx1][by1 + random3(by2 - by1 + 1)] = 3;
        }                       // end if random

        else
            grd[bx2][by1 + random3(by2 - by1 + 1)] = 3;

    }                           // end if random

    else if (random3(2) == 0)
        grd[bx1 + random3(bx2 - bx1 + 1)][by1] = 3;
    else
        grd[bx1 + random3(bx2 - bx1 + 1)][by2] = 3;

    if (random3(3) == 0)
    {
        if (random3(2) == 0)
        {
            grd[bx1][by1 + random3(by2 - by1 + 1)] = 3;
        }                       // end if random

        else
            grd[bx2][by1 + random3(by2 - by1 + 1)] = 3;
    }                           // end if random3(3)

    if (random3(3))
    {
        if (random3(2) == 0)
            grd[bx1 + random3(by2 - by1 + 1)][by1] = 3;
        else
            grd[bx1 + random3(bx2 - bx1 + 1)][by2] = 3;
    }

}                               // end box_room










int random3(unsigned int rmax)
{
    if (rmax == 0)
        return 0;
    return (random() % rmax);
}



void check_doors(void)
{
    char ig;

    for (bcount_x = 0; bcount_x < 80; bcount_x++)
    {
        for (bcount_y = 0; bcount_y < 70; bcount_y++)
        {
            ig = grd[bcount_x][bcount_y];

            if (ig != 3 && ig != 103 && ig != 33)
                continue;



            if (((grd[bcount_x - 1][bcount_y] < 10) + (grd[bcount_x + 1][bcount_y] < 10) + (grd[bcount_x][bcount_y - 1] < 10) + (grd[bcount_x][bcount_y + 1] < 10)) < 2)
                grd[bcount_x][bcount_y] = 67;
            else
                grd[bcount_x][bcount_y] = 3;

        }
    }
}


void spellbook_template(int sbook_type, int func_pass[10])
{
    ASSERT(sbook_type >= 0);
    ASSERT(sbook_type < NUMBER_SPELLBOOKS);

    // No point doing anything if it is the tome of destruction or a manual
    if (sbook_type == SPLBOOK_TOME_OF_DEST || sbook_type == SPLBOOK_MANUALS)
        return;

    for (int i = 1; i < 7; i++)
        func_pass[i] = spellbook_template_array[sbook_type][i];
}


void labyrinth_level()
{
    int lx = 0;
    int ly = 0;
    int keep_lx = 0;
    int keep_ly = 0;
    int keep_lx2 = 0;
    int keep_ly2 = 0;
    char do_2 = 0;
    int clear_space = 1;
    char start_point_x = 10;
    char start_point_y = 10;
    char going_x = 1;
    char going_y = 0;
    unsigned char traps_put2 = 0;

    if (random3(2) == 0)
        going_x = 1;
    else
        going_y = 1;

    if (random3(2) == 0)
    {
        start_point_x = 70;
        if (going_x == 1)
            going_x = -1;
    }
    if (random3(2) == 0)
    {
        start_point_y = 60;
        if (going_y == 1)
            going_y = -1;
    }

    lx = start_point_x;
    ly = start_point_y;

    if (going_y != 0)
        goto do_y;

do_x:                   // if (going_x != 0)
    traps_put2 = 0;
    clear_space = 0;            //random3(2) + 2;

    do
    {
        lx += going_x;
        if (grd[lx][ly] == DNGN_ROCK_WALL)
            grd[lx][ly] = DNGN_FLOOR;

    }
    while (grd[lx + going_x * (2 + clear_space)][ly] == DNGN_ROCK_WALL
                                                        && lx < 72 && lx > 8);

    going_x = 0;

    if (ly < 32)
        going_y = 1;
    if (ly > 37)
        going_y = -1;
    if (ly >= 32 && ly <= 37)
    {
        goto finishing;
    }


do_y:                   // if (going_y != 0)
    if (do_2 == 1)
    {
        lx = keep_lx2;
        ly = keep_ly2;
    }

    clear_space = 1;
// do_2 = 0 is the problem
    if (random3(2) == 0)
    {
        clear_space = 0;
        do_2 = 0;
    }
    else
    {
        clear_space = 2;        //2;

        do_2 = 1;
    }
    do
    {
        ly += going_y;
        if (grd[lx][ly] == 1)
            grd[lx][ly] = 67;
    }
    while (grd[lx][ly + going_y * (2 + clear_space)] == DNGN_ROCK_WALL
                                                    && ly < 62 && ly > 8);

    keep_lx = lx;
    keep_ly = ly;

//   if (clear_space > 1)
    {
        if (lx < 37)
            going_x = 1;
        if (lx > 42)
            going_x = -1;
        if (ly < 33)
            ly += 2;
        if (ly > 37)
            ly -= 2;

        if (do_2 == 0)
        {
            clear_space = 6;
        }
        else
        {
            clear_space = 2;
        }

        do
        {
            lx += going_x;
            if (grd[lx][ly] == DNGN_ROCK_WALL)
                grd[lx][ly] = DNGN_FLOOR;
        }
        while (grd[lx + going_x * (2 + clear_space)][ly] == DNGN_ROCK_WALL
                                                        && lx < 72 && lx > 8);
    }

    if (do_2 == 1)
    {
        keep_lx2 = lx;
        keep_ly2 = ly;
    }

    {
        lx = keep_lx;
        ly = keep_ly;
    }

    going_y = 0;

    if (lx < 37)
        going_x = 1;
    if (lx > 42)
        going_x = -1;
    if (lx >= 37 && lx <= 42)
    {
        goto finishing;
    }
    goto do_x;

finishing:
    start_point_x = random3(60) + 10;

    int treasure_item = 0;
    int glopop = 0;

    for (bcount_x = 0; bcount_x < 8 + random3(5) + random3(5); bcount_x++)
    {
        switch (random3(11))
        {
        case 9:
        case 0:
            glopop = OBJ_WEAPONS;
            break;
        case 1:
            glopop = OBJ_MISSILES;
            break;
        case 10:
        case 2:
            glopop = OBJ_ARMOUR;
            break;
        case 3:
            glopop = OBJ_WANDS;
            break;
        case 4:
            glopop = OBJ_MISCELLANY;
            break;
        case 5:
            glopop = OBJ_SCROLLS;
            break;
        case 6:
            glopop = OBJ_JEWELLERY;
            break;
        case 7:
            glopop = OBJ_BOOKS;
            break;
        case 8:
            glopop = OBJ_STAVES;
            break;
        }

        treasure_item = items(1, glopop, 250, 1, many_many * 3, 250);
        mitm.x[treasure_item] = lx;
        mitm.y[treasure_item] = ly;
    }

    int passed[2];

    passed[1] = 1;
    place_monster(
                     250,               //0, //plus_seventy,
                      MONS_MINOTAUR,    // typed,
                      1,                //type_place,
                      lx,               //px,
                      ly,               //py,
                      BEH_SLEEP,        //behaviour,
                      MHITNOT,          //hitting,
                      0,                //1,//allow_bands
                      many_many,
                     passed);


    grd[lx][ly] = DNGN_ROCK_STAIRS_UP;

    link_items();

    // Turn rock walls into undiggable stone or metal
    unsigned char floory = DNGN_STONE_WALL;

    if (random3(5) == 0)
        floory = DNGN_METAL_WALL;
    if (random3(15) == 0)
        floory = 10;

    for (bcount_x = 0; bcount_x < 80; bcount_x++)
    {
        for (bcount_y = 0; bcount_y < 70; bcount_y++)
        {
            if (floory == 10)
            {
                if (grd[bcount_x][bcount_y] == DNGN_ROCK_WALL)
                {
                    if (random3(2))
                        grd[bcount_x][bcount_y] = DNGN_STONE_WALL;
                    else
                        grd[bcount_x][bcount_y] = DNGN_METAL_WALL;
                }
            }
            else if (grd[bcount_x][bcount_y] == DNGN_ROCK_WALL)
                grd[bcount_x][bcount_y] = floory;
        }
    }
}                               // end void labyrinth level



int place_specific_trap(unsigned char spec_x, unsigned char spec_y,
                        unsigned char spec_type)
{

    int tcount = 0;

    if (spec_type == 100)
        spec_type = random() % 9;


    for (tcount = 0; tcount < NTRAPS; tcount++)
    {
        if (env.trap_type[tcount] == 100)
        {
            env.trap_type[tcount] = spec_type;
            env.trap_x[tcount] = spec_x;
            env.trap_y[tcount] = spec_y;
            grd[spec_x][spec_y] = 78;
            return 1;
        }
        if (tcount >= NTRAPS - 1)
            return 0;
    }

    return 0;

}                               // end place_specific_trap


void place_shops(void)
{
    int timeout = 0;
    int no_shops = 0;

    int i = 0;

    char shop_place_x = 0;
    char shop_place_y = 0;
    char force_stype = 100;

    if (random3(5) == 0)
        no_shops = 1;
    if (random3(25) == 0)
        no_shops = random3(5);  //random3(5);

    if (no_shops == 0 || many_many <= 2)
        return;
//no_shops = 4;

    for (i = 0; i < no_shops; i++)      // was no_shops

    {
        timeout = 0;
        do
        {
            shop_place_x = random3(60) + 10;
            shop_place_y = random3(50) + 10;
            timeout++;
            if (timeout > 20000)
                return;
        }
        while (grd[shop_place_x][shop_place_y] != 67);


        place_spec_shop(shop_place_x, shop_place_y, force_stype);
    }


}

void place_spec_shop(char shop_x, char shop_y, char force_s_type)
{
    int orb = 0;
    int i = 0;
    int j = 0;
    int item_level = many_many;

    for (i = 0; i < 6; i++)
    {
        if (i == 5)
            return;
        if (env.sh_type[i] == 100)
            break;
    }

    env.keeper_name[i][0] = random3(200) + 1;
    env.keeper_name[i][1] = random3(200) + 1;
    env.keeper_name[i][2] = random3(200) + 1;

    env.sh_level[i] = many_many * 2;

    if (force_s_type == 100)
    {
        env.sh_type[i] = random() % 12;
    }
    else
        env.sh_type[i] = force_s_type;

    if (env.sh_type[i] != 2 && env.sh_type[i] != 3 && env.sh_type[i] != 4)
        env.sh_greed[i] = 10 + random3(5) + random3(many_many / 2);
    else
        env.sh_greed[i] = 15 + random3(10) + random3(10) + random3(many_many);

    int plojy = 5 + random3(5) + random3(5) + random3(4);

    for (j = 0; j < plojy; j++)
    {
        if (env.sh_type[i] != 2 && env.sh_type[i] != 3 && env.sh_type[i] != 4)
            item_level = many_many + random() % ((many_many + 1) * 2);
        else
            item_level = many_many + random() % ((many_many + 1) * 3);

        if (random3(4) == 0)
            item_level = 351;
//      orb = items(0, 1, item_in_shop(env.sh_type [i]), 250, 0, item_level, 250);
        orb = items(1, item_in_shop(env.sh_type[i]), 250, 0, item_level, 250);
        mitm.x[orb] = 0;
        mitm.y[orb] = 5 + i;
        if (env.sh_type[i] != 2 && env.sh_type[i] != 3 && env.sh_type[i] != 4)
            mitm.id[orb] = 3;
    }


    env.sh_x[i] = shop_x;
    env.sh_y[i] = shop_y;

    grd[shop_x][shop_y] = 80;

}


char item_in_shop(char shop_type)
{

    switch (shop_type)
    {
    case 0:
        if (random() % 3 == 0)
            return 1;
        return 0;
    case 1:
        return 2;
    case 2:
        return 0;
    case 3:
        return 2;
    case 4:
        return item_in_shop(random() % 10);
    case 5:
        return 7;
    case 6:
        return 3;
    case 7:
        return 10;
    case 8:
        return 4;
    case 9:
        return 5;
    case 10:
        return 6;
    case 11:
        return item_in_shop(random() % 10);

    }

    return 0;

}



int treasure_area(
                     int many_many,
                     unsigned char ta1_x,
                     unsigned char ta2_x,
                     unsigned char ta1_y,
                     unsigned char ta2_y)
{
    int cx = 0;
    int cy = 0;
    int item_made = 0;

    ta2_x++;
    ta2_y++;

    if (ta2_x <= ta1_x)
        return 0;
    if (ta2_y <= ta1_y)
        return 0;

    if ((ta2_x - ta1_x) * (ta2_y - ta1_y) >= 40)
        return 0;

    for (cx = ta1_x; cx < ta2_x; cx++)
    {
        for (cy = ta1_y; cy < ta2_y; cy++)
        {
            if (grd[cx][cy] != 67)
                continue;
            if (random3(2) == 0)
                continue;
            item_made = items(1, 250, 250, 1, random3(many_many * 2), 250);
            mitm.x[item_made] = cx;
            mitm.y[item_made] = cy;
        }
    }

    return 1;

}


void hide_doors(void)
{
    char dx = 0;
    char dy = 0;

    for (dx = 0; dx < 80; dx++)
    {
        for (dy = 0; dy < 80; dy++)
        {
            if (((grd[dx - 1][dy] == 1) + (grd[dx + 1][dy] == 1) + (grd[dx][dy - 1] == 1) + (grd[dx][dy + 1] == 1)) >= 2)
                if (grd[dx][dy] == 3 && random3(3) == 0)
                    grd[dx][dy] = 5;
        }
    }

}

void chequerboard(unsigned char cheq1, unsigned char cheq2, unsigned char deleted, unsigned char chx1, unsigned char chy1, unsigned char chx2, unsigned char chy2)
{

    int i, j;

    if (chx1 >= chx2)
        return;
    if (chy1 >= chy2)
        return;

    for (i = chx1; i < chx2; i++)
    {
        for (j = chy1; j < chy2; j++)
        {
            if (grd[i][j] == deleted)
            {
                if ((i + j) % 2 == 0)
                    grd[i][j] = cheq1;
                else
                    grd[i][j] = cheq2;
            }
        }
    }

}



void spotty_level(char seeded, int iterations, char boxy)
{

// assumes starting with a level full of rock walls (1)

    int i, j, k, l;

    if (seeded == 0)
    {
        for (i = 82; i < 89; i++)
        {
            if (i == 85 || i == 86)
                continue;
            do
            {
                j = random3(60) + 10;
                k = random3(50) + 10;
            }
            while (grd[j][k] != 1 && grd[j + 1][k] != 1);
            grd[j][k] = i;
            if (i == 82)
                grd[j + 1][k] = 86;
            if (grd[j][k - 1] == 1)
                grd[j][k - 1] = 67;
            if (grd[j][k + 1] == 1)
                grd[j][k + 1] = 67;
            if (grd[j - 1][k] == 1)
                grd[j - 1][k] = 67;
            if (grd[j + 1][k] == 1)
                grd[j + 1][k] = 67;
        }
    }                           // end if seeded

    l = iterations;

    if (l == 0)
        l = 200 + random3(1500);

    for (i = 0; i < l; i++)
    {
        do
        {
            j = random3(60) + 10;
            k = random3(50) + 10;
        }
        while (grd[j][k] == 1 && grd[j - 1][k] == 1 && grd[j + 1][k] == 1 && grd[j][k - 1] == 1 && grd[j][k + 1] == 1 && grd[j - 2][k] == 1 && grd[j + 2][k] == 1 && grd[j][k - 2] == 1 && grd[j][k + 2] == 1);         // && grd [j - 1] [k - 1] == 1 && grd [j + 1] [k - 1] == 1 && grd [j + 1] [k + 1] == 1 && grd [j - 1] [k + 1] == 1);

        if (grd[j][k] == 1)
            grd[j][k] = 67;
        if (grd[j][k - 1] == 1)
            grd[j][k - 1] = 67;
        if (grd[j][k + 1] == 1)
            grd[j][k + 1] = 67;
        if (grd[j - 1][k] == 1)
            grd[j - 1][k] = 67;
        if (grd[j + 1][k] == 1)
            grd[j + 1][k] = 67;
        if (boxy == 1)
        {
            if (grd[j - 1][k - 1] == 1)
                grd[j][k - 1] = 67;
            if (grd[j + 1][k + 1] == 1)
                grd[j][k + 1] = 67;
            if (grd[j - 1][k + 1] == 1)
                grd[j - 1][k] = 67;
            if (grd[j + 1][k - 1] == 1)
                grd[j + 1][k] = 67;
        }
    }
}



void bigger_room(void)
{
    int i, j;

    for (i = 10; i < 70; i++)
    {
        for (j = 10; j < 60; j++)
        {
            if (grd[i][j] == 1)
                grd[i][j] = 67;
        }
    }

    many_pools(62);

    char pos[2];

    for (bj = 0; bj < 3 + random3(2); bj++)
    {
        for (bi = 0; bi < 2; bi++)
        {
            do
            {
                pos[0] = random3(60) + 10;
                pos[1] = random3(50) + 10;
            }
            while (grd[pos[0]][pos[1]] != 67);

            if (bi == 0)
                grd[pos[0]][pos[1]] = 82 + bj;
            else
                grd[pos[0]][pos[1]] = 86 + bj;

        }                       // end for i

    }                           // end for j

}



void place_pool(unsigned char pool_type, unsigned char pool_x1, unsigned char pool_y1, unsigned char pool_x2, unsigned char pool_y2)
{

    int i, j;

    unsigned char left_edge, right_edge;

    if (pool_x1 >= pool_x2 - 4)
        return;
    if (pool_y1 >= pool_y2 - 4)
        return;

    left_edge = pool_x1 + 2 + random3(pool_x2 - pool_x1);
    right_edge = pool_x2 - 2 - random3(pool_x2 - pool_x1);


    for (j = pool_y1 + 1; j < pool_y2 - 1; j++)
    {
        for (i = pool_x1 + 1; i < pool_x2 - 1; i++)
        {
            if (i >= left_edge && i <= right_edge && grd[i][j] == 67)
                grd[i][j] = pool_type;
        }
        if ((j - pool_y1 < (pool_y2 - pool_y1) / 2 || random3(4) == 0) && left_edge > pool_x1 + 1)
            left_edge -= random3(3);
        if ((j - pool_y1 < (pool_y2 - pool_y1) / 2 || random3(4) == 0) && right_edge < pool_x2 - 1)
            right_edge += random3(3);
        if ((j - pool_y1 >= (pool_y2 - pool_y1) / 2 || random3(4) == 0 || left_edge <= pool_x1 + 2) && left_edge < pool_x2 - 1)
            left_edge += random3(3);
        if ((j - pool_y1 >= (pool_y2 - pool_y1) / 2 || random3(4) == 0 || right_edge >= pool_x2 - 2) && right_edge > pool_x1 + 1)
            right_edge -= random3(3);

    }

}


void many_pools(unsigned char pool_type)
{

    int pools = 0;
    int i = 0, j = 0, k = 0, l = 0;
    int m = 0, n = 0;
    int no_pools = 20 + random3(5) + random3(5);
    int timeout = 0;

    do
    {
        timeout++;
        if (timeout >= 30000)
            break;
        i = 10 + random3(50);
        j = 10 + random3(40);
        k = i + 4 + random3(8) + random3(7);
        l = j + 4 + random3(8) + random3(7);
        for (m = i; m < k; m++)
        {
            for (n = j; n < l; n++)
            {
                if (grd[m][n] != 67)
                    goto continue_pools;
            }
        }
        place_pool(pool_type, i, j, k, l);
        pools++;
continue_pools:
        continue;
    }
    while (pools < no_pools);

}


void generate_abyss(void)
{

    int i, j;

    unsigned char replaced[5];

    for (i = 0; i < 5; i++)
    {
        replaced[i] = 1;
        if (random() % 3 == 0)
            replaced[i] = 2;
        if (random() % 10 == 0)
            replaced[i] = 4;
        if (random() % 1000 == 0)
            replaced[i] = 3;
    }


    for (i = 5; i < 75; i++)
    {
        for (j = 5; j < 65; j++)
        {
            if (random() % 4 == 0)
                grd[i][j] = replaced[random() % 5];
            else
                grd[i][j] = 67;
        }
    }


    grd[45][35] = 67;

}


void clear_area(unsigned char xr1, unsigned char yr1, unsigned char xr2, unsigned char yr2, unsigned char deleting, unsigned char replacing)
{

// first coordinates *must* be top left

    int rcountx = 0;
    int rcounty = 0;

    for (rcountx = xr1; rcountx < xr2; rcountx++)
    {
        for (rcounty = yr1; rcounty < yr2; rcounty++)
        {
            if (grd[rcountx][rcounty] == deleting)
                grd[rcountx][rcounty] = replacing;
        }
    }

}

void plan_main(char force_plan)
{

    char do_stairs = 0;

    char pos[2];

    unsigned char special_grid = 2;

    if (random() % 3 == 0)
        special_grid = 4;

// do_stairs:
    // 0 - stairs already done
    // 1 - stairs already done, do spotty
    // 2 - no stairs
    // 3 - no stairs, do spotty

    if (force_plan == 0)
        force_plan = random3(12) + 1;

    switch (force_plan)
    {
    case 1:
        do_stairs = plan_1();
        break;
    case 2:
        do_stairs = plan_2();
        break;
    default:
    case 3:
        do_stairs = plan_3();
        break;
    case 4:
        do_stairs = plan_4(0, 0, 0, 0, 99);
        break;                  // city

    case 5:
        if (random() % 9 != 0)
            do_stairs = plan_3();
        else
            do_stairs = plan_5();
        break;
    case 6:
        do_stairs = plan_6();
        break;
    }

    if (do_stairs == 3 || do_stairs == 1)
        spotty_level(1, 0, random() % 2);


    if (do_stairs == 2 || do_stairs == 3)
        for (bj = 0; bj < 3 + random3(2); bj++)
        {
            for (bi = 0; bi < 2; bi++)
            {
                do
                {
                    pos[0] = random3(60) + 10;
                    pos[1] = random3(50) + 10;
                }
                while (grd[pos[0]][pos[1]] != 67);

                if (bi == 0)
                    grd[pos[0]][pos[1]] = 82 + bj;
                else
                    grd[pos[0]][pos[1]] = 86 + bj;

            }                   // end for i

        }                       // end for j


    if (random() % 20 == 0)
    {
        for (bi = 0; bi < 80; bi++)
        {
            for (bj = 0; bj < 70; bj++)
            {
                if (grd[bi][bj] == 1)
                    grd[bi][bj] = special_grid;
            }
        }
    }
}


char plan_1(void)
{

    char width = 10;
    char width2 = 5;

    if (random() % 2 == 0)
        width2 -= random() % 5;
    width -= random() % 7;

    clear_area(10, 10, 70, 10 + width, 1, 67);
    clear_area(10, 60 - width, 70, 60, 1, 67);

    clear_area(10, 10, 10 + width, 60, 1, 67);
    clear_area(60 - width, 10, 70, 60, 1, 67);

    if (random() % 4 == 0)
        return 2;
    if (random() % 3 == 0)
        return 3;

    clear_area(10, 35 - width2, 70, 35 + width2, 1, 67);
    clear_area(40 - width2, 10, 40 + width2, 60, 1, 67);

    if (random() % 4 == 0)
        return 2;
    if (random() % 3 == 0)
        return 3;

    room_x1 = 25;
    room_y1 = 25;
    room_x2 = 55;
    room_y2 = 45;


    if (random() % 2 == 0)
    {
        oblique_max = random() % 20 + 5;
    }

    if (random() % 3 == 0)
    {
        octa_room(67);
    }
    else
    {
        if (random() % 5 == 0)
        {
            octa_room(61 + random() % 2);
        }
    }

    if (random() % 5 == 0)
        return 3;

    return 2;

}

char plan_2(void)               // just a cross
 {

    char width2 = 5;

    width2 -= random() % 5;

    clear_area(10, 35 - width2, 70, 35 + width2, 1, 67);
    clear_area(40 - width2, 10, 40 + width2, 60, 1, 67);

    if (random() % 4 == 0)
        return 2;

    return 3;

}

char plan_3(void)
{

/* Draws a room, then another and links them together, then another and etc
   Of course, this can easily end up looking just like a make_trail level. */


    char cnx, cny;
    char roomsss = 30 + random() % 90;
    char exclusive = 1;

    if (random() % 10 == 0)
        exclusive = 0;

    char exclusive2 = 1;

    if (random() % 2 == 0)
        exclusive2 = 0;

    char romx1[30], romy1[30], romx2[30], romy2[30];

    char which_room = 0;

    for (bi = 0; bi < roomsss; bi++)
    {
        romx1[which_room] = 10 + random() % 50;
        romy1[which_room] = 10 + random() % 40;
        romx2[which_room] = romx1[which_room] + 2 + random() % 8;
        romy2[which_room] = romy1[which_room] + 2 + random() % 8;

        if (exclusive == 1)
        {
            for (cnx = romx1[which_room] - 1; cnx < romx2[which_room] + 1; cnx++)
            {
                for (cny = romy1[which_room] - 1; cny < romy2[which_room] + 1; cny++)
                {
                    if (grd[cnx][cny] != 1)
                        goto continuing;
                }
            }
        }

        clear_area(romx1[which_room], romy1[which_room], romx2[which_room], romy2[which_room], 1, 67);

        if (which_room > 0 && exclusive2 == 0)
        {

            join_the_dots(romx1[which_room] + random() % (romx2[which_room] - romx1[which_room]), romy1[which_room] + random() % (romy2[which_room] - romy1[which_room]), romx1[which_room - 1] + random() % (romx2[which_room - 1] - romx1[which_room - 1]), romy1[which_room - 1] + random() % (romy2[which_room - 1] - romy1[which_room - 1]), 0, 0, 0, 0);

        }


        which_room++;
        if (which_room >= 29)
            break;

continuing:
        continue;       // next bi loop
    }

    if (exclusive2 == 1)
        for (bi = 0; bi < which_room; bi++)
        {
            if (bi > 0)
                join_the_dots(romx1[bi] + random() % (romx2[bi] - romx1[bi]), romy1[bi] + random() % (romy2[bi] - romy1[bi]), romx1[bi - 1] + random() % (romx2[bi - 1] - romx1[bi - 1]), romy1[bi - 1] + random() % (romy2[bi - 1] - romy1[bi - 1]), 0, 0, 0, 0);
        }

    return 2;

}


char plan_4(char forbid_x1, char forbid_y1, char forbid_x2, char forbid_y2, unsigned char force_wall)
{

// a more chaotic version of city level

    int number_boxes = 5000;

    if (random3(3) == 0)
        number_boxes -= random3(1000);
    if (random3(3) == 0)
        number_boxes -= random3(1000);
    if (random3(3) == 0)
        number_boxes -= random3(1000);
    if (random3(3) == 0)
        number_boxes -= random3(1000);

    unsigned char drawing = 1;

    char b1x, b1y, b2x, b2y;

    char cnx, cny;

    if (random() % 3 == 0)
        drawing = 2;
    if (random() % 6 == 0)
        drawing = 4;

    if (force_wall != 99)
        drawing = force_wall;

    char boxy_type = 0;

    if (random() % 3 == 0)
        boxy_type = 1;


    clear_area(10, 10, 70, 60, 1, 67);

    // clear_area can also be used to fill in:

    for (bi = 0; bi < number_boxes; bi++)
    {

        b1x = 11 + random() % 45;
        b1y = 11 + random() % 35;

        b2x = b1x + 3 + random() % 7 + random() % 5;
        b2y = b1y + 3 + random() % 7 + random() % 5;

        if (forbid_x1 != 0 || forbid_x2 != 0)
        {
            if (b1x <= forbid_x2 && b1x >= forbid_x1 && b1y <= forbid_y2 && b1y >= forbid_y1)
                goto continuing;
            if (b2x <= forbid_x2 && b2x >= forbid_x1 && b2y <= forbid_y2 && b2y >= forbid_y1)
                goto continuing;
        }

        for (cnx = b1x - 1; cnx < b2x + 1; cnx++)
        {
            for (cny = b1y - 1; cny < b2y + 1; cny++)
            {
                if (grd[cnx][cny] != 67)
                    goto continuing;
            }
        }

        if (force_wall == 99)
        {
            if (random() % 4 == 0)
                drawing = 1;
            if (random() % 10 == 0)
                drawing = 2;
            if (random() % 30 == 0)
                drawing = 4;
        }

        if (random() % 7 == 0)
            clear_area(b1x, b1y, b2x, b2y, 67, drawing);
        else if (random() % 10 == 0)
            box_room(b1x, b2x - 1, b1y, b2y - 1, drawing);
        else if (boxy_type == 0)
            clear_area(b1x, b1y, b2x, b2y, 67, drawing);
        else
            box_room(b1x, b2x - 1, b1y, b2y - 1, drawing);

continuing:
        continue;
    }

    if (random() % 4 == 0 && forbid_x1 == 0)    // a market square

    {
        room_x1 = 25;
        room_y1 = 25;
        room_x2 = 55;
        room_y2 = 45;


        if (random() % 4 != 0)
        {
            oblique_max = random() % 20 + 5;
        }
        if (random() % 10 != 0)
            octa_room(67);
        else
            octa_room(61 + random() % 2);
    }

    return 2;

}

char plan_5(void)
{

    char glop = 0;
    char glop2 = 5 + random() % 20;

    do
    {

        join_the_dots(random() % 60 + 10, random() % 50 + 10, random() % 60 + 10, random() % 50 + 10, 0, 0, 0, 0);

        glop++;

    }
    while (glop < glop2);

    if (random() % 4 != 0)
        spotty_level(1, 100, random() % 2);

    return 2;

}

char plan_6(void)
{

// circle of standing stones (well, kind of)

    room_x1 = 10;
    room_x2 = 70;
    room_y1 = 10;
    room_y2 = 60;

    oblique_max = 14;           //5 + random() % 10;

    octa_room(67);

    clear_area(23, 23, 26, 26, 67, 2);
    clear_area(23, 47, 26, 50, 67, 2);

    clear_area(55, 23, 58, 26, 67, 2);
    clear_area(55, 47, 58, 50, 67, 2);

    clear_area(39, 20, 43, 23, 67, 2);
    clear_area(39, 50, 43, 53, 67, 2);

    clear_area(20, 30, 23, 33, 67, 2);
    clear_area(20, 40, 23, 43, 67, 2);

    clear_area(58, 30, 61, 33, 67, 2);
    clear_area(58, 40, 61, 43, 67, 2);

    grd[35][32] = 2;
    grd[46][32] = 2;

    grd[35][40] = 2;
    grd[46][40] = 2;

    grd[69][34] = 82;
    grd[69][35] = 83;
    grd[69][36] = 84;

    grd[10][34] = 86;
    grd[10][35] = 87;
    grd[10][36] = 88;

    if (many_many > 20 && random() % 2 == 0)
    {
        grd[40][36] = 96;       // remember pandemonium

        grd[41][36] = 96;
    }

    return 0;

}


void join_the_dots(unsigned char dotx1, unsigned char doty1, unsigned char dotx2, unsigned char doty2, char forbid_x1, char forbid_y1, char forbid_x2, char forbid_y2)
{

    if (dotx1 == dotx2 && doty1 == doty2)
        return;

    char atx = dotx1, aty = doty1;

    int join_count = 0;

    grd[atx][aty] = 67;
    do
    {

        join_count++;
        if (join_count > 10000)
            return;             // just insurance

        if (atx < dotx2 && (forbid_x1 == 0 || (atx + 1 < forbid_x1 || atx + 1 > forbid_x2 || (aty > forbid_y2 || aty < forbid_y1))))
        {
            atx++;
            goto continuing;
        }

        if (atx > dotx2 && (forbid_x2 == 0 || (atx - 1 > forbid_x2 || atx - 1 < forbid_x1 || (aty > forbid_y2 || aty < forbid_y1))))
        {
            atx--;
            goto continuing;
        }

        if (aty > doty2 && (forbid_y2 == 0 || (aty - 1 > forbid_y2 || aty - 1 < forbid_y1 || (atx > forbid_x2 || atx < forbid_x1))))
        {
            aty--;
            goto continuing;
        }

        if (aty < doty2 && (forbid_y1 == 0 || (aty + 1 < forbid_y1 || aty + 1 > forbid_y2 || (atx > forbid_x2 || atx < forbid_x1))))
        {
            aty++;
            goto continuing;
        }

continuing:
        grd[atx][aty] = 67;
    }
    while (atx != dotx2 || aty != doty2);


}


void build_vaults(int force_vault)
{

// for some weird reason can't put a vault on level 1, because monster equip
    //  isn't generated.

    int altar_count = 0;
    char stair_exist[10];
    char stx, sty;


    char acq_item_class[7];

    acq_item_class[0] = 0;
    acq_item_class[1] = 2;
    acq_item_class[2] = 0;
    acq_item_class[3] = 7;
    acq_item_class[4] = 10;
    acq_item_class[5] = 11;
    acq_item_class[6] = 13;

//int place_a_monster = 0;
    //int monster_level = 0;
    //int monster_type_thing = 0;

    int mons_array[7];

    char roomsss = 10 + random() % 90;
    char exclusive = 1;
    char which_room = 0;

    char vgrid[81][81];

    char gluggy = vault_main(vgrid, mons_array, force_vault, many_many);
    char exclusive2 = 1;

    int vx, vy;

    int v1x = 0, v1y = 0, v2x = 0, v2y = 0;

//int item_made;

    char dig_dir_x = 0;
    char dig_dir_y = 0;
    char dig_place_x = 0;
    char dig_place_y = 0;

// note: assumes *no* previous item (I think) or monster (definitely) placement

    for (vx = 0; vx < 80; vx++)
    {
        for (vy = 0; vy < 70; vy++)
        {
            altar_count = vault_grid(vx, vy, altar_count, acq_item_class, mons_array, vgrid[vy][vx]);
        }
    }


    switch (gluggy)
    {
    case 1:                     // top half of map

        v1x = 1;
        v2x = 80;
        v1y = 1;
        v2y = 35;
        vsy++;
        dig_dir_x = 0;
        dig_dir_y = 1;
        break;
    case 2:                     // top left of map

        v1x = 1;
        v2x = 40;
        v1y = 1;
        v2y = 35;
        vsy++;
        dig_dir_x = 1;
        dig_dir_y = 0;
        break;
    case 3:                     // top right of map

        v1x = 40;
        v2x = 80;
        v1y = 1;
        v2y = 35;
        vsy++;
        dig_dir_x = -1;
        dig_dir_y = 0;
        break;
    case 4:                     // lower left of map

        v1x = 1;
        v2x = 40;
        v1y = 35;
        v2y = 70;
        vsy--;
        dig_dir_x = 0;
        dig_dir_y = -1;
        break;
    case 5:                     // lower right of map

        v1x = 40;
        v2x = 80;
        v1y = 35;
        v2y = 70;
        vsy--;
        dig_dir_x = 0;
        dig_dir_y = -1;
        break;
    case 6:                     // full map - must include all stairs

        goto full_screen;
    case 7:                     // upper, fill in with plan_4 (Dis); can't have grd 1 here

        v1x = 1;
        v2x = 80;
        v1y = 1;
        v2y = 35;
        plan_4(1, 1, 80, 35, 4);
        goto vstair;

    }


    char cnx, cny;

    if (random() % 10 == 0)
        exclusive = 0;

    if (random() % 2 == 0)
        exclusive2 = 0;

    char romx1[30], romy1[30], romx2[30], romy2[30];


    for (bi = 0; bi < roomsss; bi++)
    {

        do
        {
            romx1[which_room] = 10 + random() % 50;
            romy1[which_room] = 10 + random() % 40;
            romx2[which_room] = romx1[which_room] + 2 + random() % 8;
            romy2[which_room] = romy1[which_room] + 2 + random() % 8;
        }
        while ((romx1[which_room] >= v1x && romx1[which_room] <= v2x && romy1[which_room] >= v1y && romy1[which_room] <= v2y) || (romx2[which_room] >= v1x && romx2[which_room] <= v2x && romy2[which_room] >= v1y && romy2[which_room] <= v2y));

        if (bi == 0)
            join_the_dots(vsx, vsy, romx1[which_room], romy1[which_room], v1x, v1y, v2x, v2y);
        else
        {
            if (exclusive == 1)
            {
                for (cnx = romx1[which_room] - 1; cnx < romx2[which_room] + 1; cnx++)
                {
                    for (cny = romy1[which_room] - 1; cny < romy2[which_room] + 1; cny++)
                    {
                        if (grd[cnx][cny] != 1)
                            goto continuing;
                    }
                }
            }
        }

        clear_area(romx1[which_room], romy1[which_room], romx2[which_room], romy2[which_room], 1, 67);

        if (which_room > 0)     // && exclusive2 == 0)

        {
            join_the_dots(romx1[which_room] + random() % (romx2[which_room] - romx1[which_room]), romy1[which_room] + random() % (romy2[which_room] - romy1[which_room]), romx1[which_room - 1] + random() % (romx2[which_room - 1] - romx1[which_room - 1]), romy1[which_room - 1] + random() % (romy2[which_room - 1] - romy1[which_room - 1]), v1x, v1y, v2x, v2y);
        }


        which_room++;
        if (which_room >= 29)
            break;

      continuing:continue;      // next bi loop

    }

vstair:
    dig_place_x = vsx;
    dig_place_y = vsy;

    if (gluggy != 7)
        for (bi = 0; bi < 40; bi++)
        {
            dig_place_x += dig_dir_x;
            dig_place_y += dig_dir_y;
            if (dig_place_x < 10 || dig_place_x > 70 || dig_place_y < 10 || dig_place_y > 60)
                break;
            if (grd[dig_place_x][dig_place_y] == 1)
                grd[dig_place_x][dig_place_y] = 67;
        }

    int pos[2];

    for (stx = 0; stx < 10; stx++)
    {
        stair_exist[stx] = 0;
    }

    for (stx = 0; stx < 80; stx++)
    {
        for (sty = 0; sty < 70; sty++)
        {
            if (grd[stx][sty] >= 82 && grd[stx][sty] <= 89)
                stair_exist[grd[stx][sty] - 82] = 1;
        }
    }


    if (you.where_are_you == 1)
    {
        for (sty = 0; sty < 5; sty++)
        {
            stair_exist[sty] = 1;
        }
        for (sty = 6; sty < 10; sty++)
        {
            stair_exist[sty] = 0;
        }
    }


    for (bj = 0; bj < 3 + random3(2); bj++)
    {
        for (bi = 0; bi < 2; bi++)
        {

            if (stair_exist[(82 + bj + (bi * 4)) - 82] == 1)
                continue;

            do
            {
                pos[0] = random3(60) + 10;
                pos[1] = random3(50) + 10;
            }
            while (grd[pos[0]][pos[1]] != 67 || (pos[0] >= v1x && pos[0] <= v2x && pos[1] >= v1y && pos[1] <= v2y));

            if (bi == 0)
                grd[pos[0]][pos[1]] = 82 + bj;
            else
                grd[pos[0]][pos[1]] = 86 + bj;

        }                       // end for i

    }                           // end for j

full_screen:
    return;
}



void build_minivaults(int force_vault)
{
// for some weird reason can't put a vault on level 1, because monster equip
    //  isn't generated.

    int altar_count = 0;

    char acq_item_class[7];

    acq_item_class[0] = 0;
    acq_item_class[1] = 2;
    acq_item_class[2] = 0;
    acq_item_class[3] = 7;
    acq_item_class[4] = 10;
    acq_item_class[5] = 11;
    acq_item_class[6] = 13;

    int mons_array[7];

    char vgrid[81][81];

    if (force_vault == 200)
        force_vault = 200 + random3(34);

//char gluggy =
    vault_main(vgrid, mons_array, force_vault, many_many);

    int vx, vy;
    int v1x, v1y;

/* find a target area which can be safely overwritten: */
    do
    {
// if (random3(1000) == 0) return;
        v1x = 12 + random3(45);
        v1y = 12 + random3(35);
        for (vx = v1x; vx < v1x + 12; vx++)
        {
            for (vy = v1y; vy < v1y + 12; vy++)
            {
                if (random3(2000) == 0)
                    return;
                if ((grd[vx][vy] != 67 && grd[vx][vy] != 1 && grd[vx][vy] != 3 && grd[vx][vy] != 5) || igrd[vx][vy] != 501 || mgrd[vx][vy] != MNG)
                    goto out_of_check;
            }
        }
        /* must not be completely isolated: */
        for (vx = v1x; vx < v1x + 12; vx++)
        {
//  if (vx != v1x && vx != v1x + 12) continue;
            for (vy = v1y; vy < v1y + 12; vy++)
            {
//   if (vy != v1y && vy != v1y + 12) continue;
                if (grd[vx][vy] == 67 || grd[vx][vy] == 3 || grd[vx][vy] == 5)
                    goto break_out;
            }
        }

out_of_check:
        continue;

break_out:
        break;
    }
    while (1);

    for (vx = v1x; vx < v1x + 12; vx++)
    {
        for (vy = v1y; vy < v1y + 12; vy++)
        {
            grd[vx][vy] = vgrid[vx - v1x][vy - v1y];
        }
    }

/* note: assumes *no* previous item (I think) or monster (definitely) placement */
    for (vx = v1x; vx < v1x + 12; vx++)
    {
        for (vy = v1y; vy < v1y + 12; vy++)
        {
            altar_count = vault_grid(vx, vy, altar_count, acq_item_class, mons_array, grd[vx][vy]);
        }
    }

}



int vault_grid(int vx, int vy, int altar_count, char acq_item_class[7], int mons_array[10], char vgrid)
{
    int item_made = 501;
    int place_a_monster = 0;
    int monster_type_thing = 250;
    int passed[2];
    int monster_level = many_many;

    switch (vgrid)
    {
    case 'x':
        grd[vx][vy] = 1;
        break;
    case 'c':
        grd[vx][vy] = 2;
        break;
    case 'v':
        grd[vx][vy] = 4;
        break;
    case 'b':
        grd[vx][vy] = 6;
        break;
    case 'a':
        grd[vx][vy] = 8;
        break;
    case '.':
        grd[vx][vy] = 67;
        break;
    case '+':
        grd[vx][vy] = 3;
        break;
    case '=':
        grd[vx][vy] = 5;
        break;
    case 'w':
        grd[vx][vy] = 62;
        break;
    case 'l':
        grd[vx][vy] = 61;
        break;
    case '>':
        grd[vx][vy] = 85;
        break;
    case '<':
        grd[vx][vy] = 89;
        break;
    case '}':
        grd[vx][vy] = 82;
        break;
    case '{':
        grd[vx][vy] = 86;
        break;
    case ')':
        grd[vx][vy] = 83;
        break;
    case '(':
        grd[vx][vy] = 87;
        break;
    case ']':
        grd[vx][vy] = 84;
        break;
    case '[':
        grd[vx][vy] = 88;
        break;
    case 'A':
        grd[vx][vy] = 98;
        break;                  // Empty archway to Hell (opened by Horn)

    case 'B':
        grd[vx][vy] = 180 + altar_count;
        altar_count++;
//                      if (altar_count == 3) altar_count ++;
        //                      if (altar_count == 10) altar_count ++;
        break;
    case 'C':
        do
        {
            grd[vx][vy] = 180 + random3(12);
        }
        while (grd[vx][vy] == 183 || grd[vx][vy] == 185 || grd[vx][vy] == 190);
        break;
    case 'I':
        grd[vx][vy] = 7;
        break;                  // orcish idol

    case 'R':
        grd[vx][vy] = 67;       // honey / Royal Jelly

        item_made = items(1, 4, 5 + (random3(3) == 0), 1, many_many, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;
    case 'S':
        grd[vx][vy] = 21;
        break;                  // silver statue

    case 'T':
        grd[vx][vy] = 200;
        break;                  // water fountain

    case 'U':
        grd[vx][vy] = 202;
        break;                  // magic fountain

    case 'V':
        grd[vx][vy] = 210;
        break;                  // dry fountain

    case 'G':
        grd[vx][vy] = 22;
        break;                  // granite statue

    case 'H':
        grd[vx][vy] = 23;
        break;                  // crystal statue

    case '$':
        grd[vx][vy] = 67;
        item_made = items(1, 15, 250, 1, many_many, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;
    case '%':
        grd[vx][vy] = 67;
        item_made = items(1, 250, 250, 1, many_many, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;
    case '*':
        grd[vx][vy] = 67;
        item_made = items(1, 250, 250, 1, many_many * 2 + 5, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;
    case '|':
        grd[vx][vy] = 67;
        item_made = items(1, acq_item_class[random() % 7], 250, 1, 351, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;

    case 'P':                   // maybe rune of Zot

        if (random3(3) != 0)
        {
            grd[vx][vy] = 67;
            item_made = items(1, acq_item_class[random() % 7], 250, 1, 351, 250);
            mitm.x[item_made] = vx;
            mitm.y[item_made] = vy;
            break;
        }
        // fall through

    case 'O':                   // rune of zot

        grd[vx][vy] = 67;
/*   orb_type = 0; // 52 - Gehenna
   if (force_vault == 53) orb_type = 1;
   if (force_vault == 51) orb_type = 3;
   if (force_vault == 54) orb_type = 2;
   if (force_vault == 60) orb_type = 20;
   if (force_vault == 61) orb_type = 21;
   if (force_vault == 62) orb_type = 22;
   if (force_vault == 63) orb_type = 23; */
        item_made = items(1, 13, 14, 1, 351, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;
    case 'Z':                   // orb of zot

        grd[vx][vy] = 67;
        item_made = items(1, 12, 0, 1, 351, 250);
        mitm.x[item_made] = vx;
        mitm.y[item_made] = vy;
        break;

    case '0':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;
        monster_type_thing = 250;
        break;
    case '9':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many + 5;
        monster_type_thing = 250;
        break;
    case '8':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = (many_many + 2) * 2;
        monster_type_thing = 250;
        break;
    case '@':
        grd[vx][vy] = 67;
        vsx = vx;
        vsy = vy;
        break;

    case '^':
        if (place_specific_trap(vx, vy, 100) == 0)
            grd[vx][vy] = 67;
        break;

    case '1':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[0];
        break;
    case '2':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[1];
        break;
    case '3':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[2];
        break;
    case '4':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[3];
        break;
    case '5':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[4];
        break;
    case '6':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[5];
        break;
    case '7':
        grd[vx][vy] = 67;
        place_a_monster = 1;
        monster_level = many_many;      // this probably affects give_item

        monster_type_thing = mons_array[6];
        break;
    }


    if (place_a_monster == 1)
    {
        if (monster_level >= 30)
            monster_level = 30; // makes really high level monsters (titans etc) more common here

        passed[1] = 1;
        place_monster(
                         250,
                         monster_type_thing,
                         1,
                         vx,
                         vy,
                         0,
                         MHITNOT,
                         0,
                         monster_level,
                         passed);
    }
    place_a_monster = 0;
    monster_type_thing = 250;

    return altar_count;

}



void place_curse_skull(void)
{

    int passed[2];

    int px, py;
    int i, j;
    int k = 0;
    int l = 0;

    do
    {
rand_px:
        px = 15 + random3(55);
        py = 15 + random3(45);
        k++;
        if (k == 5000)
            return;
        l = 0;
        for (i = px - 4; i < px + 4; i++)
        {
            for (j = py - 4; j < py + 5; j++)
            {
                if (grd[i][j] == 67)
                    l++;
                if ((grd[i][j] != 1 && grd[i][j] != 3 && grd[i][j] != 5 && grd[i][j] != 67) || mgrd[i][j] != MNG)
                    goto rand_px;
            }
        }

        if (l == 0)
            goto rand_px;

        for (i = px - 4; i < px + 4; i++)
        {
            for (j = py - 4; j < py + 5; j++)
            {
                grd[i][j] = 67;
            }
        }

        passed[1] = 1;
        place_monster(
                         250,   //1, //plus_seventy,
                          361,  // typed,
                          1,    //type_place,
                          px,   //px,
                          py,   //py,
                          0,    //behaviour,
                          MHITNOT,      //hitting,
                          0,    //1,//allow_bands
                          many_many,
                         passed);

        return;

    }
    while (1);
}



void place_altar(void)
{

    int px, py;
    int i, j;
    int k = 0;
    int l = 0;

    int altar_type = 180;

    do
    {
        altar_type = 180 + random3(12);
    }
    while (altar_type == 183 || altar_type == 185 || altar_type == 190);

    do
    {
rand_px:
        px = 15 + random3(55);
        py = 15 + random3(45);
        k++;
        if (k == 5000)
            return;
        l = 0;
        for (i = px - 2; i < px + 3; i++)
        {
            for (j = py - 2; j < py + 3; j++)
            {
                if (grd[i][j] == 67)
                    l++;
                if ((grd[i][j] != 1 && grd[i][j] != 3 && grd[i][j] != 5 && grd[i][j] != 67) || mgrd[i][j] != MNG)
                    goto rand_px;
            }
        }

        if (l == 0)
            goto rand_px;

        for (i = px - 2; i < px + 3; i++)
        {
            for (j = py - 2; j < py + 3; j++)
            {
                grd[i][j] = 67;
            }
        }

        grd[px][py] = altar_type;

        return;

    }
    while (1);

}


void prepare_swamp(void)
{

    int i, j;

    for (i = 10; i < 70; i++)
    {
        for (j = 10; j < 60; j++)
        {
            if (grd[i][j] == 3 || grd[i][j] == 5)
                grd[i][j] = 67;
            if (grd[i][j] == 67 && random3(3) == 0)
                grd[i][j] = 65;
            if (grd[i][j] != 1)
                continue;
            if (random3(3) != 0)
                grd[i][j] = 62;
            if (random3(2) == 0)
                grd[i][j] = 65;
        }
    }

}


/* Gives water which is next to ground/shallow water a chance of being
 * shallow. Checks each water space.
 */
void prepare_water(void)
{

    int i, j;
    int k, l;

    for (i = 10; i < 70; i++)
    {
        for (j = 10; j < 60; j++)
        {
            if (grd[i][j] != 62)
                continue;
            for (k = -1; k < 2; k++)
            {
                for (l = -1; l < 2; l++)
                {
                    if (k == 0 && l == 0)
                        continue;
                    if (grd[i + k][j + l] != 62 && grd[i + k][j + l] != 65 && random3(6) != 0)
                    {
                        grd[i][j] = 65;
                        continue;
                    }
                    if (grd[i + k][j + l] == 65 && random3(8) == 0)
                    {
                        grd[i][j] = 65;
                        continue;
                    }
                }
            }
        }
    }

}

/* Checks how rare a weapon is. Many of these have special routines for
 * placement, especially those with a rarity of zero. Chance is out of 10.
 */
char rare_weapon(unsigned char w_type)
{

 switch(w_type)
 {
    case WPN_CLUB:
        return 10;

    case WPN_MACE:
        return 9;

    case WPN_FLAIL:
        return 8;

    case WPN_KNIFE:
        return 0; /* special routines for placing this one */

    case WPN_DAGGER:
        return 10;

    case WPN_MORNINGSTAR:
        return 8;

    case WPN_SHORT_SWORD:
        return 8;

    case WPN_LONG_SWORD:
        return 8;

    case WPN_GREAT_SWORD:
        return 6;

    case WPN_SCIMITAR:
        return 6;

    case WPN_HAND_AXE:
        return 9;

    case WPN_BATTLEAXE:
        return 6;

    case WPN_SPEAR:
        return 8;

    case WPN_TRIDENT:
        return 6;

    case WPN_HALBERD:
        return 5;

    case WPN_SLING:
        return 8;

    case WPN_BOW:
        return 8;

    case WPN_CROSSBOW:
        return 6;

    case WPN_HAND_CROSSBOW:
        return 4;

    case WPN_GLAIVE:
        return 5;

    case WPN_QUARTERSTAFF:
        return 9;

    case WPN_SCYTHE:
        return 2;

    case WPN_GIANT_CLUB:
        return 1;

    case WPN_GIANT_SPIKED_CLUB:
        return 1;

    case WPN_EVENINGSTAR:
        return 0;

    case WPN_QUICK_BLADE:
        return 0;

    case WPN_KATANA:
        return 0;

    case WPN_EXECUTIONERS_AXE:
        return 0;

    case WPN_DOUBLE_SWORD:
        return 0;

    case WPN_TRIPLE_SWORD:
        return 0;

    case WPN_HAMMER:
        return 8;

    case WPN_ANCUS:
        return 2;

    case WPN_WHIP:
        return 4;

    case WPN_SABRE:
        return 8;

    case WPN_DEMON_BLADE:
        return 0;

    case WPN_DEMON_WHIP:
        return 0;

    case WPN_DEMON_TRIDENT:
        return 0;

    case WPN_BROAD_AXE:
        return 6;

    case WPN_AXE:
        return 7;

    case WPN_SPIKED_FLAIL:
        return 6;

    case WPN_GREAT_MACE:
        return 3;

    case WPN_GREAT_FLAIL:
        return 3;

    default: return -1;

 }

}


/*
   void item_bugs(void)
   {

   int i = 0;
   int total_number = 0;

   for (i = 0; i < ITEMS; i ++)
   {
   if (mitm.quantity [i] <= 0) continue;
   total_number ++;
   itoa(i, st_prn, 10);
   cprintf("item ");
   cprintf(st_prn);
   cprintf(" x ");
   itoa(mitm.x [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", y ");
   itoa(mitm.y [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", c ");
   itoa(mitm.base_type [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", t ");
   itoa(mitm.sub_type [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", p ");
   itoa(mitm.pluses [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", p2 ");
   itoa(mitm.pluses2 [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", d ");
   itoa(mitm.special [i], st_prn, 10);
   cprintf(st_prn);
   cprintf(", q ");
   itoa(mitm.quantity [i], st_prn, 10);
   cprintf(st_prn);
   find_item(i);
   cprintf("\n\r");
   // itoa(mitm.y [i], st_prn, 10);
   if (total_number % 10 == 0)
   {
   cprintf("Waiting...\n\r");
   if (getch() == 0) getch();
   }

   }

   itoa(total_number, st_prn, 10);
   cprintf("Total: ");
   cprintf(st_prn);

   cprintf("Waiting...\n\r");
   if (getch() == 0) getch();

   clrscr();

   }


   void find_item(unsigned int found)
   {

   int i = 0;

   int x = 0;
   int y = 0;

   for (x = 0; x < 80; x ++)
   {
   for (y = 0; y < 70; y ++)
   {
   if (igrd [x] [y] == found)
   {
   cprintf(EOL"Item lying on floor at ");
   itoa(x, st_prn, 10);
   cprintf(st_prn);
   cprintf(", ");
   itoa(y, st_prn, 10);
   cprintf(st_prn);
   cprintf(".");
   }
   }
   }


   for (i = 0; i < ITEMS; i ++)
   {
   if (mitm.link [i] == found)
   {
   cprintf(EOL"Item linked from ");
   itoa(i, st_prn, 10);
   cprintf(st_prn);
   cprintf(".");
   }
   }

   for (x = 0; x < MNST; x ++)
   {
   for (y = 0; y < 8; y ++)
   {
   if (menv[x].inv [y] == found)
   {
   cprintf(EOL"Item carried by monster ");
   itoa(x, st_prn, 10);
   cprintf(st_prn);
   cprintf(" in inv slot ");
   itoa(y, st_prn, 10);
   cprintf(st_prn);
   cprintf(".");
   }
   }
   }

   }
 */
