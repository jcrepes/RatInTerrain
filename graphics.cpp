// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "glut.h"
#include "graphics.h"
#include "rat.h"
#include "cell.h"



// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;

Cell gCell;
//Maze gMaze;
//dt = 
//waterlevel = 
//flyheight = 
//resolution = 
Rat gRat(.50, .50);
bool gLButton = false;
bool gRButton = false;
bool gMButton = false;
enum viewtype { top_view, perspective_view, rat_view };
viewtype current_view = rat_view;

// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}
double getTime() {
	static clock_t start_time = clock();
	clock_t current_time = clock();
	double t = double(current_time - start_time) / CLOCKS_PER_SEC;
	return t;
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	gluLookAt(-3, -3, gCell.getZ() + 1, 3, 3, 0, 0, 0, 1);
	//glColor3ub(256, 100, 99);
	if (gLButton == true) {
		gRat.spinLeft();
	}
	if (gRButton == true) {
		gRat.spinRight();
	}
	if (gMButton == true) {
		gRat.crawlForward();
	}
	if (current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(0, 0,3, 3, 3, 0, 0, 0, 1);
	}
	else if (current_view == top_view)
	{
		glDisable(GL_DEPTH_TEST);
		//glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else // current_view == rat_view
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double x = gRat.getX();
		double y = gRat.getY();
		double z_level = gCell.getZ(x, y)+1;
		if (z_level < 2) {
			z_level = 2;
		}
		//std::cout << x << std::endl;
		//std::cout << y << std::endl;
		double dx = gRat.getDX();
		double dy = gRat.getDY();
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = gCell.getZ(at_x, at_y) + 1;
		if (at_z < 2) {
			at_z = 2;
		}
		gluLookAt(x, y, z_level, at_x, at_y, at_z, 0, 0, 1);
		//glColor3ub(100,100,255);
	}
	gCell.Draw();
		if (current_view != rat_view) {
			gRat.Draw();
		}
		//glPushMatrix();
		glScaled(.5, .5, .5);
		glPopMatrix();
		//draw Water
			glBegin(GL_QUADS);
			glColor3d(0, 72 / 255.0, 190 / 255.0);
			glVertex3d(0, 0, 2);
			glVertex3d(0, screen_y, 2);
			glVertex3d(screen_x, screen_y, 2);
			glVertex3d(screen_x, 0, 2);
			glEnd();
		//
		

		glutSwapBuffers();
		glutPostRedisplay();
}
void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 38.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .1, /* Z far */ 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void SetTopView(int w, int h)
{
	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, gCell.getWIDTH() + world_margin_x,
		-world_margin_y, gCell.getHEIGHT() + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27: // escape character means to quit the program
		exit(0);
		break;
	case 'b':
		// do something when 'b' character is hit.
		break;
	case 'r':
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 'p':
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 't':
		current_view = top_view;
		SetTopView(screen_x, screen_y);
		break;
	case 'j':
		gRat.jump();
		break;
	/*case 's':
		gRat.setSpeed(0.02);
		gMaze.noWalls();
		break;
	case 'n':
		gRat.setSpeed(0.01);
		double new_x;
		new_x = gMaze.walls(gRat.getX(), gRat.getY(), gRat.getRadius());
		gRat.setX(new_x);
		break;
	case 'm':
		gMaze.noWall();
		gMaze.RemoveWall(gRat.getX(), gRat.getY(), gRat.getRadius());
		break; */
	default:
		return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	if (current_view == top_view)
	{
		SetTopView(w, h);
	}
	else if (current_view == perspective_view)
	{
		SetPerspectiveView(w, h);
	}
	else // current_view == rat_view
	{
		SetPerspectiveView(w, h);
	}

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		gLButton = true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		gLButton = false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
		gMButton = true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
		gMButton = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gRButton = true;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		gRButton = false;
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{	
	//drawWater
	

	/*double cellWidth = screen_x / double(gCell.getWIDTH());
	double cellHeight = screen_x / double(gCell.getHEIGHT());
	int i, j;
	for (i = 0; i < screen_x; i += cellWidth) {
		for (j = 0; j < screen_x; j += cellHeight) {
			gCell.Draw(i, j);
		}
	}*/
	
	//gMaze.RemoveWalls();
	//double r = gMaze.getR();
	//double cellWidth = screen_x / (gMaze.getWIDTH());
	//gRat = Rat(r + (.5) * cellWidth, .5);
	//gRat = Rat(.5, .5);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("This appears in the title bar");
	}
	InitializeMyStuff();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(1,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color


	glutMainLoop();

	return 0;
}
