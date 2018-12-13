#include "labyrinthe.h"

int main()
{
	int val = 0;
	int decision=0;
	char* fic_save=(char*)calloc(50,sizeof(char));
	printf("Bonjour, si vous souhaitez un lab a partir d'un fichier tapez 1, un lab aléatoire tapez 2 , un labyrinthe pseudo aléatoire tapez 3\n");
	scanf("%d",&val);
	Maze m;
	switch(val)
	{
		case 1:	//cas fichier
			     
			 
				printf("donnez le nom de votre fichier, sinon tapez non et ce sera un fichier par défaut\n");
				char* fic = (char*)calloc(50,sizeof(char));
				char* s = (char*)calloc(3,sizeof(char));
				s = "non";
				scanf("%s", fic);
			    //fic = ENTREE;
				if (*fic==*s)
				{
				    //fic défaut
				     m = lectFic(ENTREE);
				}
				else
				{
				    //fic donné
					m = lectFic(fic);
				}
				Maze m_fic = m;
				if(m_fic.Lin)//si erreur dans le fichier maze.nblig = 0 sinon !=0 et on entre dans le if
				{
					if(MazeValid(m_fic))//test si le labyrinthe est valide 
					{
						printf("lab valide\n");
						aff(m_fic);
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
		case 2:	//labyrinthe totalement aléatoire
		
		        printf("le labyrinthe va etre généré aléatoirement\n");
				Maze m_alea = MazeRand1();
				aff(m_alea);
				printf("si le lab vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde, 2 sinon\n");
				scanf("%d",&decision);
				if(decision==1)
				{
					scanf("%s",fic_save);
					saveMaze(m_alea,fic_save);//sauvegarde le fichier généré sous le nom donné
				}
				else if(decision==2)
				{
					printf("labyrinthe non sauvegardé\n");
				}
				else
				{
					printf("valeur non reconnue labyrinthe non sauvegardé\n");
				}
				break;
		case 3: //labyrinthe pseudo aléatoire
	        	printf("le labyrinthe va etre généré pseudo aléatoirement\n");
	        	
		        break;
		default: printf("vous n'avez pas entré une des valeurs demandées\n");
	}
	//////faire free ()pour les malloc de Fatma!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return 0;
}
