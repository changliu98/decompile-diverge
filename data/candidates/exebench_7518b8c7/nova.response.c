int max(float *ptr) {
    int i, index = 0;
    float max = *ptr;
    for (i = 0; i < 3; i++) {
        if (max < *(ptr + i)) {
            index = i;
            max = *(ptr + i);
        }
    }
    return index;
}