int func0(char *s) {
    char *p = strstr(s, "10");
    int ans;
    if (p) {
        if (strlen(p) % 2 == 1)
            ans = 1;
        else
            ans = 0;
    } else
        ans = 0;
    return ans;
}