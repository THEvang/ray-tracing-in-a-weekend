#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"
#include "ray.h"

typedef struct Sphere {
	vec3 center;
	double radius;
} Sphere;

int hit_sphere(void* data, ray r, double ray_tmin, double ray_tmax, hit_record* rec) {

	Sphere* sphere = (Sphere*) data;

	vec3 oc = vec3_sub(sphere->center, r.orig);
	double a = vec3_dot(r.dir, r.dir);
	double h = vec3_dot(r.dir, oc);
	double c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	double discriminant = h * h - a * c;
	double sqrtd = sqrt(discriminant);

	double root = (h - sqrtd) / a;

	if (root <= ray_tmin || ray_tmax <= root) {
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root) {
			return false;
		}
	}

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vec3_mult(vec3_sub(rec->p, sphere->center), 1.0 / sphere->radius);

	return true;
}

#endif
