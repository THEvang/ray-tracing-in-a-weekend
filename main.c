#include <stdio.h>
#include "color.h"
#include "ray.h"
#include <stdbool.h>

double hit_sphere(vec3 center, double radius, ray r) {
	vec3 oc = vec3_sub(center, r.orig);
	double a = vec3_dot(r.dir, r.dir);
	double b = -2.0 * vec3_dot(r.dir, oc);
	double c = vec3_dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4.0 * a * c;

	if (discriminant < 0) {
		return -1.0;
	} else {
		return	(-b - sqrt(discriminant)) / (2.0 * a);
	}
}

color ray_color(ray r) {

	double t = hit_sphere((vec3) {0, 0, -1}, 0.5, r);
	if (t >= 0) {

		vec3 N = vec3_sub(ray_at(r, t), (vec3){0,0,-1});
		N = vec3_normalize(N);
		return vec3_mult((color) {N.x + 1.0, N.y + 1.0, N.z + 1.0}, 0.5); 
	}

	vec3 unit_direction = vec3_normalize(r.dir);
	double a = 0.5 * (unit_direction.y + 1.0);
		
	vec3 res = vec3_mult((color) {1.0, 1.0, 1.0}, (1.0 - a));
	res = vec3_add(res, vec3_mult((color) {0.5, 0.7, 1.0}, a));
	return res;
}

int main() {
	
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = (int) (image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	//Camera
	double focal_length = 1.0;
	double viewport_height = 2;
	double viewport_width = viewport_height * (((double)image_width / image_height));
	vec3 camera_center = {0,0,0};

	vec3 viewport_u = {viewport_width, 0, 0};
	vec3 viewport_v = {0, -viewport_height, 0};

	vec3 delta_u = vec3_mult(viewport_u, 1.0  / image_width);
	vec3 delta_v = vec3_mult(viewport_v, 1.0 / image_height);

	//Camera Perspect: x up, y right, z away from viewport
	vec3 viewport_upper_left = camera_center;
	viewport_upper_left = vec3_add(viewport_upper_left, (vec3) {0, 0, -focal_length});
	viewport_upper_left = vec3_add(viewport_upper_left, vec3_mult(viewport_u, -0.5));
	viewport_upper_left = vec3_add(viewport_upper_left, vec3_mult(viewport_v, -0.5));

	vec3 pixel00_loc = viewport_upper_left; 
	pixel00_loc = vec3_add(pixel00_loc, vec3_mult(delta_u, 0.5));
	pixel00_loc = vec3_add(pixel00_loc, vec3_mult(delta_v, 0.5));

	printf("P3\n%d %d \n255\n", image_width, image_height);

	for (int i = 0; i < image_height; i++) {
		fprintf(stderr, "\rScanlines remaining: %d", image_height -1);
		fflush(stderr);
		for (int j = 0; j < image_width; j++) {
			vec3 pixel_center = pixel00_loc;
			pixel_center = vec3_add(pixel_center, vec3_mult(delta_u, j));
			pixel_center = vec3_add(pixel_center, vec3_mult(delta_v, i));
			
			vec3 ray_direction = pixel_center;
			ray_direction = vec3_sub(pixel_center, camera_center);

			ray r = {camera_center, ray_direction};

			color pixel_color = ray_color(r);
			write_color(stdout, pixel_color);
		}
	}

	fprintf(stderr, "\rDone.                        \n");
}
