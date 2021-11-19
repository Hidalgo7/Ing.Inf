#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"
#include "load_obj.h"


/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d * _first_object= 0;                /*List of objects*/
object3d * _selected_object = 0;            /*Object currently selected*/
    
camera * _first_camera = 0;		     /*List of cameras*/
camera * _selected_camera = 0;	     /*Selected camera*/
GLdouble zoom = 1;

/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;

    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);
    
    _first_camera = malloc( sizeof(camera) );
    GLfloat matriz_referencia[16];
    vector3* e;
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
    
    _first_camera->matrixcsrptr = m1;
    _first_camera->matrixobjptr = m2;
    
    _first_camera->proyection[0] = -0.1;
    _first_camera->proyection[1] = 0.1;
    _first_camera->proyection[2] = -0.1;
    _first_camera->proyection[3] = 0.1;
    _first_camera->proyection[4] = 0.1;
    _first_camera->proyection[5] = 10000;
    cargar_obj_camara(_first_camera);
    
    _first_camera->next = 0;
    _selected_camera = _first_camera;

    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
