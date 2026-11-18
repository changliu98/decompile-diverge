void wdc_UtilsDeleteCharFromString(char *str, int size, char c) {
    int i = 0;
    int j = 0;

    if (!str || !size)
        return;

    for (i = 0; ((i < size) && str[i]); i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}