double func0(double val, int *size, double *buffer) {
    if (*size < BUFFER_SIZE) {
        buffer[(*size)++] = val;
    }
    return val;
}