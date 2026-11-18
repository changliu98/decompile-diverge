void parabolic_interpolation(
    float x_left,
    float x_middle,
    float x_right,
    int bin_left,
    float *result_val,
    int *result_bin
)
{
    float delta_x;
    int bin_offset;

    delta_x = (x_left - x_right) / (x_left - (2.0 * x_middle) + x_right);
    bin_offset = (int)(delta_x * 0.5);
    *result_bin = bin_left + bin_offset;
    *result_val = x_middle - (0.25 * delta_x * (x_left - x_right));
}