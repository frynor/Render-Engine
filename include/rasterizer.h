#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "../include/vector2.h"
#include "../include/vector3.h"
#include "../include/vector4.h"
#include "../include/matrix44.h"
#include "../include/framebuffer.h"
#include <stdbool.h>
#include <stdio.h>

typedef bool (*RenderCallBack) (void* userData);

typedef struct {
	int width;
	int height;
	int currentBuffer;
	Framebuffer* frameBuffers[2];
	Framebuffer* pFrame;
	Framebuffer* rFrame;
	RenderCallBack renderCallback;
	void* userData;
	bool isRendering;
} Rasterizer;

typedef struct {
	Framebuffer* fb;
	int startY;
	int endY;
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;
} ThreadData;


// Constructor and Destructor in C, kind of..... XD
Rasterizer* rasterizer_create(int width, int height, int currentBuffer); 
void rasterizer_destroy(Rasterizer* rast);

// Framebuffer management
Framebuffer* rasterizer_get_framebuffer(const Rasterizer* rast);

// Rasterizer functions
void rasterizeTriangle(const Rasterizer* rast, const Vector2* v1, const Vector2* v2, const Vector2* v3); 
void rasterizeSquare(const Rasterizer* rast, const Vector2* v1, const Vector2* v2); 

void presentFrame(Framebuffer* pFrame);
inline void clearFrame(Framebuffer* rFrame) {
	framebuffer_clear(rFrame, 0);
}

inline void swapBuffer(Rasterizer* rast) {
	if (!rast) return;

	rast->currentBuffer = 1 - rast->currentBuffer;
	rast->pFrame = rast->frameBuffers[1 - rast->currentBuffer];
	rast->rFrame = rast->frameBuffers[rast->currentBuffer];
}

void rasterizer_set_callback(Rasterizer* rast, RenderCallBack callback, void* userData);
bool rasterizer_render_frame(Rasterizer* rast);


#endif // RASTERIZER_H
