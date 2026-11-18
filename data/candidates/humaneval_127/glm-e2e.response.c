const char* func0(int a, int b, int c, int d) {
    int max_ac = (a > c) ? a : c;
    int min_bd = (b < d) ? b : d;
    int diff = min_bd - max_ac;

    if (diff < 2) {
        return "No";
    }

    for (int i = 2; i * i <= diff; i++) {
        if (diff % i == 0) {
            return "No";
        }
    }

    return "Yes";
}