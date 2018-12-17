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
	int stop=-1;
	while(stop!=0)
	{
		printf("Bonjour, choisissez une option de génération du labyrinthe:\n0- Pour arrêter le programme\n1- D'après un fichier \n2- De façon totalement aléatoire (entrée et sortie aléatoires)\n3- De façon aléatoire (entrée et sortie sur les cotés)\n4-Pour que toutes les cases soient accessibles depuis l'entrée(labyrinthe parfait)\n");
		scanf("%d",&val);
		Maze m;
		Path path;
		switch(val)
		{
			case 0 : stop = 0;break;
			case 1:	//cas fichier
				printf("Donnez le nom de votre fichier avec l'extension .txt, sinon tapez non et ce sera un fichier par défaut\n");
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
				if(m_fic.Lin!=0&&(MazeValid(m_fic))==1)//si erreur ouverture fichier 0 ou validité du fichier == 0
				{
						path = way_search(m_fic);
						dis(m_fic,path);
				}
				else
				{
					printf("labyrinthe non valide\n");
				}
				//Libération mémoire
				/*free(fic);
				free(s);
				printf("erggggeg\n");
				for (int i = 0; i < m.Col-1; ++i)
				{
					free(m.Matrix[i]);
				}
				free(m.Matrix);
				for (int i = 0; i < m.Col-1; ++i)
				{
					free(m_fic.Matrix[i]);
				}
				free(m_fic.Matrix);*/
			break;
			case 2:	//labyrinthe aléatoire (positions de l'entrée/sortie n'importe où dans le labyrinthe
		      	 	printf("le labyrinthe va être généré totalement aléatoirement\n");
				printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalisée\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%35 + 1; 
						size2 = rand()%35 + 1; 
					break;
					case 2: printf("Donnez la taille (n x m) du labyrinthe, attention si n et/ou m superieur à 35 l'affichage ne sera pas cohérent : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				}
				Maze m_alea = MazeRand1(size1,size2);
				printf("%d,%d,%d,%d,%d,%d",m_alea.Lin, m_alea.Col , m_alea.In[0],m_alea.In[1], m_alea.Out[0],m_alea.Out[1]);
				if(MazeValid(m_alea)){
					path = way_search(m_alea);
					dis(m_alea, path);
					printf("si le labyrinthe vous convient tapez 1 pour le sauvegarder et entrez le nom de sauvegarde avec l'extension .txt, 2 sinon\n");
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
				}
				else
				{
				    printf("labyrinthe non valide\n");
				}
				/*for (int i = 0; i < m.Col-1; ++i)
				{
					free(m_alea.Matrix[i]);
				}
				free(m_alea.Matrix);*/
			break;
			case 3: //labyrinthe pseudo-aléatoire (positions de l'entrée/sortie sur les bords du labyrinthe)
	        		printf("le labyrinthe va être généré pseudo-aléatoirement (l'entrée et la sortie seront positionées sur les bords su labyrinthe)\n");
				printf("Chosissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%35 + 1; 
						size2 = rand()%35 + 1; 
					break;
					case 2: printf("Donnez la taille (n x m) du labyrinthe, attention si m>35 l'affichage ne sera pas cohérent  : \n");
						scanf("%d",&size1);
						scanf("%d",&size2);
					break;
				default: break;
				}
				Maze m_alea2 = MazeRand2(size1,size2);
				if(MazeValid(m_alea2)){
				path = way_search(m_alea2);
				dis(m_alea2,path);
				printf("si le labyrinthe vous convient tapez 1 pour le sauvegarder et entrez le nom de sauvegarde avec l'extension .txt, 2 sinon\n");
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
				/*for (int i = 0; i < m.Col-1; ++i)
				{
					free(m_alea2.Matrix[i]);
				}
				free(m_alea2.Matrix);*/
		        break;
		case 4://labyrinthe parfait (pseudo-aléatoire) où toutes les cases sont accessibles.
			    printf("Labyrinthe parfait (toutes les cases sont accessibles)");
			    printf("Choisissez une option: \n1-Taille Random\n2-Taille Personalise\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:	size1 = rand()%35 + 1; 
						size2 = rand()%35 + 1; 
					break;
					case 2: printf("Donnez la taille (n x m) du labyrinthe, attention si m>35 l'affichage ne sera pas cohérent  : \n");
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
				/*for (int i = 0; i < m.Col-1; ++i)
				{
					free(m_pile.Matrix[i]);
				}
				free(m_pile.Matrix);*/
				break;
		default: printf("vous n'avez pas entré une des valeurs demandées\n");
				break;
	}
	//free(fic_save);
}
	return 0;
}
