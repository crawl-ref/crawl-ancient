/*
 *  File:       files.cc
 *  Summary:    Functions used to save and load levels/games.
 *  Written by: Linley Henzell and Alexey Guzeev
 *
 *  Change History (most recent first):
 *
 *      <5>     7/13/99         BWR             Monsters now regenerate hps
 *                                              off level & ghosts teleport
 *      <4>     6/13/99         BWR             Added tmp file pairs to
 *                                              save file.
 *      <3>     6/11/99         DML             Replaced temp file deletion
 *                                              code.
 *
 *      <2>     5/12/99         BWR             Multiuser system support,
 *                                              including appending UID to
 *                                              name, and compressed saves
 *                                              in the SAVE_DIR_PATH directory
 *
 *      <1>     -/--/--         LRH             Created
 */

#include "AppHdr.h"
#include "files.h"

#ifdef DOS
#include <conio.h>
#endif

#include "externs.h"
#include "enum.h"
#include "monstuff.h"

#ifdef DOS
  #include <file.h>
#endif

#ifdef LINUX
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <unistd.h>
#endif

#ifdef USE_EMX
  #include <sys/types.h>
  #include <fcntl.h>
  #include <unistd.h>
#endif

#ifdef MAC
  #include <stat.h>
#else
  #include <sys/stat.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "dungeon.h"
#include "itemname.h"
#include "items.h"
#include "message.h"
#include "misc.h"
#include "mstruct.h"
#include "mstuff2.h"
#include "output.h"
#include "player.h"
#include "randart.h"
#include "skills2.h"
#include "stuff.h"
#include "view.h"

bool tmp_file_pairs[MAX_LEVELS][MAX_DUNGEONS];

/*
   Order for looking for conjurations for the 1st & 2nd spell slots,
   when finding spells to be remembered by a player's ghost:
 */
unsigned char search_order_conj[] =
{
/* 0 */
    54,                         // crystal spear
     53,                        // -ve energy
     148,                       // agony
     151,                       // disintegrate
     17,                        // lightning
     79,                        // sticky flame
     60,                        // isk's blast
     15,                        // firebolt
     16,                        // cold bolt
     6,                         // fireball
/* 10 */
    35,                         // venom bolt
     128,                       // iron
     129,                       // stone arrow
     26,                        // thr fl
     27,                        // thr fr
     67,                        // pain
     115,                       // sting
     5,                         // m dart
     250,                       // terminate search
};

/*
   Order for looking for summonings and self-enchants for the 3rd spell slot:
 */
unsigned char search_order_third[] =
{
/* 0 */
    158,                        // symbol of torment
     121,                       // summon gr dmn
     72,                        // summon wraiths
     62,                        // summon hor th
     119,                       // summon demon
     120,                       // demonic horde
     22,                        // haste
     28,                        // animate dead
     25,                        // invis
     82,                        // call imp
     49,                        // summon small mammal
/* 10 */
    28,                         // controlled blink
     59,                        // blink
     250,                       // end search
};


/*
   Order for looking for enchants for the 4th + 5th spell slot. If fails, will
   go through conjs.
   Note: Dig must be in misc2 (5th) position to work.
 */
unsigned char search_order_misc[] =
{
/* 0 */
    148,                        // agony - evil spell
     113,                       // banishment
     23,                        // paralyse
     24,                        // confuse
     21,                        // slow
     20,                        // polymorph other
     37,                        // teleport other
     14,                        // dig
     250,                       // end search
};

/* Last slot (emergency) can only be teleport self or blink. */


int write2(FILE * file, char *buffer, unsigned int count);
int read2(FILE * file, char *buffer, unsigned int count);

static void reset_ch()
{
    you.redraw_hit_points = 1;
    you.redraw_magic_points = 1;
    you.redraw_strength = 1;
    you.redraw_intelligence = 1;
    you.redraw_dexterity = 1;
    you.redraw_armor_class = 1;
    you.redraw_evasion = 1;
    you.redraw_experience = 1;
    you.redraw_gold = 1;
    you.redraw_hunger = 1;
    you.hunger_state = 3;
}


struct ghost_struct ghost;


extern unsigned char your_sign; /* these two are defined in view.cc */
extern unsigned char your_colour;

unsigned char translate_spell(unsigned char spel);
unsigned char search_third_list(unsigned char ignore_spell);
unsigned char search_second_list(unsigned char ignore_spell);
unsigned char search_first_list(unsigned char ignore_spell);
char find_spell(unsigned char which_sp);
void add_spells(unsigned char buffer[40]);
void generate_random_demon();


static void save_int(char *&p, int val, int digits)
{
    char thing_quant[8];
    int add = 1;

    for (int i = 1; i < digits; ++i)
        add *= 10;

    itoa(val + add, thing_quant, 10);

    for (int i = 0; i < digits; ++i)
        *p++ = thing_quant[i];
}


static int load_int(char *&p, int digits)
{
    char thing_quant[8];
    int add = 1;

    thing_quant[0] = *p++;

    for (int i = 1; i < digits; ++i)
    {
        thing_quant[i] = *p++;
        add *= 10;
    }

    thing_quant[digits] = 0;
    return atoi(thing_quant) - add;
}


static void save_double(char *&p, double value, int digits)
{
    int n = sprintf(p, "%*.6g", digits, value);

    ASSERT(n == digits);
    UNUSED(n);

    p += digits;
}


static double load_double(char *&p, int digits)
{
    double value;

    char old = p[digits];

    p[digits] = '\0';           // make sure next value isn't interpreted as part of the double

    int count = sscanf(p, "%lg", &value);

    ASSERT(count == 1);
    UNUSED(count);

    p[digits] = old;
    p += digits;

    return value;
}


void load(unsigned char stair_taken, char moving_level, char was_a_labyrinth, char old_level, char want_followers, char just_made_new_lev, char where_were_you2)
{
    int j = 0;
    int i, count_x, count_y;
    char cha_fil[kFileNameSize];

    char corr_level[4];

    char already_saved = 0;

    int foll_class[8];
    int foll_hp[8];
    int foll_hp_max[8];
    unsigned char foll_HD[8];
    int foll_AC[8];
    char foll_ev[8];
    unsigned char foll_speed[8];
    unsigned char foll_speed_inc[8];

    unsigned char foll_targ_1_x[8];
    unsigned char foll_targ_1_y[8];
    int foll_inv[8][8];
    unsigned char foll_beh[8];
    int foll_sec[8];
    unsigned char foll_hit[8];

    unsigned char foll_ench[8][3];
    unsigned char foll_ench_1[8];

    unsigned char fit_iclass[8][8];
    unsigned char fit_itype[8][8];
    unsigned char fit_iplus[8][8];
    unsigned char fit_iplus2[8][8];
    unsigned char fit_idam[8][8];
    unsigned int fit_iquant[8][8];
    unsigned char fit_icol[8][8];
    char fit_iid[8][8];
    double elapsed_time = 0.0;

    int itmf = 0;
    int ic = 0;

#ifdef DOS_TERM
    window(1, 1, 80, 25);
#endif

    char hbjh[5];

    strcpy(corr_level, "");
    if (you.your_level < 10)
        strcpy(corr_level, "0");
    itoa(you.your_level, hbjh, 10);
    strcat(corr_level, hbjh);
    corr_level[2] = you.where_are_you + 97;
    corr_level[3] = 0;          /* null-terminate it */
    // save the information for later deletion  -- DML 6/11/99

#ifdef SAVE_DIR_PATH
    sprintf(cha_fil, SAVE_DIR_PATH "%s%d", you.your_name, getuid());
#else
    strncpy(cha_fil, you.your_name, kFileNameLen);
    cha_fil[kFileNameLen] = 0;
#endif

    strcat(cha_fil, ".");
    if (you.level_type != 0)
        strcat(cha_fil, "lab"); /* temporary level */
    else
    {
        strcat(cha_fil, corr_level);
        if (tmp_file_pairs[ you.your_level ][ you.where_are_you ] == false )
        {
            // make sure old file is gone
            unlink(cha_fil);

            // save the information for later deletion -- DML 6/11/99
            tmp_file_pairs[you.your_level][you.where_are_you] = true;
        }
    }

    you.prev_targ = MHITNOT;

    int following = -1;
    int fmenv = 0;

    int minvc = 0;

    if (moving_level == 1)
    {
        for (int clouty = 0; clouty < CLOUDS; ++clouty)
        {
            env.cloud_type[clouty] = 0;
            env.cgrid[env.cloud_x[clouty]][env.cloud_y[clouty]] = CNG;
            env.cloud_decay[clouty] = 0;
            --env.cloud_no;
        }
        env.cloud_no = 0;
    }

    if (want_followers == 1 && just_made_new_lev == 0)
    {
        for (count_x = you.x_pos - 1; count_x < you.x_pos + 2; count_x++)
        {
            for (count_y = you.y_pos - 1; count_y < you.y_pos + 2; count_y++)
            {
                if (count_x == you.x_pos && count_y == you.y_pos)
                    continue;
                following++;
                foll_class[following] = -1;

                if (mgrd[count_x][count_y] == MNG)
                    continue;

                fmenv = mgrd[count_x][count_y];

                if (menv[fmenv].type == MONS_PLAYER_GHOST)
                {
                    mpr( "The ghost fades into the shadows." );
                    monster_teleport(fmenv, 1);
                    continue;
                }

                if ((menv[fmenv].type == MONS_TUNNELING_WORM)
                            || (menv[fmenv].type == MONS_WORM_TAIL)
                            || (menv[fmenv].type == MONS_PANDEMONIUM_DEMON)
                            || (menv[fmenv].type == MONS_PLANT)
                            || (menv[fmenv].type == MONS_FUNGUS)
                            || (menv[fmenv].type == MONS_OKLOB_PLANT)
                            || (menv[fmenv].type == MONS_CURSE_SKULL)
                            || ((menv[fmenv].type == MONS_CURSE_TOE)
                                && (menv[fmenv].type == MONS_POTION_MIMIC))
                            || (menv[fmenv].type == -1))
                    continue;

                if (menv[fmenv].type >= MLAVA0)
                    continue;

                if (menv[fmenv].speed_increment < 50)
                    continue;

                foll_class[following] = menv[fmenv].type;
//        itoa(foll_class [following], st_prn, 10);

                foll_hp[following] = menv[fmenv].hit_points;
                foll_hp_max[following] = menv[fmenv].max_hit_points;
                foll_HD[following] = menv[fmenv].hit_dice;
                foll_AC[following] = menv[fmenv].armor_class;
                foll_ev[following] = menv[fmenv].evasion;
                foll_speed[following] = menv[fmenv].speed;
                foll_speed_inc[following] = menv[fmenv].speed_increment;
                foll_targ_1_x[following] = menv[fmenv].target_x;
                foll_targ_1_y[following] = menv[fmenv].target_y;

                for (minvc = 0; minvc < 8; ++minvc)
                    foll_inv[following][minvc] = 501;

                for (minvc = 0; minvc < 8; ++minvc)
                {
                    if (menv[fmenv].inv[minvc] == 501)
                    {
                        fit_iquant[following][minvc] = 0;
                        continue;
                    }
                    fit_iclass[following][minvc] = mitm.base_type[menv[fmenv].inv[minvc]];
                    fit_itype[following][minvc] = mitm.sub_type[menv[fmenv].inv[minvc]];
                    fit_iplus[following][minvc] = mitm.pluses[menv[fmenv].inv[minvc]];
                    fit_iplus2[following][minvc] = mitm.pluses2[menv[fmenv].inv[minvc]];
                    fit_idam[following][minvc] = mitm.special[menv[fmenv].inv[minvc]];
                    fit_iquant[following][minvc] = mitm.quantity[menv[fmenv].inv[minvc]];
                    fit_icol[following][minvc] = mitm.colour[menv[fmenv].inv[minvc]];
                    fit_iid[following][minvc] = mitm.id[menv[fmenv].inv[minvc]];
                    destroy_item(menv[fmenv].inv[minvc]);
                }

                foll_beh[following] = menv[fmenv].behavior;
                foll_sec[following] = menv[fmenv].number;
                foll_hit[following] = menv[fmenv].monster_foe;
                foll_ench_1[following] = menv[fmenv].enchantment1;
                foll_ench[following][0] = menv[fmenv].enchantment[0];
                foll_ench[following][1] = menv[fmenv].enchantment[1];
                foll_ench[following][2] = menv[fmenv].enchantment[2];

                /* now for the icky part: */
                for (j = 0; j < 3; ++j)
                    menv[fmenv].enchantment[j] = 0;
                menv[fmenv].enchantment1 = 0;
                menv[fmenv].type = -1;
                menv[fmenv].hit_points = 0;
                menv[fmenv].max_hit_points = 0;
                menv[fmenv].hit_dice = 0;
                menv[fmenv].armor_class = 0;
                menv[fmenv].evasion = 0;
                mgrd[count_x][count_y] = MNG;
            }
        }
        if (was_a_labyrinth == 0)
            save_level(old_level, 0, where_were_you2);
        already_saved = 1;
        was_a_labyrinth = 0;
    }                           /* end if level_type == 0 */

    strcpy(ghost.name, "");
    for (ic = 0; ic < 20; ++ic)
        ghost.values[ic] = 0;

#ifdef DOS
    strupr(cha_fil);
#endif

    FILE *handle;
    int handle2 = open(cha_fil, O_RDONLY, O_CREAT | O_TRUNC | O_BINARY, 0660);

    if (handle2 != -1)
    {
        close(handle2);
        handle = fopen(cha_fil, "rb");
    }
    else
    {                           /* generate new level */
        strcpy(ghost.name, "");
        for (int imn = 0; imn < 20; ++imn)
            ghost.values[imn] = 0;

        builder(you.your_level, you.level_type);

        if (you.level_type == 3)
            generate_random_demon();

        if (random2(3) == 0 && you.your_level > 1)
        {
            strcpy(corr_level, "");
            if (you.your_level < 10)
                strcpy(corr_level, "0");
            itoa(you.your_level, hbjh, 10);
            strcat(corr_level, hbjh);
            corr_level[2] = you.where_are_you + 97;
            corr_level[3] = 0;  /* null-terminate it */
#ifdef SAVE_DIR_PATH
            strcpy(cha_fil, SAVE_DIR_PATH "bones.");
#else
            strcpy(cha_fil, "bones.");
#endif
            if (you.level_type != 0)
                strcat(cha_fil, "lab");         /* temporary level */
            else
                strcat(cha_fil, corr_level);

            int gfile2 = open(cha_fil, S_IWRITE, S_IREAD);

            if (gfile2 != -1)
            {
                close(gfile2);
//        gfile = open(cha_fil, O_RDWR | O_CREAT | O_TRUNC | O_BINARY, 0660);
                //        gfile = open(cha_fil, O_RDONLY, O_CREAT | O_TRUNC | O_BINARY, 0660);
                FILE *gfile = fopen(cha_fil, "rb");

                if (gfile == NULL)
                {
                    strcpy(info, "Error opening ghost file: ");
                    strcat(info, cha_fil);
                    mpr(info);
                    more();
                }
                else
                {
                    char buf1[40];

                    read2(gfile, buf1, 40);
                    fclose(gfile);
                    for (int iiii = 0; iiii < 20; ++iiii)
                        ghost.name[iiii] = buf1[iiii];
                    ghost.values[0] = buf1[20];
                    ghost.values[1] = buf1[21];
                    ghost.values[2] = buf1[22];
                    ghost.values[3] = buf1[23];
                    ghost.values[4] = buf1[24];
                    ghost.values[5] = buf1[25];
                    ghost.values[6] = buf1[26];
                    ghost.values[7] = buf1[27];
                    ghost.values[8] = buf1[28];
                    /* note - as ghosts, automatically get res poison + prot_life */
                    ghost.values[9] = buf1[29];
                    ghost.values[10] = buf1[30];
                    ghost.values[11] = buf1[31];
                    ghost.values[12] = buf1[32];
                    ghost.values[13] = buf1[33];

                    ghost.values[14] = buf1[34];
                    ghost.values[15] = buf1[35];
                    ghost.values[16] = buf1[36];
                    ghost.values[17] = buf1[37];
                    ghost.values[18] = buf1[38];
                    ghost.values[19] = buf1[39];
                    unlink(cha_fil);
                    for (int imn = 0; imn < MNST - 10; imn++)
                    {
                        if (menv[imn].type != -1)
                            continue;
                        menv[imn].type = 400;
                        menv[imn].hit_dice = ghost.values[12];
                        menv[imn].hit_points = ghost.values[0];
                        menv[imn].max_hit_points = ghost.values[0];
                        menv[imn].armor_class = ghost.values[2];
                        menv[imn].evasion = ghost.values[1];
                        menv[imn].speed = 10;
                        menv[imn].speed_increment = 70;
                        if (ghost.values[14] != 250 || ghost.values[15] != 250 || ghost.values[16] != 250 || ghost.values[17] != 250 || ghost.values[18] != 250 || ghost.values[19] != 250)
                            menv[imn].number = 119;
                        else
                            menv[imn].number = 250;
                        do
                        {
                            menv[imn].x = random2(60) + 10;
                            menv[imn].y = random2(50) + 10;
                        }
                        while ((grd[menv[imn].x][menv[imn].y] != 67) || (mgrd[menv[imn].x][menv[imn].y] != MNG));
                        mgrd[menv[imn].x][menv[imn].y] = imn;
                        break;
                    }
                }
            }
        }

        for (i = 0; i < GXM; i++)
        {
            for (j = 0; j < GYM; j++)
            {
                env.map[i][j] = 0;
                if ((you.char_direction == 1)
                                    && (you.level_type != LEVEL_PANDEMONIUM))
                {
                    /* closes all the gates if you're on the way out */
                    if ((grd[i][j] == DNGN_ENTER_HELL)
                                || (grd[i][j] == DNGN_ENTER_ABYSS)
                                || (grd[i][j] == DNGN_ENTER_PANDEMONIUM))
                        grd[i][j] = DNGN_STONE_ARCH;
                }
                env.cgrid[i][j] = CNG;
            }
        }

        for (i = 0; i < MNST; i++)
        {
            if (menv[i].type == 255)
                menv[i].type = -1;
        }

        if (just_made_new_lev == 0)
        {
            if (stair_taken == DNGN_ENTER_HELL
                                    || stair_taken == DNGN_ENTER_LABYRINTH)
                stair_taken = DNGN_STONE_STAIRS_UP_I;
            else if (stair_taken <= DNGN_ROCK_STAIRS_DOWN)
                stair_taken += 4;
            else if (stair_taken >= 130 && stair_taken < 150)
                stair_taken -= 20;
            else if (stair_taken >= 110 && stair_taken < 130)
                stair_taken += 20;
            else if (stair_taken > 90)
                stair_taken = 86;
            else if (stair_taken == 67)
                stair_taken = 67;
            else
                stair_taken -= 4;

            for (count_x = 0; count_x < GXM; count_x++)
            {
                for (count_y = 0; count_y < GYM; count_y++)
                {
                    if (grd[count_x][count_y] == stair_taken)
                        goto found_stair;
                }
            }

            if (stair_taken <= DNGN_ROCK_STAIRS_DOWN)
                stair_taken = DNGN_STONE_STAIRS_DOWN_I;
            else
                stair_taken = DNGN_STONE_STAIRS_UP_I;

            for (count_x = 0; count_x < GXM; count_x++)
            {
                for (count_y = 0; count_y < GYM; count_y++)
                {
                    if (grd[count_x][count_y] == stair_taken)
                        goto found_stair;
                }
            }

            for (count_x = 0; count_x < GXM; count_x++)
            {
                for (count_y = 0; count_y < GYM; count_y++)
                {
                    if (grd[count_x][count_y] == DNGN_FLOOR)
                        goto found_stair;
                }
            }
        }

found_stair:
        if (just_made_new_lev == 0)
        {
            you.x_pos = count_x;
            you.y_pos = count_y;
        }

        // This should fix the "monster occuring under the player" bug?
        if (mgrd[you.x_pos][you.y_pos] != MNG)
            monster_teleport( mgrd[you.x_pos][you.y_pos], 1 );


        if ((you.level_type == LEVEL_LABYRINTH)
                                        || (you.level_type == LEVEL_ABYSS))
            grd[you.x_pos][you.y_pos] = DNGN_FLOOR;

        following = 0;
        fmenv = -1;

        if (((you.level_type == LEVEL_DUNGEON)
                || (you.level_type == LEVEL_PANDEMONIUM))
                        && (want_followers == 1) && (just_made_new_lev == 0))
        {
            for (ic = 0; ic < 2; ic++)
            {
                for (count_x = you.x_pos - 6; count_x < you.x_pos + 7; count_x++)
                {
                    for (count_y = you.y_pos - 6; count_y < you.y_pos + 7; count_y++)
                    {
                        if ((ic == 0) &&
                            (
                                (count_x < you.x_pos - 1) ||
                                (count_x > you.x_pos + 1) ||
                                (count_y < you.y_pos - 1) ||
                                (count_y > you.y_pos + 1)
                            )
                            )
                            continue;
                        if ((count_x == you.x_pos) && (count_y == you.y_pos))
                            continue;
                        if ((mgrd[count_x][count_y] != MNG) || (grd[count_x][count_y] < 67))
                            continue;
                        while (menv[following].type != -1)
                        {
                            following++;
                            if (following >= MNST)
                                goto out_of_foll;
                        }

                        while (fmenv < 7)
                        {
                            fmenv++;
                            if (foll_class[fmenv] == -1)
                                continue;
                            menv[following].type = foll_class[fmenv];
                            menv[following].hit_points = foll_hp[fmenv];
                            menv[following].max_hit_points = foll_hp_max[fmenv];
                            menv[following].hit_dice = foll_HD[fmenv];
                            menv[following].armor_class = foll_AC[fmenv];
                            menv[following].evasion = foll_ev[fmenv];
                            menv[following].speed = foll_speed[fmenv];
                            menv[following].speed_increment = foll_speed_inc[fmenv];
                            menv[following].x = count_x;
                            menv[following].y = count_y;
                            menv[following].target_x = 0;
                            menv[following].target_y = 0;
                            for (minvc = 0; minvc < 8; minvc++)
                            {
                                if (fit_iquant[fmenv][minvc] == 0)
                                {
                                    menv[following].inv[minvc] = 501;
                                    continue;
                                }
                                itmf = 0;
                                while (mitm.quantity[itmf] > 0)
                                    ++itmf;
                                menv[following].inv[minvc] = itmf;
                                mitm.base_type[itmf] = fit_iclass[fmenv][minvc];
                                mitm.sub_type[itmf] = fit_itype[fmenv][minvc];
                                mitm.pluses[itmf] = fit_iplus[fmenv][minvc];
                                mitm.pluses2[itmf] = fit_iplus2[fmenv][minvc];
                                mitm.special[itmf] = fit_idam[fmenv][minvc];
                                mitm.quantity[itmf] = fit_iquant[fmenv][minvc];
                                mitm.colour[itmf] = fit_icol[fmenv][minvc];
                                mitm.id[itmf] = fit_iid[fmenv][minvc];
                                mitm.link[itmf] = 501;
                            }
                            menv[following].behavior = foll_beh[fmenv];
                            menv[following].number = foll_sec[fmenv];
                            menv[following].monster_foe = foll_hit[fmenv];
                            menv[following].enchantment1 = foll_ench_1[fmenv];
                            menv[following].enchantment[0] = foll_ench[fmenv][0];
                            menv[following].enchantment[1] = foll_ench[fmenv][1];
                            menv[following].enchantment[2] = foll_ench[fmenv][2];
                            mgrd[count_x][count_y] = following;
                            break;
                        }
                    }
                }
            }
        }                       /* end if level_type == 0 */

out_of_foll:
        reset_ch();
        moving_level = 0;

        for (i = 0; i < MNST; i++)
        {
            if (menv[i].type == -1)
                continue;
            for (j = 0; j < 8; j++)
            {
                if (menv[i].inv[j] == 501)
                    continue;
                if (mitm.link[menv[i].inv[j]] != 501)
                {
                    /* items carried by monsters shouldn't be linked */
                    mitm.link[menv[i].inv[j]] = 501;
                }
            }
        }

        if (you.level_type == LEVEL_PANDEMONIUM)
        {
            for (count_x = 0; count_x < GXM; count_x++)
            {
                for (count_y = 0; count_y < GYM; count_y++)
                {
                    if ((grd[count_x][count_y] >= DNGN_STONE_STAIRS_UP_I)
                            && (grd[count_x][count_y] <= DNGN_ROCK_STAIRS_UP))
                    {
                        grd[count_x][count_y] = DNGN_FLOOR;
                        if (random2(50) == 0)
                            grd[count_x][count_y] = DNGN_EXIT_PANDEMONIUM;
                    }

                    if ((grd[count_x][count_y] >= DNGN_ENTER_LABYRINTH)
                            && (grd[count_x][count_y] <= DNGN_ROCK_STAIRS_DOWN))
                    {
                        grd[count_x][count_y] = DNGN_TRANSIT_PANDEMONIUM;
                    }
                }
            }
        }

        if (elapsed_time != 0.0)
        {
            double delta = you.elapsed_time - elapsed_time;

            if (delta > 0.0)    // because of rounding errors when saving it's possible to have a negative number if the numbers are large and close together

                update_corpses(delta);
        }

        save_level(you.your_level, (you.level_type != LEVEL_DUNGEON),
                                                        you.where_are_you);
        return;
    }

    moving_level = 0;

    for (count_x = 0; count_x < ITEMS; count_x++)
        mitm.link[count_x] = 501;

    for (i = 0; i < GXM; i++)
    {
        for (j = 0; j < GYM; j++)
            igrd[i][j] = 501;
    }

    const int oldlen = 20 + 20 + 4 * 80 * 70 + 3 * NTRAPS + 25 * ITEMS + 1 + 9 * CLOUDS + 5 * 8 + 5 * 20 + (18 + 5 + 5 + 5 + 5 + 8 * 5) * MNST;
    const int datalen = 42 + oldlen;

    char *buf = (char *) malloc(datalen);

    int bytes = read2(handle, buf, datalen);

    if (oldlen != bytes && datalen != bytes)
    {
        perror("opa (7)...");
        cprintf(EOL "Wanted to read ");
        itoa(datalen, st_prn, 10);
        cprintf(st_prn);
        cprintf(" bytes; could only read ");
        itoa(bytes, st_prn, 10);
        cprintf(st_prn);
        cprintf(".");
        end(-1);
    }

    fclose(handle);

    char *p = buf;

    if (bytes > oldlen)
    {
        char majorVersion = *p++;
        char minorVersion = *p++;
        int chunkSize = load_int(p, 4);

        if (majorVersion != 1)
        {
            free(buf);
            perror("Unable to read level (bad version)");
            end(-1);
        }

        elapsed_time = load_double(p, 14);

        for (i = 0; i < (chunkSize - 20); ++i)
            *p++;               // reserved

    }

    for (i = 0; i < 20; ++i)
        ghost.name[i] = *p++;
    for (i = 0; i < 20; ++i)
        ghost.values[i] = *p++;
//  for (j=0; j<20; ++j) ghost.values[j]-=30;

    for (count_x = 0; count_x < GXM; count_x++)
    {
        for (count_y = 0; count_y < GYM; count_y++)
        {
            grd[count_x][count_y] = *p++;
            env.map[count_x][count_y] = *p++;
            if (env.map[count_x][count_y] == 201)
                env.map[count_x][count_y] = 239;
            mgrd[count_x][count_y] = MNG;
            ++p;
            if ((mgrd[count_x][count_y] != MNG) &&
                (
                    (menv[mgrd[count_x][count_y]].type == -1) ||
                    (menv[mgrd[count_x][count_y]].x != count_x) ||
                    (menv[mgrd[count_x][count_y]].y != count_y)
                ))
            {
                mgrd[count_x][count_y] = MNG;   /* This is one of the worst things I've ever done */
            }
            env.cgrid[count_x][count_y] = *p++;
        }
    }

    for (i = 0; i < NTRAPS; i++)
    {
        env.trap_type[i] = *p++;
        env.trap_x[i] = *p++;
        env.trap_y[i] = *p++;
    }

    for (count_x = 0; count_x < GXM; count_x++)
    {
        for (count_y = 0; count_y < GYM; count_y++)
        {
            if ((igrd[count_x][count_y] < 0) || (igrd[count_x][count_y] > 501))
            {
                igrd[count_x][count_y] = 501;
            }
        }
    }

    for (i = 0; i < ITEMS; ++i)
    {
        mitm.base_type[i] = *p++;
        mitm.sub_type[i] = *p++;
        mitm.pluses[i] = *p++;
        mitm.special[i] = *p++;
        mitm.quantity[i] = load_int(p, 6);
        mitm.colour[i] = *p++;
        mitm.x[i] = *p++;
        mitm.y[i] = *p++;
        mitm.id[i] = *p++;
        mitm.link[i] = load_int(p, 5) - 40000;
        igrd[mitm.x[i]][mitm.y[i]] = load_int(p, 5) - 40000;
        mitm.pluses2[i] = *p++;
        if (mitm.base_type[i] == 100)
        {
            mitm.quantity[i] = 0;
            mitm.link[i] = 501;
        }
    }

    env.cloud_no = *p++;

    for (i = 0; i < CLOUDS; ++i)
    {
        env.cloud_x[i] = *p++;
        env.cloud_y[i] = *p++;
        env.cloud_type[i] = *p++;
        env.cloud_decay[i] = load_int(p, 5);
        ++p;
    }

    for (i = 0; i < 5; ++i)
    {
        env.keeper_name[i][0] = *p++;
        env.keeper_name[i][1] = *p++;
        env.keeper_name[i][2] = *p++;
        env.sh_x[i] = *p++;
        env.sh_y[i] = *p++;
        env.sh_greed[i] = *p++;
        env.sh_type[i] = *p++;
        env.sh_level[i] = *p++;
#ifdef DEBUG
        if (mgrd[env.sh_x[i] - 1][env.sh_y[i] - 1] == 31)
        {
            cprintf("x");
            getch();
        }
#endif
    }

    for (i = 0; i < 20; i++)
        env.mons_alloc[i] = load_int(p, 5) - 10000;

    for (count_x = 0; count_x < MNST; ++count_x)
    {
        p += 3;
        menv[count_x].armor_class = *p++;
        menv[count_x].evasion = *p++;
        menv[count_x].hit_dice = *p++;
        menv[count_x].speed = *p++;
        menv[count_x].speed_increment = *p++;
        menv[count_x].behavior = *p++;
        menv[count_x].x = *p++;
        menv[count_x].y = *p++;
        menv[count_x].target_x = *p++;
        menv[count_x].target_y = *p++;
        ++p;
        menv[count_x].enchantment1 = *p++;
        for (j = 0; j < 3; ++j)
            menv[count_x].enchantment[j] = *p++;
        menv[count_x].type = load_int(p, 5) - 40080;
        menv[count_x].hit_points = load_int(p, 5) - 40000;
        menv[count_x].max_hit_points = load_int(p, 5) - 40000;

        menv[count_x].number = load_int(p, 5) - 40000;
        for (j = 0; j < 8; ++j)
            menv[count_x].inv[j] = load_int(p, 5) - 40000;

#if 0
        for (j = 0; j < MNST; ++j)
        {
            if (menv[j].type != -1)
                mgrd[menv[j].x][menv[j].y] = j;
        }
#else

        if (menv[count_x].type != -1)
        {
            mgrd[menv[count_x].x][menv[count_x].y] = count_x;

            if (menv[count_x].hit_points < menv[count_x].max_hit_points)
            {
                if (elapsed_time != 0.0)
                {
                    int turns = (int) (you.elapsed_time - elapsed_time) / 10;

                    if (turns > 0)
                    {
                        // player ghosts included here because they cannot
                        // leave the level to follow the player.
                        if (monster_regenerates( menv[count_x].type )
                                || menv[count_x].type == MONS_PLAYER_GHOST)
                        {
                            menv[count_x].hit_points += turns;
                        }
                        else
                        {
                            menv[count_x].hit_points += (turns / 25);
                        }

                        if (menv[count_x].hit_points >
                                                menv[count_x].max_hit_points)
                        {
                            menv[count_x].hit_points =
                                                menv[count_x].max_hit_points;
                        }
                    }
                }
            }
        }

#endif
    }


    reset_ch();

    free(buf);
    if (p != buf + datalen)
    {
        perror("opa (6)...");
        end(-1);
    }

    for (i = 0; i < GXM; i++)
    {
        for (j = 0; j < GYM; j++)
        {
            if (igrd[i][j] < 0 | igrd[i][j] > 501)
                igrd[i][j] = 501;
        }
    }
    for (i = 0; i < MNST; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((menv[i].inv[j] < 0) || (menv[i].inv[j] > 501))
                menv[i].inv[j] = 501;
            if (menv[i].inv[j] != 501)
                mitm.link[menv[i].inv[j]] = 501;
        }
    }
    for (i = 0; i < ITEMS; i++)
    {
        if (mitm.link[i] > 501)
            mitm.link[i] = 501;
    }
    for (i = 0; i < MNST; i++)
    {
        if (menv[i].type == -1)
            continue;
        for (j = 0; j < 8; j++)
        {
            if (menv[i].inv[j] == 501)
                continue;
            if (mitm.link[menv[i].inv[j]] != 501)
            {
                mitm.link[menv[i].inv[j]] = 501;
            }
        }
    }


    for (int i = 0; i < GXM; i++)
    {
        for (int j = 0; j < GYM; j++)
        {
            if ((you.char_direction == 1)
                                && (you.level_type != LEVEL_PANDEMONIUM))
            {
                /* closes all the gates if you're on the way out */
                if ((grd[i][j] == DNGN_ENTER_HELL)
                                || (grd[i][j] == DNGN_ENTER_ABYSS)
                                || (grd[i][j] == DNGN_ENTER_PANDEMONIUM))
                {
                    grd[i][j] = DNGN_STONE_ARCH;
                }
            }
        }
    }



    if (you.your_level == 35 && stair_taken >= 86)
    {
        do
        {
            you.x_pos = 10 + random2(GXM - 10);
            you.y_pos = 10 + random2(GYM - 10);
        }
        while ((grd[you.x_pos][you.y_pos] != 67) || (mgrd[you.x_pos][you.y_pos] != MNG));
        count_x = you.x_pos;
        count_y = you.y_pos;
        goto found_stair;
    }
    else
    {
        if (stair_taken == 67)
            for (count_x = 0; count_x < GXM; count_x++)
            {
                for (count_y = 0; count_y < GYM; count_y++)
                {
                    if (grd[count_x][count_y] == stair_taken)
                        goto found_stair;
                }
            }
        if (stair_taken >= 130 && stair_taken < 150)
            stair_taken -= 20;
        else if (stair_taken >= 110 && stair_taken < 130)
            stair_taken += 20;
        else if (stair_taken < 86)
            stair_taken += 4;
        else
            stair_taken -= 4;
        for (count_x = 0; count_x < GXM; count_x++)
        {
            for (count_y = 0; count_y < GYM; count_y++)
            {
                if (grd[count_x][count_y] == stair_taken)
                    goto found_stair;
            }
        }
        if (stair_taken < 86)
            stair_taken = 82;
        else
            stair_taken = 86;
        for (count_x = 0; count_x < GXM; count_x++)
        {
            for (count_y = 0; count_y < GYM; count_y++)
            {
                if (grd[count_x][count_y] == stair_taken)
                    goto found_stair;
            }
        }
    }

    for (count_x = 0; count_x < GXM; count_x++)
    {
        for (count_y = 0; count_y < GYM; count_y++)
        {
            if ((mgrd[count_x][count_y] != MNG)
                    && ((menv[mgrd[count_x][count_y]].type == -1)
                        || (menv[mgrd[count_x][count_y]].x != count_x)
                        || (menv[mgrd[count_x][count_y]].y != count_y)))
            {
                /* This is one of the worst things I've ever done */
                mgrd[count_x][count_y] = MNG;
            }
        }
    }

    if (elapsed_time != 0.0)
    {
        double delta = you.elapsed_time - elapsed_time;

        if (delta > 0.0)        // because of rounding errors when saving it's possible to have a negative number if the numbers are large and close together

            update_corpses(delta);
    }
}                               /* end of void load_level(); */


void save_level(int level_saved, char was_a_labyrinth, char where_were_you)
{
    char cha_fil[kFileNameSize];
    char extens[5];
    int count_x, count_y;
    int i, j;
    char hbjh[5];

    strcpy(extens, "");
    if (level_saved < 10)
        strcpy(extens, "0");
    itoa(level_saved, hbjh, 10);
    strcat(extens, hbjh);
    extens[2] = where_were_you + 97;
    extens[3] = 0;              /* null-terminate it */

#ifdef SAVE_DIR_PATH
    sprintf(cha_fil, SAVE_DIR_PATH "%s%d", you.your_name, getuid());
#else
    strncpy(cha_fil, you.your_name, kFileNameLen);
    cha_fil[kFileNameLen] = 0;
#endif

    strcat(cha_fil, ".");
    if (was_a_labyrinth == 1)
        strcat(cha_fil, "lab"); /* temporary level */
    else
        strcat(cha_fil, extens);

    you.prev_targ = MHITNOT;

#ifdef DOS
    strupr(cha_fil);
#endif

    int fry;
    int frx;

/* Setting up x & y, which aren't normally used: */

    for (frx = 0; frx < MNST; frx++)
    {
        for (fry = 0; fry < 8; fry++)
        {
            if (menv[frx].inv[fry] != 501)
            {
                mitm.x[menv[frx].inv[fry]] = 2;
                mitm.y[menv[frx].inv[fry]] = 2;
                mitm.link[menv[frx].inv[fry]] = 501;
            }
        }
    }

    for (count_x = 0; count_x < 80; count_x++)
    {
        for (count_y = 0; count_y < 70; count_y++)
        {

            int count_out = 0;

            if (igrd[count_x][count_y] < 0 | igrd[count_x][count_y] > 501)
                igrd[count_x][count_y] = 501;
            if (igrd[count_x][count_y] > 501)
                igrd[count_x][count_y] = 501;
            if (igrd[count_x][count_y] == 501)
                continue;

            frx = igrd[count_x][count_y];

            while (frx != 501)
            {
                mitm.x[frx] = count_x;
                mitm.y[frx] = count_y;

                if (frx > 501 | frx < 0)
                {
                    cprintf("Error! Item out of bounds: ");
                    itoa(frx, st_prn, 10);
                    cprintf(st_prn);
                    if (getch() == 0)
                        getch();
                    cprintf(EOL);
                    break;
                }

                fry = mitm.link[frx];
                frx = fry;
                ++count_out;
                if (count_out > 1000)
                {
                    count_out = 0;
                    mitm.link[frx] = 501;
                    mpr("Item link error.");
                    break;
                }

                if (frx == 501)
                    break;
            }
        }
    }

    const int datalen = 42 + 20 + 20 + 4 * 80 * 70 + 3 * NTRAPS + 25 * ITEMS + 1 + 9 * CLOUDS + 5 * 8 + 5 * 20 + (18 + 5 + 5 + 5 + 5 + 8 * 5) * MNST;
    char *buf = (char *) malloc(datalen);
    char *p = buf;

    *p++ = 1;                   // major version number

    *p++ = 1;                   // minor version number

    save_int(p, 42, 4);         // chunk size

    save_double(p, you.elapsed_time, 14);
    for (i = 0; i < 22; ++i)
        *p++ = 0;               // reserved

    unsigned char ghost_bak[20];

    for (j = 0; j < 20; j++)
        ghost_bak[j] = ghost.values[j];
    for (i = 0; i < 20; ++i)
        *p++ = ghost.name[i];
    for (i = 0; i < 20; ++i)
        *p++ = ghost_bak[i];

    for (count_x = 0; count_x < 80; count_x++)
    {
        for (count_y = 0; count_y < 70; count_y++)
        {
            *p++ = (grd[count_x][count_y]);
            *p++ = env.map[count_x][count_y];
            *p++ = mgrd[count_x][count_y];
            *p++ = env.cgrid[count_x][count_y];
        }
    }

    for (i = 0; i < NTRAPS; ++i)
    {
        *p++ = env.trap_type[i];
        *p++ = env.trap_x[i];
        *p++ = env.trap_y[i];
    }

    for (i = 0; i < ITEMS; ++i)
    {
        *p++ = mitm.base_type[i];
        *p++ = mitm.sub_type[i];
        *p++ = mitm.pluses[i];
        *p++ = mitm.special[i];
        save_int(p, mitm.quantity[i], 6);
        *p++ = mitm.colour[i];
        *p++ = mitm.x[i];
        *p++ = mitm.y[i];
        *p++ = mitm.id[i];
        if (mitm.quantity[i] == 0)
            mitm.link[i] = 501;
        save_int(p, mitm.link[i] + 40000, 5);
        save_int(p, igrd[mitm.x[i]][mitm.y[i]] + 40000, 5);
        *p++ = mitm.pluses2[i];
    }

    *p++ = env.cloud_no;

    for (i = 0; i < CLOUDS; i++)
    {
        *p++ = env.cloud_x[i];
        *p++ = env.cloud_y[i];
        *p++ = env.cloud_type[i];
        save_int(p, env.cloud_decay[i], 5);
        *p++ = 0;
    }

    for (i = 0; i < 5; i++)
    {
        *p++ = env.keeper_name[i][0];
        *p++ = env.keeper_name[i][1];
        *p++ = env.keeper_name[i][2];
        *p++ = env.sh_x[i];
        *p++ = env.sh_y[i];
        *p++ = env.sh_greed[i];
        *p++ = env.sh_type[i];
        *p++ = env.sh_level[i];
#ifdef DEBUG
        if (mgrd[env.sh_x[i] - 1][env.sh_y[i] - 1] == 31)
        {
            cprintf("y");
            getch();
        }
#endif
    }

    for (i = 0; i < 20; ++i)
        save_int(p, env.mons_alloc[i] + 10000, 5);

    for (i = 0; i < MNST; i++)
    {
        *p++ = 5;
        *p++ = 5;
        *p++ = 5;
        *p++ = menv[i].armor_class;
        *p++ = menv[i].evasion;
        *p++ = menv[i].hit_dice;
        *p++ = (menv[i].speed);
        *p++ = menv[i].speed_increment;
        *p++ = menv[i].behavior;
        *p++ = menv[i].x;
        *p++ = menv[i].y;
        *p++ = menv[i].target_x;
        *p++ = menv[i].target_y;
//    *p++ = 5;
        *p++ = 0;
        *p++ = menv[i].enchantment1;
        for (j = 0; j < 3; j++)
            *p++ = menv[i].enchantment[j];
        save_int(p, menv[i].type + 40080, 5);
        save_int(p, menv[i].hit_points + 40000, 5);
        save_int(p, menv[i].max_hit_points + 40000, 5);
        save_int(p, menv[i].number + 40000, 5);
        for (j = 0; j < 8; j++)
            save_int(p, menv[i].inv[j] + 40000, 5);
    }

    if (p != buf + datalen)
    {
        perror("opa (1)...");
        end(-1);
    }
    FILE *handle = fopen(cha_fil, "wb");

    if (handle == NULL)
    {
        perror("Oh dear... ");
        end(-1);
    }
    int retval = write2(handle, buf, datalen);

    free(buf);
    if (datalen != retval)
    {
        perror("opa (2)...");
        end(-1);
    }
    fclose(handle);
}


void save_game(char leave_game)
{
    char char_f[kFileNameSize];
    int i, j;

#ifdef SAVE_PACKAGE_CMD
    char name_buff[kFileNameSize];
    char cmd_buff[1024];

    sprintf(name_buff, SAVE_DIR_PATH "%s%d", you.your_name, getuid());
    sprintf(cmd_buff, SAVE_PACKAGE_CMD, name_buff, name_buff);
    sprintf(char_f, "%s.sav", name_buff);
#else
    strncpy(char_f, you.your_name, kFileNameLen);
    char_f[kFileNameLen] = 0;
    strcat(char_f, ".sav");

#ifdef DOS
    strupr(char_f);
#endif
#endif

    int datalen = 42 + 30 + 35 + 10 + 69 + 6 + 5 + 25 + 2 + 30 + 5 + 25 + 12 * 52 + 50 * 5 + 50 * 4 + 50 + 50 + 6 * 50 + 50 + 50 + 30 + 30 + 30 + 100 + 50 + 100 + NO_UNRANDARTS + MAX_LEVELS * MAX_DUNGEONS;
    char *buf = (char *) malloc(datalen);
    char *p = buf;

    *p++ = 1;                   // major version number

    *p++ = 3;                   // minor version number

    save_int(p, 42, 4);         // chunk size

    save_double(p, you.elapsed_time, 14);
    for (i = 0; i < 22; ++i)
        *p++ = 0;               // reserved

    for (i = 0; i < MAX_LEVELS; i++)
        for (j = 0; j < MAX_DUNGEONS; j++)
            *p++ = (char) tmp_file_pairs[ i ][ j ];

    for (j = 0; j < 30; ++j)
    {
        unsigned char ch = you.your_name[j];

        if ((ch == 26) || (ch == 27))
            ch = 0;
        *p++ = ch;
    }

    *p++ = you.religion;
    *p++ = you.piety;
    *p++ = you.invis;
    *p++ = you.conf;
    *p++ = you.paralysis;
    *p++ = you.slow;
    *p++ = you.shock_shield;
    *p++ = you.rotting;
    *p++ = you.exhausted;
    *p++ = you.deaths_door;
    *p++ = your_sign;
    *p++ = your_colour;
    *p++ = 0;
    *p++ = you.pet_target;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0; // *p++ = you.spell_levels;
    *p++ = you.max_level;
    *p++ = you.where_are_you;
    *p++ = you.char_direction;
    *p++ = you.your_level;
    *p++ = you.is_undead;
    *p++ = you.special_wield;
    *p++ = you.berserker;
    *p++ = you.berserk_penalty;
    *p++ = you.level_type;
    *p++ = you.synch_time;
    *p++ = you.disease;
    *p++ = 0;
    *p++ = 0;
    *p++ = you.species;

    save_int(p, you.hp, 5);
    save_int(p, you.hp, 5);

    if (you.haste > 215)
        you.haste = 215;
    *p++ = you.haste;
    if (you.might > 215)
        you.might = 215;
    *p++ = you.might;
    if (you.levitation > 215)
        you.levitation = 215;
    *p++ = you.levitation;
    if (you.poison > 215)
        you.poison = 215;
    *p++ = you.poison;
    *p++ = 0;

    save_int(p, you.hunger, 6);

    *p++ = 0;
    for (i = 0; i < NO_EQUIP; ++i)
        *p++ = you.equip[i];
    *p++ = you.magic_points;
    *p++ = you.max_magic_points;
    *p++ = you.strength;
    *p++ = you.intel;
    *p++ = you.dex;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = you.hit_points_regeneration;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;

    save_int(p, (int) (you.hit_points_regeneration * 100), 5);
    save_int(p, you.experience, 7);
    save_int(p, you.gold, 5);

    *p++ = you.char_class;
    *p++ = you.experience_level;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;

    save_int(p, you.exp_available, 6);

    /* max values */
    *p++ = you.max_strength;
    *p++ = you.max_intel;
    *p++ = you.max_dex;
    *p++ = 0;  // *p++ = you.hunger_inc;
    *p++ = you.magic_points_regeneration;

    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;
    *p++ = 0;

    save_int(p, you.base_hp, 5);
    save_int(p, you.base_hp2, 5);
    save_int(p, you.base_magic_points, 5);
    save_int(p, you.base_magic_points2, 5);

    *p++ = (unsigned char) you.x_pos;
    *p++ = (unsigned char) you.y_pos;

    for (j = 0; j < 30; ++j)
        *p++ = you.class_name[j];

    save_int(p, you.burden, 5);

    for (i = 0; i < 25; ++i)
        *p++ = you.spells[i];

    for (i = 0; i < 52; ++i)
    {
        *p++ = you.inv_class[i];
        *p++ = you.inv_type[i];
        *p++ = you.inv_plus[i];
        *p++ = you.inv_dam[i];
        *p++ = you.inv_colour[i];
        *p++ = you.inv_ident[i];
        save_int(p, you.inv_quantity[i], 5);
        *p++ = you.inv_plus2[i];
    }

    for (i = 0; i < 5; ++i)
    {
        for (j = 0; j < 50; ++j)
            *p++ = you.item_description[i][j];
    }

    char identy[4][50];

    save_id(identy);

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 50; ++j)
            *p++ = identy[i][j];
    }

    for (j = 0; j < 50; ++j)
        *p++ = you.skills[j];   /* skills! */

    for (j = 0; j < 50; ++j)
        *p++ = you.practise_skill[j];   /* skills! */

    for (j = 0; j < 50; ++j)
        save_int(p, you.skill_points[j], 6);

    for (j = 0; j < 50; ++j)
        *p++ = you.unique_items[j];     /* unique items */

    for (j = 0; j < 50; ++j)
        *p++ = you.unique_creatures[j];         /* unique beasties */

    for (j = 0; j < 30; ++j)
        *p++ = you.duration[j];

    for (j = 0; j < 30; ++j)
        *p++ = you.attribute[j];

    for (j = 0; j < 30; ++j)
        *p++ = you.branch_stairs[j];

    for (j = 0; j < 100; ++j)
        *p++ = you.mutation[j];

    for (j = 0; j < 50; ++j)
        *p++ = you.had_item[j];

    for (j = 0; j < 100; ++j)
        *p++ = you.demon_pow[j];

    for (j = 0; j < NO_UNRANDARTS; ++j)
        *p++ = does_unrandart_exist(j);

    if (p != buf + datalen)
    {
        perror("opa (3)...");
        end(-1);
    }

/* Use the first one to amend already created files, and the second to create
   new - the 2nd will be used eventually, as save games will be deleted after
   loading. */

//  int handle=open(char_f, O_CREAT|O_TRUNC|O_BINARY, 0660);
    FILE *handle =              //open(char_f, O_RDWR|O_CREAT|O_TRUNC|O_BINARY, 0660);
     fopen(char_f, "wb");

    if (handle == NULL)
    {
        perror("Unable to open file for writing");
        end(-1);
    }
    int retval = write2(handle, buf, datalen);

    free(buf);
    if (datalen != retval)
    {
        perror("opa (4)...");
        end(-1);
    }
    fclose(handle);

    if (!leave_game)
        return;

/*if (you.level_type != 0) was_a_labyrinth = 1; */
    if (you.level_type == 0)
        save_level(you.your_level, 0, you.where_are_you);
    else
        save_level(you.your_level, 1, you.where_are_you);
/* save_level(you.your_level); */

/* was_a_labyrinth = 0; */

#ifdef DOS_TERM
    window(1, 1, 80, 25);
#endif

#ifdef SAVE_PACKAGE_CMD
    system(cmd_buff);
#endif

    clrscr();

#if defined(SAVE_PACKAGE_CMD) && defined(DO_ANTICHEAT_CHECKS)
    struct stat stat_buff;
    char  zip_buff[kFileNameLen];

    strcpy( zip_buff, name_buff );
    strcat( zip_buff, PACKAGE_SUFFIX );

    if (stat( zip_buff, &stat_buff ) == 0)
    {
        int i = 0;
        for ( ; i < 100; i++ ) {
            GDBM_FILE  dbf = gdbm_open( SAVE_DIR_PATH "savegame.db", 0,
                                                GDBM_WRCREAT, 0660, NULL );
            datum  key, content;

            if (dbf)
            {
                key.dsize = strlen( name_buff );
                key.dptr = name_buff;

                char num_buff[ sizeof( int ) * 2 + 1 ];
                content.dsize = sizeof( int ) * 2 + 1;

                sprintf( num_buff, "%x", stat_buff.st_ctime );
                content.dptr = num_buff;

                gdbm_store( dbf, key, content, GDBM_REPLACE );

                gdbm_close( dbf );
            }

            // We only want to delay and loop if we might be locked out
            // from being a writer.  Other errors or success will break
            // out of the loop.
            if (gdbm_errno != GDBM_CANT_BE_WRITER)
                break;

            delay(20);
        }

        if (i == 100)
        {
            cprintf( "Error opening database: %s", gdbm_strerror(gdbm_errno) );
            more();
        }
    }
    else
    {
        cprintf( "Saving error: Cannot stat savefile!" );
        more();
    }
#endif

    cprintf("See you soon!");

    end(0);

}                               /* end of save_game() */


void restore_game()
{
    char char_f[kFileNameSize];
    int i, j;

#ifdef SAVE_DIR_PATH
    sprintf(char_f, SAVE_DIR_PATH "%s%d", you.your_name, getuid());
#else
    strncpy(char_f, you.your_name, kFileNameLen);
    char_f[kFileNameLen] = 0;
#endif

    strcat(char_f, ".sav");

#ifdef DOS
    strupr(char_f);
#endif


//  int handle = open(char_f, O_RDONLY, S_IWRITE, S_IREAD);
    FILE *handle =              //open(char_f, O_RDWR|O_CREAT|O_TRUNC|O_BINARY, 0660);
     fopen(char_f, "rb");

    if (handle == NULL)
    {
        perror("Unable to open file for reading");
        end(-1);
    }

    int oldlen = 30 + 35 + 10 + 69 + 6 + 5 + 25 + 2 + 30 + 5 + 25 + 12 * 52 + 50 * 5 + 50 * 4 + 50 + 50 + 6 * 50 + 50 + 50 + 30 + 30 + 30 + 100 + 50 + 100 + NO_UNRANDARTS;

    int datalen = oldlen + 42 + MAX_LEVELS * MAX_DUNGEONS;
    char *buf = (char *) malloc(datalen);
    char *p = buf;

    int bytes = read2(handle, buf, datalen);

    if (oldlen != bytes && datalen != bytes && (oldlen + 42) != bytes)
    {
        free(buf);
        perror("Unable to read file");
        end(-1);
    }
    fclose(handle);

    char majorVersion;
    char minorVersion;

    if (bytes > oldlen)
    {
        majorVersion = *p++;
        minorVersion = *p++;
        int chunkSize = load_int(p, 4);

        if (majorVersion != 1)
        {
            free(buf);
            perror("Unable to read file (bad version)");
            end(-1);
        }

        // if zero we're opening a new game so we need the saved time
        if (you.elapsed_time < 0.01)
            you.elapsed_time = load_double(p, 14);

        for (i = 0; i < (chunkSize - 20); i++)
            *p++;               // reserved

        if (minorVersion >= 2)
        {
            for (int level = 0; level < MAX_LEVELS; level++)
                for (int dungeon = 0; dungeon < MAX_DUNGEONS; dungeon++)
                    tmp_file_pairs[ level ][ dungeon ] = *p++;
        }

    }
    else
        you.elapsed_time = 0;

    for (j = 0; j < 30; ++j)
        you.your_name[j] = *p++;

    you.religion = *p++;
    you.piety = *p++;
    you.invis = *p++;
    you.conf = *p++;
    you.paralysis = *p++;
    you.slow = *p++;
    you.shock_shield = *p++;
    you.rotting = *p++;
    you.exhausted = *p++;
    you.deaths_door = *p++;
    your_sign = *p++;
    your_colour = *p++;
/*you.spec_poison=*p++-40; */ ++p;
    you.pet_target = *p++;
/*you.prot_life=*p++-40; */ ++p;
/*  you.res_magic=load_int(p, 5); */ p += 5;
    ++p;  //you.spell_levels = *p++;
    you.max_level = *p++;
    you.where_are_you = *p++;
    you.char_direction = *p++;
    you.your_level = *p++;
    you.is_undead = *p++;
    you.special_wield = *p++;
    you.berserker = *p++;
    you.berserk_penalty = *p++;
    you.level_type = *p++;
    you.synch_time = *p++;
    you.disease = *p++;
/*you.spec_death=*p++; */ ++p;
/*you.spec_holy=*p++; */ ++p;
    you.species = *p++;
    you.hp = load_int(p, 5);
    you.hp_max = load_int(p, 5);
    you.haste = *p++;
    you.might = *p++;
    you.levitation = *p++;
    you.poison = *p++;
    ++p;
    you.hunger = load_int(p, 6);

/*you.item_wielded=*p++; */ ++p;

    for (i = 0; i < NO_EQUIP; ++i)
        you.equip[i] = *p++;

    you.magic_points = *p++;
    you.max_magic_points = *p++;
    you.strength = *p++;
    you.intel = *p++;
    you.dex = *p++;

/*you.AC=*p++-80; */ ++p;
/*you.evasion=*p++; */ ++p;
/*you.damage=*p++; */ ++p;
    p += 2;
    you.hit_points_regeneration = *p++;
    p += 3;
    p += 5;

    you.experience = load_int(p, 7);
    you.gold = load_int(p, 5);

    you.char_class = *p++;
    you.experience_level = *p++;
    p += 14;

    you.exp_available = load_int(p, 6);

    you.max_strength = *p++;
    you.max_intel = *p++;
    you.max_dex = *p++;
    ++p;  // you.hunger_inc = *p++;
    you.magic_points_regeneration = *p++;

    p += 5;

    you.base_hp = load_int(p, 5);
    you.base_hp2 = load_int(p, 5);
    you.base_magic_points = load_int(p, 5);
    you.base_magic_points2 = load_int(p, 5);

    you.x_pos = (int) *p++;
    you.y_pos = (int) *p++;

    for (i = 0; i < 30; ++i)
        you.class_name[i] = *p++;

    you.burden = load_int(p, 5);

    you.spell_no = 0;
    for (i = 0; i < 25; ++i)
    {
        you.spells[i] = *p++;
        if (you.spells[i] != 210)
            ++you.spell_no;
    }

    you.num_inv_items = 0;
    for (i = 0; i < 52; ++i)
    {
        you.inv_class[i] = *p++;
        you.inv_type[i] = *p++;
        you.inv_plus[i] = *p++;
        you.inv_dam[i] = *p++;
        you.inv_colour[i] = *p++;
        you.inv_ident[i] = *p++;

        you.inv_quantity[i] = load_int(p, 5);

        you.inv_plus2[i] = *p++;
        if (you.inv_quantity[i] > 0)
            ++you.num_inv_items;
    }

    for (i = 0; i < 5; ++i)
    {
        for (j = 0; j < 50; ++j)
            you.item_description[i][j] = *p++;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 50; ++j)
        {
            unsigned char ch = *p++;

            switch (i)
            {
            case 0:
                set_id(OBJ_WANDS, j, ch);
                break;
            case 1:
                set_id(OBJ_SCROLLS, j, ch);
                break;
            case 2:
                set_id(OBJ_JEWELLERY, j, ch);
                break;
            case 3:
                set_id(OBJ_POTIONS, j, ch);
                break;
            }
        }
    }

    for (j = 0; j < 50; ++j)
        you.skills[j] = *p++;   /* skills! */

    for (j = 0; j < 50; ++j)
        you.practise_skill[j] = *p++;   /* skills! */

    for (j = 0; j < 50; ++j)
    {
        you.skill_points[j] = load_int(p, 6);

        if (minorVersion < 3)
        {
            // Convert older save files to new higher granular skill points
            you.skill_points[j] *= 10;
        }
    }

    for (j = 0; j < 50; ++j)
        you.unique_items[j] = *p++;     /* unique items */

    for (j = 0; j < 50; ++j)
        you.unique_creatures[j] = *p++;         /* unique creatures */

    for (j = 0; j < 30; ++j)
        you.duration[j] = *p++;

    for (j = 0; j < 30; ++j)
        you.attribute[j] = *p++;

    for (j = 0; j < 30; ++j)
        you.branch_stairs[j] = *p++;

    for (j = 0; j < 100; ++j)
        you.mutation[j] = *p++;

    for (j = 0; j < 50; ++j)
        you.had_item[j] = *p++;

    for (j = 0; j < 100; ++j)
        you.demon_pow[j] = *p++;

    for (j = 0; j < NO_UNRANDARTS; ++j)
        set_unrandart_exist(j, *p++);

    if (p != buf + datalen && p != buf + oldlen && p != (buf + oldlen + 42))
    {
        free(buf);
        perror("opa (5)...");
        end(-1);
    }
    free(buf);

}                               /* end of restore_game() */


void save_ghost()
{
    if ((you.your_level <= 1) || (you.is_undead != 0))
        return;

    char corr_level[10];
    char hbjh[5];
    char cha_fil[kFileNameSize];

    corr_level[0] = 0;
    if (you.your_level < 10)
        strcpy(corr_level, "0");
    itoa(you.your_level, hbjh, 10);
    strcat(corr_level, hbjh);
    corr_level[2] = you.where_are_you + 'a';
    corr_level[3] = 0;          /* null-terminate it */

#ifdef SAVE_DIR_PATH
    strcpy(cha_fil, SAVE_DIR_PATH "bones.");
#else
    strcpy(cha_fil, "bones.");
#endif

    if (you.level_type != 0)
        strcat(cha_fil, "lab"); /* temporary level */
    else
        strcat(cha_fil, corr_level);

//  int gfile=open(cha_fil, S_IWRITE, S_IREAD);
    FILE *gfile = fopen(cha_fil, "rb");

    if (gfile != NULL)
    {
        fclose(gfile);
        return;
    }

    unsigned char buf1[40];

    for (int i = 0; i < 20; ++i)
        buf1[i] = you.your_name[i];
    buf1[20] = (you.hp_max >= 150) ? (150) : (you.hp_max);
    buf1[21] = player_evasion();
    buf1[22] = player_AC();
    buf1[23] = player_see_invis();
    buf1[24] = player_res_fire();
    /* note - as ghosts, automatically get res poison + prot_life */
    buf1[25] = player_res_cold();
    buf1[26] = player_res_electricity();

    int d = 4;
    int e = 0;

    if (you.species == SP_TROLL)
        d += you.experience_level;
    d += you.skills[SK_UNARMED_COMBAT];         /* Unarmed combat */
    if (you.equip[EQ_WEAPON] != -1)
    {
        if (you.inv_class[you.equip[EQ_WEAPON]] == 0)
        {
            d = property(you.inv_class[you.equip[EQ_WEAPON]], you.inv_type[you.equip[EQ_WEAPON]], 0);
            if (you.inv_dam[you.equip[EQ_WEAPON]] < 180)
                e = you.inv_dam[you.equip[EQ_WEAPON]] % 30;
            if (you.inv_dam[you.equip[EQ_WEAPON]] % 30 >= 25)
                e = randart_wpn_properties(you.inv_class[you.equip[EQ_WEAPON]], you.inv_type[you.equip[EQ_WEAPON]], you.inv_dam[you.equip[EQ_WEAPON]], you.inv_plus[you.equip[EQ_WEAPON]], you.inv_plus2[you.equip[EQ_WEAPON]], 0, RAP_BRAND);
        }
        if (you.inv_class[you.equip[EQ_WEAPON]] == 11)
            d = 5;
    }

    if (((you.equip[EQ_WEAPON] != -1) && (you.inv_class[you.equip[EQ_WEAPON]] == 0)) ||
        (you.inv_class[you.equip[EQ_WEAPON]] == 11))
    {
        d *= 26 + you.skills[weapon_skill(you.inv_class[you.equip[EQ_WEAPON]], you.inv_type[you.equip[EQ_WEAPON]])];
        d /= 25;
    }

    d *= 31 + you.skills[SK_FIGHTING];
    d /= 30;

    d += you.strength / 4;
    if (d > 50)
        d = 50;

    buf1[27] = d;
    buf1[28] = e;
    buf1[29] = you.species;
    buf1[30] = best_skill(0, 50, 99);
    buf1[31] = you.skills[best_skill(0, 50, 99)];
    buf1[32] = you.experience_level;
    buf1[33] = you.char_class;
    add_spells(buf1);

    gfile = fopen(cha_fil, "wb");       //open(cha_fil, O_RDWR|O_CREAT|O_TRUNC|O_BINARY, 0660);

    if (gfile == NULL)
    {
        strcpy(info, "Error creating ghost file: ");
        strcat(info, cha_fil);
        mpr(info);
        more();
        return;
    }
    write2(gfile, (char *) buf1, 40);
    fclose(gfile);

#ifdef SHARED_FILES_CHMOD_VAL
    chmod(cha_fil, SHARED_FILES_CHMOD_VAL);
#endif
}


//int write2(int file, const void *buffer, unsigned count)
int write2(FILE * file, char *buffer, unsigned int count)
{

/*unsigned int i = 0;

   for (i = 0; i < count; i ++)
   {
   if (buffer [i] == EOF | buffer [i] == 26) buffer [i] = 0;
   } */

    return fwrite(buffer, 1, count, file);

//return write(file, buffer, count);

}

int read2(FILE * file, char *buffer, unsigned int count)
{

    return fread(buffer, 1, count, file);

}

/*
   Used when creating ghosts: goes through and finds spells for the ghost to
   cast. Death is a traumatic experience, so ghosts only remember a few spells.
 */
void add_spells(unsigned char buffer[40])
{

    int i = 0;

    buffer[34] = 250;
    buffer[35] = 250;
    buffer[36] = 250;
    buffer[37] = 250;
    buffer[38] = 250;
    buffer[39] = 250;

    buffer[34] = search_first_list(250);
    buffer[35] = search_first_list(buffer[34]);
    buffer[36] = search_second_list(250);
    buffer[37] = search_third_list(250);
    if (buffer[37] == 250)
        buffer[37] = search_first_list(250);
    buffer[38] = search_first_list(buffer[37]);
    if (buffer[38] == 250)
        buffer[38] = search_first_list(buffer[37]);
    if (find_spell(14) == 1)
        buffer[38] = 14;

/* Looks for blink/tport for emergency slot */
    if (find_spell(28) == 1 || find_spell(59) == 1)
        buffer[39] = 28;
    if (find_spell(1) == 1)
        buffer[39] = 1;

    for (i = 34; i < 40; i++)
    {
        buffer[i] = translate_spell(buffer[i]);
    }

}

unsigned char search_first_list(unsigned char ignore_spell)
{

    int i;

    for (i = 0; i < 20; i++)
    {
        if (search_order_conj[i] == 250)
            return 250;
        if (search_order_conj[i] == ignore_spell)
            continue;
        if (find_spell(search_order_conj[i]) == 1)
            return search_order_conj[i];
    }
    return 250;
}

unsigned char search_second_list(unsigned char ignore_spell)
{

    int i;

    for (i = 0; i < 20; i++)
    {
        if (search_order_third[i] == 250)
            return 250;
        if (search_order_third[i] == ignore_spell)
            continue;
        if (find_spell(search_order_third[i]) == 1)
            return search_order_third[i];
    }
    return 250;
}

unsigned char search_third_list(unsigned char ignore_spell)
{

    int i;

    for (i = 0; i < 20; i++)
    {
        if (search_order_misc[i] == 250)
            return 250;
        if (search_order_misc[i] == ignore_spell)
            continue;
        if (find_spell(search_order_misc[i]) == 1)
            return search_order_misc[i];
    }
    return 250;
}

/*
   Searches for a specific spell, according to search order in the global arrays
   defined start of file (top to bottom).
 */
char find_spell(unsigned char which_sp)
{

    int i = 0;

    for (i = 0; i < 21; i++)
    {
        if (you.spells[i] == which_sp)
            return 1;
    }

    return 0;

}


/*
   When passed the number for a player spell, returns the equivalent monster
   spell. Returns 250 on failure (no equiv).
 */
unsigned char translate_spell(unsigned char spel)
{
    switch (spel)
    {
    case 1:
        return 14;
    case 5:
        return 0;
    case 6:
        return 12;
    case 14:
        return 18;
    case 15:
        return 8;
    case 16:
        return 9;
    case 17:
        return 10;
    case 20:
        return 43;
    case 21:
        return 4;
    case 22:
        return 5;
    case 23:
        return 3;
    case 24:
        return 6;
    case 25:
        return 11;
    case 26:
        return 1;
    case 27:
        return 2;
    case 28:
        return 16;              /* approximate */
/*  case 29: return ; no freezing/mephitic cloud yet
   case 30: return ; */
    case 35:
        return 7;
    case 37:
        return 15;
    case 49:
        return 21;              /* approximate */
    case 53:
        return 19;
    case 54:
        return 17;
    case 59:
        return 16;
    case 60:
        return 22;
    case 62:
        return 24;              /* approximate */
    case 66:
        return 28;
    case 67:
        return 29;
    case 72:
        return 42;              /* approximate */
    case 79:
        return 31;
    case 82:
        return 33;
    case 113:
        return 52;
    case 115:
        return 38;
    case 119:
        return 27;
    case 120:
        return 33;
    case 121:
        return 51;
    case 128:
        return 39;
    case 129:
        return 40;
    case 148:
        return 48;              /* Too powerful to give ghosts Torment for Agony? Nah. */
    case 151:
        return 45;
    case 158:
        return 48;
    default:
        return 100;
    }

    return 100;

}


void generate_random_demon(void)
{

    int rdem = 0;
    int i = 0;

    for (rdem = 0; rdem < MNST + 1; rdem++)
    {
        if (rdem == MNST)
            return;             /* obviously no random demon */
        if (menv[rdem].type == 401)
            break;              /* found one! */
    }

    make_name(random2(250), random2(250), random2(250), 3, st_prn);
    strcpy(ghost.name, st_prn);

    ghost.values[0] = 50 + random2(50) + random2(50) + random2(50) + random2(50);
    if (random2(3) == 0)
        ghost.values[0] += random2(50) + random2(50);
/* hp - could be defined below (as could ev, AC etc). Oh well, too late */

    ghost.values[1] = 5 + random2(10);  /* evasion */
    ghost.values[2] = random2(0);       /* AC */
    if (random2(3) == 0)
        ghost.values[3] = 1;
    else
        ghost.values[3] = 0;    /* see inv */
    if (random2(3) != 0)
    {
        ghost.values[4] = 0;    /* res_fire */
        if (random2(4) == 0)
            ghost.values[4] = 99;
        if (random2(4) == 0)
            ghost.values[4] = 102;
    }
    else
        ghost.values[4] = 101;
    if (random2(3) != 0)
    {
        ghost.values[5] = 0;    /* res_cold */
        if (random2(4) == 0)
            ghost.values[5] = 99;
    }
    else
        ghost.values[5] = 101;
/* demons, as ghosts, automatically get res poison + prot_life */
    if (random2(3) != 0)
    {
        ghost.values[6] = 0;    /* res_elec */
    }
    else
        ghost.values[6] = 1;

    ghost.values[7] = 10 + random2(20) + random2(20) + random2(20);     /* damage in combat */
    ghost.values[8] = 0;        /* special attack type (uses weapon brand code) */
    if (random2(2) == 0)
    {
        ghost.values[8] = random2(17);
        if (ghost.values[8] == 3 || ghost.values[8] == 5 || ghost.values[8] == 7 || ghost.values[8] == 11 || ghost.values[8] == 12 || ghost.values[8] == 14)
            ghost.values[8] = 0;        /* some brands inappropriate (eg holy wrath) */
    }
    ghost.values[9] = 0;        /* ghost species - used for: is demon a spellcaster? */
    if (random2(3) != 0)
        ghost.values[9] = 1;
    ghost.values[10] = random2(3);      /* ghost best skill - used for: does demon fly? */
    if (random2(3) == 0)
        ghost.values[10] = 0;
    ghost.values[11] = 0;       /* vacant - ghost best skill level */
    ghost.values[12] = 10 + random2(10);        /* Hit Dice */
    ghost.values[13] = 0;       /* ghost class - used for: does demon cycle colours? */
    if (random2(10) == 0)
        ghost.values[13] = 1;

    menv[rdem].hit_dice = ghost.values[12];
    menv[rdem].hit_points = ghost.values[0];
    menv[rdem].max_hit_points = ghost.values[0];
    menv[rdem].armor_class = ghost.values[2];
    menv[rdem].evasion = ghost.values[1];
    menv[rdem].speed = 10;
    if (random2(3) == 0)
        menv[rdem].speed = 6 + random2(13);
    menv[rdem].speed_increment = 70;
    menv[rdem].number = 1 + random2(15);        /* demon's colour */

    ghost.values[14] = 250;
    ghost.values[15] = 250;
    ghost.values[16] = 250;
    ghost.values[17] = 250;
    ghost.values[18] = 250;
    ghost.values[19] = 250;

/* This bit uses the list of player spells to find appropriate spells
   for the demon, then converts those spells to the monster spell indices.
   Some special monster-only spells are at the end. */
    if (ghost.values[9] == 1)
    {
        if (random2(2) == 0)
            do
            {
                if (random2(3) == 0)
                    break;
                ghost.values[14] = search_order_conj[i];
                i++;
                if (search_order_conj[i] == 250)
                    break;
            }
            while (1);

        if (random2(2) == 0)
            do
            {
                if (random2(3) == 0)
                    break;
                ghost.values[15] = search_order_conj[i];
                i++;
                if (search_order_conj[i] == 250)
                    break;
            }
            while (1);

        if (random2(4) != 0)
            do
            {
                if (random2(3) == 0)
                    break;
                ghost.values[16] = search_order_third[i];
                i++;
                if (search_order_third[i] == 250)
                    break;
            }
            while (1);

        if (random2(2) == 0)
            do
            {
                if (random2(3) == 0)
                    break;
                ghost.values[17] = search_order_misc[i];
                i++;
                if (search_order_misc[i] == 250)
                    break;
            }
            while (1);

        if (random2(2) == 0)
            do
            {
                if (random2(3) == 0)
                    break;
                ghost.values[18] = search_order_misc[i];
                i++;
                if (search_order_misc[i] == 250)
                    break;
            }
            while (1);

        if (random2(2) == 0)
            ghost.values[19] = 59;      /* blink */
        if (random2(2) == 0)
            ghost.values[19] = 1;       /* teleport */

        for (i = 14; i < 20; i++)
        {
            ghost.values[i] = translate_spell(ghost.values[i]);
        }                       /* Converts the player spell indices to monster spell ones */

/* give demon a chance for some monster-only spells: */
        if (random2(25) == 0)
            ghost.values[14] = 50;      /* metal splinters */
        if (random2(25) == 0)
            ghost.values[14] = 37;      /* eye of devas */
        if (random2(25) == 0)
            ghost.values[15] = 26;      /* steam */
        if (random2(25) == 0)
            ghost.values[15] = 35;      /* blast */
        if (random2(25) == 0)
            ghost.values[15] = 49;      /* fiend's hellfire */
        if (random2(25) == 0)
            ghost.values[16] = 30;      /* smiting */
        if (random2(25) == 0)
            ghost.values[16] = 20;      /* burst of hellfire */
        if (random2(25) == 0)
            ghost.values[16] = 20;      /* burst of hellfire */
        if (random2(15) == 0)
            ghost.values[18] = 18;      /* dig */

/* and demon-summoning should be fairly common: */
        if (random2(12) == 0)
            ghost.values[16] = 51;      /* summon class 1 demons */
        if (random2(12) == 0)
            ghost.values[16] = 27;      /* summon demons */
        if (random2(20) == 0)
            ghost.values[17] = 51;      /* summon class 1 demons */
        if (random2(20) == 0)
            ghost.values[17] = 27;      /* summon demons */


        if (ghost.values[17] == 250)
            ghost.values[17] = 27;      /* at least they can summon demons */

    }


}
