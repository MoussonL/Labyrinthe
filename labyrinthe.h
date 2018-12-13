#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define ENTREE "ficlab.txt"

#define DISTANCE_MAX 4095 // 2**12 - 1
#define NOPATH -1

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

typedef struct 
{
	Position * Way; //un tableau de position
	int distance;
}Path;




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

//Génération d'un labyrinthe aléatoirement 
Maze MazeRand1();


//fonctionx nécessaires à la recherche de chemin:
void display_lab(Maze* maze);
void set_distance_max(Maze* maze);
int get_distance(Maze* maze, int ligne, int colonne);
void set_distance(Maze* maze, int ligne, int colonne, int distance);
int ft_can_go_there(Maze maze, int dir);
void test_fonction_can_go_there(Maze maze);
void ft_mapping_maze(Maze maze, int longueur);
void ft_move_cursor(Maze* maze, int dir);
int is_not_a_wall(Maze maze, int ligne, int colonne, int dir);

Position pos_adjacent_cell(Maze maze, int ligne, int colonne);
Path ft_build_path(Maze maze);
Path way_search(Maze maze

#endif
