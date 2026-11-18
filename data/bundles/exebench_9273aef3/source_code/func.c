#include <math.h>

void mult_xps_vec(float v[4], const float M[16], const float u[4])
{
    v[0] = M[0] * u[0] + M[1] * u[1] + M[2] * u[2] + M[3] * u[3];
    v[1] = M[4] * u[0] + M[5] * u[1] + M[6] * u[2] + M[7] * u[3];
    v[2] = M[8] * u[0] + M[9] * u[1] + M[10] * u[2] + M[11] * u[3];
    v[3] = M[12] * u[0] + M[13] * u[1] + M[14] * u[2] + M[15] * u[3];
}
