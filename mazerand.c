#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//Définir un type pour le labyrinthe
typedef struct Maze {
   unsigned short  ** matrix;
   int size[2];
   int In[2];
   int Out[2];
   int Find[2];
} Maze;

typedef struct Position {
   int x;
   int y;
}Position;


//Creation du labyrinthe
Maze RandMaze()
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
	maze.size[0] = size1;
	maze.size[1] = size2;
	

	maze.matrix =  calloc(maze.size[0] , sizeof(unsigned short *));
	for (i=0;i<maze.size[0];i++)
	{
		maze.matrix[i]=  calloc(maze.size[1] , sizeof(unsigned short));
	}
	
	
	//Génération des murs du labyrinthe (remplissage de la matrice)s
	int test_values1;
	int test_values2;
	int test_values3;
	int test_values4;
	int val;
	
	for(i=0;i<maze.size[0];i++)
	{
		for(j=0;j<maze.size[1];j++)
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

	int Tab_size = (maze.size[1] + maze.size[1] + maze.size[0] + maze.size[0])-4;
	Tab_pos = calloc( Tab_size , sizeof(Position));
	//Regrouper les postions possible dans un tableau (type position)

	//Remplire le tableau Tab_pos des positions d'entrée possibles (i,j)={(0,0),...,(0,size-1)}
	for(i=0;i<maze.size[1];i++){
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
		else if(i == maze.size[1]-1)
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
	for(i=0;i<maze.size[1];i++){
		p.x = maze.size[0]-1;
		p.y = i;
		Tab_pos[index] = p;
		index++;
		
		if(i==0) 
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[maze.size[0]-1][i] ^= (-1 ^ maze.matrix[maze.size[0]-1][i]) & (1UL << 1);
			maze.matrix[maze.size[0]-1][i] ^= (-1 ^ maze.matrix[maze.size[0]-1][i]) & (1UL << 0);
		} 
		else if(i == maze.size[1]-1)
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[maze.size[0]-1][i] ^= (-1 ^ maze.matrix[maze.size[0]-1][i]) & (1UL << 1);
			maze.matrix[maze.size[0]-1][i] ^= (-1 ^ maze.matrix[maze.size[0]-1][i]) & (1UL << 2);
		}
		else
		{
			// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
			maze.matrix[maze.size[0]-1][i] ^= (-1 ^ maze.matrix[maze.size[0]-1][i]) & (1UL << 1);
		}
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,0),...,(size-2,0)}
	for(i=1;i<maze.size[0]-1;i++){
		p.x = i;
		p.y = 0;
		Tab_pos[index]=p;
		index++;
		
		
		// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
		maze.matrix[i][0] ^= (-1 ^ maze.matrix[i][0]) & (1UL << 0);
		
	}
	
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,size-1),...,(size-1,size-1)}
	for(i=1;i<maze.size[0]-1;i++){
		p.x = i;
		p.y = maze.size[1]-1;
		Tab_pos[index]=p;
		index++;
		
		// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
		maze.matrix[i][maze.size[1]-1] ^= (-1 ^ maze.matrix[i][maze.size[1]-1]) & (1UL << 2);
	}
	
	//Choisir aléatoirement une position parmis celle du tableau Tab_pos
	int Pos_InX= rand()%maze.size[0];
	int Pos_InY= rand()%maze.size[1];
	
	maze.In[0]=Pos_InX;
	maze.In[1]=Pos_InY;
	

	int Pos_OutX = 0 ;
	int Pos_OutY = 0;
	
	do{
		Pos_OutX = rand()%maze.size[0];
	}while(Pos_OutX == Pos_InX);
	
	do{
		Pos_OutY = rand()%maze.size[1];
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

int main ()
{
	srand(time(NULL));   
     
	int i=0,j=0;
	FILE * fp;
	
	//Creation de la matrice
	Maze maze = RandMaze();

	fp = fopen ("matrix.txt","w");

	fprintf (fp,"%d %d %d %d %d %d\n", maze.size[0],maze.size[1], maze.In[0], maze.In[1], maze.Out[0], maze.Out[1]);

	//Affichage
	printf("%d %d %d %d %d %d\n",maze.size[0],maze.size[1], maze.In[0], maze.In[1], maze.Out[0], maze.Out[1]);

	
	for(i=0;i<maze.size[0];i++)
	{
			
		for(j=0;j<maze.size[1];j++)
		{
			
			printf("%d ",maze.matrix[i][j]);
			fprintf (fp,  "%d ",maze.matrix[i][j]);
		}
		printf("\n");
		fprintf (fp,"\n");
	}

	fclose (fp);

	//Liberer l'espace allouer pour le labyrinthe
	free(maze.matrix);

 return 0;
}
