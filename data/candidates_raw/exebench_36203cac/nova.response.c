void func0(int bit, unsigned long *ptr) {
    ptr[bit / 8] |= (1UL << (bit % 8));
}