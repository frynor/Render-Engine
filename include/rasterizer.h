#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "../include/vector2.h"
#include "../include/vector3.h"
#include "../include/vector4.h"
#include "../include/matrix44.h"
#include "../include/framebuffer.h"

typedef struct {
	Framebuffer* pFrame;
	Framebuffer* rFrame;
	Framebuffer* frameBuffers[2];
	int currentBuffer;
	int width, height;
} Rasterizer;


// Constructor and Destructor in C, kind of..... XD
Rasterizer* rasterizer_create(int width, int height, int currentBuffer); 
void rasterizer_destroy(Rasterizer* rast); 

// Framebuffer management
Framebuffer* rasterizer_get_framebuffer(const Rasterizer* rast);

// Rasterizer functions
void rasterizeTriangle(const Rasterizer* rast, const Vector2* v1, const Vector2* v2, const Vector2* v3); 

void presentFrame(Framebuffer* pFrame);
inline void clearFrame(Framebuffer* rFrame) {
	framebuffer_clear(rFrame, 0);
}

inline void swapBuffer(Rasterizer* rast) {
	rast->currentBuffer ^= 1;
	rast->pFrame = rast->frameBuffers[rast->currentBuffer];
	rast->rFrame = rast->frameBuffers[rast->currentBuffer ^ 1];
}

#endif // RASTERIZER_H
