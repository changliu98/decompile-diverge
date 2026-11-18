int func0(char *s, char *t) {
    int i, j, k, l;
    int ans = 0;
    l = strlen(s);
    for (i = 0, j = 0; i < l; i++) {
        if (s[i]!= t[j])
            ans++;
        else
            j++;
    }
    int ans1;
    if (ans % 2 == 0)
        ans1 = ans / 2;
    else
        ans1 = -1;
    return ans1;
}