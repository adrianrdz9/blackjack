#ifndef _baraja_h_
#define _baraja_h_

/************************************************************************************
 * Funcion encargada de revolver las cartas que se ecuentran en el arreglo 'baraja' *
 ************************************************************************************/
void barajar();

/**********************************************************************************
 * Funcion encargada de asignar los valores correspondientes a cada               *
 * carta (estructura de tipo 'carta') dentro del arreglo 'baraja', sin parametros *
 *********************************************************************************/
void llenarBaraja();

/*********************************************************************************************
 * Funcion encargada de devolver la suma de las cartas de la baraja recibida en parametros.  *
 * Parametros:                                                                                    *
 * Carta playersCards[5]->Arreglo de cartas equivalentes a las cartas del jugador            *
 *********************************************************************************************/
int cardSum(Carta playerCards[5]);

#endif
