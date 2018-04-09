#include <vector>
#include <iostream>

#include "line.h"


#ifndef __MATRIX_H__
#define __MATRIX_H__

class matrix{
	public:
	std::vector< std::vector<double> > m;
	int s;
	
	matrix();

	matrix(int x, int y);
	
	//matrix(matrix&& lv);

	//matrix& operator=(matrix&& lv);

	matrix& operator+=(std::vector<int>& p);

	matrix& operator+=(std::vector<double>& p);

	matrix& operator+=(line& l);

	matrix& operator+=(matrix& mx);

	void ident();

	matrix& operator*=(matrix& m);

	int size();

	std::vector<double>& operator[](int i);

	void draw(screen& scrn);

	void draw(screen& scrn, pixel& color);
	
};

std::ostream& operator<<(std::ostream& os, matrix& m);

matrix operator*(matrix& m1, matrix& m2);

#endif
