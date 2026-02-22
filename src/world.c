#include "world.h"

Entity entities[MAX_ENTITIES];
u_int16_t entity_count = 0;

Entity* spawn_circle(Vector2 pos, float radius, int segments) {
    Entity *e = &entities[entity_count++];
    e->position = pos;
    e->velocity = (Vector2){0, 0};
    e->shape = SHAPE_CIRCLE;
    return e;
}
