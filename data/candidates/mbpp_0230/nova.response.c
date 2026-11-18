char *func0(char *s, int *a) {
    int i = 0, j = 0;
    while (1) {
        if (s[j] == '\0')
            break;
        if (s[j] =='')
            ans[i++] = a[0];
        else
            ans[i++] = a[s[j] - '0' + 1];
        j++;
    }
    ans[i] = '\0';
    return ans;
}