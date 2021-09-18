//
// Created by pollini on 18/09/2021.
//

#include <math.h>

#include "utils.h"



float ConstrainValue(float value, float vmin, float vmax)
{
    return fmax(fmin(value,vmax),vmin);
}

float MapValue(float value, float vmin, float vmax, float mapmin, float mapmax)
{
    float new_v = (value - vmin) / (vmax-vmin) * (mapmax-mapmin) + mapmin;
    return ConstrainValue(new_v,mapmin,mapmax);
}