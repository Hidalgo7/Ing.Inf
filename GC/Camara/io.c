#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

int rotar = 0;
int trasladar = 1;
int escalar = 0;
char referencia[10] = "Local";

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

    case '-':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else if (escalar){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m->values);
	    	glScalef(0.9,0.9,0.9);
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
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else if (escalar){
	    	GLfloat matriz_rotada[16];
	    	matrix *m = _selected_object->matrixptr;
	    	glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m->values);
	    	glScalef(1.1,1.1,1.1);
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
    	if(strcmp(referencia,"Global") != 0){
    		strcpy(referencia,"Global");
    		printf("Sistema de referencia: %s\n",referencia);
    	}
    	break;
    case 'l':
    case 'L':
    	if(strcmp(referencia,"Local") != 0){
    		strcpy(referencia,"Local");
    		printf("Sistema de referencia: %s\n",referencia);
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
	if(_selected_object != 0){
	    	if(_selected_object->matrixptr != NULL){
	    		_selected_object->matrixptr = _selected_object->matrixptr->sigptr;
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
    	GLfloat matriz_rotada[16];
    	matrix *m = _selected_object->matrixptr;
    	glMatrixMode(GL_MODELVIEW);
    	
    	if(strcmp(referencia,"Local") == 0){
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
    		glScalef(0.9,1,1);
    	}
    	
    	if (strcmp(referencia,"Global") == 0){
    		glMultMatrixf(m->values);
    	}
    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
	
	matrix *sig_matriz = malloc(sizeof (matrix));
	for(int i = 0; i < 16; i++){
		sig_matriz->values[i] = matriz_rotada[i];
	}
	sig_matriz->sigptr = m;
	_selected_object->matrixptr = sig_matriz;
    	break;
    }
    case 101: //UP
    {
    	GLfloat matriz_rotada[16];
    	matrix *m = _selected_object->matrixptr;
    	glMatrixMode(GL_MODELVIEW);
    	
	if(strcmp(referencia,"Local") == 0){
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
    		glScalef(1,1.1,1);
    	}
    	
    	if (strcmp(referencia,"Global") == 0){
    		glMultMatrixf(m->values);
    	}
    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
	
	matrix *sig_matriz = malloc(sizeof (matrix));
	for(int i = 0; i < 16; i++){
		sig_matriz->values[i] = matriz_rotada[i];
	}
	sig_matriz->sigptr = m;
	_selected_object->matrixptr = sig_matriz;
    	break;
    }
    case 102: //RIGHT
    {
    	GLfloat matriz_rotada[16];
    	matrix *m = _selected_object->matrixptr;
    	glMatrixMode(GL_MODELVIEW);
    	
	if(strcmp(referencia,"Local") == 0){
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
    		glScalef(1.1,1,1);
    	}
    	
    	if (strcmp(referencia,"Global") == 0){
    		glMultMatrixf(m->values);
    	}
    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
	
	matrix *sig_matriz = malloc(sizeof (matrix));
	for(int i = 0; i < 16; i++){
		sig_matriz->values[i] = matriz_rotada[i];
	}
	sig_matriz->sigptr = m;
	_selected_object->matrixptr = sig_matriz;
    	break;
    }
    case 103: //DOWN
    {
    	GLfloat matriz_rotada[16];
    	matrix *m = _selected_object->matrixptr;
    	glMatrixMode(GL_MODELVIEW);

	if(strcmp(referencia,"Local") == 0){
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
    		glScalef(1,0.9,1);
    	}
    	
    	if (strcmp(referencia,"Global") == 0){
    		glMultMatrixf(m->values);
    	}
    	
    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
	
	matrix *sig_matriz = malloc(sizeof (matrix));
	for(int i = 0; i < 16; i++){
		sig_matriz->values[i] = matriz_rotada[i];
	}
	sig_matriz->sigptr = m;
	_selected_object->matrixptr = sig_matriz;
    	break;
    }
    
    case 104: //Re Pag
    {
    	GLfloat matriz_rotada[16];
    	matrix *m = _selected_object->matrixptr;
    	glMatrixMode(GL_MODELVIEW);

	if(strcmp(referencia,"Local") == 0){
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
    		glScalef(1,1,0.9);
    	}
    	
    	if (strcmp(referencia,"Global") == 0){
    		glMultMatrixf(m->values);
    	}
    	
    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
	
	matrix *sig_matriz = malloc(sizeof (matrix));
	for(int i = 0; i < 16; i++){
		sig_matriz->values[i] = matriz_rotada[i];
	}
	sig_matriz->sigptr = m;
	_selected_object->matrixptr = sig_matriz;
    	break;
    }
    case 105: //Av Pag
    {
    	GLfloat matriz_rotada[16];
    	matrix *m = _selected_object->matrixptr;
    	glMatrixMode(GL_MODELVIEW);

	if(strcmp(referencia,"Local") == 0){
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
    		glScalef(1,1,1.1);
    	}
    	
    	if (strcmp(referencia,"Global") == 0){
    		glMultMatrixf(m->values);
    	}
    	
    	glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada);
	
	matrix *sig_matriz = malloc(sizeof (matrix));
	for(int i = 0; i < 16; i++){
		sig_matriz->values[i] = matriz_rotada[i];
	}
	sig_matriz->sigptr = m;
	_selected_object->matrixptr = sig_matriz;
    	break;
    }
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
        printf("special");
    }
    glutPostRedisplay();
}

