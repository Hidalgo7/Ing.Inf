//	Program developed by
//	
//	Informatika Fakultatea
//	Euskal Herriko Unibertsitatea
//	http://www.ehu.eus/if
//
// to compile it: gcc dibujar-puntos.c -lGL -lGLU -lglut
//
// This example shows :the use of GL_POINTS
//


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "cargar-triangulo.h"

// texturaren informazioa
    

extern void load_ppm(char *file, unsigned char **bufferptr, int *dimxptr, int * dimyptr);
unsigned char *bufferra;
int dimx,dimy;
int num_triangles;
hiruki *triangulosptr;
int indice = 0;

void ordenar_puntos(punto *a, punto *b, punto *c){
	punto* aux;
	
	if (a->y < b->y){
		aux = b;
		b = a;
		a = aux; 
	}
	if (b->y < c->y){
		aux = c;
		c = b;
		b = aux; 
	}
	if (a->y < b->y){
		aux = b;
		b = a;
		a = aux; 
	}
}

unsigned char* color_textura(double u, double v)
{
/* debe devolver un puntero al pixel adecuado, no al primero!! */
	int fila = dimy * (1-v);
	int columna = dimx * u;
	int total = fila * 3 * dimx + columna * 3; 
	return(bufferra + total);
}

void dibujar_punto(double x, double y, double u, double v){
	unsigned char* colorv = color_textura(u,v);
	unsigned char r,g,b;
	r = colorv[0];
	g = colorv[1];
	b = colorv[2];
	
	glBegin( GL_POINTS );
		glColor3ub(r,g,b);
	    	glVertex3f(x,y,0.);
	glEnd();
}

static void dibujar_triangulo(hiruki h){
	punto a,b,c,aux;
	
	a = h.p1;
	b = h.p2;
	c = h.p3;
	ordenar_puntos(&a,&b,&c);
	
	int xa = a.x, ya = a.y, ua = a.u, va = a.v;
	int xb = b.x, yb = b.y, ub = b.u, vb = b.v;
	int xc = c.x, yc = c.y, uc = c.u, vc = c.v;
	
	double x,y,u,v;
	for ( double alfa = 0; alfa <= 1; alfa += 0.001){
		for ( double beta = 0; beta <= 1; beta += 0.001){
			
			double gamma = 1 - beta - alfa;
			if(gamma >= 0){
				x = alfa * xa + beta * xb + gamma * xc;
				y = alfa * ya + beta * yb + gamma * yc;
				u = alfa * ua + beta * ub + gamma * uc;
				v = alfa * va + beta * vb + gamma * vc;
				dibujar_punto(x,y,u,v);
			}
			 
		}
	}
	
}




static void marraztu(void)
{
float u,v;
float i,j;
unsigned char* colorv;
unsigned char r,g,b;

// borramos lo que haya...
glClear( GL_COLOR_BUFFER_BIT );
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0, 500.0, 0.0, 500.0,-250.0, 250.0);

// por ahora dibujamos todos los pixels de la ventana de 500x500 con el color que devuelve la función color_textura
// pero hay que llamar a la función que dibuja un triangulo con la textura mapeada:


/*
for (i=0;i<500;i++)
    for (j=0;j<500;j++)
    {
        u = i/500.0;
        v = j/500.0;
        colorv=  color_textura(u, v); // si esta función es correcta se ve la foto en la ventana
        r= colorv[0];
        g= colorv[1];
        b= colorv[2];     
	    glBegin( GL_POINTS );
	    glColor3ub(r,g,b);
	    glVertex3f(i,j,0.);
	    glEnd();
	}
*/


dibujar_triangulo(triangulosptr[indice]);
glFlush();


}
// This function will be called whenever the user pushes one key
static void teklatua (unsigned char key, int x, int y)
{
switch(key)
	{
	case 13: 
		printf ("ENTER: que hay que dibujar el siguiente triángulo.\n");
		
		/* hacer algo para que se dibuje el siguiente triangulo */
         // pero si es el último? hay que controlarlo!
        if(indice < num_triangles - 1){
            indice++;
        }
		else{
            indice = 0;
        }
		break;
	case 27:  // <ESC>
		exit( 0 );
		break;
	default:
		printf("%d %c\n", key, key );
	}

// The screen must be drawn to show the new triangle
glutPostRedisplay();
}

int main(int argc, char** argv)
{
    

	printf("This program draws points in the viewport \n");
	printf("Press <ESC> to finish\n");
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_RGB );
	glutInitWindowSize ( 500, 500 );
	glutInitWindowPosition ( 100, 100 );
	glutCreateWindow( "GL_POINTS" );
    
	glutDisplayFunc( marraztu );
    	glutKeyboardFunc( teklatua );

	
	/* we put the information of the texture in the buffer pointed by bufferra. The dimensions of the texture are loaded into dimx and dimy */ 
        load_ppm("yo.ppm", &bufferra, &dimx, &dimy);
        /***** lee la información de los triángulos... pero hay que definir las variables!
        ****/
        cargar_triangulos(&num_triangles, &triangulosptr);
        
	glClearColor( 0.0f, 0.0f, 0.7f, 1.0f );

	glutMainLoop();

	return 0;   
}
