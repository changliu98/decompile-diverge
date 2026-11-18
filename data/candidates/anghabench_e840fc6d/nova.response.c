int base64_encode_value(char c) {
    char r;
    if (c > 63)
        r = '=';
    else
        r = tbl[c + 128];
    return r;
}