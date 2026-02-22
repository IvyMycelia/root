#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>

#include "types.h"
#include "globals.h"

extern Entity entities[MAX_ENTITIES];
extern u_int16_t entity_count;

void init_entity_components(uint16_t id, Vector2 pos, Color4f color, uint8_t active, uint8_t hasGravity);
Entity *spawn_circle(Vector2 pos, float radius, uint16_t segments, Color4f color, uint8_t active, uint8_t hasGravity);
Entity *spawn_rectangle(Vector2 pos, float width, float height, Color4f color, uint8_t active, uint8_t hasGravity);
Entity *spawn_triangle(Vector2 pos, Vector2 points[3], Color4f color, uint8_t active, uint8_t hasGravity);
void update_active(uint16_t id, uint8_t active);
void update_gravity(uint16_t id, uint8_t hasGravity);
void destroy_entity(uint16_t id);

#endif
