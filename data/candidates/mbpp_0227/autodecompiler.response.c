int func0(int x, int y, int z) {
    int smallest;
    if (x <= y && x <= z) {
        smallest = x;
    } else if (y <= x && y <= z) {
        smallest = y;
    } else {
        smallest = z;
    }
    return smallest;
}