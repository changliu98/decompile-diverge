int func0(int c) {
    int d;

    if (c >= 'a' && c <= 'z') {
        d = c - 'a';
    } else if (c >= '\240' && c <= '\254') {
        d = c - '\240';
    } else {
        d = c;
    }

    return d;
}