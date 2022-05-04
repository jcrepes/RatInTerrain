#include <cmath>
#include "rat.h"
#include "graphics.h"
#include "glut.h"
//include algorithm
//extern Rat gRat;

Rat::Rat(double x, double y) {
	mx = x;
	my = y;
	mz = 0;
	//waterHeight;
	mdegrees = 0;
	mradius = .15;
	speed = .1;
}
double Rat::getX() {
	return mx;
}
double Rat::getY() {
	return my;
}
//getZ() {
//	z = std::max(function(x,y), waterlevel) + flyheight;
double Rat::getDX() {
	double rads = mdegrees * 3.1415926 / 180.0;
	double dx = cos(rads);
	return dx;
}
double Rat::getDY() {
	double rads = mdegrees * 3.1415926 / 180.0;
	double dy = sin(rads);
	return dy;
}
double Rat::getRadius() {
	return mradius;
}
void Rat::setSpeed(double new_speed) {
	speed = new_speed;
}
void Rat::setX(double x) {
	mx = x;
}
void Rat::spinLeft() {
	mdegrees += 1;
}
void Rat::spinRight() {
	mdegrees -= 1;
}
void Rat::crawlForward() {
	double dx = getDX();
	double dy = getDY();
	double SPEED = speed;
	mx += dx * SPEED;
	my += dy * SPEED;
	/*if (mMaze->isSafe(mx + dx * SPEED, my + dy * SPEED, mradius)) {
		mx += dx * SPEED;
		my += dy * SPEED;
	}
	else if (mMaze->isSafe(mx + dx * SPEED, my, mradius)) {
		mx += dx * SPEED;
	}
	else if (mMaze->isSafe(mx, my + dy * SPEED, mradius)) {
		my += dy * SPEED;
	}*/
}
void Rat::jump() {
	if (mz < 10) {
		mz += .1;
	}
}
void Rat::Draw() {
	glPushMatrix();
	glColor3d(1, 0, 0);
	glTranslated(mx, my, mz);
	glRotated(mdegrees, 0, 0, 1);
	DrawTriangle(.2, 0, -.2, .2, -.2, -.2);
	glPopMatrix();
}