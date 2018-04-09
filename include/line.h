#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

//#ifndef __SCREEN_H__
//#define __SCREEN_H__
#include "screen.h"
//#endif

#ifndef __LINE_H__
#define __LINE_H__
class line{
	public:

	point p0, p1;
	pixel color;
	struct Private;

	line();

	line(int x0, int y0, int x1, int y1);

	line(point pi, point pf);

	line(std::vector<double> pi, std::vector<double> pf);

	void set_color(pixel p);

	void draw(screen& s);
};
#endif
