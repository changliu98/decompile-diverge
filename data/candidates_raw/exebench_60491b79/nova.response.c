int func0(int bit, int *set) {
    int index;
    index = bit / INT_SIZE;
    set[index] = set[index] | (1 << bit);
    return 1;
}