lab : validite.o fichiers.o Affichage.o MazeRand1.o waysearch.o main.o
	gcc -o lab validite.o fichiers.o Affichage.o MazeRand1.o waysearch.o main.o

main.o : main.c labyrinthe.h
	gcc -c -O3 main.c 
 
Affichage.o : Affichage.c labyrinthe.h
	gcc -c -O3 Affichage.c

MazeRand1.o : MazeRand1.c labyrinthe.h
	gcc -c -O3 MazeRand1.c
	
MazeRand2.o : MazeRand2.c labyrinthe.h
	gcc -c -O3 MazeRand2.c	
	
waysearch.o : waysearch.c labyrinthe.h
	gcc -c -O3 waysearch.c
	
validite.o : validite.c labyrinthe.h
	gcc -c -O3 validite.c

fichiers.o : fichiers.c labyrinthe.h
	gcc -c -O3 fichiers.c

clean: 
	rm *.o
