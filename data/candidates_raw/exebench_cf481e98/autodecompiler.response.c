void invSqrt(float x, float *y) {
    float xhalf = 0.5f*x;
    int i = *(int*)&x;

    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);

    if(x > 0)
        *y = 1.0f/x;
    else
        *y = 0.0f;
}