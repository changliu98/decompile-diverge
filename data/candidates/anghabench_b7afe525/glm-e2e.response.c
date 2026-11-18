int mt76_incr(int a, int b) {
    return (a + 1) & (b - 1);
}