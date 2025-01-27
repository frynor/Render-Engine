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
    curs_set(0);

    int width = 160, height = 48;  // Use standard terminal size
    Rasterizer* rasterizer = rasterizer_create(width, height);
    Framebuffer* fb = rasterizer_get_framebuffer(rasterizer);
    
    float angle = 0;
    while(true) {
        angle += 0.05f;
        Matrix44 transform = matrix44_create_default();
        Vector3 axis = {0, 0, 1};
        rotate(&transform, &axis, angle);
        
        Vector4 v1 = {-1.0f, 1.0f, 0, 1};
        Vector4 v2 = {1.0f, 1.0f, 0, 1};
        Vector4 v3 = {0.0f, -1.0f, 0, 1};
        
        v1 = matrix44_multiply_vector4(&transform, &v1);
        v2 = matrix44_multiply_vector4(&transform, &v2);
        v3 = matrix44_multiply_vector4(&transform, &v3);
        
        Vector2 screen_v1 = vector2_create(v1.x, v1.y);
        Vector2 screen_v2 = vector2_create(v2.x, v2.y);
        Vector2 screen_v3 = vector2_create(v3.x, v3.y);
        
        clearFrame(fb);
        rasterizeTriangle(rasterizer, fb, &screen_v1, &screen_v2, &screen_v3);
        presentFrame(fb, 0, 0);
        refresh();
        erase();
        napms(16);  // Add small delay
    }
}
