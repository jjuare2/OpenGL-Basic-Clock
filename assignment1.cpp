// assignment1.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <GL/glut.h>
#include <math.h>
#include <time.h>       

int win_H, win_W;
time_t timer;
struct tm curr_time;

void reshape(int w, int h)
{

	glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
}

void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);

	//START CLOCK FACE
	int x = 256; 
	int y = 256; 
	int z = 0;
	glColor3f(1.0f, 0.0f, 0.0f);

	int triDegree = 360; // 360 for 360 degrees. 

	GLfloat rad = 150.0f; //radius
	GLfloat twicePi = 2.0f * 3.14159265358979323846; // couldn't get M_PI to define for some odd reason, so looked up definition and used that number.

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x,y,z); // center of circle
	for (int i = 0; i <= triDegree; i++) {
		glVertex3f(x + (rad * cos(i *  twicePi / triDegree)), y + (rad * sin(i * twicePi / triDegree)), (z));
	}
	glEnd();

	// END CLOCK FACE

	//START HOUR HAND

	glPushMatrix();
	GLfloat triHour[] =
	{
			266, 256, 0,
			246, 256, 0,
			261, 196, 0,
			251, 156, 0
	};
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glTranslatef(256, 256, 0);
	glRotatef((curr_time.tm_hour * 30.0) + (curr_time.tm_min / 2.0) + (curr_time.tm_sec / 120.0), 0, 0, 1);
	glTranslatef(-256, -256, 0);
	glVertexPointer(3, GL_FLOAT, 0, triHour);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	
	//END HOUR HAND

	//START MINUTE HAND

	glPushMatrix();
	GLfloat triMin[] =
	{
		262, 256, 0,
		250, 256, 0,
		256, 156, 0
	};

	glColor3f(1.0f, 1.0f, 0.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glTranslatef(256, 256, 0);
	glRotatef(curr_time.tm_min * 6.0 + curr_time.tm_sec / 10.0, 0, 0, 1);
	glTranslatef(-256, -256, 0);
	glVertexPointer(3, GL_FLOAT, 0, triMin);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);

	//END MINUTE HAND

	//START SECONDS HAND

	glPushMatrix();
	GLfloat triSec[] =
	{
		256, 256, 0,
		256, 146, 0
	};
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3);
	glEnableClientState(GL_VERTEX_ARRAY);
	glTranslatef(256, 256, 0);
	glRotatef(curr_time.tm_sec * 6.0, 0, 0, 1);
	glTranslatef(-256, -256, 0);
	glVertexPointer(3, GL_FLOAT, 0, triSec);
	glDrawArrays(GL_LINES, 0, 2);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);

	//END SECONDS HAND

	glutSwapBuffers(); // swap the back buffer to front

}


void TimeEvent(int time_val)
{
	time(&timer); // get the current date and time from system
	localtime_s(&curr_time, &timer);
	glutPostRedisplay();
	glutTimerFunc(30, TimeEvent, 1);// By using a timed event, your application should run at the same speed on any machine.
}

int main(int argc, char **argv)
{
	GLenum type;

	glutInit(&argc, argv);

	type = GLUT_DEPTH;
	type |= GLUT_RGB;
	type |= GLUT_DOUBLE;
	glutInitDisplayMode(type);

	time(&timer); // get current date and time
	localtime_s(&curr_time, &timer);

	// set window size and create a window for rendering
	win_W = 512;
	win_H = 512;
	glutInitWindowSize(win_H, win_W);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My clock");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(30, TimeEvent, 1);
	glutMainLoop();
	return 0;
}
