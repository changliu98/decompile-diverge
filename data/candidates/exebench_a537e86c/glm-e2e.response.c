double dst_transform_push(double *dst, int *count, double value) {
    if (*count < 16) {
        int index = *count;
        *count = index + 1;
        dst[index] = value;
    }
    return value;
}