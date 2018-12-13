#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

void aff(Maze M) //val1 = M[i][j] | val2 = M[i][j-1] 
{
	int i,j,k;
/*

	for (k = 0; k < M.Col; k++)
		{
			if((M.Matrix[k][j]/2)%2 == 1)
			{
				printf("+---+"); //mur du bas
			}
			if((M.Matrix[i][j]/2)%2 == 0)
			{
				//if(M.Matrix[i][j]/%2 == 0)
				printf("   "); //mur du bas
			}
			else _
			{
				printf("   ");
			}
		}

*/

	for ( i = 0; i < M.Col; i++) //Premier mur du haut
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
			printf("   ");
		}
	}
	printf("\n");

	for (i = 0; i < M.Lin; i++)
	{
		for (j = 0; j < M.Col; j++)
		{
			if(M.Matrix[i][j]%2 == 1)//mur de gauche
			{
				if(M.Matrix[i][j-1]/4%2 == 0)
				{
					printf("|"); 
				}
			}
			if((M.Matrix[i][j]/4)%2 == 1) //mur de droite
			{
				if (M.Matrix[i][j]%2 == 1)
				{
					printf("   |");
					//printf("+---+"); 
				}
				else
				{
					printf("    |");
					//printf("+---+");
				} 
			}
			else					//Mur ni Ã  droite ni Ã  gauche
			{	
				if(M.Matrix[i][j]%2 == 0 && (M.Matrix[i][j]/4)%2 == 0)	
					{	
						printf("    "); // espace supplémentaire pour compenser l'intersection
						//printf("+---+");
					}
				else
				{
					printf("   ");
					//printf("+---+");
				}
				
			}
		}
			printf("\n");
		for (j = 0; j < M.Col; j++) //Mur du bas
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
