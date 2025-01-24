#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "../include/vector2.h"
#include "../include/vector3.h"
#include "../include/vector4.h"
#include "../include/matrix44.h"
#include "../include/framebuffer.h"

typedef struct {
	Framebuffer* fb;
	int width, height;
} Rasterizer;


// Constructor and Destructor in C, kind of..... XD
Rasterizer* rasterizer_create(int width, int height); 
void rasterizer_destroy(Rasterizer* rast); 

// Framebuffer management
Framebuffer* rasterizer_get_framebuffer(const Rasterizer* rast);

// Rasterizer functions
void rasterizeTriangle(const Rasterizer* rast, Framebuffer* fb, const Vector2* v1, const Vector2* v2, const Vector2* v3); 


#endif // RASTERIZER_H
