#include "Maze.h"

int main()
{
	int val = 0;
	int decision=0;
	int size1;
	int size2;
	int choice;
	srand(time(NULL)); 
	char* fic_save=(char*)calloc(50,sizeof(char));
	printf("Bonjour, choisissez une option de génération du labyrinthe:\n1- d'après un fichier \n2- de façon totalement aléatoire\n3- de façon pseudo aléatoire\n4-avec des piles (toutes les cases accessibles depuis l'entrée)\n");
	scanf("%d",&val);
	Maze m;
	Path path;
	switch(val)
	{
		case 1:	//cas fichier
				printf("donnez le nom de votre fichier avec l'extension .txt, sinon tapez non et ce sera un fichier par défaut\n");
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
						printf("labyrinthe valide\n");
						path = way_search(m_fic);
						dis(m_fic,path);
					}
					else
					{
						printf("labyrinthe non valide\n");
					}
				}
		break;
		case 2:	//labyrinthe totalement aléatoire
		
		       		printf("le labyrinthe va être généré aléatoirement\n");
				printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%32767 + 1; 
						size2 = rand()%32767 + 1; 
					break;
					case 2: printf("Donnez la taille (n x m)<35 du labyrinthe : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				}
				Maze m_alea = MazeRand1(size1,size2);
				if(MazeValid(m_alea)){
				path = way_search(m_alea);
				dis(m_alea, path);
				printf("si le labyrinthe vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde avec l'extension .txt, 2 sinon\n");
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
					printf("valeur non reconnue : labyrinthe non sauvegardé\n");
				}
				}else
				{
				    printf("labyrinthe non valide\n");
				}
				break;
		case 3: //labyrinthe pseudo aléatoire
	        	printf("le labyrinthe va être généré pseudo-aléatoirement\n");
			printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%32767 + 1; 
						size2 = rand()%32767 + 1; 
					break;
					case 2: printf("Donnez la taille (n x m)<35 du labyrinthe : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				default: break;
				}
				Maze m_alea2 = MazeRand2(size1,size2);
				if(MazeValid(m_alea2)){
				path = way_search(m_alea2);
				dis(m_alea2,path);
				printf("si le labyrinthe vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde avec l'extension .txt, 2 sinon\n");
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
					printf("valeur non reconnue : labyrinthe non sauvegardé\n");
				}
				}else{printf("labyrinthe non valide\n");}
		        	break;
		case 4://labyrinthe avec pile pour que toutes les cases soit accessibles depuis l'entrée
			    printf("Labyrinthe généré avec des piles pour que toutes les cases soient accessibles");
			    printf("Choisissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%32767 + 1; 
						size2 = rand()%32767 + 1; 
					break;
					case 2: printf("Donnez la taille (n x m)<35 du labyrinthe : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				}
			    Maze m_pile = MazePile(size1,size2);
			if(MazeValid(m_pile)){
			    path = way_search(m_pile);
			    dis(m_pile, path);
			    printf("si le labyrinthe vous convient tapez 1 pour sauvegarder et entrez le nom de sauvegarde avecl'extension  .txt, 2 sinon\n");
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
					printf("valeur non reconnue : labyrinthe non sauvegardé\n");
				}
			}else{printf("labyrinthe non valide\n");}
				break;
		default: printf("vous n'avez pas entré une des valeurs demandées\n");
				break;
	}



	return 0;
}
