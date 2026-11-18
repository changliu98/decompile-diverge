float map(int x, int x1, int x2, float y1, float y2) {
    double m, y;
    m = (y2 - y1) / (x2 - x1) * 1.0;
    y = y1 + m * (x - x1);
    return y;
}