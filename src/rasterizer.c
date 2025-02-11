#include "../include/defs.h"
#include "../include/rasterizer.h"
#include <threads.h>

#define MAX(a, b) (((a)>(b))? (a) : (b))
#define MIN(a, b) (((a)<(b))? (a) : (b))

static bool isPointTriangle(int ptx, int pty, const Vector2* v1, const Vector2* v2, const Vector2* v3) {
    const float EPSILON = 1e-4f;
    float denominator = ((v2->y - v3->y) * (v1->x - v3->x) + (v3->x - v2->x) * (v1->y - v3->y));
    if (fabs(denominator) < 1e-6) return false; // Avoiding division by zero.
    
    float alpha = ((v2->y - v3->y) * (ptx - v3->x) + (v3->x - v2->x) * (pty - v3->y)) / denominator;
    float beta = ((v3->y - v1->y) * (ptx - v3->x) + (v1->x - v3->x) * (pty - v3->y)) / denominator;
    float gamma = 1.0f - alpha - beta;
    
    return (alpha >= -EPSILON) && (beta >= -EPSILON) && (gamma >= -EPSILON) && 
           (alpha <= 1.0f + EPSILON) && (beta <= 1.0f + EPSILON) && (gamma <= 1.0f + EPSILON);
}

static void rasterizer_initialize_framebuffer(Rasterizer* rast, int width, int height, int currentBuffer) {
	if (!rast) return;
	rast->frameBuffers[0] = framebuffer_create(width, height);
	rast->frameBuffers[1] = framebuffer_create(width, height);

	swapBuffer(rast);
}

void rasterizer_set_callback(Rasterizer* rast, RenderCallBack callback, void* userData) {
	if (!rast) return;
	rast->renderCallback = callback;
	rast->userData = userData;
}

bool rasterizer_render_frame(Rasterizer* rast) {
	if (!rast || !rast->renderCallback || rast->isRendering) return false;

	rast->isRendering = true;

	bool success = rast->renderCallback(rast->userData);

	if (success) {
		swapBuffer(rast);
		presentFrame(rast->pFrame);
	}

	rast->isRendering = false;
	return success;
}


Rasterizer* rasterizer_create(int width, int height, int currentBuffer) {
	// Allocating the memory (heap memory (cool stuff bro, check heap vs stack (XD)))
	Rasterizer* rast = (Rasterizer*)malloc(sizeof(Rasterizer));
	if (!rast) {
		fprintf(stderr, "Memory allocation failed for Rasterizer\n");
		return NULL;
	} 

	rast->width = width;
	rast->height = height;
	rast->currentBuffer = 0;


	rasterizer_initialize_framebuffer(rast, width, height, currentBuffer);
	if (!rast->pFrame || !rast->rFrame) {
		fprintf(stderr, "Failed to initialize framebuffer for Rasterizer\n");
		free(rast);
		return NULL;
	}

	return rast;
}

void rasterizer_destroy(Rasterizer* rast) {
	// Freeing up the memory
	if (rast) {
		if (rast->frameBuffers[0]) framebuffer_destroy(rast->frameBuffers[0]);
		if (rast->frameBuffers[1]) framebuffer_destroy(rast->frameBuffers[1]);
		free(rast);
	}

}

Framebuffer* rasterizer_get_framebuffer(const Rasterizer* rast) {
	return rast ? rast->pFrame : NULL; 
}

void rasterizeTriangle(const Rasterizer* rast, const Vector2* vv1, const Vector2* vv2, const Vector2* vv3) {
	if (!rast || !vv1 || !vv2 || !vv3) return;

	Framebuffer* fb = rast->rFrame;

	int h_width = fb->width/2;
	int h_height = fb->height/2;
	int minx, maxx;
	int miny, maxy;

	Vector2 v1 = {vv1->x * h_width + h_width, -vv1->y * h_height + h_height};
	Vector2 v2 = {vv2->x * h_width + h_width, -vv2->y * h_height + h_height};
	Vector2 v3 = {vv3->x * h_width + h_width, -vv3->y * h_height + h_height};
	
    	minx = MAX(0, MIN(v1.x, MIN(v2.x, v3.x)));
    	miny = MAX(0, MIN(v1.y, MIN(v2.y, v3.y)));
    	maxx = MIN(framebuffer_get_width(fb), ceil(MAX(v1.x, MAX(v2.x, v3.x)) + 1));
    	maxy = MIN(framebuffer_get_height(fb), ceil(MAX(v1.y, MAX(v2.y, v3.y)) + 1));

	for (int j = miny; j < maxy; j++) {
		for (int i = minx; i < maxx; i++) {
			if(isPointTriangle(i, j, &v1, &v2, &v3)) {
				framebuffer_set_pixel(fb, i, j, '#', 0);
			} else {
				framebuffer_set_pixel(fb, i, j, ' ', 0);
			}
		}
	} 
}

void rasterizeSquare(const Rasterizer* rast, const Vector2* v1, const Vector2* v2) {
	if (!rast || !v1 || !v2) return;

	Framebuffer* fb = rast->rFrame;

	int x1 = MAX(0, v1->x);
	int y1 = MAX(0, v1->y);
	int x2 = MIN(framebuffer_get_width(fb), v2->x);
	int y2 = MIN(framebuffer_get_height(fb), v2->y);

	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			framebuffer_set_pixel(fb, x, y, '#', 0);
		}
	}
}


void presentFrame(Framebuffer *fb) {
    framebuffer_print(fb);
}
