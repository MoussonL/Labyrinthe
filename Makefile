lab : fichiers.o validite.o  aff.o main.o
	gcc -o lab validite.o fichiers.o aff.o main.o

main.o : main.c labyrinthe.h
	gcc -c -O3 main.c 

validite.o : validite.c labyrinthe.h
	gcc -c -O3 validite.c

fichiers.o : fichiers.c labyrinthe.h
	gcc -c -O3 fichiers.c
 
aff.o : aff.c labyrinthe.h
	gcc -c -O3 aff.c
  
clean: 
	rm *.o
