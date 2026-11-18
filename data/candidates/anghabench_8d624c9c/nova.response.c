int toup(int c) {
    int r;

    if (c >= 'a' && c <= 'z')
        r = c - 'a' + 'A';
    else
        r = c;
    return r;
}