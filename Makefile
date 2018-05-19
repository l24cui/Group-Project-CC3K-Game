CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -MMD
OBJECTS=main.o floor.o chamber.o object.o player.o enemy.o character.o item.o treasure.o potion.o rh.o ba.o bd.o ph.o wa.o wd.o shade.o drow.o troll.o goblin.o vampire.o human.o dwarf.o orc.o elf.o merchant.o dragon.o halfling.o 
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
clean:
	rm *.o main
.PHONY: clean
