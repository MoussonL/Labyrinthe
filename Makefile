lab : fichiers.o validite.o  Affichage.o main.o
	gcc -o lab validite.o fichiers.o Affichage.o main.o

main.o : main.c labyrinthe.h
	gcc -c -O3 main.c 

validite.o : validite.c labyrinthe.h
	gcc -c -O3 validite.c

fichiers.o : fichiers.c labyrinthe.h
	gcc -c -O3 fichiers.c
 
Affichage.o : Affichage.c labyrinthe.h
	gcc -c -O3 Affichage.c

Mazerand1.o : Mazerand1.c labyrinthe.h
	gcc -c -O3 Mazerand1.c
	
Waysearch.o : Waysearch.c labyrinthe.h
	gcc -c -O3 Waysearch.c
clean: 
	rm *.o
