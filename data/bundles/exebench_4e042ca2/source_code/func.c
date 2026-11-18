#include <string.h>

#include <math.h>

void mat4f_LoadScale(float* s, float* m)
{
 m[0] = s[0];
 m[1] = 0.0f;
 m[2] = 0.0f;
 m[3] = 0.0f;

 m[4] = 0.0f;
 m[5] = s[1];
 m[6] = 0.0f;
 m[7] = 0.0f;

 m[8] = 0.0f;
 m[9] = 0.0f;
 m[10] = s[2];
 m[11] = 0.0f;

 m[12] = 0.0f;
 m[13] = 0.0f;
 m[14] = 0.0f;
 m[15] = 1.0f;
}
