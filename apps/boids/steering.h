//
// Created by pollini on 18/09/2021.
//

#ifndef CSDS_STEERING_H
#define CSDS_STEERING_H

#include "boid.h"

void steering_seek(boid_t* p_boid,Vector2* p_target);
void steering_flee(boid_t* p_boid,Vector2* p_target);
#endif //CSDS_STEERING_H
