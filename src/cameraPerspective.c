#include "../include/cameraPerspective.h"
#include <math.h>
#include <stdlib.h>

Camera* camera_initialize() {
	Camera* cam = (Camera*)malloc(sizeof(Camera));
	if (!cam) {
		return NULL;
	}
	cam->position = (Vector3){0.0f, 0.0f, 0.0f};
	cam->rotation = (Vector3){0.0f, 0.0f, 0.0f};
	matrix44_identity(&cam->viewMatrix);
	matrix44_identity(&cam->projMatrix);

	return cam;
}

void camera_destroy(Camera* camera) {
	if (!camera) {
		return;
	} else {
		free(camera);
	}
}

void camera_calculate_view_matrix(Camera *camera) {
	matrix44_identity(&camera->viewMatrix);
	rotate(&camera->viewMatrix, &((Vector3){1.0f, 0.0f, 0.0f}), camera->rotation.x);
	rotate(&camera->viewMatrix, &((Vector3){0.0f, 1.0f, 0.0f}), camera->rotation.y);
	rotate(&camera->viewMatrix, &((Vector3){0.0f, 0.0f, 1.0f}), camera->rotation.z);
	translate(&camera->viewMatrix, &camera->position);
}

Matrix44 camera_get_pv_matrix(const Camera *camera) {
	Matrix44 dest;
       	matrix44_mul(&camera->projMatrix, &camera->viewMatrix, &dest);
	return dest;	
}

void camera_create_projection(Camera *camera, float fov, float aspect, float zNear, float zFar) {
	matrix44_identity(&camera->projMatrix);
	float tanhfov = (float)tanf(camera->fov / 2);

	camera->projMatrix.m00 = 1 / (camera->aspect * tanhfov);
	camera->projMatrix.m11 = 1 / tanhfov;
	camera->projMatrix.m22 = -(camera->zNear + camera->zFar) / (camera->zFar - camera->zNear);
	camera->projMatrix.m23 = -1;
	camera->projMatrix.m32 = -(2 * camera->zFar * camera->zNear) / (camera->zFar - camera->zNear);
}
