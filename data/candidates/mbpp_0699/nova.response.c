int func0(char *s, char *t) {
    int i, j, k, l;
    i = j = 0;
    l = strlen(s);
    while (i < l) {
        if (s[i]!= t[i])
            j++;
        i++;
    }
    int ans;
    if (j % 2 == 0)
        ans = j / 2;
    else
        ans = -1;
    return ans;
}