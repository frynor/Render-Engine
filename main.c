#include "include/matrix44.h"
#include "include/vector2.h"
#include "include/rasterizer.h"
#include "include/defs.h"
#include <time.h>

#define PI 3.141592653f

typedef struct RenderState {
	float angle;
	Matrix44 transform;
	Vector3 axis;
	Vector4 v1, v2, v3;
} RenderState;

Rasterizer* rasterizer = NULL;

bool renderCallBack(void* userData) {
	RenderState* state = (RenderState*)userData;
	if (!state || !rasterizer) return false;

	state->angle += 0.04f;
	state->transform = matrix44_create_default();
	rotate(&state->transform, &state->axis, state->angle);

	Vector4 transformed_v1 = matrix44_multiply_vector4(&state->transform, &state->v1);
    	Vector4 transformed_v2 = matrix44_multiply_vector4(&state->transform, &state->v2);
    	Vector4 transformed_v3 = matrix44_multiply_vector4(&state->transform, &state->v3);

	Vector2 screen_v1 = vector2_create(transformed_v1.x, transformed_v1.y);
    	Vector2 screen_v2 = vector2_create(transformed_v2.x, transformed_v2.y);
    	Vector2 screen_v3 = vector2_create(transformed_v3.x, transformed_v3.y);

	clearFrame(rasterizer->rFrame);
	rasterizeTriangle(rasterizer, &screen_v1, &screen_v2, &screen_v3);

	return true;
}

int main() {
    initscr();
    noecho();
    start_color();
    cbreak();
    curs_set(0);

    int width = WW, height = WH;
    rasterizer = rasterizer_create(width, height, 0);  
    if (!rasterizer) {
	    endwin();
	    fprintf(stderr, "Failed to create rasterizer\n");
	    return 1;
    }

    RenderState state = {
        .angle = 0.0f,
        .axis = {0.0f, 1.0f, 1.0f},
        .v1 = {-1.0f, 1.0f, 0.0f, 1.0f},
        .v2 = {1.0f, 1.0f, 0.0f, 1.0f},
        .v3 = {0.0f, -1.0f, 0.0f, 1.0f}
    };

    rasterizer_set_callback(rasterizer, renderCallBack, &state);

    struct timespec frameTime = {0, 16666667}; // 60FPS 
    while (true) {
        if (!rasterizer_render_frame(rasterizer)) {
            break;
        }
        
        refresh();
        erase();
        nanosleep(&frameTime, NULL); 
    }
    
    // Cleanup
    rasterizer_destroy(rasterizer);
    endwin();
    return 0;
}
