#include "include/matrix44.h"
#include "include/vector2.h"
#include "include/rasterizer.h"
#include <math.h>
#include <ncurses.h>
#include <stdio.h>

#define PI 3.141592653f

int main() {
	initscr();
	noecho();
	start_color();
	cbreak();

	int width = 1920, height = 1080;

	Rasterizer* rasterizer = rasterizer_create(width, height);
	if (!rasterizer) {
		fprintf(stderr, "Failed to create rasterizer\n");
		return 1;
	}
	Framebuffer* fb = rasterizer_get_framebuffer(rasterizer);
	if (!fb) {
		fprintf(stderr, "Failed to create framebuffer");
	}

	float angle = 0;
	while(true) {
	    angle += 0.002f;  // Rotation speed

	    // Define triangle vertices in model space
	    Vector4 v1 = {-0.5f, 0.5f, 0, 1};  // Top-left
	    Vector4 v2 = {0.5f, 0.5f, 0, 1};   // Top-right
	    Vector4 v3 = {0.0f, -0.5f, 0, 1};  // Bottom-center

	    // Create transformation matrices
	    Matrix44 model = matrix44_create_default();
	    Matrix44 view = matrix44_create_default();
	    Matrix44 projection = matrix44_create_default();

	    // Apply rotation
	    Vector3 rotation_axis = {0, 0, 1};  // Rotate around Z-axis
	    rotate(&model, &rotation_axis, angle);

	    // Apply scaling (if needed)
	    Vector3 scale_vector = {0.8f, 0.8f, 1.0f};  // Scale down to fit terminal
	    scale(&model, &scale_vector);

	    // Apply translation to center the triangle
	    Vector3 translation_vector = {0.0f, 0.0f, 0.0f};
	    translate(&view, &translation_vector);

	    // Combine transformations into a single matrix
	    Matrix44 mvp = matrix44_create_default();
	    matrix44_mul(&projection, &view, &mvp);
	    matrix44_mul(&mvp, &model, &mvp);

	    // Transform vertices
	    v1 = matrix44_multiply_vector4(&mvp, &v1);
	    v2 = matrix44_multiply_vector4(&mvp, &v2);
	    v3 = matrix44_multiply_vector4(&mvp, &v3);

	    // Perspective divide (convert to NDC)
	    v1.x /= v1.w; v1.y /= v1.w;
	    v2.x /= v2.w; v2.y /= v2.w;
	    v3.x /= v3.w; v3.y /= v3.w;

	    // Convert to screen space
	    Vector2 screen_v1 = vector2_create(-0.5f, 0.5f);
	    Vector2 screen_v2 = vector2_create(0.5f, 0.5f);
	    Vector2 screen_v3 = vector2_create(0.0f, -0.5f);

	    // Clear, rasterize, and display
	    clearFrame(fb);
	    rasterizeTriangle(rasterizer, fb, &screen_v1, &screen_v2, &screen_v3);
	    presentFrame(fb, 0, 0);

	    refresh();
	    erase();
	
	}
	/* float angle = 0;
	while (angle < 180) {
		Matrix44 transformation = matrix44_create_default(); 
		Vector3 v4 = {0, 0, 1};
		
		rotate(&transformation, &v4, (angle * M_PI / 180.0));

		Vector4 v1 = {-1, 1, 0, 1};
		Vector4 v2 = {1, 1, 0, 1};
		Vector4 v3 = {0, -1, 1, 1};

		v1 = matrix44_multiply_vector4(&transformation, &v1);
		v2 = matrix44_multiply_vector4(&transformation, &v2);
		v3 = matrix44_multiply_vector4(&transformation, &v3);
		
		Vector2 tv1 = vector2_create(v1.x, v1.y);
		Vector2 tv2 = vector2_create(v2.x, v2.y);
		Vector2 tv3 = vector2_create(v3.x, v3.y);

		clearFrame(fb);
		rasterizeTriangle(rasterizer, fb, &tv1, &tv2, &tv3);
		presentFrame(fb, 0, 0);
		getch();
		clear();
		angle += 20;
		
	} */

	refresh();

	getch();

	// rasterizer_destroy(rasterizer);
	endwin();

	return 0;
}
