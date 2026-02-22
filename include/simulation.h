#ifndef SIMULATION_H
#define SIMULATION_H

#include "types.h"
#include "world.h"

#include <stdio.h>

void simulation_init();
void main_loop(float dt);

extern Vector2 pos;

#endif
