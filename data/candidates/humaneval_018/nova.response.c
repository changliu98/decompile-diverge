int func0(char s1[], char s2[]) {
    int i, j, cnt = 0;
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 == 0)
        return 0;

    for (i = 0; i <= len1 - len2; i++) {
        if (strncmp(&s1[i], s2, len2) == 0)
            cnt++;
    }

    return cnt;
}