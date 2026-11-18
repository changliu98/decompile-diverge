int func0(char c) {
    char r;
    if (c > 63)
        r = '=';
    else
        r = tbl[c + 128];
    return r;
}