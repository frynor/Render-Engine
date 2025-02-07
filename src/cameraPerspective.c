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
	cam->fov = 0.0f;
	cam->zFar = 0.0f;
	cam->zNear = 0.0f;
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
    // Reset viewMatrix to identity
    matrix44_identity(&camera->viewMatrix);
    
    Vector3 negPos = { -camera->position.x, -camera->position.y, -camera->position.z };
    translate(&camera->viewMatrix, &negPos);
    
    rotate(&camera->viewMatrix, &((Vector3){0.0f, 0.0f, 1.0f}), -camera->rotation.z);
    rotate(&camera->viewMatrix, &((Vector3){0.0f, 1.0f, 0.0f}), -camera->rotation.y);
    rotate(&camera->viewMatrix, &((Vector3){1.0f, 0.0f, 0.0f}), -camera->rotation.x);
}


Matrix44 camera_get_pv_matrix(const Camera *camera) {
	Matrix44 dest;
       	matrix44_mul(&camera->projMatrix, &camera->viewMatrix, &dest);
	return dest;	
}

void camera_create_projection(Camera *camera, float fov, float aspect, float zNear, float zFar) {
	camera->fov = fov;
	camera->aspect = aspect;
	camera->zNear = zNear;
	camera->zFar = zFar;

	matrix44_identity(&camera->projMatrix);
	float tanhfov = (float)tanf(camera->fov / 2.0f);

	camera->projMatrix.m00 = 1.0f / (camera->aspect * tanhfov);
	camera->projMatrix.m11 = 1.0f / tanhfov;
	camera->projMatrix.m22 = -(camera->zNear + camera->zFar) / (camera->zFar - camera->zNear);
	camera->projMatrix.m23 = -1.0f;
	camera->projMatrix.m32 = -(2.0f * camera->zFar * camera->zNear) / (camera->zFar - camera->zNear);
	camera->projMatrix.m33 = 1.0f;
}
