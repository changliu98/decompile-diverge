int func0(char *str) {
    int i, j;

    i = 0;
    j = 0;
    while (j < strlen(str)) {
        if (str[j] >= '0' && str[j] <= '9')
            i++;
        else
            j++;
    }
    return (i);
}