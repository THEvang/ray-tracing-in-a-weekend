#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
	vec3 orig;
	vec3 dir;
} ray;


vec3 ray_at(ray r, double t) {
	return vec3_add(r.orig, vec3_mult(r.dir, t));
}

#endif
