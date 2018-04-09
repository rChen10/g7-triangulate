
#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "pixel.h"

class point : public std::vector<int>{
	public:

	point();

	point(int x);

	point(int x, int y);

	point(int x, int y, int z);

	point(int x, int y, int z, int i);

	point(std::vector<int> v);

	point(std::vector<double> v);

	//int operator[](int i);

};

class screen{
	public:
		std::vector<pixel> colors;
		pixel **grid;
		int h, w;

		screen();

		screen(int x, int y);

		void render(const char* name);

		void render(FILE * f);

		void clear();

		void plot(point& p, pixel col);

		//pixel& insert_color(pixel col);
};

#endif
