int hex2int(int c) {
    int d;

    if (c >= 'a' && c <= 'f')
        d = c + 10 - 'a';
    else if (c >= 'A' && c <= 'F')
        d = c + 10 - 'A';
    else
        d = c - '0';
    return d;
}