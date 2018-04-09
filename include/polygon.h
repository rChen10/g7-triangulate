#ifndef __POLYGON_H__
#define __POLYGON_H_

#include <iostream>
#include <fstream>
#include <cmath>

#include "matrix.h"
#include "my.h"

class polygon : public matrix{
	public:

	polygon();

	polygon(matrix& m);

	polygon& operator+=(line l);

	polygon& operator+=(std::vector<int>& p);

	polygon& operator+=(std::vector<double>& p);

	polygon& operator+=(line& l);

	polygon& operator+=(matrix& mx);

	void ident();

	int size();

	std::vector<double>& operator[](int i);

	void draw(screen& scrn);

	void draw(screen& scrn, pixel& color);
};

#define PI atan(1)*4
//helper
static double convert(double theta){
	return theta * PI / 180;
}

matrix create_translate(std::vector<double> p);

matrix create_scale(std::vector<double> a);

matrix create_rotateZ(double theta);

matrix create_rotateX(double theta);

matrix create_rotateY(double theta);

matrix make_curve(matrix& coefs, int step);

matrix make_circle(double r, std::vector<double>& pc, int step);

matrix generate_curve_coefs(matrix& a, int type);


matrix create_sphere(std::vector<double>& pc, double r, int step);

matrix generate_sphere(std::vector<double>& pc, double r, int step);

matrix create_torus(std::vector<double>& pc, double r, double R, int step);

matrix generate_torus(std::vector<double>& pc, double r, double R, int step);

matrix create_box(std::vector<double>& pc, double w, double h, double d);
#endif
