#include "Maze.h"

//Definir la fonction Push qui insert un élément dans la pile
Node* Push(Node* Head,int *Data_In){
	//Créer un nouveau noeud
	Node* Tmp = (Node*)malloc(sizeof(Node)); //Tmp variable temporaire
    //Remplire le tableau à l'interieur du neoeud avec le tableau qui est en paramètre (Data)
    Tmp->Data[0] = Data_In[0];
    Tmp->Data[1] = Data_In[1];
    Tmp->Data[2] = Data_In[2];
    Tmp->Data[3] = Data_In[3];
    
    //Pointer sur la tête de la pile
    Tmp->Next = Head;

    // la tete de la pile devient le nouveau noeud
    Head = Tmp;
    return Head;
}
/*
   La fonction Pop permet de dépiler (extraire) un élément de la pile
*/
Node* Pop(Node *Head,int *Elt) //element
{
	Node* Tmp = Head;
    	//Recuperer les donnees avant de supprimer le noeud
    	Elt[0] = Head->Data[0];
    	Elt[1] = Head->Data[1];
    	Elt[2] = Head->Data[2];
    	Elt[3] = Head->Data[3];

    //se position sur l'élèment suivant
    Head = Head->Next;

    //supprimer (liberer) le premier élèment
    free(Tmp);
    return Head;
}
/*
    Fonction Empty teste le Head si il pointe eur un élémént ou pas 
*/
int Empty(Node* Head)
{
	//short if
	//if head  == NULL 
	//return  1
	//else  return 0
    return Head == NULL ? 1 : 0;
}
 
//La fonction MazePile() génère un labyrinthe pseudo-aléatoire (Les cases sont toutes accécibles => paforcément il y a un chemain et l'entée/sortie sont sur les côté du labyrinthe)
Maze MazePile(int size1, int size2){
	Maze maze;//Déclarer une variable pour le labyrinthe
	Position p;
	Position *Tab_pos; //Tableau des positions possible pour le choix de Entrée/sortie du labyrinthe
	Node* Head = NULL;
	int stack[4];//Tableau temporaire
	int stackp[4];//Tableau temporaire
	int tempX,tempY,parentX,parentY;
	int i=0;
	int j=0;
	int choice;
	int index=0;

	//Initialiser la taille de la matrice
	maze.Lin = size1;
	maze.Col = size2;
	
	//Allocation d'un espace dynamique pour la matrice du labyrinthe
	maze.Matrix = (unsigned short **) calloc(maze.Lin, sizeof(unsigned short *));
	for (i=0;i<maze.Lin;i++)
	{
		maze.Matrix[i]= (unsigned short *) calloc(maze.Col , sizeof(unsigned short));
	}
	
	//Allocation d'un espace dynamique pour la matrice MatrixVisitedqui contient les cases visitées du labyrinthe (maze.Matrix)
	MatrixVisited = (unsigned short **) calloc(maze.Lin , sizeof(unsigned short *));
	for (i=0;i<maze.Lin;i++)
	{
		MatrixVisited[i]=(unsigned short *) calloc(maze.Col , sizeof(unsigned short));
	}
	
	//Remplir la matrice maze.Matrix avec 15 (des murs partout)
	for(i=0;i<maze.Lin;i++)
	{
		for(j=0;j<maze.Col;j++)
		{
			maze.Matrix[i][j]=15;
		}
	}
	//Remplir la matrice MatrixVisited avec 0( 1- visited 0-no Visited)
	for(i=0;i<maze.Lin;i++)
	{
		for(j=0;j<maze.Col;j++)
		{
			MatrixVisited[i][j]=0;
		}
	}
	

	//Choisir aléatoirement une position de début 
	int val= rand()%maze.Lin-1;
	int val1= rand()%maze.Col-1;
	//Initialiser le tableau temporaire stack[4] à la première position où on se positionne la première fois (pas de parent) 
	stack[0]=val;
	stack[1]=val1;
	stack[2]=-1;
	stack[3]=-1;

	//Inserer dans la pile le premier élémént (stack)
	Head = Push(Head,stack);
	/* *************** Création du labyrinthe *************** 
	*/

	// Tantque la pile n'est pas vide
	while(Empty(Head)!=1)
	{
		//Retirer de la liste le premier élément
		Head = Pop(Head,stackp);
		//Récupérer la position actuelle
		tempX=stackp[0];
		tempY=stackp[1];
		//Récupérer la position du parent
		parentX=stackp[2];
		parentY=stackp[3];
		//Tester si la position [tempX][tempY] n'est pas la case parente
		if(MatrixVisited[tempX][tempY]==0)
		{ 
			//Cas: position [tempX][tempY] non visité

			//Marquer la celulle qu'elle vient d'être vistsitée
			MatrixVisited[tempX][tempY]=1;

			//Tester si la position [tempX][tempY] n'est pas la premiere case où on est posisitioné (pas de parent)
			if(parentX!=-1)
			{
				//Cas: au moin une case à été vistée

				if(parentX-tempX==0 && parentY-tempY>0)
				{
					//cas: passage de la case [i][j] à la case [i][j-1]
					//Enlever le mur qui coincide entre les deux cases voisine (b0=0 de la case [i][j] et b2=0 de la case parent [i][j-1])
					maze.Matrix[parentX][parentY] ^= (-0 ^ maze.Matrix[parentX][parentY]) & (1UL << 0);
					maze.Matrix[tempX][tempY] ^= (-0 ^ maze.Matrix[tempX][tempY]) & (1UL << 2); 
				}
				else if(parentX-tempX==0 && parentY-tempY<0)
				{
					//cas: passage de la case [i][j] à la case [i][j+1]
					//Enlever le mur qui coincide entre les deux cases voisine (b0=0 de la case [i][j] et b2=0 de la case parent [i][j+1])
					maze.Matrix[parentX][parentY] ^= (-0 ^ maze.Matrix[parentX][parentY]) & (1UL << 2);
					maze.Matrix[tempX][tempY] ^= (-0 ^ maze.Matrix[tempX][tempY]) & (1UL << 0); 
				}
				else if(parentY-tempY==0 && parentX-tempX>0)
				{
					//cas: passage de la case [i][j] à la case [i-1][j]
					//Enlever le mur qui coincide entre les deux cases voisine (b1=0 de la case [i][j] et b3=0 de la case parent [i-1][j])
					maze.Matrix[parentX][parentY] ^= (-0 ^ maze.Matrix[parentX][parentY]) & (1UL << 3);
					maze.Matrix[tempX][tempY] ^= (-0 ^ maze.Matrix[tempX][tempY]) & (1UL << 1); 
				}
				else if(parentY-tempY==0 && parentX-tempX<0)
				{
					//cas: passage de la case [i][j] à la case [i+1][j]
					//Enlever le mur qui coincide entre les deux cases voisine (b3=0 de la case [i][j] et b1=0 de la case parent [i-1][j])
					maze.Matrix[parentX][parentY] ^= (-0 ^ maze.Matrix[parentX][parentY]) & (1UL << 1);
					maze.Matrix[tempX][tempY] ^= (-0 ^ maze.Matrix[tempX][tempY]) & (1UL << 3); 
				}
			}
			
			/* Parcourir le voisinage de la actuelle
                         */

			//voisinage du haut (il y a une case voisine au dessus de la case actuelle
			if(tempX-1>=0  && MatrixVisited[tempX-1][tempY]==0) //Verifier si la case voisine elle n'a pas été visitée
			{
				//Récupérer la position de la case voisine
				stack[0]=tempX-1;
				stack[1]=tempY;
				//Récupérer la position de la case actuelle
				stack[2]=tempX;
				stack[3]=tempY;
				//Inserer stack[4] dans la pile
				Head = Push(Head,stack);
			}
			//voisinage de droite (il y a une case voisine à droite de la case actuelle
			if(tempY+1<maze.Col && MatrixVisited[tempX][tempY+1]==0)//Verifier si la case voisine elle n'a pas été visitée
			{
				//Récupérer la position de la case voisine
				stack[0]=tempX;
				stack[1]=tempY+1;
				//Récupérer la position de la case actuelle
				stack[2]=tempX;
				stack[3]=tempY;
				//Inserer stack[4] dans la pile
				Head = Push(Head,stack);
			}
			
			//voisinage du bas (il y a une case voisine au dessous de la case actuelle
			if( tempX+1<maze.Lin && MatrixVisited[tempX+1][tempY]==0)//Verifier si la case voisine elle n'a pas été visitée
			{	
				//Récupérer la position de la case voisine
				stack[0]=tempX+1;
				stack[1]=tempY;

				//Récupérer la position de la case actuelle
				stack[2]=tempX;
				stack[3]=tempY;
				//Inserer stack[4] dans la pile
				Head = Push(Head,stack);
			}
			//voisinage à gauche (il y a une case voisine à gauche de la case actuelle
			if(tempY-1>=0 && MatrixVisited[tempX][tempY-1]==0)
			{
				//Récupérer la position de la case voisine
				stack[0]=tempX;
				stack[1]=tempY-1;
				//Récupérer la position de la case actuelle
				stack[2]=tempX;
				stack[3]=tempY;
				//Inserer stack[4] dans la pile
				Head = Push(Head,stack);
			}
			
		}
		
	}
	
	/*
	 *************** Génération de l'entrée/sortie du labyrinthe ***************
	*/
	
	//Creation de tableau Tab_pos qui contient les positions (contour du labyrinthe) i.e Matrix[i][j] = {Matrix[0][0],Matrix[0][1],...,Matrix[0][Col-1], Matrix[1][0],Matrix[2][0],...,Matrix[Lin-1][0], Matrix[Lin-1][1],Matrix[Lin-1][2],...,Matrix[Lin-1][Col-1], Matrix[1][Col-1],Matrix[2][Col-1],...,Matrix[Lin-2][Col-1]:

	int Tab_size = (maze.Lin + maze.Lin + maze.Col + maze.Col)-4;//Dimension de Tab_pos
	//Allocation d'un espace dynamique pour le tableau de position
	Tab_pos = calloc( Tab_size , sizeof(Position));

	//Remplire le tableau Tab_pos par les positions Matrix[0][0],Matrix[0][1],...,Matrix[0][Col-1]
	for(i=0;i<maze.Col;i++){
		p.X = 0;
		p.Y = i;
		Tab_pos[index]=p;
		index++;
	}
	
	//Remplire le tableau Tab_pos par les positions Matrix[Lin-1][0],...,Matrix[Lin-1][Col-1]
	for(i=0;i<maze.Col;i++){
		p.X = maze.Lin-1;
		p.Y = i;
		Tab_pos[index] = p;
		index++;
		
	}
	
	//Remplire le tableau Tab_pos par les positions Matrix[1][0],...,Matrix[Lin-2][0]
	for(i=1;i<maze.Lin-1;i++){
		p.X = i;
		p.Y = 0;
		Tab_pos[index]=p;
		index++;
		
	}
	
	
	//Remplire le tableau Tab_pos par les positions Matrix[1][Col-1],...,Matrix[Lin-2][Col-1]
	for(i=1;i<maze.Lin-1;i++){
		p.X = i;
		p.Y = maze.Col-1;
		Tab_pos[index]=p;
		index++;
	
	}
	
	int L = ((maze.Lin)-1);
	int C = ((maze.Col)-1);
	int S = ((Tab_size)-1);
	int Pos_In;
	int Pos_Out;
	//Choisir aléatoirement une position parmis celle du tableau Tab_pos
	Pos_In= (rand()%S);
	
	//Affecter la valeur de l'entrée à In[2]
	maze.In[0]=Tab_pos[Pos_In].X;
	maze.In[1]=Tab_pos[Pos_In].Y;
	

	

	
	//Génération d'une sortie aussi loin possible de l'entrée	
	if(Tab_pos[Pos_In].X == 0){
		do{
			Pos_Out =(rand()%S);
		}while(Tab_pos[Pos_Out].X != L);
	}
	else if (Tab_pos[Pos_In].X == L){
		do{
			Pos_Out = (rand()%S);
		}while(Tab_pos[Pos_Out].X!= 0);
	}
	else if(Tab_pos[Pos_In].Y == 0){
		do{
			Pos_Out= (rand()%S);
		}while(Tab_pos[Pos_Out].Y != C);
	}else if(Tab_pos[Pos_Out].Y == C){
		do{
			Pos_Out= (rand()%S);
		}while(Tab_pos[Pos_Out].Y != 0);
	}
	//Affecter la valeur de la sortie à Out[2]
	maze.Out[0] = Tab_pos[Pos_Out].X;
	maze.Out[1] = Tab_pos[Pos_Out].Y;

	//Affecter la valeur de l'entrée à Find[2] (Positioner le chercheur du chemin à l'entrée
	maze.Find[0] = maze.In[0];
	maze.Find[1] = maze.In[1];
	
	return maze;

}
