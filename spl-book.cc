/*
 *  File:       spl-book.cc
 *  Summary:    Spellbook/Staff contents array and management functions
 *  Written by: Josh Fishman
 *
 *  Change History (most recent first):
 *
 *  <1> 19mar2000  jmf  Created by taking stuff from dungeon.cc, spells0.cc,
 *                      spells.cc, shopping.cc
 */


// This really needs to go somewhere else.
// jmf: hey, look, it's somewhere else!


/*
Spellbook binary thing:
6 spells: 127
5 spells: 126
4 spells: 124
3 spells: 120
2 spells: 112
1 spells: 96
0 spells: 64
(assuming all from start, no empty spaces)
*/


#include "AppHdr.h"
#include "spl-book.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef DOS
#include <conio.h>
#endif

#ifdef USE_CURSES
#include <curses.h>
#endif

#include "externs.h"

#include "debug.h"
#include "invent.h"
#include "it_use3.h"
#include "player.h"
#include "religion.h"
#include "spells.h"
#include "spells0.h"
#include "spl-util.h"
#include "stuff.h"


// jmf: these were globals in spells.cc
// but should they be global at all? {dlb}
int learned = 0;             // used in learn_a_spell() and which_spell() {dlb}
int spell_container = 0;     // used in which_spell() and which_spellbook()
int book_thing;              // definite externed variable - grep for it {dlb}


static bool which_spellbook(void);
unsigned char spellbook_contents(unsigned char plus, unsigned char type);




int spellbook_template_array[NUMBER_SPELLBOOKS][SPELLBOOK_SIZE] =
{

#ifdef USE_BETTER_MINOR_MAGIC_BOOKS

    // 0 - Minor Magic I
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FLAME,
     SPELL_BLINK,
     SPELL_CALL_IMP,
     SPELL_SLEEP,
     SPELL_SPIDER_FORM,
     SPELL_CONJURE_FLAME,
     SPELL_NO_SPELL,
    },
    // 1 - Minor Magic II
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FROST,
     SPELL_BLINK,
     SPELL_CALL_IMP,
     SPELL_SLOW,
     SPELL_MEPHITIC_CLOUD,
     SPELL_CONDENSATION_SHIELD,
     SPELL_NO_SPELL,
    },
    // 2 - Minor Magic III
    {0,
     SPELL_MAGIC_DART,
     SPELL_BLINK,
     SPELL_STICKS_TO_SNAKES,
     SPELL_LEVITATION,
     SPELL_MEPHITIC_CLOUD,
     SPELL_SLOW,
     SPELL_CONJURE_FLAME,
     SPELL_NO_SPELL,
    },
    // 3 - Book of Conjurations I
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FLAME,
     SPELL_MEPHITIC_CLOUD,
     SPELL_STONE_ARROW,
     SPELL_CONJURE_FLAME,
     SPELL_VENOM_BOLT,
     SPELL_BOLT_OF_FIRE,
     SPELL_NO_SPELL,
    },
    // 4 - Book of Conjurations II
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FROST,
     SPELL_MEPHITIC_CLOUD,
     SPELL_CONJURE_FLAME,
     SPELL_BOLT_OF_INACCURACY, //jmf: otherwise no one will ever see the descr.
     SPELL_VENOM_BOLT,
     SPELL_BOLT_OF_COLD,
     SPELL_NO_SPELL,
    },

#else

    // 0 - Minor Magic I
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FLAME,
     SPELL_SUMMON_SMALL_MAMMAL,
     SPELL_BLINK,
     SPELL_CONJURE_FLAME,
     SPELL_BOLT_OF_FIRE,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 1 - Minor Magic II
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FROST,
     SPELL_SUMMON_SMALL_MAMMAL,
     SPELL_BLINK,
     SPELL_SLOW,
     SPELL_BOLT_OF_COLD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 2 - Minor Magic III
    {0,
     SPELL_MAGIC_DART,
     SPELL_BLINK,
     SPELL_CONJURE_FLAME,
     SPELL_SLOW,
     SPELL_BOLT_OF_FIRE,
     SPELL_MEPHITIC_CLOUD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 3 - Book of Conjurations I
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FLAME,
     SPELL_MEPHITIC_CLOUD,
     SPELL_CONJURE_FLAME,
     SPELL_BOLT_OF_COLD,
     SPELL_LIGHTNING_BOLT,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 4 - Book of Conjurations II
    {0,
     SPELL_MAGIC_DART,
     SPELL_THROW_FROST,
     SPELL_MEPHITIC_CLOUD,
     SPELL_CONJURE_FLAME,
     SPELL_BOLT_OF_FIRE,
     SPELL_BOLT_OF_IRON,        //jmf: too much fire!
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },

#endif

    // 5 - Book of Flames
    {0,
     //SPELL_BURN,
     SPELL_FLAME_TONGUE,
     SPELL_THROW_FLAME,
     SPELL_CONJURE_FLAME,
     SPELL_STICKY_FLAME,
     SPELL_BOLT_OF_FIRE,
     SPELL_FIREBALL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 6 - Book of Frost
    {0,
     SPELL_FREEZE,
     SPELL_THROW_FROST,
     SPELL_OZOCUBUS_ARMOUR,
     SPELL_ICE_BOLT,
     SPELL_SUMMON_ICE_BEAST,
     SPELL_FREEZING_CLOUD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 7 - Book of Invocations //jmf: now Summonings
    {0,
     SPELL_ABJURATION_I,
     SPELL_RECALL,
     SPELL_SHADOW_CREATURES,
     SPELL_SWARM,
     SPELL_SUMMON_WRAITHS,
     SPELL_SUMMON_HORRIBLE_THINGS,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 8 - Book of Fire
    {0,
     SPELL_EVAPORATE,
     SPELL_FIRE_BRAND,
     SPELL_SUMMON_ELEMENTAL,
     SPELL_RING_OF_FLAMES,
     SPELL_FIRE_STORM,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 9 - Book of Ice
    {0,
     SPELL_FREEZING_AURA,
     SPELL_CONDENSATION_SHIELD,
     SPELL_BOLT_OF_COLD,
     SPELL_OZOCUBUS_REFRIGERATION,
     SPELL_ICE_STORM,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },

    // 10 - Book of Surveyances
    {0,
     SPELL_DETECT_SECRET_DOORS, //jmf: added
     SPELL_DETECT_TRAPS,
     //SPELL_DETECT_ITEMS, //jmf: moved to Book of Divinations
     SPELL_DETECT_CREATURES,
     SPELL_MAGIC_MAPPING,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 11 - Book of Spatial Translocations
    {0,
     SPELL_BEND,
     SPELL_BLINK,
     SPELL_WARP_BRAND,
     //SPELL_CONTROLLED_BLINK, //jmf: moved to Book of the Warp
     SPELL_CONTROL_TELEPORT,
     SPELL_TELEPORT_SELF,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 12 - Book of Enchantments (fourth one)
    {0,
     SPELL_SELECTIVE_AMNESIA,
     SPELL_LEVITATION,
     SPELL_REMOVE_CURSE,
     SPELL_CAUSE_FEAR,
     SPELL_DEFLECT_MISSILES,
     SPELL_EXTENSION,
     SPELL_HASTE,
     SPELL_NO_SPELL,
    },
    // 13 - Young Poisoner's Handbook
    {0,
     SPELL_STING,
     SPELL_CURE_POISON_II,
     SPELL_MEPHITIC_CLOUD,
     SPELL_POISON_WEAPON,
     SPELL_VENOM_BOLT,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 14 - Book of the Tempests
    {0,
     SPELL_DISCHARGE,
     SPELL_LIGHTNING_BOLT,      // Thunderbolt
     SPELL_FIREBALL,
     SPELL_SHATTER,
     SPELL_FIRE_STORM,
     SPELL_ICE_STORM,           //jmf: added
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 15 - Book of Death
    {0,
     SPELL_BOLT_OF_DRAINING,
     SPELL_BONE_SHARDS,
     SPELL_CORPSE_ROT,
     SPELL_LETHAL_INFUSION,
     SPELL_AGONY,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 16 - Book of Hinderance
    {0,
     SPELL_CONFUSING_TOUCH,
     SPELL_SLOW,
     SPELL_CONFUSE,             //jmf: added
     SPELL_SLEEP,
     SPELL_PARALYZE,
     SPELL_NO_SPELL, // jmf: was SPELL_TELEPORT_OTHER, but didn't fit
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 17 - Book of Changes
    {0,
     SPELL_DISRUPT,
     //SPELL_SANDBLAST, //jmf: maybe not put in here?
     SPELL_STICKS_TO_SNAKES,
     SPELL_PASSWALL,
     SPELL_SPIDER_FORM,
     SPELL_BLADE_HANDS,
     SPELL_POISON_AMMUNITION,
     SPELL_ICE_FORM,
     SPELL_NO_SPELL,
    },
    // 18 - Book of Transfigurations
    {0,
     SPELL_EVAPORATE,
     SPELL_DIG,
     SPELL_POLYMORPH_OTHER,
     SPELL_STATUE_FORM,
     SPELL_ALTER_SELF,
     SPELL_DRAGON_FORM,
     SPELL_NECROMUTATION,
     SPELL_NO_SPELL,
    },
    // 19 - Book of Practical Magic
    {0,
     SPELL_PROJECTED_NOISE,
     SPELL_SELECTIVE_AMNESIA,
     SPELL_DETECT_CURSE,
     SPELL_DIG,
     SPELL_REMOVE_CURSE,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },

    // 20 - Book of War Chants
    // NB: If anything added here, *must* change Crusader in crawlfnc.cc (no longer extant - {dlb})
    {0,
     SPELL_BACKLIGHT,
     SPELL_SURE_BLADE,
     SPELL_FIRE_BRAND,
     SPELL_FREEZING_AURA,
     SPELL_REPEL_MISSILES,
     SPELL_BERSERKER_RAGE,
     SPELL_REGENERATION,
     SPELL_FORESCRY,
     //SPELL_HASTE, //jmf: removed to make room for 1st level spell BACKLIGHT
    },
    // 21 - Book of Clouds
    {0,
     SPELL_EVAPORATE,
     SPELL_MEPHITIC_CLOUD,
     SPELL_CONJURE_FLAME,
     SPELL_POISONOUS_CLOUD,
     SPELL_FREEZING_CLOUD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 22 - Book of Healing
    {0,
     SPELL_CURE_POISON_I,
     SPELL_LESSER_HEALING,
     SPELL_GREATER_HEALING,
     SPELL_PURIFICATION,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 23 - Book of Necromancy
    {0,
     SPELL_PAIN,
     SPELL_ANIMATE_SKELETON,
     SPELL_VAMPIRIC_DRAINING,
     SPELL_REGENERATION,
     SPELL_DISPEL_UNDEAD,
     SPELL_ANIMATE_DEAD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 24 - Necronomicon
    {0,
     SPELL_SYMBOL_OF_TORMENT,
     SPELL_CONTROL_UNDEAD,
     SPELL_DEATHS_DOOR,
     SPELL_SUMMON_WRAITHS,
     SPELL_NECROMUTATION,
     SPELL_DEATH_CHANNEL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 25 - Book of Summonings //jmf: now Callings
    {0,
     SPELL_SUMMON_SMALL_MAMMAL,
     SPELL_STICKS_TO_SNAKES,
     SPELL_CALL_IMP,
     //SPELL_ABJURATION_I, //jmf: moved to Demonology and Summonings
     SPELL_SUMMON_SCORPIONS,
     SPELL_SUMMON_ICE_BEAST,
     SPELL_SUMMON_ELEMENTAL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 26 - Book of Charms
    {0,
     SPELL_BACKLIGHT,
     SPELL_CONFUSING_TOUCH,
     SPELL_SURE_BLADE,
     SPELL_REPEL_MISSILES,
#ifdef USE_SILENCE_CODE
     SPELL_SILENCE,
#endif
     SPELL_SLOW,
     SPELL_ENSLAVEMENT,
     SPELL_INVISIBILITY,
#ifndef USE_SILENCE_CODE
     SPELL_NO_SPELL,
#endif
    },
    // 27 - Book of Demonology
    {0,
     SPELL_ABJURATION_I,        //jmf: added
     SPELL_CALL_IMP,            //jmf: added
     SPELL_SUMMON_DEMON,
     SPELL_DEMONIC_HORDE,
     SPELL_SUMMON_GREATER_DEMON,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 28 - Book of Air
    {0,
     //SPELL_ARC,
     SPELL_SHOCK,  //jmf: moved back to level 1
     SPELL_SWIFTNESS,
     SPELL_REPEL_MISSILES,
     SPELL_LEVITATION,
     SPELL_DISCHARGE,      //jmf: added
     SPELL_MEPHITIC_CLOUD,
     SPELL_SUMMON_ELEMENTAL,
     SPELL_NO_SPELL,
    },
    // 29 - Book of the Sky
    {0,
#ifdef USE_SILENCE_CODE
     SPELL_SILENCE,
#endif
     SPELL_INSULATION,
     SPELL_AIRSTRIKE,
     SPELL_FLY,
     SPELL_DEFLECT_MISSILES,
     SPELL_LIGHTNING_BOLT,
     SPELL_ORB_OF_ELECTROCUTION,
     SPELL_AIR_WALK,
#ifndef USE_SILENCE_CODE
     SPELL_NO_SPELL,
#endif
    },

    // 30 - Book of Divinations
    {0,
     SPELL_DETECT_CREATURES,
     SPELL_DETECT_CURSE,
     SPELL_SEE_INVISIBLE,
     SPELL_FORESCRY,
     SPELL_IDENTIFY,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 31 - Book of the Warp
    {0,
     SPELL_RECALL,
     SPELL_WARP_FIELD,
     SPELL_CONTROLLED_BLINK,
     SPELL_TELEPORT_OTHER,
     SPELL_BANISHMENT,
     SPELL_PORTAL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 32 - Book of Toxins
    {0,
     SPELL_POISON_AMMUNITION,
     SPELL_SPIDER_FORM,
     SPELL_SUMMON_SCORPIONS,
     SPELL_RESIST_POISON,
     SPELL_OLGREBS_TOXIC_RADIANCE,
     SPELL_POISONOUS_CLOUD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 33 - Book of Annihilations
    {0,
     SPELL_ISKENDERUNS_MYSTIC_BLAST,
     SPELL_POISONOUS_CLOUD,
     SPELL_ORB_OF_ELECTROCUTION,
     SPELL_LEHUDIBS_CRYSTAL_SPEAR,
     SPELL_ICE_STORM,
     SPELL_FIRE_STORM,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 34 - Book of Unlife
    {0,
     SPELL_SUBLIMATION_OF_BLOOD,
     SPELL_ANIMATE_DEAD,
     SPELL_TWISTED_RESURRECTION,
     SPELL_BORGNJORS_REVIVIFICATION,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 35 - Tome of Destruction
    {0,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 36 - Book of Control
    {0,
     SPELL_CONFUSE,
     SPELL_ENSLAVEMENT,
     SPELL_CONTROL_TELEPORT,    //jmf: added
     SPELL_TAME_BEASTS,         //jmf: added
     SPELL_MASS_CONFUSION,
     SPELL_CONTROL_UNDEAD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 37 - Book of Mutations //jmf: now Morphology
    {0,
     SPELL_FRAGMENTATION,
     SPELL_POLYMORPH_OTHER,
     SPELL_ALTER_SELF,
     SPELL_CIGOTUVIS_DEGENERATION,
     SPELL_IGNITE_POISON,
     SPELL_SHATTER,
     SPELL_AIR_WALK,
     SPELL_NO_SPELL,
    },
    // 38 - Book of Tukima
    {0,
     SPELL_TUKIMAS_VORPAL_BLADE,
     SPELL_TUKIMAS_DANCE,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 39 - Book of Geomancy
    {0,
     //SPELL_CRUSH,
     SPELL_SANDBLAST,
     SPELL_PASSWALL,
     SPELL_STONE_ARROW,
     //SPELL_DIG,   //jmf: moved to Book of Earth
     SPELL_STATUE_FORM,
     SPELL_FRAGMENTATION,
     SPELL_BOLT_OF_IRON,
     SPELL_SUMMON_ELEMENTAL,
     SPELL_NO_SPELL,
    },
    // 40 - Book of Earth
    {0,
     SPELL_MAXWELLS_SILVER_HAMMER,
     SPELL_MAGIC_MAPPING,
     SPELL_DIG,
     SPELL_STONEMAIL,
     SPELL_TOMB_OF_DOROKLOHE,
     //SPELL_ORB_OF_FRAGMENTATION,
     SPELL_LEHUDIBS_CRYSTAL_SPEAR,
     SPELL_SHATTER,
     SPELL_NO_SPELL,
    },
    // 41 - manuals of all kinds
    {0,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 42 - Book of Wizardry
    {0,
     SPELL_DETECT_CREATURES,
     SPELL_SUMMON_ELEMENTAL,
     SPELL_MAGIC_MAPPING,
     SPELL_TELEPORT_SELF,
     SPELL_FIREBALL,
     SPELL_IDENTIFY,
     SPELL_HASTE,
     SPELL_NO_SPELL,
    },
    // 43 - Book of Power
    {0,
     SPELL_ANIMATE_DEAD,
     SPELL_VENOM_BOLT,
     SPELL_BOLT_OF_DRAINING,
     SPELL_BOLT_OF_IRON,
     SPELL_INVISIBILITY,
     SPELL_MASS_CONFUSION,
     SPELL_POISONOUS_CLOUD,
     SPELL_NO_SPELL,
    },
    // 44 - Book of Cantrips      //jmf: added 04jan2000
    {0,
     SPELL_CONFUSING_TOUCH,
     SPELL_ANIMATE_SKELETON,
     SPELL_STING,
     SPELL_SUMMON_SMALL_MAMMAL,
     SPELL_DISRUPT,
     SPELL_BACKLIGHT,
     SPELL_DETECT_SECRET_DOORS,
     SPELL_NO_SPELL,
    },
    // 45 - Book of Party Tricks  //jmf: added 04jan2000
    {0,
     SPELL_SUMMON_BUTTERFLIES,
     SPELL_BLINK,
     SPELL_PROJECTED_NOISE,
     SPELL_LEVITATION,
     SPELL_INTOXICATE,
     SPELL_NO_SPELL, //jmf: SPELL_ERINGYAS_SURPRISING_BOUQUET, when finished
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 46 - Book of Inobtrusiveness //jmf: added 19mar2000
    {0,
     SPELL_SWIFTNESS,
#ifdef USE_SILENCE_CODE
     SPELL_SILENCE,
#endif
     SPELL_SLEEP,
     SPELL_INVISIBILITY,
     SPELL_MASS_SLEEP,
     SPELL_AIR_WALK,
#ifndef USE_SILENCE_CODE
     SPELL_NO_SPELL,
#endif
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 47 - Book of Beasts //jmf: added 19mar2000
    {0,
     SPELL_SUMMON_SMALL_MAMMAL,
     SPELL_SUMMON_LARGE_MAMMAL,
     SPELL_DETECT_CREATURES,
     SPELL_STICKS_TO_SNAKES,
     SPELL_TAME_BEASTS,
     SPELL_SUMMON_DRAGON,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 48 - unused
    {0,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 49 - unused
    {0,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 50 - Staff of Smiting
    {0,
     SPELL_SMITING,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 51 - Staff of Summoning
    {0,
     SPELL_RECALL,
     SPELL_SUMMON_ELEMENTAL,
     SPELL_SUMMON_DEMON,
     SPELL_SWARM,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 52 - Staff of Destruction
    {0,
     SPELL_THROW_FLAME,
     SPELL_BOLT_OF_FIRE,
     SPELL_FIREBALL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 53 - Staff of Destruction
    {0,
     SPELL_THROW_FROST,
     SPELL_BOLT_OF_COLD,
     SPELL_LIGHTNING_BOLT, // value (17) and label do not match 22jan2000 {dlb}
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 54 - Staff of Destruction
    {0,
     SPELL_FIREBALL,
     SPELL_LIGHTNING_BOLT,      // Thunderbolt     // see above 22jan2000 {dlb}
     SPELL_LEHUDIBS_CRYSTAL_SPEAR,     // Throw splinters
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 55 - Staff of Destruction
    {0,
     SPELL_BOLT_OF_INACCURACY,
     SPELL_BOLT_OF_FIRE,
     SPELL_BOLT_OF_COLD,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 56 - Staff of Warding
    {0,
     SPELL_REPEL_UNDEAD,
     SPELL_CAUSE_FEAR,
     SPELL_ABJURATION_I,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 57 - Staff of Exploration
    {0,
     SPELL_DETECT_SECRET_DOORS,
     SPELL_DETECT_TRAPS,
     SPELL_DETECT_ITEMS,
     SPELL_MAGIC_MAPPING,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    },
    // 58 - Staff of Demonology
    {0,
     SPELL_RECALL,
     SPELL_SUMMON_DEMON,
     SPELL_DEMONIC_HORDE,
     SPELL_SUMMON_GREATER_DEMON,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
     SPELL_NO_SPELL,
    }
};




void spellbook_template( int sbook_type, int sbtemplate_pass[SPELLBOOK_SIZE] )    // was foo[10] {dlb}
{

    ASSERT(sbook_type >= 0);
    ASSERT(sbook_type < NUMBER_SPELLBOOKS);

// no point doing anything if tome of destruction or a manual
    if ( sbook_type == BOOK_DESTRUCTION || sbook_type == BOOK_MANUAL )
      return;

    for (int i = 1; i < SPELLBOOK_SIZE; i++)
      sbtemplate_pass[i] = spellbook_template_array[sbook_type][i];

}          // end spellbook_template()




int which_spell_in_book( int sbook_type, int spl )
{

    int wsib_pass[SPELLBOOK_SIZE];    // was 10 {dlb}

    spellbook_template(sbook_type, wsib_pass);

    return wsib_pass[spl];

}          // end which_spell_in_book()




unsigned char spellbook_contents(unsigned char plus, unsigned char type)
{

    unsigned char i;     // loop variable {dlb}
    char already = 0;
    int spell_types[SPELLBOOK_SIZE];    // was 10 {dlb}
    char stringy[10];
    int spelcount = 0;


#ifdef DOS_TERM
    char buffer[4800];

    gettext(1, 1, 80, 25, buffer);

    window(1, 1, 80, 25);
#endif

    clrscr();

    spellbook_template(type, spell_types);

    itoa(plus, stringy, 2);

    textcolor(LIGHTGREY);
    cprintf(" Spells                             Type                      Level" EOL);

    for (int j = 1; j < SPELLBOOK_SIZE; j++)
    {
        if (spell_types[j] == SPELL_NO_SPELL)
          continue;

        cprintf(" ");
        bool knowsSpell = false;

        for (i = 0; i < 25 && !knowsSpell; i++)
          knowsSpell = (you.spells[i] == spell_types[j]);

        textcolor(knowsSpell ? DARKGREY : LIGHTGREY);    // was: ? LIGHTGREY : LIGHTBLUE

        char strng[2];

        strng[0] = index_to_letter(spelcount);
        strng[1] = '\0';

        cprintf(strng);
        cprintf(" - ");

        cprintf(spell_title(spell_types[j]));
        gotoxy(35, wherey());

        already = 0;

        for (i = SPTYP_CONJURATION; i < NUM_SPELL_TYPES; i++)
          if ( spell_typematch(spell_types[j], i) )
          {
              print_slash(already);
              cprintf(spelltype_name(i));
              already = 1;
          }

        gotoxy(65, wherey());

        char sval[2];

        itoa((int) spell_difficulty(spell_types[j]), sval, 10);
        cprintf(sval);
        cprintf(EOL);
        spelcount++;
    }

    unsigned char keyn = getch();

    if ( keyn == 0 )
      getch();

#ifdef DOS_TERM
    puttext(1, 1, 80, 25, buffer);
    window(1, 18, 80, 25);
#endif

    return keyn;     // try to figure out that for which this is used {dlb}

}




// jmf: was in shopping.cc
char book_rarity( unsigned char which_book )
{

    switch ( which_book )
    {
      case BOOK_MINOR_MAGIC_I:
      case BOOK_MINOR_MAGIC_II:
      case BOOK_MINOR_MAGIC_III:
      case BOOK_SURVEYANCES:
      case BOOK_YOUNG_POISONERS:
      case BOOK_HINDERANCE:
      case BOOK_CANTRIPS: //jmf: added 04jan2000
        return 1;

      case BOOK_CHANGES:
      case BOOK_CHARMS:
        return 2;

      case BOOK_CONJURATIONS_I:
      case BOOK_CONJURATIONS_II:
      case BOOK_PRACTICAL_MAGIC:
      case BOOK_NECROMANCY:
      case BOOK_SUMMONINGS:
      case BOOK_WIZARDRY:
        return 3;

      case BOOK_FLAMES:
      case BOOK_FROST:
      case BOOK_AIR:
      case BOOK_GEOMANCY:
        return 4;

      case BOOK_SPATIAL_TRANSLOCATIONS:
        return 5;

      case BOOK_CLOUDS:
      case BOOK_WARP:
      case BOOK_POWER:
        return 6;

      case BOOK_ENCHANTMENTS:
      case BOOK_PARTY_TRICKS:     //jmf: added 04jan2000
        return 7;

      case BOOK_TRANSFIGURATIONS:
      case BOOK_DIVINATIONS:
        return 8;

      case BOOK_FIRE:
      case BOOK_ICE:
      case BOOK_SKY:
      case BOOK_EARTH:
      case BOOK_UNLIFE:
      case BOOK_CONTROL:
        return 10;

      case BOOK_TEMPESTS:
      case BOOK_DEATH:
      case BOOK_INOBTRUSIVENESS: //jmf: added 23mar2000
        return 11;

      case BOOK_TOXINS:
      case BOOK_MUTATIONS:
      case BOOK_BEASTS: //jmf: added 23mar2000
        return 12;

      case BOOK_DEMONOLOGY:
        return 15;

      case BOOK_TUKIMA:
        return 16;

      case BOOK_ANNIHILATIONS:
        return 17;

      case BOOK_INVOCATIONS:
        return 18;

      case BOOK_NECRONOMICON:
      case BOOK_MANUAL:
        return 20;

      case BOOK_DESTRUCTION:
        return 30;

      case BOOK_HEALING:          // never created naturally
        return 100;

    default:
        return 1;
    }

}          // end book_rarity()




bool learn_a_spell( unsigned char splbook, char bitty )
{

    int spells[SPELLBOOK_SIZE];

    spellbook_template(you.inv_type[splbook], spells);

    if ( spells[bitty] != SPELL_NO_SPELL )
    {
        learned = 1 + bitty;
        return true;
    }
    else
      return false;

}          // end learn_a_spell()




static bool which_spellbook( void )
{

    unsigned char nthing = 0;
    unsigned char keyin;
    int sc_read_1, sc_read_2;

    if ( player_spell_levels() < 1 )
      {
        mpr("You can't memorise any more spells yet.");
        return false;
      }
    else if ( you.num_inv_items < 1 )
      {
        canned_msg(MSG_NOTHING_CARRIED);
        return false;
      }

query:
    strcpy(info, "You can memorise ");
    itoa(player_spell_levels(), st_prn, 10);
    strcat(info, st_prn);
    strcat(info, " more level");
    if ( !(st_prn[0] == '1' && st_prn[1] == 0) )
      strcat(info, "s");
    strcat(info, " of spells");
    strcat(info, ".");
    mpr(info);

    mpr("Memorise from which spellbook?");

    keyin = get_ch();

    if (keyin == '?' || keyin == '*')
    {
        if (keyin == '?')
          nthing = get_invent(OBJ_BOOKS);

        if (keyin == '*')
          nthing = get_invent(-1);

        if ( ( nthing >= 'A' && nthing <= 'Z' ) || ( nthing >= 'a' && nthing <= 'z' ) )
          keyin = nthing;
        else
        {
            mesclr();
            goto query;
        }
    }

    sc_read_1 = (int) keyin;

    if ( sc_read_1 < 'A' || ( sc_read_1 > 'Z' && sc_read_1 < 'a' ) || sc_read_1 > 'z' )
    {
        mpr("You don't have any such object.");
        return false;
    }

    sc_read_2 = letter_to_index(sc_read_1);

    if (you.inv_quantity[sc_read_2] == 0)
    {
        mpr("You haven't any such object.");
        return false;
    }

    if (you.inv_class[sc_read_2] != OBJ_BOOKS
        || you.inv_type[sc_read_2] == BOOK_MANUAL)
    {
        mpr("That isn't a spellbook!");
        return false;
    }

    if (you.inv_type[sc_read_2] == BOOK_DESTRUCTION)
    {
        tome_of_power(sc_read_2);
        return false;
    }

    spell_container = sc_read_2;

    read_book(spell_container);

    clrscr();

    return true;

}          // end which_spellbook()




void read_book( unsigned char book_read )
{

    unsigned char key2 = 0;
    unsigned char keyin;

// remember that this function is called from staff spells as well:
    key2 = spellbook_contents(you.inv_plus[book_read], ( (you.inv_class[book_read] == OBJ_STAVES) ? 40 + you.inv_type[book_read] : you.inv_type[book_read] ));

    if ( you.inv_class[book_read] == OBJ_BOOKS )
    {
        you.had_item[you.inv_type[book_read]] = 1;

        if ( you.inv_type[book_read] == BOOK_MINOR_MAGIC_I
              || you.inv_type[book_read] == BOOK_MINOR_MAGIC_II
              || you.inv_type[book_read] == BOOK_MINOR_MAGIC_III )
        {
            you.had_item[BOOK_MINOR_MAGIC_I] = 1;
            you.had_item[BOOK_MINOR_MAGIC_II] = 1;
            you.had_item[BOOK_MINOR_MAGIC_III] = 1;
        }

        else if ( you.inv_type[book_read] == BOOK_CONJURATIONS_I
                   || you.inv_type[book_read] == BOOK_CONJURATIONS_II )
        {
            you.had_item[BOOK_CONJURATIONS_I] = 1;
            you.had_item[BOOK_CONJURATIONS_II] = 1;
        }
    }

#ifdef PLAIN_TERM
    redraw_screen();
#endif

    /* Put special book effects in another function which can be called from
       memorise as well */

    you.turn_is_over = 1;
    you.inv_ident[book_read] = 1;
    book_thing = key2;
    keyin = key2;   // FIX this should probably go...  // I agree {dlb}

}          // end read_book()




void which_spell( void )
{

    int chance = 0;
    int levels_needed = 0;
    int sc_read_1, sc_read_2;
    unsigned char keyin;

    int i;
    int j = 0;

    for (i = SK_SPELLCASTING; i <= SK_POISON_MAGIC; i++)
      if ( you.skills[i] )
        j++;

    if (j == 0)
      {
        mpr("You can't use spell magic! I'm afraid it's scrolls only for now.");
        return;
      }

    if ( !which_spellbook() )
      return;

    sc_read_1 = (int) book_thing;

    if ( sc_read_1 < 'A' || ( sc_read_1 > 'Z' && sc_read_1 < 'a' ) || sc_read_1 > 'z' )
    {
whatt:

#ifdef PLAIN_TERM
        redraw_screen();
#endif

        mpr("What?");
        return;
    }

    sc_read_2 = letter_to_index(sc_read_1);

    if ( sc_read_2 > SPELLBOOK_SIZE )
      goto whatt;

    if ( !learn_a_spell(spell_container, sc_read_2) )
      goto whatt;

    unsigned char specspell = which_spell_in_book(you.inv_type[spell_container], learned);

    if ( specspell == SPELL_NO_SPELL )
      goto whatt;

// if changed, must also change for priest in level_change.
// You can always memorise selective amnesia:
    if ( you.spell_no == 21 && specspell != SPELL_SELECTIVE_AMNESIA )
    {
        mpr("Your head is already too full of spells!");
        return;
    }

    if (you.species == SP_MUMMY && spell_typematch(specspell, SPTYP_HOLY))
    {
        mpr("You cannot use this type of magic!");
        return;
    }

    if ( undead_cannot_memorise(specspell, you.is_undead) )
    {
        mpr("You cannot use this spell.");
        return;
    }

    for (i = 0; i < 25; i++)
    {
        if (you.spells[i] == specspell)
        {
#ifdef PLAIN_TERM
            redraw_screen();
#endif
            mpr("You already know that spell!");
            you.turn_is_over = 1;
            return;
        }
    }

    levels_needed = spell_difficulty(specspell);

    if ( player_spell_levels() < levels_needed )
    {
#ifdef PLAIN_TERM
        redraw_screen();
#endif
        mpr("You can't memorise that many levels of magic yet!");
        //sprintf( info, "levels: %d  needed: %d  spec_spells: %d", player_spell_levels(), levels_needed, specspell);
        //mpr(info);
        you.turn_is_over = 1;
        return;
    }

    if (you.experience_level < spell_difficulty(specspell))
    {
#ifdef PLAIN_TERM
        redraw_screen();
#endif
        mpr("You're too inexperienced to learn that spell!");
        you.turn_is_over = 1;
        return;
    }

    chance = spell_fail(specspell);

#ifdef PLAIN_TERM
    redraw_screen();
#endif

    strcpy(info, "This spell is ");

    strcat(info, (chance >= 80) ? "very" :
                 (chance >= 60) ? "quite" :
                 (chance >= 45) ? "rather" :
                 (chance >= 30) ? "somewhat"
                                : "not that" );
    strcat(info, " ");

    int temp_rand = random2(3);

    strcat(info, (temp_rand == 0) ? "difficult" :
                 (temp_rand == 1) ? "tricky" :
                 (temp_rand == 2) ? "challenging"
                                  : "" );

    strcat(info, " to ");

    temp_rand = random2(4);

    strcat(info, (temp_rand == 0) ? "memorise" :
                 (temp_rand == 1) ? "commit to memory" :
                 (temp_rand == 2) ? "learn" :
                 (temp_rand == 3) ? "absorb"
                                  : "" );

    strcat(info, ".");

    mpr(info);

    strcpy(info, "Memorise ");
    strcat(info, spell_title(specspell));
    strcat(info, "?");
    mpr(info);

    for (;;)
    {
        keyin = getch();

        if ( keyin == 'n' || keyin == 'N' )
        {
#ifdef PLAIN_TERM
            redraw_screen();
#endif
            return;
        }

        if ( keyin == 'y' || keyin == 'Y' )
          break;
    }

    mesclr();

    if ( you.mutation[MUT_BLURRY_VISION] > 0
        && random2(4) < you.mutation[MUT_BLURRY_VISION] )
    {
        mpr("The writing blurs into unreadable gibberish.");
        you.turn_is_over = 1;
        return;
    }

    if (random2(40) + random2(40) + random2(40) < chance)
    {
#ifdef PLAIN_TERM
        redraw_screen();
#endif
        mpr("You fail to memorise the spell.");
        you.turn_is_over = 1;

        if ( you.inv_type[spell_container] == BOOK_NECRONOMICON )
        {
            mpr("The pages of the Necronomicon glow with a malevolent light...");
            miscast_effect(SPTYP_NECROMANCY, 8, random2avg(88,3), 100);
        }
        else if ( you.inv_type[spell_container] == BOOK_DEMONOLOGY )
        {
            mpr("This book does not appreciate being disturbed by one of your ineptitude!");
            miscast_effect(SPTYP_SUMMONING, 7, random2avg(88,3), 100);
        }
        else if ( you.inv_type[spell_container] == BOOK_ANNIHILATIONS )
        {
            mpr("This book does not appreciate being disturbed by one of your ineptitude!");
            miscast_effect(SPTYP_CONJURATION, 8, random2avg(88,3), 100);
        }

#ifdef WIZARD
        if ( !yesno("Memorize anyway?") )
#endif
          return;
    }

    for (i = 0; i < 25; i++)
      if (you.spells[i] == SPELL_NO_SPELL)
        break;

    you.spells[i] = specspell;

    //you.spell_levels -= levels_needed;
    you.spell_no++;

    you.delay_t = spell_difficulty(you.spells[i]);
    you.delay_doing = 3;

    you.turn_is_over = 1;

#ifdef PLAIN_TERM
    redraw_screen();
#endif

    naughty(NAUGHTY_SPELLCASTING, 2 + random2(5));    // is learning as bad as casting, then? {dlb}

}          // end which_spell()




char *spelltype_name( unsigned char which_spelltype )
{

    switch ( which_spelltype )
    {
      case SPTYP_CONJURATION:
        return "Conjuration";
      case SPTYP_ENCHANTMENT:
        return "Enchantment";
      case SPTYP_FIRE:
        return "Fire";
      case SPTYP_ICE:
        return "Ice";
      case SPTYP_TRANSMIGRATION:
        return "Transmigration";
      case SPTYP_NECROMANCY:
        return "Necromancy";
      case SPTYP_HOLY:
        return "Holy";
      case SPTYP_SUMMONING:
        return "Summoning";
      case SPTYP_DIVINATION:
        return "Divination";
      case SPTYP_TRANSLOCATION:
        return "Translocation";
      case SPTYP_POISON:
        return "Poison";
      case SPTYP_EARTH:
        return "Earth";
      case SPTYP_AIR:
        return "Air";
      default:
        return "Bugation";
    }

}          // end spelltype_name()