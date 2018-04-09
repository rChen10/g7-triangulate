#include <iostream>
#include <vector>
#include <fstream>
#include "../include/line.h"

struct line::Private{
	static void draw_oct1(point p0, point p1, screen& s, pixel color, int a, int b){
		point pn = point(p0[0], p0[1], p0[2]);
		int d = a + b/2;
		while (pn[0] < p1[0]){
			s.plot(pn, color);
			if (d > 0){
				pn[1] +=  1;
				d += (b);	
			}	
			pn[0] += 1;
			d += (a);
		}
		s.plot(pn, color);
	}

	
	static void draw_oct2(point p0, point p1, screen& s, pixel color, int a, int b){
		point pn = point(p0[0], p0[1], p0[2]);
		int d = a/2 + b;
		while (pn[1] < p1[1]){
			s.plot(pn, color);
			if (d < 0){
				pn[0] += 1;
				d += (a);	
			}	
			pn[1] +=  1;
			d += (b);
		}
			s.plot(pn, color);
	}
	static void draw_oct7(point p0, point p1, screen& s, pixel color, int a, int b){
		point pn = point(p0[0], p0[1], p0[2]);
		int d = a/2 + b;
		while (pn[1] > p1[1]){
			s.plot(pn, color);
			if (d > 0){
				pn[0] += 1;
				d += (a);	
			}	
			pn[1] += -1;
			d -= (b);
		}
			s.plot(pn, color);
	}
	static void draw_oct8(point p0, point p1, screen& s, pixel color, int a, int b){
		point pn = point(p0[0], p0[1], p0[2]);
		int d = a - b/2;
		while (pn[0] < p1[0]){
			s.plot(pn, color);
			if (d < 0){
				pn[1] -= 1;
				d -= (b);	
			}	
			pn[0] += 1;
			d += (a);
		}
			s.plot(pn, color);
	}
};

line::line(){
		p0 = point();
		p1 = point();
		color = pixel(0, 0, 0);
}

line::line(int x0, int y0, int x1, int y1){
		if(x1 - x0 < 0){
			p0 = point(x1, y1);
			p1 = point(x0, y0);
		}
		else{
			p0 = point(x0, y0);
			p1 = point(x1, y1);
		}
		color = pixel(0, 0, 0);
}

line::line(point pi, point pf){
		if(pf[0] - pi[0] < 0){
			p0 = point(pf[0], pf[1]);
			p1 = point(pi[0], pi[1]);
		}
		else{
			p0 = point(pi[0], pi[1]);
			p1 = point(pf[0], pf[1]);
		}
		color = pixel(0, 0, 0);
}

line::line(std::vector<double> pi, std::vector<double> pf){
	point pip = point(pi);
	point pfp = point(pf);

	(*this) = line(pip, pfp);
}

void line::set_color(pixel p){
		color = p;
}

void line::draw(screen& s){
	
	int a = 2 * (p1[1]-p0[1]); int b = -2 * (p1[0]-p0[0]);

	if ( std::abs(p1[0] - p0[0]) >= std::abs(p1[1] - p0[1]) ){
		if (a > 0)
			Private::draw_oct1(p0, p1, s, color, a, b);
		else
			Private::draw_oct8(p0, p1, s, color, a, b);
	}
	else{
		if (a > 0)
			Private::draw_oct2(p0, p1, s, color, a, b);
		else
			Private::draw_oct7(p0, p1, s, color, a, b);
	}
}


