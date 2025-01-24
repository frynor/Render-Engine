#include "include/matrix44.h"
#include "include/vector2.h"
#include "include/rasterizer.h"
#include <ncurses.h>
#include <stdio.h>

#define PI 3.141592653f

int main() {
	initscr();
	noecho();
	raw();

	int width = 1920, height = 1080;

	Rasterizer* rasterizer = rasterizer_create(width, height);
	if (!rasterizer) {
		fprintf(stderr, "Failed to create rasterizer\n");
		return 1;
	}
	Framebuffer* fb = rasterizer_get_framebuffer(rasterizer);
	if (!fb) {
		fprintf(stderr, "Failed to create framebuffer");
	}

	// Vector2 v1 = {10, 0};
	// Vector2 v2 = {50, 10};
//	Vector2 v3 = {100, 40};


	float angle = 0;
	while (angle < 1) {
		Matrix44 transformation = matrix44_create_default(); 
		Vector3 v4 = {2, 1, 1};

		scale(&transformation, &v4);

		Vector4 v1 = {10, 10, 1, 1};
		Vector4 v2 = {40, 10, 1, 1};
		Vector4 v3 = {25, 20, 1, 1};

		v1 = matrix44_multiply_vector4(&transformation, &v1);
		v2 = matrix44_multiply_vector4(&transformation, &v2);
		v3 = matrix44_multiply_vector4(&transformation, &v3);
		
		Vector2 tv1 = vector2_create(v1.x, v1.y);
		Vector2 tv2 = vector2_create(v2.x, v2.y);
		Vector2 tv3 = vector2_create(v3.x, v3.y);

		rasterizeTriangle(rasterizer, fb, &tv1, &tv2, &tv3);
		getch();
		clear();
		angle += 5;
		
	}

	refresh();

	getch();

	// rasterizer_destroy(rasterizer);
	endwin();

	return 0;
}
