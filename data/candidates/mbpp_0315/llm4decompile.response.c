char * func0(char * str) {
    int len = strlen(str);
    int currlen = 0;
    int maxlen = 0;
    int st = -1;
    int i;
    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            if (currlen % 2 == 0 && currlen > maxlen) {
                maxlen = currlen;
                st = i - currlen;
            }
            currlen = 0;
        } else {
            currlen++;
        }
    }
    if (currlen % 2 == 0 && currlen > maxlen) {
        maxlen = currlen;
        st = i - currlen;
    }
    if (st == -1) {
        return "-1";
    }
    strncpy(func0::result, str + st, (size_t) maxlen);
    func0::result[maxlen] = 0;
    return func0::result;
}