#ifndef _helpers_h_
#define _helpers_h_

/*Mover la posicion del cursor a cualquier parte independientemente del
  tamaño de la consola*/
void goxy(int x,int y);

/*No mostrar el cursor en pantalla*/
void hidecursor();

int input(int lenght, int x, int y, void* var, char type, int min, char pre);

#endif
