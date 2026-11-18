int func0(int a, int b, int c) {
    char result;
    if (a == b || b == c || c == a) {
        result = 1;
    } else {
        result = 0;
    }

    return (result & 1);
}