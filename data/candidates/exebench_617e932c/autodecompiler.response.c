void parabolic_interpolation(float left, float middle, float right,
                 int bin, float *amp, int *newbin)
{
    float delta_x;

    delta_x = ((left - right) / (left - 2 * middle + right)) / 2.0;
    *newbin = bin + (int)delta_x;
    *amp = middle + fabs((left - right) / 4.0) * delta_x;
}