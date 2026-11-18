int func0(int bit, int *set) {
    int i;
    set[bit >> 5] |= (1 << (bit & 31));
    return i;
}