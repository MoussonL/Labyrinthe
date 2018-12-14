#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

void aff(Maze M) //val1 = M[i][j] | val2 = M[i][j-1] 
{
	int i,j,k;

	for ( i = 0; i < M.Col + 1 ; i++) //Premier mur du haut
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
					if(i == M.In[0] && j == M.In[1])
					{
						printf(" E |");
					}
					else
					{	
						if(i == M.Out[0] && j == M.Out[1])
						{
							printf(" S |");
						}
						else
						{
							printf("   |");
						}
					}
				}
				else
				{
					if(i == M.In[0] && j == M.In[1])
					{
						printf("  E |");
					}
					else	
					{
						if(i == M.Out[0] && j == M.Out[1])
						{
							printf(" S |");
						}
						else
						{
							printf("    |");
						}
					}
				} 
			}
			else							//Mur ni Ã  droite ni Ã  gauche
			{	
				if(M.Matrix[i][j]%2 == 0 && (M.Matrix[i][j]/4)%2 == 0)	
				{
					if(i == M.In[0] && j == M.In[1])
					{
						printf("  E ");
					}
					else	
					{
						if(i == M.Out[0] && j == M.Out[1])
						{
							printf("  S ");
						}
						else
						{
							printf("    ");		// espace supplémentaire pour compenser l'intersection
						}
					}
				}
				else
				{
					if(i == M.In[0] && j == M.In[1])
					{
						printf(" E ");
					}
					else
					{
						if(i == M.Out[0] && j == M.Out[1])
						{
							printf(" S ");
						}
						else
						{
							printf("   ");
						}
					}
				}
				
			}
		}
			printf("\n");
		for (j = 0; j < M.Col + 1; j++) //Affiche mur du bas
		{
			if((M.Matrix[i][j]/2)%2 == 1)
			{
				if ((M.Matrix[i][j-1]/2)%2 == 0) //Si il y a déjà un mur en bas précedement, 
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
				if ((M.Matrix[i][j-1]/2)%2 == 0)//Si il n'y a pas déjà un mur en bas précedement, 
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
	printf("distance : %d\n", path.distance);
	for (int i = 0; i < path.distance + 1; i++)
		printf("(%d , %d)%s\n", path.Way[i].X, path.Way[i].Y, i != path.distance ? " -> " : "");
	printf("\n\n");
}/* En cas de besoin, affiche les cases successives que le chemin emprunte. Bisous, Morgane <3 */
