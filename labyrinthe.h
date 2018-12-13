#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define ENTREE "ficlab.txt"

typedef struct Maze
{
	unsigned short int ** Matrix;
	int Lin;
	int Col;
	int In[2];
	int Out[2];
	int Find[2];
}Maze;

typedef struct Position {
   int X;
   int Y;
} Position;





//Lecture dans un fichier txt
Maze lectFic(char * fic);

//sauvegarde le labyrinthe m dans le fichier fic_alea
char* saveMaze(Maze m, char * fic_alea);

//Prends un entier et un tableau de 16 éléments et remplit le tableau avec sa base 2 tab[0]=bit poids faible
int* itob(int a, int * T);

//test la validité du labyrinthe
int MazeValid(Maze m);

//affiche le lab
void aff(Maze M);






#endif
