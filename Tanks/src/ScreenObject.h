#pragma once
class ScreenObject
{
private:
	float x, y, rotation;

public:
	ScreenObject();
	~ScreenObject();
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void setRotation(float angle);
	float getRotation();
};

