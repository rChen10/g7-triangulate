#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "matrix.h"
#include "polygon.h"

void parse_file ( const char * filename, 
		  matrix&  transform, 
		  matrix&  edges,
		  polygon& polygons,
		  screen& s);

#endif
