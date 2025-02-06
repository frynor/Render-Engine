#include "include/matrix44.h"
#include "include/vector2.h"
#include "include/rasterizer.h"
#include "include/defs.h"
#include "include/cameraPerspective.h"
#include <time.h>


#define PI 3.141592653f

typedef struct RenderState {
	float angle;
	Matrix44 transform;
	Vector3 axis;
	Vector4 v1, v2, v3;
} RenderState;

Rasterizer* rasterizer = NULL;
Camera* camera = NULL;

bool renderCallBack(void* userData) {
	RenderState* state = (RenderState*)userData;
	if (!state || !rasterizer) return false;

	state->angle += 0.01f;
	state->transform = matrix44_create_default();
	translate(&state->transform, &(Vector3){0.0f, 0.0f, -1.0f});
	rotate(&state->transform, &(Vector3){0.0f, 1.0f, 0.0f}, state->angle);

	camera_calculate_view_matrix(camera);
	Matrix44 PV = camera_get_pv_matrix(camera);
	Matrix44 MPV;
	matrix44_mul(&PV, &state->transform, &MPV);

	// Transforming vertices with MPV and perspective divide
	Vector4 transformed_v1 = matrix44_multiply_vector4(&MPV, &state->v1);
    	Vector4 transformed_v2 = matrix44_multiply_vector4(&MPV, &state->v2);
    	Vector4 transformed_v3 = matrix44_multiply_vector4(&MPV, &state->v3);

	// Perspective Divide
	if (transformed_v1.w != 0.0f) {
		transformed_v1.x /= transformed_v1.w;
		transformed_v1.y /= transformed_v1.w;
	}
	if (transformed_v2.w != 0.0f) {
        	transformed_v2.x /= transformed_v2.w;
        	transformed_v2.y /= transformed_v2.w;
    	}
    	if (transformed_v3.w != 0.0f) {
        	transformed_v3.x /= transformed_v3.w;
        	transformed_v3.y /= transformed_v3.w;
    	}


	// Passing NDC coordinates to rasterizer
	Vector2 screen_v1 = vector2_create(transformed_v1.x, transformed_v1.y);
    	Vector2 screen_v2 = vector2_create(transformed_v2.x, transformed_v2.y);
    	Vector2 screen_v3 = vector2_create(transformed_v3.x, transformed_v3.y);

	clearFrame(rasterizer->rFrame);
	rasterizeTriangle(rasterizer, &screen_v1, &screen_v2, &screen_v3);

	return true;
}

Vector4 transformVertex(const Matrix44* MVPMatrix, const Vector4* vertex) {
	Vector4 f;

	f = matrix44_multiply_vector4(MVPMatrix, vertex);
	f.x /= f.w;
	f.y /= f.w;
	f.z /= f.w;

	return f;
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

    camera = camera_initialize();
    camera->position = (Vector3){0.0f, 10.0f, 150.0f}; 
    camera_create_projection(camera, 1.6f, (WW / (float)2.0f) / WH, 0.5f, 400.0f);

    RenderState state = {
        .angle = 0.0f,
        .axis = {0.0f, 1.0f, 0.0f},
        .v1 = {-1.0f, 1.0f, 2.0f, 1.0f},
        .v2 = {1.0f, 1.0f, 2.0f, 1.0f},
        .v3 = {0.0f, -1.0f, 2.0f, 1.0f}
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
    camera_destroy(camera);
    endwin();
    return 0;
}
