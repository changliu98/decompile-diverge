float get_near_num(float *x, float *y) {
    float temp;
    if (x < y) {
        temp = *x;
        *x = *y;
        *y = temp;
    }
    return temp;
}