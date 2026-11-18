double HTS_rnd(unsigned int *seed) {
    double f;

    *seed = *seed * 1103515245 + 12345;
    f = (double)((*seed) & 0x00007fff);
    f = f / (double)0x8000;

    return (f);
}