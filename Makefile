//liaison des fichiers.o ensemble
lab : traitementfichiers.o validitelab.o main.o
    gcc -o lab lab.o main.o//ca ????
    gcc -o lab validitelab.o traitementfichiers.o main.o//ou ca ?????
//main + .h
main.o : main.c labyrinthe.h
    gcc -c -O3 main.c
//chaque fichiers.c +fichier.h sauf le main
validitelab.o : validitelab.c labyrinthe.h
    gcc -c -O3 validitelab.c

traitementfichiers.o : traitementfichiers.c labyrinthe.labyrinthe
    gcc -c -O3 traitementfichiers.c
 
//nettoie les .o    
clean: 
	rm *.o
