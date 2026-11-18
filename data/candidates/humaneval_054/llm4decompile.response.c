int func0(char *s0, char *s1)
{
    int len0 = strlen(s0);
    int len1 = strlen(s1);
    int i, j;
    for (i = 0; i < len0; i++) {
        int found = 0;
        for (j = 0; j < len1; j++) {
            if (s0[i] == s1[j]) {
                found = 1;
                break;
            }
        }
        if (!found)
            return 0;
    }
    for (i = 0; i < len1; i++) {
        int found = 0;
        for (j = 0; j < len0; j++) {
            if (s1[i] == s0[j]) {
                found = 1;
                break;
            }
        }
        if (!found)
            return 0;
    }
    return 1;
}