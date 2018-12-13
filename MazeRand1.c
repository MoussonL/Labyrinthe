#include "labyrinthe.h"

//Creation du labyrinthe
Maze RandMaze1()
{
	//Declarer une variable pour le labyrinthe
	Maze maze;
	Position p;
	Position *Tab_pos; //Tableau des positions possible pour le choix de Entrée/sortie du labyrinthe
	int i=0;
	int j=0;
	int choice;
	int size1;
	int size2;
	int index=0;

       //Generer la taille du labyrinthe random
	printf("Chosis une option: \n1-Taille Random\n2-Taille Personalise\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:	size1 = rand()%100 + 1; 
				size2 = rand()%100 + 1; 
				break;
		case 2: printf("Donner la taille (n,m) de votre labyrinthe : \n");
				scanf("%d",&size1);
				scanf("%d",&size2);
				break;
		default: break;
	}

	//Initialiser la taille de la matrice
	maze.Lin = size1;
	maze.Col = size2;
	

	maze.matrix =  calloc(maze.Lin , sizeof(unsigned short *));
	for (i=0;i<maze.Lin;i++)
	{
		maze.matrix[i]=  calloc(maze.Col , sizeof(unsigned short));
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
                    maze.matrix[i][j]=val;
				}
				else
				{
					do{
						val = rand()%15;
						test_values1 = 1 &(val>>0);
						test_values2 = 1 &(maze.matrix[i][j-1]>>2);
						
					}while(test_values1 != test_values2);

					maze.matrix[i][j]=val;	
				}
			}
			else 
			{
				if(j==0)
				{
					
					do{
					val = rand()%15;
					test_values1 = 1 &(val>>3);
					test_values2 = 1 &(maze.matrix[i-1][j]>>1);
					}while(test_values1 != test_values2);	
					maze.matrix[i][j]=val;	
					
				}
				else
				{
						
					do{
					val = rand()%15;
					
					test_values1 = 1 &(val>>0);
					test_values2 = 1 &(maze.matrix[i][j-1]>>2);
					
					test_values3 = 1 &(val>>3);
					test_values4 = 1 &(maze.matrix[i-1][j]>>1);
					}while((test_values3 != test_values4) || (test_values1 != test_values2));	
					
					maze.matrix[i][j]=val;	
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
		p.x = 0;
		p.y = i;
		Tab_pos[index]=p;
		index++;
		
		if(i==0) 
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[0][i] ^= (-1 ^ maze.matrix[0][i]) & (1UL << 3);
			maze.matrix[0][i] ^= (-1 ^ maze.matrix[0][i]) & (1UL << 0);
		} 
		else if(i==maze.Col-1)
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[0][i] ^= (-1 ^ maze.matrix[0][i]) & (1UL << 3);
			maze.matrix[0][i] ^= (-1 ^ maze.matrix[0][i]) & (1UL << 2);
		}
		else
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[0][i] ^= (-1 ^ maze.matrix[0][i]) & (1UL << 3);
		}
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(size-1,0),...,(size-1,size-1)}
	for(i=0;i<maze.Col;i++){
		p.x = maze.Lin-1;
		p.y = i;
		Tab_pos[index] = p;
		index++;
		
		if(i==0) 
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[maze.Lin-1][i] ^= (-1 ^ maze.matrix[maze.Lin-1][i]) & (1UL << 1);
			maze.matrix[maze.Lin-1][i] ^= (-1 ^ maze.matrix[maze.Lin-1][i]) & (1UL << 0);
		} 
		else if(i==maze.Col-1)
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[maze.Lin-1][i] ^= (-1 ^ maze.matrix[maze.Lin-1][i]) & (1UL << 1);
			maze.matrix[maze.Lin-1][i] ^= (-1 ^ maze.matrix[maze.Lin-1][i]) & (1UL << 2);
		}
		else
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[maze.Lin-1][i] ^= (-1 ^ maze.matrix[maze.Lin-1][i]) & (1UL << 1);
		}
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,0),...,(size-2,0)}
	for(i=1;i<maze.Lin-1;i++){
		p.x = i;
		p.y = 0;
		Tab_pos[index]=p;
		index++;
		
		
		// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
		maze.matrix[i][0] ^= (-1 ^ maze.matrix[i][0]) & (1UL << 0);
		
	}
	
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,size-1),...,(size-1,size-1)}
	for(i=1;i<maze.Lin-1;i++){
		p.x = i;
		p.y = maze.Col-1;
		Tab_pos[index]=p;
		index++;
		
		// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
		maze.matrix[i][maze.Col-1] ^= (-1 ^ maze.matrix[i][maze.Col-1]) & (1UL << 2);
	}
	
	//Choisir aléatoirement une position parmis celle du tableau Tab_pos
	int Pos_InX= rand()%maze.Lin;
	int Pos_InY= rand()%maze.Col;
	
	maze.In[0]=Pos_InX;
	maze.In[1]=Pos_InY;
	

	int Pos_OutX = 0 ;
	int Pos_OutY = 0;
	
	do{
		Pos_OutX = rand()%maze.Lin;
	}while(Pos_OutX == Pos_InX);
	
	do{
		Pos_OutY = rand()%maze.Col;
	}while(Pos_OutY == Pos_InY);
	
	
	maze.Out[0] = Pos_OutX;
	maze.Out[1] = Pos_OutY;
	
	//Sortie du labyrinthe
	//Génération d'une sortie aussi loin possible de l'entrée	
//	if(Tab_pos[Pos_In].x == 0){
//		do{
//			Pos_Out = rand()%Tab_size;
//		}while(Tab_pos[Pos_Out].x != size1-1);
//	}
//	else if (Tab_pos[Pos_In].x == size1-1){
//		do{
//			Pos_Out = rand()%Tab_size;
//		}while(Tab_pos[Pos_Out].x!= 0);
//	}
//	else if(Tab_pos[Pos_In].y == 0){
//		do{
//			Pos_Out= rand()%Tab_size;
//		}while(Tab_pos[Pos_Out].y != size1-1);
//	}else if(Tab_pos[Pos_Out].y == size1-1){
//		do{
//			Pos_Out= rand()%Tab_size;
//		}while(Tab_pos[Pos_Out].y != 0);
//	}

	
//	maze.Out[0] = Tab_pos[Pos_Out].x;
//	maze.Out[1] = Tab_pos[Pos_Out].y;
	
	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];
	return maze;
}
