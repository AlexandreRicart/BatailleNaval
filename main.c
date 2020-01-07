#include <stdio.h>
#include <stdlib.h>

/*
* \Title :  BATAILLE NAVAL VERSION
* \Type:    Jeux de la bataille naval vs IA
* \author:  Alexandre Ricart
* \version: 1.0
* \date:    07.01.2020
*/


//Valeur maximum a saisir dans le tableau
#define AXEMAX_X 10
#define AXEMAX_Y 10
//Valeur minimum a saisir dans le tableau
#define MIN 1

/*Pour plus tard ... transformer les B...
Le programmes comporte 5 bateaux dans les 2 camps
4 B = Porte-avion 1x
3 B = croiseur 2x
2 B = torpieur 2x
-----------------------------------------*/

/*Grille de tableau pour joeur de 10/10 */
char GrilleJ[AXEMAX_X][AXEMAX_Y]=
{
    {'W','B','B','B','W','W','W','B','W','W'},
    {'W','W','W','W','W','W','W','B','W','W'},
    {'W','W','W','W','W','W','W','B','W','W'},
    {'W','B','B','W','W','W','W','B','W','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','W','W','W','B','B','B','W','W','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','B','W','W','W','W','W','W','W','W'},
    {'W','B','W','W','W','W','W','W','W','W'}
};
/*Grille de tableau pour le NPC de 10/10 */
char GrilleNPC[AXEMAX_X][AXEMAX_Y]=
{
    {'W','W','W','W','W','W','W','B','B','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','B','W','W','W','W','W','W','W','W'},
    {'W','B','W','W','W','B','W','W','W','W'},
    {'W','B','W','W','W','B','W','W','W','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','W','W','B','B','B','B','W','W','W'},
    {'W','W','W','W','W','W','W','W','W','W'},
    {'W','B','B','B','W','W','W','W','W','W'}
};
/*Grille de tableau … l'affichage 10/10 */
char Historique[AXEMAX_X][AXEMAX_Y]=
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

    //Sert afficher un tableau compr‚hensible pour le joeur
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
            printf("[%c]",Historique[i][j]);
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

    //Sert afficher un tableau compr‚hensible pour le joeur
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
        printf(" %2d ",i + 1);//Trouve une valeur random de 0 … 9
        for(j = 0; j < AXEMAX_X; ++j)
        {
            //Affiche la grille de l'IA aux positions de i et de j.
            printf("[%c]",GrilleNPC[i][j]);
        }
        printf("\n");
    }
     printf("\n");
}

/**
    Tir
    @param Selon le tour du joueur, affiche si ce dernier a toucher ou louper un bateau, modifie la valeur de B (pour bateau) en S (pour sombr‚ ou coul‚) dans la grille de l'adversaire et permet de rejouer.
*/
int Tir(int Tour,int X,int Y)
{

    //Tout les tours pairs, le joueur joue
    if(Tour % 2 == 0)
    {
        //Selon la grille de l'IA
        switch(GrilleNPC[X][Y])
        {
        case 'W':
            Historique[X][Y] = 'O';
            printf("Louper pour le joueur\n");
            //Ne peux pas rejouer
            return 0;
        case 'S':
            printf("Deja touche par le joueur\n");
            //Ne peux pas rejouer
            return 0;
        case 'B':
            printf("Touche pour le joueur\n");
            //Modifie la valeur B en S (le bateau est touche a cette position)
            GrilleNPC[X][Y] = 'S';
            //Affiche un X dans la grille historique … la position X et Y
            Historique[X][Y] = 'X';
            //permet au joueur de rejouer
            return 1;
        }
    }
    //Tout les tours impairs, l'IA joue
    else if(Tour % 2 != 0)
    {
         //Selon la grille du Joueur
        switch(GrilleJ[X][Y])
        {
        case 'W':
            printf("Louper pour le NPC\n");
            //Ne peux pas rejouer
            return 0;
        case 'S':
            printf("Deja touche par l'IA\n");
            //Ne peux pas rejouer
            return 0;
        case 'B':
            printf("Touche pour le NPC\n");
            //Modifie la valeur B en S (le bateau est touche a cette position)
            GrilleJ[X][Y] = 'S';
            //permet a l'IA de rejouer
            return 1;
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
                if( GrilleNPC[i][j] == 'B')
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
                if( GrilleJ[i][j] == 'B')
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
    @param Valide si les donn‚es sont bien inf‚rieur … la taille maximum et sup‚rieur … la taille minimum du tableau, sinon demande de ressaisir la donn‚e
*/
int Validation()
{
    int Val;
    //Tant que la valeur est inf‚rieur … la valeur minimum ou sup‚rieur … la valeur maxium, affiche un message d'erreur
    do
    {
        //Vider la memoire cach et saisir une nouvelle valeur
        fflush(stdin);
        scanf("%d",&Val);

    }
    while((Val < MIN || Val >AXEMAX_X) && printf("Erreur, la valeur doit etre entre 1 et 10\nFaite aussi attention au caractŠres qui ne sont pas pris par le systeme.\n"));

    //Val N - 1, donc Val - 1 afin de saisir des valeurs entre 1 et 10.
    return Val - 1;
}

/**
    Menu
    @param Affiche le menu du d‚but de jeu, et demande le choix du joueur
*/
int Menu()
{

    int Valeur;

    printf("Bienvenu dans la bataille navale:\n");
    printf("Menu:\n");
    printf("\n\n");
    printf("1 - Jouer\n");
    printf("2 - Les_Regles\n");
    printf("3 - Quitter\n");
    printf("\n");
    scanf("%d",&Valeur);

    return Valeur;
}

/**
    Error
    @param Empˆche le programme de tourne en boucle si l'utilisateur ne rentre pas les donn‚es correctes, redemande … l'utilisateur de saisir une donn‚e s'il s'est tromp‚.
*/
int Error()
{

    int Val;

    //Effacer l'ancien message.
    system("CLS");
    printf("Error - Veuillez choisir entre 1 et 3 svp \n");
    //Vider la memoire cach et saisir une nouvelle valeur
    fflush(stdin);
    scanf("%d", &Val);

    return Val;
}

/**
    Regles
    @param Affiche les r‚gles du jeu.
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
    printf("- Suite … vos tirs et de ceux de l'IA un commentaire indiquera si un bateau est touch‚ ou non.\n  Si quelqu'un touche, il a la possibilite de rejouer.\n");
    printf("\n");
    printf("Bonne chance! :D\n");
    printf("\n");
    printf("**************************************\n");
}

int main()
{
    int Tour = 0;
    int Touche;
    //CDW = Condition de victoire
    int CDW = 0;
    int validation;
    int X = 0;
    int Y = 0;
    int Choix;
    int Choix2;
    //Triche = affiche la grille du NPC
    char Triche;
    //initialiser un temps t
    time_t t;

    //Initialiser le NPC ou L'IA selon l'heure du temps
    srand((unsigned) time(&t));

    Choix = Menu();

    while(Choix != 3)
    {
        switch(Choix)
        {
        case 1:
            printf("Debut de jeu:\n");
            while( CDW != 1)
            {
                if(Tour % 2 == 0)
                {
                    //Tour du joueur
                    Grille();
                    printf("\nTir_X : ");
                    X = Validation();
                    printf("Tir_Y : ");
                    Y = Validation();
                    printf("\n");
                    Touche = Tir(Tour,X,Y);
                    CDW = Condition_Victoire(Tour);
                    //retourn 1 s'il a 1 gagnant
                    if(CDW == 1)
                    {
                        printf("\nGagne");
                    }
                    //retourn 1 s'il a touche
                    if (Touche == 1)
                    {
                        --Tour;
                    } else {
                        printf("\nVoulez voir la solution ? (Appuyez sur y pour oui ou toucher une touche pour continuer)\n");
                        printf("Reponse: ");
                        //Vider la memoire cach et saisir une nouvelle valeur
                        fflush(stdin);
                        scanf("%c", &Triche);
                        if(Triche == 'y')
                        {
                            printf("B = Bateau\n");
                            printf("S = Touche\n");
                            printf("W = eau\n");
                            Solution();
                        }
                    }
                }
                else if(Tour % 2 != 0)
                {
                    //Tour du NPC
                    //Trouve une valeur random de 1 … 10
                    X = rand() % AXEMAX_X;
                    //Trouve une valeur random de 1 … 10
                    Y = rand() % AXEMAX_Y;
                    Touche = Tir(Tour,X,Y);
                    CDW = Condition_Victoire(Tour);
                    //retourn 1 s'il a 1 gagnant
                    if(CDW == 1)
                    {
                        //retourn 1 s'il a 1 gagnant, donc affiche perdu (pour le joueur)
                        printf("\nPerdu");
                    }
                    //retourn 1 s'il a touche
                    if (Touche == 1)
                    {
                        --Tour;
                    }
                }
                ++Tour;
            }
            printf("rejouer ?\n (Appuyer sur 3 pour quitter ou 1 pour rejouer)\n");
            scanf("%d", &Choix2);
            while(Choix2 != 3 && Choix2 != 1)
            {
                Choix2 = Error();
            }
            Choix = Choix2;
            break;
        case 2:
            Regles();
            printf("\nJouer ?\n (1 = oui / 3 = quitter)\n");
            scanf("%d", &Choix2);
            while(Choix2 != 1 && Choix2 != 3)
            {
                Choix2 = Error();
            }
            Choix = Choix2;
            break;

        default:
            //Vider la memoire cach et saisir une nouvelle valeur.
            fflush(stdin);
            //Effacer l'ancien message.
            system("CLS");
            Choix = Menu();
            break;
        }
    }
    //Eviter de sortir brusquement
    system("Pause");
    return 0;
}
