void change_bit(int bit, unsigned long long *bits) {
    bits[bit / 64] ^= (1ULL << (bit % 64));
}