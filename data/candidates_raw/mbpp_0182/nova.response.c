void func0(char *s, char *n, char *v, char *p, char *c) {
    int i, nn, vv, pp, cc;
    nn = vv = pp = cc = 0;
    for (i = 0; i < strlen(s); i++) {
        if (isupper(s[i]))
            n[nn++] = s[i];
        else if (islower(s[i]))
            v[vv++] = s[i];
        else if (isdigit(s[i]))
            p[pp++] = s[i];
        else if (s[i] == '!' || s[i] == '.' || s[i] == '?')
            c[cc++] = s[i];
    }
    n[nn] = v[vv] = p[pp] = c[cc] = '\0';
}