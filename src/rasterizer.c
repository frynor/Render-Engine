#include "../include/rasterizer.h"
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a)>(b))? (a) : (b))
#define MIN(a, b) (((a)<(b))? (a) : (b))

static bool isPointTriangle(int i, int j, const Vector2* v1, const Vector2* v2, const Vector2* v3) {
    float area = fabs((v1->x * (v2->y - v3->y) + v2->x * (v3->y - v1->y) + v3->x * (v1->y - v2->y)) / 2.0f);

    float area1 = fabs((i * (v2->y - v3->y) + v2->x * (v3->y - j) + v3->x * (j - v2->y)) / 2.0f);
    float area2 = fabs((v1->x * (j - v3->y) + i * (v3->y - v1->y) + v3->x * (v1->y - j)) / 2.0f);
    float area3 = fabs((v1->x * (v2->y - j) + v2->x * (j - v1->y) + i * (v1->y - v2->y)) / 2.0f);

    return fabs(area - (area1 + area2 + area3)) < 0.01f;

    // THANK YOU CHATGPT FOR BARYCENTRIC INTERPOLATION CALCULATION AND FORMULA, YOUR A TOP G!!!!!!!!!!!!!!!
}

/* static Framebuffer* framebuffer_create(int width, int height) {
	Framebuffer* fb = (Framebuffer*)malloc(sizeof(Framebuffer));
	if (!fb) return NULL;

	fb->width = width;
	fb->height = height;

	return fb;
} */

static void rasterizer_initialize_framebuffer(Rasterizer* rast, int width, int height) {
	if (!rast) return;
	rast->fb = framebuffer_create(width, height);
}

Rasterizer* rasterizer_create(int width, int height) {
	// Allocating the memory (heap memory (cool stuff bro, check heap vs stack (XD)))
	Rasterizer* rast = (Rasterizer*)malloc(sizeof(Rasterizer));
	if (!rast) {
		fprintf(stderr, "Memory allocation failed for Rasterizer\n");
		return NULL;
	} 

	rast->width = width;
	rast->height = height;

	rasterizer_initialize_framebuffer(rast, width, height);
	if (!rast->fb) {
		fprintf(stderr, "Failed to initialize framebuffer for Rasterizer\n");
		free(rast);
		return NULL;
	}

	return rast;
}

void rasterizer_destroy(Rasterizer* rast) {
	// Freeing up the memory
	if (rast) {
		if (rast->fb) {
			free(rast->fb);
			rast->fb = NULL;
		}
		free(rast);
	}
}

Framebuffer* rasterizer_get_framebuffer(const Rasterizer* rast) {
	return rast ? rast->fb : NULL; 
}

void rasterizeTriangle(const Rasterizer* rast, Framebuffer* fb, const Vector2* v1, const Vector2* v2, const Vector2* v3) {
	if (!rast || !v1 || !v2 || !v3) return;

	int minx, maxx;
	int miny, maxy;

	minx = MAX(0, MIN(v1->x, MIN(v2->x, v3->x)));
	miny = MAX(0, MIN(v1->y, MIN(v2->y, v3->x)));

	maxx = MIN(fb->width, ceil(MAX(v1->x, MAX(v2->x, v3->x)) + 1));
	maxy = MIN(fb->height, ceil(MAX(v1->y, MAX(v2->y, v3->x)) + 1));

	for (int j = miny; j < maxy; j++) {
		for (int i = minx; i < maxx; i++) {
			if(isPointTriangle(i, j, v1, v2, v3)) {
				mvprintw(j, i, "#");
			} else {
				mvprintw(j, i, ".");
			}
		}
	} 

}
