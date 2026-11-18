const char* func0(int a, int b, int c) {
    int p = (int)pow(a, 2);
    int q = (int)pow(b, 2);
    int r = (int)pow(c, 2);

    if (p == q + r || q == p + r || r == p + q) {
        return "Right-angled";
    } else if (p > q + r || q > p + r || r > p + q) {
        return "Obtuse-angled";
    } else {
        return "Acute-angled";
    }
}