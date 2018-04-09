#include <iostream>
#include <fstream>
#include <string>
#include "../include/pixel.h"
//using namespace std;
pixel::pixel(int red, int green, int blue){
			r = red;
		       	g = green;
		       	b = blue;
}

pixel::pixel(){
			r = 0;
			g = 0;
			b = 0;
}

		//std::ostream& operator<<(std::ostream& fs){
		//	fs << r << " " << g << " " << b;
		//	return fs;
		//}

		//std::fstream& operator<<(std::fstream& fs){
		//	fs << r << " " << g << " " << b;
		//	return fs;
		//}

		//pixel *operator*(){
		//	return &this;
		//}
		

		//~pixel(){
			
			
		//	free(&r);
		//}

pixel& pixel::operator+=(int i){
			r = (r + i) % 256;
			g = (g + i) % 256;
			b = (b + i) % 256;
			return *this;
}

pixel& pixel::operator+=(pixel p){
			r = (r + p.r) % 256;
			g = (g + p.g) % 256;
			b = (b + p.b) % 256;
			return *this;
}

pixel& pixel::operator-=(int i){
			r -= i % 256;
			g -= i % 256;
			b -= i % 256;

			if (r < 0){
				r += 256;
			}
			if (g < 0){
				g += 256;
			}
			if (b < 0){
				b += 256;
			}
			return *this;
}

pixel& pixel::operator-=(pixel p){
			r -= p.r % 256;
			g -= p.g % 256;
			b -= p.b % 256;

			if (r < 0){
				r += 256;
			}
			if (g < 0){
				g += 256;
			}
			if (b < 0){
				b += 256;
			}
			return *this;
}

pixel& pixel::operator/=(int i){
			r = (int) r / i;
			g = (int) g / i;
			b = (int) b / i;
			return *this;
}

std::ostream& operator<<(std::ostream& os, const pixel& p){
	return os << p.r << " " << " " << p.g << " " << p.b;
}

bool operator==(pixel& p1, pixel& p2){
	if( p1.r == p2.r
		&& p1.g == p2.g
		&& p1.b == p2.b )
	return true;
	else return false;
}
