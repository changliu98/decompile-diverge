int func0(int bit, int *set) {
    int tmp;
    set[bit] ^= -1;
    tmp = set[bit] >> 31;
    return tmp;
}