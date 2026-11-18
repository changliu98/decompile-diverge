int toup(int c) {
    int result;
    if (c >= 'a' && c <= 'z') {
        result = c - 'a' + 'A';
    } else {
        result = c;
    }
    return result;
}