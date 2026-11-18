void setbit(int bit, unsigned long long *bits) {
    bits[bit / 64] ^= (1ULL << (bit % 64));
}