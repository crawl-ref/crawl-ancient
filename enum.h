/*
 *  File:       enum.h
 *  Summary:    Global (ick) enums.
 *  Written by: Linley Henzell
 *
 *  Change History (most recent first):
 *
 *      <5>     9/9/99          BWR             Removed Great Swords skill
 *      <4>     8/6/99          BWR             added branch and level types
 *      <3>     6/2/99          DML             beams, clouds, ench, ms, kill,
                                                other minor changes
 *      <2>     5/26/99         JDJ             Added a header guard.
 *      <1>     -/--/--         LRH             Created
 */
#ifndef ENUM_H
#define ENUM_H


enum ABILITIES
{
    ABIL_SPIT_POISON = 1,
    ABIL_MAPPING,
    ABIL_TELEPORTATION,
    ABIL_BREATHE_FIRE,
    ABIL_BLINK,
    ABIL_BREATHE_FROST,
    ABIL_BREATHE_POISON,
    ABIL_BREATHE_LIGHTNING,
    ABIL_SPIT_ACID,
    ABIL_BREATHE_POWER,
    ABIL_GO_BERSERK_I,
    ABIL_BREATHE_STICKY_FLAME,
    ABIL_BREATHE_STEAM,
    ABIL_FLY,
    ABIL_SUMMON_MINOR_DEMON,
    ABIL_SUMMON_DEMON,
    ABIL_HELLFIRE,
    ABIL_TORMENT,
    ABIL_RAISE_DEAD,
    ABIL_CONTROL_DEMON,
    ABIL_TO_PANDEMONIUM,
    ABIL_CHANNELING,
    ABIL_THROW_FLAME,
    ABIL_THROW_FROST,
    ABIL_BOLT_OF_DRAINING,
    ABIL_TURN_INVISIBLE = 51,
    ABIL_TURN_VISIBLE,
    ABIL_LEVITATE,
    ABIL_STOP_LEVITATING,
    ABIL_END_TRANSFORMATION,
    ABIL_REPEL_UNDEAD_I = 110,
    ABIL_MINOR_HEALING,
    ABIL_PESTILENCE,
    ABIL_HOLY_WORD,
    ABIL_SUMMON_GUARDIAN,
    ABIL_REPEL_UNDEAD_II = 120,
    ABIL_SMITING,
    ABIL_ANNIHILATE_UNDEAD,
    ABIL_THUNDERBOLT,
    ABIL_SUMMON_DAEVA,
    ABIL_RECALL_UNDEAD_SLAVES = 130,
    ABIL_ENSLAVE_UNDEAD = 132,
    ABIL_INVOKE_DEATH,
    ABIL_ANIMATE_CORPSE = 140,
    ABIL_RECALL_UNDEAD,
    ABIL_ANIMATE_DEAD,
    ABIL_DRAIN_LIFE,
    ABIL_CONTROL_UNDEAD,
    ABIL_CHANNEL_ENERGY = 160,
    ABIL_MIGHT_I = 170,
    ABIL_HEALING_I,
    ABIL_HASTE,
    ABIL_MINOR_DESTRUCTION = 180,
    ABIL_LESSER_SERVANT_OF_MAKHLEB,
    ABIL_MAJOR_DESTRUCTION,
    ABIL_GREATER_SERVANT_OF_MAKHLEB,
    ABIL_FORGET_SPELL = 190,
    ABIL_GO_BERSERK_II = 200,
    ABIL_MIGHT_II,
    ABIL_HASTE_SELF,
    ABIL_LESSER_HEALING = 220,
    ABIL_PURIFICATION,
    ABIL_HEALING_II,
    ABIL_RESTORATION,
    ABIL_GREATER_HEALING,
    ABIL_RENOUNCE_RELIGION = 250
};

enum AMMUNITION_DESCRIPTIONS
{
    DAMMO_ORCISH = 3,
    DAMMO_ELVEN,
    DAMMO_DWARVEN
};

enum ARMOUR
{
    ARM_ROBE,
    ARM_LEATHER_ARMOUR,
    ARM_RING_MAIL,
    ARM_SCALE_MAIL,
    ARM_CHAIN_MAIL,
    ARM_SPLINT_MAIL,
    ARM_BANDED_MAIL,
    ARM_PLATE_MAIL,
    ARM_SHIELD,
    ARM_CLOAK,
    ARM_HELMET,
    ARM_GLOVES,
    ARM_BOOTS,
    ARM_BUCKLER,
    ARM_LARGE_SHIELD,
    ARM_DRAGON_HIDE,
    ARM_TROLL_HIDE,
    ARM_CRYSTAL_PLATE_MAIL,
    ARM_DRAGON_ARMOUR,
    ARM_TROLL_LEATHER_ARMOUR,
    ARM_ICE_DRAGON_HIDE,
    ARM_ICE_DRAGON_ARMOUR,
    ARM_STEAM_DRAGON_HIDE,
    ARM_STEAM_DRAGON_ARMOUR,
    ARM_MOTTLED_DRAGON_HIDE,
    ARM_MOTTLED_DRAGON_ARMOUR,
    ARM_STORM_DRAGON_HIDE,
    ARM_STORM_DRAGON_ARMOUR,
    ARM_GOLD_DRAGON_HIDE,
    ARM_GOLD_DRAGON_ARMOUR,
    ARM_ANIMAL_SKIN,
    ARM_SWAMP_DRAGON_HIDE,
    ARM_SWAMP_DRAGON_ARMOUR
};

enum ARMOUR_DESCRIPTIONS
{
    DARM_EMBROIDERED_SHINY = 1,
    DARM_RUNED,
    DARM_GLOWING,
    DARM_ELVEN,
    DARM_DWARVEN,
    DARM_ORCISH
};

enum ARMOUR_PROPERTIES
{
    PARM_AC,
    PARM_EVASION
};

enum ATTRIBUTES
{
    ATTR_DIVINE_LIGHTNING_PROTECTION,
    ATTR_SPEC_AIR,
    ATTR_SPEC_EARTH,
    ATTR_CONTROL_TELEPORT,
    ATTR_WALK_SLOWLY,
    ATTR_TRANSFORMATION,
    ATTR_CARD_COUNTDOWN,
    ATTR_CARD_TABLE,
    ATTR_NUM_DEMONIC_POWERS
};

enum BEAMS
{
  BEAM_MISSILE = 0,
  BEAM_MMISSILE,
  BEAM_FIRE,
  BEAM_COLD,
  BEAM_MAGIC,
  BEAM_ELECTRICITY,
  BEAM_POISON,
  BEAM_NEG,
  BEAM_CLOUD,
  BEAM_EXPLOSION = 10,
  BEAM_SPORE,
  BEAM_HOLY = 18,
  BEAM_FRAG = 19,
  BEAM_LAVA = 20,
  BEAM_ICE = 23,
  BEAM_NUKE = 27
};

//
// These represent the dungeon branches you can be in (you.where_are_you).
//
enum BRANCHES
{
   BRANCH_MAIN_DUNGEON,
   BRANCH_DIS,
   BRANCH_GEHENNA,
   BRANCH_VESTIBULE_OF_HELL,
   BRANCH_COCYTUS,
   BRANCH_TARTARUS,
   BRANCH_INFERNO,
   BRANCH_THE_PIT,
   BRANCH_ORCISH_MINES = 10,
   BRANCH_HIVE,
   BRANCH_LAIR,
   BRANCH_SLIME_PITS,
   BRANCH_VAULTS,
   BRANCH_CRYPT,
   BRANCH_HALL_OF_BLADES,
   BRANCH_HALL_OF_ZOT,
   BRANCH_ECUMENICAL_TEMPLE,
   BRANCH_SNAKE_PIT,
   BRANCH_ELVEN_HALLS,
   BRANCH_TOMB,
   BRANCH_SWAMP
};

//
// These represent the indices of the stair locations (you.branch_stairs[]).
//
enum BRANCH_STAIRS
{
    STAIRS_ORCISH_MINES,
    STAIRS_HIVE,
    STAIRS_LAIR,
    STAIRS_SLIME_PITS,
    STAIRS_VAULTS,
    STAIRS_CRYPT,
    STAIRS_HALL_OF_BLADES,
    STAIRS_HALL_OF_ZOT,
    STAIRS_ECUMENICAL_TEMPLE,
    STAIRS_SNAKE_PIT,
    STAIRS_ELVEN_HALLS,
    STAIRS_TOMB,
    STAIRS_SWAMP
};

enum BOOKS
{
    BOOK_MINOR_MAGIC_I,
    BOOK_MINOR_MAGIC_II,
    BOOK_MINOR_MAGIC_III,
    BOOK_CONJURATIONS_I,
    BOOK_CONJURATIONS_II,
    BOOK_FLAMES,
    BOOK_FROST,
    BOOK_INVOCATIONS,
    BOOK_FIRE,
    BOOK_ICE,
    BOOK_SURVEYANCES,
    BOOK_SPATIAL_TRANSLOCATIONS,
    BOOK_ENCHANTMENTS,
    BOOK_POISONINGS,
    BOOK_STORMS_AND_FIRE,
    BOOK_DEATH,
    BOOK_HINDERANCE,
    BOOK_CHANGES,
    BOOK_TRANSFIGURATIONS,
    BOOK_USEFUL_MAGIC,
    BOOK_WAR_CHANTS,
    BOOK_CLOUDS,
    BOOK_HEALING,
    BOOK_NECROMANCY,
    BOOK_NECRONOMICON,
    BOOK_SUMMONINGS,
    BOOK_CHARMS,
    BOOK_DEMONOLOGY,
    BOOK_AIR,
    BOOK_SKY,
    BOOK_DIVINATIONS,
    BOOK_WARP,
    BOOK_ENVENOMATIONS,
    BOOK_ANNIHILATIONS,
    BOOK_UNLIFE,
    BOOK_DESTRUCTION,
    BOOK_CONTROL,
    BOOK_MUTATIONS,
    BOOK_TUKIMA,
    BOOK_GEOMANCY,
    BOOK_EARTH,
    BOOK_MANUAL,
    BOOK_WIZARDRY,
    BOOK_POWER,

    NUM_BOOKS
};

enum CLOUD_TYPES
{
     CLOUD_NONE,
     CLOUD_FIRE,
     CLOUD_STINK,
     CLOUD_COLD,
     CLOUD_POISON,
     CLOUD_ENERGY = 7,
     CLOUD_STEAM,
     CLOUD_STICKY_FLAME = 10,
     CLOUD_POISON_MON = 104
};

enum DELAY
{
  DELAY_EAT,
  DELAY_ARMOR_ON,
  DELAY_ARMOR_OFF,
  DELAY_MEMORIZE,
  DELAY_BUTCHER,
  DELAY_AUTOPICKUP
};

enum DEMON_BEAMS
{
    DMNBM_HELLFIRE,
    DMNBM_SMITING,
    DMNBM_BRAIN_FEED,
    DMNBM_MUTATION
};

enum DUNGEON_FEATURES
{
    DNGN_UNSEEN,
    DNGN_ROCK_WALL,
    DNGN_STONE_WALL,
    DNGN_CLOSED_DOOR,
    DNGN_METAL_WALL,
    DNGN_SECRET_DOOR,
    DNGN_GREEN_CRYSTAL_WALL,
    DNGN_ORCISH_IDOL,
    DNGN_WAX_WALL,
    DNGN_LAVA_X = 11,
    DNGN_WATER_X,
    DNGN_SILVER_STATUE = 21,
    DNGN_GRANITE_STATUE,
    DNGN_ORANGE_CRYSTAL_STATUE,
    DNGN_STATUE_35 = 35,
    DNGN_STATUE_39 = 39,
    DNGN_LAVA = 61,
    DNGN_DEEP_WATER,
    DNGN_SHALLOW_WATER = 65,
    DNGN_WATER_STUCK,
    DNGN_FLOOR = 67,
    DNGN_ENTER_HELL = 69,
    DNGN_OPEN_DOOR,
    DNGN_BRANCH_STAIRS,
    DNGN_TRAP_I = 75,
    DNGN_TRAP_II,
    DNGN_TRAP_III,
    DNGN_UNDISCOVERED_TRAP,
    DNGN_ENTER_SHOP = 80,
    DNGN_ENTER_LABYRINTH,
    DNGN_STONE_STAIRS_DOWN_I,
    DNGN_STONE_STAIRS_DOWN_II,
    DNGN_STONE_STAIRS_DOWN_III,
    DNGN_ROCK_STAIRS_DOWN,
    DNGN_STONE_STAIRS_UP_I,
    DNGN_STONE_STAIRS_UP_II,
    DNGN_STONE_STAIRS_UP_III,
    DNGN_ROCK_STAIRS_UP,
    DNGN_ENTER_DIS = 92,
    DNGN_ENTER_GEHENNA,
    DNGN_ENTER_COCYTUS,
    DNGN_ENTER_TARTARUS,
    DNGN_ENTER_ABYSS,
    DNGN_EXIT_ABYSS,
    DNGN_STONE_ARCH,
    DNGN_ENTER_PANDEMONIUM,
    DNGN_EXIT_PANDEMONIUM,
    DNGN_TRANSIT_PANDEMONIUM,
    DNGN_ENTER_ORCISH_MINES = 110,
    DNGN_ENTER_HIVE,
    DNGN_ENTER_LAIR_I,
    DNGN_ENTER_SLIME_PITS,
    DNGN_ENTER_VAULTS,
    DNGN_ENTER_CRYPT_I,
    DNGN_ENTER_HALL_OF_BLADES,
    DNGN_ENTER_ZOT,
    DNGN_ENTER_TEMPLE,
    DNGN_ENTER_SNAKE_PIT,
    DNGN_ENTER_ELVEN_HALLS,
    DNGN_ENTER_TOMB,
    DNGN_ENTER_SWAMP,
    DNGN_RETURN_DUNGEON_I = 130,
    DNGN_RETURN_DUNGEON_II,
    DNGN_RETURN_DUNGEON_III,
    DNGN_RETURN_LAIR_II,
    DNGN_RETURN_DUNGEON_IV,
    DNGN_RETURN_VAULTS,
    DNGN_RETURN_CRYPT_II,
    DNGN_EXIT_ZOT,
    DNGN_RETURN_DUNGEON_V,
    DNGN_RETURN_LAIR_III,
    DNGN_RETURN_MINES,
    DNGN_RETURN_CRYPT_III,
    DNGN_RETURN_LAIR_IV,
    DNGN_ALTAR_ZIN = 180,
    DNGN_ALTAR_SHINING_ONE,
    DNGN_ALTAR_KIKUBAAQUDGHA,
    DNGN_ALTAR_YREDELEMNUL,
    DNGN_ALTAR_XOM,
    DNGN_ALTAR_VEHUMET,
    DNGN_ALTAR_OKAWARU,
    DNGN_ALTAR_MAKHLEB,
    DNGN_ALTAR_SIF_MUNA,
    DNGN_ALTAR_TROG,
    DNGN_ALTAR_NEMELEX_XOBEH,
    DNGN_ALTAR_ELYVILON,
    DNGN_BLUE_FOUNTAIN = 200,
    DNGN_DRY_FOUNTAIN_I,
    DNGN_SPARKLING_FOUNTAIN,
    DNGN_DRY_FOUNTAIN_II,
    DNGN_DRY_FOUNTAIN_III,
    DNGN_DRY_FOUNTAIN_IV,
    DNGN_DRY_FOUNTAIN_V,
    DNGN_DRY_FOUNTAIN_VI
};

enum DURATIONS
{
    DUR_LIQUID_FLAMES,
    DUR_ICY_ARMOUR,
    DUR_REPEL_MISSILES,
    DUR_PRAYER,
    DUR_REGENERATION,
    DUR_VORPAL_BLADE,
    DUR_FIRE_BRAND,
    DUR_ICE_BRAND,
    DUR_LETHAL_INFUSION,
    DUR_SWIFTNESS,
    DUR_INSULATION,
    DUR_STONEMAIL,
    DUR_CONTROLLED_FLIGHT,
    DUR_TELEPORT,
    DUR_CONTROL_TELEPORT,
    DUR_POISON_WEAPON,
    DUR_RESIST_POISON,
    DUR_BREATH_WEAPON,
    DUR_TRANSFORMATION,
    DUR_DEATH_CHANNEL,
    DUR_DEFLECT_MISSILES
};

enum ENCHANTMENT
{
     ENCH_NONE,
     ENCH_SLOW,
     ENCH_HASTE,
     ENCH_FEAR = 4,
     ENCH_CONFUSION,
     ENCH_INVIS,
     ENCH_YOUR_POISON_I,
     ENCH_YOUR_POISON_II,
     ENCH_YOUR_POISON_III,
     ENCH_YOUR_POISON_IV,
     ENCH_SUMMON = 19,
     ENCH_ABJ_I,
     ENCH_ABJ_II,
     ENCH_ABJ_III,
     ENCH_ABJ_IV,
     ENCH_ABJ_V,
     ENCH_ABJ_VI,
     ENCH_CHARM = 30,
     ENCH_YOUR_STICKY_FLAME_I,
     ENCH_YOUR_STICKY_FLAME_II,
     ENCH_YOUR_STICKY_FLAME_III,
     ENCH_YOUR_STICKY_FLAME_IV,
     ENCH_GLOWING_SHAPESHIFTER = 38,
     ENCH_SHAPESHIFTER,
     ENCH_TP_I,
     ENCH_TP_II,
     ENCH_TP_III,
     ENCH_TP_IV,
     ENCH_POISON_I = 57,
     ENCH_POISON_II,
     ENCH_POISON_III,
     ENCH_POISON_IV,
     ENCH_STICKY_FLAME_I,
     ENCH_STICKY_FLAME_II,
     ENCH_STICKY_FLAME_III,
     ENCH_STICKY_FLAME_IV,
};

enum EQUIPMENT
{
    EQ_WEAPON,
    EQ_CLOAK,
    EQ_HELMET,
    EQ_GLOVES,
    EQ_BOOTS,
    EQ_SHIELD,
    EQ_BODY_ARMOUR,
    EQ_LEFT_RING,
    EQ_RIGHT_RING,
    EQ_AMULET
};

enum FOODS
{
    FOOD_MEAT_RATION,
    FOOD_BREAD_RATION,
    FOOD_PEAR,
    FOOD_APPLE,
    FOOD_CHOKO,
    FOOD_HONEYCOMB,
    FOOD_ROYAL_JELLY,
    FOOD_SNOZZCUMBER,
    FOOD_PIZZA,
    FOOD_APRICOT,
    FOOD_ORANGE,
    FOOD_BANANA,
    FOOD_STRAWBERRY,
    FOOD_RAMBUTAN,
    FOOD_LEMON,
    FOOD_GRAPE,
    FOOD_SULTANA,
    FOOD_LYCHEE,
    FOOD_BEEF_JERKY,
    FOOD_CHEESE,
    FOOD_SAUSAGE,
    FOOD_CHUNK
};

enum CORPSES
{
    CORPSE_BODY,
    CORPSE_SKELETON
};

enum GODS
{
    GOD_NO_GOD,
    GOD_ZIN,
    GOD_SHINING_ONE,
    GOD_KIKUBAAQUDGHA,
    GOD_YREDELEMNUL,
    GOD_XOM,
    GOD_VEHUMET,
    GOD_OKAWARU,
    GOD_MAKHLEB,
    GOD_SIF_MUNA,
    GOD_TROG,
    GOD_NEMELEX_XOBEH,
    GOD_ELYVILON
};

enum GOOD_THINGS
{
    GOOD_KILLED_LIVING = 1,
    GOOD_KILLED_UNDEAD,
    GOOD_KILLED_DEMON,
    GOOD_KILLED_ANGEL_I,
    GOOD_KILLED_ANGEL_II,
    GOOD_HACKED_CORPSE,
    GOOD_OFFER_STUFF,
    GOOD_OFFER_CORPSE,
    GOOD_SLAVES_KILL_LIVING,
    GOOD_SERVANTS_KILL,
    GOOD_CARDS
};

enum HANDS_REQUIRED
{
    HANDS_ONE_HANDED = 1,
    HANDS_TWO_HANDED,
    HANDS_ONE_OR_TWO_HANDED,
};

enum HELMET_DESCRIPTIONS
{
    DHELM_WINGED = 1,
    DHELM_HORNED,
    DHELM_CRESTED,
    DHELM_PLUMED,
    DHELM_SPIKED,
    DHELM_VISORED,
    DHELM_JEWELLED
};

enum JEWELLERY
{
    RING_REGENERATION,
    RING_PROTECTION,
    RING_PROTECTION_FROM_FIRE,
    RING_POISON_RESISTANCE,
    RING_PROTECTION_FROM_COLD,
    RING_STRENGTH,
    RING_SLAYING,
    RING_SEE_INVISIBLE,
    RING_INVISIBILITY,
    RING_HUNGER,
    RING_TELEPORTATION,
    RING_EVASION,
    RING_SUSTAIN_ABILITIES,
    RING_SUSTENANCE,
    RING_DEXTERITY,
    RING_INTELLIGENCE,
    RING_WIZARDRY,
    RING_MAGICAL_POWER,
    RING_LEVITATION,
    RING_LIFE_PROTECTION,
    RING_PROTECTION_FROM_MAGIC,
    RING_FIRE,
    RING_ICE,
    RING_TELEPORT_CONTROL,
    AMU_RAGE = 35,
    AMU_MAINTAIN_SPEED,
    AMU_CLARITY,
    AMU_WARDING,
    AMU_RESIST_CORROSION,
    AMU_THE_GOURMAND,
    AMU_CONSERVATION,
    AMU_CONTROLLED_FLIGHT,
    AMU_INACCURACY,
    AMU_RESIST_MUTATION
};

enum JOB
{
    JOB_FIGHTER,
    JOB_WIZARD,
    JOB_PRIEST,
    JOB_THIEF,
    JOB_GLADIATOR,
    JOB_NECROMANCER,
    JOB_PALADIN,
    JOB_ASSASSIN,
    JOB_BERSERKER,
    JOB_HUNTER,
    JOB_CONJURER,
    JOB_ENCHANTER,
    JOB_FIRE_ELEMENTALIST,
    JOB_ICE_ELEMENTALIST,
    JOB_SUMMONER,
    JOB_AIR_ELEMENTALIST,
    JOB_EARTH_ELEMENTALIST,
    JOB_CRUSADER,
    JOB_DEATH_KNIGHT,
    JOB_VENOM_MAGE,
    JOB_CHAOS_KNIGHT,
    JOB_TRANSMUTER,
    JOB_HEALER,
    JOB_REAVER = 24,
    JOB_STALKER,
    JOB_MONK,
    JOB_WARPER
};

enum KILLER
{
     KILL_YOU = 1,
     KILL_MON,
     KILL_YOU_MISSILE,
     KILL_MON_MISSILE,
     KILL_MISC,
     KILL_RESET  /*abjuration, etc.*/
};

//
// The various types of level (you.level_type).
//
enum LEVEL_TYPES
{
    LEVEL_DUNGEON,
    LEVEL_LABYRINTH,
    LEVEL_ABYSS,
    LEVEL_PANDEMONIUM
};

#define YOU_KILL(x) ((x) == KILL_YOU || (x) == KILL_YOU_MISSILE)

enum MISCELLANY
{
    MISC_BOTTLED_EFREET,
    MISC_CRYSTAL_BALL_OF_SEEING,
    MISC_AIR_ELEMENTAL_FAN,
    MISC_LAMP_OF_FIRE,
    MISC_STONE_OF_EARTH_ELEMENTALS,
    MISC_LANTERN_OF_SHADOWS,
    MISC_HORN_OF_GERYON,
    MISC_BOX_OF_BEASTS,
    MISC_DECK_OF_WONDERS,
    MISC_DECK_OF_SUMMONINGS,
    MISC_CRYSTAL_BALL_OF_ENERGY,
    MISC_EMPTY_EBONY_CASKET,
    MISC_CRYSTAL_BALL_OF_FIXATION,
    MISC_DISC_OF_STORMS,
    MISC_RUNE_OF_ZOT,
    MISC_DECK_OF_TRICKS,
    MISC_DECK_OF_POWER,
    MISC_PORTABLE_ALTAR_OF_NEMELEX
};

enum MISSILES
{
    MI_STONE,
    MI_ARROW,
    MI_BOLT,
    MI_DART,
    MI_EGGPLANT,
    MI_LARGE_ROCK,
    MI_AXE = 9,
    MI_SPEAR = 11
};

enum MONSTERS
{
    MONS_GIANT_ANT,             // 0
     MONS_GIANT_BAT,
    MONS_CENTAUR,
    MONS_RED_DEVIL,
    MONS_ETTIN,
    MONS_FUNGUS,
    MONS_GOBLIN,
    MONS_HOUND,
    MONS_IMP,
    MONS_JACKAL,
    MONS_KILLER_BEE,            // 10
     MONS_KILLER_BEE_LARVA,
    MONS_MANTICORE,
    MONS_NECROPHAGE,
    MONS_ORC,
    MONS_PHANTOM,
    MONS_QUASIT,
    MONS_RAT,
    MONS_SCORPION,
    MONS_TUNNELING_WORM,
    MONS_UGLY_THING,            // 20
     MONS_FIRE_VORTEX,
    MONS_WORM,
    MONS_LARGE_ABOMINATION,
    MONS_YELLOW_WASP,
    MONS_SMALL_ZOMBIE,
    MONS_ANGEL,
    MONS_GIANT_BEETLE,
    MONS_CYCLOPS,
    MONS_DRAGON,
    MONS_TWO_HEADED_OGRE,       // 30
     MONS_FIEND,
    MONS_GIANT_SPORE,
    MONS_HOBGOBLIN,
    MONS_ICE_BEAST,
    MONS_JELLY,
    MONS_KOBOLD,
    MONS_LICH,
    MONS_MUMMY,
    MONS_GUARDIAN_NAGA,
    MONS_OGRE,                  // 40
     MONS_PLANT,
    MONS_QUEEN_BEE,
    MONS_RAKSHASA,
    MONS_SNAKE,
    MONS_TROLL,
    MONS_UNSEEN_HORROR,
    MONS_VAMPIRE,
    MONS_WRAITH,
    MONS_SMALL_ABOMINATION,
    MONS_YAK,                   // 50
     MONS_BIG_ZOMBIE,
    MONS_ORC_WARRIOR,
    MONS_KOBOLD_DEMONOLOGIST,
    MONS_ORC_WIZARD,
    MONS_ORC_KNIGHT,
    MONS_WORM_TAIL,
    MONS_WYVERN,
    MONS_BIG_KOBOLD,
    MONS_GIANT_EYEBALL,
    MONS_WIGHT,                 // 60
     MONS_OKLOB_PLANT,
    MONS_WOLF_SPIDER,
    MONS_SHADOW,
    MONS_HUNGRY_GHOST,
    MONS_EYE_OF_DRAINING,
    MONS_BUTTERFLY,
    MONS_WANDERING_MUSHROOM,
    MONS_EFREET,
    MONS_BRAIN_WORM,
    MONS_GIANT_ORANGE_BRAIN,    // 70
     MONS_BOULDER_BEETLE,
    MONS_FLYING_SKULL,
    MONS_HELL_HOUND,
    MONS_MINOTAUR,
    MONS_ICE_DRAGON,
    MONS_SLIME_CREATURE,
    MONS_FREEZING_WRAITH,
    MONS_FAKE_RAKSHASA,
    MONS_GREAT_ORB_OF_EYES,
    MONS_HELLION,               // 80
     MONS_ROTTING_DEVIL,
    MONS_TORMENTOR,
    MONS_REAPER,
    MONS_SOUL_EATER,
    MONS_HAIRY_DEVIL,
    MONS_ICE_DEVIL,
    MONS_BLUE_DEVIL,
    MONS_BEAST,
    MONS_IRON_DEVIL,
    MONS_GLOWING_SHAPESHIFTER = 98,
    MONS_SHAPESHIFTER,
    MONS_GIANT_MITE,            // 100
     MONS_STEAM_DRAGON,
    MONS_VERY_UGLY_THING,
    MONS_ORC_SORCEROR,
    MONS_HIPPOGRIFF,
    MONS_GRIFFON,
    MONS_HYDRA,
    MONS_SMALL_SKELETON,
    MONS_LARGE_SKELETON,
    MONS_HELL_KNIGHT,
    MONS_NECROMANCER,           // 110
     MONS_WIZARD,
    MONS_ORC_PRIEST,
    MONS_ORC_HIGH_PRIEST,
    MONS_HUMAN,
    MONS_GNOLL,
    MONS_CLAY_GOLEM,
    MONS_WOOD_GOLEM,
    MONS_STONE_GOLEM,
    MONS_IRON_GOLEM,
    MONS_CRYSTAL_GOLEM,         // 120
     MONS_TOENAIL_GOLEM,
    MONS_MOTTLED_DRAGON,
    MONS_EARTH_ELEMENTAL,
    MONS_FIRE_ELEMENTAL,
    MONS_AIR_ELEMENTAL,
    MONS_ICE_FIEND,
    MONS_SHADOW_FIEND,
    MONS_BROWN_SNAKE,
    MONS_GIANT_LIZARD,
    MONS_SPECTRAL_WARRIOR,      // 130
     MONS_PULSATING_LUMP,
    MONS_STORM_DRAGON,
    MONS_YAKTAUR,
    MONS_DEATH_YAK,
    MONS_ROCK_TROLL,
    MONS_STONE_GIANT,
    MONS_FLAYED_GHOST,
    MONS_BUMBLEBEE,
    MONS_REDBACK,
    MONS_INSUBSTANTIAL_WISP,    // 140
     MONS_VAPOUR,
    MONS_OGRE_MAGE,
    MONS_SPINY_WORM,
    MONS_DANCING_WEAPON,
    MONS_TITAN,
    MONS_GOLDEN_DRAGON,
    MONS_ELF,
    MONS_LINDWORM,
    MONS_ELEPHANT_SLUG,
    MONS_WAR_DOG,               // 150
     MONS_GREY_RAT,
    MONS_GREEN_RAT,
    MONS_ORANGE_RAT,
    MONS_BLACK_SNAKE,
    MONS_SHEEP,
    MONS_GHOUL,
    MONS_HOG,
    MONS_GIANT_MOSQUITO,
    MONS_GIANT_CENTIPEDE,
    MONS_IRON_TROLL,            // 160
     MONS_NAGA,
    MONS_FIRE_GIANT,
    MONS_FROST_GIANT,
    MONS_FIREDRAKE,
    MONS_SHADOW_DRAGON,
    MONS_YELLOW_SNAKE,
    MONS_GREY_SNAKE,
    MONS_DEEP_TROLL,
    MONS_GIANT_BLOWFLY,
    MONS_RED_WASP,              // 170
     MONS_SWAMP_DRAGON,
    MONS_SWAMP_DRAKE,
    MONS_SOLDIER_ANT,
    MONS_HILL_GIANT,
    MONS_QUEEN_ANT,
    MONS_ANT_LARVA,
    MONS_GIANT_FROG,
    MONS_GIANT_BROWN_FROG,
    MONS_SPINY_FROG,
    MONS_BLINK_FROG,            // 180
     MONS_WHITE_IMP = 220,
    MONS_LEMURE,
    MONS_UFETUBUS,
    MONS_MANES,
    MONS_MIDGE,
    MONS_NEQOXEC,
    MONS_ORANGE_DEMON,
    MONS_HELLWING,
    MONS_SMOKE_DEMON,
    MONS_YNOXINUL,
    MONS_EXECUTIONER,           // 230
     MONS_GREEN_DEATH,
    MONS_BLUE_DEATH,
    MONS_BALRUG,
    MONS_CACODEMON,
    MONS_DEMONIC_CRAWLER,
    MONS_SUN_DEMON,
    MONS_SHADOW_IMP,
    MONS_SHADOW_DEMON,
    MONS_LOROCYPROCA,
    MONS_SHADOW_WRAITH,         // 240
     MONS_GIANT_AMOEBA,
    MONS_GIANT_SLUG,
    MONS_GIANT_SNAIL,
    MONS_SPATIAL_VORTEX,
    MONS_PIT_FIEND,
    MONS_BORING_BEETLE,
    MONS_GARGOYLE,
    MONS_METAL_GARGOYLE,
    MONS_MOLTEN_GARGOYLE,
    MONS_PROGRAM_BUG,           // 250
     MONS_MNOLEG,
    MONS_LOM_LOBON,
    MONS_CEREBOV,
    MONS_GLOORX_VLOQ,
    MONS_NAGA_MAGE = 260,
    MONS_NAGA_WARRIOR,
    MONS_ORC_WARLORD,
    MONS_DEEP_ELF_SOLDIER,
    MONS_DEEP_ELF_FIGHTER,
    MONS_DEEP_ELF_KNIGHT,
    MONS_DEEP_ELF_MAGE,
    MONS_DEEP_ELF_SUMMONER,
    MONS_DEEP_ELF_CONJURER,
    MONS_DEEP_ELF_PRIEST,
    MONS_DEEP_ELF_HIGH_PRIEST,  // 270
     MONS_DEEP_ELF_DEMONOLOGIST,
    MONS_DEEP_ELF_ANNIHILATOR,
    MONS_DEEP_ELF_SORCEROR,
    MONS_DEEP_ELF_DEATH_MAGE,
    MONS_OOZE,
    MONS_AZURE_JELLY,
    MONS_DEATH_OOZE,
    MONS_ACID_BLOB,
    MONS_ROYAL_JELLY,
    MONS_TERENCE,               // 280
     MONS_JESSICA,
    MONS_IJYB,
    MONS_SIGMUND,
    MONS_BLORK_THE_ORC,
    MONS_EDMUND,
    MONS_PSYCHE,
    MONS_EROLCHA,
    MONS_DONALD,
    MONS_URUG,
    MONS_MICHAEL,               // 290
     MONS_JOSEPH,
    MONS_ANITA,
    MONS_ERICA,
    MONS_JOSEPHINE,
    MONS_HAROLD,
    MONS_NORBERT,
    MONS_JOZEF,
    MONS_AGNES,
    MONS_MAUD,
    MONS_LOUISE,                // 300
     MONS_FRANCIS,
    MONS_FRANCES,
    MONS_RUPERT,
    MONS_WAYNE,
    MONS_DUANE,
    MONS_XTAHUA,
    MONS_NORRIS,
    MONS_ADOLF,
    MONS_MARGERY,
    MONS_BORIS,                 // 310
     MONS_GERYON = 340,
    MONS_DISPATER,
    MONS_ASMODEUS,
    MONS_ANTAEUS,
    MONS_ERESHKIGAL,
    MONS_ANCIENT_LICH = 356,
    MONS_VAULT_GUARD = 360,
    MONS_CURSE_SKULL,
    MONS_VAMPIRE_KNIGHT,
    MONS_VAMPIRE_MAGE,
    MONS_SHINING_EYE,
    MONS_ORB_GUARDIAN,
    MONS_DAEVA,
    MONS_SPECTRAL_THING,
    MONS_GREATER_NAGA,
    MONS_SKELETAL_DRAGON,
    MONS_TENTACLED_MONSTROSITY, // 370
     MONS_SPHINX,
    MONS_ROTTING_HULK,
    MONS_GUARDIAN_MUMMY,
    MONS_GREATER_MUMMY,
    MONS_MUMMY_PRIEST,
    MONS_CENTAUR_WARRIOR,
    MONS_YAKTAUR_CAPTAIN,
    MONS_KILLER_KLOWN,
    MONS_GUARDIAN_ROBOT,
    MONS_DORGI,                 // 380
     MONS_SWORD,
    MONS_QUOKKA,
    MONS_EYE_OF_DEVASTATION = 385,
    MONS_MOTH_OF_WRATH,
    MONS_DEATH_COB,
    MONS_CURSE_TOE,
    MONS_GOLD_MIMIC,
    MONS_WEAPON_MIMIC,          // 390
     MONS_ARMOUR_MIMIC,
    MONS_SCROLL_MIMIC,
    MONS_POTION_MIMIC,
    MONS_HELL_HOG,
    MONS_SERPENT_OF_HELL,
    MONS_BOGGART,
    MONS_QUICKSILVER_DRAGON,
    MONS_IRON_DRAGON,
    MONS_SKELETAL_WARRIOR,
    MONS_PLAYER_GHOST,          // 400
     MONS_PANDEMONIUM_DEMON,
    MONS_LAVA_WORM = 420,
    MONS_LAVA_FISH,
    MONS_LAVA_SNAKE,
    MONS_ANOTHER_LAVA_THING,
    MONS_BIG_FISH = 430,
    MONS_GIANT_GOLDFISH,
    MONS_ELECTRICAL_EEL,
    MONS_JELLYFISH,
    MONS_WATER_ELEMENTAL,
    MONS_SWAMP_WORM
};

enum MONSTER_BEHAVIOR
{
    BEH_SLEEP,
    BEH_CHASING_I,
    BEH_WANDER,
    BEH_FLEE,
    BEH_CONFUSED,
    BEH_FIGHT = 6,
    BEH_ENSLAVED,
    BEH_CHASING_II = 100
};

enum MONSTER_HOLINESS
{
    MH_NORMAL,
    MH_UNDEAD,
    MH_DEMONIC
};

enum MONSTER_SPELLS
{
  MS_MMISSILE = 0,                      /* 0 */
  MS_FLAME,
  MS_FROST,
  MS_PARALYSIS,
  MS_SLOW,
  MS_HASTE,
  MS_SLOW_DUP,  /*should be deprecated, I think  -- DML*/
  MS_VENOM_BOLT,
  MS_FIRE_BOLT,
  MS_COLD_BOLT,
  MS_LIGHTNING_BOLT = 10,
  MS_INVIS,
  MS_FIREBALL,
  MS_HEAL,
  MS_TELEPORT,
  MS_TELEPORT_OTHER,
  MS_BLINK,
  MS_CRYSTAL_SPEAR,
  MS_DIG,
  MS_NEGATIVE_BOLT,
  MS_HELLFIRE_BURST,
  MS_VAMPIRE_SUMMON = 21,
  MS_ORB_ENERGY,
  MS_BRAIN_FEED,
  MS_LEVEL_SUMMON,
  MS_FAKE_RAKSHASA_SUMMON,
  MS_STEAM_BALL,
  MS_SUMMON_DEMON,
  MS_ANIMATE_DEAD,
  MS_PAIN,
  MS_SMITE = 30,
  MS_STICKY_FLAME,
  MS_POISON_BLAST,
  MS_SUMMON_LESSER_DEMON,
  MS_SUMMON_UFETUBUS,
  MS_PURPLE_BLAST,
  MS_GERYON,
  MS_ENERGY_BOLT,
  MS_STING,
  MS_IRON_BOLT,
  MS_STONE_ARROW,
  MS_POISON_SPLASH,
  MS_SUMMON_UNDEAD,
  MS_MUTATION,
  MS_ZULZER,
  MS_DISINTEGRATE,
  MS_MARSH_GAS,
  MS_QUICKSILVER_BOLT,
  MS_TORMENT,
  MS_HELLFIRE,
  MS_METAL_SPLINTERS,
  MS_SUMMON_DEMON_1,
  MS_BANISHMENT
};

enum MUTATIONS
{
    MUT_TOUGH_SKIN,
    MUT_STRONG,
    MUT_CLEVER,
    MUT_AGILE,
    MUT_GREEN_SCALES,
    MUT_BLACK_SCALES,
    MUT_GREY_SCALES,
    MUT_BONEY_PLATES,
    MUT_REPULSION_FIELD,
    MUT_POISON_RESISTANCE,
    MUT_CARNIVOROUS,
    MUT_HERBIVOROUS,
    MUT_HEAT_RESISTANCE,
    MUT_COLD_RESISTANCE,
    MUT_SHOCK_RESISTANCE,
    MUT_REGENERATION,
    MUT_FAST_METABOLISM,
    MUT_SLOW_METABOLISM,
    MUT_WEAK,
    MUT_DOPEY,
    MUT_CLUMSY,
    MUT_TELEPORT_CONTROL,
    MUT_TELEPORT,
    MUT_MAGIC_RESISTANCE,
    MUT_FAST,
    MUT_ACUTE_VISION,
    MUT_DEFORMED,
    MUT_TELEPORT_AT_WILL,
    MUT_SPIT_POISON,
    MUT_MAPPING,
    MUT_BREATHE_FLAMES,
    MUT_BLINK,
    MUT_HORNS,
    MUT_STRONG_STIFF,
    MUT_FLEXIBLE_WEAK,
    MUT_LOST,
    MUT_CLARITY,
    MUT_BERSERK,
    MUT_DETERIORATION,
    MUT_BLURRY_VISION,
    MUT_MUTATION_RESISTANCE,
    MUT_FRAIL,
    MUT_ROBUST,
    MUT_TORMENT_RESISTANCE,
    MUT_NEGATIVE_ENERGY_RESISTANCE,
    MUT_SUMMON_MINOR_DEMONS,
    MUT_SUMMON_DEMONS,
    MUT_HURL_HELLFIRE,
    MUT_CALL_TORMENT,
    MUT_RAISE_DEAD,
    MUT_CONTROL_DEMONS,
    MUT_PANDEMONIUM,
    MUT_DEATH_STRENGTH,
    MUT_CHANNEL_HELL,
    MUT_DRAIN_LIFE,
    MUT_THROW_FLAMES,
    MUT_THROW_FROST,
    MUT_SMITE
};

enum NAMED_WEAPONS
{
    NWPN_SINGING_SWORD = 181,
    NWPN_WRATH_OF_TROG,
    NWPN_SCYTHE_OF_CURSES,
    NWPN_MACE_OF_VARIABILITY,
    NWPN_GLAIVE_OF_PRUNE,
    NWPN_SCEPTRE_OF_TORMENT,
    NWPN_SWORD_OF_ZONGULDROK,
    NWPN_SWORD_OF_CEREBOV,
    NWPN_STAFF_OF_DISPATER,
    NWPN_SCEPTRE_OF_ASMODEUS,
    NWPN_SWORD_OF_POWER,
    NWPN_KNIFE_OF_ACCURACY,
    NWPN_STAFF_OF_OLGREB,
    NWPN_VAMPIRE_S_TOOTH,
    NWPN_STAFF_OF_WUCAD_MU
};

enum NAUGHTY_THINGS
{
    NAUGHTY_NECROMANCY = 1,
    NAUGHTY_UNHOLY,
    NAUGHTY_KILLING,
    NAUGHTY_ATTACK_HOLY,
    NAUGHTY_ATTACK_FRIEND,
    NAUGHTY_FRIEND_DIES,
    NAUGHTY_BUTCHER,
    NAUGHTY_STABBING,
    NAUGHTY_SPELLCASTING
};

enum OBJECT_CLASSES
{
    OBJ_WEAPONS,
    OBJ_MISSILES,
    OBJ_ARMOUR,
    OBJ_WANDS,
    OBJ_FOOD,
    OBJ_SCROLLS = 6,
    OBJ_JEWELLERY,
    OBJ_POTIONS,
    OBJ_BOOKS = 10,
    OBJ_STAVES,
    OBJ_ORBS,
    OBJ_MISCELLANY,
    OBJ_CORPSES,
    OBJ_GOLD
};

enum ORBS
{
    ORB_ZOT
};

enum POTIONS
{
    POT_HEALING,
    POT_HEAL_WOUNDS,
    POT_SPEED,
    POT_MIGHT,
    POT_GAIN_STRENGTH,
    POT_GAIN_DEXTERITY,
    POT_GAIN_INTELLIGENCE,
    POT_LEVITATION,
    POT_POISON,
    POT_SLOWING,
    POT_PARALYSIS,
    POT_CONFUSION,
    POT_INVISIBILITY,
    POT_PORRIDGE,
    POT_DEGENERATION,
    POT_DECAY,
    POT_WATER,
    POT_EXPERIENCE,
    POT_MAGIC,
    POT_RESTORE_ABILITIES,
    POT_STRONG_POISON,
    POT_BERSERK_RAGE,
    POT_CURE_MUTATION,
    POT_MUTATION
};

enum RANDART_PROP
{
    RAP_BRAND,
    RAP_AC,
    RAP_EVASION,
    RAP_STRENGTH,
    RAP_INTELLIGENCE,
    RAP_DEXTERITY,
    RAP_FIRE,
    RAP_COLD,
    RAP_ELECTRICITY,
    RAP_POISON,
    RAP_NEGATIVE_ENERGY,
    RAP_MAGIC,
    RAP_EYESIGHT,
    RAP_INVISIBLE,
    RAP_LEVITATE,
    RAP_BLINK,
    RAP_CAN_TELEPORT,
    RAP_BERSERK,
    RAP_MAPPING,
    RAP_NOISES,
    RAP_PREVENT_SPELLCASTING,
    RAP_CAUSE_TELEPORTATION,
    RAP_PREVENT_TELEPORTATION,
    RAP_ANGRY,
    RAP_METABOLISM,
    RAP_MUTAGENIC,
    RAP_ACCURACY,
    RAP_DAMAGE
};

enum SCROLLS
{
    SCR_IDENTIFY,
    SCR_TELEPORTATION,
    SCR_FEAR,
    SCR_NOISE,
    SCR_REMOVE_CURSE,
    SCR_DETECT_CURSE,
    SCR_SUMMONING,
    SCR_ENCHANT_WEAPON_I,
    SCR_ENCHANT_ARMOUR,
    SCR_TORMENT,
    SCR_RANDOM_USELESSNESS,
    SCR_CURSE_WEAPON,
    SCR_CURSE_ARMOUR,
    SCR_IMMOLATION,
    SCR_BLINKING,
    SCR_PAPER,
    SCR_MAGIC_MAPPING,
    SCR_FORGETFULNESS,
    SCR_ACQUIREMENT,
    SCR_ENCHANT_WEAPON_II,
    SCR_VORPALISE_WEAPON,
    SCR_RECHARGING,
    SCR_ENCHANT_WEAPON_III
};

enum SKILLS
{
    SK_FIGHTING,
    SK_SHORT_BLADES,
    SK_LONG_SWORDS,
    SK_UNUSED_1,          // SK_GREAT_SWORDS,  is now unused
    SK_AXES,
    SK_MACES_FLAILS,
    SK_POLEARMS,
    SK_STAVES,
    SK_SLINGS,
    SK_BOWS,
    SK_CROSSBOWS,
    SK_DARTS,
    SK_THROWING,
    SK_ARMOUR,
    SK_DODGING,
    SK_STEALTH,
    SK_STABBING,
    SK_SHIELDS,
    SK_TRAPS_DOORS,
    SK_UNARMED_COMBAT,
    SK_SPELLCASTING = 25,
    SK_CONJURATIONS,
    SK_ENCHANTMENTS,
    SK_SUMMONINGS,
    SK_NECROMANCY,
    SK_TRANSLOCATIONS,
    SK_TRANSMIGRATION,
    SK_DIVINATIONS,
    SK_FIRE_MAGIC,
    SK_ICE_MAGIC,
    SK_AIR_MAGIC,
    SK_EARTH_MAGIC,
    SK_POISON_MAGIC,
    SK_INVOCATIONS
};

enum SPECIAL_ARMOR
{
    SPARM_NORMAL,
    SPARM_RUNNING,
    SPARM_FIRE_RESISTANCE,
    SPARM_COLD_RESISTANCE,
    SPARM_POISON_RESISTANCE,
    SPARM_SEE_INVISIBLE,
    SPARM_DARKNESS,
    SPARM_STRENGTH,
    SPARM_DEXTERITY,
    SPARM_INTELLIGENCE,
    SPARM_PONDEROUSNESS,
    SPARM_LEVITATION,
    SPARM_MAGIC_RESISTANCE,
    SPARM_PROTECTION,
    SPARM_STEALTH,
    SPARM_RESISTANCE,
    SPARM_POSITIVE_ENERGY,
    SPARM_ARCHMAGI,
    SPARM_PRESERVATION
};

enum SPECIAL_WEAPONS
{
    SPWPN_NORMAL,
    SPWPN_FLAMING,
    SPWPN_FREEZING,
    SPWPN_HOLY_WRATH,
    SPWPN_ELECTROCUTION,
    SPWPN_ORC_SLAYING,
    SPWPN_VENOM,
    SPWPN_PROTECTION,
    SPWPN_DRAINING,
    SPWPN_SPEED,
    SPWPN_VORPAL,
    SPWPN_FLAME,
    SPWPN_FROST,
    SPWPN_VAMPIRICISM,
    SPWPN_DISRUPTION,
    SPWPN_PAIN,
    SPWPN_DISTORTION,
    SPWPN_REACHING,
    SPWPN_RANDART_I = 25,
    SPWPN_RANDART_II,
    SPWPN_RANDART_III,
    SPWPN_RANDART_IV,
    SPWPN_RANDART_V
};

enum SPECIAL_WIELD
{
    SPWLD_NONE,
    SPWLD_SING,
    SPWLD_TROG,
    SPWLD_CURSE,
    SPWLD_VARIABLE,
    SPWLD_TORMENT = 6,
    SPWLD_ZONGULDROK,
    SPWLD_POWER,
    SPWLD_WUCAD_MU,
    SPWLD_SHADOW = 50
};

enum SPECIES
{
    SP_HUMAN = 1,
    SP_ELF,
    SP_HIGH_ELF,
    SP_GREY_ELF,
    SP_DEEP_ELF,
    SP_SLUDGE_ELF,
    SP_HILL_DWARF,
    SP_MOUNTAIN_DWARF,
    SP_HALFLING,
    SP_HILL_ORC,
    SP_KOBOLD,
    SP_MUMMY,
    SP_NAGA,
    SP_GNOME,
    SP_OGRE,
    SP_TROLL,
    SP_OGRE_MAGE,
    SP_RED_DRACONIAN,
    SP_WHITE_DRACONIAN,
    SP_GREEN_DRACONIAN,
    SP_GOLDEN_DRACONIAN,
    SP_GREY_DRACONIAN,
    SP_BLACK_DRACONIAN,
    SP_PURPLE_DRACONIAN,
    SP_MOTTLED_DRACONIAN,
    SP_PALE_DRACONIAN,
    SP_UNK0_DRACONIAN,
    SP_UNK1_DRACONIAN,
    SP_UNK2_DRACONIAN,
    SP_CENTAUR,
    SP_DEMIGOD,
    SP_SPRIGGAN,
    SP_MINOTAUR,
    SP_DEMONSPAWN,
    SP_GHOUL,
    SP_KENKU
};

enum SPELLS
{
    SPELL_IDENTIFY,
    SPELL_TELEPORT_SELF,
    SPELL_CAUSE_FEAR,
    SPELL_CREATE_NOISE,
    SPELL_REMOVE_CURSE,
    SPELL_MAGIC_DART,
    SPELL_FIREBALL,
    SPELL_CONJURE_FLAME = 13,
    SPELL_DIG,
    SPELL_BOLT_OF_FIRE,
    SPELL_BOLT_OF_COLD,
    SPELL_LIGHTNING_BOLT,
    SPELL_POLYMORPH_OTHER = 20,
    SPELL_SLOW,
    SPELL_HASTE,
    SPELL_PARALYZE,
    SPELL_CONFUSE,
    SPELL_INVISIBILITY,
    SPELL_THROW_FLAME,
    SPELL_THROW_FROST,
    SPELL_CONTROLLED_BLINK,
    SPELL_FREEZING_CLOUD,
    SPELL_MEPHITIC_CLOUD,
    SPELL_RING_OF_FLAMES,
    SPELL_RESTORE_STRENGTH,
    SPELL_RESTORE_INTELLIGENCE,
    SPELL_RESTORE_DEXTERITY,
    SPELL_VENOM_BOLT,
    SPELL_OLGREBS_TOXIC_RADIANCE,
    SPELL_TELEPORT_OTHER,
    SPELL_LESSER_HEALING,
    SPELL_GREATER_HEALING,
    SPELL_CURE_POISON_I,
    SPELL_PURIFICATION,
    SPELL_DEATHS_DOOR,
    SPELL_SELECTIVE_AMNESIA,
    SPELL_MASS_CONFUSION,
    SPELL_SMITING,
    SPELL_REPEL_UNDEAD,
    SPELL_HOLY_WORD,
    SPELL_DETECT_CURSE,
    SPELL_SUMMON_SMALL_MAMMAL,
    SPELL_ABJURATION_I,
    SPELL_SUMMON_SCORPIONS,
    SPELL_LEVITATION,
    SPELL_BOLT_OF_DRAINING,
    SPELL_LEHUDIBS_CRYSTAL_SPEAR,
    SPELL_BOLT_OF_INACCURACY,
    SPELL_POISONOUS_CLOUD,
    SPELL_FIRE_STORM,
    SPELL_DETECT_TRAPS,
    SPELL_BLINK,
    SPELL_ISKENDERUNS_MYSTIC_BLAST,
    SPELL_SWARM,
    SPELL_SUMMON_HORRIBLE_THINGS,
    SPELL_ENSLAVEMENT,
    SPELL_MAGIC_MAPPING,
    SPELL_HEAL_OTHER,
    SPELL_ANIMATE_DEAD,
    SPELL_PAIN,
    SPELL_EXTENSION,
    SPELL_CONTROL_UNDEAD,
    SPELL_ANIMATE_SKELETON,
    SPELL_VAMPIRIC_DRAINING,
    SPELL_SUMMON_WRAITHS,
    SPELL_DETECT_ITEMS,
    SPELL_BORGNJORS_REVIVIFICATION,
    SPELL_BURN,
    SPELL_FREEZE,
    SPELL_SUMMON_ELEMENTAL,
    SPELL_OZOCUBUS_REFRIGERATION,
    SPELL_STICKY_FLAME,
    SPELL_SUMMON_ICE_BEAST,
    SPELL_OZOCUBUS_ARMOUR,
    SPELL_CALL_IMP,
    SPELL_REPEL_MISSILES,
    SPELL_BERSERKER_RAGE,
    SPELL_DISPEL_UNDEAD,
    SPELL_GUARDIAN,
    SPELL_PESTILENCE,
    SPELL_THUNDERBOLT,
    SPELL_FLAME_OF_CLEANSING,
    SPELL_SHINING_LIGHT,
    SPELL_SUMMON_DAEVA,
    SPELL_ABJURATION_II,
    SPELL_TWISTED_RESURRECTION = 110,
    SPELL_REGENERATION,
    SPELL_BONE_SHARDS,
    SPELL_BANISHMENT,
    SPELL_CIGOTUVIS_DEGENERATION,
    SPELL_STING,
    SPELL_SUBLIMATION_OF_BLOOD,
    SPELL_TUKIMAS_DANCE,
    SPELL_HELLFIRE,
    SPELL_SUMMON_DEMON,
    SPELL_DEMONIC_HORDE,
    SPELL_SUMMON_GREATER_DEMON,
    SPELL_CORPSE_ROT,
    SPELL_TUKIMAS_VORPAL_BLADE,
    SPELL_FIRE_BRAND,
    SPELL_FREEZING_AURA,
    SPELL_LETHAL_INFUSION,
    SPELL_CRUSH,
    SPELL_BOLT_OF_IRON,
    SPELL_STONE_ARROW,
    SPELL_TOMB_OF_DOROKLOHE,
    SPELL_STONEMAIL,
    SPELL_SHOCK,
    SPELL_SWIFTNESS,
    SPELL_FLY,
    SPELL_INSULATION,
    SPELL_ORB_OF_ELECTROCUTION,
    SPELL_DETECT_CREATURES,
    SPELL_CURE_POISON_II,
    SPELL_CONTROL_TELEPORT,
    SPELL_POISON_AMMUNITION,
    SPELL_POISON_WEAPON,
    SPELL_RESIST_POISON,
    SPELL_PROJECTED_NOISE,
    SPELL_ALTER_SELF,
    SPELL_DEBUGGING_RAY,
    SPELL_RECALL,
    SPELL_PORTAL,
    SPELL_AGONY,
    SPELL_SPIDER_FORM,
    SPELL_DISRUPT,
    SPELL_DISINTEGRATE,
    SPELL_BLADE_HANDS,
    SPELL_STATUE_FORM,
    SPELL_ICE_FORM,
    SPELL_DRAGON_FORM,
    SPELL_NECROMUTATION,
    SPELL_DEATH_CHANNEL,
    SPELL_SYMBOL_OF_TORMENT,
    SPELL_DEFLECT_MISSILES,
    SPELL_ORB_OF_FRAGMENTATION,
    SPELL_ICE_BOLT,
    SPELL_ICE_STORM,
    SPELL_ARC,
    SPELL_AIRSTRIKE,
    SPELL_SHADOW_CREATURES
};

enum SPELL_TYPES
{
    SPTYP_CONJURATION = 11,
    SPTYP_ENCHANTMENT,
    SPTYP_FIRE,
    SPTYP_ICE,
    SPTYP_TRANSMIGRATION,
    SPTYP_NECROMANCY,
    SPTYP_HOLY,
    SPTYP_SUMMONING,
    SPTYP_DIVINATION,
    SPTYP_TRANSLOCATION,
    SPTYP_POISON,
    SPTYP_EARTH,
    SPTYP_AIR
};

enum STATS
{
    STAT_STRENGTH,
    STAT_DEXTERITY,
    STAT_INTELLIGENCE
};

enum STAVES
{
    STAFF_WIZARDRY,
    STAFF_POWER,
    STAFF_FIRE,
    STAFF_COLD,
    STAFF_POISON,
    STAFF_ENERGY,
    STAFF_DEATH,
    STAFF_CONJURATION,
    STAFF_ENCHANTMENT,
    STAFF_SUMMONING_I,
    STAFF_SMITING,
    STAFF_SUMMONING_II,
    STAFF_DESTRUCTION_I,
    STAFF_DESTRUCTION_II,
    STAFF_DESTRUCTION_III,
    STAFF_DESTRUCTION_IV,
    STAFF_WARDING,
    STAFF_DISCOVERY,
    STAFF_DEMONOLOGY,
    STAFF_AIR = 25,
    STAFF_EARTH,
    STAFF_CHANNELING
};


enum SYMBOLS
{
     SYM_MISSILE = ')',
     SYM_SPORE = '+',
     SYM_ZAP = '#'
};

enum TRANSFORMATIONS
{
    TRAN_NONE,
    TRAN_SPIDER,
    TRAN_BLADE_HANDS,
    TRAN_STATUE,
    TRAN_ICE_BEAST,
    TRAN_DRAGON,
    TRAN_LICH
};

enum TRAPS
{
    TRAP_DART,
    TRAP_ARROW,
    TRAP_SPEAR,
    TRAP_AXE,
    TRAP_TELEPORT,
    TRAP_AMNESIA,
    TRAP_BLADE,
    TRAP_BOLT,
    TRAP_ZOT
};

enum UNARMED_ATTACKS
{
    UNAT_NO_ATTACK,
    UNAT_KICK,
    UNAT_HEADBUTT,
    UNAT_TAILSLAP,
    UNAT_PUNCH
};

enum VORPAL_DESCRIPTIONS
{
    DVORP_CRUSHING,
    DVORP_SLICING,
    DVORP_PIERCING,
    DVORP_CHOPPING
};

enum WANDS
{
    WAND_FLAME,
    WAND_FROST,
    WAND_SLOWING,
    WAND_HASTING,
    WAND_MAGIC_DARTS,
    WAND_HEALING,
    WAND_PARALYSIS,
    WAND_FIRE,
    WAND_COLD,
    WAND_CONFUSION,
    WAND_INVISIBILITY,
    WAND_DIGGING,
    WAND_FIREBALL,
    WAND_TELEPORTATION,
    WAND_LIGHTNING,
    WAND_POLYMORPH_OTHER,
    WAND_ENSLAVEMENT,
    WAND_DRAINING,
    WAND_RANDOM_EFFECTS,
    WAND_DISINTEGRATION
};

enum WEAPONS
{
    // Base weapons
    WPN_CLUB,
    WPN_MACE,
    WPN_FLAIL,
    WPN_DAGGER,
    WPN_MORNINGSTAR,
    WPN_SHORT_SWORD,
    WPN_LONG_SWORD,
    WPN_GREAT_SWORD,
    WPN_SCIMITAR,
    WPN_HAND_AXE,
    WPN_BATTLEAXE,
    WPN_SPEAR,
    WPN_HALBERD,
    WPN_SLING,
    WPN_BOW,
    WPN_CROSSBOW,
    WPN_HAND_CROSSBOW,
    WPN_GLAIVE,
    WPN_QUARTERSTAFF,

    // These three not standardly created
    WPN_SCYTHE,
    WPN_GIANT_CLUB,
    WPN_GIANT_SPIKED_CLUB,

    // "Rare" weapons -- some of these have special cases and are uncommon
    WPN_EVENINGSTAR,
    WPN_QUICK_BLADE,
    WPN_KATANA,
    WPN_EXECUTIONERS_AXE,
    WPN_DOUBLE_SWORD,
    WPN_TRIPLE_SWORD,
    WPN_HAMMER,
    WPN_ANCUS,
    WPN_WHIP,
    WPN_SABRE,
    WPN_DEMON_BLADE,
    WPN_DEMON_WHIP,
    WPN_DEMON_TRIDENT,
    WPN_BROAD_AXE,

    // Base items continued
    WPN_AXE,
    WPN_TRIDENT,
    WPN_SPIKED_FLAIL,
    WPN_GREAT_MACE,
    WPN_GREAT_FLAIL,
    WPN_KNIFE,

    WPN_UNARMED = 500,
    WPN_UNKNOWN = 1000,
};

enum WEAPON_DESCRIPTIONS
{
    DWPN_RUNED = 1,
    DWPN_GLOWING,
    DWPN_ORCISH,
    DWPN_ELVEN,
    DWPN_DWARVEN
};

enum WEAPON_PROPERTIES
{
    PWPN_DAMAGE,
    PWPN_HIT,
    PWPN_SPEED
};

enum ZAPS
{
    ZAP_FLAME,
    ZAP_FROST,
    ZAP_SLOWING,
    ZAP_HASTING,
    ZAP_MAGIC_DARTS,
    ZAP_HEALING,
    ZAP_PARALYSIS,
    ZAP_FIRE,
    ZAP_COLD,
    ZAP_CONFUSION,
    ZAP_INVISIBILITY,
    ZAP_DIGGING,
    ZAP_FIREBALL,
    ZAP_TELEPORTATION,
    ZAP_LIGHTNING,
    ZAP_POLYMORPH_OTHER,
    ZAP_VENOM_BOLT,
    ZAP_NEGATIVE_ENERGY,
    ZAP_CRYSTAL_SPEAR,
    ZAP_BEAM_OF_ENERGY,
    ZAP_ORB_OF_ENERGY,
    ZAP_ENSLAVEMENT,
    ZAP_AGONY_I,
    ZAP_STICKY_FLAME,
    ZAP_DISPEL_UNDEAD,
    ZAP_CLEANSING_FLAME,
    ZAP_BONE_SHARDS,
    ZAP_BANISHMENT,
    ZAP_DEGENERATION,
    ZAP_STING,
    ZAP_HELLFIRE,
    ZAP_IRON_BOLT,
    ZAP_PEBBLE,
    ZAP_STONE_ARROW,
    ZAP_ELECTRICITY,
    ZAP_ORB_OF_ELECTRICITY,
    ZAP_SPIT_POISON,
    ZAP_DEBUGGING_RAY,
    ZAP_BREATHE_FIRE,
    ZAP_BREATHE_FROST,
    ZAP_BREATHE_ACID,
    ZAP_BREATHE_POISON,
    ZAP_BREATHE_POWER,
    ZAP_ENSLAVE_UNDEAD,
    ZAP_AGONY_II,
    ZAP_DISRUPTION,
    ZAP_DISINTEGRATION,
    ZAP_BREATHE_STEAM = 48,
    ZAP_CONTROL_DEMON,
    ZAP_ORB_OF_FRAGMENTATION,
    ZAP_ICE_BOLT,
    ZAP_ICE_STORM
};


#endif          // ENUM_H
