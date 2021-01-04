#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <ctype.h>

#include "structures.h"
#include "drawings.h"
#include "menus.h"
#include "helpers.h"

extern App application;
extern Jugador jugadores[7];
extern bool appOn;

void singleMenu(){
     system("cls");     
     drawSprite("logos\\logo.txt", 53, 10, application.logo.colores[0], application.logo.caracteres[0], BLACK); 
     application.jugadores = 1;
     char opts[4][50] = {"Nombre:\0", "Dinero inicial($10 - $15000):\0", "", "Presiona CTRL + C para regresar"};
     for(int i = 0; i<4 ; i++){
             textcolor(WHITE);
             int y;
             
             y = 25;
             y += i*2; 
             
             goxy(40, y);
             printf(opts[i]);               
     }
     goxy(38, 25);    
     putchar('>');
     if(input(30, 73, 25, jugadores[0].nombre, 't', 0, ' ') == 1){
         mainMenu();
         return;                 
     }
     goxy(38, 25);
     putchar(' ');
     
     goxy(38, 27);
     putchar('>');
     jugadores[0].dinero = input(15000, 73, 27, "", 'n', 10, '$');
     
     if(jugadores[0].dinero == 1){
         mainMenu();
         return;                       
     }
                     
 
     return;
}


void playerNameMenu(int playerNum, int dineroInicial){
     system("cls"); /*Se limpia la pantalla*/
     drawSprite("logos\\logo.txt", 53, 10, application.logo.colores[0], application.logo.caracteres[0], BLACK); /*Se dibuja el logo*/
     
     /*Impresion de las instrucciones*/
     goxy(35, 25);
     textcolor(WHITE);
     printf("Nombre del jugador %i:", playerNum+1);  
     goxy(38, 30);
     printf("Presiona CTRL + C para regresar al menu principal");  
     
     if(input(30, 60, 25, jugadores[playerNum].nombre, 't', 0, ' ') == 1){
         mainMenu();
         return;                 
     }
       
     /*Se le asigna el dinero inicial al jugador*/
     jugadores[playerNum].dinero = dineroInicial;
}


void multiplayerMenu(){
     system("cls"); /*Limpieza de pantalla*/
     drawSprite("\\logos\\logo.txt", 53, 10, application.logo.colores[0], application.logo.caracteres[0], BLACK); /*Se dibuja el logo*/
     
     /*Diferentes opciones que se van a imprimir*/
     char opts[4][50] = {"No. de jugadores(2-7)", "Dinero inicial($10 - $15000):\0", "", "Presiona CTRL + C para regresar"};
     
     /*Impresion dinamica de las opciones*/
     for(int i = 0; i<4 ; i++){
             textcolor(WHITE);
             
             goxy(40, 25+i*2);
   printf(opts[i]);               
               }       
     
     char c = 0; /*Caracter de la tecla presionada*/
     unsigned int dineroInicial = 0; /*Dinero inicial para todos los jugadores*/
     unsigned int selected = 0; /*Opcion seleccionada*/
     application.jugadores = 2; /*Minimo numero de jugadores*/
     
     goxy(38, 25);
     putchar('>');
     application.jugadores = input(7, 73, 25, "", 'n', 2, ' ');
     if(application.jugadores == 1){
         mainMenu();
         return;            
     }
     
     goxy(38, 25);
     putchar(' ');
     goxy(38, 27);
     putchar('>');
     dineroInicial = input(1500, 73, 27, "", 'n', 10, '$');
     if(dineroInicial == 1){
         mainMenu();
         return;
     }             
     /*Obtencion del nombre de cada jugador*/
     for(int i = 0; i < application.jugadores; i++)
             playerNameMenu(i, dineroInicial); 
}

void instructionsMenu(){
     char c = 0;
     int activePage = 0;
     char page[] = "instrucciones1.bin";
     drawBackground(page, 0);
     while(c != 3){
         c = 0;
         if(kbhit()){
             c = getch();
             
             if(c == 'd' || c == 'D'){
                  activePage < 2 ? activePage++ : false;
                  page[13] = (activePage+1)+'0'; 
                  drawBackground(page, 0);    
             }else if(c == 'a' || c == 'A'){
                  activePage > 0 ? activePage-- : false;
                  page[13] = (activePage+1)+'0'; 
                  drawBackground(page, 0); 
             }
         }
         
                 
     }
     mainMenu();     
}

void mainMenu(){
     system("cls");  /*Limpiar la pantalla*/
     drawSprite("\\logos\\logo.txt", 53, 10, application.logo.colores[0], application.logo.caracteres[0], BLACK); /*Dibujar logo*/
     
     /*Diferentes opciones del menu*/
     char opts[9][15] = {"Un jugador", "Multijugador", "Instrucciones", "Salir", "", "Navega usando:\0", "      W    ", "A          D", "      S    "};
     /*Impresion de las opciones del menu*/
     for(int i = 0; i < 9; i++){
             textcolor(WHITE);
             
             goxy(57, 25+i*2); /*Ajuste dinamico de la posicion en y de la opcion*/
             printf(opts[i]);       
     }
     
     
     int selected = 0; /*variable que indica la opcion seleccionada actualmente*/
     char c = 0; /*Variable que guarda el valor de la tecla presionada*/
     while(c != 13){  /*En espera del ENTER*/
             if(kbhit()){
                  c = getch(); /*Optencion del nuevo caracter*/       
                         
                 /*Limpieza del indicador de opcion seleccionado anterior*/        
                 goxy(55, 25+selected*2);
                 putchar(' ');           
                 
                 /*Cambio de la opcion seleccionada actualmente*/
                 if(c == 'w' || c == 72){
                     selected > 0 ? selected-- : false;         
                 }
                 if(c == 's' || c == 80){
                      selected < 3 ? selected++ : false;     
                 }       
             }
             
             /*Indicador de opcion seleccionada*/
             goxy(55, 25+selected*2);
             putchar('>');                                      
     }
     
     /*Una vez presionado ENTER se redirije al menu seleccionado*/
     switch(selected){
         case 0:
              singleMenu(); /*Modo un jugador*/
              break;
         
         case 1: 
              multiplayerMenu(); /*Modo multijugador*/
              break;
              
         case 2:
              instructionsMenu(); /*Instrucciones*/     
              break;
         
         case 3: 
              appOn = false; /*Salir*/
              break;
        
        default:
              mainMenu(); /*Regreso al menu principar en caso de haber un error con la variable 'selected'*/
              break;      
     }
     
}
