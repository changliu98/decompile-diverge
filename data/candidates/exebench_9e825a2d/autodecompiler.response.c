int C_Utils_compare_float_ptr(float *a, float *b) {
    float x = *a;
    float y = *b;
    int result;

    if (x == y) {
        result = 0;
    } else if (x < y) {
        result = -1;
    } else {
        result = 1;
    }

    return result;
}