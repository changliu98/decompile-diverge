double readDummyArray(double *dummy, size_t sizeMB) {
    double sum = 0;
    for (size_t i = 0; i < sizeMB / sizeof(double); i++) {
        sum += dummy[i];
    }
    dummy[0] = sum / (sizeMB / sizeof(double));
    return sum;
}