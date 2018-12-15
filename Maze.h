#ifndef MAZE_H
#define MAZE_H

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

//Definir une structure Node qui sert à stocker les cases qui n'ont pas été déjà visitées dans une pile (pour la fonction MazePile()) 
typedef struct Node {
    int Data[4]; //Contient la position de la case courante et la position de la case précédente
    struct Node* Next;//Pointeur qui sert à pointer sur un autre noeud (liaison entre les noeuds)
}Node;
 

typedef struct 
{
	Position * Way; //un tableau de position
	int distance;
}Path;

unsigned short  ** MatrixVisited; //Definir une matrice qui sert à verifier si une case de Matrix a été visité ou pas (pour la fonction MazePile())


//Lecture dans un fichier txt
Maze lectFic(char * fic);

//sauvegarde le labyrinthe m dans le fichier fic_alea
char* saveMaze(Maze m, char * fic_alea);

//Prends un entier et un tableau de 16 éléments et remplit le tableau avec sa base 2 tab[0]=bit poids faible
int* itob(int a, int * T);

//test la validité du labyrinthe
int MazeValid(Maze m);

//affiche le lab
int way(Maze M, Path path, int i, int j);
void dis(Maze M,Path path);
void display_path(Path path);

//Génération d'un labyrinthe aléatoirement 
Maze MazeRand1(int size1, int size2);

//Génération d'un labyrinthe aléatoirement et l'entrée/sortie sur les côtés
Maze MazeRand2(int size1, int size2);

//fonctions nécessaires à la recherche de chemin:
Node* Push(Node* Head,int *Data_In);
Node* Pop(Node *Head,int *Elt);
int Empty(Node* Head);
//Génération d'un labyrinthe pseudo-aléatoirement (cases accécibles, entrée-sortie sur les côtés)
Maze MazePile(int size1, int size2);

//fonctions nécessaires à la recherche de chemin:
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
Path way_search(Maze maze);

#endif
