#include "../include/cameraPerspective.h"
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

void camera_calculate_view_matrix(Camera *camera) {
	matrix44_identity(&camera->viewMatrix);
	rotate(&camera->viewMatrix, &((Vector3){1.0f, 0.0f, 0.0f}), camera->rotation.x);
	rotate(&camera->viewMatrix, &((Vector3){0.0f, 1.0f, 0.0f}), camera->rotation.y);
	rotate(&camera->viewMatrix, &((Vector3){.0f, 0.0f, 1.0f}), camera->rotation.z);
	translate(&camera->viewMatrix, &camera->position);
}
