void SetBit(int *array, int bit_index) {
    int index = bit_index / 32;
    int offset = bit_index % 32;
    int mask = 1 << offset;
    array[index] |= mask;
}