#include "labyrinthe.h"

int main()
{
	int val = 0;
	int decision=0;
	int size1;
	int size2;
	int choice;
	srand(time(NULL)); 
	char* fic_save=(char*)calloc(50,sizeof(char));
	printf("Bonjour, si vous souhaitez un lab a partir d'un fichier tapez 1, un lab aléatoire tapez 2 , un labyrinthe pseudo aléatoire tapez 3\n");
	scanf("%d",&val);
	Maze m;
	Path path;
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
						path = way_search(m_fic);
						aff(m_fic,path);
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
				printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%100 + 1; 
						size2 = rand()%100 + 1; 
					break;
					case 2: printf("Donner la taille (n x m) du labyrinthe : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				default: break;
				}
				Maze m_alea = MazeRand1(size1,size2);
				if(MazeValid(m_alea)){
				path = way_search(m_alea);
				aff(m_alea, path);
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
				}else
				{
				    printf("erreur validité");
				}
				free(m_alea.Matrix);
				break;
		case 3: //labyrinthe pseudo aléatoire
	        	printf("le labyrinthe va etre généré pseudo aléatoirement\n");
			printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%100 + 1; 
						size2 = rand()%100 + 1; 
					break;
					case 2: printf("Donner la taille (n x m) du labyrinthe : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				default: break;
				}
				Maze m_alea2 = MazeRand2(size1,size2);
				path = way_search(m_alea2);
				aff(m_alea2,path);
				printf("si le lab vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde, 2 sinon\n");
				scanf("%d",&decision);
				if(decision==1)
				{
					scanf("%s",fic_save);
					saveMaze(m_alea2,fic_save);//sauvegarde le fichier généré sous le nom donné
				}
				else if(decision==2)
				{
					printf("labyrinthe non sauvegardé\n");
				}
				else
				{
					printf("valeur non reconnue labyrinthe non sauvegardé\n");
				}
				free(m_alea2.Matrix);
		        	break;
		case 4://labyrinthe avec pile pour que toutes les cases soit accessibles depuis l'entrée
			    printf("Labyrinthe généré avec des piles pour que toutes les cases soient accessibles");
			    printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%100 + 1; 
						size2 = rand()%100 + 1; 
					break;
					case 2: printf("Donner la taille (n x m) du labyrinthe : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				default: break;
				}
			    Maze m_pile = MazePile(size1,size2);
			    path = way_search(m_pile);
			    aff(m_pile, path);
			    printf("si le lab vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde, 2 sinon\n");
				scanf("%d",&decision);
				if(decision==1)
				{
					scanf("%s",fic_save);
					saveMaze(m_pile,fic_save);//sauvegarde le fichier généré sous le nom donné
				}
				else if(decision==2)
				{
					printf("labyrinthe non sauvegardé\n");
				}
				else
				{
					printf("valeur non reconnue labyrinthe non sauvegardé\n");
				}
				free(m_pile.Matrix);
		default: printf("vous n'avez pas entré une des valeurs demandées\n");
	}
	
	//Liberer l'espace allouer pour le labyrinthe
	free(m.Matrix);

	return 0;
}
