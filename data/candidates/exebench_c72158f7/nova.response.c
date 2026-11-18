double rnd(unsigned long *x) {
    return (genrand_int32(x) & 0xffff) / (double)0x10000;
}