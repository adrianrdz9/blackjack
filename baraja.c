#include <stdlib.h>
#include <conio.h>

#include "structures.h"
#include "baraja.h"

extern Carta baraja[52]; /*Extrae el arreglo desde el archivo principal*/

void llenarBaraja(){
     int c = 0;
     /*Ciclo para decidir el palo*/
     for(int j = 1; j <= 4; j ++){   
         /*Ciclo para decidir el num*/                
         for(int i = 1; i <= 13; i++){
                 baraja[c].num = i;
                 /*Asignacion del valor de la carta, solo pueden 
                   haber valores entre 1 y 10, a pesar de que hay 
                   13 posiciones relativas posibles*/
                 baraja[c].val = (i <= 10 ? i : 10);
                 /*Las cartas solo podran tener uno de dos colores: Verde o Rojo*/
                 if(j == 1 || j  == 3){
                      baraja[c].color = GREEN;     
                 }else{
                       baraja[c].color = RED;      
                 }
                 /*Asignacion del palo(simbolo correspondiente a cada palo)*/
                 switch(j){
                           case 1:
                                baraja[c].palo = '\x06'; /* Picas */ 
                                break;
                           case 2: 
                                baraja[c].palo = '\x03'; /* Corazones */
                                break;
                           case 3:
                                baraja[c].palo = '\x05'; /* Treboles */
                                break;
                           case 4:
                                baraja[c].palo = '\x04'; /* Diamantes */
                                break;   
                 }  
                 c++;                    
         }                       
     }
}
 
void barajar(){
     for(int i = 0; i <52; i++){
             Carta tempCard;
             int j = rand() % 52; /* Se "toma" una posicion aleatoria dentro de la baraja */
             
             tempCard = baraja[i]; /* Se almacena temporalmente la carta que se encuentra en la 
                                      posicion del contador pues sera reemplazada*/
                                      
             baraja[i] = baraja[j]; /* Se cambia la carta aleatoria a la posicion del contador */
             
             baraja[j] = tempCard;  /* Se llena el "hueco" dejado por la carta aleatoria con 
                                       la carta que sustituyo, es, decir la carta aleatoria  */      
     }       
}

int cardSum(Carta playerCards[5]){
    int cardSum = 0; /*Inicializa la suma en 0*/
    /*Ciclo a traves de la mano del jugador*/
    for(int i = 0; i < 5; i++){
        if(playerCards[i].val == 1) /*As -> 11*/
            cardSum += 11;
        else
            cardSum += playerCards[i].val;
    }
    int aceCount = 0; /*Conteo de aces para asigancion dinamica de 11 o 1 como su valor*/
    /*Ciclo a traves de la mano del jugador*/
    for(int i = 0; i < 5; i++)
        if(playerCards[i].val == 1) /*As*/
            aceCount++;
    
    /*Mientras el jugador tenga aces y aun valga la pena reasignar el valor del As*/         
    while(aceCount > 0 && cardSum > 21){
        cardSum-= 10; /*Se cambia el As de 11 a 1*/
        aceCount--; /*Se descarta el As*/              
    }
    /*Regresar la suma*/ 
    return cardSum;    
}


