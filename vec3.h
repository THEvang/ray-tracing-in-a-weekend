#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct vec3 {
	union {
		double data[3];
		struct {
			double x;
			double y;
			double z;
		};
	};
} vec3;

vec3 vec3_add(vec3 a, vec3 b) {
	return (vec3) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
}

vec3 vec3_sub(vec3 a, vec3 b) {
	return (vec3) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
}

double vec3_length(vec3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 vec3_mult(vec3 a, double t) {
	return (vec3) {
		.x = a.x * t,
		.y = a.y * t,
		.z = a.z * t
	};
}

vec3 vec3_normalize(vec3 v) {
	return vec3_mult(v, 1.0 / vec3_length(v));
}

#endif
