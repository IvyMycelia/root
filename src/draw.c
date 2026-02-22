#include <GLFW/glfw3.h>

#include "draw.h"

#include <math.h>

// void circle_test(Circle c) {
//     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//     glBegin(GL_TRIANGLE_FAN);
//     glVertex2f(c.pos.x, c.pos.y);

//     for (int i = 0; i <= c.segments; i++)
//     {
//         float theta = 2.0f * M_PI * i / c.segments;
//         float x = c.pos.x + cos(theta) * c.radius;
//         float y = c.pos.y + sin(theta) * c.radius;
//         glVertex2f(x, y);
//     }
//     glEnd();
// }
