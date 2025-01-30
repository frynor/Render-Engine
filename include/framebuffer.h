#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef uint8_t depthbuffer_t;
typedef uint16_t colorbuffer_t;

#define MAX_DEPTH_VALUE 0xFF

typedef struct {
	int width;
	int height;
	depthbuffer_t* depthbuffer;
	colorbuffer_t* colorbuffer;
} Framebuffer;

Framebuffer* framebuffer_create(int width, int height);
void framebuffer_destroy(Framebuffer* fb);


void framebuffer_recreate(Framebuffer* fb, int width, int height);
void framebuffer_clear(Framebuffer*fb, int clearColor);
void framebuffer_set_pixel(Framebuffer* fb, int x, int y, colorbuffer_t pixelcolor, depthbuffer_t depth);
colorbuffer_t framebuffer_get_color(Framebuffer* fb, int x, int y);
depthbuffer_t framebuffer_get_depth(Framebuffer* fb, int x, int y);
void framebuffer_print(Framebuffer* fb);
int framebuffer_get_width(Framebuffer* fb);
int framebuffer_get_height(Framebuffer* fb);

#endif // FRAMEBUFFER_H


