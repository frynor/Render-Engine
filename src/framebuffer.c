#include "../include/framebuffer.h"
#include <stdio.h>
#include <stdlib.h>

Framebuffer* framebuffer_create(int width, int height) {
	if (width <= 0 || height <= 0) {
		return NULL;
	}

	Framebuffer* fb = (Framebuffer*)malloc(sizeof(Framebuffer));
	if (!fb) {
		return NULL;
	}

	fb->pixels = malloc(width * height * sizeof(Color));
	if (!fb->pixels) {
		return NULL;
	}
	
	fb->width = width;
	fb->height = height;

	return fb;
}

void framebuffer_destroy(Framebuffer* fb) {
	if (fb != NULL) {
		if (fb->pixels != NULL) {
			free(fb->pixels);
		}
		free(fb);
	}
}
