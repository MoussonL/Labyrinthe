#include "Maze.h"


// Pb : Maze que carré ?
// Maze petit ?
// Position(ligne, colonne) ou (colonne, ligne) ?
// Curseur ? 


//Find[0] == ligne == x

void display_lab(Maze* maze) //test fct
{
	for(int i = 0 ; i < maze->Lin ; i++)
	{
		for(int j = 0 ; j < maze->Col ; j++)
			printf("%d\t", maze->Matrix[i][j] % 16);
		printf("\n");
	}printf("\n\n\n");

}

void test_fonction_can_go_there(Maze maze)
{
	for (int dir = 1 ; dir <= 8 ; dir *= 2)
		printf("%d\n", ft_can_go_there(maze, dir));
}

void set_distance_max(Maze* maze)
{
	for (int i=0; i<maze->Lin; i++)
	{
		for (int j=0; j < maze->Col ; j++)
			set_distance(maze, i, j, DISTANCE_MAX);
	}
	set_distance(maze, maze->In[0], maze->In[1], 0);
}

int get_distance(Maze* maze, int ligne, int colonne)
{
	return(maze->Matrix[ligne][colonne] / 16);
}

void set_distance(Maze* maze, int ligne, int colonne, int distance)
{
	maze->Matrix[ligne][colonne] = maze->Matrix[ligne][colonne]%16 + distance * 16;
}


int ft_can_go_there(Maze maze, int dir)
{
	int go_there;
	int been_there_before;
	/*go_there = !((dir == 1 && maze.Matrix[maze.Find[0]][maze.Find[1]] % 2 ) || (dir == 4 && maze.Matrix[maze.Find[0]][maze.Find[1]] / 4 % 2 ) || (dir == 2 && maze.Matrix[maze.Find[0]][maze.Find[1]] / 2 % 2) || (dir == 8 && maze.Matrix[maze.Find[0]][maze.Find[1]] / 8 % 2 ));
	 go_there me dit si oui ou non je peux avancer dans la direction demandée:
	-> booléen 1 = 1 si je veux aller à gauche et que j'ai un mur à gauche, 0 sinon
	-> booléen 2 = 1 si je veux aller à droite et que j'ai un mur à droite, 0 sinon
	-> booléen 3 = 1 si je veux aller en bas et que j'ai un mur en bas, 0 sinon
	-> booléen 4 = 1 si je veux aller en haut et que j'ai un mur en haut, 0 sinon
	booléen 1 || booléen 2 || booléen 3 || booléen 4 = 1 si l'un d'entre eux vaut 1, donc 1 si je ne peux pas aller dans la direction que je demande
	go_there = ! (booléen 1 || booléen 2 || booléen 3 || booléen 4 = 1)
	go_there = 1 si je peux aller dans la direction que je souhaite*/

	go_there = is_not_a_wall(maze, maze.Find[0], maze.Find[1], dir);

	if (go_there == 1)
	{
		been_there_before = (get_distance(&maze, maze.Find[0]+(dir == 2) - (dir == 8), maze.Find[1]-(dir == 1)+(dir == 4)) <= get_distance(&maze, maze.Find[0], maze.Find[1]) +1);
	}
	
	else
	{
		been_there_before = 0;
	}	
	/* been_there_before vaut 0 si je suis déjà passée par la case dans laquelle je veux aller avec une distance grande
	   been_there_before vaut 1 si je ne suis pas encore passée par cette case OU si j'ai atteind cette case avec une distance plus petit*/
	return(go_there && !been_there_before);
	/* cette fonction me retourne donc :
	-> 1 si je peux aller dans cette case et que, soit je n'y suis pas encore allée, soit j'y suis allée avec une distance plus grande
	-> 0 si je ne peux pas aller dans cette direction OU si j'y suis déjà passée en empruntant un chemin plus court */

}


void ft_move_cursor(Maze* maze, int dir)
{
	maze->Find[1] += ((dir == 4) - (dir == 1));
	maze->Find[0] += ((dir == 2) - (dir == 8));
} 
//maze est ici un pointeur, car je ne veux pas créer une copie locale de mon Maze
//cette fonction doit modifiée mon lab. Comme lab == pointeur, mettre -> au lieu de ".".

void ft_mapping_maze(Maze maze, int longueur)
{
	
	if ((maze.Find[1] == maze.Out[1]) && (maze.Find[0] == maze.Out[0]))
	{
		return;
	}


	for (int dir = 1; dir <= 8; dir *= 2)
	{
		if (ft_can_go_there(maze, dir) == 1)
		{
			ft_move_cursor(&maze, dir);
			longueur += 1;
			set_distance(&maze, maze.Find[0], maze.Find[1], longueur);
			ft_mapping_maze(maze, longueur);
			ft_move_cursor(&maze, dir * 4 % 15);
			longueur -= 1;
		}
	}
}


int is_not_a_wall(Maze maze, int ligne, int colonne, int dir)
{
	return(!(maze.Matrix[ligne][colonne] / dir % 2));
}
/* fonction qui retourne 1 si je n'ai pas de mur dans la direction demandée*/

Position pos_adjacent_cell(Maze maze, int ligne, int colonne)
{
	Position pos;
	for (int dir =1; dir <= 8 ; dir *= 2)
	{
		if (is_not_a_wall(maze, ligne, colonne, dir) && (get_distance(&maze, ligne + ((dir == 2) - (dir == 8)), colonne + ((dir == 4)-(dir == 1))) == get_distance(&maze, ligne, colonne) - 1))
		{
			pos.X = (ligne + ((dir == 2) - (dir == 8)));
			pos.Y = (colonne + ((dir == 4)-(dir == 1)));
			return(pos);
		}	
	}
	pos.X = -1;
	pos.Y = -1;
	return(pos);
}

Path ft_build_path(Maze maze)
{
	Path path;
	path.distance = get_distance(&maze, maze.Out[0], maze.Out[1]);

	if ((path.distance == DISTANCE_MAX) && (pos_adjacent_cell(maze, maze.Out[0], maze.Out[1]).X == -1))
	{
		path.distance = NOPATH;
		path.Way = NULL;
		return(path);
	}

	path.Way = (Position*)malloc(sizeof(Position) * (path.distance +1));
	path.Way[0].X = maze.Out[0];
	path.Way[0].Y = maze.Out[1];

	for (int i=1; i < path.distance +1; i++)
	{
		path.Way[i].X = pos_adjacent_cell(maze, path.Way[i-1].X, path.Way[i-1].Y).X;
		path.Way[i].Y = pos_adjacent_cell(maze, path.Way[i-1].X, path.Way[i-1].Y).Y;
	}

	return(path);
}

Path way_search(Maze maze)
{
	set_distance_max(&maze);
	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];
	ft_mapping_maze(maze,0);
	return(ft_build_path(maze));
}
