#include <emscripten.h>
#include <stdint.h>

#define WIDTH 360
#define HEIGHT 640

uint32_t frame_buffer[WIDTH * HEIGHT];

EMSCRIPTEN_KEEPALIVE
uint32_t* get_frame_buffer() { return frame_buffer; }

EMSCRIPTEN_KEEPALIVE
void init_screen() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        frame_buffer[i] = 0xFF1E1E1E; // 背景色（ダークグレー）
    }
}

EMSCRIPTEN_KEEPALIVE
void touch_event(int x, int y) {
    int radius = 12;
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            int px = x + dx, py = y + dy;
            if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                if (dx * dx + dy * dy <= radius * radius) {
                    frame_buffer[py * WIDTH + px] = 0xFF00FF88; // タッチ位置を緑色に
                }
            }
        }
    }
}
