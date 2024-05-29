#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"

#define MAX_OBJECTS 100

typedef struct hit_record {
	point3 p;
	vec3 normal;
	double t;
} hit_record;

typedef int (*hit_test)(void* data, ray r, double ray_tmin, double ray_tmax, hit_record* rec);

typedef struct hittable {
	hit_test is_hit;
	void* data;
} hittable;

typedef struct hit_list {
	hittable hittables[MAX_OBJECTS];	
} hit_list;

#endif
