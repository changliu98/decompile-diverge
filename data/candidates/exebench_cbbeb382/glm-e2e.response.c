int factors(int n, int *out) {
    int count = 0;
    int current = n;

    // Unrolled trial divisions for specific primes and composites
    while (current % 53 == 0) { current /= 53; out[count++] = 53; }
    while (current % 47 == 0) { current /= 47; out[count++] = 47; }
    while (current % 43 == 0) { current /= 43; out[count++] = 43; }
    while (current % 41 == 0) { current /= 41; out[count++] = 41; }
    while (current % 37 == 0) { current /= 37; out[count++] = 37; }
    while (current % 31 == 0) { current /= 31; out[count++] = 31; }
    while (current % 29 == 0) { current /= 29; out[count++] = 29; }
    while (current % 23 == 0) { current /= 23; out[count++] = 23; }
    while (current % 19 == 0) { current /= 19; out[count++] = 19; }
    while (current % 17 == 0) { current /= 17; out[count++] = 17; }
    while (current % 13 == 0) { current /= 13; out[count++] = 13; }
    while (current % 11 == 0) { current /= 11; out[count++] = 11; }
    while (current % 8  == 0) { current /= 8;  out[count++] = 8;  }
    while (current % 7  == 0) { current /= 7;  out[count++] = 7;  }
    while (current % 5  == 0) { current /= 5;  out[count++] = 5;  }
    while (current % 4  == 0) { current /= 4;  out[count++] = 4;  }
    while (current % 3  == 0) { current /= 3;  out[count++] = 3;  }
    while (current % 2  == 0) { current /= 2;  out[count++] = 2;  }

    // Wheel factorization for remaining factors
    if (current > 31) {
        int k = 2;
        while (current > 1) {
            int p1 = 6 * k - 1;
            int p2 = 6 * k + 1;
            
            while (current % p1 == 0) {
                out[count++] = p1;
                current /= p1;
            }
            
            while (current % p2 == 0) {
                out[count++] = p2;
                current /= p2;
            }
            k++;
        }
    }

    return count;
}