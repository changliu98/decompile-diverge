void warp_mat4_add_scaled(float z[16], float x[16], float y[16], float d)
{
    int i;

    for (i = 0; i < 16; i++) {
        z[i] = x[i] + d * y[i];
    }
}