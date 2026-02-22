#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "types.h"
#include "globals.h"

void input_update(void);
void input_init(void);

uint8_t getKey(int key);
uint8_t getKeyDown(int key);
uint8_t getKeyUp(int key);

#endif
