int func0(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 % len2!= 0)
        return 0;
    int i;
    for (i = 0; i < len1; i++) {
        if (s1[i]!= s2[i % len2])
            return 0;
    }
    return 1;
}