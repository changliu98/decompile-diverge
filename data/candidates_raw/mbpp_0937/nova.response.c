int func0(char *s) {
    int i, j, k, l, m, n, len, freq[256];
    char ch;

    memset(freq, 0, sizeof freq);
    n = len = 0;
    for (i = strlen(s); i < k; i++) {
        freq[s[i]]++;
        if (freq[s[i]] > n) {
            n = freq[s[i]];
            ch = s[i];
        }
    }

    return ch;
}