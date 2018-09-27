#include "Rect.h"
#include <iostream>

std::vector<Rect*> ptrs;

Rect::Rect()
{
	x = 0.0f;
	y = 0.0f;
	width = 0.0f;
	height = 0.0f;
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}


Rect::Rect(float x, float y, float w, float h, float r, float g, float b)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->r = r;
	this->g = g;
	this->b =b;
}

Rect::~Rect()
{
}

void Rect::retrieve(std::vector<Rect*> rect)
{
	//std::cout << "X1: " << rect.at(1)->x << std::endl;
	for (int i = 0; i < rect.size(); i++)
	{
		if (ptrs.size() == rect.size())
		{
			//continue;
		}
		else
		{
			Rect* ne = new Rect(rect.at(i)->x, rect.at(i)->y, rect.at(i)->width, rect.at(i)->height, rect.at(i)->r, rect.at(i)->g, rect.at(i)->b);
			ptrs.push_back(ne);
		}
	}
}

bool Rect::contains(float x, float y)
{
	for (int i = 0; i < ptrs.size(); i++)
	{
		if (x >= ptrs.at(i)->x && x < ptrs.at(i)->x + ptrs.at(i)->width)
		{
			if (y < ptrs.at(i)->y && y >= ptrs.at(i)->y - ptrs.at(i)->height)
			{
				//std::cout << "HERE" << std::endl;	
				//std::cout << "SIZE: "<< ptrs.size() << std::endl;
				//std::cout << x << " Y1: " << y << "\nX1: " << ptrs.at(0)->x << " X2: " << ptrs.at(0)->x + ptrs.at(0)->width << std::endl;
				return true;
			}
			else
			{
				//std::cout << "THERE" << std::endl;
			}
		}
	}
	
	return false;
}