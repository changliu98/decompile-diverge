int func0(float x, float y, float z) {
    int result;
    if (fabs(x * y + x * z + y * z - 2000000) < EPSILON &&
        fabs(x * x + y * y + z * z - 1000000) < EPSILON &&
        fabs(x * y * z - 1000000) < EPSILON) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}