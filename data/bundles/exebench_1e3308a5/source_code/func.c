#include <math.h>

#include <stdint.h>

#include <float.h>

#include <fenv.h>

static inline void neg_s(const float* source, float* target)
{
    *target = - *source;
}
