char *func0(char *text1) {
    size_t i, j, n;
    char *text2;

    n = strlen(text1);
    text2 = malloc(n + 1);
    if (text2 == NULL)
        return NULL;

    for (i = j = 0; i < n; i++)
        if ((((unsigned char *)(__ctype_b_loc()))[(int)(text1[i])] & (0x08)))
            text2[j++] = text1[i];

    text2[j] = '\0';
    return text2;
}