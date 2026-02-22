#include "input.h"

#define MAX_KEYS (GLFW_KEY_LAST + 1)

static uint16_t keys_prev[MAX_KEYS];
static uint16_t keys_curr[MAX_KEYS];

void input_init() {
    for (uint16_t i = 0; i < MAX_KEYS; i++) {
        keys_prev[i] = 0;
        keys_curr[i] = 0;
    }
}

void input_update() {
    for (uint16_t i = 0; i < MAX_KEYS; i++)
        keys_prev[i] = keys_curr[i];

    for (uint16_t i = 0; i < MAX_KEYS; i++)
        keys_curr[i] = glfwGetKey(window, i) == GLFW_PRESS;
}

uint8_t getKey(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS ? 1 : 0;
}

uint8_t getKeyDown(int key) {
    if (key < 0 || key >= MAX_KEYS)
        return 0;
    return keys_curr[key] && !keys_prev[key];
}

uint8_t getKeyUp(int key) {
    if (key < 0 || key >= MAX_KEYS)
        return 0;
    return !keys_curr[key] && keys_prev[key];
}
