#ifndef WORLD_H
#define WORLD_H

#include "types.h"
#include <stdio.h>

#define MAX_ENTITIES 1024

extern Entity entities[MAX_ENTITIES];
extern u_int16_t entity_count;

Entity *spawn_circle(Vector2 pos, float radius, int segments);

#endif
