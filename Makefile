LDLIBS += -ltins

all: beacon-flood

beacon-flood.cpp: beacon-flood.cpp

clean:
	rm -f beacon-flood *.o
