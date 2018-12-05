#include "labyrinthe.h"

int main()
{
	int val = 5;
	int decision=5;
	char* fic_save;
	printf("Bonjour, si vous souhaitez un lab a partir d'un fichier tapez 1, un lab aléatoire tapez 2 \n");
	scanf("%d",&val);
	Maze m;
	switch(val)
	{
		case 1:	//cas fichier
				printf("donnez le nom de votre fichier, sinon tapez 'non' et ce sera un fichier par défaut\n");
				char* fic = ENTREE;
				char* s = "non";
				scanf("%s",fic);
				if (fic==s)
				{
					Maze m = lectFic(ENTREE);
				}
				else
				{
					Maze m = lectFic(fic);
				}
				Maze m_fic = m;
				if(m_fic.Lin)//si erreur dans le fichier maze.nblig = 0 sinon !=0 et on entre dans le if
				{
					if(MazeValid(m_fic))//test si le labyrinthe est valide 
					{
						printf("lab valide\n");
						/////////////////afficher le lab du fichier donné ou par défaut !!!!!!!!!!
					}
					else
					{
						printf("lab non valide\n");
					}
				}
				//libération de la mémoire allouée
				for(int i = 0; i<m_fic.Col;i++)
				{
					free(m_fic.Matrix[i]);
				}
				free(m_fic.Matrix);
		break;
		case 2:	printf("le labyrinthe va etre généré aléatoirement\n");
				/////Maze m_alea = //lab aléa donné par Fatma
				printf("si le lab vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde, 0 sinon\n");
				scanf("%d",&decision);
				if(decision==1)
				{
					scanf("%s",fic_save);
					///saveMaze(m_alea,fic_save);//sauvegarde le fichier généré sous le nom donné
				}
				else if(decision==0)
				{
					printf("labyrinthe non sauvegardé\n");
				}
				else
				{
					printf("valeur non reconnue labyrinthe non sauvegardé\n");
				}
				break;
		
		default: printf("vous n'avez pas entré une des valeurs demandées\n");
	}
	//////faire free ()pour les malloc de Fatma!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return 0;
}
