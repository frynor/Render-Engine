#include "../include/framebuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Constructor
Framebuffer* framebuffer_create(int width, int height) {
	Framebuffer* fb = malloc(sizeof(Framebuffer));
	if (!fb) {
		fprintf(stderr, "Failed to allocate memory for the framebuffer!\n");
		return NULL;
	}

	fb->width = width;
	fb->height = height;

	fb->colorbuffer = malloc(width * height * sizeof(colorbuffer_t));
	fb->depthbuffer = malloc(width * height * sizeof(depthbuffer_t));

	if (!fb->colorbuffer || !fb->depthbuffer) {
		free(fb);
		return NULL;
	}

	if (!fb->colorbuffer || !fb->depthbuffer) {
		fprintf(stderr, "Failed to allocate memory for colorbuffer and depthbuffer!\n");
		return NULL;
	}

	return fb;
}


// Destructor 
void framebuffer_destroy(Framebuffer* fb) {
	if (!fb) return;

	free(fb->colorbuffer);
	free(fb->depthbuffer);
	free(fb);
}

void framebuffer_recreate(Framebuffer* fb, int width, int height) {
	if (!fb) return;

	// Freeing existing buffers
	free(fb->colorbuffer);
	free(fb->depthbuffer);

	// Updating dimensions
	fb->width = width;
	fb->height = height;

	// Reallocating buffers
	fb->colorbuffer = malloc(width * height * sizeof(colorbuffer_t));
	fb->depthbuffer = malloc(width * height * sizeof(depthbuffer_t));

}

void framebuffer_clear(Framebuffer* fb, int clearColor) {
	if (!fb) return;

	memset(fb->colorbuffer, clearColor, sizeof(colorbuffer_t) * fb->width * fb->height);
	memset(fb->depthbuffer, MAX_DEPTH_VALUE, sizeof(depthbuffer_t) * fb->width * fb->height);
}

void framebuffer_set_pixel(Framebuffer *fb, int x, int y, colorbuffer_t pixelcolor, depthbuffer_t depth) {
	if (!fb || x < 0 || y < 0 || x>= fb->width || y >= fb->height) return;
	
	int index = (y * fb->width) + x;

	if (depth < fb->depthbuffer[index]) {
		fb->colorbuffer[index] = pixelcolor;
		fb->depthbuffer[index] = depth;
	}
}

colorbuffer_t framebuffer_get_color(Framebuffer *fb, int x, int y) {
	if (!fb || x < 0 || y < 0 || x>= fb->width || y >= fb->height) return 0;

	int index = (y * fb->width) + x;
	return fb->colorbuffer[index];
}

depthbuffer_t framebuffer_get_depth(Framebuffer *fb, int x, int y) {
	if (!fb || x < 0 || y < 0 || x>= fb->width || y >= fb->height) return 0;

	int index = (y * fb->width) + x;
	return fb->depthbuffer[index];
}

void framebuffer_print(Framebuffer *fb) {
	if (!fb) return;

	for (int i = 0; i < fb->width; i++) {
		for (int j = 0; j < fb->height; j++) {
			int index = (j * fb->width) + i;
		
			if (!fb->colorbuffer[index]) continue;

			int color = (char)(fb->colorbuffer[index] >> 8);
			attron(COLOR_PAIR(color));

			mvprintw(j, i, "%c", (char)fb->colorbuffer[index]);
		}
	}
}

int framebuffer_get_width(Framebuffer* fb) {
	return fb ? fb->width : 0;
}

int framebuffer_get_height(Framebuffer* fb) {
	return fb ? fb->height : 0;
}
