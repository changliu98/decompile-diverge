void __cdecl convertscreenvertex(float *vec, int resolutionx, int resolutiony)
{
    float half_res_x = (float)(resolutionx >> 1);
    float half_res_y = (float)(resolutiony >> 1);

    // X normalization: Maps screen space [0, resolutionx] to clip space [-1.0, 1.0]
    vec[0] = (vec[0] - half_res_x) / half_res_x;

    // Y normalization: Maps screen space [0, resolutiony] to clip space [1.0, -1.0] (Y-axis is inverted)
    vec[1] = (half_res_y - vec[1]) / half_res_x;

    // Z depth: Pushed to the far plane
    vec[2] = -1.0f;
}