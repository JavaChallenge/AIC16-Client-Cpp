CXX = g++ --std=c++0x
FLAGS = -Wall -L/usr/local/lib -Wl,-rpath=/usr/local/lib

TARGET = flows.out

BASE_SOURCES = $(wildcard */*.cpp) $(wildcard *.cpp)
BASE_OBJ = ${BASE_SOURCES:.cpp=.o}
BASE_OBJECTS = ${BASE_OBJ:.c=.o}

OBJECTS = ${BASE_OBJECTS} ${JSON_OBJECTS}

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${FLAGS} -o ${TARGET} ${OBJECTS} ${LIBS}

clean:
	tmpfolder=`echo /tmp/CF-clean-$$$$.removed` && mkdir -p $$tmpfolder && touch a && mv -t $$tmpfolder/ a `for a in ${OBJECTS} ${TARGET} *~ base/*~ user/*~ ; do if [ -e $$a ]; then echo $$a; fi; done`

.cpp.o:
	${CXX} ${FLAGS} -c $< -o $@
.c.o:
	${CXX} ${FLAGS} -c $< -o $@

.PHONY: all clean submit
