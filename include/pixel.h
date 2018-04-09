#include <iostream>
#include <fstream>
#include <string>

#ifndef __PIXEL_H__
#define __PIXEL_H__
class pixel{
	public:
		int r, g, b;
		pixel(int red, int green, int blue);

		pixel();

		pixel& operator+=(int i);

		pixel& operator+=(pixel p);

		pixel& operator-=(int i);

		pixel& operator-=(pixel p);

		pixel& operator/=(int i);
};

std::ostream& operator<<(std::ostream& os, const pixel& p);

bool operator==(pixel& p1, pixel& p2);

#endif
