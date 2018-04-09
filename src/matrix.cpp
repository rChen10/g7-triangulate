#include <vector>
#include <iostream>
#include "../include/matrix.h"

matrix::matrix(){
	m = std::vector< std::vector<double> >();
	s = 0;
}

matrix::matrix(int x, int y){
		std::vector<double> *v;
		for(int i = 0; i < x; i++){
			v = new std::vector<double>((double)y, 0);
			m.push_back(*v);
		}
		s = x;
}

//matrix::matrix( matrix&& rv ){
//	m = std::move(rv.m);
//	s = rv.s;
//
//	rv.s = 0;
//}
//
//matrix& matrix::operator=(matrix&& rv){
//	m = std::move(rv.m);
//	s = rv.s;
//	return (*this);
//}

matrix& matrix::operator+=(std::vector<int>& p){
	std::vector<double> *dp = new std::vector<double>();
	for (int i = 0; i < 4; i++){
		std::cout<<p[i]<<"\n";
		(*dp).push_back( (double) p[i] );
	}
	m.push_back(*dp);
	s++;
	return *this;
}

matrix& matrix::operator+=(std::vector<double>& p){
	m.push_back(p);
	s++;
	return *this;
}

matrix& matrix::operator+=(line& l){
	(*this)+=l.p0;
	(*this)+=l.p1;
	s+=2;
	return *this;
}

matrix& matrix::operator+=(matrix& mx){
	for(int i = 0; i < mx.size(); i++){
		(*this) += mx[i];
	}
	return *this;
}

void matrix::ident(){
		for(int i = 0; i < s; i++){
			for(int j = 0; j < m[i].size(); j++){
				if( j == i )
					m[i][j] = 1;
				else
					m[i][j] = 0;
			}
		}	
}

matrix& matrix::operator*=(matrix& m){
		
}

int matrix::size(){
		return s;
}

std::vector<double>& matrix::operator[](int i){
	return m[i];
}

void matrix::draw(screen& scrn){
		for(int i = 0; i < s; i+=2){
			point p0 = point(m[i]);
			point p1 = point(m[i+1]);
			line l = line(p0, p1);
			l.draw(scrn);

		}
}

void matrix::draw(screen& scrn, pixel& color){
		for(int i = 0; i < s; i+=2){
			point p0 = point(m[i]);
			point p1 = point(m[i+1]);
			line l = line(p0, p1);
			l.set_color(color);
			l.draw(scrn);

		}
}

std::ostream& operator<<(std::ostream& os, matrix& m){
	//os << m.size() << "\n";
	for(int i = 0; i < m[0].size(); i++){
		os << "| ";
		for(int j = 0; j < m.size(); j++){
			os << m[j][i] << " ";
		}
		os << "|\n";
	}

	return os;
}

matrix operator*(matrix& m1, matrix& m2){
	double sum = 0;
	matrix m = matrix();
	std::vector<double> *v;
	for(int i = 0; i < m2.size(); i++){
		v = new std::vector<double>();
		for(int j = 0; j < m2[0].size(); j++){
			for(int k = 0; k < m2[0].size(); k++){
				sum += m1[k][j] * m2[i][k];
			}
			(*v).push_back(sum);
			sum = 0;
		}
		m += (*v);
	}
	return m;
}
