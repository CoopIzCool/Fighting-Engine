#pragma once
#include "Colors.h"

class Surface
{
public:
	Surface(int Width, int Height);
	Surface(const Surface&);
	~Surface();
	Surface& operator=(const Surface&);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};