#include <string.h>
#include <stdlib.h>

char vault_1(char vgrid [81] [81], int mons_array [7]);
char vault_2(char vgrid [81] [81], int mons_array [7]);
char vault_3(char vgrid [81] [81], int mons_array [7]);
char vault_4(char vgrid [81] [81], int mons_array [7]);
char vault_5(char vgrid [81] [81], int mons_array [7]);
char vault_6(char vgrid [81] [81], int mons_array [7]);
char vault_7(char vgrid [81] [81], int mons_array [7]);
char vault_8(char vgrid [81] [81], int mons_array [7]);
char vault_9(char vgrid [81] [81], int mons_array [7]);
char vault_10(char vgrid [81] [81], int mons_array [7]);

char orc_temple(char vgrid [81] [81], int mons_array [7]);
char my_map(char vgrid [81] [81], int mons_array [7]);
char fort_yaktaur(char vgrid [81] [81], int mons_array [7]);
char farm_and_country(char vgrid [81] [81], int mons_array [7]);
char box_level(char vgrid [81] [81], int mons_array [7]);
char beehive(char vgrid [81] [81], int mons_array [7]);
char slime_pit(char vgrid [81] [81], int mons_array [7]);
char vaults_vault(char vgrid [81] [81], int mons_array [7]);
char hall_of_blades(char vgrid [81] [81], int mons_array [7]);
char hall_of_Zot(char vgrid [81] [81], int mons_array [7]);


char vestibule_map(char vgrid [81] [81], int mons_array [7]);
char castle_dis(char vgrid [81] [81], int mons_array [7]);
char asmodeus(char vgrid [81] [81], int mons_array [7]);
char antaeus(char vgrid [81] [81], int mons_array [7]);
char ereshkigal(char vgrid [81] [81], int mons_array [7]);

char nemelex(char vgrid [81] [81], int mons_array [7]);
char sif_muna(char vgrid [81] [81], int mons_array [7]);
char okawaru(char vgrid [81] [81], int mons_array [7]);
char kikuba(char vgrid [81] [81], int mons_array [7]);
//char mollusc(char vgrid [81] [81], int mons_array [7]);

char vault_main(char vgrid [81] [81], int mons_array [7], char vault_force, int many_many)
{
char vx, vy;

char vault_force2 = 0;

for (vx = 0; vx < 80; vx ++)
{
 for (vy = 0; vy < 80; vy ++)
 {
  vgrid [vx] [vy] = 'x';
 }
  vgrid [80] [vx] = 0;
  vgrid [vx] [80] = 0;
}
mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;


random_vault :
if (vault_force == 100) vault_force2 = random() % 14;
 else vault_force2 = vault_force;

switch(vault_force2)
{
 case 0: return vault_1(vgrid, mons_array);
 case 1: return vault_2(vgrid, mons_array);
 case 2: return vault_3(vgrid, mons_array);
 case 3: return vault_4(vgrid, mons_array);
 case 4: return vault_5(vgrid, mons_array);
 case 5: return vault_6(vgrid, mons_array);
 case 6: return vault_7(vgrid, mons_array);
 case 7: return vault_8(vgrid, mons_array);
 case 8: return vault_9(vgrid, mons_array);
 case 9: if (many_many > 23) return my_map(vgrid, mons_array);
    if (many_many > 12) return orc_temple(vgrid, mons_array);
    goto random_vault;
 case 10: return vault_10(vgrid, mons_array);
 case 11: if (many_many > 20) return farm_and_country(vgrid, mons_array);
 goto random_vault;
 case 12: if (many_many > 20) return fort_yaktaur(vgrid, mons_array);
 goto random_vault;
 case 13: return box_level(vgrid, mons_array);
// case 10: return vault_10(vgrid, mons_array);
 case 50: return vestibule_map(vgrid, mons_array);
 case 51: return castle_dis(vgrid, mons_array);
 case 52: return asmodeus(vgrid, mons_array);
 case 53: return antaeus(vgrid, mons_array);
 case 54: return ereshkigal(vgrid, mons_array);

 case 60: return nemelex(vgrid, mons_array);
 case 61: return sif_muna(vgrid, mons_array);
 case 62: return okawaru(vgrid, mons_array);
 case 63: return kikuba(vgrid, mons_array);
// case 64: return mollusc(vgrid, mons_array);
 case 80: return beehive(vgrid, mons_array);
 case 81: return slime_pit(vgrid, mons_array);
 case 82: return vaults_vault(vgrid, mons_array);
 case 83: return hall_of_blades(vgrid, mons_array);
 case 84: return hall_of_Zot(vgrid, mons_array);

}

// make sure that vault_n, where n is a number, is a vault which can be put
//  anywhere, while other vault names are for specific level ranges etc

return 0;

}



/*
key:
x - rock wall 1
c - stone wall 2
v - metal wall 4
b - green crystal 6
a - wax wall 8
. - empty space 67
+ - door 3
= - secret door (7?)
@ - entry point - must be on outside and on a particular side - see templates
w - water
l - lava
>< - extra stairs - you can leave level by these but will never be placed on them from another level
}{ - stairs 82/86 - You must be able to reach these from each other
)( - stairs 83/87
][ - stairs 84/88
I - orcish idol (does nothing)
^ - random trap

A - Vestibule gateway (opened by Horn). Can also be put on other levels for colour.

$ - gold
% - normal item
* - higher level item (good)
| - acquirement-level item (almost guaranteed excellent)
O - place an appropriate orb here
R - honeycomb (2/3) or royal jelly (1/3)
Z - the Orb of Zot

0 - normal monster
9 - +5 depth monster
8 - (+2) * 2 depth monster (aargh!). Can get golden dragons and titans this way.
1-7 - monster array monster
   used to allocate specific monsters for a vault.
   is filled with 250 if monster not specified

note that a lot of the vaults are in there mainly to add some interest to the
 scenery, and are not the lethal treasure-fests you find in Angband (not that there's anything wrong with that)

Guidelines for creating new vault maps:

Basically you can just let your creativity run wild. You do not have
to place all of the stairs unless the level is full screen, in which
case you must place all except the extra stairs (> and <). The <> stairs
can be put anywhere and in any quantities but do not have to be there. Any
of the other stairs which are not present in the vault will be randomly
placed outside it. Also generally try to avoid rooms with no exit.

You can use the templates below to build vaults, and remember to return the
same number (this number is used in builder2.cc to determine where on the map
the vault is located). The entry point '@' must be present (except
full-screen vaults where it must not) and be on the same side of the vault
as it is on the template, but can be anywhere along that side.

You'll have to tell me the level range in which you want the vault to appear,
so that I can code it into the vault management function. Unless you've
placed specific monster types this will probably be unnecessary.


I think that's all. Have fun!



*/

char vault_1(char vgrid [81] [81], int mons_array [7]) // my first vault
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxx....x........x........x.................................xxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxx|=8...x........+........x......x....x....x....x....x....x...xxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxx|x....x........x........x....................................xxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxx+xxx+xxxxxxxxxxxxxx..................................xxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxx.......x.................+...................................8xxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxx.......x.................x..................................xxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxx.......+.................xx+xx................................xxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxx.......x.................x...x..x....x....x....x....x....x...xxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxx.......x.................x...x.............................xxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxx+xxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxx.........................x...x...xxxxxx..................|||||xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxx....xxxxxxxxxxxxxxxxxx...x...x......xxxxxx..................||xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxx....x...$$$$x****.999x...x...x.........xxxxxx.................xxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxx....+...$$$$x****....x...x...+............xxxxxx.........8....xxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxx....x...$$$$x****....+...x...x...............xxxxxx...........xxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxx....x...$$$$x****....x...x999x..................xxxxxx........xxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx....xxxxxxxxxxxxxxxxxx...x...xxx...................xxxxxx.....xxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxx.........................x...xxxxxx...................xxxxxx..xxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxxxx+xxxxxxxx+xxxxxxx+xxxx...xxxxxx+xxxxxxxx+xxxxxxxx+xxxxxxx=xxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx.........x.......x.......x...x.........x........x.............xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 109;
mons_array [1] = 109;
mons_array [2] = 109;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 1;


}


char vault_2(char vgrid [81] [81], int mons_array [7]) // cell vault
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxcccccccccccccccccccccccccccccccc");
strcpy(vgrid [7],  "xxxxxxxxccw.............w.............wc");
strcpy(vgrid [8],  "xxxxxxxxcc.ccccccccccccc.ccccccccccccc.c");
strcpy(vgrid [9],  "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [10], "xxxxxxxxcc.c.8..+.c....c.c....+.c..9.c.c");
strcpy(vgrid [11], "xxxxxxxxcc.c....c.+..9.c.c.9..c.+....c.c");
strcpy(vgrid [12], "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [13], "xxxxxxxxcc.cccccc.cccccc.cccccc.cccccc.c");
strcpy(vgrid [14], "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [15], "xxxxxxxxcc.c....c.c....c.c....+.c....c.c");
strcpy(vgrid [16], "xxxxxxxxcc.c8...+.+..8.c.c.8..c.+....c.c");
strcpy(vgrid [17], "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [18], "xxxxxxxxcc.cccccc.cccccc.cccccc.cccccc.c");
strcpy(vgrid [19], "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [20], "xxxxxxxxcc.c....+.c....c.c.0..c.c....c.c");
strcpy(vgrid [21], "xxxxxxxxcc.c..9.c.+.8..c.c....+.+.0..c.c");
strcpy(vgrid [22], "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [23], "xxxxxxxxcc.cccccc.cccccc.cccccc.cccccc.c");
strcpy(vgrid [24], "xxxxxxxxcc.c....c.c....c.c....c.c....c.c");
strcpy(vgrid [25], "xxxxxxxxcc.c.0..+.+.0..c.c....+.+....c.c");
strcpy(vgrid [26], "xxxxxxxxcc.c....c.c....c.c.0..c.c.8..c.c");
strcpy(vgrid [27], "xxxxxxxxcc.cccccc.c....c.c....c.cccccc.c");
strcpy(vgrid [28], "xxxxxxxxcc.c....c.cccccc.cccccc.c....c.c");
strcpy(vgrid [29], "xxxxxxxxcc.c....c.c....c.c..9.+.+....c.c");
strcpy(vgrid [30], "xxxxxxxxcc.c.0..+.+....c.c9...c.c.0..c.c");
strcpy(vgrid [31], "xxxxxxxxcc.c....c.c.8..c.c....c.c....c.c");
strcpy(vgrid [32], "xxxxxxxxcc.cccccc.cccccc.cccccc.cccccc.c");
strcpy(vgrid [33], "xxxxxxxxccw.......wwwwwc.cwwwww.......wc");
strcpy(vgrid [34], "xxxxxxxxcccccccccccccccc.ccccccccccccccc");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxxxc@cxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 2;


}

char vault_3(char vgrid [81] [81], int mons_array [7]) // little maze vault
{

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [0],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [1],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [2],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [3],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [4],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [5],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [6],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [7],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [8],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [9],   "x900x..............x..........xxxxxxxxxx");
strcat(vgrid [10],  "x999x.xxxxxxxxxxxx.x.xxxxxxxx.xxxxxxxxxx");
strcat(vgrid [11],  "x000x.x............x.x......x.xxxxxxxxxx");
strcat(vgrid [12],  "xx.xx.xxxxxxxxxxxxxx.x.xxxx.x.xxxxxxxxxx");
strcat(vgrid [13],  "xx.x..............xx.x.88|x.x.xxxxxxxxxx");
strcat(vgrid [14],  "xx.x.x.xxxxxxxxxx.xx.xxxxxx.x.xxxxxxxxxx");
strcat(vgrid [15],  "xx.x.x.x........x...........x.xxxxxxxxxx");
strcat(vgrid [16],  "xx.x.x.x.xxxxxx.xxxxxxxxxxxxx.xxxxxxxxxx");
strcat(vgrid [17],  "xx.xxx.x.x$$$$x...............xxxxxxxxxx");
strcat(vgrid [18],  "xx.....x.x$$$$x.xxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [19],  "xxxxxxxx.x$$$$x...............xxxxxxxxxx");
strcat(vgrid [20],  "x........x$$$$x.xxxxxxxxxxxxx.xxxxxxxxxx");
strcat(vgrid [21],  "x.xxxxxx.xxxx.x.............x.xxxxxxxxxx");
strcat(vgrid [22],  "x.xxxxxx.xxxx.xxxxxxxxxxxxx.x.xxxxxxxxxx");
strcat(vgrid [23],  "x.x.......xxx.x...........x.x.xxxxxxxxxx");
strcat(vgrid [24],  "x.x.xxxxx.....x.x.xxxxx...x.x.xxxxxxxxxx");
strcat(vgrid [25],  "x.x.x999xxxxxxx.x.x***x...x.x.xxxxxxxxxx");
strcat(vgrid [26],  "x.x.x889........x.x|||xxxxx.x.xxxxxxxxxx");
strcat(vgrid [27],  "x.x.x899x.xxxxx.x.x***xxxxx.x.xxxxxxxxxx");
strcat(vgrid [28],  "x.x.xxxxx.xxxxx.x.xx.xxxxxx.x.xxxxxxxxxx");
strcat(vgrid [29],  "x.x..........xx.x.xx........x.xxxxxxxxxx");
strcat(vgrid [30],  "x.xxxxxxx.xx.xx.x.xxxxx.xxxxx.xxxxxxxxxx");
strcat(vgrid [31],  "x.xxx000x.xx.xx.x.x$$$x.xxxxx.xxxxxxxxxx");
strcat(vgrid [32],  "x|||x000x.x$$$x.x.x$$$x%%x%%%.xxxxxxxxxx");
strcat(vgrid [33],  "x|||x000..x$8$x.x.x$$$x%%x%8%xxxxxxxxxxx");
strcat(vgrid [34],  "x|||xxxxxxx$$$x.x..$$$xxxx%%%xxxxxxxxxxx");
strcat(vgrid [35],  "xxxxxxxxxxxxxxx@xxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 3;


}

char vault_4(char vgrid [81] [81], int mons_array [7]) // thingy vault
{

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcpy(vgrid [36], "xxxxxxxxxxxxxxxxxxxxxxxxx@xxxxxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxxxxxxxxxxxxxxx.....xxxxxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxxxxxxxxxxxxxx.....xxxxxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxxxxxxxxxxxx.........xxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxxxxxxxx.................xxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxxxx.......................xxx");
strcpy(vgrid [46], "xxxxxxxxxxxxxx.......................xxx");
strcpy(vgrid [47], "xxxxxxxxxxxxx8.......................8xx");
strcpy(vgrid [48], "xxxxxxxxxxxxxx.......................xxx");
strcpy(vgrid [49], "xxxxxxxxxxxxxx.......................xxx");
strcpy(vgrid [50], "xxxxxxxxxxxxxxx.....................xxxx");
strcpy(vgrid [51], "xxxxxxxxxxxxxxxxxxxx...........xxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxx.....xxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxx...............xxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxx8.................8xxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxx.............xxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxx999xxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 4;


}

char vault_5(char vgrid [81] [81], int mons_array [7]) // Hourglass vault
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [36], "xxxxxxxxxxxxxx@xxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [37], "xxxxxx.................xxxxxxxxxxxxxxxxx");
strcat(vgrid [38], "xxxxx...................xxxxxxxxxxxxxxxx");
strcat(vgrid [39], "xxxxx...................xxxxxxxxxxxxxxxx");
strcat(vgrid [40], "xxxxxx.................xxxxxxxxxxxxxxxxx");
strcat(vgrid [41], "xxxxxx.................xxxxxxxxxxxxxxxxx");
strcat(vgrid [42], "xxxxxx.................xxxxxxxxxxxxxxxxx");
strcat(vgrid [43], "xxxxxxx...............xxxxxxxxxxxxxxxxxx");
strcat(vgrid [44], "xxxxxxx...............xxxxxxxxxxxxxxxxxx");
strcat(vgrid [45], "xxxxxxxx.............xxxxxxxxxxxxxxxxxxx");
strcat(vgrid [46], "xxxxxxxxx.....8.....xxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [47], "xxxxxxxxxx...999...xxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [48], "xxxxxxxxxxxx00000xxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [49], "xxxxxxxxxxxxx===xxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [50], "xxxxxxxxxxxx.....xxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [51], "xxxxxxxxxx.........xxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [52], "xxxxxxxxx...........xxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [53], "xxxxxxxx......|......xxxxxxxxxxxxxxxxxxx");
strcat(vgrid [54], "xxxxxxx...............xxxxxxxxxxxxxxxxxx");
strcat(vgrid [55], "xxxxxxx...............xxxxxxxxxxxxxxxxxx");
strcat(vgrid [56], "xxxxxx........$........xxxxxxxxxxxxxxxxx");
strcat(vgrid [57], "xxxxxx.......$$$.......xxxxxxxxxxxxxxxxx");
strcat(vgrid [58], "xxxxxx....$$$$$$$$$....xxxxxxxxxxxxxxxxx");
strcat(vgrid [59], "xxxxx$$$$$$$$$$$$$$$$$$$xxxxxxxxxxxxxxxx");
strcat(vgrid [60], "xxxxx$$$$$$$$$$$$$$$$$$$xxxxxxxxxxxxxxxx");
strcat(vgrid [61], "xxxxxx$$$$$$$$$$$$$$$$$xxxxxxxxxxxxxxxxx");
strcat(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 5;


}

char vault_6(char vgrid [81] [81], int mons_array [7]) // a more Angbandy vault
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [0],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [1],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [2],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [3],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [4],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [5],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [6],   "ccccccccccccccccccccccccccccccccxxxxxxxx");
strcat(vgrid [7],   "c*******cc..9...cc.+8c0c*c.c*c8cxxxxxxxx");
strcat(vgrid [8],   "c******cc..cc..cc..cc0c.c.c.c8ccxxxxxxxx");
strcat(vgrid [9],   "c*****cc..cc..cc..cc.c$c.c.c8c.cxxxxxxxx");
strcat(vgrid [10],  "c****cc9.cc..cc8.cc|c.c|c.c*c0ccxxxxxxxx");
strcat(vgrid [11],  "c***cc..cc..cc..cc.c.c.c.c.c.c$cxxxxxxxx");
strcat(vgrid [12],  "c**cc..cc8.cc..cc.c*c.c.c.c.c.ccxxxxxxxx");
strcat(vgrid [13],  "c+cc9.cc..cc..cc.c.c.c.c*c.c.c.cxxxxxxxx");
strcat(vgrid [14],  "c.c..cc..cc..cc.c$c.c.c.c.c.c*ccxxxxxxxx");
strcat(vgrid [15],  "c...cc..cc..cc.c.c.c9c$c.c.c.c9cxxxxxxxx");
strcat(vgrid [16],  "c..cc..cc..cc$c.c.c*c.c.c.c9c9ccxxxxxxxx");
strcat(vgrid [17],  "c.cc..cc..cc.c.c|c.c.c.c.c$c.c9cxxxxxxxx");
strcat(vgrid [18],  "ccc..cc..cc.c.c.c.c.c.c.c.c.cc+cxxxxxxxx");
strcat(vgrid [19],  "cc..cc..cc.c*c.c.c.c.c.c$c.cc..cxxxxxxxx");
strcat(vgrid [20],  "c0.cc..cc.c.c.c.c8c.c*c.c.cc0.ccxxxxxxxx");
strcat(vgrid [21],  "c.cc..cc*c.c.c.c.c$c.c.c.cc..cccxxxxxxxx");
strcat(vgrid [22],  "c.c..cc.c.c9c.c.c.c.c.c.cc..cc.cxxxxxxxx");
strcat(vgrid [23],  "c0..cc$c.c.c*c0c.c.c.c.cc..cc.0cxxxxxxxx");
strcat(vgrid [24],  "c..cc.c.c9c.c.c.c$c.c.cc.9cc...cxxxxxxxx");
strcat(vgrid [25],  "c.cc9c.c.c.c.c.c.c.c.cc..cc..c.cxxxxxxxx");
strcat(vgrid [26],  "ccc.c.c$c.c.c.c.c.c$cc..cc..cc.cxxxxxxxx");
strcat(vgrid [27],  "cc$c.c.c.c.c$c.c0c.cc..cc..cc..cxxxxxxxx");
strcat(vgrid [28],  "c.c.c.c.c.c.c.c.c.cc9.cc..cc..ccxxxxxxxx");
strcat(vgrid [29],  "cc.c8c.c.c$c.c.c.cc..cc..cc0.cccxxxxxxxx");
strcat(vgrid [30],  "c.c$c.c$c0c.c.c.cc..cc..cc..cc$cxxxxxxxx");
strcat(vgrid [31],  "cc.c.c.c.c.c*c.cc..cc..cc..cc$$cxxxxxxxx");
strcat(vgrid [32],  "c.c.c.c.c.c.c.cc..cc0.cc..cc$$$cxxxxxxxx");
strcat(vgrid [33],  "cc.c.c.c.c.c$cc..cc..cc..cc$$$$cxxxxxxxx");
strcat(vgrid [34],  "c.c.c.c.c.c.cc.8....cc....+$$$$cxxxxxxxx");
strcat(vgrid [35],  "cccc@cccccccccccccccccccccccccccxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 3;


}


char vault_7(char vgrid [81] [81], int mons_array [7]) // four leaf vault
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxx......................xxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxx...xxxxxxxx..xxxxxxxx...xxxx");
strcpy(vgrid [9],  "xxxxxxxxxxx...xxxxxxxxx..xxxxxxxxx...xxx");
strcpy(vgrid [10], "xxxxxxxxxx...xx$*....xx..xx....$$xx...xx");
strcpy(vgrid [11], "xxxxxxxxx...xx$*$....xx..xx....$*$xx...x");
strcpy(vgrid [12], "xxxxxxxxx..xx*$*$....xx..xx....*$$$xx..x");
strcpy(vgrid [13], "xxxxxxxxx..xx$$$.00..xx..xx..00.*$*xx..x");
strcpy(vgrid [14], "xxxxxxxxx..xx....09..xx..xx..90....xx..x");
strcpy(vgrid [15], "xxxxxxxxx..xx......+xx....xx+......xx..x");
strcpy(vgrid [16], "xxxxxxxxx..xx......x........x......xx..x");
strcpy(vgrid [17], "xxxxxxxxx..xxxxxxxxx........xxxxxxxxx..x");
strcpy(vgrid [18], "xxxxxxxxx..xxxxxxxx..........xxxxxxxx..x");
strcpy(vgrid [19], "xxxxxxxxx..............99..............x");
strcpy(vgrid [20], "xxxxxxxxx..............00..............x");
strcpy(vgrid [21], "xxxxxxxxx..xxxxxxxx..........xxxxxxxx..x");
strcpy(vgrid [22], "xxxxxxxxx..xxxxxxxxx........xxxxxxxxx..x");
strcpy(vgrid [23], "xxxxxxxxx..xx......x........x......xx..x");
strcpy(vgrid [24], "xxxxxxxxx..xx......+xx....xx+......xx..x");
strcpy(vgrid [25], "xxxxxxxxx..xx....09..xx..xx..90....xx..x");
strcpy(vgrid [26], "xxxxxxxxx..xx$$*.00..xx..xx..00.*$$xx..x");
strcpy(vgrid [27], "xxxxxxxxx..xx*$*$....xx..xx....*$$*xx..x");
strcpy(vgrid [28], "xxxxxxxxx...xx*$*....xx..xx....$$$xx...x");
strcpy(vgrid [29], "xxxxxxxxxx...xx*$....xx..xx....*$xx...xx");
strcpy(vgrid [30], "xxxxxxxxxxx...xxxxxxxxx..xxxxxxxxx...xxx");
strcpy(vgrid [31], "xxxxxxxxxxxx...xxxxxxxx..xxxxxxxx...xxxx");
strcpy(vgrid [32], "xxxxxxxxxxxxx......................xxxxx");
strcpy(vgrid [33], "xxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxxxxxxxxxxxxxx++xxxxxxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxxx@xxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 2;


}


char vault_8(char vgrid [81] [81], int mons_array [7]) // cross vault
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxx............xxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxx..................xxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxx......................xxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxx..........w..w..........xxxx");
strcpy(vgrid [11], "xxxxxxxxxxx........wwww..wwww........xxx");
strcpy(vgrid [12], "xxxxxxxxxxx......wwwvvv++vvvwww......xxx");
strcpy(vgrid [13], "xxxxxxxxxx......wwwwv......vwwww......xx");
strcpy(vgrid [14], "xxxxxxxxxx.....wwwwwv......vwwwww.....xx");
strcpy(vgrid [15], "xxxxxxxxxx....wwwwwvv......vvwwwww....xx");
strcpy(vgrid [16], "xxxxxxxxx....wwwwwvv........vvwwwww....x");
strcpy(vgrid [17], "xxxxxxxxx....wwvvvv....vv....vvvvww....x");
strcpy(vgrid [18], "xxxxxxxxx...wwwv......vvvv......vwww...x");
strcpy(vgrid [19], "xxxxxxxxx...wwwv....vv8vv8vv....vwww...x");
strcpy(vgrid [20], "xxxxxxxxx..wwwwv...vvvv||vvvv...vwwww..x");
strcpy(vgrid [21], "xxxxxxxxx..wwwwv...vvvv||vvvv...vwwww..x");
strcpy(vgrid [22], "xxxxxxxxx..wwwwv....vv8vv8vv....vwwww..x");
strcpy(vgrid [23], "xxxxxxxxx...wwwv......vvvv......vwww...x");
strcpy(vgrid [24], "xxxxxxxxx...wwwvvvv....vv....vvvvwww...x");
strcpy(vgrid [25], "xxxxxxxxx....wwwwwvv........vvwwwww....x");
strcpy(vgrid [26], "xxxxxxxxxx...wwwwwwvv......vvwwwwww...xx");
strcpy(vgrid [27], "xxxxxxxxxx....wwwwwwv......vwwwwww....xx");
strcpy(vgrid [28], "xxxxxxxxxx.....wwwwwv......vwwwww.....xx");
strcpy(vgrid [29], "xxxxxxxxxxx.....wwwwvvvvvvvvwwww.....xxx");
strcpy(vgrid [30], "xxxxxxxxxxx.......wwwwwwwwwwww.......xxx");
strcpy(vgrid [31], "xxxxxxxxxxxx.........wwwwww.........xxxx");
strcpy(vgrid [32], "xxxxxxxxxxxxx......................xxxxx");
strcpy(vgrid [33], "xxxxxxxxxxxxxxx.......x++x.......xxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxxxxxxxxx...xx..xx...xxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxx..@.xxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 2;


}

char vault_9(char vgrid [81] [81], int mons_array [7]) // another thingy vault, purely decorative with no monsters or items
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [36], "xxxxxxxxxxxxxxx@xxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [37], "xxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [38], "xxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [39], "xx...........................xxxxxxxxxxx");
strcat(vgrid [40], "x..bb..xxxxxxxxxxxxxxxxx..bb..xxxxxxxxxx");
strcat(vgrid [41], "x..b...xxxxxxxxxxxxxxxxx...b..xxxxxxxxxx");
strcat(vgrid [42], "x...b..xxxxbbbbbbbbbxxxx..b...xxxxxxxxxx");
strcat(vgrid [43], "x..bb..xxbbb.......bbbxx..bb..xxxxxxxxxx");
strcat(vgrid [44], "x......xxb...........bxx......xxxxxxxxxx");
strcat(vgrid [45], "x..bb..xbb...........bbx..bb..xxxxxxxxxx");
strcat(vgrid [46], "x...b..xb.............bx..b...xxxxxxxxxx");
strcat(vgrid [47], "x..b...xb.............bx...b..xxxxxxxxxx");
strcat(vgrid [48], "x...b..xb.............bx..b...xxxxxxxxxx");
strcat(vgrid [49], "x..b...xb.............bx...b..xxxxxxxxxx");
strcat(vgrid [50], "x...b..xbb...........bbx..b...xxxxxxxxxx");
strcat(vgrid [51], "x..b...xxb...........bxx...b..xxxxxxxxxx");
strcat(vgrid [52], "x..bb..xxbbb.......bbbxx..bb..xxxxxxxxxx");
strcat(vgrid [53], "x......xxxxbbbb.bbbbxxxx......xxxxxxxxxx");
strcat(vgrid [54], "x..bb..xxxxxxxb=bxxxxxxx..bb..xxxxxxxxxx");
strcat(vgrid [55], "x..b...xxxxxxxx=xxxxxxxx...b..xxxxxxxxxx");
strcat(vgrid [56], "x...b..xxxxxxxx.xxxxxxxx..b...xxxxxxxxxx");
strcat(vgrid [57], "x..b....xxxxxxx=xxxxxxx....b..xxxxxxxxxx");
strcat(vgrid [58], "x...b.....................b...xxxxxxxxxx");
strcat(vgrid [59], "x..b....xxxxxxxxxxxxxxx....b..xxxxxxxxxx");
strcat(vgrid [60], "x..bb..xxxxxxxxxxxxxxxxx..bb..xxxxxxxxxx");
strcat(vgrid [61], "xx....xxxxxxxxxxxxxxxxxxx....xxxxxxxxxxx");
strcat(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 5;


}

char orc_temple(char vgrid [81] [81], int mons_array [7])
{

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcpy(vgrid [36], "xxxxxxxxxxxxxxxxxxxxxxx@xxxxxxxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxxxxxxxxxxxxxx4.4xxxxxxxxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxx............x1.1x............xx");
strcpy(vgrid [41], "xxxxxxxxx............x1.1x............xx");
strcpy(vgrid [42], "xxxxxxxxx............+...+....4.......xx");
strcpy(vgrid [43], "xxxxxxxxx....4..4....x...x............xx");
strcpy(vgrid [44], "xxxxxxxxx............x...x.......4....xx");
strcpy(vgrid [45], "xxxxxxxxx............xx.xx............xx");
strcpy(vgrid [46], "xxxxxxxxx...4......xxxx+xxxx......6...xx");
strcpy(vgrid [47], "xxxxxxxxx........xxx.......xxx........xx");
strcpy(vgrid [48], "xxxxxxxxxxx...xxxx..2.....2..xxxx...xxxx");
strcpy(vgrid [49], "xxxxxxxxxxxx+xxxx.............xxxx+xxxxx");
strcpy(vgrid [50], "xxxxxxxxxxx...xxx.............xxx...xxxx");
strcpy(vgrid [51], "xxxxxxxxx......x...............x......xx");
strcpy(vgrid [52], "xxxxxxxxx..4...x...2...I...2...x...5..xx");
strcpy(vgrid [53], "xxxxxxxxx......x...............x......xx");
strcpy(vgrid [54], "xxxxxxxxx...4..xx.............xx..5...xx");
strcpy(vgrid [55], "xxxxxxxxx.......x....2...2....x.......xx");
strcpy(vgrid [56], "xxxxxxxxx.6..5..xx.....3.....xx.5...7.xx");
strcpy(vgrid [57], "xxxxxxxxx........xxx.......xxx........xx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 14; // orc
mons_array [1] = 112; // orc priest
mons_array [2] = 113; // orc high priest
mons_array [3] = 52; // orc warrior
mons_array [4] = 54; // orc wizard
mons_array [5] = 55; // orc knight
mons_array [6] = 103; // orc sorceror
// remember to add one to the array (is 1-7, not 0-6)

return 4;


}


char vault_10(char vgrid [81] [81], int mons_array [7]) // impenetrable vault
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [36], "..............@................xxxxxxxxx");
strcat(vgrid [37], "...............................xxxxxxxxx");
strcat(vgrid [38], "...............................xxxxxxxxx");
strcat(vgrid [39], "...............................xxxxxxxxx");
strcat(vgrid [40], "...............................xxxxxxxxx");
strcat(vgrid [41], ".....xxxxxxxxxxxxxxxx..........xxxxxxxxx");
strcat(vgrid [42], ".....x[.............xx.........xxxxxxxxx");
strcat(vgrid [43], ".....x.xxxxx=xxxxxx..xx........xxxxxxxxx");
strcat(vgrid [44], ".....x.x..........xx..xx.......xxxxxxxxx");
strcat(vgrid [45], ".....x.x.xxx=xxxx..xx..xx......xxxxxxxxx");
strcat(vgrid [46], ".....x.x.x$$$$$$xx..xx..x......xxxxxxxxx");
strcat(vgrid [47], ".....x.=.=$$|||$$xx..xx.x......xxxxxxxxx");
strcat(vgrid [48], ".....x.x.xx$$|||$$xx..x.x......xxxxxxxxx");
strcat(vgrid [49], ".....x.x..xx$$|||$$xx.x.x......xxxxxxxxx");
strcat(vgrid [50], ".....x.xx..xx$$|||$$=.=.x......xxxxxxxxx");
strcat(vgrid [51], ".....x..xx..xx$$$$$$x.x.x......xxxxxxxxx");
strcat(vgrid [52], ".....xx..xx..xxxx=xxx.x.x......xxxxxxxxx");
strcat(vgrid [53], "......xx..xx..........x.x......xxxxxxxxx");
strcat(vgrid [54], ".......xx..xxxxxx=xxxxx.x......xxxxxxxxx");
strcat(vgrid [55], "........xx.............]x......xxxxxxxxx");
strcat(vgrid [56], ".........xxxxxxxxxxxxxxxx......xxxxxxxxx");
strcat(vgrid [57], "...............................xxxxxxxxx");
strcat(vgrid [58], "...............................xxxxxxxxx");
strcat(vgrid [59], "...............................xxxxxxxxx");
strcat(vgrid [60], "...............................xxxxxxxxx");
strcat(vgrid [61], "...............................xxxxxxxxx");
strcat(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 5;


}


char my_map(char vgrid [81] [81], int mons_array [7])
{
// designed by Matthew Ludivico


int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}



strcpy(vgrid [36], "xxxxxxxxxx.@.xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxxxx..........................xx");
strcpy(vgrid [39], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..xx");
strcpy(vgrid [40], "xxxxxxxxx.^^..........................xx");
strcpy(vgrid [41], "xxxxxxxxxx.^^xx+xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxx.^...11....xxxxxxxx..xxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxxx..x.1..6..xxx........xx..xxx");
strcpy(vgrid [44], "xxxxxxxxxxxxx.xxxxxxxxx...vvvvv...x...xx");
strcpy(vgrid [45], "xxxxxxxxx6..1...x.........+1..v.......xx");
strcpy(vgrid [46], "xxxxxxxxx..1....x.........vvvvv........x");
strcpy(vgrid [47], "xxxxxxxxx..5...xx......................x");
strcpy(vgrid [48], "xxxxxxxxxxxxxx^++...........vvvvvvv....x");
strcpy(vgrid [49], "xxxxxxxxxxxxxx^xx...xx=xx...vv$%$vvvvv.x");
strcpy(vgrid [50], "xxxxxxxxxxxxxx^x...xxv1vxx...vvv*2...v.x");
strcpy(vgrid [51], "xxxxxxxxxxxxxx^x..vvvv7.vvvv...vv.vv+v^x");
strcpy(vgrid [52], "xxxxxxxxx..xxx^..vvvb....bvvv...vvv^...x");
strcpy(vgrid [53], "xxxxxxxxx%%.xx..vvvvb....bvvvv.......xxx");
strcpy(vgrid [54], "xxxxxxxxxx.....vvbbb......bbbvv.....xxxx");
strcpy(vgrid [55], "xxxxxxxxxxx....vvb....66....bvvxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxvvvb..llllll..bvvvxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxvvvvvvvvb..ll45ll..bvvvvvvvvxxx");
strcpy(vgrid [58], "xxxxxxxxxccc***+== .l3.2.l..cccccccccxxx");
strcpy(vgrid [59], "xxxxxxxxxccc+cccbb....ll....c..$$$$+$*cx");
strcpy(vgrid [60], "xxxxxxxxxcc|||cbb...3llll2...cc%*%*c$|cx");
strcpy(vgrid [61], "xxxxxxxxxcccccccbbbbbbbbbbbccccccccccccx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


mons_array [0] = 73; // hell hound
mons_array [1] = 110; // necromancer
mons_array [2] = 111; // wizard
mons_array [3] = 226; // LIGHTRED demon
mons_array [4] = 81; // rotting devil
mons_array [5] = 109; // hellknight
mons_array [6] = 79; // GOoE
// remember to add one to the array (is 1-7, not 0-6)

return 4;





}


char farm_and_country(char vgrid [81] [81], int mons_array [7])
// By Matthew Ludivico (mll6@lehigh.edu)
{

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}



strcpy(vgrid [0], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7], "xxxxxxxxxxxxxxxxx..........................................xxxxxxxx}.xxxxxxxxxxx");
strcpy(vgrid [8], "xxxxxxxxxxxxxxxxxxx............xxxxxx....xxx.......xx...........xxxx..]xxxxxxxxx");
strcpy(vgrid [9], "xxxxxxxxxxxxxxx***x...........xxx..xxx............xxxx...........xx..xxxxxxxxxxx");
strcpy(vgrid [10],"xxxxxxxxxxxxxxx|*$=...xx.xxxxxxx....xxxxxxxxxx......xx................xxxxxxxxxx");
strcpy(vgrid [11],"xxxxxxxxxxxxxxxxxxx....xxxxxxxx......3..xxx.................x..........xxxxxxxxx");
strcpy(vgrid [12],"xxxxxxxxxxxxxxxxxx......x........x......xx.........w...................xxxxxxxxx");
strcpy(vgrid [13],"xxxxxxxxxxx)......xx...xxx.....xxx......x........www3....3.............xxxxxxxxx");
strcpy(vgrid [14],"xxxxxxxxxxxx=xxxxxxxxxxx...xxxxxxxxx..xxx.....wwwww....%%%.............xxxxxxxxx");
strcpy(vgrid [15],"xxxxxxxxxx......xxx.......xx.xxxx.x...xxxxxxxwwwwwww..5%%%..........xx.xxxxxxxxx");
strcpy(vgrid [16],"xxxxxxxxx.........x..xxxxxxxx.....x........3wwwwwwwww..%%%........xxx..xxxxxxxxx");
strcpy(vgrid [17],"xxxxxxxxx....5...xx..x.xxxxx.....xxx........wwwwwwwww..%%%..........xx.xxxxxxxxx");
strcpy(vgrid [18],"xxxxxxxxxxx.....xxx..xx..xx........xxxxxxxxxwwwwwwwww..............xxx.xxxxxxxxx");
strcpy(vgrid [19],"xxxxxxxxxx........x..x...............xx..xxxxwwwwwwwwwwwwww............xxxxxxxxx");
strcpy(vgrid [20],"xxxxxxxxx.............................x.....xxwwwwww3wwwwww............xxxxxxxxx");
strcpy(vgrid [21],"xxxxxxxxxxx...x...........5.....7...............ww.......ww.....44....xxxxxxxxxx");
strcpy(vgrid [22],"xxxxxxxxxwxx..xx.....622...2.26...6.2...22.6...62..2..226ww.....44xx...xxxxxxxxx");
strcpy(vgrid [23],"xxxxxxxxxwwxxxx......2....2.22....2..2...2.2.......22...2ww....xxxx..xxxxxxxxxxx");
strcpy(vgrid [24],"xxxxxxxxxwwwwxxx......2...2.2.2...2.22..2.22...22.2.2..22ww.....xxx....xxxxxxxxx");
strcpy(vgrid [25],"xxxxxxxxxwwwwwx....4..2...2...........22...277..2..2.2.22ww...........xxxxxxxxxx");
strcpy(vgrid [26],"xxxxxxxxxwwwwwxx....42..2....22.4..2..2...2.4..2.22..22.2ww............xxxxxxxxx");
strcpy(vgrid [27],"xxxxxxxxxwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.wwwwwwwwwwwww..2.........xxxxxxxxx");
strcpy(vgrid [28],"xxxxxxxxxwwwwwxx.....62....2.26...62.2.2..26...6...22..26..............xxxxxxxxx");
strcpy(vgrid [29],"xxxxxxxxxwwwww.........................................................xxxxxxxxx");
strcpy(vgrid [30],"xxxxxxxxxwwwwwxx....222.2.22..2.7.......7..............................xxxxxxxxx");
strcpy(vgrid [31],"xxxxxxxxxwwwww...........ccccccc+ccccccc...ccc......cc+ccc...xxxxx.....xxxxxxxxx");
strcpy(vgrid [32],"xxxxxxxxxwwwwwxx.........c$$*.c$$5$+.5.c...+5c......c%%%%c......xxx3...xxxxxxxxx");
strcpy(vgrid [33],"xxxxxxxxxwwwwwx....2.....c$.c+cccccc.%.c...ccc......c%%%%c....xxxxx....xxxxxxxxx");
strcpy(vgrid [34],"xxxxxxxxxwwwwwx..........c..c..........c............cccccc......xxx....xxxxxxxxx");
strcpy(vgrid [35],"xxxxxxxxxwwxxxxxxx.......ccccc+ccccccccc.........................xx....xxxxxxxxx");
strcpy(vgrid [36],"xxxxxxxxxwxx.....xxxx........c...c.................2...................xxxxxxxxx");
strcpy(vgrid [37],"xxxxxxxxxxx.........xxxx...........2....xxxx...........................xxxxxxxxx");
strcpy(vgrid [38],"xxxxxxxxx..............xxxx..........xxxx..x...........................xxxxxxxxx");
strcpy(vgrid [39],"xxxxxxxxx.................xxxxx++xxxxx.....xx............xx...x........xxxxxxxxx");
strcpy(vgrid [40],"xxxxxxxxx.....................c..c..........xxxxx..........xxxxx.......xxxxxxxxx");
strcpy(vgrid [41],"xxxxxxxxx.......cccc..........c..c...cccc......xxx...........x.........xxxxxxxxx");
strcpy(vgrid [42],"xxxxxxxxx.......c..c..........c++c...c..c........xxx.........x.........xxxxxxxxx");
strcpy(vgrid [43],"xxxxxxxxx.......c..c..........c..c...c..c..........xxx.................xxxxxxxxx");
strcpy(vgrid [44],"xxxxxxxxx....cccc++cccccccccccc++ccccc..ccccccc......xxx...............xxxxxxxxx");
strcpy(vgrid [45],"xxxxxxxxx....c..........1.....................c........xxx.............xxxxxxxxx");
strcpy(vgrid [46],"xxxxxxxxx.cccc.....w....w....%1.....w.....%...c..........xxx...........xxxxxxxxx");
strcpy(vgrid [47],"xxxxxxxxx.c1.+....www..www..%%%....www...%%%1.c...........xxxxxxxxx....xxxxxxxxx");
strcpy(vgrid [48],"xxxxxxxxx.cccc.....w....w....%......w.....%...c..................xxx...xxxxxxxxx");
strcpy(vgrid [49],"xxxxxxxxx....c.......5........................c....................xxxxxxxxxxxxx");
strcpy(vgrid [50],"xxxxxxxxx....ccc....%%%%%....cccccccccccccccccc........................xxxxxxxxx");
strcpy(vgrid [51],"xxxxxxxxx......cc...........cc.........................................xxxxxxxxx");
strcpy(vgrid [52],"xxxxxxxxx.......cccccc+cccccc..........................................xxxxxxxxx");
strcpy(vgrid [53],"xxxxxxxxx........cc.......cc...........................................xxxxxxxxx");
strcpy(vgrid [54],"xxxxxxxxx.........cc.....cc.....................cccccccccccccccccccccccxxxxxxxxx");
strcpy(vgrid [55],"xxxxxxxxx..........ccc+ccc......................c......vvv.............xxxxxxxxx");
strcpy(vgrid [56],"xxxxxxxxx..........ccc.c........................c......v5+...vvvvv.....xxxxxxxxx");
strcpy(vgrid [57],"xxxxxxxxx..........ccc.c........................c......vvv...v.5.v.....xxxxxxxxx");
strcpy(vgrid [58],"xxxxxxxxxccccccccccccc.ccc......................c............v..5v.....xxxxxxxxx");
strcpy(vgrid [59],"xxxxxxxxx..........c.....cccccccccccccccccccccccccccc..........vv+vv...xxxxxxxxx");
strcpy(vgrid [60],"xxxxxxxxx..........c............................+................5111..xxxxxxxxx");
strcpy(vgrid [61],"xxxxxxxxx..........c.{([.c......................+................5.....xxxxxxxxx");
strcpy(vgrid [62],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");



mons_array [0] = 134; // death yak
mons_array [1] = 41; // plant
mons_array [2] = 105; // griffon
mons_array [3] = 10; // k bee
mons_array [4] = 40; // ogre
mons_array [5] = 61; // ok plant
mons_array [6] = 67; // wandering mush
// remember to add one to the array (is 1-7, not 0-6)

return 6;

}


char fort_yaktaur(char vgrid [81] [81], int mons_array [7])
{
// Fort yaktaur
// By Matthew Ludivico (mll6@lehigh.edu)

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [36], ".........@....wwwwwwwwwwwwwwwwwxxxxxxxxx");
strcat(vgrid [37], ".ccccc.......ww....wwww....wwwwxxxxxxxxx");
strcat(vgrid [38], ".c$c%c......ww.ccccccccc.......xxxxxxxxx");
strcat(vgrid [39], ".c+c+c......ww.c.%$....ccccccccxxxxxxxxx");
strcat(vgrid [40], ".c...+......ww.c*.115..c$$+|*|cxxxxxxxxx");
strcat(vgrid [41], ".c1..c.....ww..c...55+ccc+cxx=cxxxxxxxxx");
strcat(vgrid [42], ".ccccc.....ww..ccccccc....c|=|cxxxxxxxxx");
strcat(vgrid [43], "............ww.......c5...cxx=cxxxxxxxxx");
strcat(vgrid [44], "....6.ccccc.ww.w...2.+51..c|1.cxxxxxxxxx"); // last 1 here was 7
strcat(vgrid [45], "....63+...c..wwww..21+51..c2.2cxxxxxxxxx");
strcat(vgrid [46], "....6.ccccc..wwwwww..c5...cc+ccxxxxxxxxx");
strcat(vgrid [47], "............wwwwwww..c........cxxxxxxxxx");
strcat(vgrid [48], "............wwwwwww..ccccccccccxxxxxxxxx");
strcat(vgrid [49], "...........ww1w..www...........xxxxxxxxx");
strcat(vgrid [50], ".......566.www.....www.........xxxxxxxxx");
strcat(vgrid [51], ".........1ww....ccccc..........xxxxxxxxx");
strcat(vgrid [52], ".....566.w......+...c..........xxxxxxxxx");
strcat(vgrid [53], ".........www....ccccc..........xxxxxxxxx");
strcat(vgrid [54], "...........ww............wwwwwwxxxxxxxxx");
strcat(vgrid [55], ".......3....wwwww......www.....xxxxxxxxx");
strcat(vgrid [56], "......666.......ww...www.......xxxxxxxxx");
strcat(vgrid [57], ".....cc+cc.......wwwww.........xxxxxxxxx");
strcat(vgrid [58], ".....c...c.....................xxxxxxxxx");
strcat(vgrid [59], ".....ccccc.....................xxxxxxxxx");
strcat(vgrid [60], "...............................xxxxxxxxx");
strcat(vgrid [61], "...............................xxxxxxxxx");
strcat(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


mons_array [0] = 133; // yaktaur
mons_array [1] = 134; // death yak
mons_array [2] = 74; // minotaur
mons_array [3] = 250;
mons_array [4] = 50; // yak
mons_array [5] = 115; // gnoll
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 5;

}

char box_level(char vgrid [81] [81], int mons_array [7])
{

// By John Savard

strcpy(vgrid [0], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7], "xxxxxxxxx.................xx.............x...................^.........xxxxxxxxx");
strcpy(vgrid [8], "xxxxxxxxx.................xx...xxxxxx....x.xxxxxxx.xxxxxxxxxxxxxxxxxxx.xxxxxxxxx");
strcpy(vgrid [9], "xxxxxxxxx.................xx...xx.0......x.x........x......x.........x.xxxxxxxxx");
strcpy(vgrid [10],"xxxxxxxxx..$..............xx...xx........x.x........x.....%x.x..*..xxx.xxxxxxxxx");
strcpy(vgrid [11],"xxxxxxxxx......................xx........x.x........x.xxxxxx.x.....x...xxxxxxxxx");
strcpy(vgrid [12],"xxxxxxxxx......................xx....%...x.x........x.x......xxxxxxx.x.xxxxxxxxx");
strcpy(vgrid [13],"xxxxxxxxx.................xx...xx........x.x........x.x.xxxxxx.......x.xxxxxxxxx");
strcpy(vgrid [14],"xxxxxxxxx.................xx...xx........x.x..{.....x.x..............x.xxxxxxxxx");
strcpy(vgrid [15],"xxxxxxxxx.............0...xx...xxxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxxxxxxxx.xxxxxxxxx");
strcpy(vgrid [16],"xxxxxxxxx.................xx...........................................xxxxxxxxx");
strcpy(vgrid [17],"xxxxxxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18],"xxxxxxxxxxxxxxxxxxxxxxxxxxxx...xxx}x.........................>=........xxxxxxxxx");
strcpy(vgrid [19],"xxxxxxxxx..................x...xxx.x.xxx+xxxxxxxxxxxxxxxx+xxxxx........xxxxxxxxx");
strcpy(vgrid [20],"xxxxxxxxx..xxxxxxxxxxxxxx..x...xxx.x.x0...x..0..............0.x........xxxxxxxxx");
strcpy(vgrid [21],"xxxxxxxxx..x............x..x...xxx.x.x....x...................x........xxxxxxxxx");
strcpy(vgrid [22],"xxxxxxxxx....xxxxxxxxx..x..x...xxx.x.x....x...................x........xxxxxxxxx");
strcpy(vgrid [23],"xxxxxxxxx..x.x....0..x..x..x...xxx...x...%x...................x*.......xxxxxxxxx");
strcpy(vgrid [24],"xxxxxxxxx..x.x..........x..x...xxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [25],"xxxxxxxxx..x.x*......x..x..x..........x...........0...x...%............xxxxxxxxx");
strcpy(vgrid [26],"xxxxxxxxx..x.xxxxxxxxx..x..=..........x.xxxxxxxxxxxxx.x................xxxxxxxxx");
strcpy(vgrid [27],"xxxxxxxxx..x......0.....xxxxxxx.......x.x...x...x...x.x................xxxxxxxxx");
strcpy(vgrid [28],"xxxxxxxxx..xxxxxxxxxxxxxxxxxxxx..0....x...x.x.x.x.x.x.x......0.........xxxxxxxxx");
strcpy(vgrid [29],"xxxxxxxxx..........^.........xx.......x.x.x.x.x.x.x...+................xxxxxxxxx");
strcpy(vgrid [30],"xxxxxxxxxcccccccccccccccccc..xx.......x.x$x...x...xxxxx................xxxxxxxxx");
strcpy(vgrid [31],"xxxxxxxxxc...........9....c..xx.......x.x.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [32],"xxxxxxxxxc......c............xx.......x.x.x...x..0.....................xxxxxxxxx");
strcpy(vgrid [33],"xxxxxxxxxc.....|c............xx.......x.x.x.x.x........................xxxxxxxxx");
strcpy(vgrid [34],"xxxxxxxxxc................c..xx.......x.x...x.x........................xxxxxxxxx");
strcpy(vgrid [35],"xxxxxxxxxcccccccccccccccccc..xx.......x.xxxxx.x........................xxxxxxxxx");
strcpy(vgrid [36],"xxxxxxxxx....................xx.......x.x.....=....................*...xxxxxxxxx");
strcpy(vgrid [37],"xxxxxxxxx....................xx.......x.x.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [38],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.......x.x.x...........................(xxxxxxxxx");
strcpy(vgrid [39],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxx.x$x..xxxx.xxxxxxxxxxxxxxxxxxxx.xxxxxxxxx");
strcpy(vgrid [40],"xxxxxxxxx...............................x.x..x.......................x.xxxxxxxxx");
strcpy(vgrid [41],"xxxxxxxxx..xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.x..x.xxxxxxxxxxxxx.........x.xxxxxxxxx");
strcpy(vgrid [42],"xxxxxxxxx.............)xxx................x..x.xxxxxxxxxxxxx.........x.xxxxxxxxx");
strcpy(vgrid [43],"xxxxxxxxx..............xxx.xxxxxxxxxxxxxxxx..x.xxxxxxxxxxxxx.........x.xxxxxxxxx");
strcpy(vgrid [44],"xxxxxxxxx..............xxx...................x.x...........xxxxx+xxxxx.xxxxxxxxx");
strcpy(vgrid [45],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.x..$........x.........x.xxxxxxxxx");
strcpy(vgrid [46],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.x...........x........%x.xxxxxxxxx");
strcpy(vgrid [47],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.x.0.........x0........x.xxxxxxxxx");
strcpy(vgrid [48],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.x.......$...x.........x.xxxxxxxxx");
strcpy(vgrid [49],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.x...........xxxxxxxxxxx.xxxxxxxxx");
strcpy(vgrid [50],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxx.x...........xxxxxxxxx");
strcpy(vgrid [51],"xxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxx.............x...........xxxxxxxxx");
strcpy(vgrid [52],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx+xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [53],"xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [54],"xxxxxxxxx.xxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxxxx.xxxxxxx=xxxxxx.xxxxxx.xxxxxxxxx");
strcpy(vgrid [55],"xxxxxxxxx.....xx.................xxxxxxxxxxx.......x........x.....x....xxxxxxxxx");
strcpy(vgrid [56],"xxxxxxxxx....0xx.................xxxxxxxxxxx.%.....x.0......x...0.x....xxxxxxxxx");
strcpy(vgrid [57],"xxxxxxxxx.....xx.9...............xxxxxxxxxxx.......x........x.%...x..$.xxxxxxxxx");
strcpy(vgrid [58],"xxxxxxxxx.....xx.................xxxxxxxxxxx.......x........x.....x....xxxxxxxxx");
strcpy(vgrid [59],"xxxxxxxxx.....xx.................xxxxxxxxxxx.......x........x.....x..0.xxxxxxxxx");
strcpy(vgrid [60],"xxxxxxxxx....0xx.................xxxxxxxxxxx.......x$.......x.....x....xxxxxxxxx");
strcpy(vgrid [61],"xxxxxxxxx]....xx................*xxxxxxxxxxx......[x........x.....x$...xxxxxxxxx");
strcpy(vgrid [62],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69],"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 6;


}


char vestibule_map(char vgrid [81] [81], int mons_array [7])
{

// this is the vestibule

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxvvvvvvvxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..v.....v..xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.....v.....v.....xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxx........v.....v........xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxxxxxxx..........v..A..v..........xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxxxxxxxxxxxx............v.....v............xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxxxxxxxxxxxx.............v.....v.............xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxxxxxxxxxxx..............vvv+vvv..............xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxxxxxxxxxx.....................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxxxxxxxxxx.......................................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxxxxxxxxxx.........................................xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxxxxxxxxxx...........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxxxxxxx.............................................xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxxxxx...............................................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxxx.................................................xxxxxxxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxx...................................................xxxxxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxxx............................{............................xxxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxx...l.l.....................................................xxxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxx..l.l.l.l..................................................xxxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxx.l.l.l.l.l.................................................xxxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx.l.l.l.l.l...................................................xxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxl.l.l.l.l.l..................................................xxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx.l.l.l.A.l.l.................}1].............................=Axxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxl.l.l.l.l.l.l.................)..............................xxxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx.l.l.l.l.l.l.................................................xxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxx.l.l.l.l.l.l...............................................xxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxx..l.l.l.l..................................................xxxxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxx.....l.l...................................................xxxxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxxx......................[...........(......................xxxxxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxxxxxxx...................................................xxxxxxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxxxxxxx....................wwwww........................xxxxxxxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxxxxxxx..................wwwwwwww.....................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxxxxxxxx..............wwwwwwwwwwwww..................xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxxxxxxxx...........w..wwww..wwwww..w...............xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxxxxxxxxx..........w...ww.....ww..wwwww...........xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxxxxxxxxxx.........ww......ww....wwwwwwwww.......xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxxxxxxx.........ww....wwww...wwwwwwwwww.....xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxxxxxxx.........ww....ww....wwwwwwwwwww...xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxxxxx........wwww.......wwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxxx......wwwwwww....wwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxxx...wwwwwwwwwwAwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxwwwwwwwwwwwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxwwwwwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 340; // Geryon
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 6;


}

char castle_dis(char vgrid [81] [81], int mons_array [7])
{

// map of Dispater's castle. Rest of level filled up with plan_4 (irregular city)

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxv..............................................................vxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxv..vvvvvvvvv........................................vvvvvvvvv..vxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxv..v3.....|v........................................v|.....2v..vxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxv..v.vv+vvvv.v.v.v.v.v.v.v.v.v..v.v.v.v.v.v.v.v.v.v.vvvv+vv.v..vxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxv..v.v.....vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv.....v.v..vxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxv..v|v.....+$$v$$+$$v||vvvvvvvvvvvvvvvvv$$$$v4.4.v$$v.....v|v..vxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxv..vvvv+vvvv$$+$$v$$+||v...............v$$$$+.4.4+$$v+vv+vvvv..vxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxv....vv.vvvvvvvvvvvvvvvv.v..v..v..v..v.v$$$$v4.4.v$$+||v.vv5...vxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxv...vvv................v...............vvvvvvvvvvvvvvvvv.vvv...vxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxv...5vv................+...............+.................vv....vxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxv...vvv+vvvvvvvvvvvvvvvv.v..v..v..v..v.vvvvvvvvvvvvvvvvv.vvv...vxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxv....vv..v.+$$$$$v.....v...............vvvvvvvvvvvvvvvvv.vv5...vxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxv...vvv..v.v$$$$$v.....v...............vv|$|$|vv|$|$|$vv.vvv...vxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxv...5vv..v.vvvvvvv.....vvvvv.......vvvvvv$|$|$++$|$|$|vv.vv....vxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxv...vvv..v...............v.vvvv+vvvvvvvvvvvvvvvvvvvvv+vv.vvv...vxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxv....vvv+v..........vvvvv.4vvv...vvvvvvvvvvvvvvvvvvvv+vv.vv5...vxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxv...vvv..v.v..v..v....2vvv+vv5...5vvvvvvv.4.4.vv.4.4.4vv.vvv...vxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxv...5vv.................vv|vvv...vvvvv.++4.4.4++4.4.4.vv.vv....vxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxv...vvv.................1vOvv5...5vvvv.vvvvvvvvvvvvvvvvv.vvv...vxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxv....vv.................vv|vvv...vvvvv.vvvvvvvvvvvvvvvvv.vv5...vxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxv...vvv.v..v..v..v....3vvv+vv5...5vvvv...................vvv...vxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxv...5vv.............vvvvv.4vvv...vvvvvvvvvvvvvvvvvvvvvvv.vv....vxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxv..vvvv+vvvv.............v.vv5...5vvvvvvvvvvvvvvvvvvvvvv+vvvv..vxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxv..v|v.....vvvvvvvvvvvvvvvvvvv...vvvvvvvvvvvvvvvvvvvv.....v|v..vxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxv..v.v.....vvvvvvvvvvvvvvvvvvvv+vvvvvvvvvvvvvvvvvvvvv.....v.v..vxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxv..v.vv+vvvv5.............5.........5..............5vvvv+vv.v..vxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxv..v2.....|v........................................v|.....3v..vxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxv..vvvvvvvvv........................................vvvvvvvvv..vxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxv............................{.[.(.............................vxxxxxxxx");

mons_array [0] = 341; // Dispater
mons_array [1] = 31; // some kind of fiend
mons_array [2] = 126;
mons_array [3] = 89; // iron devil
mons_array [4] = 248; // metal gargoyle
mons_array [5] = 250;
mons_array [6] = 250;

return 7;


}



char asmodeus(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx[xxxxxxxxxx....xxxxxxxxxxxxxxx.xxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxx......(..........{..........xxxxxxxxxxxxxx..xxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxx....xxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxx...xxx................................xxxxxx....xxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxx.x.xxxxx.........................................xxx....xxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxx....xx............................................xx...xxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxx......x......................llllllllllllll.........x..xxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxx..xx..................lllllllllllllllllllllllll........xxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxx...xxx...............llllllllllllllllllllllllll........xx...xxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxx....xxx.............llllllllllllllllllllllllllll..............xxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxx....xx...........lllllllllllllllllllllllllllll...............xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxx..............llllllllllllllllllllllllllllll......xx.......xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxx...........lllllllllllllllllll.......llllll......xx......xxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxx.......llllllllllllllllll............llllll.............xxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxxx......lllllllll..........4.........4.lllllll..........xxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxx...xx...llllllll..........................llllllll......x.xxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx.......lllllll................................llll.......xxxxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxx.....llllll...cccccccc+c+c+c+c+c+c+c+c+c+c....lll......xxxxxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxx..lllllll..4.c.....c....................c....llll.....xxxxxxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxx...llllll.....c.....+....................c.....llll....x..xxxxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx...llllll...l..c.....c....................c....lllll........xxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxx...lllll..ll..c.....cccccccccccccccccccccc.4..llllll........xxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx...lllll..llll.c.....c...............c....c....lllllll.......xxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx...lllll..llll.c.....c...............c....c....lllllll.......xxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxx...lllll..lll.c.....+...............+....c...lllllll........xxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxxx..lllll...ll.cccccccccc............c....c...llllllll........xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxx...lllll......c|$$||$$|c............c....c...llllllll........xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx...lllll.......c$$$$$$$$cccccccccccccc....c...lllllll.........xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx...lllll.......c$$|2|$$|c............+....c...lllllll........xxxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxxx.lllllll......c|$$$$$$$c............c....c....llllllll.....xxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxx.lllllll......c$|$|$$|$c+ccccccccccccccccc....lllllll......xxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxx..llllll......cccccccc+c.............c.........llllll......x.xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxx..lllllll.....c$$$$$$+.c.............c.....4...llllll........xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxx..llllllll....c$$$$$$c.c.............c..ll....llllll.........xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxx...llllll..4..c$$2$$$c.ccccccccccccc+c.lll...lllllll........xxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxx..llllll.....c$$$$$$c..+............c.ll...lllllll..........xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxx..llllllll...ccccccccc+cccccccccccccc.....lllllll...........xxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxxx..llllllll.........cc..........cc........lllllll.......x..xxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxxx.llllllllll.......ccc.........cc......lllllllll.......xxxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxx....lllllllllll...4...cc.........cc....llllllllll.........xxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxx......lllllllllllll....cccccccc+cccc..lllllllllll.....xx....xxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxx.....llllllllllllll...cccccccc+cccc..llllllllll......xx....xxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxx.....lllllllllllllll..cc......cc...lllllllllll...........xxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxx.....llllllllllllll...ccO1....cc.4..lllllllll...........xxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxx.....lllllllllllll...cc......cc....lllllllll.......xx.xxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxx.......llllllllllll..cccccccccc...lllllllll........xxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxx.........llllllllllllll.cccccccccc.lllllllllll.......xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxx........llllllllllllll............lllllllll.........xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxx.........lllllllllllllll.......lllllllll...........xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxx..........llllllllllllll.4..lllllll..........x........xxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxx...xx.........lllllllllll..llll...................xx.xxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxx..xx................llll.ll.....................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxx.........xxx.................xxxxxx......xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxx....xxxxxxxx...xxx......xxxxxxxxxx.......xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxx.xxxxx...xxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


mons_array [0] = 342; // Asmodeus
mons_array [1] = 31; // fiend
mons_array [2] = 100;
mons_array [3] = 249; // molten gargoyle
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;

return 6;


}

char antaeus(char vgrid [81] [81], int mons_array [7])
{

// bottom of Cocytus. This needs work

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxx........................xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxxxx..........................xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxxxxxxxxxxxx................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxxxxxxxxxxxx....cccccccccccc..cccccccccccc....xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxxxxxxxxxxx....ccccccccccccc..ccccccccccccc....xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxxxxxxxxxx....cc..........................cc....xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxxxxxxxxxx....cc............................cc....xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxxxxxxxxxx....cc...wwwwwwwwwwwwwwwwwwwwwwww...cc....xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxxxxxxxxxx....cc...wwwwwwwwwwwwwwwwwwwwwwwwww...cc....xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxxxxxxx....cc...wwwwwwwwwwwwwwwwwwwwwwwwwwww...cc....xxxxxxxxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxxxxx....cc...ww..........................ww...cc....xxxxxxxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxxx....cc...ww............................ww...cc....xxxxxxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxx....cc...ww....xxxxxxxxxx.2xxxxxxxxxx....ww...cc....xxxxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxxxx....cc...ww....xxxxxxxxxxx..xxxxxxxxxxx....ww...cc....xxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxxxx....cc...ww....xx1.....................xx....ww...cc....xxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxx....cc...ww....xxO.......................xx....ww...cc....xxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxx....cc...ww....xx..........wwwwww..........xx....ww...cc....xxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx....cc....w....xx.......wwwwwwwwwwwwww.......xx....ww...cc....xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx....cc...w....xx.....wwwwwwwwwwwwwwwwwwww.....xx...ww...cc....xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx....cc..www..xx....wwwwwwwwwwwwwwwwwwwwwwww....xx..www..cc....xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx....cc..www.xx....wwwwwwwwwwwwwwwwwwwwwwwwww....xx.www..cc....xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx....cc..www.xx....wwwwwwwwwwwwwwwwwwwwwwwwww....xx.www..cc....xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx....cc..www.xx...wwwwwwwwwwwwwwwwwwwwwwwwwwww...xx.www..cc....xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx....cc..www..x...wwwwwwwwwwwwwwwwwwwwwwwwwwww...x..www..cc....xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx....cc..wwww...wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...wwww..cc....xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx....cc..wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww..cc....xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx....cc..wwww...wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...wwww..cc....xxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx....cc..www..x...wwwwwwwwwwwwwwwwwwwwwwwwwwww...x..www..cc....xxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxx....cc..www.xx...wwwwwwwwwwwwwwwwwwwwwwwwwwww...xx.www..cc....xxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxx....cc..www.xx....wwwwwwwwwwwwwwwwwwwwwwwwww....xx.www..cc....xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxx....cc..www.xx....wwwwwwwwwwwwwwwwwwwwwwwwww....xx.www..cc....xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxx....cc..www..xx....wwwwwwwwwwwwwwwwwwwwwwww....xx..www..cc....xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxx....cc...ww...xx.....wwwwwwwwwwwwwwwwwwww.....xx...ww...cc....xxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxx....cc...ww....xx.......wwwwwwwwwwwwww.......xx....ww...cc....xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxx....cc...ww....xx..........wwwwww..........xx....ww...cc....xxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxx....cc...ww....xx........................xx....ww...cc....xxxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxx....cc...ww....xx......................xx....ww...cc....xxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxxxxx....cc...ww....xxxxxxxxxxx..xxxxxxxxxxx....ww...cc....xxxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxxxxxxx....cc...ww....xxxxxxxxxx2.xxxxxxxxxx....ww...cc....xxxxxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxxxxxxx....cc...ww............................ww...cc....xxxxxxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxxxxxxx....cc...ww..........................ww...cc....xxxxxxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxxxxxxxx....cc...wwwwwwwwwwwww..wwwwwwwwwwwww...cc....xxxxxxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxxxxxxxx....cc...wwwwwwwwwwww..wwwwwwwwwwww...cc....xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxxxxxxxxx....cc...wwwwwwwwwww..wwwwwwwwwww...cc....xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxxxxxxxxxx....cc............................cc....xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxxxxxxx....cc..........................cc....xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxxxxxxx....cccccccccccccccccccccccccccc....xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxxxxx....cccccccccccccccccccccccccc....xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxxx................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxx..........{.(.[...........xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 343; // antaeus
mons_array [1] = 126; // ice fiend
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 6;


}





char ereshkigal(char vgrid [81] [81], int mons_array [7])
{

// Tartarus

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxx.................xxxx..........xxx............................xxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxx.............xxxxx..xxxx.....xxx.xxxx.........................xxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxx...........xxx.........xxxxxxx.....xx.........................xxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxx.........xxx.......................xx.........................xxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxx........xx.........................xx...........xxxxxxxx......xxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxx........xxxxxxx++xxx...............xx..........xx......xx.....xxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxx........xxxxx......xxx.......xxx++xxx.........xx........xx....xxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxx........xx...........xxx.....xxx..xxx.........x..........x....xxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxx........x..............x....xxxx..xx.........xx..........xx...xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxx.......xx..x........x..xx.xxx..x..x..........x............x...xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxx.......x................xxx..................x......7.....x...xxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxx......xx................xx...................xx..........xx...xxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxx......x....x........x....x..x.........x.......x..........x....xxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxx......xx................xx....................xx........xx....xxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx.......x................x......................xx......xx.....xxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxx.......xx..x........x..xx.......................xxxxxxxx......xxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxx........xx.............x......................................xxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx........xxx....17....xxx....x.........x.......................xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx........xxx=x......x=xxx......................................xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx........xxx=xxxxxxxx=xxx......................................xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx........xx||xxxxxxxx||xx......................................xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx.........xx||||O|||||xx.......................................xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx..........xxxxxxxxxxxx......x.........x.......................xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx...........................................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx...........................................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx...........................................xx$$$$xxx|||||xx...xxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx............................x.........x....xx$$$$xxx|||||xx...xxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxx...........................................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxx...........................................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxx...........................................xx44444xx22222xx...xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxx.......xxxxxxxxx+xxxxxxxxx.................xx44444xx22222xx...xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxx.......x3.2..........3...x..x.........x..xxxxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxx.......x.x.x.x.x.x.x.x.x.x.................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxx.......x...2.3..4..5..4..x......................=.......xxx...xxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxx.......xx.x.x.x.x.x.x.x.xx......................=.......xxx...xxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxx.......x..65..3..6.6...5.x.................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxx.......x.x.x.x.x.x.x.x.x.x..x.........x..xxxxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxx.......x...4...3.....4...x.................xx.....xx555555x...xxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxx.......xx=xxxxx.x.xxxxxxxx.................xx.....xx555555x...xxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxx.......x$$$$$$x.25.x$$$||x.................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxx.......x$x$$x$xx.x.x$x$x|x.................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxx.......x||||||x.556=$$$||x..x.........x....xx$$xx56565xx$|x...xxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxx.......xxxxxxxxxxxxxxxxxxx.................xx$$xx65656xx|7x...xxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxx...........................................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxx...........................................xxxxxxxxxxxxxxxx...xxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxx........(...........................................[.........xxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxx..............................{...............................xxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

// note that the tomb on the right isn't supposed to have any doors

mons_array [0] = 344; // Ereshkigal
mons_array [1] = 13; // n
mons_array [2] = 48; // Wraith
mons_array [3] = 63; // shadow
mons_array [4] = 25; // zombie
mons_array [5] = 107; // skeleton
mons_array [6] = 127; // shadow fiend


/*
case 13: strcat(gmon_name, "necrophage"); break;
case 15: strcat(gmon_name, "phantom"); break;
case 25: break;
case 37: strcat(gmon_name, "lich"); break;
case 38: strcat(gmon_name, "mummy"); break;
case 47: strcat(gmon_name, "vampire"); break;
case 48: strcat(gmon_name, "wraith"); break;
case 51: break;
case 60: strcat(gmon_name, "wight"); break;
case 63: strcat(gmon_name, "shadow"); break;
case 64: strcat(gmon_name, "hungry ghost"); break;
case 72: strcat(gmon_name, "flying skull"); break;
case 77: strcat(gmon_name, "freezing wraith"); break;
case 107: break;
case 108: break; // skeletons
*/

return 6;


}

char nemelex(char vgrid [81] [81], int mons_array [7])
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [0],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [1],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [2],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [3],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [4],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [5],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [6],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [7],   "x..............................xxxxxxxxx");
strcat(vgrid [8],   "x..............................xxxxxxxxx");
strcat(vgrid [9],   "x..xxxxxxxx...xxxxxxx..xxxxxxx.xxxxxxxxx");
strcat(vgrid [10],  "x..xxxxxxxxx...xxxxxxx..xxxxxx.xxxxxxxxx");
strcat(vgrid [11],  "x..xxxxxxxxxx...xxxxxxx..xxxxx.xxxxxxxxx");
strcat(vgrid [12],  "x..xxxxxxxxxxx.1.xxxxxxx..xxxx.xxxxxxxxx");
strcat(vgrid [13],  "x..xxxxxxxxxx....Oxxxxxxx..xxx.xxxxxxxxx");
strcat(vgrid [14],  "x..xxxxxxxxx.....xxxxxxxxx..xx.xxxxxxxxx");
strcat(vgrid [15],  "x..xxxxxxxx...x...xxxxxxxxx..x.xxxxxxxxx");
strcat(vgrid [16],  "x..xxxxxxx...xxx...xxxxxxxxx...xxxxxxxxx");
strcat(vgrid [17],  "x..xxxxxx...xxxxx...xxxxxxxxx..xxxxxxxxx");
strcat(vgrid [18],  "x..xxxxx...xxxxxxx...xxxxxxxxx.xxxxxxxxx");
strcat(vgrid [19],  "x..xxxx...xxxxxxxxx...xxxxxxx..xxxxxxxxx");
strcat(vgrid [20],  "x..xxx...xxxxxxxxxxx...xxxxx...xxxxxxxxx");
strcat(vgrid [21],  "x..xx.....xxxxxxxxxxx...xxx....xxxxxxxxx");
strcat(vgrid [22],  "x..x...x...xxxxxxxxxxx...x.....xxxxxxxxx");
strcat(vgrid [23],  "x.....xxx...xxxxxxxxxxx......x.xxxxxxxxx");
strcat(vgrid [24],  "x....xxxxx...xxxxxxxxxxx....xx.xxxxxxxxx");
strcat(vgrid [25],  "x...xxxxxxx...xxxxxxxxxxx..xxx.xxxxxxxxx");
strcat(vgrid [26],  "x.........................xxxx.xxxxxxxxx");
strcat(vgrid [27],  "x...x..xxxxxxx.xxxxxxx...xxxxx.xxxxxxxxx");
strcat(vgrid [28],  "x..xxx.......x.x.xxxx...xxxxxx.xxxxxxxxx");
strcat(vgrid [29],  "x.xxxxx..xxx.x.x.xxx...xxxxxxx.xxxxxxxxx");
strcat(vgrid [30],  "x.xxxxxx..xx.x.x.xx...xxxxxxxx.xxxxxxxxx");
strcat(vgrid [31],  "x.xxxxxxx..x.x.x.x...xxxxxxxxx.xxxxxxxxx");
strcat(vgrid [32],  "x.xxxxxxxx...x.x....xxxxxxxxxx.xxxxxxxxx");
strcat(vgrid [33],  "x.xxxxxxxxx..x.x...xxxxxxxxxxx.xxxxxxxxx");
strcat(vgrid [34],  "x..............................xxxxxxxxx");
strcat(vgrid [35],  "xxxxxxxxxxxxxx@xxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 251; // Nemelex
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 3;


}


char sif_muna(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxwwwwwwwwwwww.......wwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxwwwwwwwwwwwwbbbwwwwwww.......wwwwwwwxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxwwwwwwwwwwwwbbbbbbbbbbbwwwwww.........wwwwwwxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxwwwwwwwwwwwwbbbbwwwwwwwwwbbbbwwwwww.........wwwwwwxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxwwwwwwwbbbbbbbbwwwwwwwwwwwwwwwbbbwwwww...........wwwwwxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxwwwwwbbbb......bbbwwwwwwwwwwww...bbwwwww.............wwwxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxwwwbbb...........bbbwwwwww........bbwwwww.............wwxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxwwwbb...............bbwwww..........bwwwwww.............wwxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxwwbb........1O.......bbww...........bbwwww..............wwxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxwwwb...................bw.............bwww................wwxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxxwwbb...................bb.............bww.................wwxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxwwbb...................bbb............bbw.................wwxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxwwbbb...................b.b.................................wwxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxwwbwbb.................bb....................................wxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxwwbwwbb...............bb..b............bbw....................xxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxwwbbwwbbb...........bbb..bb............bwww...................xxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxwwwbwwwwb..b.....bbbb....b.............bwww...................xxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxwwbwwww...bbbbbbb.......bw...........bbwwww.................xxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxwwbbww.................bbww........wwbwwwww.................xxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxxwwwbbw................bbwwwww....wwwbbwwww..................xxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxxwwwwbb................bwwwwwwwwwwwwbbwww....................xxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxxxwwwwbbb...........bbbbbwwwwwwwwwbbbwww....................xxxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxxxwwwwwwbbbb.....bbbbwwwbbbbwwwbbbbwwww....................xxxxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxxxwwwwwwwwwbbbbbbbwwwwwwwwwbbbbbwwwww.....................xxxxxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxxxxwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww......................xxxxxxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxxxxwwwwwwwwwwwwwwwwwwwwwwwwwwwww.......................xxxxxxxxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxxxxxxwwwwwwwwwwwwwwwwwwwww........................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxxxxxxxxxxxxxxxxwwwwwww......................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx...@.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 252; // Nemelex
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 1;


}

char okawaru(char vgrid [81] [81], int mons_array [7])
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [0],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [1],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [2],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [3],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [4],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [5],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [6],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [7],   "...............................xxxxxxxxx");
strcat(vgrid [8],   ".............vvvvv.............xxxxxxxxx");
strcat(vgrid [9],   ".............v$$$v.............xxxxxxxxx");
strcat(vgrid [10],  ".............v|||v.............xxxxxxxxx");
strcat(vgrid [11],  ".............v$$$v.............xxxxxxxxx");
strcat(vgrid [12],  ".vvvvv...vvvvvvvvvvvvv...vvvvv.xxxxxxxxx");
strcat(vgrid [13],  ".v|$|vvvvv...........vvvvv$|$v.xxxxxxxxx");
strcat(vgrid [14],  ".v$|$v.....vvvvvvvvv.....v|$|v.xxxxxxxxx");
strcat(vgrid [15],  ".v|$|v.vvvvvvvvvvvvvvvvv.v$|$v.xxxxxxxxx");
strcat(vgrid [16],  ".vvvvv.vvvvvv..O..vvvvvv.vvvvv.xxxxxxxxx");
strcat(vgrid [17],  "...v...vv.....vvv.....vv...v...xxxxxxxxx");
strcat(vgrid [18],  "...v.vvvv....vv1vv....vvvv.v...xxxxxxxxx");
strcat(vgrid [19],  "...v.vv......v...v......vv.v...xxxxxxxxx");
strcat(vgrid [20],  "...v.vvvv.............vvvv.v...xxxxxxxxx");
strcat(vgrid [21],  "...v...vv..2.......2..vv...v...xxxxxxxxx");
strcat(vgrid [22],  ".vvvvv.vv..2.......2..vv.vvvvv.xxxxxxxxx");
strcat(vgrid [23],  ".v|$|v.vv.............vv.v$|$v.xxxxxxxxx");
strcat(vgrid [24],  ".v|$|v.vv...vv...vv...vv.v$|$v.xxxxxxxxx");
strcat(vgrid [25],  ".v|$|v.vv...vv+++vv...vv.v$|$v.xxxxxxxxx");
strcat(vgrid [26],  ".vvvvv.vvvvvvv...vvvvvvv.vvvvv.xxxxxxxxx");
strcat(vgrid [27],  "....v..vvvvvvv...vvvvvvv..v....xxxxxxxxx");
strcat(vgrid [28],  "....vv...................vv....xxxxxxxxx");
strcat(vgrid [29],  ".....vv.vvvvv.....vvvvv.vv.....xxxxxxxxx");
strcat(vgrid [30],  "......vvv|||v.....v$$$vvv......xxxxxxxxx");
strcat(vgrid [31],  "........v|$|vv...vv$|$v........xxxxxxxxx");
strcat(vgrid [32],  "........v|||v.....v$$$v........xxxxxxxxx");
strcat(vgrid [33],  "........vvvvv.....vvvvv........xxxxxxxxx");
strcat(vgrid [34],  "...............................xxxxxxxxx");
strcat(vgrid [35],  "...............@...............xxxxxxxxx");


// You might not want to teleport too much on this level unless you can reliably teleport away again.

mons_array [0] = 253;
mons_array [1] = 233;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 3;


}

char kikuba(char vgrid [81] [81], int mons_array [7])
{

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcpy(vgrid [36], "xxxxxxxxxxxxxxxxxxxxxxx@.xxxxxxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxx..............................x");
strcpy(vgrid [38], "xxxxxxxxx..............................x");
strcpy(vgrid [39], "xxxxxxxxx..............................x");
strcpy(vgrid [40], "xxxxxxxxx.x.x.x.x.x.x.x..x.x.x.x.x.x.x.x");
strcpy(vgrid [41], "xxxxxxxxx..............................x");
strcpy(vgrid [42], "xxxxxxxxx.x.xxxx=xxxxxxxxxxxx=xxxxxx.x.x");
strcpy(vgrid [43], "xxxxxxxxx...xx....................xx...x");
strcpy(vgrid [44], "xxxxxxxxx.x.x..xxxxx........xxxxx..x.x.x");
strcpy(vgrid [45], "xxxxxxxxx...x.xx................xx.x...x");
strcpy(vgrid [46], "xxxxxxxxx.x.x.x..xxxxx.xx.xxxxx..x.x.x.x");
strcpy(vgrid [47], "xxxxxxxxx...x.x.xx.....xx.....xx.x.x...x");
strcpy(vgrid [48], "xxxxxxxxx.x.x.x.x.2...xxxx...2.x.x.x.x.x");
strcpy(vgrid [49], "xxxxxxxxx...x...x...xxx..xxx...x...=...x");
strcpy(vgrid [50], "xxxxxxxxx.x.x..........1O..........x.x.x");
strcpy(vgrid [51], "xxxxxxxxx...=...x...xxx..xxx...x...x...x");
strcpy(vgrid [52], "xxxxxxxxx.x.x.x.x.2...xxxx...2.x.x.x.x.x");
strcpy(vgrid [53], "xxxxxxxxx...x.x.xx.....xx.....xx.x.x...x");
strcpy(vgrid [54], "xxxxxxxxx.x.x.x..xxxxx.xx.xxxxx..x.x.x.x");
strcpy(vgrid [55], "xxxxxxxxx...x.xx................xx.x...x");
strcpy(vgrid [56], "xxxxxxxxx.x.x..xxxxx........xxxxx..=.x.x");
strcpy(vgrid [57], "xxxxxxxxx...xx....................xx...x");
strcpy(vgrid [58], "xxxxxxxxx.x.xxxx=xxxx=xxxxxxxx=xxxxx.x.x");
strcpy(vgrid [59], "xxxxxxxxx..............................x");
strcpy(vgrid [60], "xxxxxxxxx.x.x.x.x.x.x.x..x.x.x.x.x.x.x.x");
strcpy(vgrid [61], "xxxxxxxxx..............................x");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 254; // kiku
mons_array [1] = 230; // gr demon
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 4;


}

char beehive(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxaaaaaaaaaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxxxaaaaaaaaaaaRaaaaaaaaaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxxxxxaaaaaaaaaaRa2aaR1RaaRa2aaaaaaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxxxxxxxaaaaaaaaaaRa2a3R3aRaRaRaaaaaaaaaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxxxxxxxxxxaaaaRaRaRaaa3aaa3aRa.a.aaaaaaaaaaaxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxxxxxaaaaaaRa.aRa2a2a2a2aRaRa.a.a3aaaaaaaaaaaaaaxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxxx4aaaaaaaaa.aaRaRaa2aa2aaRaaa.aa3a33aaaaaaaaaa.44xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxx.4aaaaaaa.222a3a.aaaRaaa.aaa.R3aa3a3aaaaaaaa.....4xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxx....aaaaaaa.aRa.a3aRaRa.a3a.a.a.a.aRa2aaaaaa....xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxx...aaaaaa3a3a.a.a.a3aRa2aRa3a.a.aRaRa.aaaaa...xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxx...aa2aRa3a3a3aRa.a3a.a.a.a.a.a.a.a3a.aaa...xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxx...aaa.a.a.a2a.aaa.aRaRa2a.a2a3a.a2aaaa.....xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxx.....a2a.a2a.aRaaaaa3a.a.aaa3a3a3a3a.a.........xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxx.4...aaRRaa.a2a.a3a3a3a.aaa.a.aRa.a.aa..4.......xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxx......a.a.aaa.a3a.a.a.a.aaa2a.a2a.a.aRaa.....4...xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxx.....aa3a2aaa.a.a.a3a3a3a3aRaaa.a2a.a2aa........xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxx...aaaa.a2aRa.a.a2aaa.a.a.a.aaa.a.aaaa.....xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxxxx..aaa.a.a.a.a.a.a.aaa2a.a3a2a.a2aaa.....xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxxxxxx.aaaa3a.a2aRa.a.aaaRa.a.aa.a.aaa....xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxxxxxxx...aaaaRa.a3a3a.a.a.aaa.aa.aa....4xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxxxxx........aa.a2a.a.aaa2aa.aa.aaa....xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxxxxx....4.....a.a2a2a.a2a.a2a.......4.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxxx.............a.a.a.a.a.a.....4....xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxx..............4..a.a.a......4...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxx.................a.a.........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxx........................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxx.....4................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxxxx.......................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxxxx.........................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxxxx...........................xxxxxxxx..xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxxxx.......4.....................xxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxxx..............xx...............xxxxxx....xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxxx............xxxxx........4......xxxx..4....xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxx.............xxx................xxxxx.....xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxx............xxx..................xxx........xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxx....4........xx....................x..........xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxx...............x.x...xxx...............xx.xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxx.........4...........xxx..................xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxx.....4.....................4......4...........4...xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxx.................................................wwwwwwwwxxxxxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxx............x...x.........xxxx.................wwwwwwwwwwwwxxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxx.........xx.............xxxxx................wwwwwwwwwwwwwwxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxx.......x..................xxx....4..........wwwwwwwwwwwwwwwxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxx.....xxx...4...........................xxxx.4wwwwwwwwwwwwwwwxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxx..xxx.............xx....(.........xxxxxxxx....wwwwwwwwwwwwwxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxx.............xxxx..................xxxx......wwwwwwwwwwxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxx....{..}..xxxxxx..]......xxx...........4.wwwwwwwwwwwwxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxx........xxx........xxxxxx....4....wwwwwwwwwwwwwwxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxxxx..[.xxx........xxx)....wwwwwwwwwwwwwwwwwwxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxxxxx.........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 42; // queen bee
mons_array [1] = 10; // killer bee
mons_array [2] = 11; // larva
mons_array [3] = 41; // plant
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;

return 6;


}

char vaults_vault(char vgrid [81] [81], int mons_array [7])
{

/* last level of the vaults. These 'x's will all be changed in dungeon.cc */

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxx..xxxxxxxxxxxxxxxxxxxxxxxxxxx....xxxxxxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxx..x.........................x....xxxxxxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxx..x.xxxxxxxxxxx..xxxxxxxxxx.x....xxxxx.................xxxxx..xxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxx..x.x*.*.*.*.*x..x........x.x....xxx..........8..........xxx..xxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxx..x.x.*.*.*.*.x..x........x.x....xxx.....................xxx..xxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxx..x.x*.*.*.*.*x..x...||...x.x....xx......9........9.......xx..xxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxx..x.x.*.*.*.*.x..x...||...x.x....xx.......................xx..xxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxx..x.x*.*.*.*.*x..x...||...x.x....xx......xxxxxxxxxxx......xx..xxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxx..x.x.*.*.*.*.x..x........x.x....xx......x.........x......xx..xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxx..x.x*.*.*.*.*+..+........x.x....xx....xxx..........xx....xx..xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxx..x.x.*.*.*.*.xxxxxxxxxxxxx.x....xx.0..x....xxxxx....x..8.xx..xxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxx..x.xxxxxxxxxxx0098.........x....xx....x...xx$$$xx...x....xx..xxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxx..x...........900xxxxxxxxxx.x....xx....x..xx$***$xx..x....xx..xxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxx..x.xxxxxxxxxxx99x........x.x....xx....x..x$$*|*$$x..x....xx..xxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx..x.x.....|...x88x.$$$$$$.x.x....xx..8.x..xx$***$xx..x....xx..xxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxx..x.x.|..|..|.x..x.$$$$$$.x.x....xx....x....x$$$xx...x..9.xx..xxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxx..x.x.........x..x.$$$$$$.x.x....xx....xxx..xxxxx..xxx....xx..xxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx..x.x.|..|..|.x..x.$$$$$$.x.x....xx......x.........x......xx..xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx..x.x.........x..x.$$$$$$.x.x....xx......xxxxxxxxxxx......xx..xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx..x.x|..|..|..x..x.$$$$$$.x.x....xxx.....................xxx..xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx..x.x.........x..+........x.x....xxx......0.........0....xxx..xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx..x.xxxxxxxxx+x..xxxxxxxxxx.xx.11....xx................xxxxx..xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx..x...........x..x...........x1111...xxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx..xxxxxxxxxxxxxxxxxxxxxxxxx..1....1..xxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx..........................xx1..(}..1..........................xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx...........................11.[..{.11.........................xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx............................1..])..1..........................xxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx.............................1....1...........................xxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxx..xxxxxxxxxxxxxxxxxxxxxxx.....1111..x.xxx.xxxxxxxxxxxxxxxxxx..xxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxx..xx.x.x.x.x.x.x.x.x.x.x.x.....11..........................x..xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxx..x.x.x.x.x.x.x.x|x.x.x.x.x................................x..xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxx..xx.x|x.x.x.x.x.x.x.x.x.x.x.....x.........................x..xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxx..x.x.x.x.x.x.x.x.x.x.x.x.x.x..........8..........0........x..xxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxx..xx.x.x.x.x.x.x.x.x.x.x.x.xx....x..9......................x..xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxx..x.x.x.x.x.x.x.x.x.x|x.x.x.x....x.........................x..xxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxx..xx.x.x.x.x|x.x.x.x.x.x.x.xx....x..............9...0......x..xxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxx..x.x.x.x.x9x.x.x.x.x.x.x.x.x...........8..................x..xxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxx..xx.x.x.x.x.x.x.x.x.x.x.x.xx....x..0......................x..xxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxx..x.x.x.x.x.x.x.x.x|x.x.x.x.x....x.........................x..xxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxx..xx.x.x.x.x.x.x.x.x.x.x.x.xx....x...................0.....x..xxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxx..x.x.x0x.x.x.x.x.x.x.x.x.x.x....x....0......8.............x..xxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxx..xx.x.x.x.x.x.x9x.x.x.x.x.xx....x.........................x..xxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxx..x.x.x.x.x.x.x.x.x.x.x.x.x.x....x.........................x..xxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxx..xx.x.x.x.x.x.x.x.x.x.x.x.xx....x.......9......9..........x..xxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxx..x.x.x.x.x.x.x.x.x.x0x.x.x.x....x.....................8...x..xxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxx..xx.x0x.x.x.x.x.x.x.x.x.x.xx....x.....................||.|x..xxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxx..x.x|x.x.x.x.x.x.x|x.x.x.x.x....x.....................|...x..xxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxx..xx.x.x.x.x.x.x9x.x.x.x.x.xx....x......8..................x..xxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxx..x.x.x.x.x.x.x.x.x.x.x.x.x.x....x..........8..8...8.....||x..xxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxx..xO.x.x.x.x.x.x.x.x.x.x|x.xx....x.....................|.||x..xxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxx..xxxxxxxxxxxxxxxxxxxxxxxxxxx....xxxxxxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 360; // vault guard
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;



return 6;


}


/*
char slime_pit(char vgrid [81] [81], int mons_array [7])
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [0],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [1],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [2],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [3],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [4],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [5],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [6],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [7],   "........8..8.8.................xxxxxxxxx");
strcat(vgrid [8],   "..8...........8....8.8..8......xxxxxxxxx");
strcat(vgrid [9],   "8....8..........8........8..8..xxxxxxxxx");
strcat(vgrid [10],  "...ccccccccccc..ccccccccccc..8.xxxxxxxxx");
strcat(vgrid [11],  "...cccccccccc....cxxxxxxxcc..8.xxxxxxxxx");
strcat(vgrid [12],  ".8.ccxxxxxxcc....cx|x|x|xcc....xxxxxxxxx");
strcat(vgrid [13],  "...ccx||||xcc.8..cxxxxxxxcc....xxxxxxxxx");
strcat(vgrid [14],  "...ccxxxxxxxx....xx|x|x|xcc.8..xxxxxxxxx");
strcat(vgrid [15],  "...ccx||||xcc....cxxxxxxxcc....xxxxxxxxx");
strcat(vgrid [16],  "..8ccxxxxxxcc..8.cx|x|x|xcc...8xxxxxxxxx");
strcat(vgrid [17],  ".8.ccx||||xcc....cxxxxxxxcc....xxxxxxxxx");
strcat(vgrid [18],  "...ccxxxxxxcc....cccccccccc....xxxxxxxxx");
strcat(vgrid [19],  "...cccccxcccc....ccccxccccc.8..xxxxxxxxx");
strcat(vgrid [20],  "..8c.............8..8.....c..8.xxxxxxxxx");
strcat(vgrid [21],  "....8..8......1................xxxxxxxxx");
strcat(vgrid [22],  ".8.......8.......8....88.......xxxxxxxxx");
strcat(vgrid [23],  "...c.......8..............c8...xxxxxxxxx");
strcat(vgrid [24],  "...cccccccccc.8..cccccccccc....xxxxxxxxx");
strcat(vgrid [25],  "...cccccccccc....cccccccccc.8..xxxxxxxxx");
strcat(vgrid [26],  ".8.cccccccccc....cccccccccc....xxxxxxxxx");
strcat(vgrid [27],  "...cccc||cccc..8.cccc||cccc....xxxxxxxxx");
strcat(vgrid [28],  "8..ccc||||ccc....ccc||||ccc..8.xxxxxxxxx");
strcat(vgrid [29],  "...ccc||||ccc....ccc||||ccc....xxxxxxxxx");
strcat(vgrid [30],  "...cccc||cccc8...cccc||cccc....xxxxxxxxx");
strcat(vgrid [31],  ".8.cccccccccc..8.cccccccccc.8..xxxxxxxxx");
strcat(vgrid [32],  "8..cccccccccc....cccccccccc....xxxxxxxxx");
strcat(vgrid [33],  "...ccccccccccc..ccccccccccc....xxxxxxxxx");
strcat(vgrid [34],  ".8.......8............8...8.8..xxxxxxxxx");
strcat(vgrid [35],  "..8.88.8....8...8...8.........8xxxxxxxxx");

mons_array [0] = 279; /* the royal jelly * /
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 3;


}
*/
char slime_pit(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx....xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..xxxx.........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx....................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxxxxxxxxx......................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxxxxxxxxxxxxxx..........................x.xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxxxxxxxxxxxxxx.............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxxxxxxxxxxxxx.................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxxxxxxxxxxxxxx..................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxxxxxxxxxxxxx....(................................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxxxxxxxxxxxxxx......................................xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxxxxxxxxx..........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxxxxxxxx..........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxxxxx............................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxxxxx............................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxxxxx.....................ccc..ccc............]......xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxxxxxxx...................cccc.ccccc...................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxxxxx...................cc|cc..cc|cc....................xxxxxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxxxxx..................cc|||cc.cc||cc..................xxxxxxxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxxxxx..................cc|||cc..cc|||cc..................xxxxxxxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxxxxx.................cc||O|cc.cc||O||cc.................xxxxxxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxxxxx.................cc||||cc..cc||||cc....................xxxxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxxxx..................cccc|c.cc.ccc|cccc...................xxxxxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxxxx..................cccccccc..cccccccc....................xxxxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxxx...................c...c...1....c...c.....................xxxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxxx.....................c...c....c...c.......................xxxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxxx..........)........cccccccc..cccccccc.....................xxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxx...................cc|ccc|cc.c|ccc|cc.....................xxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxx....................cc||||cc..cc||||cc....................xxxxxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxxx....................cc||O|cc.cc||O||cc....................xxxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxx.....................cc|||cc..cc|||cc....................xxxxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxxx.....................cc|||cc.cc||cc.....................xxxxxxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxxxx.....................cc|cc..cc|cc......................xxxxxxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxxxxx.....................cccc.ccccc......................xxxxxxxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxxxxxx.....................ccc..ccc.......................xxxxxxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxxxxx...........................................[.........xxxxxxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxxxx......................................................xxxxxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxxxx..............................................xxxxx...xxxxxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxxxx...........................................xxxxxxxx.xxxxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxxxxxx..........................................xxxxxxxxx.xxxxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxxxxxxxxx........................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxxxxxxxx.........................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxxxxxxxxx.......................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxxxxxxxxxxx......................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxxxxxxxxxx......................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxxxxxxxxxxx.....................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxxxxxxxxxxx.............................}......xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxxxxxxxxx.................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxxxxx...........{........xxx..xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 279; // royal jelly
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 6;


}

char hall_of_blades(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxccc....cccc.cccc.cccc.cccc.cccc.cccc.cccc.cccc.cccc.cccc.....cccxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxcc......cc...cc...cc...cc...cc...cc...cc...cc...cc...cc.......ccxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxc..........c..............c..............c..............c......cxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxc.........ccc............ccc............ccc............ccc.....cxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxc........ccccc..........ccccc..........ccccc..........ccccc....cxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxc.........ccc............ccc............ccc...........ccccc....cxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxc..........c..............c..............c.............ccc.....cxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxc......................................................ccc.....cxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxc.......................................................c......cxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxc.......................................................c......cxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxc......................................................ccc.....cxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxc..........c..............c..............c.............ccc.....cxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxc.........ccc............ccc............ccc...........ccccc....cxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxc........ccccc..........ccccc..........ccccc..........ccccc....cxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxc.........ccc............ccc............ccc............ccc.....cxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxc..........c..............c..............c..............c......cxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxc..............................................................cxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxc.......cc...cc...cc...cc...cc...cc...cc...cc...cc...cc.......ccxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxcc.....cccc.cccc.cccc.cccc.cccc.cccc.cccc.cccc.cccc.cccc.....cccxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxccc...ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxcccc.............................cccccccccccccccccccccccccccccccxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxcccccccccccccccccccccccccccccc.@.cccccccccccccccccccccccccccccccxxxxxxxx");

mons_array [0] = 144; // dancing weapon
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 1;


}


char hall_of_Zot(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxx..............xxxxxxxxxxxxxxxxxxxxxxxxx............xxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxx....................xxxxxxxxxxxxxxxxxxx..................xxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxx.......................xxxxxxxxxxxxxxx.....................xxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxx.........................xxxxxxxxxxxxx.......................xxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxx.........................xxx...1...xxx.......................xxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxx........................xx..1...1..xx......................xxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxx.......................x...........x.....................xxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxx......................1..1..Z..1..1....................xxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxx.......................x...........x.....................xxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxx........................xx..1...1..xx......................xxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxx.........................xxx...1...xxx.......................xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxx.........................xxxxxxxxxxxxx.......................xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxx.......................xxxxxxxxxxxxxxx.....................xxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxx....................xxxxxxxxxxxxxxxxxxx..................xxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxx................xxxxxxxxxxxxxxxxxxxxxxxxx..............xxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxxxxxx111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx111xxxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxxxxx....8...............xxxxxxxxxxxxxxxxx..................xxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxxx.................xx....xxxxxxxxxxxxx....xx...............xxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxx.........8...8.....xxx...xxxxxxxxxxx...xxx...8...8.........xxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxx....8................xxx...............xxx...........8...8...xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxx.......8.....8...8...xxxx.............xxxx...................xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxx.....................xxxx.............xxxx.......8...........xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxx.....................xxxxx.1...1...1.xxxxx............8....8.xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxx.......8....8.....8..xxxxx...........xxxxx....8..............xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxx.....................xxxxx...........xxxxx..........8........xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxxx...................xxxxx.............xxxxx..............8..xxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxxxx........8........xxxxxx.............xxxxxx....8..........xxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxxxx...............xxxxxx...............xxxxxx.............xxxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


mons_array [0] = 365; // orb guardian
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 1;


}



/*
NOTE: *Cannot* place 8,9 or 0 monsters in branch vaults which neither use the
normal mons_level function or are around level 35, or generation will crash.
*/



// For some reason this doesn't work
/*
char mollusc(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxwwwwwwxxxxxxxwwwwwwwwwwwwwwwxxwwxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxwwxxxwwxwxxwxxwxwwwwwwwwwwx.23wwwwxxwwwwwwwxxwxwxwxwxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxwwwwxxxxwwwxxxwxwwxwxwww3.2.1.x2xxwwwwxwwxwwwxxxwwwxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxwwwwxwxwwwxxxxwwwwwwwwwwwwwww3.....xxxwwwwxwwxwww...xwwxxwxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxwwwwx.wwxwxxxwwwwwwwwwxwwwwwwwww.2.wwwwwwwwwxxwwwxxw..wwwwwxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxwwxxx..xwxxxxwwxw.wwwwwwwwwwwwwwwwwwwxwwwwwwwxwwwwxwwwwwwxwwxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxwxxxwwxxwwxwwwxxxwwxwwwxwwwwwwwwwwwwwwwwwwxwwwwwwwxwxxwxxwwwwxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxwwwwxwwxwwwwxwwwwwwwxwwwwwwwwwwwww...wwxwwwwwwwwwwwwwwwwxwxwxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxwxwxwwxwxwxwwwwxwwwwwwwxwwwwxwwww....wwwwwwwwww.2.wwwxwxwxxxwxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxxxwwxwxwwwwwwwwwwwwwwwwwwww.wwwwww...x.wwwwww.....3wwwwwwwwxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxwxwwwwwwwwwwwwww......wwwwwwwwwwwwwww...wwxw.2..2.....xwxwwwxwxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxwwwwwwwwwwwww.3.wx..3wwxwwwwwwwwwwx....wwwww.....3wwwwwxwwwwwxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxwwwwwwwwwwwww3...ww3...wxwwwwwwwwwwwwwwwwwwwww3...wwwwwwwwxwwxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxwwwwwwwwwwwwwww3..2.2wwwwxwwwwwwwwwwwwwwwxww..3.wwwww.wwwwwwxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxwwxxwwwwwwwwwwwwwx..x.wwwwww..2xwxwwwwwwwwxww..wwxwwww.wwwwwwxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxwwwwwxwwwwwww.wwwwww.wwwww...xwwwwwwwwwwww.w3wwwwwwxw.w.wxwwwwxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxwxxwwwwwwwwwww..wwwwwwwww..3....wwwwwwwwwwwwwwxwxwww.wwwwwwwwxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxxwxwwwwwwwww.3.xwwwwwwwww3.2..wwwwwwwwwwwwwwwwwwww2wwwwwxxwxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxwxwwxwwwwxwww..x..wwwwwwxxw...2wxwwwxwwwwwwwww.w..wwwwwwwwwxwxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxwxxwwxwxwwwwww2.3.wwwxxwwwwwww.wwwwwwwwwwww.2..w.wxwwxwwxwxxxwxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxwxwwxwwxwwwwwww.w.w..xwwwwwww..w..wwwwwwwxwww3..3.wwwwwwwxxwwxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxxwwwwwwwxxxxwwwwwwwxwwwwxwwwwwwwwwwwwwwxxwwwwwwwwwxwwxwxxxwxwxxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxxwxxwxwxxwwxwwwwxwwww.xwwwwwwwwwwwwwwxw.wwwwwwwwxxxww.xwwwxwwwxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxxxwwwwxxxxwxwxxwwwwwwww.x.wwwwwwxw.w..w.wwwxwwwwwxxxw.wxxxxwxxxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxxxxwxwwwwxwwwxwxwwwwwwww.wwwwxwww2wwwwwwwwwwwwwwwwxwww.x.wwwxwxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxxxxxxwxwxxxwxxxwxwwwwwwwwwwwwwww3wwwwwwwwwwwwwwxxxxxwwwwwxxwwxxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxxxxxxxxxwwxxxxxwwwxwwwwwwwwwww.32wwwwwxxxwwwwwwwwxxxwxxxxwwwxxxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxxxxxxxxxxxxxxwwxxxxwwwwwwwwww232wwwwwwwwwwwwwwwxxxwwxwwwxxxwxxxxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxwwxwww..@..wwwxxwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 255; // Mollusc Lord
mons_array [1] = 242; // giant slug
mons_array [2] = 243; // giant snail
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;

return 1;


}
*/


/*
char vault_1(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx..............................................................xxxxxxxxx");


return 1;


}

*/

/*
char vault_2(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxx...............................");
strcpy(vgrid [8],  "xxxxxxxxx...............................");
strcpy(vgrid [9],  "xxxxxxxxx...............................");
strcpy(vgrid [10], "xxxxxxxxx...............................");
strcpy(vgrid [11], "xxxxxxxxx...............................");
strcpy(vgrid [12], "xxxxxxxxx...............................");
strcpy(vgrid [13], "xxxxxxxxx...............................");
strcpy(vgrid [14], "xxxxxxxxx...............................");
strcpy(vgrid [15], "xxxxxxxxx...............................");
strcpy(vgrid [16], "xxxxxxxxx...............................");
strcpy(vgrid [17], "xxxxxxxxx...............................");
strcpy(vgrid [18], "xxxxxxxxx...............................");
strcpy(vgrid [19], "xxxxxxxxx...............................");
strcpy(vgrid [20], "xxxxxxxxx...............................");
strcpy(vgrid [21], "xxxxxxxxx...............................");
strcpy(vgrid [22], "xxxxxxxxx...............................");
strcpy(vgrid [23], "xxxxxxxxx...............................");
strcpy(vgrid [24], "xxxxxxxxx...............................");
strcpy(vgrid [25], "xxxxxxxxx...............................");
strcpy(vgrid [26], "xxxxxxxxx...............................");
strcpy(vgrid [27], "xxxxxxxxx...............................");
strcpy(vgrid [28], "xxxxxxxxx...............................");
strcpy(vgrid [29], "xxxxxxxxx...............................");
strcpy(vgrid [30], "xxxxxxxxx...............................");
strcpy(vgrid [31], "xxxxxxxxx...............................");
strcpy(vgrid [32], "xxxxxxxxx...............................");
strcpy(vgrid [33], "xxxxxxxxx...............................");
strcpy(vgrid [34], "xxxxxxxxx...............................");
strcpy(vgrid [35], "xxxxxxxxx...............................");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 2;


}
*/


/*
char vault_3(char vgrid [81] [81], int mons_array [7])
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [0],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [1],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [2],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [3],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [4],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [5],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [6],   "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [7],   "...............................xxxxxxxxx");
strcat(vgrid [8],   "...............................xxxxxxxxx");
strcat(vgrid [9],   "...............................xxxxxxxxx");
strcat(vgrid [10],  "...............................xxxxxxxxx");
strcat(vgrid [11],  "...............................xxxxxxxxx");
strcat(vgrid [12],  "...............................xxxxxxxxx");
strcat(vgrid [13],  "...............................xxxxxxxxx");
strcat(vgrid [14],  "...............................xxxxxxxxx");
strcat(vgrid [15],  "...............................xxxxxxxxx");
strcat(vgrid [16],  "...............................xxxxxxxxx");
strcat(vgrid [17],  "...............................xxxxxxxxx");
strcat(vgrid [18],  "...............................xxxxxxxxx");
strcat(vgrid [19],  "...............................xxxxxxxxx");
strcat(vgrid [20],  "...............................xxxxxxxxx");
strcat(vgrid [21],  "...............................xxxxxxxxx");
strcat(vgrid [22],  "...............................xxxxxxxxx");
strcat(vgrid [23],  "...............................xxxxxxxxx");
strcat(vgrid [24],  "...............................xxxxxxxxx");
strcat(vgrid [25],  "...............................xxxxxxxxx");
strcat(vgrid [26],  "...............................xxxxxxxxx");
strcat(vgrid [27],  "...............................xxxxxxxxx");
strcat(vgrid [28],  "...............................xxxxxxxxx");
strcat(vgrid [29],  "...............................xxxxxxxxx");
strcat(vgrid [30],  "...............................xxxxxxxxx");
strcat(vgrid [31],  "...............................xxxxxxxxx");
strcat(vgrid [32],  "...............................xxxxxxxxx");
strcat(vgrid [33],  "...............................xxxxxxxxx");
strcat(vgrid [34],  "...............................xxxxxxxxx");
strcat(vgrid [35],  "...............................xxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 3;


}
*/

/*
char vault_4(char vgrid [81] [81], int mons_array [7])
{

int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcpy(vgrid [36], "xxxxxxxxx................@..............");
strcpy(vgrid [37], "xxxxxxxxx...............................");
strcpy(vgrid [38], "xxxxxxxxx...............................");
strcpy(vgrid [39], "xxxxxxxxx...............................");
strcpy(vgrid [40], "xxxxxxxxx...............................");
strcpy(vgrid [41], "xxxxxxxxx...............................");
strcpy(vgrid [42], "xxxxxxxxx...............................");
strcpy(vgrid [43], "xxxxxxxxx...............................");
strcpy(vgrid [44], "xxxxxxxxx...............................");
strcpy(vgrid [45], "xxxxxxxxx...............................");
strcpy(vgrid [46], "xxxxxxxxx...............................");
strcpy(vgrid [47], "xxxxxxxxx...............................");
strcpy(vgrid [48], "xxxxxxxxx...............................");
strcpy(vgrid [49], "xxxxxxxxx...............................");
strcpy(vgrid [50], "xxxxxxxxx...............................");
strcpy(vgrid [51], "xxxxxxxxx...............................");
strcpy(vgrid [52], "xxxxxxxxx...............................");
strcpy(vgrid [53], "xxxxxxxxx...............................");
strcpy(vgrid [54], "xxxxxxxxx...............................");
strcpy(vgrid [55], "xxxxxxxxx...............................");
strcpy(vgrid [56], "xxxxxxxxx...............................");
strcpy(vgrid [57], "xxxxxxxxx...............................");
strcpy(vgrid [58], "xxxxxxxxx...............................");
strcpy(vgrid [59], "xxxxxxxxx...............................");
strcpy(vgrid [60], "xxxxxxxxx...............................");
strcpy(vgrid [61], "xxxxxxxxx...............................");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 4;


}

*/
/*

char vault_5(char vgrid [81] [81], int mons_array [7])
{
int i;

for (i = 0; i < 81; i ++)
{
 strcpy(vgrid [i],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}

strcat(vgrid [36], "...........@...................xxxxxxxxx");
strcat(vgrid [37], "...............................xxxxxxxxx");
strcat(vgrid [38], "...............................xxxxxxxxx");
strcat(vgrid [39], "...............................xxxxxxxxx");
strcat(vgrid [40], "...............................xxxxxxxxx");
strcat(vgrid [41], "...............................xxxxxxxxx");
strcat(vgrid [42], "...............................xxxxxxxxx");
strcat(vgrid [43], "...............................xxxxxxxxx");
strcat(vgrid [44], "...............................xxxxxxxxx");
strcat(vgrid [45], "...............................xxxxxxxxx");
strcat(vgrid [46], "...............................xxxxxxxxx");
strcat(vgrid [47], "...............................xxxxxxxxx");
strcat(vgrid [48], "...............................xxxxxxxxx");
strcat(vgrid [49], "...............................xxxxxxxxx");
strcat(vgrid [50], "...............................xxxxxxxxx");
strcat(vgrid [51], "...............................xxxxxxxxx");
strcat(vgrid [52], "...............................xxxxxxxxx");
strcat(vgrid [53], "...............................xxxxxxxxx");
strcat(vgrid [54], "...............................xxxxxxxxx");
strcat(vgrid [55], "...............................xxxxxxxxx");
strcat(vgrid [56], "...............................xxxxxxxxx");
strcat(vgrid [57], "...............................xxxxxxxxx");
strcat(vgrid [58], "...............................xxxxxxxxx");
strcat(vgrid [59], "...............................xxxxxxxxx");
strcat(vgrid [60], "...............................xxxxxxxxx");
strcat(vgrid [61], "...............................xxxxxxxxx");
strcat(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcat(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 250;
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 5;


}


*/


/*
char vault_1(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


return 6;


}

*/


/*
char vestibule_map(char vgrid [81] [81], int mons_array [7])
{

// this is the vestibule

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxx........................xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxxxx..........................xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxxxxxxxxxxxx................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxxxxxxxxxxxx..................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxxxxxxxxxxx....................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxxxxxxxxxx......................................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxxxxxxxxxx........................................xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxxxxxxxxxx..........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxxxxxxxxxx............................................xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxxxxxxx..............................................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxxxxx................................................xxxxxxxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxxx..................................................xxxxxxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxx....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxxxx......................................................xxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxxxx........................................................xxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxx..........................................................xxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxx............................................................xxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxx..............................................................xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxx............................................................xxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxx..........................................................xxxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxx........................................................xxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxxxxx......................................................xxxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxxxxxxx....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxxxxxxx..................................................xxxxxxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxxxxxxx................................................xxxxxxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxxxxxxxx..............................................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxxxxxxxx............................................xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxxxxxxxxx..........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxxxxxxxxxx........................................xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxxxxxxx......................................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxxxxxxx....................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxxxxx..................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxxx................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxx..........................xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxx........................xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 340; // Geryon
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 6;


}

*/

/*

char vestibule_map(char vgrid [81] [81], int mons_array [7])
{

// this is the vestibule

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx...........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxx.......................xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxxxxxxx...........................xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxxxxxxxxxxxxxx...............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxxxxxxxxxxxxx.................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxxxxxxxxxxxxx...................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxxxxxxxxxxxx.....................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxxxxxxxxxxxx.......................................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxxxxxxxxxxxx.........................................xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxxxxxxxxxx...........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxxxxxxx.............................................xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxxxxx...............................................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxxx.................................................xxxxxxxxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxx...................................................xxxxxxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxxx...........................................................xxxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxxx...........................................................xxxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxx...........................................................xxxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxx.............................................................xxxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxx.............................................................xxxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx..............................{..............................xxxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx.............................................................xxxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxx.............................................................xxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxx...........................................................xxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxx...........................................................xxxxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxx...........................................................xxxxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxx.........................................................xxxxxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxxx.......................................................xxxxxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxxxxx.....................................................xxxxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxxxxxxx...................................................xxxxxxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxxxxxxx.................................................xxxxxxxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxxxxxxx...............................................xxxxxxxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxxxxxxxx.............................................xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxxxxxxxx...........................................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxxxxxxxxx.........................................xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxxxxxxxxxxxxx.......................................xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxxxxxxxxxxxxx.....................................xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxxxxxxxxxxxxxx...................................xxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxxxxxxxxxxxxxx.................................xxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxxxxxxxxxxxxxxx...............................xxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxxxxxxxxxxxxxxx...........................xxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxxxxxxxxxxxxx.......................xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx...........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

mons_array [0] = 340; // Geryon
mons_array [1] = 250;
mons_array [2] = 250;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;
// remember to add one to the array (is 1-7, not 0-6)

return 6;


}


*/

/*
char vault_1(char vgrid [81] [81], int mons_array [7])
{

strcpy(vgrid [0],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [1],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [2],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [3],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [4],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [5],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [6],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [7],  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxx....xxxxxxxxxxxxxxx.xxxxxxxxxxxx");
strcpy(vgrid [8],  "xxxxxxxxxxxxxxxxxxxxxxxxx............................xxxxxxxxxxxxxx..xxxxxxxxxxx");
strcpy(vgrid [9],  "xxxxxxxxxxxxxxxxxxxxxxxxxx..............................xxxxxxxxxx....xxxxxxxxxx");
strcpy(vgrid [10], "xxxxxxxxxxxxxxxxxxxxx...xxx................................xxxxxx....xxxxxxxxxxx");
strcpy(vgrid [11], "xxxxxxxxxxxx.x.xxxxx.........................................xxx....xxxxxxxxxxxx");
strcpy(vgrid [12], "xxxxxxxxxxxx....xx............................................xx...xxxxxxxxxxxxx");
strcpy(vgrid [13], "xxxxxxxxxxx......x......................llllllllllllll.........x..xxxxxxxxxxxxxx");
strcpy(vgrid [14], "xxxxxxxxxxx..xx..................lllllllllllllllllllllllll........xxxxxxxxxxxxxx");
strcpy(vgrid [15], "xxxxxxxxxx...xxx...............llllllllllllllllllllllllll........xx...xxxxxxxxxx");
strcpy(vgrid [16], "xxxxxxxxx....xxx.............llllllllllllllllllllllllllll..............xxxxxxxxx");
strcpy(vgrid [17], "xxxxxxxxxx....xx...........lllllllllllllllllllllllllllll...............xxxxxxxxx");
strcpy(vgrid [18], "xxxxxxxxxxxx..............llllllllllllllllllllllllllllll......xx.......xxxxxxxxx");
strcpy(vgrid [19], "xxxxxxxxxxxxx...........llllllllllllllllllllllllllllllll......xx......xxxxxxxxxx");
strcpy(vgrid [20], "xxxxxxxxxxxxxx.......llllllllllllllllllllllllllllllllllll.............xxxxxxxxxx");
strcpy(vgrid [21], "xxxxxxxxxxxxxxx......llllllllllllllllllllllllllllllllllllll..........xxxxxxxxxxx");
strcpy(vgrid [22], "xxxxxxxxxx...xx...llllllllllllllllllllllllllllllllllllllllll......x.xxxxxxxxxxxx");
strcpy(vgrid [23], "xxxxxxxxx.......lllllllllllllllllllllllllllllllllllllllllll.......xxxxxxxxxxxxxx");
strcpy(vgrid [24], "xxxxxxxxxx.....llllllllllllllllllllllllllllllllllllllllllll......xxxxxxxxxxxxxxx");
strcpy(vgrid [25], "xxxxxxxxxxx..lllllllllllllllllllllllllllllllllllllllllllllll.....xxxxxxxxxxxxxxx");
strcpy(vgrid [26], "xxxxxxxxxx...llllllllllllllllllllllllllllllllllllllllllllllll....x..xxxxxxxxxxxx");
strcpy(vgrid [27], "xxxxxxxxx...lllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxxxx");
strcpy(vgrid [28], "xxxxxxxxxx...lllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxxx");
strcpy(vgrid [29], "xxxxxxxxx...lllllllllllllllllllllllllllllllllllllllllllllllllll.......xxxxxxxxxx");
strcpy(vgrid [30], "xxxxxxxxx...lllllllllllllllllllllllllllllllllllllllllllllllllll.......xxxxxxxxxx");
strcpy(vgrid [31], "xxxxxxxxxx...lllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxxx");
strcpy(vgrid [32], "xxxxxxxxxxx..llllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxx");
strcpy(vgrid [33], "xxxxxxxxxx...llllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxx");
strcpy(vgrid [34], "xxxxxxxxx...llllllllllllllllllllllllllllllllllllllllllllllllll.........xxxxxxxxx");
strcpy(vgrid [35], "xxxxxxxxx...llllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxxx");
strcpy(vgrid [36], "xxxxxxxxxx.lllllllllllllllllllllllllllllllllllllllllllllllllllll.....xxxxxxxxxxx");
strcpy(vgrid [37], "xxxxxxxxxx.llllllllllllllllllllllllllllllllllllllllllllllllllll......xxxxxxxxxxx");
strcpy(vgrid [38], "xxxxxxxxxx..lllllllllllllllllllllllllllllllllllllllllllllllllll......x.xxxxxxxxx");
strcpy(vgrid [39], "xxxxxxxxxx..lllllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxx");
strcpy(vgrid [40], "xxxxxxxxxx..llllllllllllllllllllllllllllllllllllllllllllllllll.........xxxxxxxxx");
strcpy(vgrid [41], "xxxxxxxxxx...lllllllllllllllllllllllllllllllllllllllllllllllll........xxxxxxxxxx");
strcpy(vgrid [42], "xxxxxxxxxxx..llllllllllllllllllllllllllllllllllllllllllllllll..........xxxxxxxxx");
strcpy(vgrid [43], "xxxxxxxxxxx..lllllllllllllllllllllllllllllllllllllllllllllll...........xxxxxxxxx");
strcpy(vgrid [44], "xxxxxxxxxxxx..llllllllllllllllllllllllllllllllllllllllllllll.......x..xxxxxxxxxx");
strcpy(vgrid [45], "xxxxxxxxxxxxx.llllllllllllllllllllllllllllllllllllllllllllll.......xxxxxxxxxxxxx");
strcpy(vgrid [46], "xxxxxxxxxx....lllllllllllllllllllllllllllllllllllllllllllll.........xxxxxxxxxxxx");
strcpy(vgrid [47], "xxxxxxxxx......lllllllllllllllllllllllllllllllllllllllllll.....xx....xxxxxxxxxxx");
strcpy(vgrid [48], "xxxxxxxxxx.....llllllllllllllllllllllllllllllllllllllllll......xx....xxxxxxxxxxx");
strcpy(vgrid [49], "xxxxxxxxxxx.....lllllllllllllllllllllllllllllllllllllllll...........xxxxxxxxxxxx");
strcpy(vgrid [50], "xxxxxxxxxxx.....llllllllllllllllllllllllllllllllllllllll...........xxxxxxxxxxxxx");
strcpy(vgrid [51], "xxxxxxxxxxxx.....lllllllllllllllllllllllllllllllllllllll.......xx.xxxxxxxxxxxxxx");
strcpy(vgrid [52], "xxxxxxxxxxxx.......llllllllllllllllllllllllllllllllllll........xxxxxxxxxxxxxxxxx");
strcpy(vgrid [53], "xxxxxxxxx.........lllllllllllllllllllllllllllllllllllll.......xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [54], "xxxxxxxxxx........lllllllllllllllllllllllllllllllllll.........xxxxxxxxxxxxxxxxxx");
strcpy(vgrid [55], "xxxxxxxxxx.........lllllllllllllllllllllllllllllll...........xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [56], "xxxxxxxxxxx..........lllllllllllllllllllllllll..........x........xxxxxxxxxxxxxxx");
strcpy(vgrid [57], "xxxxxxxxxxx...xx.........lllllllllllllllll...................xx.xxxxxxxxxxxxxxxx");
strcpy(vgrid [58], "xxxxxxxxxxxxx..xx................lllllll.....................xxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [59], "xxxxxxxxxxxxxxxxx.........xxx.................xxxxxx......xxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [60], "xxxxxxxxxxxxxxxxxxx....xxxxxxxx...xxx......xxxxxxxxxx.......xxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [61], "xxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxx.xxxxx...xxxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [62], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [63], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [64], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [65], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [66], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [67], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [68], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
strcpy(vgrid [69], "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


mons_array [0] = 341; // Dispater
mons_array [1] = 31; // some kind of fiend
mons_array [2] = 126;
mons_array [3] = 250;
mons_array [4] = 250;
mons_array [5] = 250;
mons_array [6] = 250;

return 6;


}

*/



// farm & country
