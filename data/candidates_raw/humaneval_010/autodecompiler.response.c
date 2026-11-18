char* shortestPalindrome(char* s) {
    int l = strlen(s);
    char *r = (char *)malloc((l<<1)+1);
    if (!r) return NULL;
    int i, j, k;
    for (i = 0; i < l; i++) {
        int is_palin = 1;
        for (j = 0, k = l-i-1; j < (k-i)/2; j++, k--) {
            if (s[i+j] != s[k]) {
                is_palin = 0;
                break;
            }
        }
        if (is_palin) {
            strncpy(r, s, l);
            for (j = 0, k = l-i-1; j < i; j++, k++) {
                r[l+j] = s[k];
            }
            r[l+i] = '\0';
            return r;
        }
    }
    strncpy(r, s, l);
    for (j = 0, k = l-1; j < l; j++, k--) {
        r[l+j] = s[k];
    }
    r[l<<1] = '\0';
    return r;
}