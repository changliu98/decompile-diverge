float func0(float *x, float *y) {
    float temp;
    if (x < y) {
        temp = *x;
        *x = *y;
        *y = temp;
    }
    return temp;
}