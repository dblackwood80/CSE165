#ifndef RECT_H
#define RECT_H

#include <vector>

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h, float r, float g, float b);
	~Rect();

	bool contains(float x, float y);
	void retrieve(std::vector<Rect*> rect);

	float x, y, r, g, b;
	float width, height;
};

#endif // !RECT_H
