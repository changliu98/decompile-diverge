char *func0(char *str, char c) {
    int i, j, k, l;
    i = j = k = l = 0;
    while (1) {
        if (str[i] == '\0')
            break;
        if (str[i] == c)
            j++;
        i++;
    }
    char *s = (char *)malloc(sizeof(char) * (strlen(str) - j + 1));
    while (1) {
        if (str[l] == '\0')
            break;
        if (str[l]!= c)
            s[k++] = str[l];
        l++;
    }
    s[k] = '\0';
    return s;
}