//
// Created by pollini on 18/09/2021.
//

#include "steering.h"
#include "utils.h"
#include "raymath.h"

const float MAX_VELOCITY = 10.0;
const float MAX_FLEE_VELOCITY = 1.0;

void steering_seek(boid_t* p_boid,Vector2* p_target)
{
    Vector2 desired_velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(*p_target, p_boid->pos)),MAX_VELOCITY);
    Vector2 steering = Vector2Subtract(desired_velocity,p_boid->v);
    p_boid->v.x += steering.x;
    p_boid->v.y += steering.y;
    p_boid->v.x = ConstrainValue(p_boid->v.x,-MAX_VELOCITY,MAX_VELOCITY);
    p_boid->v.y = ConstrainValue(p_boid->v.y,-MAX_VELOCITY,MAX_VELOCITY);
}

void steering_flee(boid_t* p_boid,Vector2* p_target)
{
    Vector2 desired_velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(p_boid->pos,*p_target )),MAX_FLEE_VELOCITY);
    Vector2 steering = Vector2Subtract(desired_velocity,p_boid->v);
    p_boid->v.x += steering.x;
    p_boid->v.y += steering.y;
    p_boid->v.x = ConstrainValue(p_boid->v.x,-MAX_FLEE_VELOCITY,MAX_FLEE_VELOCITY);
    p_boid->v.y = ConstrainValue(p_boid->v.y,-MAX_FLEE_VELOCITY,MAX_FLEE_VELOCITY);
}