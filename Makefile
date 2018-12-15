lab : Validity.o File.o Display.o MazeRand1.o MazeRand2.o MazePile.o waysearch.o main.o
	gcc -o lab Validity.o File.o Display.o MazeRand1.o MazeRand2.o MazePile.o waysearch.o main.o

main.o : main.c labyrinthe.h
	gcc -c main.c 
 
Display.o : Display.c labyrinthe.h
	gcc -c Display.c

MazeRand1.o : MazeRand1.c labyrinthe.h
	gcc -c MazeRand1.c
	
MazeRand2.o : MazeRand2.c labyrinthe.h
	gcc -c MazeRand2.c	

MazePile.o : MazePile.c labyrinthe.h
	gcc -c MazePile.c	
	
waysearch.o : waysearch.c labyrinthe.h
	gcc -c waysearch.c
	
Validity.o : Validite.c labyrinthe.h
	gcc -c Validity.c

File.o : File.c labyrinthe.h
	gcc -c File.c

clean: 
	rm *.o
