
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

// define maximum stack capacity
#define STACK_CAP 16
// define pi for converting angles
#define PI 3.14159265359

// structure for the matrix stack, top specifies current top position on the stack, initially zero (which means one matrix in the stack)
struct matrix_stack
{
    GLdouble m[STACK_CAP][16];
    int top;
};

// define a macro for retrieving current matrix from top of current stack
#define current_matrix (current_stack->m[current_stack->top])

// identity matrix constant
const GLdouble identity[16] =
{1, 0, 0, 0,
 0, 1, 0, 0,
 0, 0, 1, 0,
 0, 0, 0, 1};

// the model view matrix stack
struct matrix_stack model_view = {{{0}}, 0};
// the projection matrix stack
struct matrix_stack projection = {{{0}}, 0};
// the current stack pointer that specifies the matrix mode
struct matrix_stack *current_stack = &model_view;

// multiply current matrix with matrix b, put the result in current matrix
// current = current * b
void matrix_multiply(const GLdouble *b)
{
	GLdouble temp[16];
	for (int i = 0; i < 16; i++)
	{
		temp[i] = current_matrix[i];// ...
		current_matrix[i] = 0;
	}
	for (size_t col = 0; col < 4; col++)
	{
		for (size_t row = 0; row < 4; row++)
		{
			for (size_t i = 0; i < 4; i ++)
				current_matrix[col*4 + row ] += temp[i*4 + row ] * b[col*4 + i ];
		}
	}
}

// calculating cross product of b and c, put the result in a
// a = b x c
void cross_product(GLdouble *ax, GLdouble *ay, GLdouble *az,
    GLdouble bx, GLdouble by, GLdouble bz,
    GLdouble cx, GLdouble cy, GLdouble cz)
{
	*ax = (by * cz) - (cy * bz);
	*ay = (bz * cx) - (cz * bx);
	*az = (bx * cy) - (cx * by);
    // ...
}

// normaliz vector (x, y, z)
void normalize(GLdouble *x, GLdouble *y, GLdouble *z)
{
	GLdouble mag = sqrt((*x * *x) + (*y * *y) + (*z * *z));
	*x /= mag;
	*y /= mag;
	*z /= mag;
}

// switch matrix mode by changing the current stack pointer
void I_my_glMatrixMode(GLenum mode)
{
	switch (mode)
	{
	case(GL_MODELVIEW) :
		current_stack = &model_view;
		break;
	case(GL_PROJECTION) :
		current_stack = &projection;
		break;
	default:
		break;
	}
    // ...
}

// overwrite current matrix with identity matrix
void I_my_glLoadIdentity(void)
{
	for (size_t i = 0; i < 16; i++)
	{
		current_matrix[i] = identity[i];
	}

}

// push current matrix onto current stack, report error if the stack is already full
void I_my_glPushMatrix(void)
{
	if (current_stack->top >= STACK_CAP-1)
	{
		printf("GL_STACK_OVERFLOW error.\n");
		//report error
	}
	else
	{
		current_stack->top++;
		for (size_t i = 0; i < 16; i++)
		{
			current_matrix[i] = current_stack->m[current_stack->top - 1][i];
		}
		
		
	}
    // ...
}

// pop current matrix from current stack, report error if the stack has only one matrix left
void I_my_glPopMatrix(void)
{
	if (current_stack->top <= 0 )
	{
		printf("GL_STACK_UNDERFLOW error.\n");
		//report error
	}
	else
	{
		current_stack->top--;		
	}
    // ...
}

// overwrite currentmatrix with m
void I_my_glLoadMatrixf(const GLfloat *m)
{
	for (size_t i = 0; i < 16; i++)
	{
		  current_matrix[i] = m[i];
	}
    // ...
}

void I_my_glLoadMatrixd(const GLdouble *m)
{
	for (size_t i = 0; i < 16; i++)
	{
		current_matrix[i] = m[i];
	}
    // ...
}

void I_my_glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
	GLdouble m[16] = 
		{ 1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  x, y, z, 1 };
	matrix_multiply(m);

    // ...
}

void I_my_glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glTranslated((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// remember to normalize vector (x, y, z), and to convert angle from degree to radius before calling sin and cos
void I_my_glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
	angle = angle * PI / 180;
	normalize(&x, &y, &z);
	
	GLdouble temp[16] = { (x*x)*(1 - cos(angle)) + cos(angle),    (x*y)*(1 - cos(angle)) + z *sin(angle), (x*z)*(1 - cos(angle)) - y*sin(angle),  0,
						  (x*y)*(1 - cos(angle)) - z *sin(angle), (y*y)*(1 - cos(angle)) + cos(angle),    (y*z)*(1 - cos(angle)) + x *sin(angle), 0,
						  (x*z)*(1 - cos(angle)) + y *sin(angle), (y*z)*(1 - cos(angle)) - x* sin(angle), (z*z)*(1 - cos(angle)) + cos(angle),    0,
						  0,                                      0,                                      0,                                      1 };
	matrix_multiply(temp);

}

void I_my_glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glRotated((GLdouble)angle, (GLdouble)x, (GLdouble)y, (GLdouble)z);
}

void I_my_glScaled(GLdouble x, GLdouble y, GLdouble z)
{
	GLdouble m[16] =
	{ x, 0, 0, 0,
	  0, y, 0, 0,
	  0, 0, z, 0,
	  0, 0, 0, 1 };
	matrix_multiply(m);
    // ...
}

void I_my_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    I_my_glScaled((GLdouble)x, (GLdouble)y, (GLdouble)z);
}

// copy current matrix to m
void I_my_glGetMatrixf(GLfloat *m)
{
	for (size_t i = 0; i < 16; i++)
	{
		m[i] = current_matrix[i];
	}
    // ...
}

void I_my_glGetMatrixd(GLdouble *m)
{
	for (size_t i = 0; i < 16; i++)
	{
		m[i] = current_matrix[i];
	}
	// ...
}

// remember to normalize vectors
void I_my_gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, 
    GLdouble centerX, GLdouble centerY, GLdouble centerZ, 
    GLdouble upX, GLdouble upY, GLdouble upZ)
{
	GLdouble w[3]{eyeX-centerX, eyeY-centerY, eyeZ- centerZ };
	normalize(w, w + 1, w + 2);
	GLdouble u[3];
	cross_product(u, u + 1, u + 2, upX, upY, upZ, w[0], w[1], w[2]);
	normalize(u, u + 1, u + 2);
	GLdouble v[3];
	cross_product(v, v + 1, v + 2, w[0], w[1], w[2], u[0], u[1], u[2]);
	GLdouble finalT[16] = { u[0], v[0], w[0], 0,
		u[1], v[1], w[1], 0,
		u[2], v[1], w[2], 0,
		-u[0] * eyeX - u[1] * eyeY - u[2] * eyeZ,
		-v[0] * eyeX - v[1] * eyeY - v[2] * eyeZ,
		-w[0] * eyeX - w[1] * eyeY - w[2] * eyeZ, 1 };
	glLoadMatrixd(finalT);
    // ...
}

void I_my_glFrustum(GLdouble left, GLdouble right, GLdouble bottom,
    GLdouble top, GLdouble zNear, GLdouble zFar)
{
	GLdouble shear[16] = { 1,0,0,0,
		0, 1, 0, 0,
		(left + right) / (2 * zNear), (top + bottom) / (2*zNear),1,0,
		0, 0, 0, 1 };
	
	GLdouble D[16] = {zNear,0,0,0,
		0, zNear,0,0,
		0, 0, (zNear + zFar) / (zFar- zNear), 1,
		0, 0, (2 * zNear*zFar) / (zFar -zNear), 0};
	
	matrix_multiply(shear);		
	I_my_glScaled(2 / (right - left), 2 / (top - bottom), 1);
	matrix_multiply(D);
	
}

// remember to convert fovy from degree to radius before calling tan
void I_my_gluPerspective(GLdouble fovy, GLdouble aspect, 
    GLdouble zNear, GLdouble zFar)
{
	GLdouble fovy2 = fovy * PI / 180;
	GLdouble t = zNear * tan(fovy2 / 2.0);
	GLdouble b = -t;
	GLdouble r = t * aspect;
	GLdouble l = -r;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(l, r, b, t, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	  // ...
}
