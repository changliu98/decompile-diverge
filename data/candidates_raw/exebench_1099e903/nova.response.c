void func0(char *str, char c, int *count) {
    int i = 0, j = 0;
    while (str[i]!= '\0') {
        if (i == j && str[i] == c) {
            i++;
            j++;
        } else if (str[j] == c || str[j] == '\0') {
            (*count)++;
            i = j;
        } else
            j++;
    }
}