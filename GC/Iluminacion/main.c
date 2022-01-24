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

light lights[5];			     /*List of lights
						1.Sun
						2.Bulb
                                              3.Object spotlight
                                              4.Camera spotlight */
                                              
material materials[4];			     /*List of materials
						1.Emerald
						2.Ruby
                                              3.Red plastic
                                              4.Yellow rubber */

int flat_smooth = 0;

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
    /*Initialize the values for the default camera*/
    _first_camera = malloc( sizeof(camera) );
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
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    
    //Initialize the sun light parameters
    lights[1].ambient[0] = 0.8;
    lights[1].ambient[1] = 0.8;
    lights[1].ambient[2] = 0.8;
    lights[1].ambient[3] = 1;
    
    lights[1].diffuse[0] = 0.5;
    lights[1].diffuse[1] = 0.5;
    lights[1].diffuse[2] = 0.5;
    lights[1].diffuse[3] = 1;
    
    lights[1].specular[0] = 0.5;
    lights[1].specular[1] = 0.5;
    lights[1].specular[2] = 0.5;
    lights[1].specular[3] = 1;
    
    lights[1].position[0] = 10;
    lights[1].position[1] = 10;
    lights[1].position[2] = 10;
    lights[1].position[3] = 1;
    
    //Light proyection matrix initialize 
    
    for(int i = 0; i < 16; i++){
        lights[1].matrix[i] = 0;
    }
    
    lights[1].matrix[0] = 1;
    lights[1].matrix[5] = 1;
    lights[1].matrix[10] = 1;
    lights[1].matrix[15] = 1;
    
    //Initialize lightbulb parameters
    lights[2].ambient[0] = 0.2;
    lights[2].ambient[1] = 0.2;
    lights[2].ambient[2] = 0.2;
    lights[2].ambient[3] = 1;
    
    lights[2].diffuse[0] = 0.3;
    lights[2].diffuse[1] = 0.3;
    lights[2].diffuse[2] = 0.3;
    lights[2].diffuse[3] = 1;
    
    lights[2].specular[0] = 0.5;
    lights[2].specular[1] = 0.5;
    lights[2].specular[2] = 0.5;
    lights[2].specular[3] = 1;
    
    lights[2].position[0] = 0;
    lights[2].position[1] = 7;
    lights[2].position[2] = 0;
    lights[2].position[3] = 1;
    
    for(int i = 0; i < 16; i++){
        lights[2].matrix[i] = 0;
    }
    
    lights[2].matrix[0] = 1;
    lights[2].matrix[5] = 1;
    lights[2].matrix[10] = 1;
    lights[2].matrix[15] = 1;
    
    //Initialize object spotlight
    lights[3].ambient[0] = 0.4;
    lights[3].ambient[1] = 0.4;
    lights[3].ambient[2] = 0.4;
    lights[3].ambient[3] = 1;
    
    lights[3].diffuse[0] = 0.3;
    lights[3].diffuse[1] = 0.3;
    lights[3].diffuse[2] = 0.3;
    lights[3].diffuse[3] = 1;
    
    
    lights[3].specular[0] = 0.7;
    lights[3].specular[1] = 0.7;
    lights[3].specular[2] = 0.7;
    lights[3].specular[3] = 1;
    
    lights[3].cutoff = 90.0;
    
    //Initialize camera spotlight
    lights[4].ambient[0] = 0.4;
    lights[4].ambient[1] = 0.4;
    lights[4].ambient[2] = 0.4;
    lights[4].ambient[3] = 1;
    
    lights[4].diffuse[0] = 0.3;
    lights[4].diffuse[1] = 0.3;
    lights[4].diffuse[2] = 0.3;
    lights[4].diffuse[3] = 1;
    
    
    lights[4].specular[0] = 0.7;
    lights[4].specular[1] = 0.7;
    lights[4].specular[2] = 0.7;
    lights[4].specular[3] = 1;
    
    lights[4].cutoff = 90.0;
    
    //Initialize emerald material
    materials[0].amb[0] = 0.0215;
    materials[0].amb[1] = 0.1745;
    materials[0].amb[2] = 0.0215;
    materials[0].dif[0] = 0.07568;
    materials[0].dif[1] = 0.61424;
    materials[0].dif[2] = 0.07568;
    materials[0].spec[0] = 0.633;
    materials[0].spec[1] = 0.727811;
    materials[0].spec[2] = 0.633;
    materials[0].shiny = 0.6;
    
    //Initialize ruby material
    materials[1].amb[0] = 0.1745;
    materials[1].amb[1] = 0.01175;
    materials[1].amb[2] = 0.01175;
    materials[1].dif[0] = 0.61424;
    materials[1].dif[1] = 0.04136;
    materials[1].dif[2] = 0.04136;
    materials[1].spec[0] = 0.727811;
    materials[1].spec[1] = 0.626959;
    materials[1].spec[2] = 0.626959;
    materials[1].shiny = 0.6;
    
    //Initialize cyan plastic material
    materials[2].amb[0] = 0.0;
    materials[2].amb[1] = 0.1;
    materials[2].amb[2] = 0.06;
    materials[2].dif[0] = 0.0;
    materials[2].dif[1] = 0.50980392;
    materials[2].dif[2] = 0.50980392;
    materials[2].spec[0] = 0.50196078;
    materials[2].spec[1] = 0.50196078;
    materials[2].spec[2] = 0.50196078;
    materials[2].shiny = 0.25;
    
    //Initialize yellow rubber material
    materials[3].amb[0] = 0.05;
    materials[3].amb[1] = 0.05;
    materials[3].amb[2] = 0.0;
    materials[3].dif[0] = 0.5;
    materials[3].dif[1] = 0.5;
    materials[3].dif[2] = 0.4;
    materials[3].spec[0] = 0.7;
    materials[3].spec[1] = 0.7;
    materials[3].spec[2] = 0.04;
    materials[3].shiny = 0.078125;
    
    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);
    
    glEnable(GL_DEPTH_TEST);
    
    if(flat_smooth == SMOOTH) glShadeModel(GL_SMOOTH);
    else glShadeModel(GL_FLAT);
    

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
