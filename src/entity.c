#include "entity.h"

uint16_t entity_count = 0;
uint16_t active_count = 0;

void init_entity_components(uint16_t id, Vector2 pos, Color4f color, uint8_t active, uint8_t hasGravity) {
    // Set Component Data
    positions[id] = pos;
    velocities[id] = (Vector2){0, 0};
    rotations[id] = 0.0f;
    colors[id] = color;

    // Set Flags
    entityFlags[id] = 0;
    if (hasGravity)
        entityFlags[id] |= FLAG_GRAVITY;
    if (active) {
        entityFlags[id] |= FLAG_ACTIVE;
        entities[id].activeId = active_count;
        activeEntities[active_count++].id = id;
    }
}


Entity* spawn_circle(Vector2 pos, float radius, uint16_t segments, Color4f color, uint8_t active, uint8_t hasGravity) {
    if (entity_count >= MAX_ENTITIES)
        return NULL;

    uint16_t id = entity_count++;
    entities[id].id = id;

    shapes[id].circle.radius = radius;
    shapes[id].circle.segments = segments;
    shapeTypes[id] = SHAPE_CIRCLE;

    init_entity_components(id, pos, color, active, hasGravity);

    // Return Pointer
    return &entities[id];
}

Entity* spawn_rectangle(Vector2 pos, float width, float height, Color4f color, uint8_t active, uint8_t hasGravity) {
    if (entity_count >= MAX_ENTITIES)
        return NULL;

    uint16_t id = entity_count++;
    entities[id].id = id;

    shapes[id].rectangle.width = width;
    shapes[id].rectangle.height = height;
    shapeTypes[id] = SHAPE_RECTANGLE;

    init_entity_components(id, pos, color, active, hasGravity);

    // Return Pointer
    return &entities[id];
}

Entity* spawn_triangle(Vector2 pos, Vector2 points[3], Color4f color, uint8_t active, uint8_t hasGravity) {
    if (entity_count >= MAX_ENTITIES)
        return NULL;

    uint16_t id = entity_count++;
    entities[id].id = id;

    for (uint8_t i = 0; i < 3; i++)
        shapes[id].triangle.points[i] = points[i];
    shapeTypes[id] = SHAPE_TRIANGLE;

    init_entity_components(id, pos, color, active, hasGravity);

    // Return Pointer
    return &entities[id];
}

// Update Active State of an Entity
void update_active(uint16_t id, uint8_t active) {
    if (active && !(entityFlags[id] & FLAG_ACTIVE)) {
        entityFlags[id] |= FLAG_ACTIVE;
        entities[id].activeId = active_count;
        activeEntities[active_count++].id = id;
    } else if (!active && (entityFlags[id] & FLAG_ACTIVE)) {
        entityFlags[id] &= ~FLAG_ACTIVE;
        uint16_t index = entities[id].activeId;
        active_count--;
        if (index != active_count) {
            activeEntities[index] = activeEntities[active_count];
            entities[activeEntities[index].id].activeId = index;
        }
    }
}

// Update Gravity State of an Entity
void update_gravity(uint16_t id, uint8_t hasGravity) {
    if (hasGravity && !(entityFlags[id] & FLAG_GRAVITY))
        entityFlags[id] |= FLAG_GRAVITY;
    else if (!hasGravity && (entityFlags[id] & FLAG_GRAVITY))
        entityFlags[id] &= ~FLAG_GRAVITY;
}

// Helper Function: Swap Entity MetaData with another Entity
void swap_entity_metaData(uint16_t entityId, uint16_t srcId) {
    entities[entityId] = entities[srcId];
    positions[entityId] = positions[srcId];
    velocities[entityId] = velocities[srcId];
    rotations[entityId] = rotations[srcId];
    colors[entityId] = colors[srcId];
    shapes[entityId] = shapes[srcId];
    shapeTypes[entityId] = shapeTypes[srcId];
    entityFlags[entityId] = entityFlags[srcId];
}

void destroy_entity(uint16_t id) {
    if (id >= entity_count)
        return;

    // Handle Actives First
    if (entityFlags[id] & FLAG_ACTIVE) {
        uint16_t index = entities[id].activeId;
        active_count--;
        if (index != active_count) {
            activeEntities[index] = activeEntities[active_count];
            entities[activeEntities[index].id].activeId = index;
        }
    }

    // Swap last entity into this slot
    uint16_t last = entity_count - 1;
    if (id != last) {
        // Swap Component Data
        swap_entity_metaData(id, last);

        // If swapped entity was active update its activeId
        if (entityFlags[id] & FLAG_ACTIVE)
            activeEntities[entities[id].activeId].id = id;
    }
    entityFlags[last] = 0;

    entity_count--;
}
