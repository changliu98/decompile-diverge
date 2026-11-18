int check_strict_monotonicity(int *data, int n) {
    int i;
    char is_increasing = 0;

    for (i = 1; ; i++) {
        if (i >= n) {
            break;
        }
        if ((data[i] - data[i - 1]) > 0 && is_increasing == 1) {
            return 0;
        }
        if ((data[i] - data[i - 1]) < 0) {
            is_increasing = 1;
        }
    }

    return 1;
}