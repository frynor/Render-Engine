#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef struct {
	uint16_t r, g, b, a;
} Color;

typedef uint8_t depthbuffer_t;

typedef struct {
	int width, height;
	Color* pixels;
	depthbuffer_t* dpf;
} Framebuffer;

Framebuffer* framebuffer_create(int width, int height);
void framebuffer_destroy(Framebuffer* fb);

#endif // FRAMEBUFFER_H
