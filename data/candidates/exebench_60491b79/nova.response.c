int sync_test_and_set_bit(int bit, int *set) {
    int index;
    index = bit / INT_SIZE;
    set[index] = set[index] | (1 << bit);
    return 1;
}