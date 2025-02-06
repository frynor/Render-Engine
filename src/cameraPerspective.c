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
	matrix44_identity(&camera->viewMatrix);
	
	Matrix44 rotX, rotY, rotZ;
	matrix44_identity(&rotX);
	matrix44_identity(&rotY);
	matrix44_identity(&rotZ);


	rotate(&rotX, &((Vector3){1.0f, 0.0f, 0.0f}), camera->rotation.x);
	rotate(&rotY, &((Vector3){0.0f, 1.0f, 0.0f}), camera->rotation.y);
	rotate(&rotZ, &((Vector3){0.0f, 0.0f, 1.0f}), camera->rotation.z);

	// Combine rotations
    	Matrix44 combinedRotation;
    	matrix44_mul(&rotZ, &rotY, &combinedRotation);
    	matrix44_mul(&combinedRotation, &rotX, &camera->viewMatrix);

	Vector3 inversePosition = {-camera->position.x, -camera->position.y, -camera->position.z};
	translate(&camera->viewMatrix, &inversePosition);
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
	camera->projMatrix.m33 = 0.0f;
}
