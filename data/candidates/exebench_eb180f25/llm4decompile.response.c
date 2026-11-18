double Mat_doubleSwap(double *a)
{
    union {
        double f;
        unsigned char b[sizeof(double)];
    } swap;

    swap.f = *a;
    swap.b[0] ^= swap.b[7];
    swap.b[1] ^= swap.b[6];
    swap.b[2] ^= swap.b[5];
    swap.b[3] ^= swap.b[4];
    swap.b[0] ^= swap.b[7];
    swap.b[1] ^= swap.b[6];
    swap.b[2] ^= swap.b[5];
    swap.b[3] ^= swap.b[4];
    *a = swap.f;

    return *a;
}