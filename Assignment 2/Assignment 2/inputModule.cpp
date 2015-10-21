/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: inputModule.c,v 1.2 2002/04/03 00:36:06 mshafae Exp $
 *
 */

#include <signal.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
//#include <unistd.h>

#include "inputModule.h"

#include "my_gl.h"
#include "testhelpers.h"

#define PI 3.14159265359

static int motionMode;
static int startX;
static int startY;
static GLfloat angle = 20;    /* in degrees */
static GLfloat angle2 = 30;   /* in degrees */
static GLfloat xdistance = 0.0;
static GLfloat ydistance = 0.0;
static GLfloat zdistance = 15.0;


void readKeyboard( unsigned char key, int x, int y ){
  switch( key ){
  case  0x1B: /* esc */
  case  'q':
//    kill( getpid(), SIGHUP );
    break; 
  case ' ':

    break;
  case ',':

    break;
  case '.':

    break;
  case 'r':
    /* reset initial view parameters */
    angle = 20; 
    angle2 = 30;
    xdistance = 0.0;
    ydistance = 0.0;
    zdistance = 5.0;
    break;
  default:
    break;
  }
  glutPostRedisplay( );
}

void readSpecialKeys( int key, int x, int y ){
  switch( key ){
  case GLUT_KEY_UP:

    break;
  case GLUT_KEY_DOWN:

    break;
  case GLUT_KEY_RIGHT:

    break;
  case GLUT_KEY_LEFT:

    break;
  }
  glutPostRedisplay( );
}

void mouseButtHandler(int button, int state, int x, int y)
{
  motionMode = 0;

  switch( button ){
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Rotate object */
      motionMode = 1;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    if( state == GLUT_DOWN ){
      /* Translate object */
      motionMode = 2;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Zoom */
      motionMode = 3;
      startX = x;
      startY = y;
    }
    break;
  }
  glutPostRedisplay( );
}

void mouseMoveHandler( int x, int y ){
  switch(motionMode){
  case 0:
    /* No mouse button is pressed... do nothing */
    /* return; */
    break;

  case 1:
    /* Calculate the rotations */
    angle = angle + (x - startX);
    angle2 = angle2 + (y - startY);
    startX = x;
    startY = y;
    break;

  case 2:
    xdistance = xdistance - (x - startX)/100.0;
    ydistance = ydistance - (y - startY)/100.0;
    startX = x;
    startY = y;
    break;

  case 3:
    zdistance = zdistance - (y - startY)/10.0;
    startX = x;
    startY = y;
    break;
  }

  glutPostRedisplay( );
}


void glTranslatef_Test()
{
	GLdouble tempmatrix[16];
	GLdouble newmatrix[16];
	// This operates the OpenGL way, retrieves the result and undoes it
	glPushMatrix();
	glTranslated(-xdistance, ydistance, -zdistance);
	glGetDoublev(GL_MODELVIEW_MATRIX, tempmatrix);
	glPopMatrix();
	// This uses your my_gl* functions, and will have effect
	my_glTranslated(-xdistance, ydistance, -zdistance);
	my_glGetMatrix(newmatrix);
	//printMat(newmatrix);
	//printMat(tempmatrix);
	if (compareMat(newmatrix, tempmatrix)) printf("Translate Matrix is wrong\n");
	// compareMat raises the flag if the matrices don't match. 
}


void glLoadIdentity_Test()
{
	GLdouble tempmatrix[16];
	GLdouble newmatrix[16];
	// This operates the OpenGL way, retrieves the result and undoes it
	glPushMatrix();
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, tempmatrix);
	glPopMatrix();
	// This uses your my_gl* functions, and will have effect
	my_glLoadIdentity();
	my_glGetMatrix(newmatrix); 
	//printMat(newmatrix);
	//printMat(tempmatrix);
	if (compareMat(newmatrix, tempmatrix)) printf("Identity Matrix is wrong\n");
	// compareMat raises the flag if the matrices don't match. 
}

void glRotatef_Test(GLfloat angleLocal,GLfloat x, GLfloat y, GLfloat z)
{
	GLdouble tempmatrix[16];
	GLdouble newmatrix[16];
	// This operates the OpenGL way, retrieves the result and undoes it
	glPushMatrix();
	glRotatef(angleLocal, x, y, z);
	glGetDoublev(GL_MODELVIEW_MATRIX, tempmatrix);
	glPopMatrix();
	// This uses your my_gl* functions, and will have effect
	my_glRotatef(angleLocal, x, y, z);
	my_glGetMatrix(newmatrix);
	//printMat(newmatrix);
	//printMat(tempmatrix);
	if (compareMat(newmatrix, tempmatrix)) printf("Rotate Matrix is wrong\n");
	// compareMat raises the flag if the matrices don't match. 
}


void setUserView(){

	//glLoadIdentity( );
	glLoadIdentity_Test();

	//distance(or radis for poalar) to center
	GLdouble rad = -zdistance; 
	GLdouble angle_rad = (360-angle) * PI / 180;
	GLdouble angle2_rad = (360- angle2) * PI / 180;

	// like converting polar to Cartesian, theta = angle 2, phi = angle 
	GLdouble eyeX = rad * sin(angle2_rad)* sin(angle_rad),
		eyeY = rad * cos(angle2_rad),
		eyeZ = rad * sin(angle2_rad) * cos(angle_rad);

	GLdouble upX = rad * sin(angle2_rad+0.1)* sin(angle_rad),
		upY = rad * cos(angle2_rad+0.1) ,
		upZ = rad * sin(angle2_rad + 0.1) * cos(angle_rad);
	
	gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, upX, upY, upZ);
	
	/*// glTranslatef( -xdistance, ydistance, -zdistance );
	glTranslatef_Test();

	//glRotatef( angle2, 1.0, 0.0, 0.0 );
	//glRotatef( angle, 0.0, 1.0, 0.0 );
	glRotatef_Test(angle2, 1.0, 0.0, 0.0);
	glRotatef_Test(angle, 0.0, 1.0, 0.0);*/
}

