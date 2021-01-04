#ifndef _game_h_
#define _game_h_

/*Crea el menu para que cada jugador haga su apuesta inicial*/
void apuestaInicial();

/*Ronda para pagar las apuestas a los ganadores*/
void priceRound();

/***************************************************************************
 * Se le entregan sus cartas iniciales a cada jugador y se da la opcion de *
 * dividir el juego, duplicar la apuesta, pedir cartas o platarse          *
 ***************************************************************************/     
void repartirCartas();

/*Vaciar manos de los jugadores y de la banca, validar que haya jugadores y empezar otra ronda*/
void gameStart();

#endif
