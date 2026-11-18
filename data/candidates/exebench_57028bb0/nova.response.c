char *ft_strcpy(char *s1, char *s2) {
    int i, j, k;
    char *s;
    for (i = 0; s1[i]!= '\0'; i++)
        ;
    for (j = 0; s2[j]!= '\0'; j++)
        ;
    k = -1;
    if (j > i) {
        s = (char *)malloc(3536);
    } else {
        s = (char *)malloc(3536);
    }
    while (s2[++k]!= '\0') {
        if (s2[k]!= '\0') {
            s1[k] = s2[k];
        } else {
            s1[k] = '\0';
        }
    }
    return s;
}