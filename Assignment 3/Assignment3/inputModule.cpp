
#include <sys/types.h>
#include "inputModule.h"
#include "PLY.h"
#include "geometry.h"

/* This File contains the KeyBoard and mouse handling routines */
static int motionMode;
static int startX;
static int startY;
static GLfloat angle = 20;    /* in degrees */
static GLfloat angle2 = 30;   /* in degrees */
static GLfloat angle_l = 20;    /* in degrees */
static GLfloat angle2_l = 30;   /* in degrees */

extern Vector3f light_pos, initial_light_pos;

GLfloat current_pos[] = {0.0, 0.0, 5.0};
GLfloat cinitial_light_pos[] = { -100.0, 100.0, 100.0, 0.0 };

int flat = 0;
int light = 1;
int mov_light = -1;
int wire = 0;

extern PLYObject* ply;

void readKeyboard(unsigned char key, int x, int y)
{
  switch(key){
  case  0x1B:
  case  'q':
  case  'Q':
    exit(0);
    break; 
  case '+':
    if (ply)
      ply->eat();
    break;
  case '-':
    if (ply)
      ply->starve();
    break;
  case 'd':
    if (ply)
      ply->dance();
    break;
  case 'i':
  case 'I':
    if (ply)
      ply->invertNormals();
    break;
  case 'l':
  case 'L':
    light = (light + 1) % 2;
		printf("%s lighting\n", (light ? "OpenGL" : "User"));
    break;
  case 't':
  case 'T':
		// A3: Change some variable here...
	  mov_light = (mov_light + 1) % 2;
	  printf("Your are Moving %s\n", (mov_light ? "Bunny" : "Light"));
		break;
  case 'r':
  case 'R': 
   // reset initial view parameters
    angle = 20;
    angle2 = 30;
    current_pos[0] = 0.0;
    current_pos[1] = 0.0;
    current_pos[2] = 5.0;
	angle_l = 0;
	angle2_l = 0;
	cinitial_light_pos[0] = -100.0;
	cinitial_light_pos[1] = 100 ;
	cinitial_light_pos[2] = 100;
	cinitial_light_pos[3] = 0;
    break;
  case 'h':
  case 'H':
    printf("\tPress q/Q for Quit\n");
    printf("\tPress h/H to print this help\n");
    printf("\tPress l/L to turn on/off Lighting\n");
    printf("\tPress i/I to invert the normals\n");
    printf("\tPress r/R to revert ViewPoint to initial position\n");
    printf("\tPress + to make the bunny grow fatter\n");
    printf("\tPress - to make the bunny grow thinner\n");
    printf("\tPress d/D to make the bunny dance randomly\n");
  default:
    break;
  }
  glutPostRedisplay();
}


void readSpecialKeys(int key, int x, int y)
{
  switch(key){
  case GLUT_KEY_UP: 
    
    break;
  case GLUT_KEY_DOWN: 
    
    break;
  case GLUT_KEY_RIGHT: 
    
    break;
  case GLUT_KEY_LEFT:  
    
    break;
  }
  glutPostRedisplay();
}


void mouseButtHandler(int button, int state, int x, int y)
{
  motionMode = 0;
  
  switch(button){
  case GLUT_LEFT_BUTTON:  
    if(state == GLUT_DOWN) {
      motionMode = 1;		// Rotate object
      startX = x;
      startY = y;
    }
    break;
  case GLUT_MIDDLE_BUTTON:  
    if(state == GLUT_DOWN) {
      motionMode = 2;		// Translate object
      startX = x;
      startY = y;
    }
    break;
  case GLUT_RIGHT_BUTTON: 
    if(state == GLUT_DOWN) { 
      motionMode = 3;		// Zoom
      startX = x;
      startY = y;
    }
    break;
  }
  glutPostRedisplay();
}


void mouseMoveHandler(int x, int y)
{
	if (mov_light){
		// No mouse button is pressed... return 
		switch (motionMode){
		case 0:
			return;
			break;

		case 1: // Calculate the rotations
			angle = angle + (x - startX);
			angle2 = angle2 + (y - startY);
			startX = x;
			startY = y;
			break;

		case 2:
			current_pos[0] = current_pos[0] - (x - startX) / 100.0;
			current_pos[1] = current_pos[1] - (y - startY) / 100.0;
			startX = x;
			startY = y;
			break;

		case 3:
			current_pos[2] = current_pos[2] - (y - startY) / 10.0;
			startX = x;
			startY = y;
			break;
		}
	}
	else
	{
		switch (motionMode){
		case 0:
			return;
			break;

		case 1: // Calculate the rotations
			angle_l = angle_l + (x - startX);
			angle2_l = angle2_l + (y - startY);
			startX = x;
			startY = y;
			break;

		case 2:
			cinitial_light_pos[0] = cinitial_light_pos[0] - (x - startX); // 10.0;
			cinitial_light_pos[1] = cinitial_light_pos[1] - (y - startY);// 10.0;
			startX = x;
			startY = y;
			break;

		case 3:
			cinitial_light_pos[2] = cinitial_light_pos[2] - (y - startY); // 10.0;
			startX = x;
			startY = y;
			break;
		}
	}
  glutPostRedisplay();
}


void gLdouble_toMatrix4f(Matrix4f o, const GLdouble i[16])
{
	for (int j = 0;  j< 4; j++)
		for (int k = 0; k < 4; k++)
		 o[j][k] = (float)i[j+4*k];
	
}

void setUserView()
{
	
		
			
	if (mov_light)
	{
		glLoadIdentity();
		glTranslatef(-current_pos[0], current_pos[1], -current_pos[2]);
		glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);
	}
	else
	{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(cinitial_light_pos[0], cinitial_light_pos[1], cinitial_light_pos[2]);
			glRotatef(angle2_l, 1.0, 0.0, 0.0);
			glRotatef(angle_l, 0.0, 1.0, 0.0);

			GLdouble m[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, m);
			Matrix4f m2;
			gLdouble_toMatrix4f(m2, m);

			multVector(initial_light_pos, m2, cinitial_light_pos);
			//printf("\nlight at: %f %f %f \n", initial_light_pos[0], initial_light_pos[1], initial_light_pos[2]);
			glLightfv(GL_LIGHT0, GL_POSITION, initial_light_pos);
			glPopMatrix();
		}
		
	
}
