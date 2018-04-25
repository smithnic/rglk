CCFLAGS = -std=c++11
CLEAN = rm -f rglk.exe
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	#Linux
	CCFLAGS += -lncurses
	CLEAN = rm -f rglk
endif	

sources = rglk.hpp rglk.cpp Area.hpp Area.cpp P1.hpp P1.cpp util.hpp util.cpp Areas.hpp Enemy.hpp Enemy.cpp Item.hpp Item.cpp

rglk: $(sources)
	g++ $(sources) $(CCFLAGS) -o rglk

clean:
	$(CLEAN)

.PHONY: clean
