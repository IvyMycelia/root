#include "types.h"
#include "draw.h"
#include "simulation.h"
#include "input.h"

float Gravity = -980.665;

static uint8_t initialized = 0;
static uint8_t paused = 0;

void simulation_init() {
    spawn_circle((Vector2){640 / 2, 300}, 25.0f, 100, (Color4f){1.0f, 0.0f, 0.0f, 1.0f}, 1, 1);
    spawn_circle((Vector2){400, 300}, 10.0f, 50, (Color4f){0.0f, 1.0f, 0.0f, 1.0f}, 1, 1);
}

void main_loop(float dt) {
    if (!initialized) {
        simulation_init();
        initialized = 1;
    }

    if (getKeyDown(GLFW_KEY_SPACE)) {
        paused = !paused;
        printf(paused ? "Paused\n" : "Unpasued\n");
    }

    /*
        Update Physics
    */
    float physics_dt = 0.016f; // ~60hz
    static float accumulator = 0.0f;
    uint8_t steps = 0;
    accumulator += dt;
    while (accumulator >= physics_dt && steps < 5 && !paused) {
        // Update physics ONCE per timestamp
        for (uint16_t id = 0; id < entity_count; id++)
        {
            Entity *e = &entities[id];
            velocities[id].y += Gravity * physics_dt;
            positions[id].y += velocities[id].y * physics_dt;

            if (positions[id].y < 0) {
                positions[id].y = 0;
                velocities[id].y *= -0.8f;
            }

            if (positions[id].y > height) {
                positions[id].y = height;
                velocities[id].y *= -0.8f;
            }

            if (positions[id].x < 0) {
                positions[id].x = 0;
                velocities[id].x *= -0.8f;
            }

            if (positions[id].x > width) {
                positions[id].x = width;
                velocities[id].x *= -0.8f;
            }

                // printf("Entity: %d — Position Y: %f\n", e->id, e->position.y);
        }
        accumulator -= physics_dt;
        steps++;
    }

    /*
        Render Entities
    */
    for (uint16_t id = 0; id < entity_count; id++) {
        Entity *e = &entities[id];

        if (shapeTypes[id] == SHAPE_CIRCLE) {
            // Circle c;
            // c.pos = e->position;
            // c.radius = 25.0f;
            // c.segments = 50;
            // circle_test(c);
        }
    }
}
