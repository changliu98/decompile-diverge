int func0(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char result = 0;

    if (len1 % len2 == 0) {
        for (int i = 0; i < len1; i++) {
            if (s1[i] != s2[i % len2]) {
                result = 0;
                goto end;
            }
        }
        result = 1;
    }

end:
    return result & 1;
}