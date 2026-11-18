int test_and_set_bit(int bit, int *set) {
    int i;
    set[bit >> 5] |= (1 << (bit & 31));
    return i;
}