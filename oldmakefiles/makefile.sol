# Make file for Dungeon Crawl (linux port only for now)

C_COMP = g++
C_ARGS = -Wall -O -DSOLARIS
L_ARGS = -s
MCHMOD = 2755
GROUP = games
INSTALLDIR = /opt/crawl/bin
LIB = -lcurses

OBJECTS = ability.o acr.o bang.o beam.o chardump.o command.o debug.o \
	    decks.o describe.o direct.o dungeon.o effects.o fight.o \
	    files.o food.o invent.o it_use2.o it_use3.o item_use.o \
	    itemname.o items.o levels.o liblinux.o llist.o macro.o \
	    maps.o message.o misc.o monplace.o mons_lev.o monstuff.o \
	    mstruct.o mstuff2.o mutation.o newgame.o ouch.o output.o \
	    player.o abyss.o randart.o religion.o rumours.o shopping.o \
	    skills.o skills2.o spell.o spells.o spells0.o spells1.o \
	    spells2.o spells3.o stuff.o transfor.o view.o initfile.o

#INCLUDE = -I/opt/include/

all:            crawl

install:        crawl
		rm -f ${INSTALLDIR}/crawl.old
		mv -f ${INSTALLDIR}/crawl ${INSTALLDIR}/crawl.old
		cp crawl ${INSTALLDIR}/crawl
		chgrp ${GROUP} ${INSTALLDIR}/crawl
		chmod ${MCHMOD} ${INSTALLDIR}/crawl

clean:
		rm -f *.o

distclean:
		rm -f *.o bones.* morgue.txt scores crawl

crawl:	${OBJECTS}
		${C_COMP} ${L_ARGS} -o $@ ${OBJECTS} ${LIB}
		chmod ${MCHMOD} $@

.cc.o:
		${C_COMP} ${C_ARGS} -c $< ${INCLUDE}