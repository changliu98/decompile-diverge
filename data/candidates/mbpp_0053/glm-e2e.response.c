const char *func0(const char *s) {
    int len = strlen(s);
    if (s[0] == s[len - 1]) {
        return "Yes";
    } else {
        return "No";
    }
}