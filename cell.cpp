#include <cmath>
//#include <cstdlib>
#include "cell.h"
#include "glut.h"
#include "graphics.h"

Cell::Cell()
{
}
void Cell::Draw() {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			glBegin(GL_QUADS);
			int r = (x * 24734623 + (y * 209821)) % 256;
			int g = (x * 32748952 + (y * 11520051)) % 256;
			int b = (x * 92535283 + (y * 5012094)) % 256;
			glColor3d((float)r / 255.0, (float)g / 255.0, (float)b / 255.0);
			//glColor3d(34 / 255.0, 139 / 255.0, 34 / 255.0);
			//DrawLine(x, y, x, y + 1);
			//DrawLine(x, y + 1, x + 1, y + 1);
			//DrawLine(x + 1, y + 1, x + 1, y);
			//DrawLine(x + 1, y, x, y);
			double z = getZ(x, y);
			//double zY = (sin(y));
			//double zX = (cos(x));
			//mZ = zX + zY;
			
			glVertex3d(x, y, z);
			z = getZ(x, y+1);
			glVertex3d(x, y+1, z);
			z = getZ(x+1, y+1);
			glVertex3d(x+1, y+1, z);
			z = getZ(x+1, y);
			glVertex3d(x+1, y, z);
			glEnd();
		}
	}
}
int Cell::getWIDTH() {
	return WIDTH;
}
int Cell::getHEIGHT() {
	return HEIGHT;
}
double Cell::getZ(double x, double y) {
	//x /= 5;
	//y /= 5;
	double z = 0;
	z += 2 * 2 * sin(.4 * y);
	z += 1.5 * cos(.3 * x);
	z += 2 * 4 * sin(.2 * x) * cos(.3 * y);
	z += 2 * 6 * sin(.11 * x) * cos(.03 * y);
	//z = cos(x) + sin(y);
	return z;
}