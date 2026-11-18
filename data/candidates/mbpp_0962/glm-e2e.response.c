int func0(int a, int b) {
    int half_b = b / 2;
    int term1 = half_b * (half_b + 1);
    int term2 = ((a - 1) * (a + 1)) / 2;
    return term1 - term2;
}