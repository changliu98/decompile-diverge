int getOffset(int x, int y, int width) {
    return width - ((y * y) + 1) * 4 * x;
}