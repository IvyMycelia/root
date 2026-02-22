#include "types.h"
#include "draw.h"
#include "simulation.h"
#include "input.h"

float Gravity = -980.665;

static uint8_t initialized = 0;
static uint8_t paused = 0;

void simulation_init() {
    spawn_circle((Vector2){640 / 2, 300}, 25.0f, 100);
    spawn_circle((Vector2){400, 300}, 10.0f, 50);
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
        for (uint16_t i = 0; i < entity_count; i++)
        {
            Entity *e = &entities[i];
            e->velocity.y += Gravity * physics_dt;
            e->position.y += e->velocity.y * physics_dt;

            if (e->position.y < 0) {
                e->position.y = 0;
                e->velocity.y *= -0.8f;
            }

            if (e->position.y > height) {
                e->position.y = height;
                e->velocity.y *= -0.8f;
            }

            if (e->position.x < 0) {
                e->position.x = 0;
                e->velocity.x *= -0.8f;
            }

            if (e->position.x > width) {
                e->position.x = width;
                e->velocity.x *= -0.8f;
            }

                // printf("Entity: %d — Position Y: %f\n", e->id, e->position.y);
        }
        accumulator -= physics_dt;
        steps++;
    }

    /*
        Render Entities
    */
    for (uint16_t i = 0; i < entity_count; i++) {
        Entity *e = &entities[i];

        if (e->shape == SHAPE_CIRCLE) {
            Circle c;
            c.pos = e->position;
            c.radius = 25.0f;
            c.segments = 50;
            circle_test(c);
        }
    }
}
