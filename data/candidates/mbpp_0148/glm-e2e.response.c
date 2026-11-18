int func0(int n) {
    int c = closest(n);
    int s1 = sum_digits_single(c);
    int s2 = sum_digits_single(n - c);
    return s1 + s2;
}