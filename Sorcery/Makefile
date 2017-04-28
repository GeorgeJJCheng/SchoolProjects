CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g -Wno-sign-compare
EXEC = sorcery
OBJECTS = main.o player.o game.o window.o ascii_graphics.o card.o minion.o spell.o enchantment.o ritual.o cardlist.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
