//
// Created by pollini on 16/09/2021.
//

#ifndef CSDS_BOIDS_H
#define CSDS_BOIDS_H

#include "list.h"

#include "boid.h"

void boids_init();
void boids_add(Vector2 pos);
int boids_count();
boid_t* boids_get(int pos);
void boids_remove();

#endif //CSDS_BOIDS_H
