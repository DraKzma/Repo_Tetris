tetris : menu.o scores.o saves.o jeu.o
	gcc -o tetris menu.o scores.o saves.o jeu.o -W -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV` -pedantic -std=c89 -O2
menu : menu.c scores.h saves.h
	gcc -o menu.o -W -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` menu.c `pkg-config --libs-only-l MLV` -pedantic -std=c89 -O2 -c menu.c
scores : scores.c scores.h
	gc -o scores.o c -W -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` scores.c `pkg-config --libs-only-l MLV` -pedantic -std=c89 -O2 -c scores.c
saves : saves.c saves.h
	gc -o saves.o c -W -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` saves.c `pkg-config --libs-only-l MLV` -pedantic -std=c89 -O2 -c saves.c
jeu : jeu.c jeu.h
	gcc -o jeu.o -W -Wall -pedantic -std=c89 -O2 -c jeu.c
clean :
	rm -rf *.o *~ tetris