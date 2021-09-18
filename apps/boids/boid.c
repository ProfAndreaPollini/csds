//
// Created by pollini on 15/09/2021.
//

#include "boid.h"
#include "raylib.h"
#include "raymath.h"

#include "utils.h"

const float VMAX = 4.0;

void boid_update(boid_t *p_boid) {
    p_boid->v = Vector2Add(p_boid->a,p_boid->v);
    p_boid->v.x = ConstrainValue(p_boid->v.x,-VMAX,VMAX);
    p_boid->v.y = ConstrainValue(p_boid->v.y,-VMAX,VMAX);
    p_boid->pos = Vector2Add(p_boid->pos,p_boid->v);
}

void boid_draw(boid_t *p_boid) {
    Vector2 base_dir = Vector2Normalize(Vector2Rotate(p_boid->v,90));
    Vector2 v1 = Vector2Add(p_boid->pos, Vector2Scale(base_dir,5));
    Vector2 v2 = Vector2Add(p_boid->pos, Vector2Scale(Vector2Rotate(base_dir,180),5));
    Vector2 v3 = Vector2Add(p_boid->pos,Vector2Scale(Vector2Normalize(p_boid->v),15));

    DrawTriangle(v1,v3,v2,RED);
}

void boid_check_screen_bounds(boid_t* p_boid,int width, int height)
{
    if (p_boid->pos.x < 0) p_boid->pos.x = width-1;
    if (p_boid->pos.y < 0) p_boid->pos.y = height-1;
    if (p_boid->pos.x > width) p_boid->pos.x = 0;
    if (p_boid->pos.y > height) p_boid->pos.y = 0;


}
