#ifndef DISPLAY_H
#define DISPLAY_H

#include "definitions.h"
void display(void);
void reshape(int width, int height);
int poligono_delantero(object3d *o,face f);
int poligono_delantero_cam(camera *c,face f);
void get_matriz_csr(GLfloat* m1,GLfloat* m2);

#endif // DISPLAY_H
