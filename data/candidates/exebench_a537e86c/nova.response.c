double dst_transform_push(double val, int *size, double *buffer) {
    if (*size < BUFFER_SIZE) {
        buffer[(*size)++] = val;
    }
    return val;
}