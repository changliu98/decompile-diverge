int func0(char *s) {
    int i, j, k, l, m, n;
    int a[26];
    int ans;

    memset(a, 0, sizeof(a));
    a['a' - 'a'] = 1;
    a['e' - 'a'] = 5;
    a['i' - 'a'] = 10;
    a['o' - 'a'] = 50;
    a['u' - 'a'] = 100;
    a['y' - 'a'] = 500;

    ans = 0;
    l = strlen(s);
    for (i = 0; i < l; i++) {
        if (i > 0 && a[s[i] - 'a'] > a[s[i - 1] - 'a']) {
            ans += a[s[i] - 'a'] - 2 * a[s[i - 1] - 'a'];
        } else {
            ans += a[s[i] - 'a'];
        }
    }

    return ans;
}