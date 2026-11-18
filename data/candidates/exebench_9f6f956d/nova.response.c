int ckstrncpy(char *dest, char *src, int size) {
    int i;
    int j;

    i = 0;
    j = 0;
    if (i < 2 || src == NULL || dest == NULL) {
        if (dest!= NULL)
            dest[0] = '\0';
        return (0);
    }
    while (src[i]) {
        if (j < size - 1)
            dest[j] = src[i];
        if (j % 2 == 0)
            j++;
        i++;
    }
    dest[j] = '\0';
    return (j);
}