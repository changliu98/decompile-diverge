char *func0(int n) {
    char s[10];
    sprintf(s, "%d", n);
    int i = 0, j = 0;
    while (s[i]!= '\0') {
        i += s[i] - '0';
        i++;
    }
    char *ans = (char *)malloc(sizeof(char) * i);
    int k = 0;
    while (k < i / 2) {
        char temp = ans[k];
        ans[k] = ans[i - k - 1];
        ans[i - k - 1] = temp;
        k++;
    }
    ans[i] = '\0';
    return ans;
}