void change_bit(int bit, uint64_t *arr) {
    arr[bit / 64] ^= (1ULL << (bit % 64));
}