/*
 * TEC, Cartago, Escuela de Ingeniería en Computación, Principios de Sistemas Operativos
 * Proyecto: TriviaCR
 * Abraham Meza Vega, 2018168174
 * Lindsay Morales Bonilla, 2018077301
 * 05/06/2021, I Semestre 2021, Prof. Esteban Arias Méndez
*/

#ifndef USERINFO_H
#define USERINFO_H

/**
  * Data structure to hold logged users information
  */
struct UserInfo {
    char name[128];
    int score;
};
#endif