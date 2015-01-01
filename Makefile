COMPILER=g++
RUNSTRING=./${TARGET}

OBJECTS=main.o

LIBS=-pthread -lncurses
CXXFLAGS= -g -std=c++11

TARGET=matedit

all: .depend ${TARGET}

#Calculating dependincies
.depend: $(wildcard ./*.cpp ./*.h) Makefile
	$(CXX) $(FLAGS) -MM *.cpp > ./.dependtmp
	cat ./.dependtmp | sed 's/h$$/h \n\t \$(CXX) $$< -c $(FLAGS) -o $$@/' > ./.depend
	rm ./.dependtmp

${TARGET}: ${OBJECTS}
	${COMPILER} ${FLAGS} -o ${TARGET} ${OBJECTS} ${LIBS}

include .depend

.depend: $(MOCSRC)

#För att kunna köra filen direkt
run: ${TARGET}
	${RUNSTRING}

clean:
	rm $(OBJECTS)
	rm .depend

rebuild: clean ${TARGET}
