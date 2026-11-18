void update16(unsigned short *ptr, int threshold, int increment, unsigned short max_val) {
    if (*ptr <= threshold) {
        *ptr += increment;
    } else {
        *ptr = max_val;
    }
}