#include "definitions.h"

#ifndef IO_H
#define IO_H

void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void print_help();
void get_matriz_objeto(GLfloat* m1, vector3* e,GLfloat* m2);

#endif // IO_H
