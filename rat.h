#pragma once
class Rat {
public:
	Rat(double x, double y);
	double getX();
	double getY();
	//getZ
	//setZ
	double getDX();
	double getDY();
	double getRadius();
	void setSpeed(double new_speed);
	void setX(double x);
	void spinLeft();
	void spinRight();
	void crawlForward();
	void jump();
	void Draw();
private:
	double mdegrees;
	double mradius;
	double mx;
	double my;
	double mz;
	double speed;
};



