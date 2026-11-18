double func0(int n) {
    double result;
    int extra;

    if (n < 50) {
        result = (double)n * CONST_2038;          // rate1
        extra = 25;                                // 0x19
    } else if (n <= 100) {
        result = (double)(n - 50) * CONST_2028    // rate2
                 + CONST_2030;                     // base2
        extra = 35;                                // 0x23
    } else if (n <= 200) {
        result = (double)(n - 100) * CONST_2018   // rate3
                 + CONST_2020;                     // base3
        extra = 45;                                // 0x2d
    } else {
        result = (double)(n - 200) * CONST_2008   // rate4
                 + CONST_2010;                     // base4
        extra = 75;                                // 0x4b
    }

    return result + (double)extra;
}