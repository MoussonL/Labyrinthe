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
  
clean: 
rm *.o
