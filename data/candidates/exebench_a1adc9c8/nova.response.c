char *upcase(char *str) {
    int i;

    i = 0;
    while (str[i]) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
        else
            str[i] = str[i];
        i++;
    }
    return (str);
}