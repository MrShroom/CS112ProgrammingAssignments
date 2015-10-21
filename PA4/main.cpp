#include <stdio.h>
#include <stdlib.h>
#include "glew\include\GL\glew.h"
#include "glut\glut.h"
#include <memory.h>
#include <math.h>
#include "mymath.h"
 
#define PI       3.14159265358979323846

void setTransMatrix(float *mat, float x, float y, float z);
void multiplyMatrix(float *a, float *b);
void xProduct( float *a, float *b, float *res);
void normalize(float *a);
void setIdentMatrix( float *mat, int size);
void placeCam(float posX, float posY, float posZ, float lookX, float lookY, float lookZ);
float * rotationMatrix(float x, float y, float z, float angle);
void init();
GLuint loadBMP_custom(const char * imagepath);

struct vec3
{
	float x;
	float y;
	float z;
};

// vertices for triangle
float vertices1[] = {       -1.0f,-1.0f,-1.0f, // triangle 1 : begin
							-1.0f,-1.0f, 1.0f,
							-1.0f, 1.0f, 1.0f, // triangle 1 : end

							1.0f, 1.0f,-1.0f, // triangle 2 : begin
							-1.0f,-1.0f,-1.0f,
							-1.0f, 1.0f,-1.0f, // triangle 2 : end

							1.0f,-1.0f, 1.0f,
							-1.0f,-1.0f,-1.0f,
							1.0f,-1.0f,-1.0f,

							1.0f, 1.0f,-1.0f,
							1.0f,-1.0f,-1.0f,
							-1.0f,-1.0f,-1.0f,

							-1.0f,-1.0f,-1.0f,
							-1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f,-1.0f,

							1.0f,-1.0f, 1.0f,
							-1.0f,-1.0f, 1.0f,
							-1.0f,-1.0f,-1.0f,

							-1.0f, 1.0f, 1.0f,
							-1.0f,-1.0f, 1.0f,
							1.0f,-1.0f, 1.0f,

							1.0f, 1.0f, 1.0f,
							1.0f,-1.0f,-1.0f,
							1.0f, 1.0f,-1.0f,

							1.0f,-1.0f,-1.0f,
							1.0f, 1.0f, 1.0f,
							1.0f,-1.0f, 1.0f,

							1.0f, 1.0f, 1.0f,
							1.0f, 1.0f,-1.0f,
							-1.0f, 1.0f,-1.0f,

							1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f,-1.0f,
							-1.0f, 1.0f, 1.0f,

							1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f, 1.0f,
							1.0f,-1.0f, 1.0f
						};




float normals1[] = {     -1.0f,0.0f,0.0f, // triangle 1 : begin
						-1.0f,0.0f,0.0f,
						-1.0f,0.0f,0.0f, // triangle 1 : end

						0.0f,0.0f,-1.0f, // triangle 2 : begin
						0.0f,0.0f,-1.0f,
						0.0f,0.0f,-1.0f, // triangle 2 : end

						0.0f,-1.0f,0.0f,
						0.0f,-1.0f,0.0f,
						0.0f,-1.0f,0.0f,

						0.0f,0.0f,-1.0f,
						0.0f,0.0f,-1.0f,
						0.0f,0.0f,-1.0f,

						-1.0f,0.0f,0.0f,
						-1.0f,0.0f,0.0f,
						-1.0f,0.0f,0.0f,

						0.0f,-1.0f,0.0f,
						0.0f,-1.0f,0.0f,
						0.0f,-1.0f,0.0f,

						0.0f,0.0f, 1.0f,
						0.0f,0.0f, 1.0f,
						0.0f,0.0f, 1.0f,

						1.0f,0.0f,0.0f,
						1.0f,0.0f,0.0f,
						1.0f,0.0f,0.0f,

						1.0f,0.0f,0.0f,
						1.0f,0.0f,0.0f,
						1.0f,0.0f,0.0f,

						0.0f, 1.0f,0.0f,
						0.0f, 1.0f,0.0f,
						0.0f, 1.0f,0.0f,

						0.0f, 1.0f,0.0f,
						0.0f, 1.0f,0.0f,
						0.0f, 1.0f,0.0f,

						0.0f,0.0f, 1.0f,
						0.0f,0.0f, 1.0f,
						0.0f,0.0f, 1.0f
						};


 
float colors1[] = { 0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
			0.0f, 0.0f, 1.0f, 0.3f,
            0.0f, 0.0f, 1.0f, 0.3f,
            0.0f,0.0f, 1.0f, 0.3f,
};

// Calculate the texture coordinates for each vertex and put all the texture coordinates into texture1.
float texture1[] = {0.0f, 0.0f,					//triange 1
					0.1666666666666667f,0.0f,
					0.1666666666666667f, 1.0f, 

					0.3333333333333333f, 1.0f,//trangle #2
					0.5f,0.0f,
					0.5f, 1.0f,

					0.3333333333333333f, 1.0f,
					0.1666666666666667f, 0.0f,
					0.3333333333333333f, 0.0f,

					0.3333333333333333f, 1.0f,
					0.3333333333333333f, 0.0f,
					0.5f, 0.0f,

					0.0f, 0.0f,
					0.1666666666666667f, 1.0f,
					0.0f, 1.0f,

					0.3333333333333333f, 1.0f,
					0.1666666666666667f, 1.0f,
					0.1666666666666667f, 0.0f,

					0.5f,1.0f,
					0.5f,0.0f,
					0.6666666666666667f, 0.0f,

					0.8333333333333333f, 1.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,

					1.0f, 0.0f,
					0.8333333333333333f, 1.0f,
					0.8333333333333333f, 0.0f,

					0.8333333333333333f, 0.0f,
					0.8333333333333333f, 1.0f,
					0.6666666666666667f, 1.0f,

					0.8333333333333333f, 0.0f,
					0.6666666666666667f, 1.0f,
					0.6666666666666667f, 0.0f,
					
					0.6666666666666667f, 1.0f,
					0.5f, 1.0f,
					0.6666666666666667f, 0.0f,

					};
 



// shader names

//# 1 Geometric Transformation
//char *vertexFileName = "vertgeometry.txt";
//char *fragmentFileName = "fraggeometry.txt";

//# 2 Lightning:
//Part 1: Gouraud shading
//char *vertexFileName = "vertgouraud.txt";
//char *fragmentFileName = "fraggouraud.txt";

//Part 2: Phong shading
//char *vertexFileName = "vertphong.txt.";
//char *fragmentFileName = "fragphong.txt";

//#3 Texture Mapping
char *vertexFileName = "vertmapping.txt.";
char *fragmentFileName = "fragmapping.txt";

// program and shader Id
GLuint p,v,f;
 
// vert attrib locations
GLuint vertexLoc, colorLoc, normalLoc;
 
// uniform var locations
GLuint projMatrixLoc, viewMatrixLoc, normalMatrixLoc;

GLuint ambientColorLoc,lightColorLoc, lightPositionLoc, ShininessLoc, StrengthLoc, EyeDirectionLoc;

GLuint textureLoc,samplerLoc;
 
// vert array obj Id
GLuint vert[3];
 
// storage for matrices
float projMatrix[16];
float viewMatrix[16];
float normalMatrix[9];

float ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
float lightColor[] = {0.9f, 0.8f, 0.9f};
float lightPosition[] = { 4.0f, 4.0f, 4.0f };
float Shininess = 10.0;
float Strength = 10.0;
float EyeDirection[] = {0 , 0 , -5};


int frame=0,time,timebase=0;
char s[50];

int viewPosition[3];
float angle = 0.0f;
float angle2 = 0.0f;
int startX;
int startY;
int startZ;

int selectX;
int selectY;
int selectZ;
int window_width;
int window_height;
GLuint texID = -1;
 
// vector opt
// res = a cross b;
void xProduct( float *a, float *b, float *res) 
{
 
    res[0] = a[1] * b[2]  -  b[1] * a[2];
    res[1] = a[2] * b[0]  -  b[2] * a[0];
    res[2] = a[0] * b[1]  -  b[0] * a[1];
}
 
// normalize a vec3
void normalize(float *a) 
{
 
    float mag = sqrt(a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2]);
    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}

// Matrix Opt. - In Opengl 3 we need to handle our own matrix.
 
// In this form : a = a * b; 
void multiplyMatrix(float *a, float *b) 
{
    float res[16];
 
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[j*4 + i] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                res[j*4 + i] += a[k*4 + i] * b[j*4 + k];
            }
        }
    }
    memcpy(a, res, 16 * sizeof(float));
}

// sets the square matrix mat to the ID matrix,
void setIdentMatrix( float *mat, int size) 
{
 
    // 0s
    for (int i = 0; i < size * size; ++i)
            mat[i] = 0.0f;
 
    // diagonal 1s
    for (int i = 0; i < size; ++i)
        mat[i + i * size] = 1.0f;
}
 
// View Matrix
// just like glulookat
void placeCam(float posX, float posY, float posZ, float lookX, float lookY, float lookZ) 
{
 
    float dir[3], right[3], up[3];
 
    up[0] = 0.0f;   up[1] = 1.0f;   up[2] = 0.0f;
 
    dir[0] =  (lookX - posX);
    dir[1] =  (lookY - posY);
    dir[2] =  (lookZ - posZ);
    normalize(dir);
 
	// this order matters
    xProduct(dir,up,right);
    normalize(right);
 
    xProduct(right,dir,up);
    normalize(up);
 
    float aux[16];
 
    viewMatrix[0]  = right[0];
	viewMatrix[1]  = up[0];
	viewMatrix[2]  = -dir[0];
	viewMatrix[3]  = 0.0f;
    viewMatrix[4]  = right[1];
	viewMatrix[5]  = up[1];
	viewMatrix[6]  = -dir[1];
	viewMatrix[7]  = 0.0f;
    viewMatrix[8]  = right[2];
	viewMatrix[9]  = up[2];
	viewMatrix[10] = -dir[2];
	viewMatrix[11] = 0.0f;
    viewMatrix[12] = 0.0f;
    viewMatrix[13] = 0.0f;
    viewMatrix[14] =  0.0f;
    viewMatrix[15] = 1.0f;

	normalMatrix[0] = viewMatrix[0];
	normalMatrix[1] = viewMatrix[1];
	normalMatrix[2] = viewMatrix[2];
	normalMatrix[3] = viewMatrix[4];
	normalMatrix[4] = viewMatrix[5];
	normalMatrix[5] = viewMatrix[6];
	normalMatrix[6] = viewMatrix[8];
	normalMatrix[7] = viewMatrix[9];
	normalMatrix[8] = viewMatrix[10];

    setTransMatrix(aux, -posX, -posY, -posZ);
    multiplyMatrix(viewMatrix, aux);
	
}

// Generates a rotation matrix.  Angle is in radian.
float * rotationMatrix(float x, float y, float z, float angle)
{
	float tempVec[3];
	tempVec[0] = x;
	tempVec[1] = y;
	tempVec[2] = z;
    normalize(tempVec);

	vec3 axis;
	axis.x = tempVec[0];
	axis.y = tempVec[1];
	axis.z = tempVec[2];

    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

	float mat[16] = {oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
				0.0,                                0.0,                                0.0,                                1.0};

    return mat;

}
 
// Projection Matrix
void buildProjMatrix(float fov, float ratio, float nearP, float farP) {
 
    float f = 1.0f / tan (fov * (PI / 360.0));
    setIdentMatrix(projMatrix,4);
    projMatrix[0] = f / ratio;
    projMatrix[1 * 4 + 1] = f;
    projMatrix[2 * 4 + 2] = (farP + nearP) / (nearP - farP);
    projMatrix[3 * 4 + 2] = (2.0f * farP * nearP) / (nearP - farP);
    projMatrix[2 * 4 + 3] = -1.0f;
    projMatrix[3 * 4 + 3] = 0.0f;
}

// Transformation matrix mat with a translation
void setTransMatrix(float *mat, float x, float y, float z) {
 
    setIdentMatrix(mat,4);
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

//Transformation matrix mat with a scaling
void setScale(float *mat, float xScale, float yScale, float zScale) 
{
    setIdentMatrix(mat,4);
	mat[0] = xScale;
	mat[5] = yScale;
	mat[10] = zScale;
}

void changeSize(int w, int h) {
 
    float ratio;

    // place viewport to be the entire window
    glViewport(0, 0, w, h);
    ratio = (1.0f * w) / h;
    buildProjMatrix(53.13f, ratio, 1.0f, 30.0f);
}
 
void setupBuffers() {
 
    GLuint buffers[4];
 
    glGenVertexArrays(1, vert);

    // first triangle
    glBindVertexArray(vert[0]);
    // generate 2 buffers for vert and color
    glGenBuffers(4, buffers);
    // bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, 0, 0, 0);
 
    // bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);

	// bind buffer for normals and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals1), normals1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, 0, 0, 0);

	// bind buffer for texture and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture1), texture1, GL_STATIC_DRAW);
    glEnableVertexAttribArray(textureLoc);
    glVertexAttribPointer(textureLoc, 2, GL_FLOAT, 0, 0, 0);

}
 
void setUniforms() {
 
    // must be called after glUseProgram
	// set the variables for the shader
    glUniformMatrix4fv(projMatrixLoc,  1, false, projMatrix);
    glUniformMatrix4fv(viewMatrixLoc,  1, false, viewMatrix);
	glUniformMatrix3fv(normalMatrixLoc, 1, false, normalMatrix);
	glUniform4fv(ambientColorLoc, 1, ambientColor);
	glUniform3fv(lightColorLoc, 1, lightColor);
	glUniform3fv(lightPositionLoc, 1, lightPosition);
	glUniform1f(ShininessLoc,Shininess);
	glUniform1f(StrengthLoc, Strength);
	glUniform3fv(EyeDirectionLoc,1,EyeDirection);

	if (texID == -1)
		texID = loadBMP_custom("texture.bmp");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc,0);
	//glActiveTexture(GL_TEXTURE0 + texID);
	//glUniform1i(samplerLoc, texID);

}
 
void renderScene(void) {

	
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",
			frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}
    glutSetWindowTitle(s);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    //placeCam(10,2,10,0,2,-5);
	placeCam(viewPosition[0],viewPosition[1],viewPosition[2],0,0,-5);
	multiplyMatrix(viewMatrix, rotationMatrix(0.0,1.0,0.0, angle));
	multiplyMatrix(viewMatrix, rotationMatrix(1.0,0.0,0.0, angle2));
    glUseProgram(p);
    setUniforms();

    glBindVertexArray(vert[0]);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices1));

	float T[16];	
	setScale(T,0.5,0.5,0.5);
	multiplyMatrix(viewMatrix, T);
	setTransMatrix(T,4,0,0);
	multiplyMatrix(viewMatrix, T);

    setUniforms();

    glBindVertexArray(vert[1]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices1));
  
   glutSwapBuffers();
}
 

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 
void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 
GLuint initShaders() {
 
    char *vertShader = NULL,*fragShader = NULL;
 
    GLuint p,v,f;
 
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
    vertShader = getTxtFile(vertexFileName);
    fragShader = getTxtFile(fragmentFileName);
    const char * vv = vertShader;
    const char * ff = fragShader;
    glShaderSource(v, 1, &vv,NULL);
    glShaderSource(f, 1, &ff,NULL);
    free(vertShader);
	free(fragShader);
    glCompileShader(v);
    glCompileShader(f);
    printShaderInfoLog(v);
    printShaderInfoLog(f);
    p = glCreateProgram();
    glAttachShader(p,v);
    glAttachShader(p,f);
    glBindFragDataLocation(p, 0, "outputF");
    glLinkProgram(p);
    printProgramInfoLog(p);
    vertexLoc = glGetAttribLocation(p,"position");
    colorLoc = glGetAttribLocation(p, "color"); 
	normalLoc = glGetAttribLocation(p, "normal");
    projMatrixLoc = glGetUniformLocation(p, "projMatrix");
    viewMatrixLoc = glGetUniformLocation(p, "viewMatrix");
	normalMatrixLoc = glGetUniformLocation(p, "normalMatrix");
	//ambientColorLoc = glGetUniformLocation(p,"Ambient");
	ambientColorLoc = glGetUniformLocation(p, "ambientColor");
	//lightColorLoc = glGetUniformLocation(p,"LightColor");
	lightColorLoc = glGetUniformLocation(p, "lightColor");
	//lightPositionLoc = glGetUniformLocation(p,"LightPosition");
	lightPositionLoc = glGetUniformLocation(p, "lightPosition");
	ShininessLoc = glGetUniformLocation(p,"Shininess");
	StrengthLoc = glGetUniformLocation(p,"Strength");
	EyeDirectionLoc = glGetUniformLocation(p,"EyeDirection");
	textureLoc = glGetAttribLocation(p,"vertexUV");
	samplerLoc = glGetUniformLocation(p,"myTextureSampler");
 
    return(p);
}

float deltaAngle = 0.0f;
int xOrigin = -1;



//This event will trigger when you have a mouse button pressed down.
void mouseMove(int x, int y) 
{
	// x and y is the mouse position.
	//printf("%d ,  %d \n",x,y);
	int motionMode = 1;
	switch(motionMode){
  case 0:
    /* No mouse button is pressed... do nothing */
    /* return; */
    break;

  case 1:
    /* rotating the view*/
	angle = angle + (x - startX)/1.5;
    angle2 = angle2 + (y - startY)/1.5;
    startX = x;
    startY = y;
    break;

  case 2:

    break;

  case 3:
	  startZ = y;
    break;
  }
	
}

//This event occur when you press a mouse button.
void mouseButton(int button, int state, int x, int y) 
{
	startX = x;
	startY = y;
	startZ = y;
	selectX = x;
	selectY = y;
	selectZ = y;
	//printf("%d , %d",selectX,selectY);
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) 
	{
		// when the button is released
		if (state == GLUT_UP) 
		{
			  window_width = glutGet(GLUT_WINDOW_WIDTH);
			  window_height = glutGet(GLUT_WINDOW_HEIGHT);
 
			  GLbyte color[4];
			  GLfloat depth;
			  GLuint index;
 
			  glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			  glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			  glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
 
			  printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
					 x, y, color[0], color[1], color[2], color[3], depth, index);
					}
		else  // state = GLUT_DOWN	
		{
		}
	}
}

void readKeyboard(unsigned char key, int x, int y){
	switch (key){
	case  0x1B: /* esc */
	case  'q':
		//    kill( getpid(), SIGHUP );
		break;
	case 'a':
		angle = angle + PI/10;
		break;
	case 'd':
		angle = angle - PI/10;
	case 'w':
		angle2 = angle2 + PI/10;
		break;
	case 's':
		angle2= angle2 - PI/10;
		break;
	case '+':
		viewPosition[2] -= 1;
		break;
	case '-':
		viewPosition[2] += 1;
		break;
	case 'r':
		/* reset initial view parameters */
		angle = PI;
		angle2 = PI;
		startX = 0.0;
		startY = 0.0;
		viewPosition[0] = 0;
		viewPosition[1] = 0;
		viewPosition[2] = 11;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void init(){
	viewPosition[0] = 0;
	viewPosition[1] = 0;
	viewPosition[2] = 11;	
}
 
int main(int argc, char **argv) 
{
	// sets up glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("ICS Graphics");
    glutSetWindowTitle(s);
	// call back functions
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(readKeyboard);
 
	// check if a particular extension is available on your platform
	// Originally designed for OpenGL 4.4, but we lowered the version to 3.3, however, the project name remains 4_4.
    glewInit();
    if (glewIsSupported("GL_VERSION_3_3"))
        printf("OpenGL 3.3 is supported\n");
    else 
	{
        printf("OpenGL 3.3 not supported\n");
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);

   glClearColor(1.0,1.0,1.0,1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	init();
    p = initShaders(); 
    setupBuffers(); 
    glutMainLoop();

    return(0); 
}



//// load bmp file 
GLuint loadBMP_custom(const char * imagepath){
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file){printf("Image could not be opened\n"); return 0;}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way
	// Create a buffer
	data = new unsigned char [imageSize];
 
	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);
 
	//Everything is in memory now, the file can be closed
	fclose(file);
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



	return textureID;
}