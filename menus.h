#ifndef _menus_h_
#define _menus_h_

#include  "structures.h"

struct application;
struct carta;

/*Menu para el modo de un jugador, elige el nombre de usuario y el dinero inicial*/
void singleMenu();

/**********************************************************************************
 * Obtencion del nombre de cada jugador para la opcion multijugador, parametros:  *
 * playerNum -> Poicion del jugador dentro del arreglo jugadores                  *
 * dineroInicial -> Dinero con el que el jugador empezara el juego                *
 **********************************************************************************/
void playerNameMenu(int playerNum, int dineroInicial);

/*Menu para el modo multijugador, se elige en numero de jugadores y el dinero con el que se iniciara el juego*/
void multiplayerMenu();

/*Mostrar las instrucciones del juego*/
void instructionsMenu();

/*Funcion para dibujar el menu principal y dirigir a los diferentes menu's*/
void mainMenu();

#endif
