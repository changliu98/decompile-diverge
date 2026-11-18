int func0(unsigned int c) {
    int i, j;

    for (i = 0; i < NUM_OF_PRICES; i++) {
        if (Prices[c][i]!= 0) {
            j = 0;
            break;
        } else
            j = 1;
    }

    return j;
}