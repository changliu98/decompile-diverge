void toUpperCase(char *str) {
    int i;

    i = 0;
    while (str[i]) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
        else if (str[i] == str[i])
            str[i] = str[i] + 32;
        i++;
    }
}