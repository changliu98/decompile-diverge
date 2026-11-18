int func0(int a, int b, int c) {
    int min;
    if (b - 1 > c) {
        min = b - 1;
    } else {
        min = c;
    }
    return (a * min) / b;
}