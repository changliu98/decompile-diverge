int set_bit(int *num, int bit) {
    *num |= (1 << bit);
    return *num;
}