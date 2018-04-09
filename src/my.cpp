#include "../include/my.h"

//std::vector<double> my::view = my::vector(0, 0, 1, 1);

my::vector::vector() : std::vector<double>(){
}

my::vector::vector(double a, double b, double c, double d) : std::vector<double>(){
	(*this).push_back(a);
	(*this).push_back(b);
	(*this).push_back(c);
	(*this).push_back(d);
}

my::vector::vector(std::vector<double>& v1, std::vector<double>& v2) : std::vector<double>(){
	(*this).push_back(v2[0] - v1[0]);
	(*this).push_back(v2[1] - v1[1]);
	(*this).push_back(v2[2] - v1[2]);
	(*this).push_back(1);
}

double my::vector::dot(std::vector<double>& v){
	return (v[0] * (*this)[0]) + (v[1] * (*this)[1]) + (v[2] * (*this)[2]);
}

my::vector my::vector::cross(std::vector<double>& v){
	my::vector ret = my::vector();
	ret.push_back( ((*this)[1]*v[2]) - ((*this)[2]*v[1]) );
	ret.push_back( ((*this)[2]*v[0]) - ((*this)[0]*v[2]) );
	ret.push_back( ((*this)[0]*v[1]) - ((*this)[1]*v[0]) );
	ret.push_back(1);

	return ret;
}
