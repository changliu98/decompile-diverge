int func0(char *s, int n) {
    char s1[11], s2[11];
    memset(s1, 0, 11);
    memset(s2, 0, 11);
    int i = 0, j = 0, k = 0;
    while (1) {
        if (s[k] == '\0')
            break;
        if (isdigit(s[k])) {
            if (i == 0)
                s1[j++] = s[k];
            else
                s2[j++] = s[k];
        } else {
            if (i == 0 && j > 0) {
                i = 1;
                j = 0;
            }
        }
        k++;
    }
    int ans1 = atoi(s1);
    int ans2 = n - ans1;
    int ans = ans2 - atoi(s2);
    return ans;
}