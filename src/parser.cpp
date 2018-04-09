#include "../include/parser.h"
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

char ** parse_args( char *line ){
  char **args = (char **)calloc(10, sizeof(char *));
  char *temp = 0;
  int i = 0;
  while (temp = strsep(&line, " ")){
    args[i] = temp;
    i++;
  }
  return args;
}

void parse_line(char *str, matrix& edges){
	char **args = parse_args(str);
	std::cout<<"\n";
	point *p;
	for(int i = 0; i < 2; i++){
		p = new point(atoi(args[(i*3) + 0]), atoi(args[(i*3) + 1]), atoi(args[(i*3) + 2]));
		edges+=(*p);
	}

}

void parse_scale(char *str, matrix& transform){
	char **args = parse_args(str);
	std::vector<double> p;
	for (int j = 0; j < 3; j++){
		p.push_back(atof(args[j]));
	}
	matrix scale = create_scale(p);
	transform = scale * transform;
}

void parse_translate(char *str, matrix& transform){
	char **args = parse_args(str);
	std::vector<double> p;
	for (int j = 0; j < 3; j++){
		p.push_back(atof(args[j]));
	}
	matrix translate = create_translate(p);
	transform = translate * transform;
}

void parse_rotate(char *str, matrix& transform){
	char **args = parse_args(str);
	matrix rotate = matrix(4, 4);
	rotate.ident();
	if (strncmp(args[0], "x", 1) == 0){
		std::cout<<"rotating\n";
		rotate = create_rotateX(atof(args[1]));
	}
	else if (strncmp(args[0], "y", 1) == 0){
		std::cout<<"rotating\n";
		rotate = create_rotateY(atof(args[1]));
	}
	else if (strncmp(args[0], "z", 1) == 0){
		std::cout<<"rotating\n";
		rotate = create_rotateZ(atof(args[1]));
	}
	transform = rotate * transform;

}

void parse_display(screen& s, matrix& m, polygon& poly){
	FILE *f;
	m.draw(s);
	std::cout<<"here\n";
	poly.draw(s);
	std::cout<<"there\n";
	f = popen("display", "w");
	s.render(f);
	pclose(f);
	std::cout<<"rendered\n";
}

void parse_hermite(char *str, matrix& edges){	
	std::vector<double> x = std::vector<double>(4, 0); std::vector<double> y = std::vector<double>(4, 0); int step = 25;
	char **args = parse_args(str);
	int j = 0;
	for(int i = 0; i < 8; i+=2){
		x[j] = atof(args[i]);
		y[j] = atof(args[i+1]);
		j++;
	}
	matrix intermediate = matrix(); intermediate+=x; intermediate+=y;
	matrix coeffs = generate_curve_coefs(intermediate, 0);
	matrix hermite = make_curve(coeffs, step);
	edges+=hermite;
	std::cout<<"herm\n";
}
void parse_bezier(char *str, matrix& edges){
	std::cout<<str<<"\n";
	std::vector<double> x = std::vector<double>(4, 0); std::vector<double> y = std::vector<double>(4, 0); int step = 25;
	char **args = parse_args(str);
	int j = 0;
	for(int i = 0; i < 8; i+=2){
		x[j] = atof(args[i]);
		y[j] = atof(args[i+1]);
		j++;
	}
	matrix intermediate = matrix(); intermediate+=x; intermediate+=y;
	matrix coeffs = generate_curve_coefs(intermediate, 1);
	matrix bezier = make_curve(coeffs, step);
	edges+=bezier;
	std::cout<<"bez\n";
}
void parse_circle(char *str, matrix& edges){
	double r; std::vector<double> pc = std::vector<double>(4, 0); int step = 25;
	char **args = parse_args(str);
	for(int i = 0; i < 3; i++){
		pc[i] = atof(args[i]);
	}
	r = atof(args[3]);
	matrix circle = make_circle(r, pc, step);
	edges += circle;
}
void parse_sphere(char *str, matrix& edges){
	double r; std::vector<double> pc = std::vector<double>(4, 0); int step = 25;
	char **args = parse_args(str);
	for(int i = 0; i < 3; i++){
		pc[i] = atof(args[i]);
	}
	r = atof(args[3]);
	std::cout<<"create sphere\n";
	matrix sphere = create_sphere(pc, r, step);
	std::cout<<"add sphere\n";
	edges += sphere;
}
void parse_torus(char *str, matrix& edges){
	double r; double R; std::vector<double> pc = std::vector<double>(4, 0); int step = 25;
	char **args = parse_args(str);
	for(int i = 0; i < 3; i++){
		pc[i] = atof(args[i]);
	}
	r = atof(args[3]);
	R = atof(args[4]);
	matrix torus = create_torus(pc, r, R, step);
	edges += torus;
}
void parse_box(char *str, matrix& edges){
	double w; double h; double d; std::vector<double> pc = std::vector<double>(4, 0);
	char **args = parse_args(str);
	for(int i = 0; i < 3; i++){
		pc[i] = atof(args[i]);
	}
	w = atof(args[3]);
	h = atof(args[4]);
	d = atof(args[5]);
	matrix box = create_box(pc, w, h, d);
	edges += box;
}
void parse_save(screen& s, matrix& m, polygon& poly, char *str){
	m.draw(s);
	poly.draw(s);
	s.render(str);
}
void parse_apply(matrix& transform, matrix& poly){
	poly = transform * poly;
}
void parse_file ( const char * filename, 
		  matrix&  transform, 
		  matrix&  edges,
		  polygon& poly,
		  screen& s){
	std::ifstream f;
	f.open(filename);
	std::cout<<"file read\n";
	char * str = (char *) calloc(250, sizeof(char));
	
	f.getline(str, 250);


	while ( (f.rdstate() & std::ifstream::eofbit ) == 0 ){
		if(strncmp(str, "line", 250) == 0){
			f.getline(str, 250);
			parse_line(str, edges);
		}
		
		else if(strncmp(str, "ident", 250) == 0){
			transform.ident();
		}

		else if(strncmp(str, "scale", 250) == 0){
			f.getline(str, 250);
			parse_scale(str, transform);
		}

		else if(strncmp(str, "move", 250) == 0){
			f.getline(str, 250);
			parse_translate(str, transform);
		}

		else if(strncmp(str, "rotate", 250) == 0){
			f.getline(str, 250);
			parse_rotate(str, transform);
		}

		else if(strncmp(str, "apply", 250) == 0){
			parse_apply(transform, poly);
		}

		else if(strncmp(str, "display", 250) == 0){
			s.clear();
			parse_display(s, edges, poly);
		}

		else if(strncmp(str, "save", 250) == 0){
			s.clear();
			f.getline(str, 250);
			parse_save(s, edges, poly, str);
		}

		else if(strncmp(str, "clear", 250) == 0){
			edges = matrix();
			poly = polygon();
		}
		else if(strncmp(str, "hermite", 250) == 0){
			f.getline(str, 250);
			parse_hermite(str, edges);
		}
		
		else if(strncmp(str, "bezier", 250) == 0){
			f.getline(str, 250);
			parse_bezier(str, edges);
		}

		else if(strncmp(str, "circle", 250) == 0){
			f.getline(str, 250);
			parse_circle(str, edges);
		}

		else if(strncmp(str, "sphere", 250) == 0){
			std::cout<<"sphere\n";
			f.getline(str, 250);
			parse_sphere(str, poly);
		}

		else if(strncmp(str, "torus", 250) == 0){
			f.getline(str, 250);
			parse_torus(str, poly);
		}

		else if(strncmp(str, "box", 250) == 0){
			f.getline(str, 250);
			parse_box(str, poly);
		}

		f.getline(str, 250);
	}
}
