#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

extern object3d * _first_object;
extern object3d * _selected_object;
extern camera * _first_camera;
extern camera * _selected_camera;

extern light lights[4];

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern int flat_smooth;

int rotar = 0;
int trasladar = 1;
int escalar = 0;

int referencia = 0;
int modo = 0;

int proyection = 1;
int vista = 0;

int luz = 1;

void cargar_obj_camara(camera *cam){
    object3d auxiliar_object;
    read_wavefront("camara.obj", &auxiliar_object);

    /*There is not error treatment because camara.obj will always be there*/

    cam->face_table = auxiliar_object.face_table;
    cam->num_faces = auxiliar_object.num_faces;
    cam->vertex_table = auxiliar_object.vertex_table;
    cam->num_vertices = auxiliar_object.num_vertices;
    cam->max = auxiliar_object.max;
    cam->min = auxiliar_object.min;
    
    cam->material.amb[0] = 0.0;
    cam->material.amb[1] = 0.0;
    cam->material.amb[2] = 0.0;
    cam->material.dif[0] = 0.01;
    cam->material.dif[1] = 0.01;
    cam->material.dif[2] = 0.01;
    cam->material.spec[0] = 0.5;
    cam->material.spec[1] = 0.5;
    cam->material.spec[2] = 0.5;
    cam->material.shiny = 0.25;

}

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

void mirar_obj_selec(){
		vector3 obj,cam;
		obj.x = _selected_object->matrixptr->values[12];
		obj.y = _selected_object->matrixptr->values[13];
		obj.z = _selected_object->matrixptr->values[14];
		cam.x = _selected_camera->matrixobjptr->values[12];
		cam.y = _selected_camera->matrixobjptr->values[13];
		cam.z = _selected_camera->matrixobjptr->values[14];
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cam.x,cam.y,cam.z,obj.x,obj.y,obj.z,0,1,0);
		glGetFloatv(GL_MODELVIEW_MATRIX,_selected_camera->matrixcsrptr->values);
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
    printf("<P>\t\t Alternar perspectiva/paralelo\n");
    printf("<F9>\t\t Activar/Desactivar iluminación\n");
    printf("<F9>\t\t Cambiar iluminación flat/smooth\n");
    printf("<F1-F4>\t\t Activar/Desactivar iluminación\n");
    printf("<1-4>\t\t Seleccionar luces");
    printf("<O>\t\t Modo Objeto\n");
    printf("<C>\t\t Modo Cámara\n");
    printf("<A>\t\t Modo Iluminación\n");
    printf("<G>\t\t Referencia global / Modo Análisis\n");
    printf("<L>\t\t Referencia local / Modo Vuelo\n\n");
    printf("<R>\t\t Activar rotacion\n");
    printf("<T>\t\t Activar traslacion\n");
    printf("<E>\t\t Activar escalado\n");
    printf("<n>\t\t Crear una nueva camara\n");
    printf("<k>\t\t Navegar entre las camaras\n");
    printf("<K>\t\t Vista de objeto seleccionado\n");
    printf("<UP> \t\t Trasladar +Y; Escalar + Y; Rotar +X\n");
    printf("<DOWN> \t\t Trasladar -Y; Escalar - Y;  Rotar -X\n");
    printf("<RIGHT> \t Trasladar +X; Escalar +X;  Rotar +Y\n");
    printf("<LEFT> \t\t Trasladar -X; Escalar -X;  Rotar -Y\n");
    printf("<AVPAG> \t Trasladar +Z; Escalar +X;  Rotar +Y\n");
    printf("<REPAG> \t Trasladar -Z; Escalar -Z; Rotar -Z\n");
    printf("<+> \t\t Escalar + / Ampliar campo de vision / Incrementar angulo de apertura\n");
    printf("<-> \t\t Escalar - / Reducir campo de vision / Decrementar angulo de apertura\n");
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
		vector3* e = malloc( sizeof(vector3) );
		e->x = 10;
		e->y = 10;
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
		
		auxiliar_camera->proyection[0] = -0.1;
		auxiliar_camera->proyection[1] = 0.1;
		auxiliar_camera->proyection[2] = -0.1;
		auxiliar_camera->proyection[3] = 0.1;
		auxiliar_camera->proyection[4] = 0.1;
		auxiliar_camera->proyection[5] = 10000;
		
		cargar_obj_camara(auxiliar_camera);
		
		auxiliar_camera->next = _first_camera;
		_first_camera = auxiliar_camera;
		_selected_camera = _first_camera;
		
		
		
		if(vista == ANALISIS){
			mirar_obj_selec();
		}
		break;
	}
	case 9: /* <TAB> */
	     if(_selected_object != NULL){
		_selected_object = _selected_object->next;
		/*The selection is circular, thus if we move out of the list we go back to the first element*/
		if (_selected_object == 0) _selected_object = _first_object;
		if(vista == ANALISIS){
			mirar_obj_selec();
		}
	     }
	     else{
		printf("No hay ningun objeto cargado\n");
             }
	     break; 
	
	case 'k':
	     	_selected_camera = _selected_camera->next;
	     	if(_selected_camera == 0) _selected_camera = _first_camera;
	     	if (vista == ANALISIS){
	     		mirar_obj_selec();
	     	}
	     	break;
	case 'K':
	     if (modo != CAMARAOBJETO){
	     	modo = CAMARAOBJETO;
	     	printf("Punto de vista del objeto\n");
	     }
	     else{
	     	modo = CAMARA;
	     	printf("Modo: Camara\n");
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
		if (vista == ANALISIS){
			mirar_obj_selec();
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
    
    case 'a':
    case 'A':
    	if (modo != ILUMINACION){
    		modo = ILUMINACION;
    		printf("Modo: Iluminacion\n");
    	}
    	break;
    case 'p':
    case 'P':
    	proyection = 1 - proyection;
    	if(proyection){
    		printf("Modo de vista: Perspectiva\n");
    		_selected_camera->proyection[0] = -0.1;
    		_selected_camera->proyection[1] = 0.1;
    		_selected_camera->proyection[2] = -0.1;
    		_selected_camera->proyection[3] = 0.1;
    		_selected_camera->proyection[4] = 0.1;
    		_selected_camera->proyection[5] = 10000;
    	}
    	else{
    		printf("Modo de vista: Paralelo\n");
    		_selected_camera->proyection[0] = _ortho_x_min;
    		_selected_camera->proyection[1] = _ortho_x_max;
    		_selected_camera->proyection[2] = _ortho_y_min;
    		_selected_camera->proyection[3] = _ortho_y_max;
    		_selected_camera->proyection[4] = 0;
    		_selected_camera->proyection[5] = _ortho_z_max;
    	}
    	break;
    case '-':
        if(modo == CAMARA){
        	_selected_camera->proyection[0] = _selected_camera->proyection[0]-0.01;
        	_selected_camera->proyection[1] = _selected_camera->proyection[1]+0.01;
        	_selected_camera->proyection[2] = _selected_camera->proyection[2]-0.01;
        	_selected_camera->proyection[3] = _selected_camera->proyection[3]+0.01;
        }
        else if(modo == OBJETO){
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
	}
	else if(modo == ILUMINACION){
        	if (luz == 3 || luz == 4){
        		if(lights[luz].cutoff > 30){
        			lights[luz].cutoff -=10;
        		}
        		else{
        			printf("Angulo minimo de foco\n");
        		}
        	}
        	else{
        		printf("La luz seleccionada no es un foco\n");
        	}
        }
        break;
        
    case '+':
        if(modo == CAMARA){
        	if(escalar){
        	_selected_camera->proyection[0] = _selected_camera->proyection[0]+0.01;
        	_selected_camera->proyection[1] = _selected_camera->proyection[1]-0.01;
        	_selected_camera->proyection[2] = _selected_camera->proyection[2]+0.01;
        	_selected_camera->proyection[3] = _selected_camera->proyection[3]-0.01;
        	}
        }
        else if(modo == OBJETO){
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
        }
        else if(modo == ILUMINACION){
        	if (luz == 3 || luz == 4){
        		if(lights[luz].cutoff < 160){
        			lights[luz].cutoff +=10;
        		}
        		else{
        			printf("Angulo maximo de foco\n");
        		}
        	}
        	else{
        		printf("La luz seleccionada no es un foco\n");
        	}
        }
        break;

    case '?':
        print_help();
        break;
        
    case 'g':
    case 'G':
    	if (modo == CAMARA){
    		if(vista != ANALISIS){
    			vista = ANALISIS;
    			printf("Vista de la camara: Analisis\n");
    			mirar_obj_selec();
    		}
    	}
    	else if(modo == OBJETO){
	    	if(referencia != GLOBAL){
	    		referencia = GLOBAL;
	    		printf("Sistema de referencia: Global\n");
	    	}
    	}
    	break;
    case 'l':
    case 'L':
    	if (modo == CAMARA){
    		if(vista != VUELO){
    			vista = VUELO;
    			printf("Vista de la camara: Vuelo\n");
    		}
    	}
    	else if (modo == OBJETO){
    		if(referencia != LOCAL){
    			referencia = LOCAL;
    			printf("Sistema de referencia: Local\n");
    		}
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
    case '1':
    	if (modo == ILUMINACION){
    		luz = 1;
    		printf("Luz 1 seleccionada.(Sol)\n");
    	}
    	break;
    case '2':
    	if (modo == ILUMINACION){
    		luz = 2;
    		printf("Luz 2 seleccionada.(Bombilla)\n");
    	}
    	break;
    case '3':
    	if (modo == ILUMINACION){
    		luz = 3;
    		printf("Luz 3 seleccionada.(Foco del objeto)\n");
    	}
    	break;
    case '4':
    	if (modo == ILUMINACION){
    		luz = 4;
    		printf("Luz 4 seleccionada.(Foco de la camara)\n");
    	}
    	break;
    	
    case 'm':
    case 'M':
    	if (_selected_object != 0 && modo == OBJETO){
    		if (_selected_object->material != 3){
    			_selected_object->material++;
    		}
    		else{
    			_selected_object->material = 0;
    		}
    	}
    	break;
    case 26:
	if(_selected_object != 0){
	    	if(_selected_object->matrixptr->sigptr != 0){
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
        printf("keyboard\n");
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
    	if(modo == OBJETO || modo == CAMARAOBJETO){
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
		if(vista == ANALISIS){
			vector3 e;
			e.x = _selected_object->matrixptr->values[12];
			e.y = _selected_object->matrixptr->values[13];
			e.z = _selected_object->matrixptr->values[14];
			glLoadIdentity();
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,0,-1,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glMultMatrixf(m1->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadMatrixf(m2->values);
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,0,1,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(vista == VUELO){
			if(rotar || trasladar){
				glLoadMatrixf(m1->values);
				glRotatef(10,0,1,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
				glLoadIdentity();
				glRotatef(10,0,-1,0);
				glMultMatrixf(m2->values);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
			}
			else if(escalar){
				_selected_camera->proyection[0] = _selected_camera->proyection[0]+0.001;
        			_selected_camera->proyection[1] = _selected_camera->proyection[1]+0.001;
			break;
			}
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
	else if (modo == ILUMINACION){
		GLfloat matriz_anterior[16];
		GLfloat matriz_nueva[16];
		
		for(int i = 0; i < 16; i++){
			matriz_anterior[i] = lights[luz].matrix[i];
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matriz_anterior);
		if (rotar){
			if (luz == 1 || luz == 2){
				vector3 e;
				e.x = _selected_object->matrixptr->values[12];
				e.y = _selected_object->matrixptr->values[13];
				e.z = _selected_object->matrixptr->values[14];
				glTranslatef(e.x,e.y,e.z);
				glRotatef(10,0,-1,0);
				glTranslatef(-e.x,-e.y,-e.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(trasladar){
			if (luz == 1){
				printf("No se puede trasladar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glTranslatef(-1,0,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(escalar){
			if (luz == 1){
				printf("No se puede escalar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glScalef(0.8,1,1);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		for(int i = 0; i < 16; i++){
			lights[luz].matrix[i] = matriz_nueva[i];
		}

		
	}
    	break;
    }
    case 101: //UP
    {
    	if(modo == OBJETO || modo == CAMARAOBJETO){
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
		if(vista == ANALISIS){
			vector3 e;
			e.x = _selected_object->matrixptr->values[12];
			e.y = _selected_object->matrixptr->values[13];
			e.z = _selected_object->matrixptr->values[14];
			glLoadIdentity();
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,-1,0,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glMultMatrixf(m1->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadMatrixf(m2->values);
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,1,0,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if (vista == VUELO){
			if(rotar || trasladar){
				glLoadMatrixf(m1->values);
				glRotatef(10,1,0,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
				glLoadIdentity();
				glRotatef(10,-1,0,0);
				glMultMatrixf(m2->values);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
			}
			else if(escalar){
				_selected_camera->proyection[2] = _selected_camera->proyection[2]+0.001;
        			_selected_camera->proyection[3] = _selected_camera->proyection[3]+0.001;
				break;
			}
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
	else if (modo == ILUMINACION){
		GLfloat matriz_anterior[16];
		GLfloat matriz_nueva[16];
		for(int i = 0; i < 16; i++){
			matriz_anterior[i] = lights[luz].matrix[i];
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matriz_anterior);
		if (rotar){
			if (luz == 1 || luz == 2){
				vector3 e;
				e.x = _selected_object->matrixptr->values[12];
				e.y = _selected_object->matrixptr->values[13];
				e.z = _selected_object->matrixptr->values[14];
				glTranslatef(e.x,e.y,e.z);
				glRotatef(10,1,0,0);
				glTranslatef(-e.x,-e.y,-e.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(trasladar){
			if (luz == 1){
				printf("No se puede trasladar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glTranslatef(0,1,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(escalar){
			if (luz == 1){
				printf("No se puede escalar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glScalef(1,1.25,1);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		for(int i = 0; i < 16; i++){
			lights[luz].matrix[i] = matriz_nueva[i];
		}

	}
	
    	break;
    }
    case 102: //RIGHT
    {
    	if(modo == OBJETO || modo == CAMARAOBJETO){
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
		if(vista == ANALISIS){
			vector3 e;
			e.x = _selected_object->matrixptr->values[12];
			e.y = _selected_object->matrixptr->values[13];
			e.z = _selected_object->matrixptr->values[14];
			
			glLoadIdentity();
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,0,1,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glMultMatrixf(m1->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			
			glLoadMatrixf(m2->values);
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,0,-1,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(vista == VUELO){
			if(rotar || trasladar){
				glLoadMatrixf(m1->values);
				glRotatef(10,0,-1,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
				glLoadIdentity();
				glRotatef(10,0,1,0);
				glMultMatrixf(m2->values);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
			}
			else if(escalar){
				_selected_camera->proyection[0] = _selected_camera->proyection[0]+0.001;
				_selected_camera->proyection[1] = _selected_camera->proyection[1]+0.001;
				break;
			}
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
	else if (modo == ILUMINACION){
		GLfloat matriz_anterior[16];
		GLfloat matriz_nueva[16];
		for(int i = 0; i < 16; i++){
			matriz_anterior[i] = lights[luz].matrix[i];
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matriz_anterior);
		if (rotar){
			if (luz == 1 || luz == 2){
				vector3 e;
				e.x = _selected_object->matrixptr->values[12];
				e.y = _selected_object->matrixptr->values[13];
				e.z = _selected_object->matrixptr->values[14];
				glTranslatef(e.x,e.y,e.z);
				glRotatef(10,0,1,0);
				glTranslatef(-e.x,-e.y,-e.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(trasladar){
			if (luz == 1){
				printf("No se puede trasladar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glTranslatef(1,0,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(escalar){
			if (luz == 1){
				printf("No se puede escalar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glScalef(1.25,1,1);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		
		for(int i = 0; i < 16; i++){
			lights[luz].matrix[i] = matriz_nueva[i];
		}
		
	}
	
    	break;
    }
    case 103: //DOWN
    {
    	if(modo == OBJETO || modo == CAMARAOBJETO){
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
		if(vista == ANALISIS){
			vector3 e;
			e.x = _selected_object->matrixptr->values[12];
			e.y = _selected_object->matrixptr->values[13];
			e.z = _selected_object->matrixptr->values[14];
			glLoadIdentity();
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,1,0,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glMultMatrixf(m1->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadMatrixf(m2->values);
			glTranslatef(e.x,e.y,e.z);
			glRotatef(10,-1,0,0);
			glTranslatef(-e.x,-e.y,-e.z);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(vista == VUELO){
			if(rotar || trasladar){
				glLoadMatrixf(m1->values);
				glRotatef(10,-1,0,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
				glLoadIdentity();
				glRotatef(10,1,0,0);
				glMultMatrixf(m2->values);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
			}
			else if(escalar){
				_selected_camera->proyection[2] = _selected_camera->proyection[2]-0.001;
				_selected_camera->proyection[3] = _selected_camera->proyection[3]-0.001;
				break;
			}
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
	
	else if (modo == ILUMINACION){
		GLfloat matriz_anterior[16];
		GLfloat matriz_nueva[16];
		for(int i = 0; i < 16; i++){
			matriz_anterior[i] = lights[luz].matrix[i];
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matriz_anterior);
		if (rotar){
			if (luz == 1 || luz == 2){
				vector3 e;
				e.x = _selected_object->matrixptr->values[12];
				e.y = _selected_object->matrixptr->values[13];
				e.z = _selected_object->matrixptr->values[14];
				glTranslatef(e.x,e.y,e.z);
				glRotatef(10,-1,0,0);
				glTranslatef(-e.x,-e.y,-e.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(trasladar){
			if (luz == 1){
				printf("No se puede trasladar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glTranslatef(0,-1,0);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(escalar){
			if (luz == 1){
				printf("No se puede escalar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glScalef(1,0.8,1);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		
		for(int i = 0; i < 16; i++){
			lights[luz].matrix[i] = matriz_nueva[i];
		}
		
	}
	break;
    }
    
    case 104: //Re Pag
    {
    	if (modo == OBJETO || modo == CAMARAOBJETO){
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
			glTranslatef(0,0,1);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(0,0,-1);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
			_selected_camera->proyection[4] = _selected_camera->proyection[4]+0.001;
        		_selected_camera->proyection[5] = _selected_camera->proyection[5]+100;
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
	else if(modo == ILUMINACION){
		GLfloat matriz_anterior[16];
		GLfloat matriz_nueva[16];
		for(int i = 0; i < 16; i++){
			matriz_anterior[i] = lights[luz].matrix[i];
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matriz_anterior);
		if (rotar){
			if (luz == 1 || luz == 2){
				vector3 e;
				e.x = _selected_object->matrixptr->values[12];
				e.y = _selected_object->matrixptr->values[13];
				e.z = _selected_object->matrixptr->values[14];
				glTranslatef(e.x,e.y,e.z);
				glRotatef(10,0,0,-1);
				glTranslatef(-e.x,-e.y,-e.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(trasladar){
			if (luz == 1){
				printf("No se puede trasladar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glTranslatef(0,0,-1);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(escalar){
			if (luz == 1){
				printf("No se puede escalar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glScalef(1,1,0.8);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		
		for(int i = 0; i < 16; i++){
			lights[luz].matrix[i] = matriz_nueva[i];
		}
	}
    	break;
    }
    case 105: //Av Pag
    {
    	if (modo == OBJETO || modo == CAMARAOBJETO){
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
			glTranslatef(0,0,-1);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada1);
			glLoadIdentity();
			glTranslatef(0,0,1);
			glMultMatrixf(m2->values);
			glGetFloatv(GL_MODELVIEW_MATRIX,matriz_rotada2);
		}
		else if(escalar){
        		_selected_camera->proyection[4] = _selected_camera->proyection[4]-0.001;
        		_selected_camera->proyection[5] = _selected_camera->proyection[5]-100;
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
	else if(modo == ILUMINACION){
		GLfloat matriz_anterior[16];
		GLfloat matriz_nueva[16];
		for(int i = 0; i < 16; i++){
			matriz_anterior[i] = lights[luz].matrix[i];
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matriz_anterior);
		if (rotar){
			if (luz == 1 || luz == 2){
				vector3 e;
				e.x = _selected_object->matrixptr->values[12];
				e.y = _selected_object->matrixptr->values[13];
				e.z = _selected_object->matrixptr->values[14];
				glTranslatef(e.x,e.y,e.z);
				glRotatef(10,0,0,1);
				glTranslatef(-e.x,-e.y,-e.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(trasladar){
			if (luz == 1){
				printf("No se puede trasladar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glTranslatef(0,0,1);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		else if(escalar){
			if (luz == 1){
				printf("No se puede escalar el sol.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else if (luz == 2){
				glScalef(1,1,1.25);
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
			else{
				printf("No se pueden transformar los focos.\n");
				glGetFloatv(GL_MODELVIEW_MATRIX,matriz_nueva);
			}
		}
		
		for(int i = 0; i < 16; i++){
			lights[luz].matrix[i] = matriz_nueva[i];
		}
	}
    	break;
    }
    case 1: //F1
    	if (glIsEnabled(GL_LIGHT1)){
    		glDisable(GL_LIGHT1);
    		printf("Luz 1 apagada.(Sol)\n");
    	}
    	else{
    		glEnable(GL_LIGHT1);
    		printf("Luz 1 encendida.(Sol)\n");
    	}
    	break;
    	
    case 2: //F2
    	if (glIsEnabled(GL_LIGHT2)){
    		glDisable(GL_LIGHT2);
    		printf("Luz 2 apagada.(Bombilla)\n");
    	}
    	else{
    		glEnable(GL_LIGHT2);
    		printf("Luz 2 encendida.(Bombilla)\n");
    	}
    	break;
    case 3: //F3
    	if (glIsEnabled(GL_LIGHT3)){
    		glDisable(GL_LIGHT3);
    		printf("Luz 3 apagada.(Foco del objeto)\n");
    	}
    	else{
    		glEnable(GL_LIGHT3);
    		printf("Luz 3 encendida.(Foco del objeto)\n");
    	}
    	break;
    case 4: //F3
    	if (glIsEnabled(GL_LIGHT4)){
    		glDisable(GL_LIGHT4);
    		printf("Luz 4 apagada.(Foco de la camara)\n");
    	}
    	else{
    		glEnable(GL_LIGHT4);
    		printf("Luz 4 encendida.(Foco de la camara)\n");
    	}
    	break;
    case 9: //F9
    	if (glIsEnabled(GL_LIGHTING)){
    		glDisable(GL_LIGHTING);
    		glPolygonMode(GL_FRONT, GL_LINE);
    	}
    	else{
    		glEnable(GL_LIGHTING);
    		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    	}
    	break;
    case 12: //F12
    	flat_smooth = 1 - flat_smooth;
    	break;
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
        printf("special\n");
    }
    glutPostRedisplay();
}

