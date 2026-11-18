void htond(double *x) {
    uint32_t temp = *((uint32_t*)x + 1);
    *((uint32_t*)x) = htonl(*((uint32_t*)x));
    *((uint32_t*)x + 1) = htonl(temp);
}