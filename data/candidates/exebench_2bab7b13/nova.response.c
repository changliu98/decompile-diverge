void Swap8Bytes(char *s) {
    char t = s[0];
    s[0] = s[6];
    s[6] = t;
    t = s[1];
    s[1] = s[5];
    s[5] = t;
    t = s[2];
    s[2] = s[4];
    s[4] = t;
    t = s[3];
    s[3] = s[3];
}