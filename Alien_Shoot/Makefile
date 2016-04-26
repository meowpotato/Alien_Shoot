CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: Alien_Shoot

Alien_Shoot: Alien_Shoot.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) Alien_Shoot.cpp ppm.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o Alien_Shoot

clean:
	rm -f Alien_Shoot
	rm -f *.o

