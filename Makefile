PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall

all:
		$(CC) $(CFLAGS) -I$(PREFIX)/include slowm.c -L$(PREFIX)/lib -lX11 -o slowm

clean:
		rm -f slowm

install:
		rm ~/Scripts/slowm
		cp slowm ~/Scripts/slowm
