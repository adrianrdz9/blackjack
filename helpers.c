#include <windows.h>
#include <conio.h>
#include <ctype.h>

#include "helpers.h"

void goxy(int x,int y){ 
    
    //Definir estructura coordenada
    COORD coords;
    
    //Inicializar los miembros de la estructura con los parametros de entrada
    coords.X = x;
    coords.Y = y;
    
    //Referencia al buffer de salida de la consola
    HANDLE outHandle;
    outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //Establecer la posicion del cursor en la consola definida
    SetConsoleCursorPosition(outHandle, coords);
}

void hidecursor(){
    //Referencia al buffer de salida de la consola
    HANDLE outHandle;
    outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //Informacion del cursor de la consola
    CONSOLE_CURSOR_INFO info;
    //Porcentaje del tamaño de la celda de caracter que sera ocupado por el cursor
    info.dwSize = 100;
    //Visibilidad del cursor
    info.bVisible = FALSE;
    
    //Cambiar la informacion del cursor de la consola
    SetConsoleCursorInfo(outHandle, &info);
}

int input(int len, int x, int y, void* var, char type, int min, char pre){
    char str[len+1];
    str[0] = '\0';
    int i = 0, num = 0;
    char c = getch();
    
    while(c != 13 || ((i == 0 || str[0] == '\0' || str[0] == ' ') && type == 't') || (num < min && type == 'n') ){
             goxy(x, y);
             
             if(type == 't'){ /*campo de tipo texto*/                                   
                 if(isalpha(c) && i < len){ /*Validacion alfabetica y de la longitud del nombre*/
                     /*Se guarda el nombre carcater por carcacter*/
                     str[i++] = c;
                     str[i] = '\0';
                     printf(str);             
                 }else if(c == 8 && i != 0){ /*Tecla delete*/
                     /*Se borra el ultimo carcater*/
                     str[i-1] = ' ';
                     str[i--] = '\0';
                     printf(str);  
                 }else if(!isalpha(c)){
                       goxy(x, y+1);
                       textcolor(RED);
                       printf("Solo puedes introducir letras");      
                       textcolor(WHITE);
                 }   
             }else if(type == 'n'){ /*Campo tipo numero*/                 
                 if(isdigit(c)){
                     if(len < 10){
                         if(c-'0' < min){
                             num = min;
                         }else{
                             num = c-'0';
                         }
                     }else{
                         num = num*10 + c-'0';
                     }                     
                 }     
                 
                 if(num < min && c == 13){
                     goxy(x, y+1);
                     printf("El minimo es %c%i", pre, min);  
                 }
                  
                 if(num > len){
                     num = len;
                     goxy(x, y+1);
                     printf("El maximo es %c%i", pre, len);                          
                 }else if(c == 8){
                     num = (int)num/10;                           
                 }else if(c == 3){
                     return 1;                  
                 }
                 goxy(x, y);
                 printf("%c%5i", pre, num);
                 if(!isdigit(c)){
                     goxy(x, y+1);
                     printf("Solo puedes introducir numeros"); 
                 }        
             }
                          
             if(c == 3){
                 return 1; /*Validacion del regreso al menu princiapal, se regresa un codifo para indicar la vuelta al menu principal*/
             } 
             
             c = getch();
             
             goxy(x, y+1);
             printf("                                 ");
                         
     }
     if(type == 't')  
         strcpy(var, str);
     else if(type == 'n')
         return num;
         
     return 0;  
        
}
