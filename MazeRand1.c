#include "Maze.h"

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
	
	//Allocation d'un espace dynamique pour la matrice du labyrinthe
	maze.Matrix =  calloc(maze.Lin , sizeof(unsigned short *));
	for (i=0;i<maze.Lin;i++)
	{
		maze.Matrix[i]=  calloc(maze.Col , sizeof(unsigned short));
	}
	
	//Definir des variables test dont on aura besoin dans le remplissage de la matrice et la gestion des murs
	int test_values1;
	int test_values2;
	int test_values3;
	int test_values4;
	int val;//variable intermédiaire que nous allons utiliser pour remplire les case de la matrice

	//Remplire la matrice - Génération des murs du labyrinthe
	for(i=0;i<maze.Lin;i++)
	{
		for(j=0;j<maze.Col;j++)
		{
			
			if(i==0)
			{ 
				if(j==0)
				{	/*
						Cas Matrix[i][j] = Matrix[0][0]:
					*/

					//Donner à val une valeur alétoire modulo 15 de sorte à avoir un entier sur 4 bits (val=(b3 b2 b1 b0) en base 2) pour la gestion des 4 murs de chaque case de la matrice
					val = (rand()%(15));
					//Affecter la valeur à Matrix[0][0]
					maze.Matrix[i][j]=val;
				}
				else
				{
					/*
						Cas Matrix[i][j] = {Matrix[0][1], Matrix[0][2], Matrix[0][3], ... , Matrix[0][Col-1]:
					*/
					do{
						val = (rand()%(15));
						//Prendre la valeur du b0 de val
						test_values1 = 1 &(val>>0);
						//Prendre la valeur du b2 de Matrix[i][j-1]
						test_values2 = 1 &(maze.Matrix[i][j-1]>>2);
					//Faire tourner la boucle jusqu'à avoir b0 de val égal à b2 de Matrix[i][j-1] pour qu'il n'y est pas d'anomalie entre les murs que partages les cases voisines	
					}while(test_values1 != test_values2);
					maze.Matrix[i][j]=val;	
				}
			}
			else 
			{
				if(j==0)
				{
					/*
						Cas Matrix[i][j] = {Matrix[1][0],... , Matrix[Lin-1][0]:
					*/
					
					do{
						val = (rand()%(15));
						//Prendre la valeur du b3 de val
						test_values1 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[i-1][j]
						test_values2 = 1 &(maze.Matrix[i-1][j]>>1);
					//Faire tourner la boucle jusqu'à avoir b3 de val égal au b1 de Matrix[i-1][j] pour qu'il n'y est pas d'anomalie entre les murs que partages les cases voisines	
					}while(test_values1 != test_values2);	
					maze.Matrix[i][j]=val;	
					
				}
				else
				{
					/*
						Cas Matrix[i][j] = {Matrix[1][1],Matrix[1][2],...,Matrix[1][Col-1], Matrix[2][1],Matrix[2][2],...,Matrix[2][Col-1],...,Matrix[Lin-1][1],Matrix[Lin-1][2],...,Matrix[Lin-1][Col-1]:
					*/	
					do{
						val = (rand()%(15));
						//Prendre la valeur du b0 de val
						test_values1 = 1 &(val>>0);
						//Prendre la valeur du b2 de Matrix[i][j-1]
						test_values2 = 1 &(maze.Matrix[i][j-1]>>2);
						//Prendre la valeur du b3 de val
						test_values3 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[i-1][j]
						test_values4 = 1 &(maze.Matrix[i-1][j]>>1);
					//Faire tourner la boucle jusqu'à avoir b0 de val égal au b2 de Matrix[i][j-1] et b3 de val égal au b1 de Matrix[i-1][j] pour qu'il n'y est pas d'anomalie entre les murs que partages les cases voisines	
					}while((test_values3 != test_values4) || (test_values1 != test_values2));	
					maze.Matrix[i][j]=val;	
				}
			}		
		}
	}
	
			
	//Creation de tableau Tab_pos qui contient les positions (contour du labyrinthe) i.e Matrix[i][j] = {Matrix[0][0],Matrix[0][1],...,Matrix[0][Col-1], Matrix[1][0],Matrix[2][0],...,Matrix[Lin-1][0], Matrix[Lin-1][1],Matrix[Lin-1][2],...,Matrix[Lin-1][Col-1], Matrix[1][Col-1],Matrix[2][Col-1],...,Matrix[Lin-2][Col-1]:

	int Tab_size = (maze.Col + maze.Col + maze.Lin + maze.Lin)-4; //Dimension de Tab_pos
	
	
	//Allocation d'un espace dynamique pour le tableau de position
	Tab_pos = calloc( Tab_size , sizeof(Position)); //Ce tableau nous l'utiliserons pour mettre des murs sur ces positions là ainsi que pour le choix de l'entrée/sortie positionées sur les côtés du labyrinthe
	
	//Remplire le tableau Tab_pos par les positions Matrix[0][0],Matrix[0][1],...,Matrix[0][Col-1]
	for(i=0;i<maze.Col;i++){
				p.X = 0;
				p.Y = i;
				Tab_pos[index]=p;
				index++;
		
				if(i==0){
					//Cas Matrix[i][j] = Matrix[0][0]:
					// Affecter 1 au b3 de Matrix[0][i]
					maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 3);// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
					// Affecter 1 au b0 de Matrix[0][i]
					maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 0);
					} 
				else if(i==maze.Col-1){
					//Cas Matrix[i][j] = Matrix[0][Col-1]:
					// Affecter 1 au b3 de Matrix[0][i]		
					maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 3);
					// Affecter 1 au b2 de Matrix[0][i]
					maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 2);
					}
				else{
					//Cas Matrix[i][j] = Matrix[0][1],...,Matrix[0][Col-2]:
					// Affecter 1 au b3 de Matrix[0][i]
					maze.Matrix[0][i] ^= (-1 ^ maze.Matrix[0][i]) & (1UL << 3);
					}
	}
	
	//Remplire le tableau Tab_pos par les positions Matrix[Lin-1][0],...,Matrix[Lin-1][Col-1]
	for(i=0;i<maze.Col;i++){
				p.X = ((maze.Lin)-1);
				p.Y = i;
				Tab_pos[index] = p;
				index++;
		
				if(i==0){
					
					//Cas Matrix[i][j] = Matrix[Lin-1][0]
					//Affecter 1 au b1 de Matrix[Lin-1][0]
					maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 1);
					//Affecter 1 au b0 de Matrix[Lin-1][0]
					maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 0);
					} 
				else if(i==maze.Col-1){
					//Cas Matrix[i][j] = Matrix[Lin-1][Col-1]
					//Affecter 1 au b1 de Matrix[Lin-1][i]
					maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 1);
					//Affecter 1 au b2 de Matrix[Lin-1][i]
					maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 2);
					}
				else{
					//Cas Matrix[i][j] = Matrix[Lin-1][1],...,Matrix[Lin-1][Col-1]
					//Affecter 1 au b1 de Matrix[Lin-1][i]
					maze.Matrix[maze.Lin-1][i] ^= (-1 ^ maze.Matrix[maze.Lin-1][i]) & (1UL << 1);
					}
	}
	
	//Remplire le tableau Tab_pos par les positions Matrix[1][0],...,Matrix[Lin-2][0]
	for(i=1;i<maze.Lin-1;i++){
				p.X = i;
				p.Y = 0;
				Tab_pos[index]=p;
				index++;
				
				//Cas Matrix[i][j] = Matrix[1][0],...,Matrix[Lin-2][0]
				//Affecter 1 au b0 de Matrix[i][0]
				maze.Matrix[i][0] ^= (-1 ^ maze.Matrix[i][0]) & (1UL << 0);
				}

	//Remplire le tableau Tab_pos par les positions Matrix[1][Col-1],...,Matrix[Lin-2][Col-1]
	for(i=1;i<maze.Lin-1;i++){
				p.X = i;
				p.Y = ((maze.Col)-1);
				Tab_pos[index]=p;
				index++;
		
				//Cas Matrix[i][j] = Matrix[1][Col-1],...,Matrix[Lin-2][Col-1]
				//Affecter 1 au b2 de Matrix[i][Col-1]
				maze.Matrix[i][maze.Col-1] ^= (-1 ^ maze.Matrix[i][maze.Col-1]) & (1UL << 2);
	}
	
	//Choisir aléatoirement une position parmis celle du tableau Tab_pos
	int Pos_InX= (rand()%((maze.Lin)));
	int Pos_InY= (rand()%((maze.Col)));
	
	//Affecter la valeur de l'entrée à In[2]
	maze.In[0]=Pos_InX;
	maze.In[1]=Pos_InY;
	
	int Pos_OutX = 0;
	int Pos_OutY = 0;

	//Chercher une position differente de l'entrée	
	do{
		Pos_OutX = (rand()%((maze.Lin)));
	}while(Pos_OutX == Pos_InX);
	
	do{
		Pos_OutY = (rand()%((maze.Col)));
	}while(Pos_OutY == Pos_InY);
	
	//Affecter la valeur de la sortie à Out[2]
	maze.Out[0] = Pos_OutX;
	maze.Out[1] = Pos_OutY;
	
	//Affecter la valeur de l'entrée à Find[2] (Positioner le chercheur du chemin à l'entrée
	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];
	
	return maze;
}
