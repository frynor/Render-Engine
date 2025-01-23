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

	Vector2 v1 = {0, 0};
	Vector2 v2 = {100, 0};
	Vector2 v3 = {50, 50};

	rasterizeTriangle(rasterizer, fb, &v1, &v2, &v3);

	refresh();

	getch();

	rasterizer_destroy(rasterizer);
	endwin();

	return 0;
}
