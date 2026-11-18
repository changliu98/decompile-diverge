char* func0(int a, int b, int c) {
    char* result;
    if ((b * b) - (4 * a * c) > 0) {
        result = "2 solutions";
    } else if ((b * b) - (4 * a * c) == 0) {
        result = "1 solution";
    } else {
        result = "No solutions";
    }
    return result;
}