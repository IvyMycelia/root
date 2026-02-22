#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <GLFW/glfw3.h>

#define MAX_ENTITIES 1024

// 2D Values for position, velocity, etc
typedef struct Vector2 {
    float x;
    float y;
} Vector2;


// RGBA color
typedef struct Color4f {
    float r; // Red
    float g; // Green
    float b; // Blue
    float a; // Alpha
} Color4f;

typedef struct {
    float radius;       // Size of the circle
    uint16_t segments;  // How smooth it will look
} CircleData;

typedef struct {
    float width, height;
} RectangleData;

typedef struct {
    Vector2 points[3];
} TriangleData;


/*
    Shape Components
*/
#define SHAPE_CIRCLE    0
#define SHAPE_RECTANGLE 0
#define SHAPE_TRIANGLE  0

typedef union {
    CircleData circle;
    RectangleData rectangle;
    TriangleData triangle;
} ShapeData;    // Type of shape
ShapeData shapes[MAX_ENTITIES];


uint8_t shapeTypes[MAX_ENTITIES];    // An entity's shape type

/*
    Component Caches
*/
Vector2 positions[MAX_ENTITIES];    // Position of an entity
Vector2 velocities[MAX_ENTITIES];   // Velocity of an entity

float rotations[MAX_ENTITIES];      // The rotation of an entity [Not Implemented]
Color4f colors[MAX_ENTITIES];       // The color of an entity

#define FLAG_ACTIVE     0x01        // Whether or not an entity should be rendered / updated
#define FLAG_GRAVITY    0x02        // Whether or not an entity's velocity will be updated by global Gravity
#define FLAG_COLLIDED   0x04        // Whether or not an entity is overlapping another entity
#define FLAG_FOURTH     0x08
#define FLAG_FIFTH      0x10
#define FLAG_SIXTH      0x20
#define FLAG_SEVENTH    0x40
#define FLAG_EIGHT      0x80

uint8_t entityFlags[MAX_ENTITIES];  // Bit Flags of an entity, e.g: Active, hasGravity, etc.

// Entity MetaData
typedef struct Entity
{
    uint16_t id;        // ID of entity
    uint16_t activeId;  // Lookup ID for quick destruction O(1)
} Entity;

Entity activeEntities[MAX_ENTITIES];    //Array of all active entities ONLY

#endif
