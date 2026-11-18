static unsigned int rand_r(unsigned int *x) {
    return (*x = *x * 1103515245 + 12345) % ((unsigned int)RAND_MAX + 1);
}