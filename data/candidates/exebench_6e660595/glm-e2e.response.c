void IdealTrack(long a, long b, long c, long *d) {
    long num = b * (a - c) + c * (b + 1);
    long den = b + c;
    
    if (den != 0) {
        *d = num / den;
    } else {
        *d = 1;
    }
}