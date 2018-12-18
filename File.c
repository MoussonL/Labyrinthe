#include "Maze.h"



//Lecture dans un fichier txt
Maze lectFic(char * fic)
{	
	Maze m;
	FILE*flot;
	//test si le fichier s'ouvre bien
	if((flot = fopen(fic,"r"))==NULL)
	{
		printf("impossible de lire le fichier %s \n",fic);
		Maze error;//déclare un lab error
		error.Lin=0;
		return error;
	}
	//scan les valeurs taille entree sortie
	fscanf(flot,"%d %d %d %d %d %d",&m.Lin,&m.Col,&m.In[0],&m.In[1],&m.Out[0],&m.Out[1]);
	//alloue une Matrix a 2 dimensions
	m.Matrix = (unsigned short int**)calloc(m.Col,sizeof(unsigned short int*));
	for(int k = 0; k < m.Col; k++)
	{
		m.Matrix[k]= (unsigned short int*)calloc(m.Lin,sizeof(unsigned short int));
	}
	//remplit les valeurs du tableau avec les valeurs scannées dans le fichier
	for(int i=0;i<m.Lin;i++)
	{
		for(int j=0;j<m.Col;j++)
		{
			fscanf(flot,"%lu",&m.Matrix[i][j]);
		}
	}
	fclose(flot);
	return m;
}


//sauvegarde le labyrinthe m dans le fichier fic_alea
void saveMaze(Maze m, char * fic_alea)
{
	FILE*flot;
	if((flot = fopen(fic_alea,"w+"))==NULL)
	{
		printf("erreur fichier ouverture\n");
	}

	fprintf(flot,"%d %d %d %d %d %d\n",m.Lin,m.Col,m.In[0],m.In[1],m.Out[0],m.Out[1]);
	for (int i = 0; i < m.Lin; ++i)
	{
		for (int j = 0; j < m.Col; ++j)
		{
			fprintf(flot,"%lu ",m.Matrix[i][j]);
		}
		fprintf(flot,"\n");
	}
	fclose(flot);
	
}
