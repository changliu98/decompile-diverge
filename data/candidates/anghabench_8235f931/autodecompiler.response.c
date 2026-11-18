int lowercase(int c) {
    int ret;
    if ('A' <= c && c <= 'Z') {
        ret = c - 'A' + 'a';
    } else {
        ret = c;
    }
    return ret;
}