#include <math.h>

#include <float.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <stdio.h>

static void
parabolic_interpolation(float left_val, float middle_val, float right_val,
                        int current_bin, float *result_val, int *result_bin)
{
  float delta_x = 0.5 * ((left_val - right_val) / (left_val - 2.f * middle_val + right_val));
  *result_bin = current_bin + (int)delta_x;
  *result_val = middle_val - 0.25 * (left_val - right_val) * delta_x;
}
