int func0(int a, int b) {
    int result;
    int term1;
    int term2;

    if (a < b) {
        result = -1;
    } else {
        term1 = (a - b + 1) * (a - b + 2) / 2;
        term2 = (a - 2 * b + 1) * (a - 2 * b + 2) / 2;
        result = term1 + term2;
    }

    return result;
}