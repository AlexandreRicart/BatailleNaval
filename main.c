#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* \Title :  BATAILLE NAVAL VERSION
* \Type:    Jeux de la bataille naval vs IA
* \author:  Alexandre Ricart
* \version: 1.0 (final)
* \date:    23.01.2020
*/

//Valeur maximum a saisir dans le tableau
#define AXEMAX_X 10
#define AXEMAX_Y 10
//Valeur minimum a saisir dans le tableau
#define MIN 1
//Chemin par defaut
#define PATH_GRILLE "fichiers_jeux\\grilles\\GRILLES"
#define PATH_SCORES "fichiers_jeux\\resultats\\RES.txt"
#define PATH_LOGS "fichiers_jeux\\resumes\\LOGS.txt"
//Nbre de grille
#define NBR_GRILLES 4
//Nbre de caractäre maximum pour le pseudo
#define CHARMAX 10
//Nbre de score max a enregistrer
#define SCOREMAX 5

//Calcul les points + total
int total = 0;
//CDW = Condition de victoire
int cdw = 0;

char grilleJ[AXEMAX_X][AXEMAX_Y];

char grilleNPC[AXEMAX_X][AXEMAX_Y];

//Grille de tableau a l'affichage 10/10
char historique[AXEMAX_X][AXEMAX_Y]=
{
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};

/**
    Grille
    @param Parcours un tableau, permet d'afficher le tableau Historique qui est vide de base mais permet au joueur de visionner ses positions de tirs.
*/
void Grille()
{
    int h,i,j;

    //Sert afficher un tableau comprehensible pour le joeur
    printf("\n");
    printf("  X\n");
    printf("Y :");
    for(h = 0; h < AXEMAX_X; ++h)
    {
        printf("  %d",h + 1);
    }
    printf("\n");
    for(i = 0; i < AXEMAX_X; ++i)
    {
        printf(" %2d ",i + 1);
        for(j = 0; j < AXEMAX_X; ++j)
        {
            //Affiche la grille historique aux positions de i et de j.
            printf("[%c]",historique[i][j]);
        }
        printf("\n");

    }
}

/**
    Solution
    @param Parcours un tableau, affiche le tableau de l'IA.
*/
void Solution()
{
    int h,i,j;

    //Sert afficher un tableau comprehensible pour le joeur
    printf("\n");
    printf("  X\n");
    printf("Y :");
    for(h = 0; h < AXEMAX_X; ++h)
    {
        printf("  %d",h + 1);
    }
    printf("\n");
    for(i = 0; i < AXEMAX_X; ++i)
    {
        printf(" %2d ",i + 1);//Trouve une valeur random de 0 G«™ 9
        for(j = 0; j < AXEMAX_X; ++j)
        {
            //Affiche la grille de l'IA aux positions de i et de j.
            printf("[%c]",grilleNPC[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
    Tir
    @param Selon le tour du joueur, affiche si ce dernier a toucher ou louper un bateau, modifie la valeur de B (pour bateau) en S (pour sombree ou coulee) dans la grille de l'adversaire et permet de rejouer.
*/
int Tir(int Tour,int X,int Y, char nomjoueur[CHARMAX])
{
    //Tout les tours pairs, le joueur joue
    if(Tour % 2 == 0)
    {
        //ecrire dans le fichier
        Enregistrements_partie(Tour,X,Y, nomjoueur);
        //Selon la grille de l'IA
        switch(grilleNPC[X][Y])
        {
        case 'W':
            historique[X][Y] = 'O';
            printf("Louper pour %s\n", nomjoueur);
            //Ne peux pas rejouer
            return 0;
        case 'S':
            printf("Deja touche par %s\n", nomjoueur);
            //Ne peux pas rejouer
            return 0;
        case 'T':
        case 'A':
        case 'C':
            printf("Touche pour %s\n", nomjoueur);
            //Modifie la valeur B en S (le bateau est touche a cette position)
            grilleNPC[X][Y] = 'S';
            //Affiche un X dans la grille historique a la position X et Y
            historique[X][Y] = 'X';
            //permet au joueur de rejouer
            return 1;
        }
    }
    //Tout les tours impairs, l'IA joue
    else if(Tour % 2 != 0)
    {
        Enregistrements_partie(Tour,X,Y, nomjoueur);
        //Selon la grille du Joueur
        switch(grilleJ[X][Y])
        {
        case 'W':
            printf("Louper pour le NPC\n");
            //Ne peux pas rejouer
            return 0;
        case 'S':
            printf("Deja touche par le NPC\n");
            //Ne peux pas rejouer
            return 0;
        case 'T':
        case 'A':
        case 'C':
            printf("Touche pour le NPC\n");
            //Modifie la valeur B en S (le bateau est touche a cette position)
            grilleJ[X][Y] = 'S';
            //permet a l'IA de rejouer
            return 1;
        }
    }
}

/**
    Enregistrements_scores
    @param Enregistre dans un fichier RES.txt (resultat) les scores des 5 dernieres parties
*/
void Enregistrements_scores(){


	FILE* fichier = NULL;
	int scoretab[SCOREMAX] = {0};

    //ecrire lires les 5 derniers scores
	fichier = fopen(PATH_SCORES, "r");
	for(int i = 0; i < 5; i++)
	{
        //enregistrer les scores des parties prÇcÇdentes
		fscanf(fichier, "%d ", &scoretab[i]);
		//afficher les scores des parties prÇcÇdentes
		printf("Les meilleurs scores sont : %d\n", scoretab[i]);
	}

	fclose(fichier);

	for(int i = 5; i > 0; i--)
	{
	    //ecraser le derniers scores lorsque le 6äme scores prend la place du premier.
		scoretab[i] = scoretab[i-1];
	}
	scoretab[0] = total;

	fichier = fopen(PATH_SCORES, "w+");

	for(int i = 0; i < 5; i++)
	{
        //afficher le nouveau tableau des scores.
		fprintf(fichier, "%d ",scoretab[i]);
	}

	fclose(fichier);

}

/**
    Enregistrements_findepartie
    @param Enregistre dans un fichier LOGS.txt le gagnant de la partie, il donne egalement son total de point.
*/
void Enregistrements_findepartie(int tour, char nomjoueur[CHARMAX],int total){

    FILE* fichier = NULL;

    if(tour % 2 == 0)
    {
        fichier = fopen(PATH_LOGS, "a+");
        if (fichier != NULL)
        {
            fprintf(fichier,"Victoire de %s avec %d pts\n", nomjoueur, total);
            fclose(fichier);

        }
    }else{
        fichier = fopen(PATH_LOGS, "a+");
        if (fichier != NULL)
        {
            fprintf(fichier,"Defaite de %s avec %d pts\n", nomjoueur, total);
            fclose(fichier);
        }
    }
}

/**
    Enregistrements_partie
    @param Enregistre dans un fichier LOGS.txt les evenement de la bataille naval des 2 joueurs.
*/
void Enregistrements_partie(int tour, int X,int Y, char nomjoueur[CHARMAX])
{
    FILE* fichier = NULL;

    if(tour % 2 == 0)
    {
        switch(grilleNPC[X][Y])
        {
        case 'W':
            //permet a l'utilisateur de quitter l'appliquation sans faire beuger l'ajout de la phrase dans le programme.
            //Cette methode a ete repete pour tous les cases.
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"%s ordonne un tir en position %d %d, c est tombe a l eau.\n", nomjoueur, X, Y);
                fclose(fichier);

            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'S':
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"%s ordonne un tir en position %d %d, c est deja touche.\n", nomjoueur, X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'T':
            total = total + 3;
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"*BOUM* %s touche un torpilleur en position %d %d, +3pts.\n", nomjoueur, X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'A':
            total = total + 1;
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"*BOUM* %s touche un porte avion en position %d %d, +1pts.\n", nomjoueur, X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'C':
            total = total + 2;
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"*BOUM* %s touche un croiseur en position %d %d, +2pts.\n", nomjoueur, X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        }
    }
    else
    {
        switch(grilleJ[X][Y])
        {
        case 'W':
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"L ordinateur ordonne un tir en position %d %d, c est tombe a l eau.\n", X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'S':
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"L ordinateur ordonne un tir en position %d %d, c est deja touche.\n", X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'T':
            total = total - 3;
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"*BOUM* L ordinateur touche un torpilleur en position %d %d, -3pts.\n", X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'A':
            total = total - 1;
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"*BOUM* L ordinateur touche un porte avion en position %d %d, -1pts.\n", X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        case 'C':
            total = total - 2;
            fichier = fopen(PATH_LOGS, "a+");
            if (fichier != NULL)
            {
                fprintf(fichier,"*BOUM* L ordinateur touche un croiseur en position %d %d, -2pts.\n", X, Y);
                fclose(fichier);
            }
            else
            {
                printf("requet impossible.\n");
            }
            break;
        }
    }
}

/**
    Condition_Victoire
    @param Selon le tour des joueurs, va constater s'il reste encore un bateau dans la grille adverse. Si c'est le cas, alors la partie n'est pas encore finie.
*/
int Condition_Victoire(int Tour)
{
    int i,j;


    if(Tour % 2 == 0)
    {
        //Tour du joueur
        for(i = 0; i < AXEMAX_X; ++i)
        {
            for(j = 0; j < AXEMAX_X; ++j)
            {
                //Selon la grille NPC, s'il reste encore un bateau retourne 0, la partie continue.
                if( grilleNPC[i][j] == 'T' || grilleNPC[i][j] == 'A' || grilleNPC[i][j] == 'C')
                {
                    return 0;
                }
            }
        }

    }
    else if(Tour % 2 != 0)
    {
        //Tour du NPC
        for(i = 0; i < AXEMAX_X; ++i)
        {
            for(j = 0; j < AXEMAX_X; ++j)
            {
                //Selon la grille du Joueur, s'il reste encore un bateau retourne 0, la partie continue.
                if( grilleJ[i][j] == 'T' || grilleJ[i][j] == 'A' || grilleJ[i][j] == 'C')
                {
                    return 0;
                }
            }
        }
    }
    //Il y a un vainqueur
    return 1;
}

/**
    Validation
    @param Valide si les donnees sont bien inferieur a la taille maximum et superieur a la taille minimum du tableau, sinon demande de ressaisir la donnee
*/
int Validation()
{
    int val;
    //Tant que la valeur est inferieur G«™ la valeur minimum ou superieur a la valeur maxium, affiche un message d'erreur
    do
    {
        //Vider la memoire cach et saisir une nouvelle valeur
        fflush(stdin);
        scanf("%d",&val);

    }
    while((val < MIN || val >AXEMAX_X) && printf("Erreur, la valeur doit etre entre 1 et 10\nFaite aussi attention au caracteres qui ne sont pas pris par le systeme.\n"));

    //Val N - 1, donc Val - 1 afin de saisir des valeurs entre 1 et 10.
    return val - 1;
}

/**
    Menu
    @param Affiche le menu du debut de jeu, et demande le choix du joueur
*/
int Menu()
{
    int valeur;

    printf("Bienvenu dans la bataille navale:\n");
    printf("Menu:\n");
    printf("\n\n");
    printf("1 - Jouer\n");
    printf("2 - Les_Regles\n");
    printf("3 - Quitter\n");
    printf("\n");
    scanf("%d",&valeur);

    return valeur;
}

/**
    Error
    @param Empeche le programme de tourne en boucle si l'utilisateur ne rentre pas les donnees correctes, redemande a l'utilisateur de saisir une donnee s'il s'est trompee.
*/
int Error()
{

    int val;

    //Effacer l'ancien message.
    system("CLS");
    printf("Error - Veuillez choisir entre 1 et 3 svp \n");
    //Vider la memoire cach et saisir une nouvelle valeur
    fflush(stdin);
    scanf("%d", &val);

    return val;
}

/**
    Regles
    @param Affiche les regles du jeu.
*/
void Regles()
{
    printf("\n**************************************\n");
    printf("Les regles de jeux sont simples :\n");
    printf("- Vous allez jouer contre un ordinateur et vous commencer en premier.\n");
    printf("- Les navires sont deja places, si vous trouvez tous les bateaux adverses vous gagnez, sinon vous perdez.\n");
    printf("- Si vous loupez un tir, le system vous proposera une solution montrant la grille des bateaux de l'ordinateur\n");
    printf("\n\nA l'affichage:\n");
    printf("- O: signifie que vous avez loupe\n");
    printf("- X: signifie que vous avez touche\n");
    printf("- Suite a vos tirs et de ceux de l'IA un commentaire indiquera si un bateau est touche ou non.\n  Si quelqu'un touche, il a la possibilite de rejouer.\n");
    printf("\n");
    printf("Bonne chance! :D\n");
    printf("\n");
    printf("**************************************\n");
}

/**
    RecuperationGrille
    @param lire le contenu d'un fichier GRILLE.txt
*/
void RecuperationGrille(char *path, char grille[AXEMAX_X][AXEMAX_Y])
{

    FILE* fichier = NULL;

    //lire le fichier s'il existe
    fichier = fopen(path, "r");
    if (fichier != NULL)
    {
        char caractere;
        int i = 0;
        int j = 0;

        //Tant qu'il n'y arrive pas ‡ la fin du fichier
        while(caractere != EOF)    // EOF = End Of File
        {
            //lire caractere par caractere
            caractere = fgetc(fichier);
            switch(caractere)
            {
            case 'T':
            case 'A':
            case 'C':
            case 'W':
                grille[i][j] = caractere;
                if(j == AXEMAX_Y-1)
                {
                    i += 1;
                    j = 0;
                }
                else
                {
                    j += 1;
                }
                break;
            default:
                break;
            }
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier contenant la grille.");
    }
}

/**
    GrilleAttribue
    @param Va inscrire le contenu d'une grille random (entre les 4 grilles possibles), 1 pour le joueur et 1 pour le NPC
*/
void GrilleAttribue(char pseudo[CHARMAX])
{

    int randomJ = 0;
    int randomNPC = 0;
    int taille = strlen(PATH_GRILLE) + 10;
    char path[taille];

    //Choisir une GRILLE aleatoire
    randomJ = rand() % NBR_GRILLES + 1;
    randomNPC = rand() % NBR_GRILLES + 1;

    //Lire les donnees √  mettre dans la grille du joueur
    printf("Grille de jeu attribuee a %s:", pseudo);
    snprintf(path,taille,"%s%d%s",PATH_GRILLE,randomJ,".txt");
    printf("\n%s", path);
    RecuperationGrille(path, grilleJ);
    printf("\n");
    //Lire les donnees √  mettre dans la grille du NPC
    printf("Grille de jeu attribuee au NPC:");
    snprintf(path,taille,"%s%d%s",PATH_GRILLE,randomNPC,".txt");
    printf("\n%s", path);
    RecuperationGrille(path, grilleNPC);
}

/**
    NomJoueur
    @param va lire caractere par caractere et inscrire dans un tableau pseudo le nom du joueur
*/
void NomJoueur(char *pseudo)
{
    char validation = 'n';

    printf("Bonjour, comment vous nommez-vous ?\nATTENTION 10 CARACTERES MAX!\n");

    while(validation != 'y')
    {
        printf("Entrez votre nom: \n");
        scanf("%s", pseudo);
        printf("Vous vous nommez %s ? (y pour oui, n pour non) ", pseudo);
        fflush(stdin);
        scanf("%c", &validation);
        //tant que la reponse est differente de 'n' ou 'y', affiche un message d erreur
        if(validation != 'n' && validation != 'y')
        {
            system("CLS");
            fflush(stdin);
            printf("Erreur, veuillez respecter la demande precedente!\n taper y pour oui ou n pour non!");
        }
    }

    system("CLS");
}

int main()
{
    int tour = 0;
    int touche;
    int validation;
    int x = 0;
    int y = 0;
    int choix;
    int choix2;
    //Triche = affiche la grille du NPC
    char triche;
    //initialiser un temps t
    time_t t;

    FILE* fichier = NULL;

    //Initialiser le NPC ou L'IA selon l'heure du temps
    srand((unsigned) time(&t));

    char pseudo[CHARMAX];

    choix = Menu();
    system("CLS");

    while(choix != 3)
    {
        switch(choix)
        {
        case 1:

            //vider le fichier LOGS de la partie precedente avant le debut de la nouvelle partie
            fichier = fopen(PATH_LOGS, "w+");
            fclose(fichier);

            //Initialiser au debut du jeu la grille du NPC et celui du joueur
            NomJoueur(&pseudo);
            GrilleAttribue(pseudo);

            while(cdw != 1)
            {
                if(tour % 2 == 0)
                {
                    printf("\n");
                    //Tour du joueur
                    Grille();
                    printf("\nTir_X : ");
                    x = Validation();
                    printf("Tir_Y : ");
                    y = Validation();
                    printf("\n");
                    touche = Tir(tour,x,y,pseudo);
                    cdw = Condition_Victoire(tour);
                    //retourn 1 s'il a 1 gagnant
                    if(cdw == 1)
                    {
                        printf("\nGagne !!!\n\n");
                        Enregistrements_findepartie(tour, pseudo,total);
                    }
                    //retourn 1 s'il a touche
                    if (touche == 1)
                    {
                        --tour;
                    }
                    else
                    {
                        printf("\nVoulez voir la solution ? (Appuyez sur y pour oui ou toucher une touche pour continuer)\n");
                        printf("Reponse: ");
                        //Vider la memoire cach et saisir une nouvelle valeur
                        fflush(stdin);
                        scanf("%c", &triche);
                        if(triche == 'y')
                        {
                            printf("T = Torpieurs\n");
                            printf("C = Croiseurs\n");
                            printf("A = Portes-avions\n");
                            printf("S = Touche\n");
                            printf("W = eau\n");
                            Solution();
                        }
                    }
                }
                else if(tour % 2 != 0)
                {
                    //Tour du NPC
                    //Trouve une valeur random de 1 a 10
                    x = rand() % AXEMAX_X;
                    //Trouve une valeur random de 1 a 10
                    y = rand() % AXEMAX_Y;
                    touche = Tir(tour,x,y,pseudo);
                    cdw = Condition_Victoire(tour);
                    //retourn 1 s'il a 1 gagnant
                    if(cdw == 1)
                    {
                        //retourn 1 s'il a 1 gagnant, donc affiche perdu (pour le joueur)
                        printf("\nPerdu !!!\n\n");
                        Enregistrements_findepartie(tour, pseudo, total);
                    }
                    //retourn 1 s'il a touche
                    if (touche == 1)
                    {
                        --tour;
                    }
                }
                ++tour;
            }
			Enregistrements_scores();

            printf("rejouer ?\n (Appuyer sur 3 pour quitter ou 1 pour rejouer)\n");
            scanf("%d", &choix2);
            while(choix2 != 3 && choix2 != 1)
            {
                choix2 = Error();
            }
            choix = choix2;

            break;
        case 2:
            Regles();
            printf("\nJouer ?\n (1 = oui / 3 = quitter)\n");
            scanf("%d", &choix2);
            while(choix2 != 1 && choix2 != 3)
            {
                choix2 = Error();
            }
            choix = choix2;
            break;

        default:
            //Vider la memoire cach et saisir une nouvelle valeur.
            fflush(stdin);
            //Effacer l'ancien message.
            system("CLS");
            choix = Menu();
            break;
        }
    }
    //Eviter de sortir brusquement
    system("Pause");
    return 0;
}
