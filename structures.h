#ifndef _structures_h_
#define _structures_h_

#include <stdbool.h>

struct carta;
struct application;
struct jugador;

typedef struct carta {
       int val;  /* Valor de la carta (1-10) */
       char palo; 
       int color; 
       int num; /* Posicion de la carta respento a otras del mismo palo (1-13)*/      
} Carta;

typedef struct application{
       char root[128]; 
       struct logo{
              char caracteres[2][3];
              int colores[2][3];
       } logo;  
       int jugadores; 
       Carta manoBanca[5];                    
} App;

typedef struct jugador {
       char nombre[128];
       int apuesta[2];
       int apuestaSeguro;
       int dinero;
       bool isDivided;
       Carta mano[2][5];      
} Jugador;


#endif
