#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#include "structures.h"
#include "helpers.h"
#include "drawings.h"
#include "baraja.h"
#include "game.h"
#include "menus.h"

/***************************** variables globales *****************************/
                /* ROOT           LOGO -> caracteres[0]   caracteres[1]  ->   colores[0]        colores[1]     */
App application = {"applicationFiles\\", { { {' ', 219, 178}, {' ', 219} }, { {BLACK ,BLUE, RED}, {BLACK, WHITE} }  }  };

Jugador jugadores[7]; /*Arreglo con la informacion de cada jugador*/

int barajaIndex = 0; /*Posicion de la proxima carta que se puede tomar*/

Carta baraja[52];  /* Baraja -> arreglo con 52 cartas */

bool appOn = true; /*La aplicacion esta abierta*/
bool gameOn = false; /*Hay una partida corriendo*/
/******************************************************************************/


/*Funcion para la animacion de inicio del juego*/
void fadeInAnimation(){
    /*Logo del juego*/
    drawSprite("logos\\logo.txt", 55, 10, application.logo.colores[0], application.logo.caracteres[0], BLACK);
    drawText("Black Jack", 40, 25, BLUE);
    Sleep(1000);
    system("cls");

    return;
}



/*Funcion para preparar todo lo necesario*/
void inicializar(){
     srand(time(NULL));
     hidecursor();
     /*Agrandar la pantalla*/
     system("mode con: cols=120 lines=50");
     return;
}



int main(){
    /*Preparar el entorno del juego*/
    inicializar();
    /*Animacion de inicio*/
    fadeInAnimation();  
    /*Bucle continuo hasta que el usuario quiera salir*/
    while(appOn == true){
        mainMenu();

        /*Si el jugador decidio salir desde el menu principal*/
        if(!appOn)
            return 0;
        else
            /*Se inicia un juego*/
            gameOn = true;
        while(gameOn == true){
            /*Empezar una partida*/
            gameStart();
            /*Preguntar si el jugador quiere seguir jugando*/
            if(gameOn == true){
                system("cls");
                goxy(50, 30);
                printf("Fin de ronda");
                goxy(47, 31);
                printf("%cQuieres seguir?", 168);
                if(!siNo(55, 33))
                    gameOn = false;
            }
        }
    }

    return 0;
}
