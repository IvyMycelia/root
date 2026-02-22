#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <GLFW/glfw3.h>

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

typedef struct Circle {
    Vector2 pos;
    float radius;
    uint16_t segments;
} Circle;

typedef uint8_t Shape;
enum
{
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,
    SHAPE_TRIANGLE,
};

typedef struct Entity Entity;
typedef void (*PhysicsUpdater)(Entity *);

typedef struct Entity
{
    Shape shape;
    Vector2 position;
    Vector2 velocity;
} Entity;

extern float Gravity;
extern uint16_t width;
extern uint16_t height;

extern GLFWwindow *window;

#endif
