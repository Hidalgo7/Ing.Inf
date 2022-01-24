#include "definitions.h"
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;
extern camera * _first_camera;
extern camera *_selected_camera;
extern int modo;
extern int proyection;
extern int flat_smooth;

extern light lights[4];
extern material materials[4];

void get_matriz_csr(GLfloat* m1,GLfloat* m2)
{
    for(int i = 0; i < 3; i++){
    	for (int j = 0; j < 3;j++){
    			m2[i+4*j] = m1[4*i+j];
    	}
    }
    m2[12] = -(m1[12]*m1[0]+m1[13]*m1[1]+m1[14]*m1[2]);
    m2[13] = -(m1[12]*m1[4]+m1[13]*m1[5]+m1[14]*m1[6]);
    m2[14] = -(m1[12]*m1[8]+m1[13]*m1[9]+m1[14]*m1[10]);
    m2[3] = 0;
    m2[7] = 0;
    m2[11] = 0;
    m2[15] = 1;
}

int poligono_delantero(object3d *o,face f){
	/*First we get the camera location*/
	vector3 e;
	if (modo == CAMARAOBJETO){
		e.x = _selected_object->matrixptr->values[12];
		e.y = _selected_object->matrixptr->values[13];
		e.z = _selected_object->matrixptr->values[14];
	}
	else{
		e.x = _selected_camera->matrixobjptr->values[12];
		e.y = _selected_camera->matrixobjptr->values[13];
		e.z = _selected_camera->matrixobjptr->values[14];
	}
	
	
	/*Then, we pass the camera location to the object reference system*/
	GLfloat csr_objeto[16];
	get_matriz_csr(o->matrixptr->values,csr_objeto);
	e.x = e.x*csr_objeto[0] + e.y*csr_objeto[4] + e.z*csr_objeto[8] + csr_objeto[12];
	e.y = e.x*csr_objeto[1] + e.y*csr_objeto[5] + e.z*csr_objeto[9] + csr_objeto[13];
	e.z = e.x*csr_objeto[2] + e.y*csr_objeto[6] + e.z*csr_objeto[10] + csr_objeto[14];
	
	/*Now we calculate the vector between the camera and the face*/
	
	vector3 v;
	vertex p_obj = o->vertex_table[f.vertex_table[0]];
	v.x = p_obj.coord.x - e.x;
	v.y = p_obj.coord.y - e.y;
	v.z = p_obj.coord.z - e.z;
	
	/*Finally we calculate the escalar product of the normal and the v vector to see the angle between them*/
	
	GLfloat escalar = v.x * f.normal.x + v.y * f.normal.y + v.z * f.normal.z;
	
	if(escalar > 0){
		return 0;
	}
	else{
		return 1;
	}
}

int poligono_delantero_cam(camera *c,face f){
	/*First we get the camera location*/
	vector3 e;
	if (modo == CAMARAOBJETO){
		e.x = _selected_object->matrixptr->values[12];
		e.y = _selected_object->matrixptr->values[13];
		e.z = _selected_object->matrixptr->values[14];
	}
	else{
		e.x = _selected_camera->matrixobjptr->values[12];
		e.y = _selected_camera->matrixobjptr->values[13];
		e.z = _selected_camera->matrixobjptr->values[14];
	}
	
	
	/*Then, we pass the camera location to the object reference system*/
	GLfloat csr_objeto[16];
	get_matriz_csr(c->matrixobjptr->values,csr_objeto);
	e.x = e.x*csr_objeto[0] + e.y*csr_objeto[4] + e.z*csr_objeto[8] + csr_objeto[12];
	e.y = e.x*csr_objeto[1] + e.y*csr_objeto[5] + e.z*csr_objeto[9] + csr_objeto[13];
	e.z = e.x*csr_objeto[2] + e.y*csr_objeto[6] + e.z*csr_objeto[10] + csr_objeto[14];
	
	/*Now we calculate the vector between the camera and the face*/
	
	vector3 v;
	vertex p_obj = c->vertex_table[f.vertex_table[0]];
	v.x = p_obj.coord.x - e.x;
	v.y = p_obj.coord.y - e.y;
	v.z = p_obj.coord.z - e.z;
	
	/*Finally we calculate the escalar product of the normal and the v vector to see the angle between them*/
	
	GLfloat escalar = v.x * f.normal.x + v.y * f.normal.y + v.z * f.normal.z;
	
	if(escalar > 0){
		return 0;
	}
	else{
		return 1;
	}
}

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(KG_MAX_DOUBLE,0,0);
    glVertex3d(-1*KG_MAX_DOUBLE,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,KG_MAX_DOUBLE,0);
    glVertex3d(0,-1*KG_MAX_DOUBLE,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,KG_MAX_DOUBLE);
    glVertex3d(0,0,-1*KG_MAX_DOUBLE);
    glEnd();
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}


/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;
    camera *aux_cam = _first_camera;

    /* Clear the screen */
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(proyection){
    	glFrustum(_selected_camera->proyection[0],_selected_camera->proyection[1],
    	_selected_camera->proyection[2],_selected_camera->proyection[3],
    	_selected_camera->proyection[4],_selected_camera->proyection[5]);	
    }
    else{
    	glOrtho(_selected_camera->proyection[0],_selected_camera->proyection[1],
    	_selected_camera->proyection[2],_selected_camera->proyection[3],
    	_selected_camera->proyection[4],_selected_camera->proyection[5]);
    }
    

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    
    glLoadMatrixf(lights[1].matrix);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, lights[1].ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[1].diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lights[1].specular);
    glLightfv(GL_LIGHT1, GL_POSITION, lights[1].position);

    glLoadMatrixf(lights[2].matrix);
    
    glLightfv(GL_LIGHT2, GL_AMBIENT, lights[2].ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lights[2].diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lights[2].specular);
    glLightfv(GL_LIGHT2, GL_POSITION, lights[2].position);

    /*First, we draw the axes*/
    draw_axes();

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {
    
    	    if(modo == CAMARAOBJETO){
		   matrix *aux_matrix = malloc( sizeof(matrix) );
		   get_matriz_csr(_selected_object->matrixptr->values,aux_matrix->values);
		   glLoadMatrixf(aux_matrix->values);
	    }
	    else{
		   glLoadMatrixf(_selected_camera->matrixcsrptr->values);
	    }
	    
	    	glLightfv(GL_LIGHT4, GL_AMBIENT, lights[4].ambient);
	    	glLightfv(GL_LIGHT4, GL_DIFFUSE, lights[4].diffuse);
	    	glLightfv(GL_LIGHT4, GL_SPECULAR, lights[4].specular);
	    	lights[4].position[0] = 0;
	    	lights[4].position[1] = 0;
	    	lights[4].position[2] = 0;
	    	lights[4].position[3] = 1;
	    	glLightfv(GL_LIGHT4, GL_POSITION, lights[4].position);
	    	GLfloat spot_direction[3];
	    	spot_direction[0] = 0;
		spot_direction[1] = 0;
	    	spot_direction[2] = 1;
	    	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);
	    	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, lights[4].cutoff);
	    
    
    	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[aux_obj->material].amb);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[aux_obj->material].dif);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials[aux_obj->material].spec);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materials[aux_obj->material].shiny * 128.0);

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }
	
	glMultMatrixf(aux_obj->matrixptr->values);
	
   	for (f = 0; f < aux_obj->num_faces; f++) {
	    int draw = poligono_delantero(aux_obj,aux_obj->face_table[f]);
	    if (draw){
	    	    /* Draw the object; for each face create a new polygon with the corresponding vertices */
	    	    glBegin(GL_POLYGON);
	    	    if (flat_smooth == FLAT){
	    	    	glNormal3f(aux_obj->face_table[f].normal.x,aux_obj->face_table[f].normal.y,aux_obj->face_table[f].normal.z);
	    	    }
		    for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
			v_index = aux_obj->face_table[f].vertex_table[v];
			if (flat_smooth == SMOOTH){
		    		glNormal3f(aux_obj->vertex_table[v_index].normal.x,aux_obj->vertex_table[v_index].normal.y,aux_obj->vertex_table[v_index].normal.z);
		    	}
			glVertex3d(aux_obj->vertex_table[v_index].coord.x,
			        aux_obj->vertex_table[v_index].coord.y,
			        aux_obj->vertex_table[v_index].coord.z);

	    	    }
		   glEnd();
	    }
	    
       }
       //If we are drawing the selected object, draw the box with its limits.
       if(_selected_object == aux_obj){
            glLightfv(GL_LIGHT3, GL_AMBIENT, lights[3].ambient);
    	    glLightfv(GL_LIGHT3, GL_DIFFUSE, lights[3].diffuse);
    	    glLightfv(GL_LIGHT3, GL_SPECULAR, lights[3].specular);
    	    lights[3].position[0] = aux_obj->max.x;
    	    lights[3].position[1] = aux_obj->max.y;
    	    lights[3].position[2] = aux_obj->max.z;
    	    lights[3].position[3] = 1;
    	    glLightfv(GL_LIGHT3, GL_POSITION, lights[3].position);
    	    GLfloat spot_direction[3];
    	    spot_direction[0] = 0;
            spot_direction[1] = 0;
    	    spot_direction[2] = 1;
    	    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
    	    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lights[3].cutoff);
       
            GLfloat vx = aux_obj->max.x - aux_obj->min.x;
            GLfloat vy = aux_obj->max.y - aux_obj->min.y;
            GLfloat vz = aux_obj->max.z - aux_obj->min.z;

            
            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x, aux_obj->min.y, aux_obj->min.z);
                glVertex3d(aux_obj->min.x, aux_obj->min.y+vy, aux_obj->min.z);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x, aux_obj->min.y+vy, aux_obj->min.z);
                glVertex3d(aux_obj->min.x+vx, aux_obj->min.y+vy, aux_obj->min.z);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x, aux_obj->min.y+vy, aux_obj->min.z);
                glVertex3d(aux_obj->min.x, aux_obj->min.y+vy, aux_obj->min.z+vz);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x, aux_obj->min.y, aux_obj->min.z);
                glVertex3d(aux_obj->min.x+vx, aux_obj->min.y, aux_obj->min.z);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x, aux_obj->min.y, aux_obj->min.z);
                glVertex3d(aux_obj->min.x, aux_obj->min.y, aux_obj->min.z+vz);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x, aux_obj->min.y, aux_obj->min.z+vz);
                glVertex3d(aux_obj->min.x, aux_obj->min.y+vy, aux_obj->min.z+vz);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->max.x, aux_obj->max.y, aux_obj->max.z);
                glVertex3d(aux_obj->max.x, aux_obj->max.y, aux_obj->max.z-vz);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->max.x, aux_obj->max.y, aux_obj->max.z);
                glVertex3d(aux_obj->max.x, aux_obj->max.y-vy, aux_obj->max.z);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->max.x, aux_obj->max.y, aux_obj->max.z);
                glVertex3d(aux_obj->max.x-vx, aux_obj->max.y, aux_obj->max.z);
            glEnd();

            glBegin(GL_LINES);
                glVertex3d(aux_obj->max.x, aux_obj->max.y-vy, aux_obj->max.z);
                glVertex3d(aux_obj->max.x, aux_obj->max.y-vy, aux_obj->max.z-vz);
            glEnd();

             glBegin(GL_LINES);
                glVertex3d(aux_obj->max.x, aux_obj->max.y-vy, aux_obj->max.z);
                glVertex3d(aux_obj->max.x-vx, aux_obj->max.y-vy, aux_obj->max.z);
            glEnd();
            
            glBegin(GL_LINES);
                glVertex3d(aux_obj->min.x+vx, aux_obj->min.y, aux_obj->min.z);
                glVertex3d(aux_obj->max.x, aux_obj->max.y, aux_obj->max.z-vz);
            glEnd();
    	}
       aux_obj = aux_obj->next;
    }
    
    while (aux_cam != 0) {
    	
    	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, aux_cam->material.amb);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, aux_cam->material.dif);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, aux_cam->material.spec);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, aux_cam->material.shiny * 128.0);
        /* We will draw the cameras blue */
        glColor3f(0.0,0.0,KG_COL_NONSELECTED_B);
        
        if (modo == CAMARAOBJETO){
        	matrix *aux_matrix = malloc( sizeof(matrix) );
		get_matriz_csr(_selected_object->matrixptr->values,aux_matrix->values);
		glLoadMatrixf(aux_matrix->values);
        }
        else{
        	glLoadMatrixf(_selected_camera->matrixcsrptr->values);
        }
        
        glMultMatrixf(aux_cam->matrixobjptr->values);
	
	/*If we are viewing from the camera we have to check not to draw the selected camera*/
	if (aux_cam != _selected_camera){
		
		/* Draw the camera; for each face create a new polygon with the corresponding vertices */
		for (f = 0; f < aux_cam->num_faces; f++) {
			int draw = poligono_delantero_cam(aux_cam,aux_cam->face_table[f]);
			if(draw){
				glBegin(GL_POLYGON);
				if (flat_smooth == FLAT){
					glNormal3f(aux_cam->face_table[f].normal.x,aux_cam->face_table[f].normal.y,aux_cam->face_table[f].normal.z);
				}
		    		for (v = 0; v < aux_cam->face_table[f].num_vertices; v++) {
		        		v_index = aux_cam->face_table[f].vertex_table[v];
		        		if (flat_smooth == SMOOTH){
		    				glNormal3f(aux_cam->vertex_table[v_index].normal.x,aux_cam->vertex_table[v_index].normal.y,aux_cam->vertex_table[v_index].normal.z);
		    			}
		        		glVertex3d(aux_cam->vertex_table[v_index].coord.x,
		                	aux_cam->vertex_table[v_index].coord.y,
		                	aux_cam->vertex_table[v_index].coord.z);
            	    		}
                   		glEnd();
			}
               }
	}
        aux_cam = aux_cam->next;
    }

    /*Do the actual drawing*/
    glutSwapBuffers();
}
