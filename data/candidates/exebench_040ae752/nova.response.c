int test_and_clear_bit(int bit, int *set) {
    int tmp;
    set[bit] ^= -1;
    tmp = set[bit] >> 31;
    return tmp;
}