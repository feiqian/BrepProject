#ifndef _GLUT_DISPLAY
#define _GLUT_DISPLAY
#include <stdio.h>
#include "HalfEdgeDS.h"
#include "glut.h"

class GlutDisplay
{
public:
	static void display(int argc, char**argv);
	static void setSolid(Solid* solid);
private:
	static void render();
	static void reshape(int w, int h);

	static void CALLBACK tessBegin(GLenum which);
	static void CALLBACK vertexBack(GLvoid * data);
	static void CALLBACK tessEnd();
	static void motionCallBack(int x, int y );
	static void mouseCallBack(int button, int state, int x, int y);
	static void keyboardCallBack(unsigned char key,int x,int y);

	static bool bSolidDisplay;
	static Solid* solid;
	static bool bMouseDown;
	static int mouseX;
	static int mouseY;
	static GLfloat cameraDistance;
	static GLfloat cameraAngleX;
	static GLfloat cameraAngleY;
};
#endif