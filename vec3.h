#ifndef VEC3_H
#define VEC3_H

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

vec3 add(vec3 a, vec3 b) {
	return (vec3) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
}

#endif
