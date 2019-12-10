/**
* \title main.c
* \brief utilisation de sizeof
* \author Alexandre Ricart
* \version 1.0
* \date 03.09.2019
*/

#include <stdio.h>
#include <stdlib.h>
#define TABMAX 10
#define x 10
#define y 10

int TableauNaval[x][y];

int Menu(){
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

int Reglement(){
    int o;

    printf("");


}

void CarteNaval(){

    printf("  ");
    for(int k = 0; k < TABMAX; k++){
        printf(" %d",k + 1);
    }
    printf("\n");
    for(int i = 0; i < TABMAX; i++){
    printf("%2d ",i + 1);
        for(int j = 0; j < TABMAX; j++){
           printf("%c ", 176);
        }
        printf("\n");
    }
}

int main()
{
   int x, y;
   int TableauGrille[][];

   printf("Choisir le placement d un bateau 1 cases.\n");
   scanf("%d %d", x, y);

    printf("  ");
    for(int k = 0; k < TABMAX; k++){
        printf(" %d",k + 1);
    }
    printf("\n");
    for(int i = 0; i < TABMAX; i++){
    printf("%2d ",i + 1);
        for(int j = 0; j < TABMAX; j++){
           T
        }
        printf("\n");
    }

}
