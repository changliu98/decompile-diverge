void count_down(int *a, int *b) {
    if (*a > 0) {
        *a = *a - 1;
    }
    
    for (int i = 0; i < 5; i++) {
        if (b[i] > 0) {
            b[i] = b[i] - 1;
        }
    }
}