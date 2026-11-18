void make_double_bigendian(double *d) {
    union {
        double d;
        unsigned char c[sizeof(double)];
    } u;
    u.d = *d;
    *d = u.c[sizeof(double) - 1];
}