
#include "Maze.h"

//Prends un entier et un tableau de 16 éléments et remplit le tableau avec sa base 2 tab[0]=bit poids faible
int* itob(int a, int * T)
{
	//initialise T à 0
	for (int i = 0; i < 16; ++i)
	{
		T[i]=0;
	}
	int i = 0;
	while(a!=0&&i<16)
	{
		if(a==0&&i<16)//remplit toutes les cases restantes à 0 
		{
			T[i]=0;
		}
		if(a!=0&&i<16)
		{
			T[i]=a%2;
			if(T[i]!=0)
			{
				a=(int)a/2;
			}
			else
			{
				a=a/2;
			}
		}
		i++;
	}
	return T;
}


int MazeValid(Maze m)
{
	//test validité entree sortie<taille

	if((m.In[0]<0)||(m.In[0]>m.Lin-1)||(m.In[1]<0)||(m.In[1]>m.Col-1))
	{
		if((m.Out[0]<0)||(m.Out[0]>m.Lin-1)||(m.Out[1]<0)||(m.Out[1]>m.Col-1))
		{
			printf("index entree/sortie faux : erreur %d %d entree %d %d sortie %d ligne %d col !!\n", m.In[0], m.In[1], m.Out[0], m.Out[1],m.Lin, m.Col);
			return 0;
		}
	}
	//test entree!=sortie
	if(m.In[0]==m.Out[0]&&m.In[1]==m.Out[1])
	{
		printf("entree == sortie erreur !! \n);
		       return 0;
	}
		
		

	//test correspondance murs
	int *case_courante = (int *)calloc(16,sizeof(int));
	int * case_courante_2 = (int*)calloc(16,sizeof(int));
	int* case_courante_3=(int*)calloc(16,sizeof(int));
	int* case_courante_4=(int*)calloc(16,sizeof(int));

	for(int i = 0; i<m.Lin; i++)
	{
		for(int j=0; j<m.Col-1;j++)
		{
			case_courante = itob(m.Matrix[i][j],case_courante);
			case_courante_2 = itob(m.Matrix[i][j+1],case_courante_2);//case2 a doite de case courante
			if(case_courante[2]!=case_courante_2[0])//test les murs de droite de case c et de gauche de case c2 correspondent
			{
				printf("droite gauche %d %d %d %d\n",case_courante[2],case_courante_2[0],i,j);
				return 0;//un mur n'est pas valide
			}
		}
	}
	for(int i = 0; i<m.Lin-1; i++)
	{
		for(int j=0; j<m.Col;j++)
		{
			case_courante_3 = itob(m.Matrix[i][j],case_courante_3);
			case_courante_4 = itob(m.Matrix[i+1][j],case_courante_4);//case_4 en dessous de case c3
			if(case_courante_3[1]!=case_courante_4[3])//test les murs de bas de case c et de haut de case c2 correspondent
			{
				printf("haut bas %d %d %d %d\n",case_courante_3[1],case_courante_4[3],i,j);
				return 0;//un mur n'est pas valide
			}
		}
	}
	//libération mémoire
	free(case_courante);
	free(case_courante_2);
	free(case_courante_3);
	free(case_courante_4);
	return 1;
}
