int func0(char *s) {
    int i, j, k, l, m, n;
    int t[26];

    n = strlen(s);
    memset(t, 0, sizeof(t));
    for (i = 0; i < n; i++) {
        t[s[i] - 'a']++;
    }

    for (i = 0; i < 26; i++) {
        if (t[i] > m)
            m = t[i];
        else
            break;
    }

    return n - m;
}