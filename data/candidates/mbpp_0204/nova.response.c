int func0(char *str, char c) {
    int i, j;

    i = 0;
    j = 0;
    while (j < strlen(str)) {
        if (str[j] == c)
            i++;
        else
            j++;
    }
    return (i);
}