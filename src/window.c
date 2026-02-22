#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "simulation.h"
#include "input.h"

#define GL_SILENCE_DEPRECATION

Vector2 pos;

uint16_t width;
uint16_t height;

uint8_t WindowFocused;

GLFWwindow *window;
// GLFWimage icon;

void window_close_callback() {
    /*
        Save to file, do other things before exiting..
    */
    printf("Closing window after saving..");
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void window_refresh_callback(GLFWwindow* window) {
    /*
        Repair window..
    */
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void window_focus_callback(GLFWwindow* window, int focused) {
    /*
        Do something when focused / unfocused
    */
    WindowFocused = focused;
    printf("Window: %s\n", WindowFocused ? "Focused" : "Unfocused");
}

int window_init(void) {
    if (!glfwInit())
        return -1;

    int w_width = 640;
    int w_height = 480;
    width = (uint16_t)w_width;
    height = (uint16_t)w_height;


    window = glfwCreateWindow(width, height, "Root Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &w_width, &w_height);
    glViewport(0, 0, 640, 480);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowRefreshCallback(window, window_refresh_callback);

    pos = (Vector2){640 / 2, 480 / 2};

    double last_time = glfwGetTime();
    double fps_timer = 0.0f;
    int frames = 0;

    input_init();

    while (!glfwWindowShouldClose(window))
    {
        double current_time = glfwGetTime();
        double dt = current_time - last_time;
        last_time = current_time;

        frames++;
        fps_timer += dt;

        if (fps_timer >= 0.5f) {
            char title[256];
            snprintf(title, sizeof(title), "Root Engine — FPS: %.2f", frames / fps_timer);
            glfwSetWindowTitle(window, title);
            frames = 0;
            fps_timer = 0.0f;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        input_update();
        main_loop(dt);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
