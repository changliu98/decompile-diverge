int alphabeta_cutoff(int value, int *alpha, int *beta, int is_maximizing) {
    if (is_maximizing != 0) {
        if (value > *alpha) {
            *alpha = value;
        }
    } else {
        if (value < *beta) {
            *beta = value;
        }
    }

    if (*beta <= *alpha) {
        return 1;
    } else {
        return 0;
    }
}