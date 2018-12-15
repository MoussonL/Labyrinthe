
#include "Maze.h"

int way(Maze M, Path path, int i, int j)
{
	int k;
	int n=0;
	for (k = 1; k < path.distance; k++)			// Le curseur est de 1 a path.distance car k = 0 est l'entrÃ©e 
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

void dis(Maze M, Path path) //val1 = M[i][j] | val2 = M[i][j-1] 
{
	int i,j,k;
	int way1,way2;
	if(path.distance == -1)
	{
		printf("Ce Labyrinthe ne possède pas de chemin entre l'entrée et la sortie\n");
	}
	/*for (i = 0; i < M.Lin; i++)
	{
		for (j = 0; j < M.Col; j++)
		{
			way2 =way(M,path,i,j); 
			printf("%d  ",way2);
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
			if ((M.Matrix[0][i-1]/8)%2 == 0)//Si il n'y a pas dÃ©jÃ  un mur en bas prÃ©cedement, 
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
			way1 = way(M,path,i,j);
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
					switch(way1)
					{
						case 0: 			//Le cas 0 c'est si il n'y a rien
							printf("   |");
							break;
						case 1:				//Le cas 1 c'est si le chemin passe par cette case
							printf(" வ |");
							break;
						case 2:				//Le cas 2 c'est si l'entrÃ©e est sur cette case
							printf(" E |");
							break;
						case 3:				//Le cas 3 c'est si la sortie est sur cette case
							printf(" S |");
							break;
					}
				}
				else
				{
					switch(way1)
					{
						case 0:
							printf("    |");
							break;
						case 1:
							printf("  வ |");
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
			else							//Mur ni ÃƒÆ’  droite ni ÃƒÆ’  gauche
			{	
				if(M.Matrix[i][j]%2 == 0 && (M.Matrix[i][j]/4)%2 == 0)	
				{
					switch(way1)
					{
						case 0:
							printf("    ");
							break;
						case 1:
							printf("  வ ");
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
					switch(way1)
					{
						case 0:
							printf("   ");
							break;
						case 1:
							printf(" வ ");
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
				if ((M.Matrix[i][j-1]/2)%2 == 0) //Si il y a dÃƒÂ©jÃƒ  un mur en bas prÃƒÂ©cedement, 
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
				if ((M.Matrix[i][j-1]/2)%2 == 0)//Si il n'y a pas dÃƒÂ©jÃƒ  un mur en bas prÃƒÂ©cedement, 
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
