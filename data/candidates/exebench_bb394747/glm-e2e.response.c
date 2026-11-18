int get_hashmask(int *p) {
    int mask = 1;
    while (mask < *p) {
        mask <<= 1; // Equivalent to mask *= 2;
    }
    *p = mask;
    return mask - 1;
}