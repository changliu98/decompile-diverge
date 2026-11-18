float mul_sf(float *x, float *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
    return *x * *y;
}