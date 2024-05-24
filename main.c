#include <stdio.h>
#include "color.h"
int main() {

	int image_width = 256;
	int image_height = 256;

	printf("P3\n%d %d \n255\n", image_width, image_height);

	for (int i = 0; i < image_height; i++) {
		fprintf(stderr, "\rScanlines remaining: %d", image_height -1);
		fflush(stderr);
		for (int j = 0; j < image_width; j++) {
			color c = {
				.x = (double) j / (image_width - 1),
				.y = (double) i / (image_height -1),
				.z = 0.0
			};
			write_color(stdout, c);
		}
	}

	fprintf(stderr, "\rDone.                        \n");
}
