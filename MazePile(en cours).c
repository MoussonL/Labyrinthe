#include <stdio.h>
#include <time.h>
#include <stdlib.h>



unsigned short  ** matrixVisited;

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


struct node
{
    int data[4];
    struct node* next;
};
 
/*
    init the stack
*/
void init(struct node* head)
{
    head = NULL;
}
 
/*
    push an element into stack
*/
struct node* push(struct node* head,int *data)
{
	//cree un nouve noeud
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
  	if(tmp == NULL)
    {
        exit(0);
    }
    //Remplire le tableau a l'interieru du neoeud avec le tableau qui est en parametre (data)
    tmp->data[0] = data[0];
    tmp->data[1] = data[1];
    tmp->data[2] = data[2];
    tmp->data[3] = data[3];
    
    //pointer sur la tete de la pile
    tmp->next = head;
    // la tete de la pile devient le nouveau noeud
    head = tmp;
    return head;
}
/*
    pop an element from the stack
*/
struct node* pop(struct node *head,int *element)
{
	
    struct node* tmp = head;
    //Recuperer les donnees avant de supprimer le noeud
    element[0] = head->data[0];
    element[1] = head->data[1];
    element[2] = head->data[2];
    element[3] = head->data[3];
    //se position sur l'element suivant
    head = head->next;
    //supprimer le premier element
    free(tmp);
    return head;
}
/*
    returns 1 if the stack is empty, otherwise returns 0
*/
int empty(struct node* head)
{
	//short if
	//if head  == NULL 
	//return  1
	//else  return 0
    return head == NULL ? 1 : 0;
}
 

//Creation du labyrinthe
Maze PerfMaze()
{
	//Declarer une variable pour le labyrinthe
	Maze maze;
	Position p;
	Position *Tab_pos; //Tableau des positions possible pour le choix de Entrée/sortie du labyrinthe
	struct node* head = NULL;
	init(head);
	//Position p;
	int stack[4];
	int stackp[4];
	int tempX,tempY,parentX,parentY;
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
	
	//creation du labyrinthe
	maze.matrix = (unsigned short **) calloc(maze.size[0] , sizeof(unsigned short *));
	for (i=0;i<maze.size[0];i++)
	{
		maze.matrix[i]= (unsigned short *) calloc(maze.size[1] , sizeof(unsigned short));
	}
	
	//creation du labyrinthe (position deja vistee)
	matrixVisited = (unsigned short **) calloc(maze.size[0] , sizeof(unsigned short *));
	for (i=0;i<maze.size[0];i++)
	{
		matrixVisited[i]=(unsigned short *) calloc(maze.size[1] , sizeof(unsigned short));
	}
	
	//Remplir la matrice avec 15 (des murs partout)
	for(i=0;i<maze.size[0];i++)
	{
		for(j=0;j<maze.size[1];j++)
		{
			maze.matrix[i][j]=15;
		}
	}
	//Remplir la matrice visited avec 0( 1- visited 0-no Visited)
	for(i=0;i<maze.size[0];i++)
	{
		for(j=0;j<maze.size[1];j++)
		{
			matrixVisited[i][j]=0;
		}
	}
	
	
			
	//Entree du labyrinthe
	//Creation d'un tableau qui contient les positions possible pour générer une entrée i.e: (i,j)={(0,0),...,(0,size-1),(1,0),...,(size-1,0),(0,size-1),...,(size-1,size-1),(size-1,0),...,(size-1,size-1)} 

	int Tab_size = (maze.size[1] + maze.size[1] + maze.size[0] + maze.size[0])-4;
	Tab_pos = (Position*)calloc( Tab_size , sizeof(Position));
	//Regrouper les postions possible dans un tableau (type position)

	//Remplire le tableau Tab_pos des positions d'entrée possibles (i,j)={(0,0),...,(0,size-1)}
	for(i=0;i<maze.size[1];i++){
		p.x = 0;
		p.y = i;
		Tab_pos[index]=p;
		index++;
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(size-1,0),...,(size-1,size-1)}
	for(i=0;i<maze.size[1];i++){
		p.x = maze.size[0]-1;
		p.y = i;
		Tab_pos[index] = p;
		index++;
		
	}
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,0),...,(size-2,0)}
	for(i=1;i<maze.size[0]-1;i++){
		p.x = i;
		p.y = 0;
		Tab_pos[index]=p;
		index++;
		
	}
	
	
	//Ajouter au tableau Tab_pos les positions d'entrée possibles (i,j)={(1,size-1),...,(size-1,size-1)}
	for(i=1;i<maze.size[0]-1;i++){
		p.x = i;
		p.y = maze.size[1]-1;
		Tab_pos[index]=p;
		index++;
	
	}
	
	//Choisir aléatoirement une position parmis celle du tableau Tab_pos
	int Pos_In= rand()%Tab_size;
	
	
	maze.In[0]=Tab_pos[Pos_In].x;
	maze.In[1]=Tab_pos[Pos_In].y;
	

	int Pos_Out;

	
	//Génération d'une sortie aussi loin possible de l'entrée	
	if(Tab_pos[Pos_In].x == 0){
		do{
			Pos_Out = rand()%Tab_size;
		}while(Tab_pos[Pos_Out].x != maze.size[0]-1);
	}
	else if (Tab_pos[Pos_In].x == maze.size[0]-1){
		do{
			Pos_Out = rand()%Tab_size;
		}while(Tab_pos[Pos_Out].x!= 0);
	}
	else if(Tab_pos[Pos_In].y == 0){
		do{
			Pos_Out= rand()%Tab_size;
		}while(Tab_pos[Pos_Out].y != maze.size[1]-1);
	}else if(Tab_pos[Pos_Out].y == maze.size[1]-1){
		do{
			Pos_Out= rand()%Tab_size;
		}while(Tab_pos[Pos_Out].y != 0);
	}
	//Sortie du labyrinthe
	maze.Out[0] = Tab_pos[Pos_Out].x;
	maze.Out[1] = Tab_pos[Pos_Out].y;

	//Positionner le chercheur à l'entrée
	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];
	
	
	//parcouriir et remplir
	//choisir randomly la position de debut de generation de labyrinthe
	int val= rand()%maze.size[0];
	int val1= rand()%maze.size[1];


	stack[0]=val;
	stack[1]=val1;
	stack[2]=-1;
	stack[3]=-1;
	//relmplir dans la liste le premier element
	head = push(head,stack);
	
	// tantque la pile n'est pas vide
	while(empty(head)!=1)
	{
		//Retirer de la liste le premier element
		head = pop(head,stackp);
		
		tempX=stackp[0];
		tempY=stackp[1];
		parentX=stackp[2];
		parentY=stackp[3];
		
		if(matrixVisited[tempX][tempY]==0)
		{
			//marquer la celulle qu'elle est vistsitee
			matrixVisited[tempX][tempY]=1;
			//tester si ce n'est pas la case parente
			if(parentX!=-1)
			{
				if(parentX-tempX==0 && parentY-tempY>0)
				{
					//case left
					// number ^= (- (0 ou 1) ^ number) & (1UL << (le bit a changer(0,1,2,3)));
					maze.matrix[parentX][parentY] ^= (-0 ^ maze.matrix[parentX][parentY]) & (1UL << 0);
					maze.matrix[tempX][tempY] ^= (-0 ^ maze.matrix[tempX][tempY]) & (1UL << 2); 
				}
				else if(parentX-tempX==0 && parentY-tempY<0)
				{
					//case right
					maze.matrix[parentX][parentY] ^= (-0 ^ maze.matrix[parentX][parentY]) & (1UL << 2);
					maze.matrix[tempX][tempY] ^= (-0 ^ maze.matrix[tempX][tempY]) & (1UL << 0); 
				}
				else if(parentY-tempY==0 && parentX-tempX>0)
				{
					//case up
					maze.matrix[parentX][parentY] ^= (-0 ^ maze.matrix[parentX][parentY]) & (1UL << 3);
					maze.matrix[tempX][tempY] ^= (-0 ^ maze.matrix[tempX][tempY]) & (1UL << 1); 
				}
				else if(parentY-tempY==0 && parentX-tempX<0)
				{
					//case down
					maze.matrix[parentX][parentY] ^= (-0 ^ maze.matrix[parentX][parentY]) & (1UL << 1);
					maze.matrix[tempX][tempY] ^= (-0 ^ maze.matrix[tempX][tempY]) & (1UL << 3); 
				}
			}
			
			//parcourir le voisinage
			//voisinage haut
			if(tempX-1>=0  && matrixVisited[tempX-1][tempY]==0)
			{
				stack[0]=tempX-1;
				stack[1]=tempY;
				stack[2]=tempX;
				stack[3]=tempY;
				head = push(head,stack);
			}
			//voisinage droite
			if(tempY+1<maze.size[1] && matrixVisited[tempX][tempY+1]==0)
			{
				stack[0]=tempX;
				stack[1]=tempY+1;
				stack[2]=tempX;
				stack[3]=tempY;
				head = push(head,stack);
			}
			
			//voisinage bas
			if( tempX+1<maze.size[0] && matrixVisited[tempX+1][tempY]==0)
			{
				stack[0]=tempX+1;
				stack[1]=tempY;
				stack[2]=tempX;
				stack[3]=tempY;
				head = push(head,stack);
			}
			//voisinage gauche
			if(tempY-1>=0 && matrixVisited[tempX][tempY-1]==0)
			{
				stack[0]=tempX;
				stack[1]=tempY-1;
				stack[2]=tempX;
				stack[3]=tempY;
				head = push(head,stack);
			}
			
		}
		
	}
	
	
	return maze;
}

int main ()
{
	srand(time(NULL));   
     
	int i=0,j=0;
	FILE * fp;
	
	//Creation de la matrice
	Maze maze = PerfMaze();

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
