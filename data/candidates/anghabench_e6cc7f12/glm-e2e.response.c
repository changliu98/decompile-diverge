int aligned(int x) {
    return (x + 63) >> 6 << 6;
}