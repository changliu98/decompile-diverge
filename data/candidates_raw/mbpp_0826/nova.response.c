char *func0(int a, int b, int c) {
    int x = pow(a, 2);
    int y = pow(b, 2);
    int z = pow(c, 2);
    char *result;
    if (x == y + z || y == x + z || z == x + y) {
        result = "right";
    } else if (x > y + z || y > x + z || z > x + y) {
        result = "obtuse";
    } else {
        result = "acute";
    }
    return result;
}