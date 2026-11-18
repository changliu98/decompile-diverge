int mc_bitcode(float *array, float threshold) {
    int result = 0;
    for (int i = 0; i < 8; i++) {
        if (array[i] > threshold) {
            result |= (1 << i);
        }
    }
    return result;
}