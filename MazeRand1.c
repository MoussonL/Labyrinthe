#include "Maze.h.h"

Maze MazeRand1(int size1,int size2)
{
	Maze maze; //Déclarer une variable de type Maze (labyrinthe)
	Position p;
	Position *Tab_pos; //Tableau des positions possible pour le choix de Entrée/sortie du labyrinthe
	int i=0;
	int j=0;
	int index=0;

	//Initialiser la taille de la matrice
	maze.Lin = size1;
	maze.Col = size2;
	

	maze.Matrix =  calloc(maze.Lin , sizeof(unsigned short *));
	for (i=0;i<maze.Lin;i++)
	{
		maze.Matrix[i]=  calloc(maze.Col , sizeof(unsigned short));
	}
	
	
	//Génération des murs du labyrinthe (remplissage de la matrice)s
	int test_values1;
	int test_values2;
	int test_values3;
	int test_values4;
	int val;
	
	for(i=0;i<maze.Lin;i++)
	{
		for(j=0;j<maze.Col;j++)
		{
			
			if(i==0)
			{ 
				if(j==0)
				{
					val = rand()%15;
                    maze.Matrix[i][j]=val;
				}
				else
				{
					do{
						val = rand()%15;
						test_values1 = 1 &(val>>0);
						test_values2 = 1 &(maze.Matrix[i][j-1]>>2);
						
					}while(test_values1 != test_values2);

					maze.Matrix[i][j]=val;	
				}
			}
			else 
			{
				if(j==0)
				{
					
					do{
					val = rand()%15;
					test_values1 = 1 &(val>>3);
					test_values2 = 1 &(maze.Matrix[i-1][j]>>1);
					}while(test_values1 != test_values2);	
					maze.Matrix[i][j]=val;	
					
				}
				else
				{
						
					do{
					val = rand()%15;
					
					test_values1 = 1 &(val>>0);
					test_values2 = 1 &(maze.Matrix[i][j-1]>>2);
					
					test_values3 = 1 &(val>>3);
					test_values4 = 1 &(maze.Matrix[i-1][j]>>1);
					}while((test_values3 != test_values4) || (test_values1 != test_values2));	
					
					maze.Matrix[i][j]=val;	
				}
			}		
		}
	}
			
	//Entree du labyrinthe
	//Creation d'un tableau qui contient les positions possible pour générer une entrée i.e: (i,j)={(0,0),...,(0,size-1),(1,0),...,(size-1,0),(0,size-1),...,(size-1,size-1),(size-1,0),...,(size-1,size-1)} 

	int Tab_size = (maze.Col + maze.Col + maze.Lin + maze.Lin)-4;
	Tab_pos = calloc( Tab_size , sizeof(Position));
	//Regrouper les postions possible dans un tableau (type position)

	//Remplire le tableau Tab_pos des positions d'entrée possibles (i,j)={(0,0),...,(0,size-1)}
	for(i=0;i<maze.Col;i++){
		p.X = 0;
		p.Y = i;
		Tab_pos[index]=p;
		index++;
		
		if(i==0) 
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 3);
			maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 0);
		} 
		else if(i==maze.Col-1)
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 3);
			maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 2);
		}
		else
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 3);
		}
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(size-1,0),...,(size-1,size-1)}
	for(i=0;i<maze.Col;i++){
		p.X = maze.Lin-1;
		p.Y = i;
		Tab_pos[index] = p;
		index++;
		
		if(i==0) 
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 1);
			maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 0);
		} 
		else if(i==maze.Col-1)
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 1);
			maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 2);
		}
		else
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 1);
		}
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,0),...,(size-2,0)}
	for(i=1;i<maze.Lin-1;i++){
		p.X = i;
		p.Y = 0;
		Tab_pos[index]=p;
		index++;
		
		
		// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
		maze.Matrix[i][0] ^= (-1 ^ maze.Matrix[i][0]) & (1UL << 0);
		
	}
	
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,size-1),...,(size-1,size-1)}
	for(i=1;i<maze.Lin-1;i++){
		p.X = i;
		p.Y = maze.Col-1;
		Tab_pos[index]=p;
		index++;
		
		// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
		maze.Matrix[i][maze.Col-1] ^= (-1 ^ maze.Matrix[i][maze.Col-1]) & (1UL << 2);
	}
	
	//Choisir aléatoirement une position parmis celle du tableau Tab_pos
	int Pos_InX= rand()%maze.Lin-1;
	int Pos_InY= rand()%maze.Col-1;
	
	maze.In[0]=Pos_InX;
	maze.In[1]=Pos_InY;
	

	int Pos_OutX = 0 ;
	int Pos_OutY = 0;
	
	do{
		Pos_OutX = rand()%maze.Lin-1;
	}while(Pos_OutX == Pos_InX);
	
	do{
		Pos_OutY = rand()%maze.Col-1;
	}while(Pos_OutY == Pos_InY);
	
	
	maze.Out[0] = Pos_OutX;
	maze.Out[1] = Pos_OutY;
	
	//Sortie du labyrinthe

	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];
	
	return maze;
}
