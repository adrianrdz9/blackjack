#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

#include "game.h"
#include "structures.h"
#include "drawings.h"
#include "helpers.h"
#include "baraja.h"

/*Extraccion de varaibles globales de el archivo principal*/
extern App application;
extern Jugador jugadores[7];
extern Carta baraja[52];
extern int barajaIndex;
extern bool gameOn;

int fichas[7][2] = {{LIGHTRED, WHITE}, {LIGHTGREEN, BLACK}, {MAGENTA, WHITE}, {CYAN, BLACK}, {LIGHTBLUE, WHITE}, {YELLOW, BLACK}, {WHITE, BLACK}};

struct pos{
       int x;
       int y;       
} huecos[7] = {{17, 32},{29, 35},{42, 36},{56, 36},{70, 36},{84, 35},{97, 31}};

void apuestaInicial(){
     system("cls");
     drawBackground("mesa.bin", 10); 
     
    /*Ciclo sobre cada jugador*/
    for(int i = 0; i < application.jugadores; i++){
        /*Si aun tiene dinero para apostar*/
        if(jugadores[i].dinero >= 10){              
               
            /*Datos basicos del jugador*/
            goxy(50, 35);
            printf(jugadores[i].nombre);
            goxy(50, 37);
            printf("Dinero: $%5i", jugadores[i].dinero);
                   
            /*Menu para elegir la apuesta inicial*/
            goxy(50, 40);
            printf("Realiza tu apuesta inicial:");
            goxy(50, 41);
            printf("$10 - $%5i", jugadores[i].dinero);
            char c = 0;
            /*Mientras no se presione enter o la apuesta sea menor al minimo*/
            while(c != 13 || jugadores[i].apuesta[0] < 10){
                if(isdigit(c)){ /*Validacion numerica*/
                    /*Se aumentan las unidades y se recorren las decenas, centenas, etc*/
                    jugadores[i].apuesta[0] = jugadores[i].apuesta[0]*10 + (c-'0');               
                }
                
                /*Validar que el jugador pueda cubrir su apuesta*/
                if(jugadores[i].apuesta[0] >jugadores[i].dinero){
                    /*Mantener una apuesta maxima igual al dinero del jugador*/                       
                    jugadores[i].apuesta[0] = jugadores[i].dinero; 
                    
                    goxy(40, 43);
                    printf("No puedes apostar mas, solo tienes $%i", jugadores[i].dinero);                         
                }
                          
                if(c == 8){/*Tecla DEL*/
                    /*Eliminar las unidades y se recorren las decenas, centenas, etc.*/
                    jugadores[i].apuesta[0] = (int)jugadores[i].apuesta[0]/10;
                }
                
                if(c == 13 && jugadores[i].apuesta[0] < 10){
                     goxy(40, 43);
                     printf("La apuesta minima es de $10, por favor apuesta mas");     
                }
                          
                /*Actualizar la apuesta*/
                goxy(50, 42);
                printf("$%5i", jugadores[i].apuesta[0]);            
                c = getch();
                
                goxy(40, 43);
                printf("                                                   "); 
            } 
                   
            /*Restar la apuesta al dinero del jugador*/
            jugadores[i].dinero -= jugadores[i].apuesta[0];
                   
            /*Actualizar los datos del jugador*/  
            goxy(50, 37);
            printf("Dinero: $%5i", jugadores[i].dinero); 
            goxy(50, 40);
            printf("Apuesta: $%5i                ", jugadores[i].apuesta[0]);
            
            /*Dibuja las 'fichas' en el hueco de la mesa correspondiente al jugador 
            y de un color especifico dependiendo de el valor de la apuesta*/
            
            for(int p = 0; p <= i; p++){
                goxy(huecos[p].x, huecos[p].y-9);
                textcolor(fichas[jugadores[p].apuesta[0]%7][1]);
                textbackground(fichas[jugadores[p].apuesta[0]%7][0]);
                printf("$%i", jugadores[p].apuesta[0]);
                textbackground(BLACK);
                textcolor(WHITE);
            }       
            
            /*Borrar de pantalla el menu anterior*/
            goxy(50,41);
            printf("                                      ");    
                   
            /*Esperar para que el jugador vea lo que hizo*/
            goxy(50,47);  
            printf("Presiona una tecla para continuar...");
            getch();   
            goxy(50,47);
            printf("                                        ");
            goxy(50, 35);
            printf("                                        ");
        }     
    } 
}

void priceRound(){
     
    /*La banca toma cartas hasta llenar su mano*/
    for(int i = 1; i < 5; i++){
        /*La banca pide con 16 y se planta con 17*/
        if(cardSum(application.manoBanca) <= 16){
            /*'Toma' otra carta*/
            application.manoBanca[i] = baraja[barajaIndex++];         
        }
    }
     
    /*Ciclo sobre cada jugador*/
    for(int j = 0; j < application.jugadores; j++){
        system("cls");
        
        /*Dibujar las 'Fichas' de la banca*/
        for(int i = 0; i < 7; i++){
            for(int j = 10; j > (rand()%5); j--){
                    goxy(4+i, 4+j);
                    textbackground(fichas[i][0]);
                    putchar(' ');        
                    textbackground(BLACK);
            }        
        }
        
        
        goxy(30, 2);
        printf("BANCA");
        /*Se dibujan las cartas de la banca*/
        for(int i = 0; i < 5; i++){
            Sleep(100);
            drawCard(application.manoBanca[i], 25+(i*11), 4);
        }
        /*Muestra la suma de las cartas de la banca*/
        goxy(70, 2);
        printf("SUMA: %i", cardSum(application.manoBanca));
             
        /*Mostrar datos del jugador*/
        drawPlayerData(jugadores[j]);
            
        /*Dibuja la(s) mano(s) del jugador*/
        for(int c = 0; c < 5; c++){
            if(jugadores[j].isDivided){
                goxy(3, 28);
                printf("Juego 1");      
                goxy(100, 28);
                printf("Juego 2");   
                goxy(100, 47);
                printf("Suma: %i", cardSum(jugadores[0].mano[1]) );   
                drawCard(jugadores[j].mano[1][c], 100+c, 30+c);                        
            }
            drawCard(jugadores[j].mano[0][c], 3+c, 30+c);
            goxy(3, 47);
            printf("Suma: %i", cardSum(jugadores[j].mano[0]) );
                      
                 
        }   
             
        /*Validacion de un juego perdido desde el principio*/
        for(int c = 0; c < 2; c++){
            if(cardSum(jugadores[j].mano[c]) > 21){   
                textbackground(RED);
                goxy((c*97)+2, 36);
                printf("                ");
                goxy((c*97)+2, 37);
                printf("    Perdiste    ");
                goxy((c*97)+2, 38);
                printf("                ");
                textbackground(BLACK);                        
            }         
        }  
             
        /*Ciclo que recorre cada mano del jugador teniendo o no el juego dividido*/
        for(int i = 0; i < (jugadores[j].isDivided ? 2 : 1); i++){                
            /*Sombrear el juego activo en caso de haber mas de un juego*/
            if(jugadores[j].isDivided){
                if(i == 0){
                    goxy(3, 28);
                    textbackground(WHITE);
                    textcolor(BLACK);
                    printf("Juego 1");
                    textbackground(BLACK);
                    textcolor(WHITE); 
                               
                }else{
                    goxy(3, 28);
                    printf("Juego 1");
                    textbackground(WHITE);
                    textcolor(BLACK);
                    goxy(100, 28);
                    printf("Juego 2");
                    textbackground(BLACK);
                    textcolor(WHITE);     
                }                               
            } 
                     
            char msg[17]; /*Mensaje que aparecera sobre la mano*/
            int bgmsg, tcmsg = WHITE; /*Colores usados para el mensaje*/
            /*Validacion de mano ganadora*/
            if(cardSum(jugadores[j].mano[i]) <= 21 && (cardSum(jugadores[j].mano[i]) >= cardSum(application.manoBanca)|| cardSum(application.manoBanca) > 21)){
                /*GANO*/
                if(cardSum(jugadores[j].mano[i]) == 21 && jugadores[j].mano[i][2].num == 0 && jugadores[i].isDivided == false){
                    int pago = jugadores[j].apuesta[i]*2.5;
                    /*Animacion de pago de apuesta*/
                    for(int i = 11; i < 30; i++){
                        goxy(i, 3+i);
                        textbackground(fichas[pago%7][0]);
                        textcolor(fichas[pago%7][1]);
                        printf("$%i", pago);
                        textcolor(WHITE);
                        textbackground(BLACK);
                        Sleep(80);
                        goxy(i, 3+i);
                        printf("      ");          
                    }
                   
                    /*Gano con blackjack, apuesta 3:2*/
                    jugadores[j].dinero += pago;
                    strcpy(msg, "   BLACKJACK!   ");
                    bgmsg = BLUE;                                 
                }else if(cardSum(jugadores[j].mano[i]) == cardSum(application.manoBanca)){                      
                    /*Empato con la banca, recupera la apuesta*/
                    jugadores[j].dinero += jugadores[j].apuesta[i];
                    strcpy(msg, "  HAS EMPATADO  ");
                    tcmsg = BLACK;
                    bgmsg = YELLOW;     
                }else{
                    int pago = jugadores[j].apuesta[i]*2;
                    /*Animacion de pago de apuesta*/
                    for(int i = 11; i < 30; i++){
                        goxy(i, 3+i);
                        textbackground(fichas[pago%7][0]);
                        textcolor(fichas[pago%7][1]);
                        printf("$%i", pago);
                        textcolor(WHITE);
                        textbackground(BLACK);
                        Sleep(80);
                        goxy(i, 3+i);
                        printf("      ");          
                    }  
                      
                    /*Gano 'normal', apuesta 1:1*/
                    jugadores[j].dinero += pago;
                    strcpy(msg, "    GANASTE!    ");
                    bgmsg = GREEN;      
                }                                                     
            }else{
                int pago = jugadores[j].apuesta[i];
                /*Animacion de cobro de apuesta*/
                for(int i = 30; i > 11; i--){
                    goxy(i, 3+i);
                    textbackground(fichas[pago%7][0]);
                    textcolor(fichas[pago%7][1]);
                    printf("$%i", pago);
                    textcolor(WHITE);
                    textbackground(BLACK);
                    Sleep(80);
                    goxy(i, 3+i);
                    printf("      ");          
                }  
                  
                /*El jugador perdio*/
                strcpy(msg, "    PERDISTE    ");
                bgmsg = RED;           
            }
                     
            /*Validar que el jugador haya apostado al seguro*/
            if(jugadores[j].apuestaSeguro != 0){
                goxy(30, 23);
                /*Validacion del blackjack de la banca*/
                if(cardSum(application.manoBanca) == 21 && application.manoBanca[2].val == 0){                               
                    printf("Apuesta de seguro ganada");
                    jugadores[j].dinero += jugadores[j].apuestaSeguro*3;                                  
                }else{
                    printf("Apuesta de seguro perdida");      
                }                                  
            }
                     
            /*Reinicio de las apuestas*/
            jugadores[j].apuesta[i] = 0; 
            jugadores[j].apuestaSeguro = 0;
                     
            /*Se coloca el mensaje predefinido*/
            textbackground(bgmsg);
            textcolor(tcmsg);
            goxy((i*100)+2, 36);
            printf("                ");
            goxy((i*100)+2, 37);
            printf(msg);
            goxy((i*100)+2, 38);
            printf("                ");
            textbackground(BLACK);
            textcolor(WHITE);
                     
            /*Se acutalizan los datos del jugador*/
            drawPlayerData(jugadores[j]);
            goxy(40,47);  
            printf("Presiona una tecla para continuar...");
            getch();                                        
        }               
    }            
}

void repartirCartas(){
    /*La banca recibe su primera carta*/
    application.manoBanca[0] = baraja[barajaIndex++];
     
    /*Recorre cada jugador*/
    for(int i = 0; i < application.jugadores; i++){
        system("cls");
        drawBackground("mesa.bin", 0);
        
        /*Dibujar la carta de la banca*/
        drawCard(application.manoBanca[0], 45, 0);     
        
        /*Posibilidad de apostar al seguro*/
        if(application.manoBanca[0].num == 1 && jugadores[i].dinero >= jugadores[i].apuesta[0]/2){
            goxy(60, 2);
            printf("%cQuieres apostar al seguro?(50%c de la apuesta inicial)", 168, '%');
            if(siNo(60, 4)){
                jugadores[i].apuestaSeguro = jugadores[i].apuesta[0]/2;
                jugadores[i].dinero -= jugadores[i].apuestaSeguro;                               
            }  
            goxy(60,2);
            printf("                                                       ");                                                                 
        } 
        
        goxy(35, 47);
        printf("Presiona una tecla para recibir tus cartas...");
        getch();           
        
        system("cls"); 
        drawBackground("mesa.bin", 11); 
           
         
        /*Mostrar los datos del jugador*/
        drawPlayerData(jugadores[i]); 
             
        /*El jugador recibe sus primeras 2 cartas*/
        for(int c = 0; c < 2; c++){
            jugadores[i].mano[0][c] = baraja[barajaIndex++];
            drawCard(jugadores[i].mano[0][c], 3+c, 30+c);       
        }
             
        /*Se guarada el valor de la apuesta inicial en caso de que se duplique*/
        int apuestaInicial = jugadores[i].apuesta[0]; 
             
        /*Si el jugador tiene dinero suficiente puede duplicar su apuesta*/
        if(jugadores[i].dinero >= jugadores[i].apuesta[0]){
            goxy(60, 35);
            printf("%cQuieres duplicar tu apuesta?", 168 ); 
                         
            if(siNo(60, 37)){
                jugadores[i].dinero -= jugadores[i].apuesta[0];
                jugadores[i].apuesta[0] *= 2;
                goxy(60, 35);
                printf("                                     "); 
                drawPlayerData(jugadores[i]);                                   
            }                       
        }        
             
        /*Si tiene cartas iguales puede dividir su juego*/
        if(jugadores[i].mano[0][0].num == jugadores[i].mano[0][1].num && jugadores[i].dinero >= apuestaInicial){
            goxy(60, 35);
            printf("%cQuieres dividir tu juego?", 168 );
            goxy(57, 36);
            printf("Deber%cs hacer una apuesta para el segundo", 160);
            goxy(57, 37);
            printf("   juego igual a la apuesta inicial ($%i)", apuestaInicial);
                  
            if(siNo(60, 39)){
                /*Se limpia el dibujo de la mano original*/
                for(int x = 3; x < 15; x++){
                    for(int y = 30; y < 50; y++){
                        goxy(x,y);
                        putchar(' ');        
                    }                                         
                }   
                        
                jugadores[i].isDivided = true;
                        
                /*Se pasa la segunda carta de la primera mano a la primera carta de la segunda mano*/
                jugadores[i].mano[1][0] = jugadores[i].mano[0][1];
                        
                /*Se borra la segunda carta de la primera mano*/
                Carta nullCard = {0,0,0,0};
                jugadores[i].mano[0][1] = nullCard;
                        
                /*Se hace la segunda apuesta*/
                jugadores[i].apuesta[1] = apuestaInicial;
                jugadores[i].dinero -= jugadores[i].apuesta[1];
                        
                /*Se numeran los juegos*/   
                goxy(3, 28);
                printf("Juego 1");      
                drawCard(jugadores[i].mano[0][0], 3, 30); 
                goxy(110, 28);
                printf("Juego 2");
                drawCard(jugadores[i].mano[1][0], 108, 30);   
                        
                /*Se actualizan los datos del jugador*/
                drawPlayerData(jugadores[i]);
            }
                  
            /*Se borra el menu anterior*/
            for(int y = 0; y < 3; y++){
                goxy(57, 35+y);
                printf("                                            "); 
            }                       
        }
        if(jugadores[i].isDivided){
            goxy(110, 47);
            printf("Suma: %i", cardSum(jugadores[i].mano[1]) );                           
        }
        goxy(3, 47);
        printf("Suma: %i", cardSum(jugadores[i].mano[0]) );
         
        /*Ciclo que recorre cada mano del jugador teniendo o no el juego dividido*/
        for(int j = 0; j < (jugadores[i].isDivided ? 2 : 1); j++){                
            /*Se sombrea el juego activo*/
            if(jugadores[i].isDivided){
                if(j == 0){
                    goxy(3, 28);
                    textbackground(WHITE);
                    textcolor(BLACK);
                    printf("Juego 1");
                    textbackground(BLACK);
                    textcolor(WHITE); 
                }else{
                    goxy(3, 28);
                    printf("Juego 1");
                    textbackground(WHITE);
                    textcolor(BLACK);
                    goxy(110, 28);
                    printf("Juego 2");
                    textbackground(BLACK);
                    textcolor(WHITE);     
                }                 
            }
                 
            goxy(60, 35);
            printf("%cQieres otra carta?", 168 );
                 
            int k = (jugadores[i].isDivided ? 1 : 2); /*Numero de cartas en la mano activa*/
                 
            /*Si el jugador quiere otra carta y aun no pierde y tiene menos de 5 cartas puede pedir otra carta*/
            while(cardSum(jugadores[i].mano[j]) <= 21 && siNo(63,37) && k < 5 ){                    
                jugadores[i].mano[j][k] = baraja[barajaIndex++];
                      
                drawCard(jugadores[i].mano[j][k], ((j*107)+3)+((-j)*k)+((-j)*3)+((unsigned int)(1-j)*k), 30+k);     
                k++;
                      
                goxy((j*107)+3, 47);
                printf("Suma: %i", cardSum(jugadores[i].mano[j]) );                         
            }  
                 
            /*Se dibuja un cartel en caso de que el jugador ya haya perdido*/
            if(cardSum(jugadores[i].mano[j]) > 21){   
                textbackground(RED);
                goxy((j*100)+2, 36);
                printf("                ");
                goxy((j*100)+2, 37);
                printf("    Perdiste    ");
                goxy((j*100)+2, 38);
                printf("                ");
                textbackground(BLACK);                         
            }            
        }
         
        goxy(60, 35);
        printf("                                     ");
         
        goxy(35,47);  
        printf("Presiona una tecla para continuar...");
        getch();
            
    }          
}

void gameStart(){
     llenarBaraja(); 
     barajar();
     
     barajaIndex = 0; /*Almacena el la posicion de la proxima carta que debe ser tomada*/
     Carta nullCard = {0,0,0,0}; /*Carta vacia*/
     /*Se usa la carta vacia para vaciar la mano de cada jugador*/
     for(int i = 0; i<application.jugadores; i++){
             for(int j = 0; j < 5; j++){
                     jugadores[i].mano[0][j] = nullCard;
                     jugadores[i].mano[1][j] = nullCard;
                     application.manoBanca[j] = nullCard;       
             }
             /*Se borran los datos viejos*/
             jugadores[i].apuestaSeguro = 0;
             jugadores[i].apuesta[0] = 0;
             jugadores[i].apuesta[1] = 0;
             jugadores[i].isDivided = false;
     }
     
     /*Validar que aun haya jugadores*/
     bool anyPlayers = false;   
     for(int i = 0; i<application.jugadores; i++){
             if(jugadores[i].dinero >= 10)
                 anyPlayers = true;                
     }
     
     /*Si ya no hay jugadores se regresa al menu principal*/
     if(anyPlayers == false){
         system("cls");
         goxy(20, 25);
         printf("Todos los jugadores han perdido, presiona una tecla para volver al menu principal.");
         getch();
         gameOn = false;
     }else{
         /*Se incial el juego*/
         apuestaInicial(); 
         repartirCartas();
         priceRound();
     }
                  
}
