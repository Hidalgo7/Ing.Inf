#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

extern object3d * _first_object;
extern object3d * _selected_object;
extern camera * _first_camera;
extern camera * _selected_camera;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;
extern GLdouble zoom;

int rotar = 0;
int trasladar = 1;
int escalar = 0;

int referencia = 0;
char modo = 0;

void get_matriz_objeto(GLfloat* m1, vector3* e,GLfloat* m2){
    for(int i = 0; i < 3; i++){
    	for (int j = 0; j < 3;j++){
    			m2[i+4*j] = m1[4*i+j];
    	}
    }
    m2[3] = 0;
    m2[7] = 0;
    m2[11] = 0;
    m2[12] = e->x;
    m2[13] = e->y;
    m2[14] = e->z;
    m2[15] = 1;
}

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Visualizar esta ayuda \n");
    printf("<ESC>\t\t Salir del programa \n");
    printf("<F>\t\t Cargar un objeto\n");
    printf("<TAB>\t\t Navegar en los objetos cargados\n");
    printf("<DEL>\t\t Borrar el objeto seleccionado\n");
    printf("<CTRL + ->\t Aumentar el campo de vision\n");
    printf("<CTRL + +>\t Reducir el campo de vision\n\n");
    printf("<G>\t\t Sistema de referencia global\n");
    printf("<L>\t\t Sistema de referencia local\n\n");
    printf("<R>\t\t Activar rotacion\n");
    printf("<T>\t\t Activar traslacion\n");
    printf("<E>\t\t Activar escalado\n");
    printf("<UP> \t\t Trasladar +Y; Escalar + Y; Rotar +X\n");
    printf("<DOWN> \t\t Trasladar -Y; Escalar - Y;  Rotar -X\n");
    printf("<RIGHT> \t Trasladar +X; Escalar +X;  Rotar +Y\n");
    printf("<LEFT> \t\t Trasladar -X; Escalar -X;  Rotar -Y\n");
    printf("<AVPAG> \t Trasladar +Z; Escalar +X;  Rotar +Y\n");
    printf("<REPAG> \t Trasladar -Z; Escalar -Z; Rotar -Z\n");
    printf("<+> \t\t Escalar + en todos los ejes\n");
    printf("<-> \t\t Escalar - en todos los ejes\n");
    printf("<CTRL + Z> \t Deshacer cambios\n");
    printf("\n\n");
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    camera *auxiliar_camera = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {
   	case 'f':
	case 'F':
		/*Ask for file*/
		printf("%s", KG_MSSG_SELECT_FILE);
		scanf("%s", fname);
		/*Allocate memory for the structure and read the file*/
		auxiliar_object = (object3d *) malloc(sizeof (object3d));
		read = read_wavefront(fname, auxiliar_object);
		switch (read) {
		/*Errors in the reading*/
		case 1:
		    printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
		    break;
		case 2:
		    printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
		    break;
		case 3:
		    printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
		    break;
		/*Read OK*/
		case 0:
		    /*Insert the new object in the list*/
		    auxiliar_object->next = _first_object;
		    _first_object = auxiliar_object;
		    _selected_object = _first_object;
		    printf("%s\n",KG_MSSG_FILEREAD);
		    break;
		}
		break;
	
	case 'n':
	case 'N':
	{
		auxiliar_camera = malloc( sizeof(camera) );
		GLfloat matriz_referencia[16];
		vector3* e;
		e->x = 10;
		e->y = 15;
		e->z = 10;
		matrix* m1 = malloc( sizeof(matrix) );
		matrix* m2 = malloc( sizeof(matrix) );
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(e->x,e->y,e->z,0,0,0,0,1,0);
		glGetFloatv(GL_MODELVIEW_MATRIX,m1->values);
		get_matriz_objeto(m1->values,e,m2->values);

		auxiliar_camera->matrixcsrptr = m1;
		auxiliar_camera->matrixobjptr = m2;
		
		auxiliar_camera->next = _first_camera;
		_first_camera = auxiliar_camera;
		_selected_camera = _first_camera;
		break;
	}
	case 9: /* <TAB> */
	     if(_selected_object != NULL){
		_selected_object = _selected_object->next;
		/*The selection is circular, thus if we move out of the list we go back to the first element*/
		if (_selected_object == 0) _selected_object = _first_object;
	     }
	     else{
		printf("No hay ningun objeto cargado\n");
             }
	     break;
	
	case 'k':
	case 'K':
	     if(_selected_camera != NULL){
	     	_selected_camera = _selected_camera->next;
	     	if(_selected_camera == 0) _selected_camera = _first_camera;
	     }

	case 127: /* <SUPR> */
	if(_selected_object != NULL){
		/*Erasing an object depends on whether it is the first one or not*/
		if (_selected_object == _first_object)
		{
		    /*To remove the first object we just set the first as the current's next*/
		    _first_object = _first_object->next;
		   
		    for(int i=0; i < _selected_object->num_faces; i++){
		    	face poligono = _selected_object->face_table[i]; 
			free(poligono.vertex_table);
			(_selected_object->face_table[i]);
			 
		    }
		    /*Once updated the pointer to the first object it is save to free the memory*/
		    free(_selected_object);
		    /*Finally, set the selected to the new first one*/
		    _selected_object = _first_object;
		} else {
		    /*In this case we need to get the previous element to the one we want to erase*/
		    auxiliar_object = _first_object;
		    while (auxiliar_object->next != _selected_object){
		    	auxiliar_object = auxiliar_object->next;
		    }
		    /*Now we bypass the element to erase*/
		    auxiliar_object->next = _selected_object->next;
		    /*free the memory*/
		     for(int i=0; i < _selected_object->num_faces; i++){
		    	face poligono= _selected_object->face_table[i]; 
			free(poligono.vertex_table);
			(_selected_object->face_table[i]);
				 
		    }
		    /*and update the selection*/
		    _selected_object = auxiliar_object;
		}
	}
	break;
    case 'o':
    case 'O':
    	if(modo != OBJETO){
    		modo = OBJETO;
    		printf("Modo: Objeto\n");
    	}
    	break;
    case 'c':
    case 'C':
    	if(modo != CAMARA){
    		modo = CAMARA;
    		printf("Modo: Camara\n");
    	}
    	break;
    case '-':
    	/*
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        */
        zoom += 0.1;
        if (escalar){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m->values);
	    	glScalef(0.8,0.8,0.8);
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
        }
        break;
        

    case '+':
        //INPLEMENTA EZAZU CTRL + + KONBINAZIOAREN FUNTZIOANLITATEA
        /*
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions
            wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        */
        if(zoom > 0.1){
                zoom -= 0.1;
        }
        else if(zoom > 0.000001){
        	zoom -= 0.000001;
        }
        if (escalar){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m->values);
	    	glScalef(1.25,1.25,1.25);
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
        }
        break;

    case '?':
        print_help();
        break;
        
    case 'g':
    case 'G':
    	if(referencia != GLOBAL){
    		referencia = GLOBAL;
    		printf("Sistema de referencia: Global\n");
    	}
    	break;
    case 'l':
    case 'L':
    	if(referencia != LOCAL){
    		referencia = LOCAL;
    		printf("Sistema de referencia: Local\n");
    	}
    	break;
    	
    case 'r':
    case 'R':
    	//Activar Rotacion
    	if(rotar != 1){
    		rotar = 1;
	    	trasladar = 0;
	    	escalar = 0;
	    	printf("Rotacion activada\n");
    	}
    	break;
    	
    case 't':
    case 'T':
    	//Activar Traslacion
    	if(trasladar != 1){
	    	rotar = 0;
	    	trasladar = 1;
	    	escalar = 0;
	    	printf("Traslacion activada\n");
    	}
    	break;
    case 'e':
    case 'E':
    	//Activar Escalado
    	if(escalar != 1){
	    	rotar = 0;
	    	trasladar = 0;
	    	escalar = 1;
	    	printf("Escalado activado\n");
    	}
    	break;
    case 26:
    	if (modo == OBJETO){
		if(_selected_object != 0){
		    	if(_selected_object->matrixptr->sigptr != 0){
		    		_selected_object->matrixptr = _selected_object->matrixptr->sigptr;
		    	}
	    	}
	}
	else if (modo == CAMARA){
		if (_selected_camera != 0){
			if(_selected_camera->matrixcsrptr->sigptr != NULL){
				_selected_camera->matrixcsrptr = _selected_camera->matrixcsrptr->sigptr;
				_selected_camera->matrixobjptr = _selected_camera->matrixobjptr->sigptr;
			}
		}
	}
    	break;
    case 27: /* <ESC> */
        exit(0);
        break;

    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
        printf("keyboard");
    }
    fflush(stdout);
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}

void special(int key, int x, int y) {
    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;
    
    switch (key){
    case 100: //LEFT
    {	
    	if(modo == OBJETO){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
	    	if(referencia == LOCAL){
	    		glLoadMatrixf(m->values);
	    	}
		else {
			glLoadIdentity();
		}
		
	    	if (rotar){
	    		glRotatef(10,0,-1,0);
	    	}
	    	else if (trasladar){
	    		glTranslatef(-1,0,0);
	    	}
	    	else if (escalar){
	    		glScalef(0.8,1,1);
	    	}
	    	
	    	if (referencia == GLOBAL){
	    		glMultMatrixf(m->values);
	    	}
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
	}
	else if(modo == CAMARA){
		GLfloat matriz_rotada1[16];
		GLfloat matriz_rotada2[16];
		matrix *m1 = _selected_camera->matrixobjptr;
		matrix *m2 = _selected_camera->matrixcsrptr;
		matrix *sig_matriz1 = malloc(sizeof (matrix));
		matrix *sig_matriz2 = malloc(sizeof (matrix));
		glMatrixMode(GL_MODELVIEW);
		if(rotar){
			glLoadMatrixf(m1->values);
			glRotatef(10,0,-1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glRotatef(10,0,1,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(trasladar){
			glLoadMatrixf(m1->values);
			glTranslatef(-1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(1,0,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			printf("No es posible escalar la camara");
			break;
		}
		
		for(int i = 0; i < 16; i++){
			sig_matriz1->values[i] = matriz_rotada1[i];
			sig_matriz2->values[i] = matriz_rotada2[i];
		}
		sig_matriz1->sigptr = m1;
		_selected_camera->matrixobjptr = sig_matriz1;
		
		sig_matriz2->sigptr = m2;
		_selected_camera->matrixcsrptr = sig_matriz2;
	}
    	break;
    }
    case 101: //UP
    {
    	if(modo == OBJETO){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
	    	
		if(referencia == LOCAL){
	    		glLoadMatrixf(m->values);
	    	}
		else {
			glLoadIdentity();
		}
		
	    	if (rotar){
	    		glRotatef(10,1,0,0);
	    	}
	    	else if (trasladar){
	    		glTranslatef(0,1,0);
	    	}
	    	else if (escalar){
	    		glScalef(1,1.25,1);
	    	}
	    	
	    	if (referencia == GLOBAL){
	    		glMultMatrixf(m->values);
	    	}
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
    	}
    	else if(modo == CAMARA){
		GLfloat matriz_rotada1[16];
		GLfloat matriz_rotada2[16];
		matrix *m1 = _selected_camera->matrixobjptr;
		matrix *m2 = _selected_camera->matrixcsrptr;
		matrix *sig_matriz1 = malloc(sizeof (matrix));
		matrix *sig_matriz2 = malloc(sizeof (matrix));
		glMatrixMode(GL_MODELVIEW);
		if(rotar){
			glLoadMatrixf(m1->values);
			glRotatef(10,1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glRotatef(10,-1,0,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(trasladar){
			glLoadMatrixf(m1->values);
			glTranslatef(0,1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(0,-1,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			printf("No es posible escalar la camara");
			break;
		}
		
		for(int i = 0; i < 16; i++){
			sig_matriz1->values[i] = matriz_rotada1[i];
			sig_matriz2->values[i] = matriz_rotada2[i];
		}
		sig_matriz1->sigptr = m1;
		_selected_camera->matrixobjptr = sig_matriz1;
		
		sig_matriz2->sigptr = m2;
		_selected_camera->matrixcsrptr = sig_matriz2;
	}
    	break;
    }
    case 102: //RIGHT
    {
    	if(modo == OBJETO){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
	    	
		if(referencia == LOCAL){
	    		glLoadMatrixf(m->values);
	    	}
		else {
			glLoadIdentity();
		}
		
	    	if (rotar){
	    		glRotatef(10,0,1,0);
	    	}
	    	else if (trasladar){
	    		glTranslatef(1,0,0);
	    	}
	    	else if (escalar){
	    		glScalef(1.25,1,1);
	    	}
	    	
	    	if (referencia == GLOBAL){
	    		glMultMatrixf(m->values);
	    	}
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
	}
	else if(modo == CAMARA){
		GLfloat matriz_rotada1[16];
		GLfloat matriz_rotada2[16];
		matrix *m1 = _selected_camera->matrixobjptr;
		matrix *m2 = _selected_camera->matrixcsrptr;
		matrix *sig_matriz1 = malloc(sizeof (matrix));
		matrix *sig_matriz2 = malloc(sizeof (matrix));
		glMatrixMode(GL_MODELVIEW);
		if(rotar){
			glLoadMatrixf(m1->values);
			glRotatef(10,0,1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glRotatef(10,0,-1,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(trasladar){
			glLoadMatrixf(m1->values);
			glTranslatef(1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(-1,0,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			printf("No es posible escalar la camara");
			break;
		}
		
		for(int i = 0; i < 16; i++){
			sig_matriz1->values[i] = matriz_rotada1[i];
			sig_matriz2->values[i] = matriz_rotada2[i];
		}
		sig_matriz1->sigptr = m1;
		_selected_camera->matrixobjptr = sig_matriz1;
		
		sig_matriz2->sigptr = m2;
		_selected_camera->matrixcsrptr = sig_matriz2;
	}
    	break;
    }
    case 103: //DOWN
    {
    	if(modo == OBJETO){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);

		if(referencia == LOCAL){
	    		glLoadMatrixf(m->values);
	    	}
		else {
			glLoadIdentity();
		}
		
	    	if (rotar){
	    		glRotatef(10,-1,0,0);
	    	}
	    	else if (trasladar){
	    		glTranslatef(0,-1,0);
	    	}
	    	else if (escalar){
	    		glScalef(1,0.8,1);
	    	}
	    	
	    	if (referencia == GLOBAL){
	    		glMultMatrixf(m->values);
	    	}
	    	
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
	}
	else if(modo == CAMARA){
		GLfloat matriz_rotada1[16];
		GLfloat matriz_rotada2[16];
		matrix *m1 = _selected_camera->matrixobjptr;
		matrix *m2 = _selected_camera->matrixcsrptr;
		matrix *sig_matriz1 = malloc(sizeof (matrix));
		matrix *sig_matriz2 = malloc(sizeof (matrix));
		glMatrixMode(GL_MODELVIEW);
		if(rotar){
			glLoadMatrixf(m1->values);
			glRotatef(10,-1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glRotatef(10,1,0,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(trasladar){
			glLoadMatrixf(m1->values);
			glTranslatef(0,-1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(0,1,0);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			printf("No es posible escalar la camara");
			break;
		}
		
		for(int i = 0; i < 16; i++){
			sig_matriz1->values[i] = matriz_rotada1[i];
			sig_matriz2->values[i] = matriz_rotada2[i];
		}
		sig_matriz1->sigptr = m1;
		_selected_camera->matrixobjptr = sig_matriz1;
		
		sig_matriz2->sigptr = m2;
		_selected_camera->matrixcsrptr = sig_matriz2;
	}
	break;
    }
    
    case 104: //Re Pag
    {
    	if (modo == OBJETO){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);

		if(referencia == LOCAL){
	    		glLoadMatrixf(m->values);
	    	}
		else {
			glLoadIdentity();
		}
		
	    	if (rotar){
	    		glRotatef(10,0,0,-1);
	    	}
	    	else if (trasladar){
	    		glTranslatef(0,0,-1);
	    	}
	    	else if (escalar){
	    		glScalef(1,1,0.8);
	    	}
	    	
	    	if (referencia == GLOBAL){
	    		glMultMatrixf(m->values);
	    	}
	    	
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
	}
	else if(modo == CAMARA){
		GLfloat matriz_rotada1[16];
		GLfloat matriz_rotada2[16];
		matrix *m1 = _selected_camera->matrixobjptr;
		matrix *m2 = _selected_camera->matrixcsrptr;
		matrix *sig_matriz1 = malloc(sizeof (matrix));
		matrix *sig_matriz2 = malloc(sizeof (matrix));
		glMatrixMode(GL_MODELVIEW);
		if(rotar){
			glLoadMatrixf(m1->values);
			glRotatef(10,0,0,-1);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glRotatef(10,0,0,1);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(trasladar){
			glLoadMatrixf(m1->values);
			glTranslatef(0,0,-1);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(0,0,1);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			printf("No es posible escalar la camara");
			break;
		}
		
		for(int i = 0; i < 16; i++){
			sig_matriz1->values[i] = matriz_rotada1[i];
			sig_matriz2->values[i] = matriz_rotada2[i];
		}
		sig_matriz1->sigptr = m1;
		_selected_camera->matrixobjptr = sig_matriz1;
		
		sig_matriz2->sigptr = m2;
		_selected_camera->matrixcsrptr = sig_matriz2;
	}
    	break;
    }
    case 105: //Av Pag
    {
    	if (modo == OBJETO){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);

		if(referencia == LOCAL){
	    		glLoadMatrixf(m->values);
	    	}
		else {
			glLoadIdentity();
		}
		
	    	if (rotar){
	    		glRotatef(10,0,0,1);
	    	}
	    	else if (trasladar){
	    		glTranslatef(0,0,1);
	    	}
	    	else if (escalar){
	    		glScalef(1,1,1.25);
	    	}
	    	
	    	if (referencia == GLOBAL){
	    		glMultMatrixf(m->values);
	    	}
	    	
	    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
		
		matrix *sig_matriz = malloc(sizeof (matrix));
		for(int i = 0; i < 16; i++){
			sig_matriz->values[i] = matriz_rotada[i];
		}
		sig_matriz->sigptr = m;
		_selected_object->matrixptr = sig_matriz;
	}
	else if(modo == CAMARA){
		GLfloat matriz_rotada1[16];
		GLfloat matriz_rotada2[16];
		matrix *m1 = _selected_camera->matrixobjptr;
		matrix *m2 = _selected_camera->matrixcsrptr;
		matrix *sig_matriz1 = malloc(sizeof (matrix));
		matrix *sig_matriz2 = malloc(sizeof (matrix));
		glMatrixMode(GL_MODELVIEW);
		if(rotar){
			glLoadMatrixf(m1->values);
			glRotatef(10,0,0,1);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glRotatef(10,0,0,-1);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(trasladar){
			glLoadMatrixf(m1->values);
			glTranslatef(0,0,1);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(0,0,-1);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			printf("No es posible escalar la camara");
			break;
		}
		
		for(int i = 0; i < 16; i++){
			sig_matriz1->values[i] = matriz_rotada1[i];
			sig_matriz2->values[i] = matriz_rotada2[i];
		}
		sig_matriz1->sigptr = m1;
		_selected_camera->matrixobjptr = sig_matriz1;
		
		sig_matriz2->sigptr = m2;
		_selected_camera->matrixcsrptr = sig_matriz2;
	}
    	break;
    }
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
        printf("special");
    }
    glutPostRedisplay();
}

