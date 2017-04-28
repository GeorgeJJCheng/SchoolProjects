CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
EXEC = quadris
OBJECTS = main.o posn.o singleblock.o quadblock.o board.o game.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
