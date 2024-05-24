#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

void write_color(FILE* f, color c) {
	
	double r = c.x;
	double g = c.y;
	double b = c.z;

	int rbyte = (int) 255.999 * r;
	int gbyte = (int) 255.999 * g;
	int bbyte = (int) 255.999 * b;

	printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif
