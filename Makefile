lab : fichiers.o validite.o  affichage.o main.o
	gcc -o lab validite.o fichiers.o affichage.o main.o

main.o : main.c labyrinthe.h
	gcc -c -O3 main.c 

validite.o : validite.c labyrinthe.h
	gcc -c -O3 validite.c

fichiers.o : fichiers.c labyrinthe.h
	gcc -c -O3 fichiers.c
 
affichage.o : affichage.c labyrinthe.h
	gcc -c -O3 affichage.c
  
clean: 
	rm *.o
