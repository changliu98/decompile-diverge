int func0(char *s) {
    int i = 0;
    int ans;
    while (1) {
        if (s[i] == '\0') {
            ans = -1;
            break;
        }
        if (isalpha(s[i])) {
            ans = i;
            break;
        }
        i++;
    }
    return ans;
}