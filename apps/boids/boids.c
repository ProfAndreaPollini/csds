//
// Created by pollini on 16/09/2021.
//

#include <stdlib.h>

#include "boids.h"

#include "list.h"

#include "raymath.h"

csds_list_t* boids = NULL;//csds_list_create(sizeof(boid_t));

void boids_init()
{
    boids = csds_list_create(sizeof(boid_t));
}

void boids_add(Vector2 pos)
{
    boid_t* new_boid = malloc(sizeof(boid_t));
    csds_list_item_t* el = csds_list_append(boids);
    new_boid->pos = (Vector2){
            .x = GetRandomValue(50,200),
            .y = GetRandomValue(50,200)
    };
    new_boid->v = Vector2Rotate(Vector2Normalize(Vector2One()), GetRandomValue(0,359));
    el->data = new_boid;
}

int boids_count()
{
    return boids->size;
}

boid_t* boids_get(int pos)
{
    csds_list_item_t*current = boids->p_head;

    while(current != NULL) {
        if (--pos <0) {
            return (boid_t*)current->data;
        }
        current = current->p_next;
    }
}

void boids_remove() {
    csds_free_list_remove_last(boids);
}