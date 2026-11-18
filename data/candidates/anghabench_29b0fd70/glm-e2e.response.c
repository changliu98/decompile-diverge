float map(int a, int b, int c, float d, float e) {
    double f = (double)(e - d) * 1.0 / (double)(c - b);
    double g = (double)d + f * (double)(a - b);
    return (float)g;
}