#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

int chemin(Maze M, Path path, int i, int j)
{
	int k;
	int n=0;
	for (k = 1; k < path.distance; k++)			// Le curseur est de 1 a path.distance car k = 0 est l'entrée 
	{							// et k = path.distance+1 est la sortie 
		if (path.Way[k].X == i && path.Way[k].Y == j)
		{
			n=1;
		}
	}
	if (i == M.In[0] && j == M.In[1])
	{
		n=2;
	}
	if (i == M.Out[0] && j == M.Out[1])
	{
		n=3;
	}
	return n;
}

void aff(Maze M, Path path) //val1 = M[i][j] | val2 = M[i][j-1] 
{
	int i,j,k;
	int chem,che;

	/*for (i = 0; i < M.Lin; i++)
	{
		for (j = 0; j < M.Col; j++)
		{
			chem =chemin(M,path,i,j); 
			printf("%d  ",chem);
		}
		printf("\n");	}*/
	for ( i = 0; i < M.Col ; i++) //Premier mur du haut
	{
		if((M.Matrix[0][i]/8)%2 == 1)
		{
			if ((M.Matrix[0][i-1]/8)%2 == 0)
			{
				printf("+---+");
			}
			else
			{
				printf("---+");
			}
		}
		else
		{
			if ((M.Matrix[0][i-1]/8)%2 == 0)//Si il n'y a pas déjà un mur en bas précedement, 
				{                           //il faut marquer l'intersection de deux case
					printf("+   ");
				}
				else
				{
				    printf("   ");
			    }
		}
	}
	printf("\n");

	for (i = 0; i < M.Lin; i++)
	{
		for (j = 0; j < M.Col; j++)
		{
			che = chemin(M,path,i,j);
			if(M.Matrix[i][j]%2 == 1)//Affiche le mur de gauche
			{
				if(M.Matrix[i][j-1]/4%2 == 0)
				{
					printf("|"); 
				}
			}
			if((M.Matrix[i][j]/4)%2 == 1) //Affiche le mur de droite
			{
				if (M.Matrix[i][j]%2 == 1)
				{ 
					switch(che)
					{
						case 0: 			//Le cas 0 c'est si il n'y a rien
							printf("   |");
							break;
						case 1:				//Le cas 1 c'est si le chemin passe par cette case
							printf(" ഖ |");
							break;
						case 2:				//Le cas 2 c'est si l'entrée est sur cette case
							printf(" E |");
							break;
						case 3:				//Le cas 3 c'est si la sortie est sur cette case
							printf(" S |");
							break;
					}
				}
				else
				{
					switch(che)
					{
						case 0:
							printf("    |");
							break;
						case 1:
							printf("  ഖ |");
							break;
						case 2:
							printf("  E |");
							break;
						case 3:
							printf("  S |");
							break;

					}
				} 
			}
			else							//Mur ni Ãƒ  droite ni Ãƒ  gauche
			{	
				if(M.Matrix[i][j]%2 == 0 && (M.Matrix[i][j]/4)%2 == 0)	
				{
					switch(che)
					{
						case 0:
							printf("    ");
							break;
						case 1:
							printf("  ഖ ");
							break;
						case 2:
							printf("  E ");
							break;
						case 3:
							printf("  S ");
							break;

					}
				}
				else
				{
					switch(che)
					{
						case 0:
							printf("   ");
							break;
						case 1:
							printf(" ഖ ");
							break;
						case 2:
							printf(" E ");
							break;
						case 3:
							printf(" S ");
							break;

					}
				}
				
			}
		}
			printf("\n");
		for (j = 0; j < M.Col + 1; j++) //Affiche mur du bas
		{
			if((M.Matrix[i][j]/2)%2 == 1)
			{
				if ((M.Matrix[i][j-1]/2)%2 == 0) //Si il y a dÃ©jÃ  un mur en bas prÃ©cedement, 
				{                               //il n'y a pas besoin de remettre une intersection
					printf("+---+");
				}
				else
				{
					printf("---+");
				}
			}
			else
			{
				if ((M.Matrix[i][j-1]/2)%2 == 0)//Si il n'y a pas dÃ©jÃ  un mur en bas prÃ©cedement, 
				{                               //il faut marquer l'intersection de deux case
					printf("+   ");
				}
				else
				{
				    printf("   ");
			    }
			}
		}
		printf("\n");
	}
}

void display_path(Path path)
{
	int i;	
	printf("distance : %d\n", path.distance);
	for (i = 0; i < path.distance + 1; i++)
		printf("(%d , %d)%s\n", path.Way[i].X, path.Way[i].Y, i != path.distance ? " -> " : "");
	printf("\n\n");
}
// En cas de besoin, affiche les cases successives que le chemin emprunte. Bisous, Morgane <3 
