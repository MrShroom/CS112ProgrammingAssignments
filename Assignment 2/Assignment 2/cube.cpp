/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: cube.c,v 1.1 2002/04/03 00:00:35 mshafae Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glut.h>
#include <signal.h>


#include "sceneModule.h"
#include "viewModule.h"
#include "inputModule.h"

#include "my_gl.h"

int window;
int updateFlag;
GLdouble angle = 0;

perspectiveData pD;

#ifdef __cplusplus
extern "C"
#endif
void cleanup( int sig ){
  // insert cleanup code here (i.e. deleting structures or so)
  exit( 0 );
}


//##########################################3
// OpenGL Display function
#ifdef __cplusplus
extern "C"
#endif
void display( void ){
  glutSetWindow(window);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f( 1.0, 1.0, 1.0 );

  /* Set up where the projection */
  setUserView( );
  /* Draw the scene into the back buffer */
  //drawScene();
  glPushMatrix();
  if (angle >= 360) angle -= 360;
  glRotated(angle += .1, 0, 1, 0);
  glScaled(2, 2, 2);
  drawScene();
  glPopMatrix();

  glPushMatrix();
  glRotated(angle , 0, 1, 0);
  glTranslated(10, 0, 0);
  drawScene();
  glPopMatrix();
  /* Swap the front buffer with the back buffer - assumes double buffering */

  glutSwapBuffers( ); 


}

//##########################################
// Init display settings
#ifdef __cplusplus
extern "C"
#endif
void initDisplay( ){
  /* Perspective projection parameters */
  pD.fieldOfView = 45.0;
  pD.aspect      = (float)IMAGE_WIDTH/IMAGE_HEIGHT;
  pD.nearPlane   = 0.1;
  pD.farPlane    = 50.0;

  /* setup context */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluPerspective( pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane );

  glEnable( GL_DEPTH_TEST );
  glDisable( GL_CULL_FACE );

  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  glClearIndex( 0 );
  glClearDepth( 1 );

  glMatrixMode( GL_MODELVIEW );
}

//##########################################
// Main function

int main( int argc, char **argv ){
//  signal( SIGHUP, cleanup );

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |
                       GLUT_DEPTH | GLUT_MULTISAMPLE );

  glutInitWindowSize( IMAGE_WIDTH,IMAGE_HEIGHT );

  /* glutInitWindowPosition(0,0); */
  window = glutCreateWindow( argv[0] );

  /* Register the appropriate callback functions with GLUT */
  glutDisplayFunc( display );
  glutKeyboardFunc( readKeyboard );
  glutMouseFunc( mouseButtHandler );
  glutMotionFunc( mouseMoveHandler );
  glutPassiveMotionFunc( mouseMoveHandler );
  glutIdleFunc(display);

  initDisplay( );

  /* This function doesn't return - put all clean up code in
   * the cleanup function */
  glutMainLoop( );

  /* ANSI C requires main to return an int. */
  return( 0 );
}
