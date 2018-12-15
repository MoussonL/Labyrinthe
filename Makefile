lab : Validity.o File.o Display.o MazeRand1.o MazeRand2.o MazePile.o waysearch.o main.o
	gcc -o lab Validity.o File.o Display.o MazeRand1.o MazeRand2.o MazePile.o waysearch.o main.o

main.o : main.c Maze.h
	gcc -c main.c 
 
Display.o : Display.c Maze.h
	gcc -c Display.c

MazeRand1.o : MazeRand1.c Maze.h
	gcc -c MazeRand1.c
	
MazeRand2.o : MazeRand2.c Maze.h
	gcc -c MazeRand2.c	

MazePile.o : MazePile.c Maze.h
	gcc -c MazePile.c	
	
waysearch.o : waysearch.c Maze.h
	gcc -c waysearch.c
	
Validity.o : Validite.c Maze.h
	gcc -c Validity.c

File.o : File.c Maze.h
	gcc -c File.c

clean: 
	rm *.o
