#pragma once
class ScreenObject
{
private:
	int x, y, rotation;

public:
	ScreenObject();
	~ScreenObject();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setRotation(int angle);
	int getRotation();
};

