CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -l pthread -lm -lalut#-lXrandr

all: Alien_Shoot

Alien_Shoot: Alien_Shoot.cpp jeffC.cpp lakhdeepS.cpp sabrinaS.cpp pedroH.cpp ppm.cpp log.cpp
	g++ $(CFLAGS) Alien_Shoot.cpp jeffC.cpp lakhdeepS.cpp sabrinaS.cpp pedroH.cpp ppm.cpp log.cpp /usr/lib/x86_64-linux-gnu/libopenal.so libggfonts.a -Wall -Wextra $(LFLAGS) -o Alien_Shoot

clean:
	rm -f Alien_Shoot
	rm -f *.o

