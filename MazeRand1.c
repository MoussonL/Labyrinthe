#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//Définir un type pour le labyrinthe
typedef struct Maze {
   unsigned short  ** Matrix; //Matrice = pointeur de pointeur
   int Lin; //Nombre de lignes
   int Col; //Nombre de colonnes 
   int In[2]; //Position de l'entrée i.e In[0]=ligne et In[1]=colonne
   int Out[2]; //Position de la sortie i.e Out[0]=ligne et Out[1]=colonne
   int Find[2]; //Position du chercheur du chemain i.e Find[0]=ligne et Find[1]=colonne
} Maze;

//Fonction RandMaze1() qui génère un labyrinthe totalement aléatoire (Les cases ne sont pas forcément toutes accécibles => paforcément de chemain et l'entée/sortie sont n'importe où)
Maze RandMaze1()
{
	Maze maze; //Déclarer une variable labyrinthe
	int i=0;
	int j=0;
	int choice; //Déclarer une variable pour le choix de la taille du labyrinthe (aléatoirement ou donner à l'entrée)
	int size1; //Déclarer une variable pour le nombre de ligne qu'on aura besoin dans le cas où l'utilisateur fait renter la valeur
	int size2; //Déclarer une variable pour le nombre de colonne qu'on aura besoin dans le cas où l'utilisateur fait renter la valeur
       
	/* 
		*************** Choisir la taille du labyrinthe ***************
	*/

	//Proposer à l'utilisateur de choisire la taille par lui même ou bien aléatoirement.
	printf("Chosis une option: \n1-Taille Random\n2-Taille Personalise\n"); 
	scanf("%d",&choice);

	switch(choice){
		//1er choix: génération alétoire de la taille du labyrinthe(max=100x100)
		case 1:	size1 = rand()%100 + 1; 
			size2 = rand()%100 + 1; 
				break;
		//2ème choix: faire rentrer la taille du labyrinthe par l'utilisateur (max=100x100)
		case 2: printf("Donner la taille (n,m) de votre labyrinthe (max(n,m)=100x100) : \n");
				scanf("%d",&size1);
				scanf("%d",&size2);
				break;
		default: break;
	}
	
	/*
		*************** Création du labyrinthe *************** 
	*/

	//Initialisation de la taille de la matrice du labyrinthe
	maze.Lin = size1;
	maze.Col = size2;
	
	//Allocation d'un espace dynamique pour la matrice du labyrinthe
	maze.Matrix =  calloc(maze.Lin , sizeof(unsigned short *));
	for (i=0;i<maze.Lin;i++)
	{
		maze.Matrix[i]=  calloc(maze.Col , sizeof(unsigned short));
	}
	
	//Definir des variables dont on aura besoin dans le remplissage de la matrice et la gestion des murs
	int test_values1; //variable intermédiaire que nous allons utiliser pour des tests
	int test_values2; //variable intermédiaire que nous allons utiliser pour des tests
	int test_values3; //variable intermédiaire que nous allons utiliser pour des tests
	int test_values4; //variable intermédiaire que nous allons utiliser pour des tests
	int test_values5; //variable intermédiaire que nous allons utiliser pour des tests
	int test_values6; //variable intermédiaire que nous allons utiliser pour des tests
	int val; //variable intermédiaire que nous allons utiliser pour remplire les case de la matrice

	//Remplire la matrice
	for(i=0;i<maze.Lin;i++)
	{
		for(j=0;j<maze.Col;j++)
		{
			
			if(i==0)
			{ 
				if(j==0)
				{
					//Cas Matrix[i][j] = Matrix[0][0]: 

					do{
						//Donner à val une valeur alétoire modulo 15 de sorte à avoir un entier sur 4 bits (val=(b3 b2 b1 b0) en base 2) pour la gestion des 4 murs de chaque case de la matrice
						val = rand()%15;
						//Prendre la valeur du b0 de val
						test_values1 = 1 &(val>>0);
						//Prendre la valeur du b3 de val
						test_values2 = 1 &(val>>3);
						//Faire tourner la boucle jusqu'à avoir un b0 et b3 de val égales à 1 car il nous faut des murs sur les côté
					}while((test_values1 != 1) || (test_values2 != 1) );
					//Affecter la valeur à Matrix[0][0]
                    			maze.Matrix[i][j]=val;
				}
				else if(j == maze.Col-1)
				{
					//Cas Matrix[i][j] = Matrix[0][Col-1]:
					do{
						val = rand()%15;
						//Prendre les valeur du b2 de val
						test_values1 = 1 &(val>>2);
						//Prendre la valeur du b3 de val
						test_values2 = 1 &(val>>3);
						//Prendre les valeur du b0 de val
						test_values3 = 1 &(val>>0);
						//Prendre la valeur du b2 de Matrix[0][j-1]
						test_values4 = 1 &(maze.Matrix[i][j-1]>>2);
					//Faire tourner la boucle jusqu'à avoir un b2 et b3 de val égales à 1 car il faut des murs sur les côtés du labyrithe et b0 de val soit égal à b2 de Matrix[0][j-1] pour qu'il n'y est pas d'anomalie entre les murs que partages les cases voisines
					}while((test_values1 != 1) || (test_values2 != 1) || (test_values3 != test_values4) );
					//Affecter la valeur à Matrix[0][Col-1]
                    			maze.Matrix[i][j]=val;
				}
				else
				{
					//Cas Matrix[i][j] = {Matrix[0][1], Matrix[0][2], Matrix[0][3], ... , Matrix[0][Col-2]:
					do{	
						val = rand()%15;
						//Prendre la valeur du b3 de val
						test_values1 = 1 &(val>>3); 
						//Prendre la valeur du b0 de val
						test_values2 = 1 &(val>>0);
						//Prendre la valeur du b3 de Matrix[0][j-1] 
						test_values3 = 1 &(maze.Matrix[i][j-1]>>2);
					//Faire tourner la boucle jusqu'à avoir b3 de val égal à 1 car il nous faut un murs sur les côtés du labyrinthe et b0 de val soit égal à b2 de Matrix[0][j-1] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines	
					}while((test_values1 != 1) || (test_values2 != test_values3));
					//Affecter la valeur à Matrix[0][j]
					maze.Matrix[i][j]=val;	
				}
			}
			else if (i == maze.Lin-1)
			{
				if(j==0)
				{
					//Cas Matrix[Lin-1,0]:	
					do{
						val = rand()%15;
						
						//Prendre la valeur du b1 de val
						test_values1 = 1 &(val>>1);
						//Prendre la valeur du b3 de val
						test_values2 = 1 &(val>>3);
						//Prendre la valeur du b0 de val
						test_values3 = 1 &(val>>0);
						//Prendre la valeur du b1 de Matrix[i-1][0]
						test_values4 = 1 &(maze.Matrix[i-1][j]>>1);		
					//Faire tourner la boucle jusqu'à avoir b1 et b3 de val égales à 1 car il nous faut des murs sur les côtés du labyrinthe et b0 de val soit égal à b1 de Matrix[i-1][0] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines
					}while((test_values1 != 1) || (test_values2 != 1) || (test_values3 != test_values4));
					//Affecter la valeur à Matrix[Lin-1][0]
					maze.Matrix[i][j]=val;	
					
				}
				else if (j == maze.Col-1)
				{
					//Cas Matrix[Lin-1,Col-1]:
					do{
						val = rand()%15;
						//Prendre la valeur du b1 de val
						test_values1 = 1 &(val>>1);
						//Prendre la valeur du b2 de val
						test_values2 = 1 &(val>>2);
						//Prendre la valeur du b0 de val
						test_values3 = 1 &(val>>0);
						//Prendre la valeur du b2 de Matrix[Lin-1][Col-1]
						test_values4 = 1 &(maze.Matrix[i][j-1]>>2);
						//Prendre la valeur du b3 de val
						test_values5 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[Lin-1][Col-1]
						test_values6 = 1 &(maze.Matrix[i-1][j]>>1);
					//Faire tourner la boucle jusqu'à avoir b1 et b2 de val égales à 1 car il nous faut des murs sur les côtés du labyrinthe et b0 de val soit égal à b2 de Matrix[Lin-1][Col-1] et que b3 de val soit égal à b1 de Matrix[Lin-1][Col-1] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines
					}while(((test_values1 != 1) || (test_values2 != 1)) || ((test_values3 != test_values4) || (test_values5 != test_values6)));	
					//Affecter la valeur à Matrix[Lin-1][Col-1]
					maze.Matrix[i][j]=val;
				}
				else
				{
					//Cas Matrix[Lin-1,j]={Matrix[Lin-1,1], .. ,Matrix[Lin-1,j]}:					
					do{
						val = rand()%15;
						//Prendre la valeur du b0 de val
						test_values1 = 1 &(val>>0);
						//Prendre la valeur du b1 de val
						test_values2 = 1 &(val>>1);
						//Prendre la valeur du b2 de Matrix[Lin-1][j-1]
						test_values3 = 1 &(maze.Matrix[i][j-1]>>2);
						//Prendre la valeur du b3 de val
						test_values4 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[Lin-1][j-1]
						test_values5 = 1 &(maze.Matrix[i-1][j]>>1);
					//Faire tourner la boucle jusqu'à avoir b0 de val égal à 1 car il nous faut des murs sur les côtés du labyrinthe et b1 de val soit égal à b2 de Matrix[Lin-1][j-1] et que b3 de val soit égal à b1 de Matrix[Lin-1][j-1] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines
					}while((test_values1 != 1) || (test_values2 != test_values3) || (test_values4 != test_values5));	
					//Affecter la valeur à Matrix[Lin-1][Col-1]
					maze.Matrix[i][j]=val;	
				}
			}
			else
			{
				if(j==0)
				{
					//Cas Matrix[i,j]={Matrix[1,0], .. ,Matrix[Lin-2,0]}:
					do{
						val = rand()%15;
						//Prendre la valeur du b0 de val
						test_values1 = 1 &(val>>0);
						//Prendre la valeur du b3 de val
						test_values2 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[i-1][j]
						test_values3 = 1 &(maze.Matrix[i-1][j]>>1);
					//Faire tourner la boucle jusqu'à avoir b0 de val égal à 1 car il nous faut des murs sur les côtés du labyrinthe et b3 de val soit égal à b1 de Matrix[i-1][j] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines	
					}while((test_values1 != 1) || (test_values2 != test_values3));
					//Affecter la valeur à Matrix[Lin-1][Col-1]
					maze.Matrix[i][j]=val;	
					
				}
				else if (j == maze.Col-1)
				{
					//Cas Matrix[i,j]={Matrix[1,Col-1], .. ,Matrix[Lin-2,Col-1]}:
					do{
						val = rand()%15;
						//Prendre la valeur du b2 de val
						test_values1 = 1 &(val>>2);
						//Prendre la valeur du b0 de val
						test_values2 = 1 &(val>>0);
						//Prendre la valeur du b2 de Matrix[i][j-1]
						test_values3 = 1 &(maze.Matrix[i][j-1]>>2);
						//Prendre la valeur du b3 de val
						test_values4 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[i][j-1]
						test_values5 = 1 &(maze.Matrix[i-1][j]>>1);

					//Faire tourner la boucle jusqu'à avoir b2 de val égal à 1 de car il nous faut des murs sur les côtés du labyrinthe et b0 de val soit égal à b2 de Matrix[i][j-1] et b3 de val soit égal à b1 de Matrix[i][j-1] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines	
					}while((test_values1 != 1) || ((test_values2 != test_values3) || (test_values4 != test_values5)));	
					//Affecter la valeur à Matrix[Lin-1][Col-1]
					maze.Matrix[i][j]=val;
				}
				else
				{	
					//Cas Matrix[i,j] / i={1,..,Lin-2} et j={1,..,Col-2}:					
					do{
						val = rand()%15;
						//Prendre la valeur du b0 de val
						test_values1 = 1 &(val>>0);
						//Prendre la valeur du b2 de Matrix[i][j-1]
						test_values2 = 1 &(maze.Matrix[i][j-1]>>2);
						//Prendre la valeur du b3 de val
						test_values3 = 1 &(val>>3);
						//Prendre la valeur du b1 de Matrix[i-1][j]
						test_values4 = 1 &(maze.Matrix[i-1][j]>>1);
					//Faire tourner la boucle jusqu'à avoir b0 de val égal à b2 de Matrix[i][j-1] et b3 de val soit égal à b1 de Matrix[i-1][j] pour qu'il n'y est pas d'anomalie entre les murs que partagent les cases voisines	
					}while((test_values1 != test_values2) || (test_values3 != test_values4));	
					//Affecter la valeur à Matrix[i][j]
					maze.Matrix[i][j]=val;	
				}		
			}
						
		}
	}
	
	//Choisir la position de l'entrée du labyrinthe aléatoirement
	test_values1 = rand()%maze.Lin;
	test_values2 = rand()%maze.Col;

	//Affecter la valeur de l'entrée à In[2]
	maze.In[0] = test_values1;
	maze.In[1] = test_values2;
	
	//Choisir la position de la sortie du labyrinthe aléatoirement
	//Faire un test pour que le choix de la sortie ne coincide pas avec l'entrée
	do{
		test_values3 = rand()%maze.Lin;
	}while(test_values1 == test_values3);
	
	do{
		test_values4 = rand()%maze.Col;
	}while(test_values2 == test_values4);
	
	//Affecter la valeur de l'entrée à Out[2]
	maze.Out[0] = test_values3;
	maze.Out[1] = test_values4;

	//Affecter la valeur de l'entrée à Find[2] (Positioner le chercheur du chemin à l'entrée
	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];

	return maze;
}

int main ()
{
	srand(time(NULL));   
     
	int i=0,j=0;
	FILE * fp;
	
	//Générer un labyrinthe
	Maze maze = RandMaze1();
	
	//Créer un fichier .txt qui va contenir la structure du labyrinthe
	fp = fopen ("Matrix.txt","w");
	fprintf (fp,"%d %d %d %d %d %d\n", maze.Lin,maze.Col, maze.In[0], maze.In[1], maze.Out[0], maze.Out[1]);

	//Affichage
	printf("%d %d %d %d %d %d\n",maze.Lin,maze.Col, maze.In[0], maze.In[1], maze.Out[0], maze.Out[1]);
	printf("\n");

	
	for(i=0;i<maze.Lin;i++)
	{
			
		for(j=0;j<maze.Col;j++)
		{
			
			printf("%d ",maze.Matrix[i][j]);
			fprintf (fp,  "%d ",maze.Matrix[i][j]);
		}
		printf("\n");
		fprintf (fp,"\n");
	}

	fclose (fp);

	//Liberer l'espace allouer pour le labyrinthe
	free(maze.Matrix);

 return 0;
}
