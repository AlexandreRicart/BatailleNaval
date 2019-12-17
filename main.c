/**
* \title main.c
* \brief utilisation de sizeof
* \author Alexandre Ricart
* \version 1.0
* \date 03.09.2019
*/

#include <stdio.h>
#include <stdlib.h>
//#include <exemple.h>
#define TABMAX 10
#define SIZE_X 10
#define SIZE_Y 10

int TableauNaval[SIZE_X][SIZE_Y];
int TableauCoups[SIZE_X][SIZE_Y];

int Menu()
{
    int choix;

    printf("\nProjet Bataille Naval AKA <<FAKE AZUR LANE !>>\n\n");
    printf("Type :          BETA.01\n");
    printf("Derniere MAJ:   10.12.2019\n");
    printf("Createur:       Alexandre Ricart\n\n");
    printf("Que souhaitez-vous ?\n");
    printf("1) Lire les regles.\n");
    printf("2) Jouer.\n");
    printf("3) Exit.\n");
    scanf("%d", &choix);

    return choix;
}

int Reglement()
{

    printf("Nani");

    return 0;
}

int DeclarerAttaque()
{

    /*Navires d‚clar‚s */
    TableauNaval[4][4] = 1;
    TableauNaval[3][4] = 1;
    TableauNaval[2][4] = 1;
    TableauNaval[1][4] = 1;


    int x, y;
    printf("Placer un ‚l‚ment dans le tableau:\n");
    printf("Axe X:");
    scanf("%d",&x);
    printf("Axe Y:");
    scanf("%d",&y);

    if(TableauNaval[x-1][y-1] == 1)
    {
        TableauCoups[x-1][y-1] = 1;
    }
    else
    {
        TableauCoups[x-1][y-1] = 2;
    }

    return TableauCoups[x-1][y-1];
}

void CarteNaval()
{
    printf("  ");
    for(int k = 0; k < TABMAX; k++)
    {
        printf(" %d",k + 1);
    }
    printf("\n");
    for(int i = 0; i < TABMAX; i++)
    {
        printf("%2d ",i + 1);
        for(int j = 0; j < TABMAX; j++)
        {
            switch(TableauCoups[i][j])
            {
            case 1:
                printf("X ");
                break;
            case 2:
                printf("O ");
                break;
            default :
                printf("%c ", 176);
                break;
            }
            printf("\n");
        }
    }
}

int main()
{




    CarteNaval();

    system("Pause");
}
