/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

#include "interface.h"

int showMenu(char** options, int length) {

    printf("********Menu********\n");
    for (int option = 1; option <= length; option++) {
        printf("%d. %s\n", option, options[option - 1]);
    }
    
    return askOption(length);
}

int askOption(int numberOfOptions) {
    printf("\nDigite una opcion: ");

    int option = 0;
    while(1){
        scanf("%d", &option);
        if (option > 0 && option <= numberOfOptions){
            return option;
        }
        printf("Debe ingresar una opcion entre 1 y %d: ", numberOfOptions);
    }
}