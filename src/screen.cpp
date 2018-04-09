#include <iostream>
#include <fstream>
#include <vector>
#include "../include/screen.h"

point::point(){
		//v = std::vector<int>(4, 0);
}

point::point(int x) : std::vector<int>(4, 0){
		(*this)[0] = x;
		(*this)[3] = 1;
}

point::point(int x, int y) : std::vector<int>(4, 0){
		//v = std::vector<int>(4, 0);
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[3] = 1;
}

point::point(int x, int y, int z) : std::vector<int>(4, 0){
		//v = std::vector<int>(4, 0);
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = 1;
}

point::point(int x, int y, int z, int i) : std::vector<int>(4, 0){
		//v = std::vector<int>(4, 0);
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = i;
}

point::point(std::vector<int> v) : std::vector<int>(4, 0){
		(*this)[0] = v[0];
		(*this)[1] = v[1];
		(*this)[2] = v[2];
		(*this)[3] = 1;
}

point::point(std::vector<double> v) : std::vector<int>(4, 0){
		(*this)[0] = (int) v[0];
		(*this)[1] = (int) v[1];
		(*this)[2] = (int) v[2];
		(*this)[3] = 1;
}
	//int operator[](int i){
	//	return v[i];
	//}

//	void add(int pos, int i){
//		this[pos] += i;
//	}

screen::screen(){
			grid = 0;
}

screen::screen(int x, int y){
			w = x;
			h = y;

			//colors.push_back( pixel(255, 255, 255) );
			//colors.push_back( pixel(0, 0, 0) );

			grid = (pixel **) calloc(y, sizeof(pixel *));
			for (int i = 0; i < h; i++){
				grid[i] = (pixel *) calloc(x, sizeof(pixel));
				for(int j = 0; j < w; j++){
					grid[i][j] = pixel(255, 255, 255);
				}
			}

}

void screen::render(const char* name){
			std::ofstream f;
			f.open(name);
			f << "P3\n";
			f << w << " " << h << "\n";
			f << "255\n";

			for(int i = h-1; i >= 0; i--){
				for(int j = 0; j < w; j++){
					f << grid[i][j];
					if (j != (w-1))
						f << " ";
				}
					f << "\n";
			}

			f.close();
}

void screen::render(FILE *f){
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  		for ( int y=h-1; y >= 0; y-- ) {
    			for ( int x=0; x < w; x++) 
      				fprintf(f, "%d %d %d ", grid[y][x].r, grid[y][x].g, grid[y][x].b);
    			fprintf(f, "\n");
			}
}

void screen::clear(){
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			grid[i][j] = pixel(255, 255, 255);
		}
	}
}

void screen::plot(point& p, pixel col){
	//pixel& c = insert_color(col);
	if(p[0] < w && p[0] > 0
		&& p[1] < h && p[1] > 0)
		grid[p[1]][p[0]] = col;
}

//pixel& screen::insert_color(pixel col){
//			for (int i = 0; i < colors.size(); i++){
//				if( colors[i] == col ){
//					//delete &col;
//					return colors[i];
//				}
//			}
//			pixel *cull = new pixel(col.r, col.g, col.b);
//			colors.push_back(*cull);
//			return *cull;
//}
