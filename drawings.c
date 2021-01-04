#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#include "structures.h"
#include "baraja.h"
#include "helpers.h"
#include "drawings.h"

extern App application;

void drawCard(Carta card, int x, int y){
     char route[128], cardName[10];
     if(card.val == 1 || card.num > 10){
         switch(card.palo){
               case '\x06':  /*Picas*/
                    strcpy(cardName, "asP");
                    break;
               case '\x03':  /*Corazones*/ 
                    strcpy(cardName, "asC");
                    break;
               case '\x05':  /*Treboles*/
                    strcpy(cardName, "asT");
                    break;
               case '\x04': /*Diamantes*/
                    strcpy(cardName, "asD");
                    break;                    
         }            
     }else{
           sprintf(cardName, "%i", card.val);
     }
     if(card.val == 0)
                 return;
    
     strcpy(route, "cartas\\");
     strcat(route, cardName);
     strcat(route, ".txt");
     char cardCaracters[9];
     cardCaracters[0] = ' ';
     switch(card.num){
         case 1: 
              cardCaracters[1] = 'A';
              break;
         case 10:
              cardCaracters[1] = 'X';
              break;
         case 11:
              cardCaracters[1] = 'J';
              break;
         case 12:
              cardCaracters[1] = 'Q';
              break;
         case 13: 
              cardCaracters[1] = 'K';
              break;
         default: 
              cardCaracters[1] = card.val+'0';
              break;                 
     }
     cardCaracters[2] = card.palo;
     cardCaracters[3] = (card.val == 1 || card.num > 10) ? 219 : ' ';
     
     int cardColors[] = {BLACK, card.color, card.color, card.color};
     textbackground(WHITE);
     
         
     drawSprite(route, x, y, cardColors, cardCaracters, WHITE);
     textbackground(BLACK);
     textcolor(WHITE);
     
     return;              
}

void drawPlayerData(Jugador jugador){
     goxy(30, 35);
     printf(jugador.nombre);
     goxy(30, 42);
     printf("Apuesta de seguro: $%5i", jugador.apuestaSeguro);   
     goxy(30, 36);
     printf("Dinero: $%5i", jugador  .dinero);
     if(jugador.isDivided){
         goxy(30, 40);
         printf("Apuesta 2: $%5i", jugador.apuesta[1]);                          
     }
     goxy(30, 38);
     printf("Apuesta: $%5i\t\t", jugador.apuesta[0]);     
}


void drawSprite(char fileRoute[], int x, int y, int colors[], char caracteres[], int bgcolor){
    /*Creacion de la ruta completa del archivo*/
    char filename[128];  
    strcpy(filename, application.root);
    strcat(filename, fileRoute);
    
    /*Apertura del archivo*/
    FILE* spriteFile = fopen(filename, "r");
    
    /*Validacion de la existencia del archivo*/
    if(!spriteFile){
        fclose(spriteFile);
        printf("Archivo: %s no encontrado", filename);
        return;                
    }
    /*Ciclo de obtencion de caracteres del archivo*/
    char c = fgetc(spriteFile);
    int cx = x;
    /*El punto y coma(';') marca el fin del dibujo*/
    while(c != ';'){
        /*Dibujo por renglones->El salto de linea('\n') marca el fin del renglon*/
        if(c != '\n'){
             goxy(cx, y);
             textcolor(colors[c-'0']);
             textbackground(bgcolor);
             putchar(caracteres[c - '0']);
             cx++;     
        }else{/*Cambio de renglon*/
            y++; 
            cx = x;     
        }
        /*Obtencion del siguiente caracter*/
        c = fgetc(spriteFile);                             
    }
    
    /*Cierre del archivo*/
    fclose(spriteFile);   
    
    return;  
}
void drawText(char text[], int x, int y, int color){
     int i = 0;
     while(text[i] != '\0'){
             if(text[i] != ' '){
                 char fileroute[25];
                 strcpy(fileroute, "letras\\");
                 char c[2] = {text[i], '\0'};
                 strcat(fileroute, c);
                 strcat(fileroute, ".txt");
                 char caracs[2] = {' ', 219};
                 int colors[2] = {0, color};
                 drawSprite(fileroute, x+(5*i), y, colors, caracs, BLACK);   
             }
             i++;  
     }    
     
     return;      
}

void printCardSum(Carta playerCards[5], int x, int y){
     goxy(x, y);     
     printf("Suma de las cartas: %i", cardSum(playerCards));
}

bool siNo(int x, int y){
    int selected = 0; /*Opcion seleccionada*/
    bool chose = false;
    /*Opciones del menu*/
    goxy(x, y);
    printf("SI");
    goxy(x-2, y);
    putchar('>');
    goxy(x, y+2);
    printf("NO");
     
    /*Espera el 'enter'*/
    while(chose == false){ 
        if(kbhit()){
            char c = getch();
            /*Comparacion de las teclas presionadas y las teclas configuradas para el movimiento*/
            switch(c){
                case 'w':
                case 73:
                    if(selected > 0)
                        selected--;
                    break;
                case 's':
                case 78:
                    if(selected < 1)
                        selected++; 
                    break; 
                case 13:
                     chose = true;
                     break;             
            }
                
            /*Se coloca un apuntador al lado de la opcion seleccionada*/
            if(selected == 0){
                goxy(x-2, y+2);
                putchar(' ');
                goxy(x-2, y);
                putchar('>');
            } else if(selected == 1){
                goxy(x-2, y+2);
                putchar('>');
                goxy(x-2, y);
                putchar(' ');       
            }                          
        }        
    }
    /*Borra el menu*/
    goxy(x-2, y);
    printf("               ");
    goxy(x-2, y+2);
    printf("               ");
    
    /*Regresa la opcion elegida*/
    if(selected == 0)
        return true;
    else if(selected == 1)
        return false;
}

void drawBackground(char filename[127], int desfase){
     struct carac{
            char ch;
            int color;
            int bgColor;       
     } drawing[120][50];
     
     char route[127];
     strcpy(route, application.root);
     strcat(route, filename);
     
     FILE *bg = fopen(route, "rb");
     
     if(bg == NULL){
        printf("Archivo %s no encontrado", route);
        return;
     }   
        for(int y = 0; y < 49; y ++){
                for(int x = 0; x < 120; x++){
                        fread(&drawing[x][y], sizeof(drawing[x][y]), 1, bg);
                        textcolor(drawing[x][y].color);
                        textbackground(drawing[x][y].bgColor);
                        goxy(x, y - (desfase));
                        putchar(drawing[x][y].ch);
                        textcolor(WHITE);
                        textbackground(BLACK);        
                }
        }
     
     fclose(bg);     
}
