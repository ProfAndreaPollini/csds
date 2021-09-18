//
// Created by pollini on 15/09/2021.
//

#ifndef BOIDS_BOID_H
#define BOIDS_BOID_H

#include "raylib.h"


__attribute__((unused)) typedef struct boid {
    Vector2 pos;
    Vector2 v;
    Vector2 a;
} boid_t;

void boid_update(boid_t* p_boid);
void boid_draw(boid_t* p_boid);
void boid_check_screen_bounds(boid_t* p_boid,int width, int height);
#endif //BOIDS_BOID_H
