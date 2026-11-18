bool func0(int x, int y) {
    while (x > 0 && y > 0) {
        x /= 10;
        y /= 10;
    }
    return x == 0 && y == 0;
}