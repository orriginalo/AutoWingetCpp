GXX = g++
GXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Oz
SRC = src/main.cpp
DST = pkginstaller

ifeq ($(OS),Windows_NT)
	STRIP = strip $(DST).exe
else 
	STRIP = strip $(DST)
endif
	

all: $(SRC)
	$(GXX) $(GXXFLAGS) -o pkginstaller $(SRC)
	$(STRIP)