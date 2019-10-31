// assignment1.cpp : Defines the entry point for the console application.
/*
George Villaume
gvilla3@lsu edu
CSC 4356: Interactive Computer Graphics
Professor: Jinwei Ye
*/

#include <iostream>
#include <GL/glut.h>  //use #include <GLUT/glut.h> if using Xcode in MacOS
//#include <GLUT/glut.h>
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

	/* Draw top watch band */
	glColor3f(0.85, 0.78, .09); // Sets color to gold

	glBegin(GL_QUADS); // Draws base band first
	glVertex2f(140.0, 132.0);
	glVertex2f(150.0, 72.0);
	glVertex2f(362.0, 72.0);
	glVertex2f(372.0, 132.0);
	glEnd();

	glColor3f(0.65, 0.6, .07); // Sets color to a darker gold for depth

	glBegin(GL_QUADS); // Draws middle band
	glVertex2f(150.8, 67.0);
	glVertex2f(155.0, 37.0);
	glVertex2f(357.0, 37.0);
	glVertex2f(361.2, 67.0);
	glEnd();

	glColor3f(0.49, 0.45, .04); // Darker gold

	glBegin(GL_QUADS); // Draws top watch band
	glVertex2f(155.8, 32.0);
	glVertex2f(160.0, 2.0);
	glVertex2f(352.0, 2.0);
	glVertex2f(356.2, 32.0);
	glEnd();

	/* Draw bottom watch band */
	glPushMatrix(); // Push new matrix on to the stack

	// Transformations act as a stack
	glTranslatef(256.0, 256.0, 0.0); // 3. Translate back to desired location
	glRotatef(180.0, 0.0, 0.0, 1.0); // 2. Rotate around origin
	glTranslatef(-256.0, -256.0, 0.0); // 1. Translate to origin

	glColor3f(0.85, 0.78, .09); // Same gold as top base

	glBegin(GL_QUADS); // Bottom base band
	glVertex2f(140.0, 132.0);
	glVertex2f(150.0, 72.0);
	glVertex2f(362.0, 72.0);
	glVertex2f(372.0, 132.0);
	glEnd();

	glColor3f(0.65, 0.6, .07); // Darker gold

	glBegin(GL_QUADS); // Darker gold
	glVertex2f(150.8, 67.0);
	glVertex2f(155.0, 37.0);
	glVertex2f(357.0, 37.0);
	glVertex2f(361.2, 67.0);
	glEnd();

	glColor3f(0.49, 0.45, .04); //Darkest gold

	glBegin(GL_QUADS); //Bottom bottom band
	glVertex2f(155.8, 32.0);
	glVertex2f(160.0, 2.0);
	glVertex2f(352.0, 2.0);
	glVertex2f(356.2, 32.0);
	glEnd();

	glPopMatrix(); // Pop matrix off the stack

	/* Draw rim of watch */
	glColor3f(0.969, 0.898, .125); // Set rim of watch to lightest gold

	glBegin(GL_TRIANGLE_FAN); //Begin a triangle fan object to draw a circle
	glVertex2f(256.0, 256.0); // Center point
	glVertex2f(256.0, 86.0); // Next point that sets radius

	float lastX = 256.0; // Save the points from the last vertex added
	float lastY = 86.0;
	float currentX, currentY;
	for (int i = 1; i <= 360; i++) // For loop to draw the rest of the vertices
	{
		currentX = ((cos(1.0) * (lastX - 256.0)) - (sin(1.0) * (lastY - 256.0))) + 256.0; // Calculate next vertex to be placed by rotating 
		currentY = ((sin(1.0) * (lastX - 256.0)) + (cos(1.0) * (lastY - 256.0))) + 256.0; // the last points 1 degree using a 2D rotation equation
		glVertex2f(currentX, currentY); // Place vertex
		lastX = currentX; // Save last points
		lastY = currentY;
	}
	glEnd(); // Close triangle fan object

	/* Draw glare on watch rim */
	glColor3f(1.0, 1.0, 1.0); // White for watch glare
	for (int k = 300; k < 359; k++) // For loop to rotate the glare around the rim of the watch
	{
		if (k < 304 || k > 308) // Add the gap in the glare
		{
			glPushMatrix();

			glTranslatef(256.0, 256.0, 0.0);
			glRotatef((float)k, 0.0, 0.0, 1.0); // Rotates the glare by k degrees so that it coveres the range I picked
			glTranslatef(-256.0, -256.0, 0.0);

			glBegin(GL_QUADS); // Draw glare
			glVertex2f(254.0, 93.0);
			glVertex2f(254.0, 99.0);
			glVertex2f(258.0, 99.0);
			glVertex2f(258.0, 93.0);
			glEnd();

			glPopMatrix();
		}
	}

	/* Draw clock face */

	// White color carried over from glare

	glBegin(GL_TRIANGLE_FAN); // Begin drawing clock face
	glVertex2f(256.0, 256.0); // Center point
	glVertex2f(256.0, 106.0); // First vertex sets radius

	lastX = 256.0; // Save points
	lastY = 106.0;
	
	for (int i = 1; i <= 360; i++) // Iterated 359 times to draw vertices 1 degree apart
	{

		currentX = ((cos(1.0) * (lastX - 256.0)) - (sin(1.0) * (lastY - 256.0))) + 256.0; // 2D rotation equation
		currentY = ((sin(1.0) * (lastX - 256.0)) + (cos(1.0) * (lastY - 256.0))) + 256.0;
		glVertex2f(currentX, currentY); // Place vertex
		lastX = currentX; // Save points
		lastY = currentY;
	}
	glEnd(); // Finish drawing triangle fan

	/* Draw tick marks and watch dial */
	for (int j = 0; j < 360; j += 6) // For loop to draw tick marks every 30 degrees
	{
		glColor3f(0.0, 0.0, 0.0); // Sets color to black in the for loop to avoid improper color after drawing watch dial
		if (j % 30 == 0) // Every 30 degrees for hour marks
		{
			glPushMatrix();

			glTranslatef(256.0, 256.0, 0.0);
			glRotatef((float)j, 0.0, 0.0, 1.0); // Rotate by j degrees
			glTranslatef(-256.0, -256.0, 0.0);

			glBegin(GL_QUADS); // Draw thick tick mark
				glVertex2d(254.0, 106.0);
				glVertex2d(258.0, 106.0);
				glVertex2d(258.0, 120.0);
				glVertex2d(254.0, 120.0);
			glEnd();

			if (j == 90) // At 90 degrees, draws the dial on the side
			{
				glColor3f(0.65, 0.6, .07);
				glBegin(GL_QUADS);
				glVertex2d(240.0, 87.0);
				glVertex2d(272.0, 87.0);
				glVertex2d(272.0, 74.0);
				glVertex2d(240.0, 74.0);
				glEnd();
			}

			glPopMatrix();
		}
		else // At all other intervals, draw the small tick mark
		{
			glPushMatrix();

			glTranslatef(256.0, 256.0, 0.0);
			glRotatef((float)j, 0.0, 0.0, 1.0);
			glTranslatef(-256.0, -256.0, 0.0);

			glBegin(GL_LINES);
				glVertex2d(256.0, 106.0);
				glVertex2d(256.0, 116.0);
			glEnd();

			glPopMatrix();
		}
	}

	/* Draw hour hand */
	glPushMatrix();

	glTranslatef(256.0, 256.0, 0.0);
	glRotatef((((float)curr_time.tm_hour) * 30.0 + ((float)curr_time.tm_min) / 2.0 + ((float)curr_time.tm_sec) / 120.0), 0.0, 0.0, 1.0);
	glTranslatef(-256.0, -256.0, 0.0);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(266.0, 256.0);
		glVertex2f(246.0, 256.0);
		glVertex2f(261.0, 156.0);
		glVertex2f(251.0, 156.0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(266.0, 256.0);
	glVertex2f(246.0, 256.0);
	glVertex2f(261.0, 286.0);
	glVertex2f(251.0, 286.0);
	glEnd();

	glPopMatrix();

	/* Draw minute hand */
	glPushMatrix();

	glTranslatef(256.0, 256.0, 0.0);
	glRotatef((((float)curr_time.tm_min) * 6.0 + ((float)curr_time.tm_sec) / 10.0), 0.0, 0.0, 1.0);
	glTranslatef(-256.0, -256.0, 0.0);

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
		glVertex2f(262.0, 256.0);
		glVertex2f(250.0, 256.0);
		glVertex2f(256.0, 126.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(262.0, 256.0);
	glVertex2f(250.0, 256.0);
	glVertex2f(256.0, 286.0);
	glEnd();

	glPopMatrix();

	/* Draw second hand */
	glPushMatrix();

	glTranslatef(256.0, 256.0, 0.0);
	glRotatef((((float)curr_time.tm_sec) * 6.0), 0.0, 0.0, 1.0);
	glTranslatef(-256.0, -256.0, 0);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(256.0, 256.0);
		glVertex2f(256.0, 121.0);
	glEnd();

	glPopMatrix();

	glutSwapBuffers(); // swap the back buffer to front
}

void TimeEvent(int time_val)
{
	time(&timer); // get the current date and time from system
	localtime_s(&curr_time, &timer); // use localtime_r(&timer, &curr_time); if using Xcode in MacOS
	//localtime_r(&timer, &curr_time);
	glutPostRedisplay();
	glutTimerFunc(30, TimeEvent, 1);// By using a timed event, your application should run at the same speed on any machine.
}

int main(int argc, char** argv)
{
	GLenum type;

	glutInit(&argc, argv);

	type = GLUT_DEPTH;
	type |= GLUT_RGB;
	type |= GLUT_DOUBLE;
	glutInitDisplayMode(type);

	time(&timer); // get current date and time
	localtime_s(&curr_time, &timer); // use localtime_r(&timer, &curr_time); if using Xcode in MacOS
	//localtime_r(&timer, &curr_time);

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