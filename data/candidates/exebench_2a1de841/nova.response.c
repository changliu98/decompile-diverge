double linsched_rand(unsigned int *seed) {
    unsigned int temp = (*seed) * 16807;
    temp = temp % 0x7fffffff;
    temp = temp / 2;
    *seed = temp;
    return (double)temp / 2147483647.0;
}