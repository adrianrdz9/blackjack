#ifndef _drawings_h_
#define _drawings_h_

void drawCard(Carta card, int x, int y);

/**********************************************************************************************
 * Funcion encargada de dibujar en la pantalla a partir                                       *
 * de un sprite dado en un archivo de text en una posicion especifica, parametros:            *
 * fileRoute->ruta del archivo relativa al root de la applicacion                             *
 * x->posicion x de la esquina superior izquierda del dibujo                                  *
 * y->posicion y de la esquina superior izquierda del dibujo                                  *
 * colors->arreglo con los colores correcpondientes para cada punto del dibujo                *
 * caracteres->arreglo con los caracteres correspondientes para cada punto del dibujo         *
 *********************************************************************************************/
void drawSprite(char fileRoute[], int x, int y, int colors[], char caracteres[], int bgcolor);

/********************************************************************************************
 * Funcion encargada de transformar una cadena de entrada en una imagen y dibujarlo         *
 * en una posicion dada, parametros:                                                        *
 * text->Texto a ser dibujado                                                               *
 * length->Largo del texto                                                                  *
 * x->posicion x de la esquina superior izquierda del texto                                 *
 * y->posicion y de la esquina superior izquierda del texto                                 *
 * color->Color usado para hacer el dibujo del texto                                        *
 ********************************************************************************************/
 void drawText(char text[], int x, int y, int color);
 
 void printCardSum(Carta playerCards[5], int x, int y);
 
 void drawPlayerData(Jugador jugador);
 
 bool siNo(int x, int y);
 
 void drawBackground(char filename[127], int desfase);

#endif
