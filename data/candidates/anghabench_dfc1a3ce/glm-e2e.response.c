void TH_float2halfbits(unsigned int *f, unsigned short *h) {
    unsigned int x = *f;
    unsigned int u = x & 0x7fffffff;
    unsigned short hs;

    if (u > 0x7f800000) {
        // NaN
        hs = 0x7fff;
    } else if (u > 0x477fefff) {
        // Overflow to Infinity
        hs = (x >> 16) & 0x8000 | 0x7c00;
    } else if (u < 0x33000001) {
        // Underflow to Zero
        hs = (x >> 16) & 0x8000;
    } else {
        // Normalized or Denormalized
        unsigned int e = (u >> 23) & 0xff;
        unsigned int m = u & 0x7fffff;
        unsigned int shift;
        
        if (e > 0x70) {
            // Normalized
            shift = 13;
            e = e - 0x70;
        } else {
            // Denormalized
            shift = 0x7e - e;
            e = 0;
            m |= 0x800000;
        }
        
        unsigned int a = 1 << shift;
        unsigned int half_a = a >> 1;
        unsigned int mask = a - 1;
        unsigned int remainder = m & mask;
        m >>= shift;
        
        // Round to nearest, ties to even
        if (remainder > half_a || (remainder == half_a && (m & 1))) {
            m++;
            if ((m & 0x3ff) == 0) {
                e++;
                m = 0;
            }
        }
        
        hs = ((x >> 16) & 0x8000) | (e << 10) | m;
    }

    *h = hs;
}