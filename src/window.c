#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
int WindowFocused;

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

    window = glfwCreateWindow(640, 480, "Root Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowRefreshCallback(window, window_refresh_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
