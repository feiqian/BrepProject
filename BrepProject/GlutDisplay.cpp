#include "GlutDisplay.h"

bool GlutDisplay::bSolidDisplay = true;
Solid* GlutDisplay::solid = NULL;
bool GlutDisplay::bMouseDown = false;
int GlutDisplay::mouseX=-1;
int GlutDisplay::mouseY=-1;

GLfloat GlutDisplay::cameraDistance = 10.0;
GLfloat GlutDisplay::cameraAngleX = 0.0;
GLfloat GlutDisplay::cameraAngleY = 0.0;

void GlutDisplay::setSolid(Solid* solid)
{
	GlutDisplay::solid = solid;
}

void GlutDisplay::reshape(int w, int h)
{
	// prevents division by zero when minimising window
	if (h == 0)	h = 1;

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// just use a perspective projection
	gluPerspective(45,(float)w/h,1,1000);
	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,10.0, 0.0,0.0,0.0,0.0f,1.0f,0.0f);
}

void GlutDisplay::mouseCallBack(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			bMouseDown = true;
			mouseX=x;
			mouseY=y;
			return;
		}
	}
	bMouseDown = false;
}

void GlutDisplay::motionCallBack(int x, int y )
{
	if (bMouseDown)
	{
		cameraAngleY += (x - mouseX);
		cameraAngleX += (y - mouseY);
		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
}

void GlutDisplay::keyboardCallBack(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 13:
			bSolidDisplay = !bSolidDisplay;
			glutPostRedisplay();
			break;
	}
}

void GlutDisplay::display(int argc, char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
	glutInitWindowSize(500, 500);
	glutCreateWindow("BREP MODEL");
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseCallBack);
	glutMotionFunc(motionCallBack);
	glutKeyboardFunc(keyboardCallBack);
	glutMainLoop();
}

void GlutDisplay::render()
{
	if(!solid) return;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -cameraDistance);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);

	if(bSolidDisplay)
	{
		// create tessellator
		GLUtesselator *tess = gluNewTess();
		if(!tess) return;
		// register callback functions
		gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK*)())&tessBegin);
		gluTessCallback(tess, GLU_TESS_END,   (void (CALLBACK*)())&tessEnd);
		gluTessCallback(tess, GLU_TESS_VERTEX,  (void (CALLBACK*)())&vertexBack);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		for(Solid* tmpSolid = solid;tmpSolid!=NULL;tmpSolid = tmpSolid->next)
		{
			for(Face* face = solid->face;face!=NULL;face = face->next)
			{
				// describe non-convex polygon
				gluTessBeginPolygon(tess, NULL);
				for(Loop* loop = face->loop;loop!=NULL;loop = loop->next)
				{
					gluTessBeginContour(tess);
					Half_Edge* he = loop->he;
					do 
					{
						Point& pt = he->ve1->point;
						gluTessVertex(tess, pt.coords,pt.coords);
						printf("%d -> ",pt.index);
						he = he->next;
					} while (he!=loop->he);
					gluTessEndContour(tess);
					printf("\n");
				}
				gluTessEndPolygon(tess);
			}
		}
		// delete tessellator after processing
		gluDeleteTess(tess);
	}
	else
	{
		glColor3d (1.0, 0.0, 0.0);
		glLineWidth(10.0);

		for(Solid* tmpSolid = solid;tmpSolid!=NULL;tmpSolid = tmpSolid->next)
		{
			for(Edge* edge = solid->edge;edge!=NULL;edge = edge->next)
			{
				glBegin(GL_LINES);
				Point& pt1 = edge->he1->ve1->point;
				Point& pt2 = edge->he1->ve2->point;
				glVertex3dv(pt1.coords);
				glVertex3dv(pt2.coords);
				printf("%d -> %d\n",pt1.index,pt2.index);
				glEnd();
			}
		}
	}
	glPopMatrix();
	glutSwapBuffers();
}

void GlutDisplay::tessBegin( GLenum which )
{
	glBegin(which);
}

void GlutDisplay::vertexBack( GLvoid * data )
{
	const GLdouble *ptr = (const GLdouble*)data;
	glColor3dv(ptr);
	glVertex3dv(ptr); 
}

void GlutDisplay::tessEnd()
{
	glEnd();
}