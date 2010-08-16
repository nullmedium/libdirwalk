OBJECTS=main.o

CXXFLAGS=-I/usr/include -I/opt/local/include
LDFLAGS=-L/opt/local/lib -lboost_filesystem-mt-d -lboost_system-mt-d

all: ${OBJECTS}
	g++ -o dirwalk ${OBJECTS} ${CXXFLAGS} ${LDFLAGS}