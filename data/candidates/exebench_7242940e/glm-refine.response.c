void __cdecl bn_mul_comba4(unsigned int *r, unsigned int *a, unsigned int *b)
{
    uint64_t c1 = 0, c2 = 0, c3 = 0;

    // Column 0
    c1 += (uint64_t)a[0] * b[0];
    r[0] = (unsigned int)c1;
    c1 >>= 32;

    // Column 1
    c2 += (uint64_t)a[0] * b[1];
    c2 += (uint64_t)a[1] * b[0];
    c2 += c1;
    r[1] = (unsigned int)c2;
    c2 >>= 32;

    // Column 2
    c3 += (uint64_t)a[0] * b[2];
    c3 += (uint64_t)a[1] * b[1];
    c3 += (uint64_t)a[2] * b[0];
    c3 += c2;
    r[2] = (unsigned int)c3;
    c3 >>= 32;

    // Column 3
    c1 = 0;
    c1 += (uint64_t)a[0] * b[3];
    c1 += (uint64_t)a[1] * b[2];
    c1 += (uint64_t)a[2] * b[1];
    c1 += (uint64_t)a[3] * b[0];
    c1 += c3;
    r[3] = (unsigned int)c1;
    c1 >>= 32;

    // Column 4
    c2 = 0;
    c2 += (uint64_t)a[1] * b[3];
    c2 += (uint64_t)a[2] * b[2];
    c2 += (uint64_t)a[3] * b[1];
    c2 += c1;
    r[4] = (unsigned int)c2;
    c2 >>= 32;

    // Column 5
    c3 = 0;
    c3 += (uint64_t)a[2] * b[3];
    c3 += (uint64_t)a[3] * b[2];
    c3 += c2;
    r[5] = (unsigned int)c3;
    c3 >>= 32;

    // Column 6
    c1 = 0;
    c1 += (uint64_t)a[3] * b[3];
    c1 += c3;
    r[6] = (unsigned int)c1;
    c1 >>= 32;

    // Column 7
    r[7] = (unsigned int)c1;
}