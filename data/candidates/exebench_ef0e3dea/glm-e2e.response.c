void sun_mjulianday2date(long jd, int *year, int *month, int *day) {
    long l = jd + 2399857; // 0x249f01
    long n = l + 1401;     // 0x579
    long p = (l * 4 + 274277) / 146097; // 0x42f65 and 0x23ab1
    int q = (p * 3) / 4;
    int j = n + q - 38;    // 0x26
    int r = (j * 4 + 3) % 1461; // 0x5b5
    int s = (r / 4) * 5 + 2;    // 0x2
    int t = (s % 153) / 5 + 1;  // 0x99 and 0x5
    
    *day = t;
    *month = ((s / 153 + 2) % 12) + 1;
    *year = j / 1461 - 4716 + (14 - *month) / 12; // 0x126c is 4716
}